// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.13.
//
//    DiaperGlu v5.13 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.13 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.13; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// February 2, 2025           //
// version 5.13               //
// /////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "diapergluforth.h"
// #include <dlfcn.h>
#ifdef DGLU_OS_FREEBSD
#include <unistd.h>
#endif

unsigned char megabuf[0x10000]; // a test does not need to be re-entrant

void testdg_compareforconditionsub ()
{
    UINT64 x;
    UINT32 xlo, xhi;

    printf("testing dg_compareforconditionsub\n");

    x = dg_compareforconditionsub(0, 0);

    if ((x & 0x40) != 0x40)
    {
        printf(" - FAIL! dg_compareforconditionsub(0, 0) & 0x40 did not give 0x40, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }


    x = dg_compareforconditionsub(0, 1);

    if ((x & 0x40) != 0)
    {
        printf(" - FAIL! dg_compareforconditionsub(0, 1,) & 0x40 did not give 0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_compareforconditionsub(0x10, 0x11);

    if ((x & 0x1) != 0x0)
    {
        printf(" - FAIL! dg_compareforconditionsub(0x10, 0x11) & 0x1 did not give 0x0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_compareforconditionsub(0x11, 0x10);

    if ((x & 0x1) != 0x1)
    {
        printf(" - FAIL! dg_compareforconditionsub(0x11, 0x10) & 0x1 did not give 0x1, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }
}

void testdg_getulowestbitsmask ()
{
    INT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_getulowestbitsmask\n");
    
    x = dg_getulowestbitsmask(0); 

    if (x != 0)
    {
        printf(" - FAIL! dg_getulowestbitsmask(0) did not give 0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbitsmask(1);   

    if (x != 1)
    {
        printf(" - FAIL! dg_getulowestbitsmask(1) did not give 1, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbitsmask(2);   

    if (x != 3)
    {
        printf(" - FAIL! dg_getulowestbitsmask(3) did not give 3, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbitsmask(3);   

    if (x != 7)
    {
        printf(" - FAIL! dg_getulowestbitsmask(3) did not give 7, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbitsmask(0x3f); 

    if (x != 0x7FFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestbitsmask(0x3F) did not give 0x7FFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbitsmask(0x3e); 

    if (x != 0x3FFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestbitsmask(0x3E) did not give 0x3FFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbitsmask(0x40); 

    if (x != 0xFFFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestbitsmask(0x40) did not give 0xFFFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbitsmask(0x41); 

    if (x != 0xFFFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestbitsmask(0x41) did not give 0xFFFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbitsmask(0x42); 

    if (x != 0xFFFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestbitsmask(0x42) did not give 0xFFFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }
}

void testdg_getulowestbits ()
{
    INT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_getulowestbits\n");
    
    x = dg_getulowestbits(0, 0); 

    if (x != 0)
    {
        printf(" - FAIL! dg_getulowestbits(0, 0) did not give 0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(1, 0);   

    if (x != 0)
    {
        printf(" - FAIL! dg_getulowestbits(1, 0) did not give 0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(1, 1);   

    if (x != 1)
    {
        printf(" - FAIL! dg_getulowestbits(1, 1) did not give 1, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0, 1);   

    if (x != 0)
    {
        printf(" - FAIL! dg_getulowestbits(0, 1) did not give 0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(2, 1);   

    if (x != 0)
    {
        printf(" - FAIL! dg_getulowestbits(2, 1) did not give 0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(1, 2);   

    if (x != 1)
    {
        printf(" - FAIL! dg_getulowestbits(1, 2) did not give 1, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(6, 1);   

    if (x != 0)
    {
        printf(" - FAIL! dg_getulowestbits(6, 1) did not give 0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(6, 2);   

    if (x != 2)
    {
        printf(" - FAIL! dg_getulowestbits(6, 2) did not give 2, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(6, 3);   

    if (x != 6)
    {
        printf(" - FAIL! dg_getulowestbits(6, 3) did not give 6, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0xE0, 3); 

    if (x != 0x0)
    {
        printf(" - FAIL! dg_getulowestbits(0xE0, 3) did not give 0x0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0x0E, 3); 

    if (x != 6)
    {
        printf(" - FAIL! dg_getulowestbits(0x0E, 3) did not give 6, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0x0E, 4); 

    if (x != 0x0E)
    {
        printf(" - FAIL! dg_getulowestbits(0x0E, 4) did not give 0x0E, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0x0E, 5); 

    if (x != 0x0E)
    {
        printf(" - FAIL! dg_getulowestbits(0x0E, 5) did not give 0x0E, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0xFF5A, 5); 

    if (x != 0x1A)
    {
        printf(" - FAIL! dg_getulowestbits(0xFF5A, 5) did not give 0x1A, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0x15A, 8); 

    if (x != 0x5A)
    {
        printf(" - FAIL! dg_getulowestbits(0x5A, 8) did not give 0x5A, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0x15A, 9); 

    if (x != 0x15A)
    {
        printf(" - FAIL! dg_getulowestbits(0x15A, 9) did not give 0x15A, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0x15A, 6); 

    if (x != 0x1A)
    {
        printf(" - FAIL! dg_getulowestbits(0x1A, 6) did not give 0x1A, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0x8000000000000000, 1); 

    if (x != 0)
    {
        printf(" - FAIL! dg_getulowestbits(0, 1) did not give 0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0x8000000000000000, 0x40); 

    if (x != 0x8000000000000000)
    {
        printf(" - FAIL! dg_getulowestbits(0x8000000000000000, 0x40) did not give 0x8000000000000000, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0xC000000000000000, 0x40); 

    if (x != 0xC000000000000000)
    {
        printf(" - FAIL! dg_getulowestbits(0xC000000000000000, 0x40) did not give 0xC000000000000000, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0xC000000000000000, 0x3f); 

    if (x != 0x4000000000000000)
    {
        printf(" - FAIL! dg_getulowestbits(0xC000000000000000, 0x3f) did not give 0x4000000000000000, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0xFFFFFFFFFFFFFFFF, 0x40); 

    if (x != 0xFFFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestbits(0xFFFFFFFFFFFFFFFF, 0x40) did not give 0xFFFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0xFFFFFFFFFFFFFFFF, 0x41); 

    if (x != 0xFFFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestbits(0xFFFFFFFFFFFFFFFF, 0x41) did not give 0xFFFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0xFFFFFFFFFFFFFFFF, 0x42); 

    if (x != 0xFFFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestbits(0xFFFFFFFFFFFFFFFF, 0x42) did not give 0xFFFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF); 

    if (x != 0xFFFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestbits(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF) did not give 0xFFFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestbits(0xFEEFFFFFFFFFF00F, 0xFFFFFFFFFFFFFFFF); 

    if (x != 0xFEEFFFFFFFFFF00F)
    {
        printf(" - FAIL! dg_getulowestbits(0xFEEFFFFFFFFFF00F, 0xFFFFFFFFFFFFFFFF) did not give 0xFEEFFFFFFFFFF00F, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }
}

void testdg_getulowestsetbits ()
{
    INT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_getulowestsetbits\n");
    
    x = dg_getulowestsetbits(0, 0);   // scan for 0th set bit... should return not found

    if (x != 0)
    {
        printf(" - FAIL! dg_getulowestsetbits(0, 0) did not give 0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(1, 0);   // scan for 0th set bit... should return not found

    if (x != 0)
    {
        printf(" - FAIL! dg_getulowestsetbits(1, 0) did not give 0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(1, 1);   

    if (x != 1)
    {
        printf(" - FAIL! dg_getulowestsetbits(1, 1) did not give 1, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0, 1);   // scan for 0th set bit... should return not found

    if (x != 0)
    {
        printf(" - FAIL! dg_getulowestsetbits(0, 1) did not give 0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(2, 1);   

    if (x != 2)
    {
        printf(" - FAIL! dg_getulowestsetbits(2, 1) did not give 2, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(6, 1);   

    if (x != 2)
    {
        printf(" - FAIL! dg_getulowestsetbits(6, 1) did not give 2, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(6, 2);   

    if (x != 6)
    {
        printf(" - FAIL! dg_getulowestsetbits(6, 2) did not give 6, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0xE0, 3); 

    if (x != 0xE0)
    {
        printf(" - FAIL! dg_getulowestsetbits(0xE0, 3) did not give 0xE0, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0x0E, 2); 

    if (x != 6)
    {
        printf(" - FAIL! dg_getulowestsetbits(0x0E, 2) did not give 6, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0xFF5A, 5); 

    if (x != 0x15A)
    {
        printf(" - FAIL! dg_getulowestsetbits(0xFF5A, 5) did not give 0x15A, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0x15A, 5); 

    if (x != 0x15A)
    {
        printf(" - FAIL! dg_getulowestsetbits(0x15A, 5) did not give 0x15A, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0x15A, 6); 

    if (x != 0x15A)
    {
        printf(" - FAIL! dg_getulowestsetbits(0x15A, 6) did not give 0x15A, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0x8000000000000000, 1); 

    if (x != 0x8000000000000000)
    {
        printf(" - FAIL! dg_getulowestsetbits(0x8000000000000000, 1) did not give 0x8000000000000000, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0x8000000000000000, 2); 

    if (x != 0x8000000000000000)
    {
        printf(" - FAIL! dg_getulowestsetbits(0x8000000000000000, 2) did not give 0x8000000000000000, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0xC000000000000000, 2); 

    if (x != 0xC000000000000000)
    {
        printf(" - FAIL! dg_getulowestsetbits(0xC000000000000000, 2) did not give 0xC000000000000000, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0xC000000000000000, 3); 

    if (x != 0xC000000000000000)
    {
        printf(" - FAIL! dg_getulowestsetbits(0xC000000000000000, 3) did not give 0xC000000000000000, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0xB000000000000000, 2); 

    if (x != 0x3000000000000000)
    {
        printf(" - FAIL! dg_getulowestsetbits(0xB000000000000000, 2) did not give 0x3000000000000000, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0xFFFFFFFFFFFFFFFF, 0x40); 

    if (x != 0xFFFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestsetbits(0xFFFFFFFFFFFFFFFF, 0x40) did not give 0xFFFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0xFFFFFFFFFFFFFFFF, 0x41); 

    if (x != 0xFFFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestsetbits(0xFFFFFFFFFFFFFFFF, 0x41) did not give 0xFFFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0xFFFFFFFFFFFFFFFF, 0x42); 

    if (x != 0xFFFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestsetbits(0xFFFFFFFFFFFFFFFF, 0x42) did not give 0xFFFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF); 

    if (x != 0xFFFFFFFFFFFFFFFF)
    {
        printf(" - FAIL! dg_getulowestsetbits(0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF) did not give 0xFFFFFFFFFFFFFFFF, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }

    x = dg_getulowestsetbits(0xFEEFFFFFFFFFF00F, 0xFFFFFFFFFFFFFFFF); 

    if (x != 0xFEEFFFFFFFFFF00F)
    {
        printf(" - FAIL! dg_getulowestsetbits(0xFEEFFFFFFFFFF00F, 0xFFFFFFFFFFFFFFFF) did not give 0xFEEFFFFFFFFFF00F, got ");
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("%08x%08x\n", xhi, xlo);
    }
}

void testdg_scanforuthsetbit ()
{
    INT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_scanforuthsetbit\n");
    
    x = dg_scanforuthsetbit(0, 0);   // scan for 0th set bit... should return not found

    if (x != 0x40)
    {
        printf(" - FAIL! dg_scanforuthsetbit(0, 0) did not give 0x40\n");
    }

    x = dg_scanforuthsetbit(1, 0);   // scan for 0th set bit... should return not found

    if (x != 0x40)
    {
        printf(" - FAIL! dg_scanforuthsetbit(0, 1) did not give 0x40\n");
    }

    x = dg_scanforuthsetbit(2, 0);    // scan for 0th set bit... should return not found

    if (x != 0x40)
    {
        printf(" - FAIL! dg_scanforuthsetbit(2, 0) did not give 0x40\n");
    }

    x = dg_scanforuthsetbit(0, 1);  // scan for first bit set... but there are none... 

    if (x != 0x40)
    {
        printf(" - FAIL! dg_scanforuthsetbit(0, 1) did not give 0x40\n");
    }

    x = dg_scanforuthsetbit(1, 1);  // scan for first bit set in 1... should return bit 0

    if (x != 0)
    {
        printf(" - FAIL! dg_scanforuthsetbit(1, 1) did not give 0\n");
    }

    x = dg_scanforuthsetbit(2, 1);

    if (x != 1)
    {
        printf(" - FAIL! dg_scanforuthsetbit(2, 1) did not give 1\n");
    }

    x = dg_scanforuthsetbit(0x8000000000000000, 1);

    if (x != 0x3f)
    {
        printf(" - FAIL! dg_scanforuthsetbit(0x8000000000000000, 1) did not give 0x3f\n");
    }

    x = dg_scanforuthsetbit(3, 2);

    if (x != 1)
    {
        printf(" - FAIL! dg_scanforuthsetbit(3, 2) did not give 1\n");
    }

    x = dg_scanforuthsetbit(5, 2);

    if (x != 2)
    {
        printf(" - FAIL! dg_scanforuthsetbit(5, 2) did not give 2\n");
    } 

    x = dg_scanforuthsetbit(0x0a, 2);

    if (x != 3)
    {
        printf(" - FAIL! dg_scanforuthsetbit(0x0a, 2) did not give 3\n");
    }

    x = dg_scanforuthsetbit(0x1a, 2);

    if (x != 3)
    {
        printf(" - FAIL! dg_scanforuthsetbit(0x0a, 2) did not give 3\n");
    }

    x = dg_scanforuthsetbit(0x1a, 2);

    if (x != 3)
    {
        printf(" - FAIL! dg_scanforuthsetbit(0x1a, 2) did not give 3\n");
    }

    x = dg_scanforuthsetbit(0x1a, 3);

    if (x != 4)
    {
        printf(" - FAIL! dg_scanforuthsetbit(0x1a, 3) did not give 4\n");
    }

    x = dg_scanforuthsetbit(0x1a, 4);

    if (x != 0x40)
    {
        printf(" - FAIL! dg_scanforuthsetbit(0x1a, 4) did not give 0x40\n");
    }

    x = dg_scanforuthsetbit(largestunsignedint, 0x40);

    if (x != 0x3f)
    {
        printf(" - FAIL! dg_scanforuthsetbit(-1, 0x40) did not give 0x3f\n");
    }
}

void testdg_setbit ()
{
    INT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_setbit\n");
    
    x = dg_setbit(0, 0);

    if (x != 1)
    {
        printf(" - FAIL! dg_setbit(0, 0) did not give 1\n");
    }

    x = dg_setbit(1, 0);

    if (x != 1)
    {
        printf(" - FAIL! dg_setbit(1, 0) did not give 1\n");
    }

    x = dg_setbit(2, 0);

    if (x != 3)
    {
        printf(" - FAIL! dg_setbit(2, 0) did not give 3\n");
    }

    x = dg_setbit(0, 1);

    if (x != 2)
    {
        printf(" - FAIL! setbit(0, 1) did not give 2\n");
    }

    x = dg_setbit(0, 2);

    if (x != 4)
    {
        printf(" - FAIL! setbit(0, 2) did not give 4\n");
    }

    x = dg_setbit(0x8000000000000000, 1);

    if (x != 0x8000000000000002)
    {
        printf(" - FAIL! setbit(0x8000000000000000, 1) did not give 0x8000000000000002\n");
    }

    x = dg_setbit(0x0000000000000000, 0x3f);

    if (x != 0x8000000000000000)
    {
        printf(" - FAIL! setbit(0x0000000000000000, 0x3f) did not give 0x8000000000000000\n");
    } 
}

void testdg_clrbit ()
{
    INT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_clrbit\n");
    
    x = dg_clrbit(0xffffffffffffffff, 0);

    if (x != 0xfffffffffffffffe)
    {
        printf(" - FAIL! dg_clrbit(0xffffffffffffffff, 0) did not give 0xfffffffffffffffe\n");
    }

    x = dg_clrbit(0xfffffffffffffffd, 0);

    if (x != 0xfffffffffffffffc)
    {
        printf(" - FAIL! dg_clrbit(0xfffffffffffffffd, 0) did not give 0xfffffffffffffffc\n");
    }

    x = dg_clrbit(0xfffffffffffffffb, 0);

    if (x != 0xfffffffffffffffa)
    {
        printf(" - FAIL! dg_clrbit(0xfffffffffffffffb, 0) did not give 0xfffffffffffffffa\n");
    }

    x = dg_clrbit(0xffffffffffffffff, 1);

    if (x != 0xfffffffffffffffd)
    {
        printf(" - FAIL! setbit(0xffffffffffffffff, 1) did not give 0xfffffffffffffffd\n");
    }

    x = dg_clrbit(0xffffffffffffffff, 2);

    if (x != 0xfffffffffffffffb)
    {
        printf(" - FAIL! clrbit(0xffffffffffffffff, 2) did not give 0xfffffffffffffffb\n");
    }

    x = dg_clrbit(0x7fffffffffffffff, 1);

    if (x != 0x7ffffffffffffffd)
    {
        printf(" - FAIL! setbit(0x7fffffffffffffff, 1) did not give 0x7ffffffffffffffd\n");
    }

    x = dg_clrbit(0xffffffffffffffff, 0x3f);

    if (x != 0x7fffffffffffffff)
    {
        printf(" - FAIL! setbit(0xffffffffffffffff, 0x3f) did not give 0x7fffffffffffffff\n");
    } 
}

void testdg_notbit ()
{
    INT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_notbit\n");
    
    x = dg_notbit(0, 0);

    if (x != 1)
    {
        printf(" - FAIL! dg_clrbit(0, 0) did not give 1\n");
    }

    x = dg_notbit(1, 0);

    if (x != 0)
    {
        printf(" - FAIL! dg_clrbit(1, 0) did not give 0\n");
    }

    x = dg_notbit(0, 1);

    if (x != 2)
    {
        printf(" - FAIL! dg_clrbit(0, 1) did not give 2\n");
    }

    x = dg_notbit(2, 1);

    if (x != 0)
    {
        printf(" - FAIL! dg_clrbit(2, 1) did not give 0\n");
    }

    x = dg_notbit(0, 0x3f);

    if (x != 0x8000000000000000)
    {
        printf(" - FAIL! dg_clrbit(0, 0x3f) did not give 0x8000000000000000\n");
    }

    x = dg_notbit(0x8000000000000000, 0x3f);

    if (x != 0)
    {
        printf(" - FAIL! dg_clrbit(0x8000000000000000, 0x3f) did not give 0\n");
    }
}

void testdg_twototheu ()
{
    INT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_twototheu\n");
    
    x = dg_twototheu(0);

    if (x != 1)
    {
        printf(" - FAIL! 2 ^ 0x00 did not give 1\n");
    }

    x = dg_twototheu(1);

    if (x != 2)
    {
        printf(" - FAIL! 2 ^ 0x01 did not give 2\n");
    }

    x = dg_twototheu(2);

    if (x != 4)
    {
        printf(" - FAIL! 2 ^ 0x02 did not give 4\n");
    }

    x = dg_twototheu(3);

    if (x != 8)
    {
        printf(" - FAIL! 2 ^ 0x03 did not give 8\n");
    }

    x = dg_twototheu(8);

    if (x != 0x100)
    {
        printf(" - FAIL! 2 ^ 0x08 did not give 0x100\n");
    }

    x = dg_twototheu(0x10);

    if (x != 0x10000)
    {
        printf(" - FAIL! 2 ^ 0x10 did not give 0x10000\n");
    }

    x = dg_twototheu(0x20);

    if (x != 0x100000000)
    {
        printf(" - FAIL! 2 ^ 0x20 did not give 0x100000000\n");
    }

    x = dg_twototheu(0x3f);

    if (x != 0x8000000000000000)
    {
        printf(" - FAIL! 2 ^ 0x3f did not give 0x8000000000000000\n");
    }

    x = dg_twototheu(0x40);

    if (x != 1)
    {
        printf(" - FAIL! 2 ^ 0x40 did not give 1\n");
    }

    x = dg_twototheu(0x41);

    if (x != 2)
    {
        printf(" - FAIL! 2 ^ 0x41 did not give 2\n");
    }
}

void testdg_n8ton64 ()
{
    INT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_n8ton64\n");
    
    x = dg_n8ton64(0);

    if (x != 0)
    {
        printf(" - FAIL! 0x00 sign extended did not give 0\n");
    }

    x = dg_n8ton64(0x80);

    if (x != (INT64)((UINT64)0xffffffffffffff80))
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf(" - FAIL! 0x80 sign extended did not give 0xffffffffffffff80, got %08x%08x\n", xhi, xlo);        
    }

    x = dg_n8ton64(0xff);

    if (x != 0xffffffffffffffff)
    {
        printf(" - FAIL! 0xff sign extended did not give 0xffffffffffffffff\n");
    }
}


void testdg_n16ton64 ()
{
    INT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_n16ton64\n");
    
    x = dg_n16ton64(0);

    if (x != 0)
    {
        printf(" - FAIL! 0x0000 sign extended did not give 0\n");
    }

    x = dg_n16ton64(0x8000);

    if (x != (INT64)0xffffffffffff8000)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf(" - FAIL! 0x8000 sign extended did not give 0xffffffffffff8000, got %08x%08x\n", xhi, xlo);
    }

    x = dg_n16ton64(0xffff);

    if (x != 0xffffffffffffffff)
    {
        printf(" - FAIL! 0xffff sign extended did not give 0xffffffffffffffff\n");
    }
}


void testdg_n32ton64 ()
{
    INT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_n32ton64\n");
    
    x = dg_n32ton64(0);

    if (x != 0)
    {
        printf(" - FAIL! 0x00000000 sign extended did not give 0\n");
    }

    x = dg_n32ton64(0x80000000);

    if (x != (INT64)((UINT64)0xffffffff80000000))
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf(" - FAIL! 0x80000000 sign extended did not give 0xffffffff80000000, got %08x%08x\n", xhi, xlo);
    }

    x = dg_n32ton64(0xffffffff);

    if (x != 0xffffffffffffffff)
    {
        printf(" - FAIL! 0xffffffff sign extended did not give 0xffffffffffffffff\n");
    }
}


void testmaxu32comparecompilation()
{
    UINT64 x = 0;

    printf("testing compilation of comparing UINT64 with max UINT32 constant\n");

    if (x > 0xffffffff)
    {
        printf(" - FAIL! 0 compared greater than 0xFFFFFFFF\n");
    }

    ((UINT32*)(&x))[0] = 0xffffffff;

    if (x > 0xffffffff)
    {
        printf(" - FAIL! 0xffffffff compared greater than 0xFFFFFFFF\n");
    }

    if (x != 0xffffffff)
    {
        printf(" - FAIL! 0xffffffff was not equal to 0xFFFFFFFF\n");
    }

    ((UINT32*)(&x))[0] = 0;

    ((UINT32*)(&x))[1] = 1;

    if (x <= 0xffffffff)
    {
        printf(" - FAIL! 0x100000000 compared less than or equal to 0xFFFFFFFF\n");
    }
}

void testu64constantcompilation()
{
    UINT64 x = 0;

    printf("testing compilation of UINT64 constant\n");

    x = 0x1314151687868582;

    if (((UINT32*)(&x))[1] != 0x13141516)
    {
        printf(" - FAIL! high 32 bits incorrect\n");
    }

    if (((UINT32*)(&x))[0] != 0x87868582)
    {
        printf(" - FAIL! low 32 bits incorrect\n");
    }
}

// Windows C compiler (and Mac too) sign extends negative constants to 32 bits, then unsign
//      extends them to 64 bits. https://docs.microsoft.com/en-us/windows/console/getstdhandle
/*
void testmaxnegi32constantcompilation()
{
    INT64 x = 0;

    printf("testing compilation of max negative int32 constant - this test fails on Windows. (so I'm not using this constant.)\n");

    x = -0x80000000;

    if (((UINT32*)(&x))[1] != 0xffffffff)
    {
        printf(" - FAIL! high 32 bits incorrect, got %x\n", ((UINT32*)(&x))[1]);
    }

    if (((UINT32*)(&x))[0] != 0x80000000)
    {
        printf(" - FAIL! low 32 bits incorrect\n");
    }
}
*/

void testneg1constantcompilation()
{
    INT64 x = 0;

    printf("testing compilation -1 constant\n");

    x = -1;

    if (((UINT32*)(&x))[1] != 0xffffffff)
    {
        printf(" - FAIL! high 32 bits incorrect, got %x\n", ((UINT32*)(&x))[1]);
    }

    if (((UINT32*)(&x))[0] != 0xffffffff)
    {
        printf(" - FAIL! low 32 bits incorrect\n");
    }
}

void testdg_initpbharrayhead()
{
    Bufferhandle myBHarrayhead;
    printf("test calling dg_initpbharrayhead\n");

    dg_initpbharrayhead(&myBHarrayhead);
}

/*
    myBHarrayhead.argc = argc;
    myBHarrayhead.argv = argv;

    printf("\n");
    printf("testing assembler const char* import linking using dg_testasmimport\n");

    mylength = (UINT32)dg_testasmimport();

    if (mylength != (UINT32)dg_success)
    {
        printf("  const char* import failed\n");
        printf("dg_success = %d\n", (UINT32)dg_success);
        printf(" ooh got %d\n", mylength);
    }
    else
    {
        printf("  const char* import succeeded\n");
    }
*/


void testdg_testasm()
{
    UINT64 x;
    UINT32 xlo, xhi;

    printf("testing dg_testasm\n");

    x = dg_testasm(1);

    if (x != 2)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_testasm(1) fail! - expected 2, got %08x%08x\n", xhi, xlo);
    }

    x = dg_testasm(0x123456789abcdef0);

    if (x != 0x123456789abcdef1)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf(" - FAIL! dg_testasm, expected 0x123456789abcdef1, got %08x%08x\n", xhi, xlo);
    }
}

void testdg_bswap()
{
    UINT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_bswap\n");

    x = 0x9897969565646362;

    x = dg_bswap(x);

    if (x != 0x6263646595969798)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf(" - FAIL! dg_getuint64 success case, expected 0x6263646595969798, got %08x%08x\n", xhi, xlo);
    }
}

void testdg_hibit()
{
    UINT64 x;
    printf("testing dg_hibit\n");

    x = dg_hibit(1);

    if (x != 0)
    {
        printf("  dg_hibit fail! - expected 0, instead got %x\n", (UINT32)x);
    }

    x = dg_hibit(2);

    if (x != 1)
    {
        printf("  dg_hibit fail! - expected 1, instead got %x\n", (UINT32)x);
    }

    x = dg_hibit(3);

    if (x != 1)
    {
        printf("  dg_hibit fail! - expected 1, instead got %x\n", (UINT32)x);
    }

    x = dg_hibit(4);

    if (x != 2)
    {
        printf("  dg_hibit fail! - expected 2, instead got %x\n", (UINT32)x);
    }

    x = dg_hibit((UINT64)-1);

    if (x != 63)
    {
        printf("  dg_hibit fail! - expected 63, instead got %x\n", (UINT32)x);
    }

    x = dg_hibit(0);

    if (x != (UINT64)-1)
    {
        printf("  dg_hibit fail! - expected -1, instead got %x\n", (UINT32)x);
    }
}

void testdg_lobit()
{
    UINT64 x;
    printf("testing dg_lobit\n");

    x = dg_lobit(1);

    if (x != 0)
    {
        printf("  dg_lobit fail! - expected 0, instead got %x\n", (UINT32)x);
    }

    x = dg_lobit(2);

    if (x != 1)
    {
        printf("  dg_lobit fail! - expected 1, instead got %x\n", (UINT32)x);
    }

    x = dg_lobit(3);

    if (x != 0)
    {
        printf("  dg_lobit fail! - expected 0, instead got %x\n", (UINT32)x);
    }

    x = dg_lobit(4);

    if (x != 2)
    {
        printf("  dg_lobit fail! - expected 2, instead got %x\n", (UINT32)x);
    }

    x = dg_lobit((UINT64)-1);

    if (x != 0)
    {
        printf("  dg_lobit fail! - expected 0, instead got %x\n", (UINT32)x);
    }

    x = dg_lobit(0);

    if (x != (UINT64)-1)
    {
        printf("  dg_lobit fail! - expected -1, instead got %x\n", (UINT32)x);
    }
}

void testdg_countbits()
{
    UINT64 x;

    printf("testing dg_countbits\n");

    x = dg_countbits(1);

    if (x != 1)
    {
        printf("  dg_countbits fail! - expected 1, instead got %x\n", (UINT32)x);
    }

    x = dg_countbits(2);

    if (x != 1)
    {
        printf("  dg_countbits fail! - expected 1, instead got %x\n", (UINT32)x);
    }

    x = dg_countbits(3);

    if (x != 2)
    {
        printf("  dg_countbits fail! - expected 2, instead got %x\n", (UINT32)x);
    }

    x = dg_countbits(4);

    if (x != 1)
    {
        printf("  dg_countbits fail! - expected 1, instead got %x\n", (UINT32)x);
    }

    x = dg_countbits((UINT64)-1);

    if (x != 64)
    {
        printf("  dg_countbits fail! - expected 64, instead got %x\n", (UINT32)x);
    }

    x = dg_countbits(0);

    if (x != 0)
    {
        printf("  dg_lobit fail! - expected 0, instead got %x\n", (UINT32)x);
    }
}

void testdg_twoslash()
{
    INT64 n;
    printf("testing dg_twoslash\n");

    n = dg_twoslash(5);

    if (n != 2)
    {
        printf("  dg_twoslash fail! - expected 2, instead got %x\n", (UINT32)n);
    }

    n = dg_twoslash(-8);

    if (n != -4)
    {
        printf("  dg_twoslash fail! - expected -4, instead got %x\n", (INT32)n);
    }
}

void testdg_lshift()
{
    UINT64 x;
    UINT32 xlo, xhi;
    printf("testing dg_lshift\n");

    x = dg_lshift(5, 1);

    if (x != 10)
    {
        printf("  dg_lshift fail! - expected 10, instead got %x\n", (UINT32)x);
    }

    x = dg_lshift(0xffffffffffffffff, 1);

    if (x != 0xfffffffffffffffe)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_lshift fail! - expected 0xfffffffffffffffe, instead got %08x%08x\n", xhi, xlo);
    }

    x = dg_lshift(5, 2);

    if (x != 20)
    {
        printf("  dg_lshift fail! - expected 8, instead got %x\n", (UINT32)x);
    }
}

void testdg_rshift()
{
    UINT64 x;
    UINT32 xhi, xlo;
    printf("testing dg_rshift\n");

    x = dg_rshift(10, 1);

    if (x != 5)
    {
        printf("  dg_rshift fail! - expected 5, instead got %x\n", (UINT32)x);
    }

    x = dg_rshift(0xffffffffffffffff, 1);

    if (x != 0x7fffffffffffffff)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_lshift fail! - expected 0xfffffffffffffffe, instead got %08x%08x\n", xhi, xlo);
    }

    x = dg_rshift(20, 2);

    if (x != 5)
    {
        printf("  dg_lshift fail! - expected 5, instead got %x\n", (UINT32)x);
    }
}

void testdg_udmslashmod()
{
    UINT64 pints[4];
    printf("testing dg_udmslashmod\n");

    pints[0] = 100;
    pints[1] = 0;
    pints[2] = 5;
    pints[3] = 0;

    dg_udmslashmod(pints);

    if (pints[0] != 20)
    {
        printf("  dg_udmslashmod fail! - expected pints[0] = 20, instead got %x\n", (UINT32)pints[0]);
    }

    if (pints[1] != 0)
    {
        printf("  dg_udmslashmod fail! - expected pints[1] = 0, instead got %x\n", (UINT32)pints[1]);
    }

    if (pints[2] != 0)
    {
        printf("  dg_udmslashmod fail! - expected pints[2] = 0, instead got %x\n", (UINT32)pints[2]);
    }

    if (pints[3] != 0)
    {
        printf("  dg_udmslashmod fail! - expected UINT64 after pints to = 0, instead got %x\n", (UINT32)pints[3]);
    }

    pints[0] = 3;
    pints[1] = 0x100;
    pints[2] = 0x10;
    pints[3] = 0;

    dg_udmslashmod(pints);

    if (pints[0] != 0)
    {
        printf("  dg_udmslashmod fail! - expected pints[0] = 0, instead got %x\n", (UINT32)pints[0]);
    }

    if (pints[1] != 0x10)
    {
        printf("  dg_udmslashmod fail! - expected pints[1] = 0x10, instead got %x\n", (UINT32)pints[1]);
    }

    if (pints[2] != 3)
    {
        printf("  dg_udmslashmod fail! - expected pints[2] = 3, instead got %x\n", (UINT32)pints[2]);
    }

    if (pints[3] != 0)
    {
        printf("  dg_udmslashmod fail! - expected UINT64 after pints to = 0, instead got %x\n", (UINT32)pints[3]);
    }

    pints[0] = 39;
    pints[1] = 0x1000000000000000;
    pints[2] = 0x100;
    pints[3] = 0;

    dg_udmslashmod(pints);

    if (pints[0] != 0)
    {
        printf("  dg_udmslashmod fail! - expected pints[0] = 0, instead got %x\n", (UINT32)pints[0]);
    }

    if (pints[1] != 0x10000000000000)
    {
        printf("  dg_udmslashmod fail! - expected pints[1] = 0x10000000000000, instead got %x\n", (UINT32)pints[1]);
    }

    if (pints[2] != 39)
    {
        printf("  dg_udmslashmod fail! - expected pints[2] = 39, instead got %x\n", (UINT32)pints[2]);
    }

    if (pints[3] != 0)
    {
        printf("  dg_udmslashmod fail! - expected UINT64 after pints to = 0, instead got %x\n", (UINT32)pints[3]);
    }
}

void testdg_shrd()
{
    UINT64 pud[2];

    printf("testing dg_shrd\n");

    pud[1] = 0x0F7F6E5D4C3B2A19;
    pud[0] = 0x0817263544536271;

    dg_shrd(pud, 4);

    if (((pud[0]) != 0x9081726354453627) ||
        ((pud[1]) != 0x00F7F6E5D4C3B2A1))
    {
        printf("  dg_shrd(0x0F7F6E5D 4C3B2A19 08172635 44536271, 4) fail! - expected 0x 00F7F6E5 D4C3B2A1 90817263 54453627, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[1] = 0x8F7F6E5D4C3B2A19;
    pud[0] = 0x0817263544536271;

    dg_shrd(pud, 8);

    if ( (pud[0] != 0x1908172635445362) ||
         (pud[1] != 0x008F7F6E5D4C3B2A) )
    {
        printf("  dg_shrd(0x8F7F6E5D 4C3B2A19 08172635 44536271, 8) fail! - expected 0x 008F7F6E 5D4C3B2A 19081726 35445362, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[1] = 0x8F7F6E5D4C3B2A19;
    pud[0] = 0x0817263544536271;

    dg_shrd(pud, 0x3C);

    if ((pud[0] != 0xF7F6E5D4C3B2A190) ||
        (pud[1] != 0x0000000000000008))
    {
        printf("  dg_shrd(0x8F7F6E5D 4C3B2A19 08172635 44536271, 0x3C) fail! - expected 0x 00000000 00000008 F7F6E5D4 C3B2A190, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[1] = 0x8000000000000002;
    pud[0] = 0x0817263544536271;

    dg_shrd(pud, 0x3F);

    if ((pud[0] != 0x0000000000000004) ||
        (pud[1] != 0x0000000000000001))
    {
        printf("  dg_shrd(0x80000000 00000001 08172635 44536271, 0x44) fail! - expected 0x 00000000 00000001 00000000 00000004, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[1] = 0x8F7F6E5D4C3B2A19;
    pud[0] = 0x0817263544536271;

    dg_shrd(pud, 0x40);

    if ((pud[0] != 0x8F7F6E5D4C3B2A19) ||
        (pud[1] != 0x0))
    {
        printf("  dg_shrd(0x8F7F6E5D 4C3B2A19 08172635 44536271, 0x40) fail! - expected 0x 00000000 00000000 8F7F6E5D 4C3B2A19, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[1] = 0x8F7F6E5D4C3B2A19;
    pud[0] = 0x0817263544536271;

    dg_shrd(pud, 0x44);

    if ((pud[0] != 0x08F7F6E5D4C3B2A1) ||
        (pud[1] != 0x0))
    {
        printf("  dg_shrd(0x8F7F6E5D 4C3B2A19 08172635 44536271, 0x44) fail! - expected 0x 00000000 00000000 08F7F6E5 D4C3B2A1, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_ashrd()
{
    INT64 pud[2];

    printf("testing dg_ashrd\n");

    pud[1] = 0x0F7F6E5D4C3B2A19;
    pud[0] = 0x0817263544536271;

    dg_ashrd(pud, 4);

    if ( (pud[0] != 0x9081726354453627) ||
         (pud[1] != 0x00F7F6E5D4C3B2A1))
    {
        printf("  dg_ashrd(0x0F7F6E5D 4C3B2A19 08172635 44536271, 4) fail! - expected 0x 00F7F6E5 D4C3B2A1 90817263 54453627, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }


    pud[1] = 0x8F7F6E5D4C3B2A19;
    pud[0] = 0x0817263544536271;

    dg_ashrd(pud, 4);

    if ( (pud[0] != 0x9081726354453627) ||
         (pud[1] != 0xF8F7F6E5D4C3B2A1) )
    {
        printf("  dg_ashrd(0x8F7F6E5D 4C3B2A19 08172635 44536271, 4) fail! - expected 0x F8F7F6E5 D4C3B2A1 90817263 54453627, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }


    pud[1] = 0x8000000000000002;
    pud[0] = 0x0817263544536271;

    dg_ashrd(pud, 0x3F);

    if ( (pud[0] != 0x0000000000000004) ||
         (pud[1] != 0xFFFFFFFFFFFFFFFF) )
    {
        printf("  dg_ashrd(0x80000000 00000001 08172635 44536271, 0x44) fail! - expected 0x FFFFFFFF FFFFFFFF 00000000 00000004, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }


    pud[1] = 0x8F7F6E5D4C3B2A19;
    pud[0] = 0x0817263544536271;

    dg_ashrd(pud, 0x40);

    if ( (pud[0] != 0x8F7F6E5D4C3B2A19) ||
         (pud[1] != 0xFFFFFFFFFFFFFFFF) )
    {
        printf("  dg_ashrd(0x8F7F6E5D 4C3B2A19 08172635 44536271, 0x40) fail! - expected 0x FFFFFFFF FFFFFFFF 00000000 8F7F6E5D 4C3B2A19, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_shld()
{
    UINT64 pud[2];

    printf("testing dg_shld\n");

    pud[1] = 0x0F7F6E5D4C3B2A19;
    pud[0] = 0x0817263544536271;

    dg_shld(pud, 4);

    if ((pud[0] != 0x8172635445362710) ||
        (pud[1] != 0xF7F6E5D4C3B2A190))
    {
        printf("  dg_shld(0x0F7F6E5D 4C3B2A19 08172635 44536271, 4) fail! - expected 0x F7F6E5D4 C3B2A190 81726354 45362710, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[1] = 0x0F7F6E5D4C3B2A19;
    pud[0] = 0x8000000000000001;

    dg_shld(pud, 0x3f);

    if ((pud[0] != 0x8000000000000000) ||
        (pud[1] != 0xC000000000000000))
    {
        printf("  dg_shld(0x0F7F6E5D 4C3B2A19 80000000 00000001, 0x3f) fail! - expected 0x C0000000 00000000 80000000 00000000, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[1] = 0x0F7F6E5D4C3B2A19;
    pud[0] = 0x0817263544536271;

    dg_shld(pud, 0x40);

    if ((pud[0] != 0x0) ||
        (pud[1] != 0x0817263544536271))
    {
        printf("  dg_shld(0x0F7F6E5D 4C3B2A19 08172635 44536271, 0x40) fail! - expected 0x 08172635 44536271 00000000 00000000, instead got 0x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_tentothex()
{
    Bufferhandle BHarrayhead;

    FLOAT64 df;
    UINT64 x;

    dg_initpbharrayhead(&BHarrayhead);

    printf("testing dg_tentothex\n");

    df = dg_tentothex(0);

    if (df != 1.0)
    {
        printf("  dg_tentothex(0) fail! - expected 10.0, got %e\n", df);
    }

    df = dg_tentothex(1);

    if (df != 10.0)
    {
        printf("  dg_tentothex(1) fail! - expected 10.0, got %e\n", df);
    }

    df = dg_tentothex(2);

    if (df != 100.0)
    {
        printf("  dg_tentothex(2) fail! - expected 100.0, got %e\n", df);
    }

    df = dg_tentothex(3);

    if (df != 1000.0)
    {
        printf("  dg_tentothex(3) fail! - expected 1000.0, got %e\n", df);
    }

    df = dg_tentothex(4);

    if (df != 10000.0)
    {
        printf("  dg_tentothex(4) fail! - expected 10000.0, got %e\n", df);
    }

    df = dg_tentothex(5);

    if (df != 100000.0)
    {
        printf("  dg_tentothex(5) fail! - expected 100000.0, got %e\n", df);
    }

    df = dg_tentothex(6);

    if (df != 1000000.0)
    {
        printf("  dg_tentothex(6) fail! - expected 1000000.0, got %e\n", df);
    }

    df = dg_tentothex(7);

    if (df != 10000000.0)
    {
        printf("  dg_tentothex(7) fail! - expected 10000000.0, got %e\n", df);
    }

    df = dg_tentothex(8);

    if (df != 100000000.0)
    {
        printf("  dg_tentothex(8) fail! - expected 100000000.0, got %e\n", df);
    }

    df = dg_tentothex(9);

    if (df != 1000000000.0)
    {
        printf("  dg_tentothex(9) fail! - expected 1000000000.0, got %e\n", df);
    }

    df = dg_tentothex(10);

    if (df != 10000000000.0)
    {
        printf("  dg_tentothex(10) fail! - expected 1000000000.0, got %e\n", df);
    }

    df = dg_tentothex(10);

    if (df != (FLOAT64)1.0e10)
    {
        printf("  dg_tentothex(10^10) fail! - expected 1e10, got %e\n", df);
    }

    // df = dg_tentothex(308);

    // if (df != (FLOAT64)1.0e308) // 64 bit floating point constants not supported in C
    // {                           // I checked it by eye, it gives the correct result
    //    printf("  dg_tentothex(308) fail! - expected 1e308, got %e\n", df);
    // }

    df = dg_tentothex(309);
    x = (UINT64)df;

    if ((((UINT32*)(&x))[0] != 0) &&
        (((UINT32*)(&x))[1] != 0x7FF00000))
    {
        printf("  dg_tentothex(309) fail! - expected infinity, got %e\n", df);
    }
}


void testdg_f64tan()
{
    FLOAT64 myf64 = 0.0;

    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_f64tan\n");
    
    myf64 = dg_f64tan(0.0);

    if (myf64 != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64tan 0.0 - f64 returned not 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_f64tan(3.14159265359/4.0);

    if ((myf64 > 1.001) || (myf64 < 0.999))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64tan pi/4 - f64 returned not near 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
}


void testdg_putbyte()
{
    unsigned char c;
    const char* perror;

    printf("testing dg_putbyte\n");

    c = 0;

    perror = dg_putbyte(&c, 0x76);

    if (perror != dg_success)
    {
        printf(" - FAIL! dg_putbyte, expected %s got %s\n", dg_success, perror);
    }

    if (c != 0x76)
    {
        printf(" - FAIL! dg_putbyte, expected 0x76 got %x\n", (UINT32)c);
    }

    perror = dg_putbyte(
        (unsigned char*)-0x1001,
        0x11);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_putbyte bad memory at dest case, expected %s\n got %s\n", dg_badmemoryerror, perror);
    }
}


void testdg_putuint16()
{
    UINT16 w;
    const char* perror;

    printf("testing dg_putuint16\n");

    w = 0;

    perror = dg_putuint16(&w, 0x7689);

    if (perror != dg_success)
    {
        printf(" - FAIL! dg_putuint16, expected %s got %s\n", dg_success, perror);
    }

    if (w != 0x7689)
    {
        printf(" - FAIL! dg_putuint16, expected 0x7689 got %x\n", (UINT32)w);
    }



    perror = dg_putuint16(
        (UINT16*)-0x1001,
        0x1122);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_putuint16 bad memory at dest case, expected %s\n got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_putuint32()
{
    UINT32 l;
    const char* perror;

    printf("testing dg_putuint32\n");

    l = 0;

    perror = dg_putuint32(&l, 0x76892301);

    if (perror != dg_success)
    {
        printf(" - FAIL! dg_putuint32, expected %s got %s\n", dg_success, perror);
    }

    if (l != 0x76892301)
    {
        printf(" - FAIL! dg_putuint32, expected 0x76892301 got %x\n", l);
    }



    perror = dg_putuint32(
        (UINT32*)-0x1001,
        0x11223344);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_putuint32 bad memory at dest case, expected %s\n got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_putuint64()
{
    UINT64 x;
    UINT32 xhi, xlo;
    const char* perror;

    printf("testing dg_putuint64\n");

    perror = dg_putuint64(&x, 0x9897969565646362);

    if (perror != dg_success)
    {
        printf(" - FAIL! dg_putuint64 success case, expected %s got %s\n", dg_success, perror);
    }

    if (x != 0x9897969565646362)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf(" - FAIL! dg_putuint64 success case, expected 0x9897969565646362, got %08x%08x\n", xhi, xlo);
    }

    perror = dg_putuint64(
        (UINT64*)-0x1001,
        0x1122334455667788);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_putuint64 bad memory at dest case, expected %s\n got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_getbyte()
{
    unsigned char c, csrc;
    const char* perror;

    printf("testing dg_getbyte\n");

    c = 0, csrc = 0x91;

    perror = dg_getbyte(&csrc, &c);

    if (perror != dg_success)
    {
        printf(" - FAIL! dg_getbyte, expected %s got %s\n", dg_success, perror);
    }

    if (c != 0x91)
    {
        printf(" - FAIL! dg_getbyte, expected 0x91 got %x\n", (UINT32)c);
    }

    perror = dg_getbyte(
        (unsigned char*)-0x1001,
        &c);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_getbyte bad memory at src case, expected %s\n  got %s\n", dg_badmemoryerror, perror);
    }

    perror = dg_getbyte(
        &csrc,
        (unsigned char*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_getbyte bad memory at presult case, expected %s\n  got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_getuint16()
{
    UINT16 w, wsrc;
    const char* perror;

    printf("testing dg_getuint16\n");

    w = 0, wsrc = 0x9123;

    perror = dg_getuint16(&wsrc, &w);

    if (perror != dg_success)
    {
        printf(" - FAIL! dg_getuint16, expected %s got %s\n", dg_success, perror);
    }

    if (w != 0x9123)
    {
        printf(" - FAIL! dg_getuint16, expected 0x9123 got %x\n", (UINT32)w);
    }

    perror = dg_getuint16(
        (UINT16*)-0x1001,
        &w);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_getuint16 bad memory at src case, expected %s\n  got %s\n", dg_badmemoryerror, perror);
    }

    perror = dg_getuint16(
        &wsrc,
        (UINT16*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_getuint16 bad memory at presult case, expected %s\n  got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_getuint32()
{
    UINT32 l, lsrc;
    const char* perror;

    printf("testing dg_getuint32\n");

    l = 0, lsrc = 0x91238420;

    perror = dg_getuint32(&lsrc, &l);

    if (perror != dg_success)
    {
        printf(" - FAIL! dg_getuint32, expected %s got %s\n", dg_success, perror);
    }

    if (l != 0x91238420)
    {
        printf(" - FAIL! dg_getuint32, expected 0x91238420 got %x\n", l);
    }

    perror = dg_getuint32(
        (UINT32*)-0x1001,
        &l);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_getuint32 bad memory at src case, expected %s\n  got %s\n", dg_badmemoryerror, perror);
    }

    perror = dg_getuint32(
        &lsrc,
        (UINT32*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_getuint32 bad memory at presult case, expected %s\n  got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_getuint64()
{
    UINT64 x, xsrc;
    UINT32 xhi, xlo;
    const char* perror;

    printf("testing dg_getuint64\n");

    x = 0, xsrc = 0x9897969565646362;

    perror = dg_getuint64(&xsrc, &x);

    if (perror != dg_success)
    {
        printf(" - FAIL! dg_getuint64 success case, expected %s got %s\n", dg_success, perror);
    }

    if (x != 0x9897969565646362)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf(" - FAIL! dg_getuint64 success case, expected 0x9897969565646362, got %08x%08x\n", xhi, xlo);
    }

    perror = dg_getuint64(
        (UINT64*)-0x1001,
        &x);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_getuint64 bad memory at src case, expected %s\n  got %s\n", dg_badmemoryerror, perror);
    }

    perror = dg_getuint64(
        &xsrc,
        (UINT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_getuint64 bad memory at presult case, expected %s\n  got %s\n", dg_badmemoryerror, perror);
    }
}


void testdg_movebytes()
{
    UINT64 i;
    unsigned char srcbuf[64];
    unsigned char destbuf[64];
    const char* perror;

    printf("testing dg_movebytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 'x';
        srcbuf[i] = (UINT8)i + 0x41;
    }

    perror = dg_movebytes((unsigned char*)srcbuf, destbuf, 9);

    if (perror != dg_success)
    {
        printf("  dg_movebytes failed with error %s\n", perror);
    }

    if (destbuf[0] != 0x41)
    {
        printf("  first character moved incorrect, expected 'A', got %c\n", destbuf[0]);
    }

    if (destbuf[8] != 'I')
    {
        printf("  last character moved incorrect, expected 'I', got %c\n", destbuf[8]);
    }

    if (destbuf[9] != 'x')
    {
        printf("  dg_movebytes changed buffer after last character moved!\n");
    }
    
    perror = dg_movebytes((unsigned char*)-0x1001, destbuf, 9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_movebytes bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    perror = dg_movebytes((unsigned char*)srcbuf, (unsigned char*)-0x1001, 9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_movebytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 'x';
    }

    srcbuf[0] = 'd';
    srcbuf[8] = 'u';
    srcbuf[9] = 'a';

    perror = dg_movebytes((unsigned char*)srcbuf, destbuf, 9);

    if (perror != dg_success)
    {
        printf("  dg_movebytes failed with error %s\n", perror);
    }

    if (destbuf[0] != 'd')
    {
        printf("  first character moved incorrect, expected 'd', got %c\n", destbuf[0]);
    }

    if (destbuf[8] != 'u')
    {
        printf("  last character moved incorrect, expected 'u', got %c\n", destbuf[8]);
    }

    if (destbuf[9] != 'x')
    {
        printf("  dg_movebytes changed buffer after last character moved!\n");
    }
}


void testdg_moveuint64s()
{
    UINT64 i;
    UINT64 srcbuf[64];
    UINT64 destbuf[64];
    const char* perror;
    UINT64 x;
    UINT32 xlo, xhi;

    printf("testing dg_moveuint64s\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 'x';
        srcbuf[i] = (UINT8)i + 0x4142434445464741;
    }

    perror = dg_moveuint64s(srcbuf, destbuf, 9);

    if (perror != dg_success)
    {
        printf("  dg_moveuint64s failed with error %s\n", perror);
    }

    if (destbuf[0] != 0x4142434445464741)
    {
        printf("  first character moved incorrect\n");
    }

    if (destbuf[8] != 0x4142434445464749)
    {
        printf("  last character moved incorrect\n");
    }

    if (destbuf[9] != 'x')
    {
        printf("  dg_moveuint64s changed buffer after last character moved!\n");
    }
    
    perror = dg_moveuint64s((UINT64*)-0x1001, destbuf, 9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_moveuint64s bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    perror = dg_moveuint64s((UINT64*)srcbuf, (UINT64*)-0x1001, 9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_moveuint64s bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 'x';
    }

    srcbuf[0] = 'd';
    srcbuf[8] = 'u';
    srcbuf[9] = 'a';

    perror = dg_moveuint64s(srcbuf, destbuf, 9);

    if (perror != dg_success)
    {
        printf("  dg_moveuint64s failed with error %s\n", perror);
    }

    if (destbuf[0] != 'd')
    {
        printf("  first character moved incorrect, expected 'd'n");
    }

    if (destbuf[8] != 'u')
    {
        printf("  last character moved incorrect, expected 'u'\n");
    }

    if (destbuf[9] != 'x')
    {
        printf("  dg_moveuint64s changed buffer after last character moved!\n");
    }

    // testing reverse case
    for (i = 0; i < 20; i++)
    {
        srcbuf[i] = i + 0x41;
    }

    perror = dg_moveuint64s(srcbuf, srcbuf+1, 9);

    if (perror != dg_success)
    {
        printf("  dg_moveuint64s reverse case failed with error %s\n", perror);
    }

    if (srcbuf[0] != 0x41)
    {
        x = srcbuf[0];
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_moveuint64s reverse case first source character changed, expected 0x41, got %08x%08x\n", xhi, xlo);
    }

    if (srcbuf[1] != 0x41)
    {
        x = srcbuf[1];
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_moveuint64s reverse case first dest character incorrect, expected 0x41, got %08x%08x\n", xhi, xlo);
    }

    if (srcbuf[2] != 0x42)
    {
        x = srcbuf[2];
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_moveuint64s reverse case second dest character incorrect, expected 0x42, got %08x%08x\n", xhi, xlo);
    }

    if (srcbuf[9] != 0x49)
    {
        x = srcbuf[9];
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_moveuint64s reverse case last dest character incorrect, expected 0x49, got %08x%08x\n", xhi, xlo);
    }

    if (srcbuf[10] != 0x4b)
    {
        x = srcbuf[10];
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_moveuint64s reverse case changed buffer after last character moved!, expected 0x4b, got %08x%08x\n", xhi, xlo);
    }
}



void testdg_scanforbyte()
{
    UINT64 i, mylength;
    unsigned char srcbuf[64];
    unsigned char destbuf[64];
    const char* perror;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    printf("testing dg_scanforbyte\n");

    for (i = 0; i < 20; i++)
    {
        srcbuf[i] = (UINT8)i + 0x41;
    }

    mylength = 9;

    perror = dg_scanforbyte((void*)srcbuf, &mylength, (UINT64)'C');

    if (perror != dg_success)
    {
        printf("  dg_scanforbyte failed with error %s\n", perror);
    }
    else
    {
        if (mylength != 2)
        {

            printf("  expected to find character 'C' at position 2, instead dg_scanforbyte returned position %d\n", (UINT32)mylength);
        }
    }

    perror = dg_scanforbyte((void*)-0x1001, &mylength, (UINT64)'C');

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_scanforbyte bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    perror = dg_scanforbyte((void*)srcbuf, (UINT64*)-0x1001, (UINT64)'C');

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_scanforbyte bad memory at plength case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    mylength = 9;
    srcbuf[0] = 'D';
    srcbuf[1] = 'i';
    srcbuf[2] = 'a';
    srcbuf[3] = 'p';


    perror = dg_scanforbyte((void*)srcbuf, &mylength, (UINT32)'a');

    if (perror != dg_success)
    {
        printf("  dg_scanforbyte failed with error %s\n", perror);
    }
    
    if (mylength != 2)
    {
        printf("  expected to find character 'a' at position 2, instead dg_scanforbyte returned position %d\n", (UINT32)mylength);
    }
}

void testdg_scanforbyte2()
{
    UINT64 length;
    UINT64 value;
    void* pbuf = (void*)"abcdefghijklmnopqrstuvwxyz";
    void* badpbuf = (void*)-3;
    const char* flag;
    
    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    printf("testing dg_scanforbyte again\n");
    //::dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_scanforbyte\n");

    // success case
    length = 26;
    value = (UINT64)'c';

    flag = dg_scanforbyte(pbuf, &length, value);

    if (length != 2)
    {
        printf("dg_scanforbyte success case - FAIL! got wrong length, got length = %d\n", (UINT32)length);
        //dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforbyte success case - FAIL! got wrong length\n");
    }

    if (flag != dg_success)
    {
        printf("dg_scanforbyte success case - FAIL! got error %s\n", flag);
        //dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforbyte success case - FAIL! got an error\n");
    }

    printf("testing dg_printzerostring\n");

    dg_printzerostring(&BHarrayhead, (unsigned char*)"  if you see this, dg_printzerostring worked\n");

    printf("tested dg_printzerostring\n");
    // success first case
    length = 26;
    value = (UINT64)'a';

    flag = dg_scanforbyte(pbuf, &length, value);

    if (length != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_scanforbyte success first case - FAIL! got wrong length\n");
    }

    if (flag != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_scanforbyte success first case - FAIL! got an error\n");
    }

    // success last case
    length = 26;
    value = (UINT64)'z';

    flag = dg_scanforbyte(pbuf, &length, value);

    if (length != 25)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_scanforbyte success last case - FAIL! got wrong length\n");
    }

    if (flag != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_scanforbyte success last case - FAIL! got an error\n");
    }

    // not found case
    length = 26;
    value = (UINT64)'8';

    flag = dg_scanforbyte(pbuf, &length, value);

    if (length != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_scanforbyte not found case - FAIL! got wrong length\n");
    }

    if (flag != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_scanforbyte not found case - FAIL! got an error\n");
    }

    // not found match off end case
    length = 25;
    value = (UINT64)'z';

    flag = dg_scanforbyte(pbuf, &length, value);

    if (length != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_scanforbyte not found match off end case - FAIL! got wrong length\n");
    }

    if (flag != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_scanforbyte not found match off end case - FAIL! got an error\n");
    }

    // bad memory case
    //  dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_scanforbyte bad memory case\n");

    length = 26;
    value = (UINT64)'8';

    flag = dg_scanforbyte(badpbuf, &length, value);

    if (length != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_scanforbyte bad memory case - FAIL! got wrong length\n");
    }

    if (flag != dg_badmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_scanforbyte bad memory case - FAIL! got wrong error expected:\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)dg_badmemoryerror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"got:\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)flag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}

void testdg_comparebytes()
{
    unsigned char* pbuf1 = (unsigned char*)"abcdefghijklmnopqrstuvwxyz";
    unsigned char* pbuf2 = (unsigned char*)"def";
    unsigned char* pbuf3 = (unsigned char*)"CHARGGGG";
    unsigned char* pbuf4 = (unsigned char*)"CHARAAAA";
    unsigned char* pbuf5 = (unsigned char*)"CHARZZZZ";
    unsigned char* badpbuf = (unsigned char*)-3;
    const char* perror;
    INT64 compareflag = 5;
    INT64 myflag;
    unsigned char srcbuf[16];
    unsigned char destbuf[16];
    UINT32 xhi, xlo;

    srcbuf[0] = 'c';
    srcbuf[1] = 'a';
    srcbuf[2] = 't';
    srcbuf[3] = 1;

    destbuf[0] = 'c';
    destbuf[1] = 'a';
    destbuf[2] = 't';
    destbuf[3] = 0;

    // Bufferhandle BHarrayhead;

    // dg_initpbharrayhead(&BHarrayhead);

    printf("testing dg_comparebytes\n");

    // success w/ match case
    perror = dg_comparebytes(pbuf1 + 3, 3, pbuf2, 3, &compareflag);

    if (perror != dg_success)
    {
        printf("dg_comparebytes success w/ match case - FAIL! got error %s\n", (unsigned char*)perror);
    }

    if (compareflag != 0)
    {
        printf("dg_comparebytes success w/ match case - got wrong flag\n");
    }

    // success w/ string1 > string2
    perror = dg_comparebytes(pbuf1 + 3, 5, pbuf2, 3, &compareflag);

    if (perror != dg_success)
    {
        printf("dg_comparebytes success w/ string1 > string2 case - FAIL! got error %s\n", (unsigned char*)perror);
    }

    if (compareflag != 1)
    {
        printf("dg_comparebytes success w/ string1 > string2 case - got wrong flag\n");
    }

    // success w/ string1 < longer string2
    perror = dg_comparebytes(pbuf2, 3, pbuf1 + 3, 5, &compareflag);

    if (perror != dg_success)
    {
        printf("dg_comparebytes success w/ string1 < longer string2 - FAIL! got error %s\n", (unsigned char*)perror);
    }

    if (compareflag != -1)
    {
        xlo = compareflag & 0xffffffff;
        xhi = (compareflag >> 32) & 0xffffffff;
        printf("dg_comparebytes success w/ string1 < longer string2 - got wrong flag, expected -1, got %08x%08x\n", xhi, xlo);
    }

    // success w/ string1 < string2
    perror = dg_comparebytes(pbuf1, 5, pbuf2, 3, &compareflag);

    if (perror != dg_success)
    {
        printf("dg_comparebytes success w/ string1 < string2 case - FAIL! got error %s\n", (unsigned char*)perror);
    }

    if (compareflag != -1)
    {
        printf("dg_comparebytes success w/ string1 < string2 case - got wrong flag\n");
    }

    // success making sure only string is compared equals case
    perror = dg_comparebytes(pbuf4, 4, pbuf3, 4, &compareflag);

    if (perror != dg_success)
    {
        printf("dg_comparebytes success making sure only string is compared equals case - FAIL! got error %s\n", (unsigned char*)perror);
    }

    if (compareflag != 0)
    {
        xlo = compareflag & 0xffffffff;
        xhi = (compareflag >> 32) & 0xffffffff;
        printf("dg_comparebytes success making sure only string is compared equals case - got wrong flag, expected 0 for equals, got %08x%08x\n", xhi, xlo);
    }

    // success making sure only string is compared equals case 2
    perror = dg_comparebytes(pbuf5, 4, pbuf3, 4, &compareflag);

    if (perror != dg_success)
    {
        printf("dg_comparebytes success making sure only string is compared equals case 2 - FAIL! got error %sn", perror);
    }

    if (compareflag != 0)
    {
        xlo = compareflag & 0xffffffff;
        xhi = (compareflag >> 32) & 0xffffffff;
        printf("dg_comparebytes success making sure only string is compared equals case 2 - got wrong flag, expected 0 for equals, got %08x%08x\n", xhi, xlo);
    }

    // success making sure only string is compared mostly equals source a longer case
    perror = dg_comparebytes(pbuf3, 5, pbuf4, 4, &compareflag);

    if (perror != dg_success)
    {
        printf("dg_comparebytes success making sure only string is compared mostly equals source a longer case - FAIL! got error %s\n", (unsigned char*)perror);
    }

    if (compareflag != 1)
    {
        xlo = compareflag & 0xffffffff;
        xhi = (compareflag >> 32) & 0xffffffff;
        printf("dg_comparebytes success making sure only string is compared mostly equals source a longer case - got wrong flag, expected 1 for greater than, got %08x%08x\n", xhi, xlo);
    }

    // success making sure only string is compared mostly equals source a longer case 2
    perror = dg_comparebytes(pbuf3, 5, pbuf5, 4, &compareflag);

    if (perror != dg_success)
    {
        printf("dg_comparebytes success making sure only string is compared mostly equals source a longer case 2 - FAIL! got error %s\n", (unsigned char*)perror);
    }

    if (compareflag != 1)
    {
        xlo = compareflag & 0xffffffff;
        xhi = (compareflag >> 32) & 0xffffffff;
        printf("dg_comparebytes success making sure only string is compared mostly equals source a longer case 2 - got wrong flag, expected 1 for greater than, got %08x%08x\n", xhi, xlo);
    }

    // success making sure only string is compared mostly equals source b longer case
    perror = dg_comparebytes(pbuf4, 4, pbuf3, 5, &compareflag);

    if (perror != dg_success)
    {
        printf("dg_comparebytes success making sure only string is compared mostly equals source b longer case - FAIL! got error %s\n", (unsigned char*)perror);
        // dg_printzerostring(&BHarrayhead, (unsigned char*));
        // dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (compareflag != -1)
    {
        xlo = compareflag & 0xffffffff;
        xhi = (compareflag >> 32) & 0xffffffff;
        printf("dg_comparebytes success making sure only string is compared mostly equals source b longer case - got wrong flag, expected -1 for less than, got %08x%08x\n", xhi, xlo);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_comparebytes success making sure only string is compared mostly equals source b longer case - got wrong flag, expected -1 for less than, got ");
        // dg_writestdoutuinttodec(&BHarrayhead, compareflag);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // success making sure only string is compared mostly equals source b longer case 2
    perror = dg_comparebytes(pbuf5, 4, pbuf3, 5, &compareflag);

    if (perror != dg_success)
    {
        printf("dg_comparebytes success making sure only string is compared mostly equals source b longer case 2 - FAIL! got error %s\n", (unsigned char*)perror);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_comparebytes success making sure only string is compared mostly equals source b longer case 2 - FAIL! got error ");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (compareflag != -1)
    {
        xlo = compareflag & 0xffffffff;
        xhi = (compareflag >> 32) & 0xffffffff;
        printf("dg_comparebytes success making sure only string is compared mostly equals source b longer case 2 - got wrong flag, expected -1 for less than, got %08x%08x\n", xhi, xlo);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_comparebytes success making sure only string is compared mostly equals source b longer case 2 - got wrong flag, expected -1 for less than, got ");
        // dg_writestdoutuinttodec(&BHarrayhead, compareflag);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // success making sure only string is compared mostly equals source b longer case 3
    perror = dg_comparebytes(pbuf5, 4, pbuf3, 6, &compareflag);

    if (perror != dg_success)
    {
        printf("dg_comparebytes success making sure only string is compared mostly equals source b longer case 3 - FAIL! got error %s\n", (unsigned char*)perror);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_comparebytes success making sure only string is compared mostly equals source b longer case 3 - FAIL! got error ");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (compareflag != -1)
    {
        xlo = compareflag & 0xffffffff;
        xhi = (compareflag >> 32) & 0xffffffff;
        printf("dg_comparebytes success making sure only string is compared mostly equals source b longer case 3 - got wrong flag, expected -1 for less than, got %08x%08x\n", xhi, xlo);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_comparebytes success making sure only string is compared mostly equals source b longer case 3 - got wrong flag, expected -1 for less than, got ");
        // dg_writestdoutuinttodec(&BHarrayhead, compareflag);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    // bad memory case
    perror = dg_comparebytes(badpbuf, 3, pbuf2, 3, &compareflag);

    if (perror != dg_badmemoryerror)
    {
        printf("dg_comparebytes bad memory case - FAIL! got wrong error, expected: %s, got %s\n", (unsigned char*)dg_badmemoryerror, (unsigned char*)perror);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_comparebytes bad memory case - FAIL! got wrong error, expected:\n");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)dg_badmemoryerror);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"got:\n");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (compareflag != -2)
    {
        printf("dg_comparebytes bad memory case - got wrong flag\n");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"dg_comparebytes bad memory case - got wrong flag\n");
    }

    perror = dg_comparebytes(
        (unsigned char*)srcbuf,
        3,
        (unsigned char*)destbuf,
        3,
        &myflag);

    if (perror != dg_success)
    {
        printf("  dg_comparebytes failed with error %s\n", perror);
    }
    else
    {
        if (myflag != 0)
        {
            printf("  expected flag = 0, instead dg_comparebytes returned flag = %d\n", (INT32)myflag);
        }
    }

    destbuf[2] = 's';

    perror = dg_comparebytes(
        (unsigned char*)srcbuf,
        3,
        (unsigned char*)destbuf,
        3,
        &myflag);

    if (perror != dg_success)
    {
        printf("  dg_comparebytes failed with error %s\n", perror);
    }
    else
    {
        if (myflag != 1)
        {
            printf("  expected flag = 1, instead dg_comparebytes returned flag = %d\n", (INT32)myflag);
        }
    }

    destbuf[2] = 'u';

    perror = dg_comparebytes(
        (unsigned char*)srcbuf,
        3,
        (unsigned char*)destbuf,
        3,
        &myflag);

    if (perror != dg_success)
    {
        printf("  dg_comparebytes failed with error %s\n", perror);
    }
    else
    {
        if (myflag != -1)
        {
            printf("  expected flag = -1, instead dg_comparebytes returned flag = %d\n", (INT32)myflag);
        }
    }

    perror = dg_comparebytes(
        (unsigned char*)-0x1001,
        3,
        (unsigned char*)destbuf,
        3,
        &myflag);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_comparebytes bad memory reading from source case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    perror = dg_comparebytes(
        (unsigned char*)srcbuf,
        3,
        (unsigned char*)-0x1001,
        3,
        &myflag);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_comparebytes bad memory reading from source case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    perror = dg_comparebytes(
        (unsigned char*)srcbuf,
        3,
        (unsigned char*)destbuf,
        3,
        (INT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_comparebytes bad memory reading from source case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_fillwithbyte()
{
    UINT64 i;
    UINT64 mylength;
    const char* perror;
    unsigned char destbuf[64];
    
    printf("testing dg_fillwithbyte\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 'x';
    }

    mylength = 9;

    perror = dg_fillwithbyte((unsigned char*)destbuf, mylength, (UINT64)'z');

    if (perror != dg_success)
    {
        printf("  dg_fillwithbyte failed with error %s\n", perror);
    }
    else
    {
        if (destbuf[0] != 'z')
        {
            printf("  expected to find character 'z' at position 0, instead position 0 had %c\n", destbuf[0]);
        }

        if (destbuf[8] != 'z')
        {
            printf("  expected to find character 'z' at position 8, instead position 8 had %c\n", destbuf[8]);
        }

        if (destbuf[9] != 'x')
        {
            printf("  dg_fillwithbyte changed buffer after last character!\n");
        }
    }

    perror = dg_fillwithbyte((unsigned char*)-0x1001, mylength, (UINT64)'z');

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_fillwithbyte bad memory writing to dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_readallbytes()
{
    UINT64 i;
    UINT64 mylength;
    const char* perror;
    unsigned char destbuf[64];

    printf("testing dg_readallbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 'x';
    }

    mylength = 9;

    perror = dg_readallbytes((unsigned char*)destbuf, mylength); // basically a crash test

    if (perror != dg_success)
    {
        printf("  dg_readallbytes failed with error %s\n", perror);
    }
    else
    {
        if (destbuf[0] != 'x')
        {
            printf("  expected to find character 'x' at position 0, instead position 0 had %c\n", destbuf[0]);
        }

        if (destbuf[8] != 'x')
        {
            printf("  expected to find character 'x' at position 8, instead position 8 had %c\n", destbuf[8]);
        }

        if (destbuf[9] != 'x')
        {
            printf("  dg_readallbytes changed buffer after last character!\n");
        }
    }

    perror = dg_readallbytes((unsigned char*)-0x1001, mylength);

    if (perror != dg_badmemoryerror)
    {
        printf(" - FAIL! dg_readallbytes bad memory writing to dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_search()
{
    unsigned char* caddr1;
    unsigned char* caddr2;
    unsigned char* caddrout;
    const char* perror;
    UINT64 u1, u2;
    UINT64 x;

    printf("testing dg_search\n");
    

    
   //    unsigned char* dg_search (
   //        unsigned char* caddr1, // target string to search
   //        UINT64 u1, // length of target string
   //        unsigned char* caddr2, // string to search for in target string
   //        UINT64 u2,             // length of string to search for
   //        unsigned char** pcaddrout) // pointer to found string or pointer to null

   //     returns dg_success on success
   //     returns dg_badmemoryerror if memory at strings is not part of current process
    
    
    // success case
    caddr1 = (unsigned char*)"abcdefghijklmnopqrstuvwxyz";
    u1 = 26;
    caddr2 = (unsigned char*)"defg";
    u2 = 4;
    caddrout = NULL;

    perror = dg_search(caddr1, u1, caddr2, u2, &caddrout);

    if (perror != dg_success)
    {
        printf("FAIL! dg_search success case - got error %s\n", (UINT8*)perror);
    }

    if (caddrout != caddr1 + 3)
    {
        x = (UINT64)(caddrout - (caddr1 + 3));
        printf("FAIL! dg_search success case - got wrong caddrout, caddrout off by %d\n,", (UINT32)x);
    }

    // success case beginning
    caddr1 = (unsigned char*)"abcdefghijklmnopqrstuvwxyz";
    u1 = 26;
    caddr2 = (unsigned char*)"abcde";
    u2 = 5;
    caddrout = NULL;

    perror = dg_search(caddr1, u1, caddr2, u2, &caddrout);

    if (perror != dg_success)
    {
        printf("FAIL! dg_search success case beginning - got error %s\n", (UINT8*)perror);
    }

    if (caddrout != caddr1)
    {
        x = (UINT64)(caddrout - caddr1);
        printf("FAIL! dg_search success case beginning - got wrong caddrout, caddrout of by %d \n", (UINT32)x);
    }

    // success case end
    caddr1 = (unsigned char*)"abcdefghijklmnopqrstuvwxyz";
    u1 = 26;
    caddr2 = (unsigned char*)"xyz";
    u2 = 3;
    caddrout = NULL;

    perror = dg_search(caddr1, u1, caddr2, u2, &caddrout);

    if (perror != dg_success)
    {
        printf("FAIL! dg_search success case end - got error %s\n", (UINT8*)perror);
    }

    if (caddrout != caddr1 + 23)
    {
        printf("FAIL! dg_search success case end - got wrong caddrout \n");
    }

    // success case length 1
    caddr1 = (unsigned char*)"abcdefghijklmnopqrstuvwxyz";
    u1 = 26;
    caddr2 = (unsigned char*)"w";
    u2 = 1;
    caddrout = NULL;

    perror = dg_search(caddr1, u1, caddr2, u2, &caddrout);

    if (perror != dg_success)
    {
        printf("FAIL! dg_search success case length 1 - got error %s\n", (UINT8*)perror);
    }

    if (caddrout != caddr1 + 22)
    {
        printf("FAIL! dg_search success case length 1 - got wrong caddrout \n");
    }

    // success case w/ near matches
    caddr1 = (unsigned char*)"abcabcabcababcdabcdeabc";
    u1 = 26;
    caddr2 = (unsigned char*)"abcde";
    u2 = 5;
    caddrout = NULL;

    perror = dg_search(caddr1, u1, caddr2, u2, &caddrout);

    if (perror != dg_success)
    {
        printf("FAIL! dg_search success case w/ near matches - got error %s\n", (UINT8*)perror);
    }

    if (caddrout != caddr1 + 15)
    {
        printf("FAIL! dg_search success case w/ near matches - got wrong caddrout \n");
    }

    // not found case
    caddr1 = (unsigned char*)"abcabcabcababcdabcdeabc";
    u1 = 26;
    caddr2 = (unsigned char*)"ef";
    u2 = 2;
    caddrout = NULL;

    perror = dg_search(caddr1, u1, caddr2, u2, &caddrout);

    if (perror != dg_success)
    {
        printf("FAIL! dg_search not found case - got error %s\n", (UINT8*)perror);
    }

    if (caddrout != 0)
    {
        printf("FAIL! dg_search not found case - got wrong caddrout \n");
    }


    // too long case
    caddr1 = (unsigned char*)"abcdef";
    u1 = 5;
    caddr2 = (unsigned char*)"abcdef";
    u2 = 6;
    caddrout = NULL;

    perror = dg_search(caddr1, u1, caddr2, u2, &caddrout);

    if (perror != dg_success)
    {
        printf("FAIL! dg_search too long case - got error %s\n", (UINT8*)perror);
    }

    if (caddrout != 0)
    {
        printf("FAIL! dg_search too long case - got wrong caddrout \n");
    }


    // exact match case
    caddr1 = (unsigned char*)"abcdef";
    u1 = 6;
    caddr2 = (unsigned char*)"abcdef";
    u2 = 6;
    caddrout = NULL;

    perror = dg_search(caddr1, u1, caddr2, u2, &caddrout);

    if (perror != dg_success)
    {
        printf("FAIL! dg_search exact match case - got error %s\n", (UINT8*)perror);
    }

    if (caddrout != caddr1)
    {
        printf("FAIL! dg_search exact match case - got wrong caddrout \n");
    }

    // bad memory case
    caddr1 = (unsigned char*)"abcdef";
    u1 = 6;
    caddr2 = (unsigned char*)-1;
    u2 = 6;
    caddrout = (unsigned char*)-2;

    perror = dg_search(caddr1, u1, caddr2, u2, &caddrout);

    if (perror != dg_badmemoryerror)
    {
        printf("FAIL! dg_search bad memory at string to find case - expected %s\n got %s\n", (UINT8*)dg_badmemoryerror, (UINT8*)perror);
    }

    if (caddrout != (unsigned char*)-2)
    {
        printf("FAIL! dg_search bad memory case case - got wrong caddrout \n");
    }
}

void testdg_getpagesize()
{
    UINT64 x;
    printf("testing dg_getpagesize\n");

    x = dg_getpagesize();  // basically a crash test
}

void testdg_mallocanddg_free()
{
    UINT64 x;
    void* caddr1;
    const char* perror;

    printf("testing dg_malloc and dg_free\n");

    x = dg_getpagesize();
    perror = dg_malloc((void**)&caddr1, 32 * x, dg_success);

    if (perror != dg_success)
    {
        printf("  dg_malloc failed with error %s", perror);
    }

    if (caddr1 == (unsigned char*)badbufferhandle)
    {
        printf("  dg_malloc returned a bad buffer handle\n");
    }
    // else
    // {
    //    xlo = x & 0xffffffff;
    //    xhi = (x >> 32) & 0xffffffff;
    //    printf("  dg_malloc returned a valid buffer handle for a buffer starting at %08x%08x\n", xhi, xlo);
    // }

    // uses pbuf and buffer from dg_malloc test

    if (caddr1 == (unsigned char*)badbufferhandle)
    {
        printf("  unable to test dg_free because dg_malloc failed\n");
    }
    else
    {
        perror = dg_free((void*)caddr1, 32 * x, dg_success);

        if (perror != dg_success)
        {
            printf("  dg_free failed with error %s", perror);
            printf("\n");
        }
        // else
        // {
        //    printf("  dg_free worked\n");
        // }

    }
}

void testdg_realloc()
{
    UINT64 x;
    void* caddr1;
    void* caddr2;
    const char* perror;

    printf("testing dg_realloc\n");

    // printf(" ... doing dg_malloc to allocate a buffer\n");
    x = dg_getpagesize();
    perror = dg_malloc((void**)&caddr1, 32 * x, dg_success);

    if (caddr1 == (unsigned char*)badbufferhandle)
    {
        printf("  unable to test dg_realloc because dg_malloc failed\n");
    }
    else
    {

        caddr2 = caddr1;

        // printf(" ... now doing dg_realloc\n");
        perror = dg_realloc((void**)&caddr1, 32 * x, 64 * x, dg_success);

        if (perror != dg_success)
        {
            // printf("dg_success = %d\n", (UINT32)dg_success);
            // printf("dg_success = %s\n", dg_success);
            // printf("dg_badmemoryerror = %d\n", (UINT32)dg_badmemoryerror);
            // printf("dg_oserror = %d\n", (UINT32)dg_oserror);
            // printf("dg_osexception = %d\n", (UINT32)dg_osexception);
            // printf("perror = %d\n", (UINT32)perror);
            printf("  dg_realloc failed with error %s \n", perror);
        }

        if (caddr1 == (unsigned char*)badbufferhandle)
        {
            printf("  dg_realloc changed the buffer handle to a bad buffer handle\n");
        }

        // if (caddr1 == caddr2)
        // {
        //    printf("  dg_realloc did not change the buffer's base address, not necessarily an error\n");
        // }

        if (caddr1 != (unsigned char*)badbufferhandle)
        {
            perror = dg_free(caddr1, 32 * x, dg_success);
            // printf("  dg_realloc worked\n");
        }

    }
}

void testdg_gethstdin()
{
    Bufferhandle myBHarrayhead;
    UINT64 myfileid;
    const char* perror;

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_gethstdin\n");

    perror = dg_gethstdin(&myBHarrayhead, &myfileid, dg_success);

    if (perror != dg_success)
    {
        printf("  dg_gethstdin failed with error %s\n", perror);
    }
    // else
    // {
    //    printf("  dg_gethstdin succeeded and returned file handle = %d\n", (UINT32)myfileid);
    // }
}


void testdg_gethstdout()
{
    Bufferhandle myBHarrayhead;
    UINT64 myfileid;
    const char* perror;

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_gethstdout\n");

    perror = dg_gethstdout(&myBHarrayhead, &myfileid, dg_success);

    if (perror != dg_success)
    {
        printf("  dg_gethstdout failed with error %s\n", perror);
    }
    // else
    // {
    //    printf("  dg_gethstdout succeeded and returned file handle = %d\n", (UINT32)myfileid);
    // }
}



void testdg_gethstderror()
{
    Bufferhandle myBHarrayhead;
    UINT64 myfileid;
    const char* perror;

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_gethstderror\n");

    perror = dg_gethstderror(&myBHarrayhead, &myfileid, dg_success);

    if (perror != dg_success)
    {
        printf("  dg_gethstderror failed with error %s\n", perror);
    }
    // else
    // {
    //    printf("  dg_gethstderror succeeded and returned file handle = %d\n", (UINT32)myfileid);
    // }
}

void testdg_openfileforwritenewanddg_closefile()
{
    UINT64 myfileid;
    const char* perror;

    printf("testing dg_openfileforwritenew\n");

    perror = dg_openfileforwritenew(
        (const char*)"testosapitestfile.txt",
        &myfileid,
        dg_success);

    if (perror != dg_success)
    {
        printf("  dg_openfileforwritenew failed with error %s", perror);
        printf("\n");
    }
    // else
    // {
    //    x = myfileid;
    //    xlo = x & 0xffffffff;
    //    xhi = (x >> 32) & 0xffffffff;
    //    printf("  dg_openfileforwritenew opened a file with fileid = %08x%08x", xhi, xlo);
    //    printf("  \n");
    // }

    // uses open file and perror from dg_opefileforwritenew test
    printf("testing dg_closefile\n");

    if (perror != dg_success)
    {
        printf("  could not test dg_closefile because dg_openfileforwritenew failed\n");
    }
    else
    {
        perror = dg_closefile(myfileid, dg_success);

        if (perror != dg_success)
        {
            printf("  dg_closefile failed with error %s", perror);
            printf("\n");
        }
        // else
        // {
        //    printf("  dg_closefile succeeded\n");
        // }
    }
}

void testdg_writefile()
{
    UINT64 myfileid;
    const char* perror;
    Bufferhandle myBHarrayhead;

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_writefile\n");

    perror = dg_openfileforwritenew((const char*)"testosapitestfile.txt", &myfileid, dg_success);

    if (perror != dg_success)
    {
        printf("  could not test dg_writefile because dg_openfileforwritenew failed with error %s", perror);
    }
    else
    {
        perror = dg_writefile(&myBHarrayhead, myfileid, (unsigned char*)"diaperglu", 9, dg_success);

        if (perror != dg_success)
        {
            printf("  dg_writefile failed with error %s", perror);
            printf("\n");
        }
        //  else
        // {
        //    printf("  dg_writefile succeeded\n");
        // }

        perror = dg_closefile(myfileid, dg_success);

        if (perror != dg_success)
        {
            printf("  dg_closefile failed with eror %s", perror);
            printf("\n");
        }
    }
}

void testdg_getfilelength()
{
    UINT64 myfileid;
    const char* perror;
    UINT64 myfilelength;
    UINT32 xhi, xlo;

    Bufferhandle myBHarrayhead;

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_getfilelength\n");

    perror = dg_openfileforwritenew((const char*)"testosapitestfile.txt", &myfileid, dg_success);

    if (perror != dg_success)
    {
        printf("  could not test dg_getfilelength because dg_openfileforwritenew failed with error %s", perror);
        printf("\n");
    }
    else
    {
        perror = dg_writefile(&myBHarrayhead, myfileid, (unsigned char*)"diaperglu", 9, dg_success);

        if (perror != dg_success)
        {
            printf("  could not test dg_getfilelength because dg_writefile failed with error %s", perror);
            printf("\n");
        }
        else
        {
            perror = dg_getfilelength(&myBHarrayhead, myfileid, &myfilelength, dg_success);

            if (perror != dg_success)
            {
                printf("  dg_getfilelength failed with error %s", perror);
                printf("\n");
            }
            else
            {
                if (myfilelength != 9)
                {
                    xlo = myfilelength & 0xffffffff;
                    xhi = (myfilelength >> 32) & 0xffffffff;
                    printf("  expected file length of 9, got wrong length of %08x%08x instead\n", xhi, xlo);
                }
                // else
                // {
                //    printf("  dg_getfilelength worked immediately after writing to a new file\n");
                // }
            }
        }

        perror = dg_closefile(myfileid, dg_success);

        if (perror != dg_success)
        {
            printf("  dg_closefile failed with error %s\n", perror);
        }
    }
}

void testdg_openfileforread()
{
    UINT64 myfileid;
    const char* perror;

    Bufferhandle myBHarrayhead;

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_openfileforread\n");

    perror = dg_openfileforwritenew((const char*)"testosapitestfile.txt", &myfileid, dg_success);

    if (perror != dg_success)
    {
        printf("  could not test dg_openfileforread because while trying to make test file, dg_openfileforwritenew failed with error %s\n", perror);
    }
    else
    {
        perror = dg_writefile(&myBHarrayhead, myfileid, (unsigned char*)"diaperglu", 9, dg_success);

        if (perror != dg_success)
        {
            printf("  could not test dg_openfileforread because while trying to make test file, dg_writefile failed with error %s\n", perror);
        }
        else
        {
            perror = dg_closefile(myfileid, dg_success);

            if (perror != dg_success)
            {
                printf("  could not test dg_opefileforread because while trying to make test file, dg_closefile failed with error %s\n", perror);
            }
            else
            {
                perror = dg_openfileforread("testosapitestfile.txt", &myfileid, dg_success);

                if (perror != dg_success)
                {
                    printf("  dg_openfileforread failed with error %s\n", perror);
                }
                else
                {
                    // printf("  dg_openfileforread succeeded\n");

                    perror = dg_closefile(myfileid, dg_success);

                    if (perror != dg_success)
                    {
                        printf("  dg_closefile failed after successful dg_openfileforread\n");
                    }
                }
            }
        }
    }
}

void testdg_readfile()
{
    UINT64 myfileid;
    const char* perror;
    UINT64 i;
    unsigned char myreadbuf[64];
    UINT64 mynumread;

    Bufferhandle myBHarrayhead;

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_readfile\n");

    for (i = 0; i < 20; i++)
    {
        myreadbuf[i] = 'x';
    }

    perror = dg_openfileforwritenew((const char*)"testosapitestfile.txt", &myfileid, dg_success);

    if (perror != dg_success)
    {
        printf("  could not test dg_readfile because while trying to make test file, dg_openfileforwritenew failed with error %s\n", perror);
    }
    else
    {
        perror = dg_writefile(&myBHarrayhead, myfileid, (unsigned char*)"diaperglu", 9, dg_success);

        if (perror != dg_success)
        {
            printf("  could not test dg_readfile because while trying to make test file, dg_writefile failed with error %s\n", perror);
        }
        else
        {
            perror = dg_closefile(myfileid, dg_success);

            if (perror != dg_success)
            {
                printf("  could not test dg_readfile because while trying to make test file, dg_closefile failed with error %s\n", perror);
            }
            else
            {
                perror = dg_openfileforread("testosapitestfile.txt", &myfileid, dg_success);

                if (perror != dg_success)
                {
                    printf("  could not test dg_readfile because while trying to make test file, dg_openfileforread failed with error %s\n", perror);
                }
                else
                {
                    // printf("  dg_openfileforread succeeded\n");

                    perror = dg_readfile(&myBHarrayhead, myfileid, (unsigned char*)&myreadbuf, 9, 0, &mynumread, dg_success);

                    if (perror != dg_success)
                    {
                        printf("  dg_readfile failed with error %s\n", perror);
                    }
                    else
                    {
                        // printf("  dg_readfile reported success\n");
                        // printf("  checking read buffer, if no errors are reported read then succeeded\n");

                        if (mynumread != 9)
                        {
                            printf("  operating system returned %d bytes which is less than the 9 asked for.\n   This should not happen for blocking reads of disk files\n", (UINT32)mynumread);
                        }

                        if (myreadbuf[0] != 'd')
                        {
                            printf("  first character read incorrect. expected 'd', got %c\n", myreadbuf[0]);
                        }

                        if (myreadbuf[1] != 'i')
                        {
                            printf("  second character read incorrect. expected 'i', got %c\n", myreadbuf[1]);
                        }

                        if (myreadbuf[2] != 'a')
                        {
                            printf("  third character read incorrect. expected 'a', got %c\n", myreadbuf[2]);
                        }

                        if (myreadbuf[3] != 'p')
                        {
                            printf("  fourth character read incorrect. expected 'p', got %c\n", myreadbuf[3]);
                        }

                        if (myreadbuf[4] != 'e')
                        {
                            printf("  fifth character read incorrect. expected 'e', got %c\n", myreadbuf[4]);
                        }

                        if (myreadbuf[5] != 'r')
                        {
                            printf("  sixth character read incorrect. expected 'r', got %c\n", myreadbuf[5]);
                        }

                        if (myreadbuf[6] != 'g')
                        {
                            printf("  seventh character read incorrect. expected 'g', got %c\n", myreadbuf[6]);
                        }

                        if (myreadbuf[7] != 'l')
                        {
                            printf("  eigth character read incorrect. expected 'l', got %c\n", myreadbuf[7]);
                        }

                        if (myreadbuf[8] != 'u')
                        {
                            printf("  ninth character read incorrect. expected 'u', got %c\n", myreadbuf[8]);
                        }

                        if (myreadbuf[9] != 'x')
                        {
                            printf("  operating system changed byte after end of buffer. expected 'x', got %c\n", myreadbuf[9]);
                        }
                    }

                    perror = dg_closefile(myfileid, dg_success);

                    if (perror != dg_success)
                    {
                        printf("  dg_closefile failed\n");
                    }
                }
            }
        }
    }
}

void testdg_writestdoutraw()
{
    const char* perror;

    Bufferhandle myBHarrayhead;

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_writestdoutraw\n");

    printf("  sending 'test message\\n' to stdout, instead of doing carriage return, a character like . should be drawn...\n");
    perror = dg_writestdoutraw(&myBHarrayhead, (unsigned char*)"  test message\n", 15);
    printf("\n");

    if (perror != dg_success)
    {
        printf("  dg_writestdoutraw failed with error %s\n", perror);
    }
    // else
    // {
    //    printf("  dg_writestdoutraw reported success\n");
    // }
}


void testdg_getfiletype()
{
    UINT64 myfileid;
    const char* pmyfiletype;
    const char* perror;

    Bufferhandle myBHarrayhead;

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_getfiletype\n");

    perror = dg_gethstdin(&myBHarrayhead, &myfileid, dg_success);

    if (perror != dg_success)
    {
        printf("  could not test dg_getfiletype for stdin because dg_gethstdin failed with error %s\n", perror);
    }
    else
    {
        perror = dg_getfiletype(&myBHarrayhead, myfileid, &pmyfiletype, dg_success);

        if (perror != dg_success)
        {
            printf("  dg_getfiletype for stdin failed with error %s\n", perror);
        }
        // else
        // {
        //    printf("  dg_getfiletype for stdin reported success with file type %s\n", pmyfiletype);
        // }

        perror = dg_openfileforwritenew((const char*)"testosapitestfile.txt", &myfileid, dg_success);

        if (perror != dg_success)
        {
            printf("  could not test dg_getfiletype for a disk file because while trying to make test file, dg_openfileforwritenew failed with error %s\n", perror);
        }
        else
        {
            perror = dg_getfiletype(&myBHarrayhead, myfileid, &pmyfiletype, dg_success);

            if (perror != dg_success)
            {
                printf("  dg_getfiletype for a disk file failed with error %s\n", perror);
            }
            // else
            // {
            //    printf("  dg_getfiletype for a disk file reported success with file type %s\n", pmyfiletype);
            // }

            perror = dg_closefile(myfileid, dg_success);

            if (perror != dg_success)
            {
                printf("  dg_closefile failed\n");
            }
        }
    }
}

void testdg_writefilewithlargemessage()
{
    const char* perror;
    UINT64 myfileid;
    UINT64 i;

    Bufferhandle myBHarrayhead;

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_writefile with large message\n");

    perror = dg_openfileforwritenew((const char*)"testosapitestfile.txt", &myfileid, dg_success);

    if (perror != dg_success)
    {
        printf("  could not test dg_writefile with large message because dg_openfileforwritenew failed with error %s", perror);
        printf("\n");
    }
    else
    {
        for (i = 0; i < 0x10000 / 2; i++)
        {
            megabuf[2 * i] = 'x';
            megabuf[(2 * i) + 1] = (unsigned char)(i & 0xff);
        }

        perror = dg_writefile(&myBHarrayhead, myfileid, (unsigned char*)megabuf, 0x10000, dg_success);

        if (perror != dg_success)
        {
            printf("  dg_writefile with large message failed with error %s", perror);
            printf("\n");
        }
        // else
        // {
        //    printf("  dg_writefile with large message succeeded\n");
        // }

        perror = dg_closefile(myfileid, dg_success);

        if (perror != dg_success)
        {
            printf("  dg_closefile failed with error %s", perror);
            printf("\n");
        }
    }
}

void testdg_readfilewithlargemessage()
{
    const char* perror;
    UINT64 myfileid;
    UINT64 mynumread;

    UINT64 i;

    Bufferhandle myBHarrayhead;

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_readfile and checking large message\n");

    perror = dg_openfileforread("testosapitestfile.txt", &myfileid, dg_success);

    if (perror != dg_success)
    {
        printf("  could not test file written with large message because dg_openfileforread failed with error %s", perror);
        printf("\n");
    }
    else
    {
        perror = dg_readfile(&myBHarrayhead, myfileid, (unsigned char*)megabuf, 0x10000, 0, &mynumread, dg_success);

        if (perror != dg_success)
        {
            printf("  dg_readfile with large message failed with error %s", perror);
            printf("\n");
        }
        // else
        // {
        //    printf("  dg_readfile with large message succeeded\n");
        // }

        perror = dg_closefile(myfileid, dg_success);

        if (perror != dg_success)
        {
            printf("  dg_closefile failed with eror %s", perror);
            printf("\n");
        }

        for (i = 0; i < 0x10000 / 2; i++)
        {
            if (megabuf[2 * i] != 'x')
            {
                printf("  readback of file written with large message not correct\n");
                break;
            }
            if (megabuf[(2 * i) + 1] != (unsigned char)(i & 0xff))
            {
                printf("  readback of file written with large message not correct\n");
                break;
            }
        }
    }
}


void testdg_openfileforwritenewwithexistingfile()
{
    const char* perror;
    UINT64 myfileid;
    UINT64 myfilelength;

    Bufferhandle myBHarrayhead;

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_openfileforwritenew with existing file that existing file gets emptied\n");

    perror = dg_openfileforwritenew((const char*)"testosapitestfile.txt", &myfileid, dg_success);

    if (perror != dg_success)
    {
        printf("  dg_openfileforwritenew failed with error %s", perror);
        printf("\n");
    }
    else
    {
        perror = dg_getfilelength(&myBHarrayhead, myfileid, &myfilelength, dg_success);

        if (perror != dg_success)
        {
            printf("  dg_getfilelength failed with error %s", perror);
            printf("\n");
        }
        else
        {
            if (myfilelength != 0)
            {
                printf("  expected file length of 0, got wrong length of %d instead\n", (UINT32)myfilelength);
            }
            // else
            // {
            //    printf("  dg_getfilelength worked immediately after opening a truncated file\n");
            // }
        }

        perror = dg_closefile(myfileid, dg_success);

        if (perror != dg_success)
        {
            printf("  dg_closefile failed with eror %s", perror);
            printf("\n");
        }
    }
}

void testdg_mstar()
{
    INT64 pnd[2];
    UINT64 xlo;
    INT64 nlo;

    printf("testing dg_mstar\n");

    dg_mstar(5, 3, pnd);

    if ((pnd[0] != 15) ||
        (pnd[1] != 0))
    {
        printf("  dg_mstar fail! - expected 15, instead got %x\n", (UINT32)pnd[0]);
    }

    dg_mstar(0x2000000000000000, 0x3000000000000000, pnd);

    xlo = (pnd[1] >> 32);

    if (xlo != 0x06000000)
    {
        printf("  dg_mstar fail! - expected hi dwoard 0x60000000, instead got %x\n", (UINT32)xlo);
    }

    dg_mstar(-5, 3, pnd);

    if ((pnd[0] != -15) ||
        (pnd[1] != -1))
    {
        nlo = (INT32)(pnd[0] & 0xffffffff);
        printf("  dg_mstar fail! - expected -15, instead got %x\n", (UINT32)nlo);
    }
}

void testdg_umstar()
{
    UINT64 pud[2];
    UINT64 xlo;
    UINT32 nlo, nlo1, nlo2;

    printf("testing dg_umstar\n");

    dg_umstar(5, 3, pud);

    if ((pud[0] != 15) ||
        (pud[1] != 0))
    {
        printf("  dg_umstar fail! - expected 15, instead got %x\n", (UINT32)pud[0]);
    }

    dg_umstar(0x2000000000000000, 0x3000000000000000, pud);

    xlo = (pud[1] >> 32);

    if (xlo != 0x06000000)
    {
        printf("  dg_mstar fail! - expected hi dword 0x60000000, instead got %x\n", (UINT32)xlo);
    }

    dg_umstar(-5, 3, pud); 
    //    0xFFFFFFFFFFFFFFFB
    // + 0x1FFFFFFFFFFFFFFF6
    //   -------------------
    //   0x2FFFFFFFFFFFFFFF1
    if ((pud[0] != 0xFFFFFFFFFFFFFFF1) ||
        (pud[1] != 0x2))
    {
        nlo = (UINT32)(pud[0] & 0xffffffff);
        nlo1 = (UINT32)((pud[0] >> 32) & 0xffffffff);
        nlo2 = (UINT32)(pud[1] & 0xffffffff);
        printf("  dg_umstar fail! - expected 0x10 0xFFFFFFFFFFFFFFAB, instead got %x %x %x\n", nlo2, nlo1, nlo);
    }
}

void testdg_mstarslash()
{
    INT64 px[2];
    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_mstarslash\n");
    
    px[0] = 0;
    px[1] = 0;
    dg_mstarslash(px, 0, 0);

    if (px[0] != 0xFFFFFFFFFFFFFFFF)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 0 0 0 -  return lo not all 1s, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0x7FFFFFFFFFFFFFFF)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 0 0 0 -  return hi not all 0x7fffffffffffffff, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = 1;
    px[1] = 0;
    dg_mstarslash(px, 1, 0);

    if (px[0] != 0xFFFFFFFFFFFFFFFF)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 1 1 0 -  return lo not all 1s, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0x7FFFFFFFFFFFFFFF)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 1 1 0 -  return hi not all 0x7fffffffffffffff, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = 0;
    px[1] = 0;
    dg_mstarslash(px, 1, 1);

    if (px[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 0 1 1 -  return lo 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 0 1 1 -  return hi not 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = 1;
    px[1] = 0;
    dg_mstarslash(px, 0, 1);

    if (px[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 1 0 1 -  return lo not 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 1 0 1 -  return hi not 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = 1;
    px[1] = 0;
    dg_mstarslash(px, 1, 1);

    if (px[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 1 1 1 -  return lo not 1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 1 1 1 -  return hi not 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = -1;
    px[1] = -1;
    dg_mstarslash(px, 1, 1);

    if (px[0] != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash -1 1 1 -  return lo not -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash -1 1 1 -  return hi not -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = 1;
    px[1] = 0;
    dg_mstarslash(px, -1, 1);

    if (px[0] != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 1 -1 1 -  return lo not -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 1 -1 1 -  return hi not -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = 1;
    px[1] = 0;
    dg_mstarslash(px, 1, -1);

    if (px[0] != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 1 1 -1 -  return lo not -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 1 1 -1 -  return hi not -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = -1;
    px[1] = -1;
    dg_mstarslash(px, -1, 1);

    if (px[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash -1 -1 1 -  return lo not 1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash -1 -1 1 -  return hi not 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = 1;
    px[1] = 0;
    dg_mstarslash(px, -1, -1);

    if (px[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 1 -1 -1 -  return lo not 1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 1 -1 -1 -  return hi not 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = -1;
    px[1] = -1;
    dg_mstarslash(px, 1, -1);

    if (px[0] != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash -1 1 -1 -  return lo not 1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash -1 1 -1 -  return hi not 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = -1;
    px[1] = -1;
    dg_mstarslash(px, -1, -1);

    if (px[0] != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash -1 -1 -1 -  return lo not -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash -1 -1 -1 -  return hi not -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = 2;
    px[1] = 0;
    dg_mstarslash(px, 3, 1);

    if (px[0] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 2 3 1 -  return lo not 6, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 2 3 1 -  return hi not 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = 3;
    px[1] = 0;
    dg_mstarslash(px, 4, 2);

    if (px[0] != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 3 4 2 -  return lo not 6, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 3 4 2 -  return hi not 0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = 0;
    px[1] = 0x4000000000000000;
    dg_mstarslash(px, 2, 1);

    if (px[0] != 0xFFFFFFFFFFFFFFFF)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 0x40000000000000000000000000000000 2 1 -  return lo not 0xFFFFFFFFFFFFFFFF, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0x7FFFFFFFFFFFFFFF)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 0x40000000000000000000000000000000 2 1 -  return hi not 0x7FFFFFFFFFFFFFFF, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = 0xFFFFFFFFFFFFFFFE;
    px[1] = 0x7FFFFFFFFFFFFFFF;
    dg_mstarslash(px, 2, 2);

    if (px[0] != 0xFFFFFFFFFFFFFFFE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE 2 2 -  return lo not 0xFFFFFFFFFFFFFFFF, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0x7FFFFFFFFFFFFFFF)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 0x7FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFE 2 2 -  return hi not 0x7FFFFFFFFFFFFFFF, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    px[0] = -2;
    px[1] = -1;
    dg_mstarslash(px, 1, 1);

    if (px[0] != 0xFFFFFFFFFFFFFFFE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash -2 1 1 -  return lo not 0xFFFFFFFFFFFFFFFE, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0xFFFFFFFFFFFFFFFF)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash -2 1 1 -  return hi not 0xFFFFFFFFFFFFFFFF, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    // need to test the carry from add case...
    px[0] = 0xFFFFFFFFFFFFFFFF;
    px[1] = 2;

    dg_mstarslash(px, 0x7FFFFFFFFFFFFFFF, 1);

    if (px[0] != 0xFFFFFFFFFFFFFFFF)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 0x2FFFFFFFFFFFFFFFF 0x7FFFFFFFFFFFFFFF 1 -  return lo not 0xFFFFFFFFFFFFFFFF, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (px[1] != 0x7FFFFFFFFFFFFFFF)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_mstarslash 0x2FFFFFFFFFFFFFFFF 0x7FFFFFFFFFFFFFFF 1 -  return hi not 0x7FFFFFFFFFFFFFFF, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, px[1]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }  
}


void testdg_f64sin()
{
    FLOAT64 myf64 = 0.0;

    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_f64sin\n");
    
    myf64 = dg_f64sin(0.0);

    if (myf64 != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64sin 0.0 - f64 returned not 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_f64sin(3.14159265359/2.0);

    if ((myf64 > 1.001) || (myf64 < 0.999))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64sin pi/2 - f64 returned not near 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
}


void testdg_f64cos()
{
    FLOAT64 myf64 = 0.0;

    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_f64cos\n");
    
    myf64 = dg_f64cos(0.0);

    if (myf64 != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64cos 0.0 - f64 returned not 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_f64cos(3.14159265359/2.0);

    if ((myf64 > 0.001) || (myf64 < -0.001))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64cos pi/2 - f64 returned not near 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
}

void testdg_f64sincos()
{
    FLOAT64 myf64cos = 0.0;
    FLOAT64 myf64sin = 0.0;

    Bufferhandle BHarrayhead;

    BHarrayhead.pisapiecb = (void*)-1;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_f64sincos\n");

    myf64cos = dg_f64sincos(0.0, &myf64sin);

    if (myf64sin != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64sincos 0.0 - f64sin returned not 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64sin)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (myf64cos != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64sincos 0.0 - f64cos returned not 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64cos)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myf64cos = dg_f64sincos(3.14159265359 / 2.0, &myf64sin);

    if ((myf64sin > 1.001) || (myf64sin < 0.999))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64sincos pi/2 - f64sin returned not near 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64sin)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if ((myf64cos > 0.001) || (myf64cos < -0.001))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64sincos pi/2 - f64cos returned not near 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64cos)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}


void testdg_f32tof64()
{
    FLOAT64 myf64 = 0.0;
    FLOAT32 myf32 = 0.0;

    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_f32tof64\n");
    
    myf32 = 8.0;
    myf64 = dg_f32tof64(myf32);

    if (myf64 != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f32tof64 8.0 - f64 returned not 8.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf32 = 32.0;
    myf64 = dg_f32tof64(myf32);

    if (myf64 != 32.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f32tof64 32.0 - f64 returned not 32.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
}


void testdg_f64tof32()
{
    FLOAT64 myf64 = 0.0;
    FLOAT32 myf32 = 0.0;
    UINT64 x;

    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_f64tof32\n");
    
    myf64 = 8.0;
    myf32 = dg_f64tof32(myf64);

    if (myf32 != 8.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f32tof64 8.0 - f64 returned not 8.0, got ");
        x = (UINT64)(*((UINT32*)(&myf32)));
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = 32.0;
    myf32 = dg_f32tof64(myf64);

    if (myf32 != 32.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f32tof64 32.0 - f64 returned not 32.0, got ");
        x = (UINT64)(*((UINT32*)(&myf32)));
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
}


void testdg_f64sqrt()
{
    FLOAT64 myf64 = 0.0;

    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_f64sqrt\n");
    
    myf64 = dg_f64sqrt(1.0);

    if (myf64 != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64sqrt 1.0 - f64 returned not 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_f64sqrt(4.0);

    if (myf64 != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64sqrt 4.0 - f64 returned not 2.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_f64sqrt(9.0);

    if (myf64 != 3.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64sqrt 9.0 - f64 returned not 3.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_f64sqrt(16.0);

    if (myf64 != 4.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64sqrt 16.0 - f64 returned not 4.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
}


void testdg_pchartof64()
{
    FLOAT64 myf64 = 0.0;
    UINT64 myflag;

    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_pchartof64\n");
    
    myf64 = dg_pchartof64(
        (unsigned char*)"",  // pnumber,
        0,                     // length,
        &myflag);

    if (myf64 != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '' - f64 returned not 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '' - flag returned not TRUE, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, myflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"    ",  // pnumber,
        4,                     // length,
        &myflag);

    if (myf64 != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '    ' - f64 returned not 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '    ' - flag returned not TRUE, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, myflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)" 123.45E1",  // pnumber,
        9,                            // length,
        &myflag);

    if (myf64 != 1234.5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 ' 123.45E1' - f64 returned not 1234.5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 ' 123.45E1' - flag returned not FORTH_TRUE, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, myflag);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"0E",  // pnumber,
        2,                     // length,
        &myflag);

    if (myf64 != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '0E' - f64 returned not 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"123.45E1",  // pnumber,
        8,                           // length,
        &myflag);

    if (myf64 != 1234.5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.45E1' - f64 returned not 1234.5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"123.45E2",  // pnumber,
        8,                           // length,
        &myflag);

    if (myf64 != 12345.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.45E2' - f64 returned not 12345.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"123.45E3",  // pnumber,
        8,                           // length,
        &myflag);

    if (myf64 != 123450.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.45E3' - f64 returned not 123450.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"123.45E4",  // pnumber,
        8,                           // length,
        &myflag);

    if (myf64 != 1234500.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.45E4' - f64 returned not 1234500.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"123.45E5",  // pnumber,
        8,                           // length,
        &myflag);

    if (myf64 != 12345000.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.45E5' - f64 returned not 12345000.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"123.45E6",  // pnumber,
        8,                           // length,
        &myflag);

    if (myf64 != 123450000.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.45E6' - f64 returned not 123450000.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"123.45E7",  // pnumber,
        8,                           // length,
        &myflag);

    if (myf64 != 1234500000.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.45E7' - f64 returned not 1234500000.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"123.45E8",  // pnumber,
        8,                           // length,
        &myflag);

    if (myf64 != 12345000000.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.45E8' - f64 returned not 12345000000.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"123.45E9",  // pnumber,
        8,                           // length,
        &myflag);

    if (myf64 != 123450000000.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.45E9' - f64 returned not 123450000000.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"123.45E",  // pnumber,
        7,                           // length,
        &myflag);

    if (myf64 != 123.45)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.45E' - f64 returned not 123.45, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.45E' - flag returned not FORTH_TRUE\n");
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"123.451",  // pnumber,
        7,                           // length,
        &myflag);

    if (myf64 != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.451' - f64 returned not 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '123.451' - flag returned not FORTH_FALSE\n");
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"5629E0",  // pnumber,
        6,                            // length,
        &myflag);

    if ( myf64 != 5629.0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '5629E0' - f64 returned not 5629.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '5629E0' - flag returned not FORTH_TRUE\n");
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"9007199254740991E0",  // pnumber,
        18,                                    // length,
        &myflag);

    if ( myf64 != 9007199254740991.0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '9007199254740991E0' - f64 returned not 9007199254740991.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '9007199254740991E0' - flag returned not FORTH_TRUE\n");
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"9007199254740992E0",  // pnumber,
        18,                                    // length,
        &myflag);

    if ( myf64 != 9007199254740992.0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '9007199254740992E0' - f64 returned not 9007199254740992.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '9007199254740992E0' - flag returned not FORTH_TRUE\n");
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"9007199254740993E0",  // pnumber,
        18,                                    // length,
        &myflag);

    if ( myf64 != 9007199254740993.0  )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '9007199254740993E0' - f64 returned not 9007199254740993.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '9007199254740993E0' - flag returned not FORTH_TRUE\n");
    }
    
    myf64 = dg_pchartof64(
        (unsigned char*)"18014398509481983E0",  // pnumber,
        19,                                     // length,
        &myflag);

    if ( myf64 != 18014398509481983.0 )
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '18014398509481983E0' - f64 returned not 18014398509481983.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartof64 '18014398509481983E0' - flag returned not FORTH_TRUE\n");
    }
}

void testdg_u64times10totheu64tof64()
{
    FLOAT64 myf64 = 0.0;

    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_u64times10totheu64tof64\n");
    
    myf64 = dg_u64times10totheu64tof64(0, 0);

    if (myf64 != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_u64times10totheu64tof64 0 0 - f64 returned not 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_u64times10totheu64tof64(0, 1);

    if (myf64 != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_u64times10totheu64tof64 0 1 - f64 returned not 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_u64times10totheu64tof64(1, 0);

    if (myf64 != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_u64times10totheu64tof64 1 0 - f64 returned not 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_u64times10totheu64tof64(-1, 0);

    if (myf64 != -1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_u64times10totheu64tof64 -1 0 - f64 returned not -1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_u64times10totheu64tof64(-1, 1);

    if (myf64 != -10.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_u64times10totheu64tof64 -1 1 - f64 returned not -10.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_u64times10totheu64tof64(-10, -1);

    if (myf64 != -1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_u64times10totheu64tof64 -10 -1 - f64 returned not -1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_u64times10totheu64tof64(125, 1);

    if (myf64 != 1250.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_u64times10totheu64tof64 125 1 - f64 returned not 1250.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_u64times10totheu64tof64(125, 0);

    if (myf64 != 125.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_u64times10totheu64tof64 125 0 - f64 returned not 125.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_u64times10totheu64tof64(125, -1);

    if (myf64 != 12.5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_u64times10totheu64tof64 125 -1 - f64 returned not 12.5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_u64times10totheu64tof64(125, -2);

    if (myf64 != 1.25)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_u64times10totheu64tof64 125 -2 - f64 returned not 1.25, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
}


void testdg_i64tof64()
{
    FLOAT64 myf64 = 0.0;

    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_i64tof64\n");
    
    myf64 = dg_i64tof64(0);

    if (myf64 != 0.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_i64tof64 0 - f64 returned not 0.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_i64tof64(1);

    if (myf64 != 1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_i64tof64 1 - f64 returned not 1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_i64tof64(2);

    if (myf64 != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_i64tof64 2 - f64 returned not 2.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    myf64 = dg_i64tof64(-1);

    if (myf64 != -1.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_i64tof64 12 - f64 returned not -1.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myf64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
}

void testdg_f64toi64()
{
    INT64 myi64 = 0;

    Bufferhandle BHarrayhead;

    BHarrayhead.pisapiecb = (void*)-1;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_f64toi64\n");

    myi64 = dg_f64toi64(2.0);

    if (myi64 != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64toi64 2.0 - i64 returned not 2, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myi64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myi64 = dg_f64toi64(1.0);

    if (myi64 != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64toi64 1.0 - i64 returned not 1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myi64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myi64 = dg_f64toi64(-2.0);

    if (myi64 != -2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64toi64 -2.0 - f64 returned not -2, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myi64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myi64 = dg_f64toi64(-1.0);

    if (myi64 != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64toi64 -1.0 - f64 returned not -1, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)myi64);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}


void testdg_roundf64tonearesteven()
{
    FLOAT64 myf64;

    Bufferhandle BHarrayhead;

    BHarrayhead.pisapiecb = (void*)-1;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_roundf64tonearesteven\n");

    myf64 = dg_roundf64tonearesteven(2.5);

    if (myf64 != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_roundf64tonearesteven 2.5 - f64 returned not 2.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myf64 = dg_roundf64tonearesteven(3.5);

    if (myf64 != 4.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_roundf64tonearesteven 3.5 - f64 returned not 4.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myf64 = dg_roundf64tonearesteven(3.4);

    if (myf64 != 3.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_roundf64tonearesteven 3.4 - f64 returned not 3.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}


void testdg_roundf64tonegativeinfinity()
{
    FLOAT64 myf64;

    Bufferhandle BHarrayhead;

    BHarrayhead.pisapiecb = (void*)-1;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_roundf64tonegativeinfinity\n");

    myf64 = dg_roundf64tonegativeinfinity(2.5);

    if (myf64 != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_roundf64tonegativeinfinity 2.5 - f64 returned not 2.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myf64 = dg_roundf64tonegativeinfinity(3.5);

    if (myf64 != 3.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_roundf64tonegativeinfinity 3.5 - f64 returned not 3.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myf64 = dg_roundf64tonegativeinfinity(3.6);

    if (myf64 != 3.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_roundf64tonegativeinfinity 3.6 - f64 returned not 3.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myf64 = dg_roundf64tonegativeinfinity(-3.6);

    if (myf64 != -4.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_roundf64tonegativeinfinity -3.6 - f64 returned not -4.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}


void testdg_truncatef64()
{
    FLOAT64 myf64;

    Bufferhandle BHarrayhead;

    BHarrayhead.pisapiecb = (void*)-1;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_truncatef64\n");

    myf64 = dg_truncatef64(2.5);

    if (myf64 != 2.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_truncatef64 2.5 - f64 returned not 2.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myf64 = dg_truncatef64(3.5);

    if (myf64 != 3.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_truncatef64 3.5 - f64 returned not 3.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myf64 = dg_truncatef64(3.6);

    if (myf64 != 3.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_truncatef64 3.6 - f64 returned not 3.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    myf64 = dg_truncatef64(-3.6);

    if (myf64 != -3.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_truncatef64 -3.6 - f64 returned not -3.0, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}


void testdg_f64getfractional()
{
    FLOAT64 myf64;

    Bufferhandle BHarrayhead;

    BHarrayhead.pisapiecb = (void*)-1;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_f64getfractional\n");

    myf64 = dg_f64getfractional(2.5);

    if (myf64 != 0.5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64getfractional 2.5 - f64 returned not 0.5, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myf64 = dg_f64getfractional(3.125);

    if (myf64 != 0.125)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64getfractional 3.125 - f64 returned not 0.125, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}


void testdg_f64logbase2of10()
{
    FLOAT64 myf64;

    Bufferhandle BHarrayhead;

    BHarrayhead.pisapiecb = (void*)-1;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_f64logbase2of10\n");

    myf64 = dg_f64logbase2of10();

    if ((myf64 < 3.321928094) || (myf64 > 3.321928095))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64logbase2of10 - f64 returned not close to 3.321928094887362, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}


void testdg_f64logbase2ofe()
{
    FLOAT64 myf64;

    Bufferhandle BHarrayhead;

    BHarrayhead.pisapiecb = (void*)-1;

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_f64logbase2ofe\n");

    myf64 = dg_f64logbase2ofe();

    if ((myf64 < 1.44269504) || (myf64 > 1.442695041))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_f64logbase2ofe - f64 returned not close to 1.44269504088963, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, *((UINT64*)(&myf64)));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}


void testdg_pchartobase10numberandexponent()
{
    INT64 mynumber = 0;
    INT64 myexponent = 0;

    UINT64 myflag = FORTH_FALSE;

    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_pchartobase10numberandexponent\n");
    
    mynumber = dg_pchartobase10numberandexponent (
        (unsigned char*)"0E",  // pnumber,
        2,                     // length,
        &myexponent,           // pexponent,
        &myflag);              //  pflag)

    if (mynumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '0E' - number returned not 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mynumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myexponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '0E' - exponent returned not 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myexponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '0E' - flag returned not FORTH_TRUE\n"); 
    }
    
    mynumber = dg_pchartobase10numberandexponent (
        (unsigned char*)"E",  // pnumber,
        1,                     // length,
        &myexponent,           // pexponent,
        &myflag);              //  pflag)

    if (mynumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string 'E' - number returned not 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mynumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myexponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string 'E' - exponent returned not 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myexponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string 'E' - flag returned not FORTH_TRUE\n"); 
    }
    
    mynumber = dg_pchartobase10numberandexponent (
        (unsigned char*)".E",  // pnumber,
        2,                     // length,
        &myexponent,           // pexponent,
        &myflag);              //  pflag)

    if (mynumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '.E' - number returned not 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mynumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myexponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '.E' - exponent returned not 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myexponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '.E' - flag returned not FORTH_TRUE\n"); 
    }
    
    
    mynumber = dg_pchartobase10numberandexponent (
        (unsigned char*)"",  // pnumber,
        0,                     // length,
        &myexponent,           // pexponent,
        &myflag);              //  pflag)

    if (mynumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '' - number returned not 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mynumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myexponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '' - exponent returned not 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myexponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_FALSE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '' - flag returned not FORTH_FALSE\n"); 
    }
    
    mynumber = dg_pchartobase10numberandexponent (
        (unsigned char*)"1E",  // pnumber,
        2,                     // length,
        &myexponent,           // pexponent,
        &myflag);              //  pflag)

    if (mynumber != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '1E' - number returned not 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mynumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myexponent != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '1E' - exponent returned not 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myexponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '1E' - flag returned not FORTH_TRUE\n"); 
    }
    
    mynumber = dg_pchartobase10numberandexponent (
        (unsigned char*)"1E5",  // pnumber,
        3,                     // length,
        &myexponent,           // pexponent,
        &myflag);              //  pflag)

    if (mynumber != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '1E5' - number returned not 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mynumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myexponent != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '1E5' - exponent returned not 5, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myexponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '1E5' - flag returned not FORTH_TRUE\n"); 
    }
    
    mynumber = dg_pchartobase10numberandexponent (
        (unsigned char*)"12E5",  // pnumber,
        4,                     // length,
        &myexponent,           // pexponent,
        &myflag);              //  pflag)

    if (mynumber != 12)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '12E5' - number returned not 12, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mynumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myexponent != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '12E5' - exponent returned not 5, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myexponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '12E5' - flag returned not FORTH_TRUE\n"); 
    }
    
    mynumber = dg_pchartobase10numberandexponent (
        (unsigned char*)"12E45",  // pnumber,
        5,                     // length,
        &myexponent,           // pexponent,
        &myflag);              //  pflag)

    if (mynumber != 12)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '12E45' - number returned not 12, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mynumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myexponent != 45)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '12E45' - exponent returned not 45, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myexponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '12E45' - flag returned not FORTH_TRUE\n"); 
    }
    
    mynumber = dg_pchartobase10numberandexponent (
        (unsigned char*)"1.5E",  // pnumber,
        4,                     // length,
        &myexponent,           // pexponent,
        &myflag);              //  pflag)

    if (mynumber != 15)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '1.5E' - number returned not 15, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mynumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myexponent != -1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '1.5E' - exponent returned not -1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myexponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '1.5E' - flag returned not FORTH_TRUE\n"); 
    }
    
    mynumber = dg_pchartobase10numberandexponent (
        (unsigned char*)"1.56E78",  // pnumber,
        7,                     // length,
        &myexponent,           // pexponent,
        &myflag);              //  pflag)

    if (mynumber != 156)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '1.56E78' - number returned not 156, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mynumber);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myexponent != 76)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '1.56E78' - exponent returned not 76, got ");
        dg_writestdoutuinttodec(&BHarrayhead, myexponent);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n"); 
    }
    
    if (myflag != FORTH_TRUE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartobase10numberandexponent base 10 string '1.56E78' - flag returned not FORTH_TRUE\n"); 
    }
}


void testdg_pchartonumberskipperiod()
{
    INT64 x = 0;
    INT64 exponent;
    UINT64 index;
    UINT64 digitsafterperiod;

    UINT64 flag = FORTH_FALSE;

    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_pchartonumberskipperiod\n");
    
    
    x = dg_pchartonumberskipperiod (
        (unsigned char*)"", // pnumber
        0,                   // length,
        10,                  // base
        &index,
        &digitsafterperiod);

    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '' - number returned not 0\n"); 
    }
    
    if (index != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '' - index returned not 1\n"); 
    }
    
    if (digitsafterperiod != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '' - digitsafterperiod returned not 0\n"); 
    }
    
    

    x = dg_pchartonumberskipperiod (
        (unsigned char*)"0", // pnumber
        1,                   // length,
        10,                  // base
        &index,
        &digitsafterperiod);

    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '0' - number returned not 0\n"); 
    }
    
    if (index != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '0' - index returned not 1\n"); 
    }
    
    if (digitsafterperiod != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '0' - digitsafterperiod returned not 0\n"); 
    }
    
    
    x = dg_pchartonumberskipperiod (
        (unsigned char*)"q", // pnumber
        1,                   // length,
        10,                  // base
        &index,
        &digitsafterperiod);

    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string 'q' - number returned not 0\n"); 
    }
    
    if (index != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string 'q' - index returned not 1\n"); 
    }
    
    if (digitsafterperiod != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string 'q' - digitsafterperiod returned not 0\n"); 
    }
    
    x = dg_pchartonumberskipperiod (
        (unsigned char*)"0E", // pnumber
        2,                   // length,
        10,                  // base
        &index,
        &digitsafterperiod);

    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '0E' - number returned not 0\n"); 
    }
    
    if (index != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '0E' - index returned not 1\n"); 
    }
    
    if (digitsafterperiod != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '0E' - digitsafterperiod returned not 0\n"); 
    }
    
    
    x = dg_pchartonumberskipperiod (
        (unsigned char*)"123", // pnumber
        3,                     // length,
        10,                    // base
        &index,
        &digitsafterperiod);

    if (x != 123)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '123' - number returned not 0\n"); 
    }
    
    if (index != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '123' - index returned not 1\n"); 
    }
    
    if (digitsafterperiod != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '123' - digitsafterperiod returned not 0\n"); 
    }
    
    
    x = dg_pchartonumberskipperiod (
        (unsigned char*)"123.456", // pnumber
        7,                     // length,
        10,                    // base
        &index,
        &digitsafterperiod);

    if (x != 123456)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '123.456' - number returned not 0\n"); 
    }
    
    if (index != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '123.456' - index returned not 1\n"); 
    }
    
    if (digitsafterperiod != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '123.456' - digitsafterperiod returned not 3\n"); 
    }
    
    
    x = dg_pchartonumberskipperiod (
        (unsigned char*)"123.4567", // pnumber
        8,                     // length,
        10,                    // base
        &index,
        &digitsafterperiod);

    if (x != 1234567)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '123.4567' - number returned not 0\n"); 
    }
    
    if (index != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '123.4567' - index returned not 1\n"); 
    }
    
    if (digitsafterperiod != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '123.4567' - digitsafterperiod returned not 3\n"); 
    }
    
    
    x = dg_pchartonumberskipperiod (
        (unsigned char*)"123.4567.8", // pnumber
        10,                     // length,
        10,                    // base
        &index,
        &digitsafterperiod);

    if (x != 1234567)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '123.4567.8' - number returned not 0\n"); 
    }
    
    if (index != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '123.4567.8' - index returned not 1\n"); 
    }
    
    if (digitsafterperiod != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '123.4567.8' - digitsafterperiod returned not 3\n"); 
    }
    
    
    x = dg_pchartonumberskipperiod (
        (unsigned char*)"-123.4567", // pnumber
        9,                     // length,
        10,                    // base
        &index,
        &digitsafterperiod);

    if (x != -1234567)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '-123.4567' - number returned not -1234567, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (index != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '-123.4567' - index returned not 1\n"); 
    }
    
    if (digitsafterperiod != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '-123.4567' - digitsafterperiod returned not 3\n"); 
    }
    
    
    x = dg_pchartonumberskipperiod (
        (unsigned char*)"+123.4567", // pnumber
        9,                     // length,
        10,                    // base
        &index,
        &digitsafterperiod);

    if (x != 1234567)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '+123.4567' - number returned not 1234567, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (index != 9)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '+123.4567' - index returned not 9\n"); 
    }
    
    if (digitsafterperiod != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '+123.4567' - digitsafterperiod returned not 3\n"); 
    }
    
    x = dg_pchartonumberskipperiod (
        (unsigned char*)"9223372036854775807", // pnumber
        19,                     // length,
        10,                    // base
        &index,
        &digitsafterperiod);

    if (x != 9223372036854775807)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '9223372036854775807' - number returned not 9223372036854775807, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (index != 19)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '9223372036854775807' - index returned not 19\n"); 
    }
    
    if (digitsafterperiod != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '9223372036854775807' - digitsafterperiod returned not 0\n"); 
    }
    
    x = dg_pchartonumberskipperiod (
        (unsigned char*)"9223372036854775808", // pnumber
        19,                     // length,
        10,                    // base
        &index,
        &digitsafterperiod);

    if (x != 9223372036854775807)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '9223372036854775808' - number returned not 9223372036854775807, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (index != 19)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '9223372036854775808' - index returned not 19\n"); 
    }
    
    if (digitsafterperiod != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '9223372036854775808' - digitsafterperiod returned not 0\n"); 
    }
    
    x = dg_pchartonumberskipperiod (
        (unsigned char*)"9223372036854775817", // pnumber
        19,                     // length,
        10,                    // base
        &index,
        &digitsafterperiod);

    if (x != 9223372036854775807)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '9223372036854775817' - number returned not 9223372036854775807, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (index != 19)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '9223372036854775817' - index returned not 19\n"); 
    }
    
    if (digitsafterperiod != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumberskipperiod base 10 string '9223372036854775817' - digitsafterperiod returned not 0\n"); 
    }

}



/*
void testdg_runfileandwait()
{
    Bufferhandle BHarrayhead;
    
    const char* perror;
    char* argv[8];
    char* envp[8];
    
    argv[0] = (char*)"echo\0";
    argv[1] = (char*)"  ... yay echo printed this message\n\0";
    argv[2] = (char*)NULL;
    
    envp[0] = (char*)NULL;
    
    dg_initpbharrayhead(&BHarrayhead);
    
    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_runfileandwait\n");
    dg_printzerostring(&BHarrayhead, (unsigned char*)"... you should see a message from running echo -> ");
    
    perror = dg_runfileandwait(
        // &BHarrayhead,
        (const char*)"/bin/echo",
        argv,
        envp,
        dg_success);
    
    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_runfileandwait success running echo case - got an error , got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    perror = dg_runfileandwait(
        // &BHarrayhead,
        (const char*)"/badpath/badfilename",
        argv,
        envp,
        dg_success);
    
    if (perror != dg_couldnotrunfileerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_runfileandwait bad path and filename case - got wrong error or success. Expected program exited with error error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
}
*/
/*
void testdg_pushhctwotobuffer()
{
    Bufferhandle BHarrayhead;

    UINT64 codebufferid;
    unsigned char* mypcodebuffer;
    UINT64* mypcodebufferlength;
    
    UINT64 x;
    UINT128 udy;

    const char* pError;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushhctwotobuffer\n");

    dg_initbuffers(&BHarrayhead);

    // need to create a code buffer
    codebufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        1000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushhctwotobuffer success case - got an error making the code buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (0 == codebufferid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushhctwotobuffer success case - got an error making the code buffer, for some reason the codebufferid is 0, which is reserved for the error stack.\n");
        return;
    }

    udy = dg_touleb128(0); // makes a 1 byte hcstring in a UINT128
    
    dg_pushhctwotobuffer (
        &BHarrayhead,
        codebufferid,
        udy);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushhctwotobuffer success 1 byte case - got an error doing dg_pushhctwotobuffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    mypcodebuffer = dg_getpbuffer (
        &BHarrayhead,
        codebufferid,
        &mypcodebufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushhctwotobuffer success 1 byte case - got an error getting pointer to code buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = *mypcodebufferlength;
    if (x != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushhctwotobuffer success 1 byte case - got wrong answer. Expected length of 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = mypcodebuffer[0];
    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushhctwotobuffer success 1 byte case - got wrong answer. Expected first byte of string to be 0x00, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearbuffer(
        &BHarrayhead,
        codebufferid);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushhctwotobuffer success 2 bytes case - got an error clearing the buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    udy = dg_touleb128(0x80); // makes a 2 byte hcstring in a UINT128
    
    dg_pushhctwotobuffer (
        &BHarrayhead,
        codebufferid,
        udy);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushhctwotobuffer success 2 bytes case - got an error doing dg_pushhctwotobuffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    mypcodebuffer = dg_getpbuffer (
        &BHarrayhead,
        codebufferid,
        &mypcodebufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushhctwotobuffer success 2 bytes case - got an error getting pointer to code buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = *mypcodebufferlength;
    if (x != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushhctwotobuffer success 2 bytes case - got wrong answer. Expected length of 1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = mypcodebuffer[0];
    if (x != 0x80)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushhctwotobuffer success 2 bytes case - got wrong answer. Expected first byte of string to be 0x80, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    x = mypcodebuffer[1];
    if (x != 0x01)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushhctwotobuffer success 2 bytes case - got wrong answer. Expected second byte of string to be 0x01, got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_clearerrors(&BHarrayhead);

    dg_freeallbuffers(&BHarrayhead);
}
*/

void testdg_getuleb128size()
{
    Bufferhandle BHarrayhead;
    UINT64 x,y;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getuleb128size\n");

    x = dg_getuleb128size(0);
    
    if (1 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuleb128size(0) case - got wrong answer.\n");
        return;
    }

    x = dg_getuleb128size(1);
    
    if (1 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuleb128size(1) case - got wrong answer.\n");
        return;
    }
    
    x = dg_getuleb128size(127);
    
    if (1 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuleb128size(127) case - got wrong answer.\n");
        return;
    }
    
    x = dg_getuleb128size(128);
    
    if (2 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuleb128size(128) case - got wrong answer.\n");
        return;
    }
    
    y = (1 << 14) - 1;
    x = dg_getuleb128size(y);
    
    if (2 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuleb128size((2^14) - 1) case - got wrong answer. Expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"(2^14) - 1 = ");
        dg_writestdoutuinttodec(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" or 0x");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    y++;
    x = dg_getuleb128size(y);
    
    if (3 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuleb128size(2^14) case - got wrong answer.\n");
        return;
    }
    
    y = (1 << 21) - 1;
    x = dg_getuleb128size(y);
    
    if (3 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuleb128size((2^21) - 1) case - got wrong answer.\n");
        return;
    }
    
    y++;
    x = dg_getuleb128size(y);
    
    if (4 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuleb128size(2^21) case - got wrong answer.\n");
        return;
    }
    
    y = (1 << 28) - 1;
    x = dg_getuleb128size(y);
    
    if (4 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuleb128size((2^28) - 1) case - got wrong answer.\n");
        return;
    }
    
    y++;
    x = dg_getuleb128size(y);
    
    if (5 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getuleb128size(2^28) case - got wrong answer.\n");
        return;
    }
}


void testdg_getlengthwithuleb128length()
{
    Bufferhandle BHarrayhead;
    UINT64 x,y;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getlengthwithuleb128length\n");

    x = dg_getlengthwithuleb128length(0);
    
    if (1 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthwithuleb128length(0) case - got wrong answer.\n");
        return;
    }

    x = dg_getlengthwithuleb128length(1);
    
    if (2 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthwithuleb128length(1) case - got wrong answer.\n");
        return;
    }
    
    x = dg_getlengthwithuleb128length(126);
    
    if (127 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthwithuleb128length(126) case - got wrong answer.\n");
        return;
    }
    
    x = dg_getlengthwithuleb128length(127);
    
    if (129 != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthwithuleb128length(127) case - got wrong answer.\n");
        return;
    }
    
    y = (1 << 14) - 3;
    x = dg_getlengthwithuleb128length(y);
    
    if ((y+2) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthwithuleb128length((2^14) - 3) case - got wrong answer. Expected (2^14)-1, got ");
        dg_writestdoutuinttodec(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"(2^14) - 1 = ");
        dg_writestdoutuinttodec(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" or 0x");
        dg_writestdoutuint64tohex(&BHarrayhead, y);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        return;
    }
    
    y++;
    x = dg_getlengthwithuleb128length(y);
    
    if ((y+3) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthwithuleb128length((2^14) - 2) case - got wrong answer.\n");
        return;
    }
    
    y = (1 << 21) - 4;
    x = dg_getlengthwithuleb128length(y);
    
    if ((y+3) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthwithuleb128length((2^21) - 4) case - got wrong answer.\n");
        return;
    }
    
    y++;
    x = dg_getlengthwithuleb128length(y);
    
    if ((y+4) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthwithuleb128length((2^21) - 3) case - got wrong answer.\n");
        return;
    }
    
    y = (1 << 28) - 5;
    x = dg_getlengthwithuleb128length(y);
    
    if ((y+4) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthwithuleb128length((2^28) - 5) case - got wrong answer.\n");
        return;
    }
    
    y++;
    x = dg_getlengthwithuleb128length(y);
    
    if ((y+5) != x)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getlengthwithuleb128length((2^28)-4) case - got wrong answer.\n");
        return;
    }
}

void testdg_touleb128()
{
    UINT64 pud[2];

    printf("testing dg_touleb128\n");

    dg_touleb128(0, pud);

    if ((pud[1] != 0x0100000000000000) ||
        (pud[0] != 0x0000000000000000))
    {
        printf("  dg_touleb128(0) fail! - expected 0x010000000000000000000000000000000, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(1, pud);

    if ((pud[1] != 0x0100000000000000) ||
        (pud[0] != 0x0000000000000001))
    {
        printf("  dg_touleb128(1) fail! - expected 0x01000000000000000000000000000001, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x7f, pud);

    if ((pud[1] != 0x0100000000000000) ||
        (pud[0] != 0x000000000000007F))
    {
        printf("  dg_touleb128(0x7F) fail! - expected 0x0100000000000000000000000000007F, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x80, pud);

    if ((pud[1] != 0x0200000000000000) ||
        (pud[0] != 0x0000000000000180))
    {
        printf("  dg_touleb128(0x80) fail! - expected 0x02000000000000000000000000000180, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x3FFF, pud);

    if ((pud[1] != 0x0200000000000000) ||
        (pud[0] != 0x0000000000007FFF))
    {
        printf("  dg_touleb128(0x3FFF) fail! - expected 0x02000000000000000000000000007FFF, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x4000, pud);

    if ((pud[1] != 0x0300000000000000) ||
        (pud[0] != 0x0000000000018080))
    {
        printf("  dg_touleb128(0x4000) fail! - expected 0x03000000000000000000000000018080, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x1FFFFF, pud);

    if ((pud[1] != 0x0300000000000000) ||
        (pud[0] != 0x00000000007FFFFF))
    {
        printf("  dg_touleb128(0x1FFFFF) fail! - expected 0x030000000000000000000000007FFFFF, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x200000, pud);

    if ((pud[1] != 0x0400000000000000) ||
        (pud[0] != 0x0000000001808080))
    {
        printf("  dg_touleb128(0x200000) fail! - expected 0x04000000000000000000000001808080, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0xFFFFFFF, pud);

    if ((pud[1] != 0x0400000000000000) ||
        (pud[0] != 0x000000007FFFFFFF))
    {
        printf("  dg_touleb128(0xFFFFFFF) fail! - expected 0x0400000000000000000000007FFFFFFF, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x10000000, pud);

    if ((pud[1] != 0x0500000000000000) ||
        (pud[0] != 0x0000000180808080))
    {
        printf("  dg_touleb128(0x10000000) fail! - expected 0x05000000000000000000000180808080, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x7FFFFFFFF, pud);

    if ((pud[1] != 0x0500000000000000) ||
        (pud[0] != 0x0000007FFFFFFFFF))
    {
        printf("  dg_touleb128(0x7FFFFFFFF) fail! - expected 0x05000000000000000000007FFFFFFFFF, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x800000000, pud);

    if ((pud[1] != 0x0600000000000000) ||
        (pud[0] != 0x0000018080808080))
    {
        printf("  dg_touleb128(0x800000000) fail! - expected 0x06000000000000000000018080808080, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x3FFFFFFFFFF, pud);

    if ((pud[1] != 0x0600000000000000) ||
        (pud[0] != 0x00007FFFFFFFFFFF))
    {
        printf("  dg_touleb128(0x3FFFFFFFFFF) fail! - expected 0x060000000000000000007FFFFFFFFFFF, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x40000000000, pud);

    if ((pud[1] != 0x0700000000000000) ||
        (pud[0] != 0x0001808080808080))
    {
        printf("  dg_touleb128(0x40000000000) fail! - expected 0x07000000000000000001808080808080, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x1FFFFFFFFFFFF, pud);

    if ((pud[1] != 0x0700000000000000) ||
        (pud[0] != 0x007FFFFFFFFFFFFF))
    {
        printf("  dg_touleb128(0x1FFFFFFFFFFFF) fail! - expected 0x0700000000000000007FFFFFFFFFFFFF, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x2000000000000, pud);

    if ((pud[1] != 0x0800000000000000) ||
        (pud[0] != 0x0180808080808080))
    {
        printf("  dg_touleb128(0x2000000000000) fail! - expected 0x08000000000000000180808080808080, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0xFFFFFFFFFFFFFF, pud);

    if ((pud[1] != 0x0800000000000000) ||
        (pud[0] != 0x7FFFFFFFFFFFFFFF))
    {
        printf("  dg_touleb128(0xFFFFFFFFFFFFFF) fail! - expected 0x07000000000000007FFFFFFFFFFFFFFF, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x0100000000000000, pud);

    if ((pud[1] != 0x0900000000000001) ||
        (pud[0] != 0x8080808080808080))
    {
        printf("  dg_touleb128(0x0100000000000000) fail! - expected 0x09000000000000018080808080808080, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x7FFFFFFFFFFFFFFF, pud);

    if ((pud[1] != 0x090000000000007F) ||
        (pud[0] != 0xFFFFFFFFFFFFFFFF))
    {
        printf("  dg_touleb128(0x7FFFFFFFFFFFFFFF) fail! - expected 0x090000000000007FFFFFFFFFFFFFFFFF, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0x8000000000000000, pud);

    if ((pud[1] != 0x0A00000000000180) ||
        (pud[0] != 0x8080808080808080))
    {
        printf("  dg_touleb128(0x8000000000000000) fail! - expected 0x0A0000000000018080808080808080, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    dg_touleb128(0xFFFFFFFFFFFFFFFF, pud);

    if ((pud[1] != 0x0A000000000001FF) ||
        (pud[0] != 0xFFFFFFFFFFFFFFFF))
    {
        printf("  dg_touleb128(0xFFFFFFFFFFFFFFFF) fail! - expected 0x0A000000000001FFFFFFFFFFFFFFFFF, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_getlengthwithuleb128length2()
{
    UINT64 x;
    printf("testing dg_getlengthwithuleb128length again\n");

    x = dg_getlengthwithuleb128length(0);

    if (x != 1)
    {
        printf("  dg_getlengthwithuleb128length(0) fail! - expected 1, instead got 0x %08x %08x\n",
            ((UINT32*)(&x))[1],
            ((UINT32*)(&x))[0]);
    }

    x = dg_getlengthwithuleb128length(126);

    if (x != 127)
    {
        printf("  dg_getlengthwithuleb128length(126) fail! - expected 127, instead got 0x %08x %08x\n",
            ((UINT32*)(&x))[1],
            ((UINT32*)(&x))[0]);
    }

    x = dg_getlengthwithuleb128length(127);

    if (x != 129)
    {
        printf("  dg_getlengthwithuleb128length(127) fail! - expected 129, instead got 0x %08x %08x\n",
            ((UINT32*)(&x))[1],
            ((UINT32*)(&x))[0]);
    }

    x = dg_getlengthwithuleb128length((1 << 15) - 3);

    if (x != (1 << 15))
    {
        printf("  dg_getlengthwithuleb128length((1 << 15) - 3) fail! - expected (1 << 15), instead got 0x %08x %08x\n",
            ((UINT32*)(&x))[1],
            ((UINT32*)(&x))[0]);
    }

    x = dg_getlengthwithuleb128length((1 << 15) - 2);

    if (x != ((1 << 15) + 1))
    {
        printf("  dg_getlengthwithuleb128length((1 << 15) - 2) fail! - expected ((1 << 15) + 1), instead got 0x %08x %08x\n",
            ((UINT32*)(&x))[1],
            ((UINT32*)(&x))[0]);
    }

    x = dg_getlengthwithuleb128length((1 << 15) - 1);

    if (x != ((1 << 15) + 2))
    {
        printf("  dg_getlengthwithuleb128length((1 << 15) - 1) fail! - expected ((1 << 15) +2), instead got 0x %08x %08x\n",
            ((UINT32*)(&x))[1],
            ((UINT32*)(&x))[0]);
    }

    x = dg_getlengthwithuleb128length(1 << 15);

    if (x != ((1 << 15) + 3))
    {
        printf("  dg_getlengthwithuleb128length(1 << 15) fail! - expected ((1 << 15) + 3), instead got 0x %08x %08x\n",
            ((UINT32*)(&x))[1],
            ((UINT32*)(&x))[0]);
    }
}

void testdg_dabs()
{
    INT64 pud[2];

    printf("testing dg_dabs\n");

    pud[0] = 0;
    pud[1] = 0;

    dg_dabs(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 0) )
    {
        printf("  dg_dabs 0 fail! - expected 0, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = -2;
    pud[1] = -1;

    dg_dabs(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 2) )
    {
        printf("  dg_dabs -2 fail! - expected:\n  2, instead got:\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 5;
    pud[1] = 7;

    dg_dabs(pud);

    if ((pud[1] != 7) ||
        (pud[0] != 5) )
    {
        printf("  dg_dabs 5 7 fail! - expected:\n  0x000000000000000070000000000000005,\n instead got\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 2;
    pud[1] = -1;

    dg_dabs(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 0xFFFFFFFFFFFFFFFE))
    {
        printf("  dg_dabs 2 -1 fail! - expected:\n  0x00000000000000000FFFFFFFFFFFFFFFB,\n instead got\n  %08x %08x %08x %08x \n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_dnegate()
{
    INT64 pud[2];

    printf("testing dg_dnegate\n");

    pud[0] = 0;
    pud[1] = 0;

    dg_dnegate(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 0))
    {
        printf("  dg_dnegate 0 fail! - expected 0, instead got %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = -2;
    pud[1] = -1;

    dg_dnegate(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 2))
    {
        printf("  dg_dnegate -2 fail! - expected:\n  2, instead got:\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 5;
    pud[1] = 7;

    dg_dnegate(pud);

    if ((pud[1] != 0xFFFFFFFFFFFFFFF8) ||
        (pud[0] != 0xFFFFFFFFFFFFFFFB))
    {
        printf("  dg_dnegate 5 7 fail! - expected:\n  0xFFFFFFFFFFFFFFF9FFFFFFFFFFFFFFFB,\n instead got\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 2;
    pud[1] = -1;

    dg_dnegate(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 0xFFFFFFFFFFFFFFFE))
    {
        printf("  dg_dnegate 2 -1 fail! - expected:\n  0x00000000000000000FFFFFFFFFFFFFFFB,\n instead got\n  %08x %08x %08x %08x \n",
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_dplus()
{
    UINT64 pud[4];

    printf("testing dg_dplus\n");

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dplus(pud);

    if ((pud[1] != 0x0000000000000000) ||
        (pud[0] != 0x0000000000000000) ||
        (pud[3] != 0) || 
        (pud[2] != 0))
    {
        printf("  dg_dplus 0 + 0 fail! - expected 0x000000000000000000000000000000000, instead got %08x %08x %08x %08x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 3;
    pud[1] = 5;
    pud[2] = 7;
    pud[3] = 11;

    dg_dplus(pud);

    if ((pud[1] != 0x0000000000000010) ||
        (pud[0] != 0x000000000000000A) ||
        (pud[3] != 11) ||
        (pud[2] != 7))
    {
        printf("  dg_dplus 3 5 7 11 fail! - expected:\n  0x0000000000000000b0000000000000007,\n  0x00000000000000012000000000000000A\n instead got:\n  %08x %08x %08x %08x\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0xFFFFFFFFFFFFFFFF;
    pud[1] = 5;
    pud[2] = 3;
    pud[3] = 11;

    dg_dplus(pud);

    if ((pud[1] != 0x0000000000000011) ||
        (pud[0] != 0x0000000000000002) ||
        (pud[3] != 11) ||
        (pud[2] != 3))
    {
        printf("  dg_dplus -1 5 3 11 fail! - expected:\n  0x0000000000000000b0000000000000003,\n  0x000000000000000190000000000000002\n  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

 
}

void testdg_dminus()
{
    UINT64 pud[4];

    printf("testing dg_dminus\n");

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dminus(pud);

    if ((pud[1] != 0x0000000000000000) ||
        (pud[0] != 0x0000000000000000) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dminus 0 - 0 fail! - expected 0x000000000000000000000000000000000, instead got %08x %08x %08x %08x %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 7;
    pud[1] = 11;
    pud[2] = 3;
    pud[3] = 5;

    dg_dminus(pud);

    if ((pud[1] != 0x0000000000000006) ||
        (pud[0] != 0x0000000000000004) ||
        (pud[3] != 5) ||
        (pud[2] != 3))
    {
        printf("  dg_dminus 7 11 3 5 fail! - expected:\n  0x000000000000000050000000000000003,\n  0x000000000000000060000000000000004\n instead got:\n  %08x %08x %08x %08x\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 3;
    pud[1] = 11;
    pud[2] = 0xFFFFFFFFFFFFFFFF;
    pud[3] = 5;

    dg_dminus(pud);

    if ((pud[1] != 0x0000000000000005) ||
        (pud[0] != 0x0000000000000004) ||
        (pud[2] != 0xFFFFFFFFFFFFFFFF) ||
        (pud[3] != 5))
    {
        printf("  dg_dminus 3 11 -1 5 fail! - expected:\n  0x00000000000000005FFFFFFFFFFFFFFFF,\n  0x000000000000000050000000000000004\n  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 1;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dminus(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 1) ||
        (pud[2] != 0) ||
        (pud[3] != 0))
    {
        printf("  dg_dminus 1 0 0 0 fail! - expected: 0 0 0 1  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_dulessthan()
{
    UINT64 pud[4];

    printf("testing dg_dulessthan\n");

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dulessthan(pud);

    if ((pud[1] != 0x0000000000000000) ||
        (pud[0] != 0x0000000000000000) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dulessthan 0 0 fail! - expected 0 0, instead got %08x %08x %08x %08x\n %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 1;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dulessthan(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 0) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dulessthan 1 0  fail! - expected:\n  0x000000000000000000000000000000000,\n  0x000000000000000000000000000000000\n instead got:\n  %08x %08x %08x %08x\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 1;
    pud[3] = 0;

    dg_dulessthan(pud);

    if ((pud[1] != 0xFFFFFFFFFFFFFFFF) || // the result of the subtract with borrow
        (pud[0] != 0xFFFFFFFFFFFFFFFF) || // the returned flag
        (pud[2] != 1) ||
        (pud[3] != 0))
    {
        printf("  dg_dulessthan 0 1 fail! - expected:\n  0x00000000000000000000000000000001,\n  0x0000000000000000FFFFFFFFFFFFFFFF\n  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_dugreaterequalthan()
{
    UINT64 pud[4];

    printf("testing dg_dugreaterequalthan\n");

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dugreaterequalthan(pud);

    if ((pud[1] != 0) ||  // the result of the subtract with borrow
        (pud[0] != -1) || // the returned flag
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dugreaterequalthan 0 0 fail! - expected 0 0 0 -1, instead got:\n %08x %08x %08x %08x\n %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 1;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dugreaterequalthan(pud);

    if ((pud[1] != 0) ||  // the result of the subtract with borrow
        (pud[0] != -1) || // the returned flag
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dugreaterequalthan 1 0  fail! - expected: 0 0 0 -1 instead got:\n  %08x %08x %08x %08x\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 1;
    pud[3] = 0;

    dg_dugreaterequalthan(pud);

    if ((pud[1] != -1) || // the result of the subtract with borrow
        (pud[0] != 0)  || // the returned flag
        (pud[2] != 1) ||
        (pud[3] != 0))
    {
        printf("  dg_dugreaterequalthan 0 1 fail! - expected: 0 1 0 0  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_dlessthan()
{
    INT64 pud[4];

    printf("testing dg_dlessthan\n");

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dlessthan(pud);

    if ((pud[1] != 0x0000000000000000) ||
        (pud[0] != 0x0000000000000000) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dlessthan 0 0 fail! - expected 0 0, instead got %08x %08x %08x %08x\n %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 1;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dlessthan(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 0) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dlessthan 1 0  fail! - expected:\n  0x000000000000000000000000000000000,\n  0x000000000000000000000000000000000\n instead got:\n  %08x %08x %08x %08x\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 1;
    pud[3] = 0;

    dg_dlessthan(pud);

    if ((pud[1] != 0xFFFFFFFFFFFFFFFF) || // the result of the subtract with borrow
        (pud[0] != 0xFFFFFFFFFFFFFFFF) || // the returned flag
        (pud[2] != 1) ||
        (pud[3] != 0))
    {
        printf("  dg_dlessthan 0 1 fail! - expected: 0 -1  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = -2;
    pud[1] = -1;
    pud[2] = 0;
    pud[3] = 0;

    dg_dlessthan(pud);

    if ((pud[1] != -1) || // the result of the subtract with borrow
        (pud[0] != -1) || // the returned flag
        (pud[2] != 0) ||
        (pud[3] != 0))
    {
        printf("  dg_dlessthan -1 0 fail! - expected: 0 0 -1 -1  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0;
    pud[1] = 1;
    pud[2] = -1;
    pud[3] = -1;

    dg_dlessthan(pud);

    if ((pud[1] != 1) || // the result of the subtract with borrow
        (pud[0] != 0) || // the returned flag
        (pud[2] != -1) ||
        (pud[3] != -1))
    {
        printf("  dg_dlessthan 0 1 -1 -1 fail! - expected: -1 -1 1 0  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_dgreaterequalthan()
{
    INT64 pud[4];

    printf("testing dg_dgreaterequalthan\n");

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dgreaterequalthan(pud);

    if ((pud[1] != 0) ||
        (pud[0] != -1) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dgreaterequalthan 0 0 fail! - expected 0 0 0 -1, instead got %08x %08x %08x %08x\n %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 1;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dgreaterequalthan(pud);

    if ((pud[1] != 0) ||
        (pud[0] != -1) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dgreaterequalthan 1 0  fail! - expected: 0 0 0 -1 instead got:\n  %08x %08x %08x %08x\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 1;
    pud[3] = 0;

    dg_dgreaterequalthan(pud);

    if ((pud[1] != 0xFFFFFFFFFFFFFFFF) || // the result of the subtract with borrow
        (pud[0] != 0) || // the returned flag
        (pud[2] != 1) ||
        (pud[3] != 0))
    {
        printf("  dg_dgreaterequalthan 0 1 fail! - expected: 0 1 0 -1  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = -2;
    pud[1] = -1;
    pud[2] = 0;
    pud[3] = 0;

    dg_dgreaterequalthan(pud);

    if ((pud[1] != -1) || // the result of the subtract with borrow
        (pud[0] != 0) || // the returned flag
        (pud[2] != 0) ||
        (pud[3] != 0))
    {
        printf("  dg_dgreaterequalthan -1 0 fail! - expected: 0 0 -1 0  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0;
    pud[1] = 1;
    pud[2] = -1;
    pud[3] = -1;

    dg_dgreaterequalthan(pud);

    if ((pud[1] != 1) || // the result of the subtract with borrow
        (pud[0] != -1) || // the returned flag
        (pud[2] != -1) ||
        (pud[3] != -1))
    {
        printf("  dg_dgreaterequalthan 0 1 -1 -1 fail! - expected: -1 -1 -1 2  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_dumin()
{
    UINT64 pud[4];

    printf("testing dg_dumin\n");

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dumin(pud);

    if ((pud[1] != 0x0000000000000000) ||
        (pud[0] != 0x0000000000000000) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dumin 0 0 fail! - expected 0 0, instead got %08x %08x %08x %08x\n %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 1;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dumin(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 0) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dumin 1 0  fail! - expected: 0 0 0 0 instead got:\n  %08x %08x %08x %08x\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 1;
    pud[3] = 0;

    dg_dumin(pud);

    if ((pud[1] != 0) || 
        (pud[0] != 0) || 
        (pud[2] != 1) ||
        (pud[3] != 0))
    {
        printf("  dg_dumin 0 1 fail! - expected: 0 1 0 0  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_dumax()
{
    UINT64 pud[4];

    printf("testing dg_dumax\n");

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dumax(pud);

    if ((pud[1] != 0) ||  
        (pud[0] != 0) || 
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dumax 0 0 fail! - expected 0 0 0 -1, instead got:\n %08x %08x %08x %08x\n %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 1;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dumax(pud);

    if ((pud[1] != 0) ||  
        (pud[0] != 1) || 
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dumax 1 0  fail! - expected: 0 0 0 1 instead got:\n  %08x %08x %08x %08x\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 1;
    pud[3] = 0;

    dg_dumax(pud);

    if ((pud[1] != 0) || 
        (pud[0] != 1) || 
        (pud[2] != 1) ||
        (pud[3] != 0))
    {
        printf("  dg_dumax 0 1 fail! - expected: 0 1 0 1  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_dmin()
{
    INT64 pud[4];

    printf("testing dg_dmin\n");

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dmin(pud);

    if ((pud[1] != 0x0000000000000000) ||
        (pud[0] != 0x0000000000000000) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dmin 0 0 fail! - expected 0 0, instead got %08x %08x %08x %08x\n %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 1;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dmin(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 0) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dmin 1 0  fail! - expected: 0 0 instead got:\n  %08x %08x %08x %08x\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 1;
    pud[3] = 0;

    dg_dmin(pud);

    if ((pud[1] != 0) || // the result of the subtract with borrow
        (pud[0] != 0) || // the returned flag
        (pud[2] != 1) ||
        (pud[3] != 0))
    {
        printf("  dg_dmin 0 1 fail! - expected: 0 1 0 0  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = -2;
    pud[1] = -1;
    pud[2] = 0;
    pud[3] = 0;

    dg_dmin(pud);

    if ((pud[1] != -1) || // the result of the subtract with borrow
        (pud[0] != -2) || // the returned flag
        (pud[2] != 0) ||
        (pud[3] != 0))
    {
        printf("  dg_dmin -1 0 fail! - expected: 0 0 -1 -2  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0;
    pud[1] = 1;
    pud[2] = -2;
    pud[3] = -1;

    dg_dmin(pud);

    if ((pud[1] != -1) || // the result of the subtract with borrow
        (pud[0] != -2) || // the returned flag
        (pud[2] != -2) ||
        (pud[3] != -1))
    {
        printf("  dg_dmin 0 1 -2 -1 fail! - expected: -1 -2 -1 -2  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

void testdg_dmax()
{
    INT64 pud[4];

    printf("testing dg_dmax\n");

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dmax(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 0) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dmax 0 0 fail! - expected 0 0 0 0, instead got %08x %08x %08x %08x\n %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 1;
    pud[1] = 0;
    pud[2] = 0;
    pud[3] = 0;

    dg_dmax(pud);

    if ((pud[1] != 0) ||
        (pud[0] != 1) ||
        (pud[3] != 0) ||
        (pud[2] != 0))
    {
        printf("  dg_dmax 1 0  fail! - expected: 0 0 0 1 instead got:\n  %08x %08x %08x %08x\n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0;
    pud[1] = 0;
    pud[2] = 1;
    pud[3] = 0;

    dg_dmax(pud);

    if ((pud[1] != 0) || // the result of the subtract with borrow
        (pud[0] != 1) || // the returned flag
        (pud[2] != 1) ||
        (pud[3] != 0))
    {
        printf("  dg_dmax 0 1 fail! - expected: 0 1 0 1  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = -2;
    pud[1] = -1;
    pud[2] = 0;
    pud[3] = 0;

    dg_dmax(pud);

    if ((pud[1] != 0) || // the result of the subtract with borrow
        (pud[0] != 0) || // the returned flag
        (pud[2] != 0) ||
        (pud[3] != 0))
    {
        printf("  dg_dmax -1 0 fail! - expected: 0 0 0 0  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }

    pud[0] = 0;
    pud[1] = 1;
    pud[2] = -1;
    pud[3] = -1;

    dg_dmax(pud);

    if ((pud[1] != 1) || // the result of the subtract with borrow
        (pud[0] != 0) || // the returned flag
        (pud[2] != -1) ||
        (pud[3] != -1))
    {
        printf("  dg_dmax 0 1 -1 -1 fail! - expected: -1 -1 1 0  instead got\n  %08x %08x %08x %08x \n  %08x %08x %08x %08x\n",
            ((UINT32*)(pud))[7],
            ((UINT32*)(pud))[6],
            ((UINT32*)(pud))[5],
            ((UINT32*)(pud))[4],
            ((UINT32*)(pud))[3],
            ((UINT32*)(pud))[2],
            ((UINT32*)(pud))[1],
            ((UINT32*)(pud))[0]);
    }
}

/*
void testdg_makedototobuf()
{
    Bufferhandle BHarrayhead;

    UINT64 codebufferid;
    unsigned char* mypcodebuffer;
    UINT64* mypcodebufferlength;

    UINT64 ogetbaseaddressfunction;
    // UINT64 ofirstimportpointer;
    // UINT64 osecondimportpointer;
    //UINT64 othirdimportpointer;
    
    UINT64 otestcallimportfunction;
    UINT64 ogetgotaddressfunction;
    UINT64 ogetgotaddress2function;
    UINT64 ogetgotaddress3function;
    
    UINT64 ogotimport1;
    UINT64 ogotimport2;
    UINT64 ogotimport3;
    UINT64 ogotcallimportfunction;
    
    UINT64 ofirstfunction;
    UINT64 osecondfunction;
    
    UINT64 exportsparentelementid;
    UINT64 importsparentelementid;
    
    UINT64 destbufferid;
    
    UINT64 mysrchlistid;
    UINT64 x;
    UINT64* pimporttable;

    const char* pError;

    UINT64 mycompiledlibhandle;
    void* symbol1 = (void*)-1;
    void* symbol2 = (void*)-1;
    void* symbol3 = (void*)-1;
    void* symboltestcallimportfunction = (void*)-1;
    void* symbolgetgotimportfunction = (void*)-1;
    void* symbolgetgotimport2function = (void*)-1;
    void* symbolgetgotimport3function = (void*)-1;
    
    UINT64 mydiaperglulibhandle;
    void* dg_testasmsymbol = (void*)-1;
    void* dg_successsymbol = (void*)-1;
    
    char* argv[14];
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_makedototobuf... This test runs ld so it might take awhile.\n");

    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

    // need to create a code buffer
    codebufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        1000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making the code buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (0 == codebufferid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making the code buffer, for some reason the codebufferid is 0, which is reserved for the error stack.\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        currentcompilebuffer,
        codebufferid);
	
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_makedototobuf success case - could not set current compile buffer\n");
        return;
    }
    */
    
    /*
    ofirstimportpointer = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);
    
    // for the first imported pointer at offset 0
    dg_pushbufferuint64 (
        &BHarrayhead,
        codebufferid,
        0);
    
    osecondimportpointer = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);
    
    // for the second imported pointer at offset 8
    dg_pushbufferuint64 (
        &BHarrayhead,
        codebufferid,
        0);
    
    othirdimportpointer = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);
    
    // for the third imported pointer at offset 16
    dg_pushbufferuint64 (
        &BHarrayhead,
        codebufferid,
        0);
    */
    
    /*
    otestcallimportfunction = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);
    
    dg_compilecallbracketripd32 (
        &BHarrayhead,
        0);  // 6 byte instruction
    
    ogotcallimportfunction = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);
    
    dg_compilereturn(&BHarrayhead);
    
    
    
    ogetgotaddressfunction = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);
    
    dg_compilemovbracketripd32torax (
        &BHarrayhead,
        0);
    
    ogotimport1 = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);
    
    dg_compilereturn(&BHarrayhead);
    
    
    ogetgotaddress2function = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);
    
    dg_compilemovbracketripd32torax (
        &BHarrayhead,
        0);
    
    ogotimport2 = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);
    
    dg_compilereturn(&BHarrayhead);
    
    
    ogetgotaddress3function = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);
    
    dg_compilemovbracketripd32torax (
        &BHarrayhead,
        0);
    
    ogotimport3 = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);
    
    dg_compilereturn(&BHarrayhead);
    
    
    // offset 6
    ogetbaseaddressfunction = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);
    
    dg_compilecalloffset (
        &BHarrayhead,
        0); // 5 byte instruction
    
    // offset 11
    dg_compilepopregfromret(
        &BHarrayhead,
        dg_rax);
    
    dg_compilemovntoreg(
        &BHarrayhead,
        (UINT64)(-19),
        dg_rdx);
    
    dg_compileaddregtoreg (
        &BHarrayhead,
        dg_rax, // it seems I have src and dest regs reversed for this function
        dg_rdx);
    
    dg_compilereturn(&BHarrayhead);
    
    
    ofirstfunction = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);

    dg_compilemovntorax (
        &BHarrayhead,
        0x9988776655443322);

    dg_compilereturn(&BHarrayhead);
    

    osecondfunction = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);

    dg_compilemovntorax (
        &BHarrayhead,
        0x1213141516171819);

    dg_compilereturn(&BHarrayhead);
    
    
    // need to create an hlist
    mysrchlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // adding a root element for the symbol lists (name and value aren't used so making them empty)
    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"", // pname
        0, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // making parent for exports
    exportsparentelementid = dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        0, // parentelementid, // root element
        (unsigned char*)"", // pname
        0, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making exports parent element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // adding first export symbol
    x = ofirstfunction;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        exportsparentelementid, // parentelementid,
        (unsigned char*)"firstsymbol", // pname
        11, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making first exports hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    
    // adding second export symbol
    x = osecondfunction;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        exportsparentelementid, // parentelementid,
        (unsigned char*)"secondsymbol", // pname
        12, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making second new exports hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    // adding third export symbol
    x = ogetbaseaddressfunction;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        exportsparentelementid, // parentelementid,
        (unsigned char*)"getbaseaddress", // pname
        14, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making third new export hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding test call import function export symbol
    x = otestcallimportfunction;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        exportsparentelementid, // parentelementid,
        (unsigned char*)"testcallimport", // pname
        14, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making test call import function export hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    x = ogetgotaddressfunction;
    
    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        exportsparentelementid, // parentelementid,
        (unsigned char*)"getgotimport", // pname
        12, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making getgotimport function export hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    x = ogetgotaddress2function;
    
    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        exportsparentelementid, // parentelementid,
        (unsigned char*)"getgotimport2", // pname
        13, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making getgotimport2 function export hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    x = ogetgotaddress3function;
    
    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        exportsparentelementid, // parentelementid,
        (unsigned char*)"getgotimport3", // pname
        13, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making getgotimport3 function export hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    // adding parent element for imports
    importsparentelementid = dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        0, // parentelementid, // root element
        (unsigned char*)"", // pname
        0, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making imports parent element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    // adding import symbol for test call import function
    x = ogotimport1 - 4;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        importsparentelementid, // parentelementid,
        (unsigned char*)"dg_testasm", // pname
        10, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making import symbol for get got address 1 hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    x = ogotimport2 - 4;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        importsparentelementid, // parentelementid,
        (unsigned char*)"dg_success", // pname
        10, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making import symbol for get got address 2 hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    x = ogotimport3 - 4;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        importsparentelementid, // parentelementid,
        (unsigned char*)"dg_testasm", // pname
        10, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making import symbol for get got address 3 hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    
    x = ogotcallimportfunction - 4;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        importsparentelementid, // parentelementid,
        (unsigned char*)"dg_testasm", // pname
        10, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making import symbol for call got import function hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    */
    
    /*
    // adding first import symbol
    x = ofirstimportpointer;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        importsparentelementid, // parentelementid,
        (unsigned char*)"firstsymbol", // pname
        11, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making second new hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
   
    // adding second import symbol
    x = osecondimportpointer;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        importsparentelementid, // parentelementid,
        (unsigned char*)"secondsymbol", // pname
        12, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making second imports hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    // adding third import symbol
    x = othirdimportpointer;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        importsparentelementid, // parentelementid,
        (unsigned char*)"firstsymbol", // pname
        11, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making third new hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    */
/*
    // need to make a destination buffer
    destbufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        1000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error making the destination buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    mypcodebuffer = dg_getpbuffer (
        &BHarrayhead,
        codebufferid,
        &mypcodebufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error getting pointer to code buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_makedototobuf (
        &BHarrayhead,
        mypcodebuffer,
        *mypcodebufferlength,
        mysrchlistid,
        exportsparentelementid, // exportssymbollistparentelementid,
        mysrchlistid,
        importsparentelementid,
        destbufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        // pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error doing dg_makesharedlibtobuf, got:\n");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // save to file
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        19, 
        (unsigned char*)"compiledtest.o");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error pushing file name string to string stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_pushbufferuint64(
        &BHarrayhead, 
        DG_DATASTACK_BUFFERID, 
        destbufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error pushing destination buffer id to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_forthsavefilestring(&BHarrayhead);
   
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error saving new shared lib to file, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }
    
    argv[0] = (char*)"ld";
    argv[1] = (char*)"-macosx_version_min";
    argv[2] = (char*)"10.11";
    argv[3] = (char*)"-dynamic";
    argv[4] = (char*)"-dylib";
    argv[5] = (char*)"-no_uuid";
    argv[6] = (char*)"-no_eh_labels";
    argv[7] = (char*)"-o";
    argv[8] = (char*)"compiledtest.dylib";
    argv[9] = (char*)"compiledtest.o";
    argv[10] = (char*)"-ldiaperglu";
    argv[11] = (char*)"-lSystem"; // this lib need to prevent  ld: symbol dyld_stub_binder not found (normally in libSystem.dylib)
    argv[12] = (char*)"-L.";
    argv[13] = (char*)NULL;
    
    pError = dg_runfileandwait(
    // Bufferhandle* pBHarrayhead,
        "ld",  // filename
        argv,
        (char**)NULL,  // envp
        dg_success);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error running ld to convert the .o to a .dylib, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    pError = dg_loadlibrary(
        (char*)"libdiaperglu.dylib\0",
        (UINT64*)&mydiaperglulibhandle,
        (const char*)dg_success);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error opening the libdiaperglu.dylib file, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_testasmsymbol = dlsym((void*)mydiaperglulibhandle, "dg_testasm");
    dg_successsymbol = dlsym((void*)mydiaperglulibhandle, "dg_success");
    
    pError = dg_loadlibrary(
        (char*)"compiledtest.dylib\0",
        (UINT64*)&mycompiledlibhandle,
        (const char*)dg_success);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - got an error opening the .dylib file, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    symbol1 = dlsym((void*)mycompiledlibhandle, "firstsymbol");
    
    symbol2 = dlsym((void*)mycompiledlibhandle, "secondsymbol");

    symbol3 = dlsym((void*)mycompiledlibhandle, "getbaseaddress");
    
    symboltestcallimportfunction = dlsym((void*)mycompiledlibhandle, "testcallimport");
    
    symbolgetgotimportfunction = dlsym((void*)mycompiledlibhandle, "getgotimport");
    symbolgetgotimport2function = dlsym((void*)mycompiledlibhandle, "getgotimport2");
    symbolgetgotimport3function = dlsym((void*)mycompiledlibhandle, "getgotimport3");
    
    x = ((UINT64(*)())(symbol1))();
    
    if (x != 0x9988776655443322)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - calling first exported function returned wrong value\n");
        
        return;
    }
    
    x = ((UINT64(*)())(symbol2))();
    
    if (x != 0x1213141516171819)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - calling second exported function returned wrong value\n");
        
        return;
    }
    
    x = ((UINT64(*)())(symbolgetgotimportfunction))();
    
    if ( x != (UINT64)dg_testasmsymbol)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - import of dg_testasm from libdiaperglu did not match the value obtained using dlsym on libdiaperglu, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)dg_testasmsymbol);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    x = ((UINT64(*)())(symbolgetgotimport2function))();
    
    if ( x != (UINT64)dg_successsymbol)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - import of dg_success from libdiaperglu did not match the value obtained using dlsym on libdiaperglu, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)dg_testasmsymbol);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    x = ((UINT64(*)())(symbolgetgotimport3function))();
    
    if ( x != (UINT64)dg_testasmsymbol)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - 2nd import of dg_testasm from libdiaperglu did not match the value obtained using dlsym on libdiaperglu, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)dg_testasmsymbol);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    
    x = ((UINT64(*)(UINT64))(symboltestcallimportfunction))(0x1133224455776688);
    
    if ( x != 0x1133224455776689)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - test call import function did not have correct result, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, 0x1133224455776689);
        dg_printzerostring(&BHarrayhead, (unsigned char*)" got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    */
    
    /*
    if (x != 0x1122334455667789)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - calling testcallimport exported function returned wrong value\n");
        
        return;
    }
     */
    
    
    /*
    pimporttable = ((UINT64*(*)())(symbol3))();
    */
    /*
    dg_hexdumpsegment (
        &BHarrayhead,
        (UINT8*)pimporttable,
        0x80);
     */
    
    /*
    if (pimporttable[0] != (UINT64)symbol1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - first import address incorrect, expected ");
        dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)symbol1);
        dg_printzerostring(&BHarrayhead, (unsigned char*)", got ");
        dg_writestdoutuint64tohex(&BHarrayhead, pimporttable[0]);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        dg_hexdumpsegment (
            &BHarrayhead,
            (UINT8*)pimporttable,
            0x80);
        
        return;
    }
    
    if (pimporttable[1] != (UINT64)symbol2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - second import address incorrect\n");
        
        return;
    }
    
    if (pimporttable[2] != (UINT64)symbol1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makedototobuf success case - third import address incorrect\n");
        
        return;
    }
    */
    /*
    dg_freeallbuffers(&BHarrayhead);
}
*/
/*
void testdg_makesharedlibtobuf()
{
    Bufferhandle BHarrayhead;

    UINT64 codebufferid;
    unsigned char* mypcodebuffer;
    UINT64* mypcodebufferlength;

    UINT64 osecondfunction;

    UINT64 triebufferid;
    unsigned char* myptriebuffer;
    UINT64* myptriebufferlength;

    UINT64 exportvaluelstringoffsetbufferid;
    UINT64 exportvaluelstringstringbufferid;
    
    UINT64 destbufferid;
    // unsigned char* mypdestbuffer;
    // UINT64* mypdestbufferlength;
    
    UINT64 mysrchlistid;
    UINT64 x;

    const char* pError;

    void* mycompiledlibhandle = (void*)-1;
    void* symbol1 = (void*)-1;
    void* symbol2 = (void*)-1;
            
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_makesharedlibtobuf\n");

    dg_initbuffers(&BHarrayhead);
    
    dg_initvariables(&BHarrayhead);
    
    dg_inithlists (&BHarrayhead);

    // need to create a code buffer
    codebufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        1000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error making the code buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    if (0 == codebufferid)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error making the code buffer, for some reason the codebufferid is 0, which is reserved for the error stack.\n");
        return;
    }

    dg_putbufferuint64(
        &BHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        currentcompilebuffer,
        codebufferid);
	
    if (BHarrayhead.errorcount != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_makesharedlibtobuf success case - could not set current compile buffer\n");
        return;
    }

    dg_compilemovntorax (
        &BHarrayhead,
        0x9988776655443322);

    dg_compilereturn(&BHarrayhead);

    osecondfunction = dg_getbufferlength(
        &BHarrayhead,
        codebufferid);

    dg_compilemovntorax (
        &BHarrayhead,
        0x1213141516171819);

    dg_compilereturn(&BHarrayhead);
    
    // need to create a trie export buffer
    triebufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        1000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error making the trie buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    exportvaluelstringoffsetbufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        10000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error making the value offset buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    exportvaluelstringstringbufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        10000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error making the value string buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // need to create an hlist
    mysrchlistid = dg_newhlist(&BHarrayhead);
    
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // adding a root element for the symbol list (name and value aren't used so making them empty)
    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)"", // pname
        0, // namelength,
        (unsigned char*)"", // pvalue,
        0); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error making first new hlist root element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // adding first symbol
    x = 0;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)"firstsymbol", // pname
        11, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error making first new hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // adding second symbol
    x = osecondfunction;

    dg_newhlistelement (
        &BHarrayhead,
        mysrchlistid, // hlistid,
        0, // parentelementid,
        (unsigned char*)"secondsymbol", // pname
        12, // namelength,
        (unsigned char*)(&x), // pvalue,
        8); // valuelength);
        
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error making second new hlist child element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_makemachotrieforlt256 (
        &BHarrayhead,
        mysrchlistid,
        0,                      // srcparentelementid,
        (unsigned char*)"_",    //  pprefix, // this will likely be a pointer to a '-'
        1,                      // prefixlength,     // this will likely be 1
        exportvaluelstringoffsetbufferid,
        exportvaluelstringstringbufferid,
        triebufferid);          // destbufid)

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error making export trie, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // need to make a destination buffer
    destbufferid = dg_newbuffer (
        &BHarrayhead,
        1000, // growby,
        1000, // maxsize,
        &pError,
        FORTH_FALSE); // forceoutofmemory)
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error making the destination buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }


    mypcodebuffer = dg_getpbuffer (
        &BHarrayhead,
        codebufferid,
        &mypcodebufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error getting pointer to code buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    myptriebuffer = dg_getpbuffer (
        &BHarrayhead,
        triebufferid,
        &myptriebufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error getting pointer to trie buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_makesharedlibtobuf (
        &BHarrayhead,
        mypcodebuffer,
        *mypcodebufferlength,
        myptriebuffer,
        *myptriebufferlength,
        destbufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        // pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error doing dg_makesharedlibtobuf, got:\n");
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // save to file
    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID, 
        DG_STRINGSTRINGSTACK_BUFFERID, 
        19, 
        (unsigned char*)"compiledtest.dylib");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error pushing file name string to string stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_pushbufferuint64(
        &BHarrayhead, 
        DG_DATASTACK_BUFFERID, 
        destbufferid);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error pushing destination buffer id to data stack, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_forthsavefilestring(&BHarrayhead);
   
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error saving new shared lib to file, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // dlopen file
    mycompiledlibhandle = dlopen("./compiledtest.dylib", RTLD_NOW);

    if (0 == (UINT64)mycompiledlibhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error dlopening the compiled shared library, got:\n");
        return;
        pError = dlerror();
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    // dlsym the two functions
    symbol1 = dlsym(mycompiledlibhandle, "firstsymbol");

    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error doing dlsym for the first symbol, got:\n");
        return;
        pError = dlerror();
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;

    symbol2 = dlsym(mycompiledlibhandle, "secondsymbol");

    dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_makesharedlibtobuf success case - got an error doing dlsym for the second symbol, got:\n");
        return;
        pError = dlerror();
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;

    // call the functions and check the results
    dg_printzerostring(&BHarrayhead, (unsigned char*)"shared library handle = ");
    dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)mycompiledlibhandle);
    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    dg_printzerostring(&BHarrayhead, (unsigned char*)"first symbol value = ");
    dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)symbol1);
    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    dg_printzerostring(&BHarrayhead, (unsigned char*)"second symbol value = ");
    dg_writestdoutuint64tohex(&BHarrayhead, (UINT64)symbol2);
    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");

    dlclose(mycompiledlibhandle);

    dg_freeallbuffers(&BHarrayhead);
}
*/


void testdg_getsenvnamevalue ()
{
    Bufferhandle BHarrayhead;
    
    dg_initpbharrayhead(&BHarrayhead);
    
    const char* pError = NULL;
    char* argv[8];
    
    argv[0] = (char*)"oat=yes";
    argv[1] = 0;
    argv[2] = (char*)"potato=no";
    argv[3] = (char*)"mustard=yummy";
    argv[4] = (char*)"ketchupy";
    argv[5] = (char*)"hotdoggitydog=";
    argv[6] = 0;
    
    UINT64 argc = 1;
    
    char* pnametofind = (char*)"potato";
    UINT64 nametofindlength = 6;
    
    char* pfoundname;
    UINT64 foundnamelength;
    
    char* pfoundvalue;
    UINT64 foundvaluelength;
    
    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getsenvnamevalue\n");
    
    // first one found case
    pnametofind = (char*)"potato";
    nametofindlength = 6;
    
    pError = dg_getsenvnamevalue (
        argc,
        argv,
        pnametofind,
        nametofindlength,
        &pfoundname,
        &foundnamelength,
        &pfoundvalue,
        &foundvaluelength);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue first one found success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pfoundname != argv[2])
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue first one found success case - got wrong pname\n");
    }
    
    if (foundnamelength != 6)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue first one found success case - got wrong name length, expected 6, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundnamelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pfoundvalue != argv[2] + 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue first one found success case - got wrong pvalue\n");
    }
    
    if (foundvaluelength != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue first one found success case - got wrong value length, expected 2, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundvaluelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // second one found case
    pnametofind = (char*)"mustard";
    nametofindlength = 7;
    
    pError = dg_getsenvnamevalue (
        argc,
        argv,
        pnametofind,
        nametofindlength,
        &pfoundname,
        &foundnamelength,
        &pfoundvalue,
        &foundvaluelength);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue second one found success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pfoundname != argv[3])
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue second one found success case - got wrong pname\n");
    }
    
    if (foundnamelength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue second one found success case - got wrong name length, expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundnamelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pfoundvalue != argv[3] + 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue second one found success case - got wrong pvalue\n");
    }
    
    if (foundvaluelength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue second one found success case - got wrong value length, expected 5, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundvaluelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // third one found case
    pnametofind = (char*)"ketchupy";
    nametofindlength = 8;
    
    pError = dg_getsenvnamevalue (
        argc,
        argv,
        pnametofind,
        nametofindlength,
        &pfoundname,
        &foundnamelength,
        &pfoundvalue,
        &foundvaluelength);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue third one found success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pfoundname != argv[4])
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue third one found success case - got wrong pname\n");
    }
    
    if (foundnamelength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue third one found success case - got wrong name length, expected 7, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundnamelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pfoundvalue != argv[4] + 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue third one found success case - got wrong pvalue\n");
    }
    
    if (foundvaluelength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue third one found success case - got wrong value length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundvaluelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }  
    
    // fourth one found case
    pnametofind = (char*)"hotdoggitydog";
    nametofindlength = 13;
    
    pError = dg_getsenvnamevalue (
        argc,
        argv,
        pnametofind,
        nametofindlength,
        &pfoundname,
        &foundnamelength,
        &pfoundvalue,
        &foundvaluelength);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue fourth one found success case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pfoundname != argv[5])
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue fourth one found success case - got wrong pname\n");
    }
    
    if (foundnamelength != 13)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue fourth one found success case - got wrong name length, expected 13, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundnamelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pfoundvalue != argv[5] + 14)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue fourth one found success case - got wrong pvalue\n");
    }
    
    if (foundvaluelength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue fourth one found success case - got wrong value length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundvaluelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // not found case
    pnametofind = (char*)"mustards";
    nametofindlength = 8;
    
    pError = dg_getsenvnamevalue (
        argc,
        argv,
        pnametofind,
        nametofindlength,
        &pfoundname,
        &foundnamelength,
        &pfoundvalue,
        &foundvaluelength);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue not found case - got an error, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pfoundname != NULL)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue not found case - got wrong pname\n");
    }
    
    if (foundnamelength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue not found case - got wrong name length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundnamelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (pfoundvalue != NULL)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue not found case - got wrong pvalue\n");
    }
    
    if (foundvaluelength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_getsenvnamevalue not found case - got wrong value length, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, foundvaluelength);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}




void testdg_chartodigit()
{
	UINT64 x = 0;

    Bufferhandle BHarrayhead;

    BHarrayhead.pisapiecb= (void*)-1;

	dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_chartodigit\n");

	x = dg_chartodigit('0');

	if (x != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case 0\n");
	}

	x = dg_chartodigit('1');

	if (x != 1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case 1\n");
	}

	x = dg_chartodigit('2');

	if (x != 2)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case 2\n");
	}

	x = dg_chartodigit('3');

	if (x != 3)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case 3\n");
	}

	x = dg_chartodigit('4');

	if (x != 4)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case 4\n");
	}

	x = dg_chartodigit('5');

	if (x != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case 5\n");
	}

	x = dg_chartodigit('6');

	if (x != 6)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case 6\n");
	}

	x = dg_chartodigit('7');

	if (x != 7)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case 7\n");
	}

	x = dg_chartodigit('8');

	if (x != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case 8\n");
	}

	x = dg_chartodigit('9');

	if (x != 9)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case 9\n");
	}

	x = dg_chartodigit('A');

	if (x != 10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case A\n");
	}

	x = dg_chartodigit('B');

	if (x != 11)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case B\n");
	}

	x = dg_chartodigit('C');

	if (x != 12)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case C\n");
	}

	x = dg_chartodigit('D');

	if (x != 13)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case D\n");
	}

	x = dg_chartodigit('E');

	if (x != 14)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case E\n");
	}

	x = dg_chartodigit('F');

	if (x != 15)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case F\n");
	}

	x = dg_chartodigit('F');

	if (x != 15)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case F\n");
	}

	x = dg_chartodigit('/');

	if (x != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case /\n");
	}

	x = dg_chartodigit(':');

	if (x != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case :\n");
	}

	x = dg_chartodigit('@');

	if (x != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case @\n");
	}

	x = dg_chartodigit('[');

	if (x != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case [\n");
	}

	x = dg_chartodigit('a');

	if (x != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_chartodigit case a\n");
	}
}


void testdg_pchartonumber()
{
	INT64 x = 0;

	UINT64 flag = FORTH_FALSE;

    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_pchartonumber\n");

	x = dg_pchartonumber((unsigned char*)"0", 1, 10, &flag);

	if (x != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 10 string '0' - number returned not 0\n"); 
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 10 string '0' - flag not FORTH_TRUE\n");
	}

	x = dg_pchartonumber((unsigned char*)"1234", 4, 10, &flag);

	if (x != 1234)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 10 string '1234' - number returned not 1234\n"); 
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 10 string '1234' - flag not FORTH_TRUE\n");
	}

	x = dg_pchartonumber((unsigned char*)"FE05", 4, 16, &flag);

	if (x != 0xfe05)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string 'FE05' - number returned not fe05\n"); 
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string 'FE05' - flag not FORTH_TRUE\n");
	}

	x = dg_pchartonumber((unsigned char*)"GE05", 4, 16, &flag);

	if (x != 0x0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string 'GE05' - number returned not 0\n"); 
	}

	if (flag != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string 'GE05' - flag not FORTH_FALSE\n");
	}

	x = dg_pchartonumber((unsigned char*)"-FE05", 5, 16, &flag);

	if (x != -0xfe05)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string '-FE05' - number returned not -fe05\n"); 
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string '-FE05' - flag not FORTH_TRUE\n");
	}

	x = dg_pchartonumber((unsigned char*)"-10", 3, 10, &flag);

	if (x != -10)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 10 string '-10' - number returned not -10\n"); 
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 10 string '-10' - flag not FORTH_TRUE\n");
	}

	x = dg_pchartonumber((unsigned char*)"HELLO", 5, 16, &flag);

	if (x != 0x0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string 'HELLO' - number returned not 0\n"); 
	}

	if (flag != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string 'HELLO' - flag not FORTH_FALSE\n");
	}

	x = dg_pchartonumber((unsigned char*)"abcde", 5, 16, &flag); // dg_forth standard is uppercase letters only

	if (x != 0x0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string 'abcde' - number returned not 0\n"); 
	}

	if (flag != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string 'abcde' - flag not FORTH_FALSE\n");
	}

	x = dg_pchartonumber((unsigned char*)"-", 1, 16, &flag);

	if (x != 0x0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string '-' - number returned not 0\n"); 
	}

	if (flag != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string '-' - flag not FORTH_FALSE\n");
	}

	x = dg_pchartonumber((unsigned char*)"00000", 0, 16, &flag);

	if (x != 0x0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string '' - number returned not 0\n"); 
	}

	if (flag != FORTH_FALSE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 16 string '' - flag not FORTH_FALSE\n");
	}

	x = dg_pchartonumber((unsigned char*)"000", 3, 10, &flag);

	if (x != 0)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 10 string '000' - number returned not 0\n"); 
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pchartonumber base 10 string '000' - flag not FORTH_TRUE\n");
	}
}



void testdg_hexdectonumber()
{
    INT64 x = 0;

	UINT64 flag = FORTH_FALSE;
    
    Bufferhandle BHarrayhead;
    
    BHarrayhead.pisapiecb= (void*)-1;
    
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_hexdectonumber\n");

    x = dg_hexdectonumber (
        (unsigned char*)"12",
        2,
        &flag);
    
    if (x != 12)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '12' - number returned not 12\n");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '12' - flag not FORTH_TRUE\n");
	}
    
    x = dg_hexdectonumber (
        (unsigned char*)"8",
        1,
        &flag);
    
    if (x != 8)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '8' - number returned not 8\n");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '8' - flag not FORTH_TRUE\n");
	}
    
    x = dg_hexdectonumber (
        (unsigned char*)"  736",
        5,
        &flag);
    
    if (x != 736)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '  736' - number returned not 736\n");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '  736' - flag not FORTH_TRUE\n");
	}
    
    x = dg_hexdectonumber (
        (unsigned char*)"2182   ",
        7,
        &flag);
    
    if (x != 2182)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '2182   ' - number returned not 2182\n");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '2182   ' - flag not FORTH_TRUE\n");
	}
    
    x = dg_hexdectonumber (
        (unsigned char*)"    5 ",
        6,
        &flag);
    
    if (x != 5)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '    5 ' - number returned not 5\n");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '    5 ' - flag not FORTH_TRUE\n");
	}
    
    x = dg_hexdectonumber (
        (unsigned char*)"0x100",
        5,
        &flag);
    
    if (x != 256)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '0x100' - number returned not 0x100\n");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '0x100' - flag not FORTH_TRUE\n");
	}
    
    x = dg_hexdectonumber (
        (unsigned char*)"0X101",
        5,
        &flag);
    
    if (x != 257)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '0X101' - number returned not 0x101\n");
	}

	if (flag != FORTH_TRUE)
	{
		dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_hexdectonumber string '0X101' - flag not FORTH_TRUE\n");
	}
}

void testdg_scanfornotbytereverse()
{
    UINT64 length;
    UINT64 value;
    void* pbuf = (void*)"abcdefghijklmnopqrstuvwxyzzz";
    void* pbuf2 = (void*)"abcdef";
    void* pbuf3 = (void*)"baaaaa";
    void* pbuf4 = (void*)"qqqqqq";
    void* badpbuf = (void*)-3;
    const char* flag;

    Bufferhandle BHarrayhead;

    dg_initpbharrayhead(&BHarrayhead);

    printf("testing dg_scanfornotbytereverse\n");
    //::dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_scanfornotbytereverse\n");

    // success case
    length = 28;
    value = (UINT64)'z';

    flag = dg_scanfornotbytereverse(pbuf, &length, value);

    if (length != 3)
    {
        printf("dg_scanfornotbytereverse success case - FAIL! got wrong length, got length = %d\n", (UINT32)length);
        //dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanfornotbytereverse success case - FAIL! got wrong length\n");
    }

    if (flag != dg_success)
    {
        printf("dg_scanfornotbytereverse success case - FAIL! got error %s\n", flag);
        //dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanfornotbytereverse success case - FAIL! got an error\n");
    }
    
    // success first case
    length = 6;
    value = (UINT64)'f';

    flag = dg_scanfornotbytereverse(pbuf2, &length, value);

    if (length != 1)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanfornotbytereverse success first case - FAIL! got wrong length\n");
    }

    if (flag != dg_success)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanfornotbytereverse success first case - FAIL! got an error\n");
    }

    // success last case
    length = 6;
    value = (UINT64)'a';

    flag = dg_scanfornotbytereverse(pbuf3, &length, value);

    if (length != 5)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanfornotbytereverse success last case - FAIL! got wrong length\n");
    }

    if (flag != dg_success)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanfornotbytereverse success last case - FAIL! got an error\n");
    }

    // not found case
    length = 6;
    value = (UINT64)'q';

    flag = dg_scanfornotbytereverse(pbuf4, &length, value);

    if (length != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanfornotbytereverse not found case - FAIL! got wrong length\n");
    }

    if (flag != dg_success)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanfornotbytereverse not found case - FAIL! got an error\n");
    }

    // not found match off end case
    length = 5;
    value = (UINT64)'a';

    flag = dg_scanfornotbytereverse((void*)((unsigned char*)pbuf3 + 1), &length, value);

    if (length != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanfornotbytereverse not found match off end case - FAIL! got wrong length\n");
    }

    if (flag != dg_success)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanfornotbytereverse not found match off end case - FAIL! got an error\n");
    }

    // bad memory case
    // dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_scanfornotbytereverse bad memory case\n");
    
    length = 26;
    value = (UINT64)'8';

    flag = dg_scanfornotbytereverse(badpbuf, &length, value);

    if (length != (UINT64)-1)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanfornotbytereverse bad memory case - FAIL! got wrong length\n");
    }

    if (flag != dg_badmemoryerror)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanfornotbytereverse bad memory case - FAIL! got wrong error expected:\n");
        dg_printzerostring(&BHarrayhead,  (unsigned char*)dg_badmemoryerror);
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"got:\n");
        dg_printzerostring(&BHarrayhead,  (unsigned char*)flag);
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"\n");
    }    
}



void testdg_scanforuint64()
{
	UINT64 length = 8;
	UINT64 value;
	UINT64 pbuf[8] = { 0x11223344, 0x55667788, 0xaabbccdd, 0xeeff0102, 0x03040506, 0x0708090a, 0x1a1b1c1d, 0x0b0c0d0e };
	UINT64* badpbuf = (UINT64*)-3;
	const char* flag;

    Bufferhandle BHarrayhead;

    BHarrayhead.pisapiecb = (void*)-1;

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_scanforuint64\n");

	// success case
	length = 8;
	value = 0xaabbccdd;

	flag = dg_scanforuint64(pbuf, &length, value);

	if (length != 2)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforuint64 success case - FAIL! got wrong length, got ");
        dg_writestdoutuinttodec(&BHarrayhead, length);
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"\n");
	}

	if (flag != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforuint64 success case - FAIL! got an error\n");
	}

	// success first case
	length = 8;
	value = 0x11223344;

	flag = dg_scanforuint64(pbuf, &length, value);

	if (length != 0)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforuint64 success first case - FAIL! got wrong length, got ");
        dg_writestdoutuinttodec(&BHarrayhead, length);
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"\n");
	}

	if (flag != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforuint64 success first case - FAIL! got an error\n");
	}

	// success last case
	length = 8;
	value = 0x0b0c0d0e;

	flag = dg_scanforuint64(pbuf, &length, value);

	if (length != 7)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforuint64 success last case - FAIL! got wrong length, got ");
        dg_writestdoutuinttodec(&BHarrayhead, length);
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"\n");
	}

	if (flag != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforuint64 success last case - FAIL! got an error\n");
	}

	// not found case
	length = 8;
	value = 0x37871727;

	flag = dg_scanforuint64(pbuf, &length, value);

	if (length != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforuint64 not found case - FAIL! got wrong length, got ");
        dg_writestdoutuinttodec(&BHarrayhead, length);
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"\n");
	}

	if (flag != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforuint64 not found case - FAIL! got an error\n");
	}

	// not found match off end case
	length = 7;
	value = 0x0b0c0d0e;

	flag = dg_scanforuint64(pbuf, &length, value);

	if (length != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforuint64 not found match off end case - FAIL! got wrong length, got ");
        dg_writestdoutuinttodec(&BHarrayhead, length);
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"\n");
	}

	if (flag != dg_success)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforuint64 not found match off end case - FAIL! got an error\n");
	}

	// bad memory case
	length = 8;
	value = 0x0b0c0d0e;

	flag = dg_scanforuint64(badpbuf, &length, value);

	if (length != (UINT64)-1)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforuint64 bad memory case - FAIL! got wrong length, got ");
        dg_writestdoutuinttodec(&BHarrayhead, length);
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"\n");
	}

	if (flag != dg_badmemoryerror)
	{
		dg_printzerostring(&BHarrayhead,  (unsigned char*)"dg_scanforuint64 bad memory case - FAIL! got wrong error, expected:\n");
        dg_printzerostring(&BHarrayhead,  (unsigned char*)dg_badmemoryerror);
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"got:\n");
        dg_printzerostring(&BHarrayhead,  (unsigned char*)flag);
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"\n");
	}	
}


void testdg_movebytesforward()
{
    unsigned char buf1[27] = "abcdefghijklmnopqrstuvwxyz";
    unsigned char buf2[27] = "                          ";
    unsigned char* pbuf1 = buf1;
    unsigned char* pbuf2 = buf2;

    Bufferhandle BHarrayhead;

    const char* perror;

    BHarrayhead.pisapiecb = (void*)-1;
    // test won't work in isapi mode unless this gets set correctly

    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_movebytesforward\n");

    // success case no overlap forward
    perror = dg_movebytesforward(pbuf1+1, pbuf2+1, 2);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success case no overlap forward - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf2[0] != ' ')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success case no overlap forward - FAIL! changed 1 before start of dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf2[1] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success case no overlap forward - FAIL! expected b at start of dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf2[2] != 'c')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success case no overlap forward - FAIL! expected c at 2nd dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf2[3] != ' ')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success case no overlap forward - FAIL! dest after end changed");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // success case length 0 bad pointers
    perror = dg_movebytesforward((unsigned char*)badbufferhandle, (unsigned char*)badbufferhandle, 0);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success length 0 bad pointers - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // bad memory case
    perror = dg_movebytesforward((unsigned char*)badbufferhandle, (unsigned char*)badbufferhandle, 5);

    if (perror != dg_badmemoryerror)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward bad memory case - FAIL! did not get correct error, expected:\n ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)dg_badmemoryerror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"got:\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // success forward overlap case
    perror = dg_movebytesforward(pbuf1, pbuf1+2, 5);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success forward overlap case - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success forward overlap case - FAIL! src changed at position 0 from a to ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[0]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[1] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success forward overlap case - FAIL! src changed at position 1 from b to ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[1]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[2] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success forward overlap case - FAIL! src 2, dest 0 should be a, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[2]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[3] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success forward overlap case - FAIL! src 3, dest 1 should be b, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[3]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[6] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success forward overlap case - FAIL! src 6, dest 4 should be a, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[6]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[7] != 'h')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesforward success forward overlap case - FAIL! dest after end changed, should be h, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[7]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}


void testdg_movebytesreverse()
{
    unsigned char buf1[27] = "abcdefghijklmnopqrstuvwxyz";
    unsigned char buf2[27] = "                          ";
    unsigned char* pbuf1 = buf1;
    unsigned char* pbuf2 = buf2;

    Bufferhandle BHarrayhead;

    const char* perror;

    BHarrayhead.pisapiecb = (void*)-1;
    // test won't work in isapi mode unless this gets set correctly

    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_movebytesreverse\n");

    // success case no overlap forward
    perror = dg_movebytesreverse(pbuf1+1, pbuf2+1, 2);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success case no overlap forward - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf2[0] != ' ')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success case no overlap forward - FAIL! changed 1 before start of dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf2[1] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success case no overlap forward - FAIL! expected b at start of dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf2[2] != 'c')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success case no overlap forward - FAIL! expected c at 2nd dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf2[3] != ' ')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success case no overlap forward - FAIL! dest after end changed");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // success case no overlap reverse
    perror = dg_movebytesreverse(pbuf2+1, pbuf1+5, 2);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success case no overlap reverse - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[4] != 'e')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success case no overlap reverse - FAIL! changed 1 before start of dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[5] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success case no overlap reverse - FAIL! expected b at start of dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[6] != 'c')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success case no overlap reverse - FAIL! expected c at 2nd dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[7] != 'h')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success case no overlap reverse - FAIL! dest after end changed");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // success case length 0 bad pointers
    perror = dg_movebytesreverse((unsigned char*)badbufferhandle, (unsigned char*)badbufferhandle, 0);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success length 0 bad pointers - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // bad memory case
    perror = dg_movebytesreverse((unsigned char*)badbufferhandle, (unsigned char*)badbufferhandle, 5);

    if (perror != dg_badmemoryerror)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse bad memory case - FAIL! did not get correct error, expected:\n ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)dg_badmemoryerror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"got:\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // success forward overlap case
    perror = dg_movebytesreverse(pbuf1, pbuf1+2, 5);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success forward overlap case - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success forward overlap case - FAIL! src changed at position 0 from a to ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[0]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[1] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success forward overlap case - FAIL! src changed at position 1 from b to ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[1]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[2] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success forward overlap case - FAIL! src 2, dest 0 should be a, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[2]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[3] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success forward overlap case - FAIL! src 3, dest 1 should be b, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[3]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[6] != 'e')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success forward overlap case - FAIL! src 6, dest 4 should be e, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[6]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[7] != 'h')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success forward overlap case - FAIL! dest after end changed, should be h, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[7]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // success reverse overlap case ababcdehijklm to ababcdehklml
    perror = dg_movebytesreverse(pbuf1+10, pbuf1+8, 3);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success reverse overlap case - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[7] != 'h')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success reverse overlap case - FAIL! dest changed before start from h to ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[7]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[8] != 'm')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success reverse overlap case - FAIL! dest first should be m, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[8]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[9] != 'l')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success reverse overlap case - FAIL! dest second should be l, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[9]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[10] != 'm')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success reverse overlap case - FAIL! dest third should be m, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[10]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[11] != 'l')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytesreverse success reverse overlap case - FAIL! after dest changed should be l, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[11]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}


void testdg_movebytes2()
{
    unsigned char buf1[27] = "abcdefghijklmnopqrstuvwxyz";
    unsigned char buf2[27] = "                          ";
    unsigned char* pbuf1 = buf1;
    unsigned char* pbuf2 = buf2;

    Bufferhandle BHarrayhead;

    const char* perror;

    BHarrayhead.pisapiecb = (void*)-1;
    // test won't work in isapi mode unless this gets set correctly

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_movebytes again\n");

	// success case no overlap forward
    perror = dg_movebytes(pbuf1+1, pbuf2+1, 2);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success case no overlap forward - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf2[0] != ' ')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success case no overlap forward - FAIL! changed 1 before start of dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf2[1] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success case no overlap forward - FAIL! expected b at start of dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf2[2] != 'c')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success case no overlap forward - FAIL! expected c at 2nd dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf2[3] != ' ')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success case no overlap forward - FAIL! dest after end changed");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // success case no overlap reverse
    perror = dg_movebytes(pbuf2+1, pbuf1+5, 2);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success case no overlap reverse - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[4] != 'e')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success case no overlap reverse - FAIL! changed 1 before start of dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[5] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success case no overlap reverse - FAIL! expected b at start of dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[6] != 'c')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success case no overlap reverse - FAIL! expected c at 2nd dest");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[7] != 'h')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success case no overlap reverse - FAIL! dest after end changed");
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // success case length 0 bad pointers
    perror = dg_movebytes((unsigned char*)badbufferhandle, (unsigned char*)badbufferhandle, 0);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success length 0 bad pointers - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // bad memory case
    perror = dg_movebytes((unsigned char*)badbufferhandle, (unsigned char*)badbufferhandle, 5);

    if (perror != dg_badmemoryerror)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes bad memory case - FAIL! did not get correct error, expected:\n ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)dg_badmemoryerror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"got:\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // success forward overlap case
    perror = dg_movebytes(pbuf1, pbuf1+2, 5);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success forward overlap case - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success forward overlap case - FAIL! src changed at position 0 from a to ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[0]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[1] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success forward overlap case - FAIL! src changed at position 1 from b to ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[1]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[2] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success forward overlap case - FAIL! src 2, dest 0 should be a, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[2]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[3] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success forward overlap case - FAIL! src 3, dest 1 should be b, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[3]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[6] != 'e')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success forward overlap case - FAIL! src 6, dest 4 should be e, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[6]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[7] != 'h')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success forward overlap case - FAIL! dest after end changed, should be h, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[7]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    // success reverse overlap case ababcdehijklm to ababcdehklml
    perror = dg_movebytes(pbuf1+10, pbuf1+8, 3);

    if (perror != dg_success)
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success reverse overlap case - FAIL! got an error");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[7] != 'h')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success reverse overlap case - FAIL! dest changed before start from h to ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[7]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[8] != 'k')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success reverse overlap case - FAIL! dest first should be k, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[8]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[9] != 'l')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success reverse overlap case - FAIL! dest second should be l, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[9]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[10] != 'm')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success reverse overlap case - FAIL! dest third should be m, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[10]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (pbuf1[11] != 'l')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"dg_movebytes success reverse overlap case - FAIL! after dest changed should be l, got ");
        dg_printzerostring(&BHarrayhead, &(pbuf1[11]));
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
}



void testdg_movebytesskipdestination()
{
	unsigned char buf1[27] = "abcdefghijklmnopqrstuvwxyz";
    unsigned char buf2[27] = "                          ";
    
    unsigned char* pbuf1 = buf1;
    unsigned char* pbuf2 = buf2;

    Bufferhandle BHarrayhead;

    const char* perror;

    BHarrayhead.pisapiecb = (void*)-1;
    // test won't work in isapi mode unless this gets set correctly

	dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_movebytesskipdestination\n");

	// success case no overlap source < destination
    
      // initializing buf2
    perror = dg_movebytes(pbuf1, pbuf2, 26);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source < destination - got an error doing copy to set up test. Got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    perror = dg_movebytesskipdestination(pbuf2, pbuf2 + 2, 2);
    
    if (pbuf2[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source < destination - changed src[0]\n");
    }

    if (pbuf2[1] != 'b')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source < destination - changed src[1]\n");
    }

    if (pbuf2[2] != 'a')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source < destination - dest[0] incorrect\n");    
    }

    if (pbuf2[3] != 'b')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source < destination - dest[1] incorrect\n");
    }
    
    if (pbuf2[4] != 'e')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source < destination - after destination changed\n");
    }

    // success case no overlap source > destination
    
      // initializing buf2
    perror = dg_movebytes(pbuf1, pbuf2, 26);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - got an error doing copy to set up test. Got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    perror = dg_movebytesskipdestination(pbuf2 + 3, pbuf2 + 1, 2);
    
    if (pbuf2[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - before destination changed\n");
    }

    if (pbuf2[1] != 'd')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - dest[0] incorrect\n");
    }

    if (pbuf2[2] != 'e')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - dest[1] incorrect\n");    
    }

    if (pbuf2[3] != 'd')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - src[0] changed\n");
    }
    
    if (pbuf2[4] != 'e')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - src[1] changed\n");
    }
    
    if (pbuf2[5] != 'f')
    {
        dg_printzerostring(
             &BHarrayhead,
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case no overlap source > destination - after source changed\n");
    }
    
    // success case overlap source starts in destination
      // initializing buf2
    perror = dg_movebytes(pbuf1, pbuf2, 26);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - got an error doing copy to set up test. Got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    perror = dg_movebytesskipdestination(pbuf2 + 2, pbuf2 + 1, 2);
    
    if (pbuf2[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - before destination changed\n");
    }
    
    if (pbuf2[1] != 'd')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - dest[0] incorrect\n");
    }
    
    if (pbuf2[2] != 'e')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - dest[1] incorrect\n");
    }
    
    if (pbuf2[3] != 'd')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - alternate src[0] changed\n");
    }
    
    if (pbuf2[4] != 'e')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - alternate src[1] changed\n");
    }
    
    if (pbuf2[5] != 'f')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts in destination - after alternate source changed\n");
    }
    
    // success case overlap source starts before destination
      // initializing buf2
    perror = dg_movebytes(pbuf1, pbuf2, 26);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - got an error doing copy to set up test. Got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    perror = dg_movebytesskipdestination(pbuf2 + 1, pbuf2 + 2, 2);
    
    if (pbuf2[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - before source changed\n");
    }
    
    if (pbuf2[1] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - src[0] incorrect\n");
    }
    
    if (pbuf2[2] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - dest[0] incorrect\n");
    }
    
    if (pbuf2[3] != 'e')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - dest[1] incorrect\n");
    }
    
    if (pbuf2[4] != 'e')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - alternate src[1] incorrect\n");
    }
    
    if (pbuf2[5] != 'f')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case overlap source starts before destination - after alternate source incorrect\n");
    }
    
    
    // success case 2 overlap source starts before destination
      // initializing buf2
    perror = dg_movebytes(pbuf1, pbuf2, 26);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead,  (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - got an error doing copy to set up test. Got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    perror = dg_movebytesskipdestination(pbuf2 + 1, pbuf2 + 3, 5);
    
    if (pbuf2[0] != 'a')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - before source changed\n");
    }
    
    if (pbuf2[1] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - src[0] incorrect\n");
    }
    
    if (pbuf2[2] != 'c')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - src[1] incorrect\n");
    }
    
    if (pbuf2[3] != 'b')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - dest[0] incorrect\n");
    }
    
    if (pbuf2[4] != 'c')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - dest[1] incorrect\n");
    }
    
    if (pbuf2[5] != 'i')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - dest[2] incorrect\n");
    }
    
    if (pbuf2[6] != 'j')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - dest[3] incorrect\n");
    }
    
    if (pbuf2[7] != 'k')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - dest[4] incorrect\n");
    }
    
    if (pbuf2[8] != 'i')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - alternate src[2] incorrect\n");
    }
    
    if (pbuf2[9] != 'j')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - alternate src[3] incorrect\n");
    }
    
    if (pbuf2[10] != 'k')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - alternate src[4] incorrect\n");
    }
    
    if (pbuf2[11] != 'l')
    {
        dg_printzerostring(
            &BHarrayhead,  
            (unsigned char*)"FAIL! dg_movebytesskipdestination success case 2 overlap source starts before destination - after alternate src incorrect\n");
    }

}

void testdg_hctwostore()
{
    printf("testing dg_hctwostore\n");

    UINT64 pud[2];
    unsigned char destbuf[64];
    const char* perror;

    pud[1] = 0x0000000000000000;
    pud[0] = 0x0000000000000032;

    destbuf[0] = 0x99;
    destbuf[1] = 0x86;

    perror = dg_hctwostore((unsigned char*)destbuf, pud);

    if (perror != dg_success)
    {
        printf("  dg_hctwostore(pdest, 0x00..99) fail! - got error %s", perror);
    }

    if ((destbuf[0] != 0x99) ||
        (destbuf[1] != 0x86))
    {
        printf("  dg_touleb128(pdest, 0x00..99) fail! - expected 0x35 86, instead got %02x %02x\n",
            destbuf[0],
            destbuf[1]);
    }

    pud[1] = 0x1000000000000000;
    pud[0] = 0x0000000000000033;

    destbuf[0] = 0x98;
    destbuf[1] = 0x86;

    perror = dg_hctwostore((unsigned char*)destbuf, pud);

    if (perror != dg_success)
    {
        printf("  dg_hctwostore(pdest, 0x10..98) fail! - got error %s", perror);
    }

    if ((destbuf[0] != 0x98) ||
        (destbuf[1] != 0x86))
    {
        printf("  dg_touleb128(pdest, 0x10..98) fail! - expected 0x35 86, instead got %02x %02x\n",
            destbuf[0],
            destbuf[1]);
    }

    pud[1] = 0x0100000000000000;
    pud[0] = 0x0000000000000035;

    destbuf[0] = 0;
    destbuf[1] = 0x86;

    perror = dg_hctwostore((unsigned char*)destbuf, pud);

    if (perror != dg_success)
    {
        printf("  dg_hctwostore(pdest, 0x01..35) fail! - got error %s", perror);
    }

    if ((destbuf[0] != 0x35) ||
        (destbuf[1] != 0x86))
    {
        printf("  dg_touleb128(pdest, 0x01..35) fail! - expected 0x35 86, instead got %02x %02x\n",
            destbuf[0],
            destbuf[1]);
    }

    pud[1] = 0x0200000000000000;
    pud[0] = 0x0000000000004135;

    destbuf[0] = 0;
    destbuf[1] = 0;
    destbuf[2] = 0x98;

    perror = dg_hctwostore((unsigned char*)destbuf, pud);

    if (perror != dg_success)
    {
        printf("  dg_hctwostore(pdest, 0x02..4135) fail! - got error %s", perror);
    }

    if ((destbuf[0] != 0x35) ||
        (destbuf[1] != 0x41) ||
        (destbuf[2] != 0x98))
    {
        printf("  dg_touleb128(pdest, 0x02..4135 98) fail! - expected 0x4135, instead got %02x %02x %02x\n",
            destbuf[0],
            destbuf[1],
            destbuf[2]);
    }

    pud[1] = 0x0400000000000000;
    pud[0] = 0x0000000060514436;

    destbuf[0] = 0;
    destbuf[1] = 0;
    destbuf[2] = 0;
    destbuf[3] = 0;
    destbuf[4] = 0x76;

    perror = dg_hctwostore((unsigned char*)destbuf, pud);

    if (perror != dg_success)
    {
        printf("  dg_hctwostore(pdest, 0x04..60514436) fail! - got error %s", perror);
    }

    if ((destbuf[0] != 0x36) ||
        (destbuf[1] != 0x44) ||
        (destbuf[2] != 0x51) ||
        (destbuf[3] != 0x60) ||
        (destbuf[4] != 0x76))
    {
        printf("  dg_touleb128(pdest, 0x04..60514436 76) fail! - expected 0x60514436, instead got %02x %02x %02x %02x %02x\n",
            destbuf[0],
            destbuf[1],
            destbuf[2],
            destbuf[3],
            destbuf[4]);
    }

    pud[1] = 0x0800000000000000;
    pud[0] = 0x9897969561524537;

    destbuf[0] = 0;
    destbuf[1] = 0;
    destbuf[2] = 0;
    destbuf[3] = 0;
    destbuf[4] = 0;
    destbuf[5] = 0;
    destbuf[6] = 0;
    destbuf[7] = 0;
    destbuf[8] = 0x77;

    perror = dg_hctwostore((unsigned char*)destbuf, pud);

    if (perror != dg_success)
    {
        printf("  dg_hctwostore(pdest, 0x08..9897969561524537) fail! - got error %s", perror);
    }

    if ((destbuf[0] != 0x37) ||
        (destbuf[1] != 0x45) ||
        (destbuf[2] != 0x52) ||
        (destbuf[3] != 0x61) ||
        (destbuf[4] != 0x95) ||
        (destbuf[5] != 0x96) ||
        (destbuf[6] != 0x97) ||
        (destbuf[7] != 0x98) ||
        (destbuf[8] != 0x77))
    {
        printf("  dg_touleb128(pdest, 0x08..9897969561524537 77) fail! - expected 0x4135, instead got %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
            destbuf[0],
            destbuf[1],
            destbuf[2],
            destbuf[3],
            destbuf[4],
            destbuf[5],
            destbuf[6],
            destbuf[7],
            destbuf[8]);
    }

    pud[1] = 0x0F7F6E5D4C3B2A19;
    pud[0] = 0x0817263544536271;

    destbuf[0] = 0;
    destbuf[1] = 0;
    destbuf[2] = 0;
    destbuf[3] = 0;
    destbuf[4] = 0;
    destbuf[5] = 0;
    destbuf[6] = 0;
    destbuf[7] = 0;
    destbuf[8] = 0;
    destbuf[9] = 0;
    destbuf[0x0A] = 0;
    destbuf[0x0B] = 0;
    destbuf[0x0C] = 0;
    destbuf[0x0D] = 0;
    destbuf[0x0E] = 0;
    destbuf[0x0F] = 0x77;

    perror = dg_hctwostore((unsigned char*)destbuf, pud);

    if (perror != dg_success)
    {
        printf("  dg_hctwostore(pdest, 0x0F..7F 77) fail! - got error %s", perror);
    }

    if ((destbuf[0] != 0x71) ||
        (destbuf[1] != 0x62) ||
        (destbuf[2] != 0x53) ||
        (destbuf[3] != 0x44) ||
        (destbuf[4] != 0x35) ||
        (destbuf[5] != 0x26) ||
        (destbuf[6] != 0x17) ||
        (destbuf[7] != 0x08) ||
        (destbuf[8] != 0x19) ||
        (destbuf[9] != 0x2A) ||
        (destbuf[0x0A] != 0x3B) ||
        (destbuf[0x0B] != 0x4C) ||
        (destbuf[0x0C] != 0x5D) ||
        (destbuf[0x0D] != 0x6E) ||
        (destbuf[0x0E] != 0x7F) ||
        (destbuf[0x0F] != 0x77))
    {
        printf("  dg_touleb128(pdest, 0x0F..7F 77) fail! - expected 0x4135, instead got %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x %02x\n",
            destbuf[0],
            destbuf[1],
            destbuf[2],
            destbuf[3],
            destbuf[4],
            destbuf[5],
            destbuf[6],
            destbuf[7],
            destbuf[8],
            destbuf[9],
            destbuf[0x0A],
            destbuf[0x0B],
            destbuf[0x0C],
            destbuf[0x0D],
            destbuf[0x0E],
            destbuf[0x0F]);
    }
}


void testdg_gethctwolength()
{
    printf("testing dg_gethctwolength\n");

    UINT64 pud[2];
    UINT64 x;

    pud[1] = 0x0700000000000000;
    pud[0] = 0x0000000000000032;

    x = dg_gethctwolength(pud);

    if (x != 7)
    {
        printf("  dg_gethctwolength - expected 7, instead got %08x\n",
            (UINT32)x);
    }
}


void testdg_search2()
{
    UINT64 u1;
    UINT64 u2;
    unsigned char* caddr1;
    unsigned char* caddr2; 
    unsigned char* caddrout;
    const char* pError;
    
    Bufferhandle BHarrayhead;
    
    dg_initpbharrayhead(&BHarrayhead);
    dg_printzerostring(&BHarrayhead,  (unsigned char*)"testing dg_search again\n");
    
    // success case
    caddr1 = (unsigned char*)"abcdefghijklmnopqrstuvwxyz";
    u1 = 26;
    caddr2 = (unsigned char*)"defg";
    u2 = 4;
    caddrout = NULL;
    
    pError = dg_search(caddr1, u1, caddr2, u2, &caddrout);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search success case - got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");        
    }
    
    if (caddrout != caddr1 + 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search success case - got wrong caddrout \n");
    }
    
    // success case beginning
    caddr1 = (unsigned char*)"abcdefghijklmnopqrstuvwxyz";
    u1 = 26;
    caddr2 = (unsigned char*)"abcde";
    u2 = 5;
    caddrout = NULL;
    
    pError = dg_search(caddr1, u1, caddr2, u2, &caddrout);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search success case beginning - got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");        
    }
    
    if (caddrout != caddr1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search success case beginning - got wrong caddrout \n");
    }
    
    // success case end
    caddr1 = (unsigned char*)"abcdefghijklmnopqrstuvwxyz";
    u1 = 26;
    caddr2 = (unsigned char*)"xyz";
    u2 = 3;
    caddrout = NULL;
    
    pError = dg_search(caddr1, u1, caddr2, u2, &caddrout);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search success case end - got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");        
    }
    
    if (caddrout != caddr1 + 23)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search success case end - got wrong caddrout \n");
    }

    // success case length 1
    caddr1 = (unsigned char*)"abcdefghijklmnopqrstuvwxyz";
    u1 = 26;
    caddr2 = (unsigned char*)"w";
    u2 = 1;
    caddrout = NULL;
    
    pError = dg_search(caddr1, u1, caddr2, u2, &caddrout);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search success case length 1 - got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");        
    }
    
    if (caddrout != caddr1 + 22)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search success case length 1 - got wrong caddrout \n");
    }
    
    // success case w/ near matches
    caddr1 = (unsigned char*)"abcabcabcababcdabcdeabc";
    u1 = 26;
    caddr2 = (unsigned char*)"abcde";
    u2 = 5;
    caddrout = NULL;
    
    pError = dg_search(caddr1, u1, caddr2, u2, &caddrout);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search success case w/ near matches - got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");        
    }
    
    if (caddrout != caddr1 + 15)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search success case w/ near matches - got wrong caddrout \n");
    }

    // not found case
    caddr1 = (unsigned char*)"abcabcabcababcdabcdeabc";
    u1 = 26;
    caddr2 = (unsigned char*)"ef";
    u2 = 2;
    caddrout = NULL;
    
    pError = dg_search(caddr1, u1, caddr2, u2, &caddrout);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search not found case - got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");        
    }
    
    if (caddrout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search not found case - got wrong caddrout \n");
    }


    // too long case
    caddr1 = (unsigned char*)"abcdef";
    u1 = 5;
    caddr2 = (unsigned char*)"abcdef";
    u2 = 6;
    caddrout = NULL;
    
    pError = dg_search(caddr1, u1, caddr2, u2, &caddrout);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search too long case - got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");        
    }
    
    if (caddrout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search too long case - got wrong caddrout \n");
    }
    
    
    // exact match case
    caddr1 = (unsigned char*)"abcdef";
    u1 = 6;
    caddr2 = (unsigned char*)"abcdef";
    u2 = 6;
    caddrout = NULL;
    
    pError = dg_search(caddr1, u1, caddr2, u2, &caddrout);
    
    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search exact match case - got error ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");        
    }
    
    if (caddrout != caddr1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search exact match case - got wrong caddrout \n");
    }

    // badmemory match case
    caddr1 = (unsigned char*)"abcdef";
    u1 = 6;
    caddr2 = (unsigned char*)-1;
    u2 = 6;
    caddrout = NULL;
    
    pError = dg_search(caddr1, u1, caddr2, u2, &caddrout);
    
    if (pError != dg_badmemoryerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search exact match case - got wrong error, expected:\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)dg_badmemoryerror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"got:\n");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");        
    }
    
    if (caddrout != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL! dg_search exact match case - got wrong caddrout \n");
    }
}


void testdg_getenvironmentvariable()
{
    UINT64 flag, mylength;
    const char* perror;
    Bufferhandle myBHarrayhead;

    unsigned char destbuf[128];

    dg_initpbharrayhead(&myBHarrayhead);

    printf("testing dg_getenvironmentvariable and setting a test environment variable\n");

#ifdef DGLU_OS_WIN64

    flag = SetEnvironmentVariable(
        (LPCTSTR)"DG_MEOW",
        (LPCTSTR)"cat");

    if (0 == flag)
    {
        printf("  OS FAIL! could not do setenv to set test environment variable\n");
    }

#else

    flag = setenv((const char*)"DG_MEOW", (const char*)"cat", -1);

    if (0 != flag)
    {
        printf("  OS FAIL! could not do setenv to set test environment variable\n");
    }

#endif

    // success found dest buffer length 0 case    
    perror = dg_getenvironmentvariable(
        &myBHarrayhead,
        (const char*)"DG_MEOW", // pvarname,
        (unsigned char*)destbuf, // pbuf,
        0, // buflength,
        &mylength,
        dg_success); // const char* forceerrorflag);

    if (perror != dg_success)
    {
        printf("  FAIL! dg_getenvironmentvariable success found dest buffer 0 case - got an error %s\n", perror);
    }
    else
    {
        // printf("  dg_getenvironmentvariable succeeded for found with dest buffer 0 case\n");

        if (3 != mylength)
        {
            printf("   - FAIL! value length is not 3 got, %d\n", (UINT32)mylength);
        }
        // else
        // {
        //    printf("   - value length is 3 as it should be\n");
        // }
    }

    // success found dest buffer length too small case
    destbuf[0] = 0;

    perror = dg_getenvironmentvariable(
        &myBHarrayhead,
        (const char*)"DG_MEOW", // pvarname,
        (unsigned char*)destbuf, // pbuf,
        3, // buflength,
        &mylength,
        dg_success); // const char* forceerrorflag);

    if (perror != dg_success)
    {
        printf("  FAIL! dg_getenvironmentvariable success found dest buffer too small case - got an error %s\n", perror);
    }
    else
    {
        // printf("  dg_getenvironmentvariable succeeded for found with dest buffer too small case\n");

        if (3 != mylength)
        {
            printf("   - FAIL! value length is incorrect, should be 3, got %d\n", (UINT32)mylength);
        }
        else
        {
            // printf("   - value length is 3 as it should be\n");

            if (0 != destbuf[0])
            {
                printf("   - FAIL! destination was changed\n");
            }
            // else
            // {
            //    printf("   - destination not changed as it should be\n");
            // }
        }
    }

    // success found dest buffer big enough case
    destbuf[0] = 0;
    destbuf[1] = 1;
    destbuf[2] = 2;
    destbuf[3] = 4;

    perror = dg_getenvironmentvariable(
        &myBHarrayhead,
        (const char*)"DG_MEOW", // pvarname,
        (unsigned char*)destbuf, // pbuf,
        4, // buflength,
        &mylength,
        dg_success); // const char* forceerrorflag);

    if (perror != dg_success)
    {
        printf("  FAIL! dg_getenvironmentvariable success found dest buffer big enough case - got an error %s\n", perror);
    }
    else
    {
        // printf("  dg_getenvironmentvariable succeeded for found with dest buffer big enough case\n");

        if (3 != mylength)
        {
            printf("   - FAIL! value length not 3, got %d\n", (UINT32)mylength);
        }
        else
        {
            // printf("   - value length is 3 as it should be\n");

            if (('c' == destbuf[0]) &&
                ('a' == destbuf[1]) &&
                ('t' == destbuf[2]) &&
                (0 == destbuf[3]))
            {
                // printf("   - destination changed as it should be\n");
            }
            else
            {
                printf("   - FAIL! destination not changed\n");
            }
        }
    }

    // success not found case    
    perror = dg_getenvironmentvariable(
        &myBHarrayhead,
        (const char*)"dg_envvarnoexist", // pvarname,
        (unsigned char*)destbuf, // pbuf,
        0, // buflength,
        &mylength,
        dg_success); // const char* forceerrorflag);

    if (perror != dg_success)
    {
        printf("  FAIL! dg_getenvironmentvariable success not found case  - got an error %s\n", perror);
    }
    else
    {
        // printf("  dg_getenvironmentvariable succeeded for not found case \n");

        if ((UINT64)-1 != mylength)
        {
            printf("   - FAIL! value length should be -1 but it is not\n");
        }
        // else
        // {
        //     printf("   - value length is -1 as it should be\n");
        // }
    }
}


void testdg_addbytes()
{
    UINT64 i;
    unsigned char srcbuf[64];
    unsigned char destbuf[64];
    const char* perror;
    UINT64 carryout;

    printf("testing dg_addbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i;
        srcbuf[i] = 2*(UINT8)i + 1;
    }

    perror = dg_addbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_addbytes no carry case failed with error %s\n", perror);
    }
    
    if (carryout != 0)
    {
        printf("  dg_addbytes no carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 1)
    {
        printf("  dg_addbytes no carry case first byte added incorrect, expected 1, got %d\n", destbuf[0]);
    }

    if (destbuf[8] != 25)
    {
        printf("  dg_addbytes no carry case last byte added incorrect, expected 25, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 9)
    {
        printf("  dg_addbytes no carry case changed buffer after last character added! expected 19, got %d\n", destbuf[9]);
    }
    
    perror = dg_addbytes(
        (unsigned char*)-0x1001, 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_addbytes bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_addbytes(
        (unsigned char*)srcbuf, 
        (unsigned char*)-0x1001, 
        9,
        &carryout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_addbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_addbytes(
        (unsigned char*)srcbuf, 
        (unsigned char*)destbuf, 
        9,
        (UINT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_addbytes bad memory at pcarryout case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 0xff;
    }

    srcbuf[0] = 2;
    srcbuf[1] = 5;
    srcbuf[8] = 0xfe;
    destbuf[9] = 33;

    perror = dg_addbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_addbytes carry case failed with error %s\n", perror);
    }
    
    if (carryout != 1)
    {
        printf("  add bytes carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 0x1)
    {
        printf("  add bytes carry case first byte added incorrect, expected 1, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0x5)
    {
        printf("  add bytes carry case second byte added incorrect, expected 5, got %d\n", destbuf[1]);
    }

    if (destbuf[8] != 0xfe)
    {
        printf("  add bytes carry case last byte added incorrect, expected 0xfe, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 33)
    {
        printf("  dg_addbytes carry case changed buffer after last character moved! expected 33, got %d\n", destbuf[9]);
    }
}


void testdg_adcbytes()
{
    UINT64 i;
    unsigned char srcbuf[64];
    unsigned char destbuf[64];
    const char* perror;
    UINT64 carryinout = 0;

    printf("testing dg_adcbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i;
        srcbuf[i] = 2*(UINT8)i + 1;
    }

    perror = dg_adcbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        9,
        &carryinout);

    if (perror != dg_success)
    {
        printf("  dg_adcbytes no carry case failed with error %s\n", perror);
    }
    
    if (carryinout != 0)
    {
        printf("  dg_adcbytes no carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryinout);
    }

    if (destbuf[0] != 1)
    {
        printf("  dg_adcbytes no carry case first byte added incorrect, expected 1, got %d\n", destbuf[0]);
    }

    if (destbuf[8] != 25)
    {
        printf("  dg_adcbytes no carry case last byte added incorrect, expected 25, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 9)
    {
        printf("  dg_adcbytes no carry case changed buffer after last character added! expected 19, got %d\n", destbuf[9]);
    }
    
    carryinout = 0;
    perror = dg_adcbytes(
        (unsigned char*)-0x1001, 
        destbuf, 
        9,
        &carryinout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_adcbytes bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    carryinout = 0;
    perror = dg_adcbytes(
        (unsigned char*)srcbuf, 
        (unsigned char*)-0x1001, 
        9,
        &carryinout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_adcbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    carryinout = 0;
    perror = dg_adcbytes(
        (unsigned char*)srcbuf, 
        (unsigned char*)destbuf, 
        9,
        (UINT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_adcbytes bad memory at pcarryout case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 0xff;
    }

    srcbuf[0] = 2;
    srcbuf[1] = 5;
    srcbuf[8] = 0xfe;
    destbuf[9] = 33;
    carryinout = 1;

    perror = dg_adcbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        9,
        &carryinout);

    if (perror != dg_success)
    {
        printf("  dg_adcbytes carry case failed with error %s\n", perror);
    }
    
    if (carryinout != 1)
    {
        printf("  dg_adcbytes carry case carry out incorrect, expected 1, got %d\n", (UINT32)carryinout);
    }

    if (destbuf[0] != 0x2)
    {
        printf("  dg_adcbytes bytes carry case first byte added incorrect, expected 2, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0x5)
    {
        printf("  dg_adcbytes bytes carry case second byte added incorrect, expected 5, got %d\n", destbuf[1]);
    }

    if (destbuf[8] != 0xfe)
    {
        printf("  dg_adcbytes bytes carry case last byte added incorrect, expected 0xfe, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 33)
    {
        printf("  dg_adcbytes carry case changed buffer after last character moved! expected 33, got %d\n", destbuf[9]);
    }
    
    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 0xff;
    }

    srcbuf[0] = 2;
    srcbuf[1] = 5;
    srcbuf[8] = 0xfe;
    destbuf[9] = 33;
    carryinout = 1;

    perror = dg_adcbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        0,
        &carryinout);

    if (perror != dg_success)
    {
        printf("  dg_adcbytes length 0 case failed with error %s\n", perror);
    }
    
    if (carryinout != 0)
    {
        printf("  dg_adcbytes length 0 case carry out incorrect, expected 1, got %d\n", (UINT32)carryinout);
    }

    if (destbuf[0] != 0xff)
    {
        printf("  dg_adcbytes bytes length 0 case first byte added incorrect, expected 255, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0xff)
    {
        printf("  dg_adcbytes bytes length 0 case second byte added incorrect, expected 255, got %d\n", destbuf[1]);
    }

    if (destbuf[8] != 0xff)
    {
        printf("  dg_adcbytes bytes length 0 case last byte added incorrect, expected 255, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 33)
    {
        printf("  dg_adcbytes carry length 0 changed buffer after last character moved! expected 33, got %d\n", destbuf[9]);
    }
}


void testdg_sbbbytes()
{
    UINT64 i;
    unsigned char srcbuf[64];
    unsigned char destbuf[64];
    const char* perror;
    UINT64 carryinout = 0;

    printf("testing dg_sbbbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 2*(UINT8)i + 1;
        srcbuf[i] = (UINT8)i;
    }

    perror = dg_sbbbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        9,
        &carryinout);

    if (perror != dg_success)
    {
        printf("  dg_sbbbytes no borrow case failed with error %s\n", perror);
    }
    
    if (carryinout != 0)
    {
        printf("  dg_sbbbytes no borrow case carry out incorrect, expected 0, got %d\n", (UINT32)carryinout);
    }
    
    if (srcbuf[1] != 1)
    {
        printf("  dg_sbbbytes no borrow case src[1] changed, expected 1, got %d\n", srcbuf[0]);
    }

    if (destbuf[0] != 1)
    {
        printf("  dg_sbbbytes no borrow case first byte added incorrect, expected 1, got %d\n", destbuf[0]);
    }

    if (destbuf[8] != 9)
    {
        printf("  dg_sbbbytes no borrow case last byte added incorrect, expected 9, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 19)
    {
        printf("  dg_sbbbytes no borrow case buffer after last character changed! expected 19, got %d\n", destbuf[9]);
    }
    
    carryinout = 0;
    perror = dg_sbbbytes(
        (unsigned char*)-0x1001, 
        destbuf, 
        9,
        &carryinout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_sbbbytes bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    carryinout = 0;
    perror = dg_sbbbytes(
        (unsigned char*)srcbuf, 
        (unsigned char*)-0x1001, 
        9,
        &carryinout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_sbbbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    carryinout = 0;
    perror = dg_sbbbytes(
        (unsigned char*)srcbuf, 
        (unsigned char*)destbuf, 
        9,
        (UINT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_sbbbytes bad memory at pcarryout case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    for (i = 0; i < 20; i++)
    {
        srcbuf[i] = 0xff;
    }

    destbuf[0] = 2;
    destbuf[1] = 5;
    destbuf[8] = 0xfe;
    destbuf[9] = 33;
    carryinout = 1;

    perror = dg_sbbbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        9,
        &carryinout);

    if (perror != dg_success)
    {
        printf("  dg_sbbbytes borrow case failed with error %s\n", perror);
    }
    
    if (carryinout != 1)
    {
        printf("  dg_sbbbytes borrow case carry out incorrect, expected 1, got %d\n", (UINT32)carryinout);
    }

    if (destbuf[0] != 0x2)
    {
        printf("  dg_sbbbytes borrow case first byte added incorrect, expected 2, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0x5)
    {
        printf("  dg_sbbbytes borrow case second byte added incorrect, expected 5, got %d\n", destbuf[1]);
    }

    if (destbuf[8] != 0xfe)
    {
        printf("  dg_sbbbytes borrow case last byte added incorrect, expected 0xfe, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 33)
    {
        printf("  dg_sbbbytes borrow case buffer after last character changed! expected 33, got %d\n", destbuf[9]);
    }
    
    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 0xff;
    }

    srcbuf[0] = 2;
    srcbuf[1] = 5;
    srcbuf[8] = 0xfe;
    destbuf[9] = 33;
    carryinout = 1;

    perror = dg_sbbbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        0,
        &carryinout);

    if (perror != dg_success)
    {
        printf("  dg_sbbbytes length 0 case failed with error %s\n", perror);
    }
    
    if (carryinout != 0)
    {
        printf("  dg_sbbbytes length 0 case carry out incorrect, expected 1, got %d\n", (UINT32)carryinout);
    }

    if (destbuf[0] != 0xff)
    {
        printf("  dg_sbbbytes bytes length 0 case first byte added incorrect, expected 255, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0xff)
    {
        printf("  dg_sbbbytes bytes length 0 case second byte added incorrect, expected 255, got %d\n", destbuf[1]);
    }

    if (destbuf[8] != 0xff)
    {
        printf("  dg_sbbbytes bytes length 0 case last byte added incorrect, expected 255, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 33)
    {
        printf("  dg_sbbbytes carry length 0 changed buffer after last character moved! expected 33, got %d\n", destbuf[9]);
    }
}


void testdg_shlbytes()
{
    UINT64 i;
    unsigned char destbuf[64];
    const char* perror;
    UINT64 carryout;

    printf("testing dg_shlbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i + 2;
    }

    perror = dg_shlbytes( 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_shlbytes no carry case failed with error %s\n", perror);
    }
    
    if (carryout !=0)
    {
        printf("  dg_shlbytes no carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 4)
    {
        printf("  dg_shlbytes no carry case first byte added incorrect, expected 4, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 6)
    {
        printf("  dg_shlbytes no carry case second byte added incorrect, expected 6, got %d\n", destbuf[1]);
    }

    if (destbuf[8] != 20)
    {
        printf("  dg_shlbytes no carry case last byte added incorrect, expected 20, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 11)
    {
        printf("  dg_shlbytes no carry case changed buffer after last character added! expected 11, got %d\n", destbuf[9]);
    }
    
    perror = dg_shlbytes( 
        (unsigned char*)-0x1001, 
        9,
        &carryout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_shlbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_shlbytes(
        (unsigned char*)destbuf, 
        9,
        (UINT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_shlbytes bad memory at pcarryout case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 0xfe - i;
    }

    destbuf[9] = 33;

    perror = dg_shlbytes( 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_shlbytes carry case failed with error %s\n", perror);
    }
    
    if (carryout != 1)
    {
        printf("  dg_shlbytes bytes carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 0xfc)
    {
        printf("  dg_shlbytes bytes carry case first byte added incorrect, expected 0xfc, got %x\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0xfb)
    {
        printf("  dg_shlbytes bytes carry case second byte added incorrect, expected 0xfb, got %x\n", destbuf[1]);
    }

    if (destbuf[8] != 0xed)
    {
        printf("  dg_shlbytes bytes carry case last byte added incorrect, expected 0xed, got %x\n", destbuf[8]);
    }

    if (destbuf[9] != 33)
    {
        printf("  dg_shlbytes carry case changed buffer after last character moved! expected 33, got %d\n", destbuf[9]);
    }
}


void testdg_rclbytes()
{
    UINT64 i;
    unsigned char destbuf[64];
    const char* perror;
    UINT64 carryinout;

    printf("testing dg_rclbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i + 2;
    }
    
    carryinout = 0;

    perror = dg_rclbytes( 
        destbuf, 
        9,
        &carryinout);

    if (perror != dg_success)
    {
        printf("  dg_rclbytes no carry case failed with error %s\n", perror);
    }
    
    if (carryinout !=0)
    {
        printf("  dg_rclbytes no carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryinout);
    }

    if (destbuf[0] != 4)
    {
        printf("  dg_rclbytes no carry case first byte added incorrect, expected 4, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 6)
    {
        printf("  dg_rclbytes no carry case second byte added incorrect, expected 6, got %d\n", destbuf[1]);
    }

    if (destbuf[8] != 20)
    {
        printf("  dg_rclbytes no carry case last byte added incorrect, expected 20, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 11)
    {
        printf("  dg_rclbytes no carry case changed buffer after last character added! expected 11, got %d\n", destbuf[9]);
    }
    
    perror = dg_rclbytes( 
        (unsigned char*)-0x1001, 
        9,
        &carryinout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_rclbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_rclbytes(
        (unsigned char*)destbuf, 
        9,
        (UINT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_rclbytes bad memory at pcarryout case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 0xfe - i;
    }

    destbuf[9] = 33;

    carryinout = 1;
    
    perror = dg_rclbytes( 
        destbuf, 
        9,
        &carryinout);

    if (perror != dg_success)
    {
        printf("  dg_rclbytes carry case failed with error %s\n", perror);
    }
    
    if (carryinout != 1)
    {
        printf("  dg_rclbytes bytes carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryinout);
    }

    if (destbuf[0] != 0xfd)
    {
        printf("  dg_rclbytes bytes carry case first byte added incorrect, expected 0xfd, got %x\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0xfb)
    {
        printf("  dg_rclbytes bytes carry case second byte added incorrect, expected 0xfb, got %x\n", destbuf[1]);
    }

    if (destbuf[8] != 0xed)
    {
        printf("  dg_rclbytes bytes carry case last byte added incorrect, expected 0xed, got %x\n", destbuf[8]);
    }

    if (destbuf[9] != 33)
    {
        printf("  dg_rclbytes carry case changed buffer after last character moved! expected 33, got %d\n", destbuf[9]);
    }
}


void testdg_shrbytes()
{
    UINT64 i;
    unsigned char destbuf[64];
    const char* perror;
    UINT64 carryout;

    printf("testing dg_shrbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 2*((UINT8)i + 1);
    }

    perror = dg_shrbytes( 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_shrbytes no carry case failed with error %s\n", perror);
    }
    
    if (carryout !=0)
    {
        printf("  dg_shrbytes no carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 1)
    {
        printf("  dg_shrbytes no carry case first byte incorrect, expected 1, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 2)
    {
        printf("  dg_shrbytes no carry case second byte incorrect, expected 2, got %d\n", destbuf[1]);
    }

    if (destbuf[8] != 9)
    {
        printf("  dg_shrbytes no carry case last byte incorrect, expected 9, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 20)
    {
        printf("  dg_shrbytes no carry case changed buffer after last character added! expected 20, got %d\n", destbuf[9]);
    }
    
    perror = dg_shrbytes( 
        (unsigned char*)-0x1001, 
        9,
        &carryout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_shrbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_shrbytes(
        (unsigned char*)destbuf, 
        9,
        (UINT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_shrbytes bad memory at pcarryout case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 0xff - i; // ff fe fd fc fb fa f9 f8 f7 33
                               //  00 f7f8f9fafbfcfdfeff -> 7b fc 7c fd 7d fe 7e ff 7f 33
    }

    destbuf[9] = 33;

    perror = dg_shrbytes( 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_shrbytes carry case failed with error %s\n", perror);
    }
    
    if (carryout != 1)
    {
        printf("  dg_shrbytes bytes carry case carry out incorrect, expected 1, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 0x7f)
    {
        printf("  dg_shrbytes bytes carry case first byte incorrect, expected 0x7f, got %x\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0xff)
    {
        printf("  dg_shrbytes bytes carry case second byte incorrect, expected 0xff, got %x\n", destbuf[1]);
    }

    if (destbuf[8] != 0x7b)
    {
        printf("  dg_shrbytes bytes carry case last byte incorrect, expected 0x7b, got %x\n", destbuf[8]);
    }

    if (destbuf[9] != 33)
    {
        printf("  dg_shrbytes carry case changed buffer after last character moved! expected 33, got %d\n", destbuf[9]);
    }
}


void testdg_sarbytes()
{
    UINT64 i;
    unsigned char destbuf[64];
    const char* perror;
    UINT64 carryout;

    printf("testing dg_sarbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 2*((UINT8)i + 1);
    }

    perror = dg_sarbytes( 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_sarbytes no carry case failed with error %s\n", perror);
    }
    
    if (carryout !=0)
    {
        printf("  dg_sarbytes no carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 1)
    {
        printf("  dg_sarbytes no carry case first byte incorrect, expected 1, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 2)
    {
        printf("  dg_sarbytes no carry case second byte incorrect, expected 2, got %d\n", destbuf[1]);
    }

    if (destbuf[8] != 9)
    {
        printf("  dg_sarbytes no carry case last byte incorrect, expected 9, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 20)
    {
        printf("  dg_sarbytes no carry case changed buffer after last character added! expected 20, got %d\n", destbuf[9]);
    }
    
    perror = dg_sarbytes( 
        (unsigned char*)-0x1001, 
        9,
        &carryout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_sarbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_sarbytes(
        (unsigned char*)destbuf, 
        9,
        (UINT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_sarbytes bad memory at pcarryout case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 0xff - i; // ff fe fd fc fb fa f9 f8 f7 33
                               //  00 f7f8f9fafbfcfdfeff -> 7b fc 7c fd 7d fe 7e ff 7f 33
    }

    destbuf[9] = 33;

    perror = dg_sarbytes( 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_sarbytes carry case failed with error %s\n", perror);
    }
    
    if (carryout != 1)
    {
        printf("  dg_sarbytes bytes carry case carry out incorrect, expected 1, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 0x7f)
    {
        printf("  dg_sarbytes bytes carry case first byte incorrect, expected 0x7f, got %x\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0xff)
    {
        printf("  dg_sarbytes bytes carry case second byte incorrect, expected 0xff, got %x\n", destbuf[1]);
    }

    if (destbuf[8] != 0xfb)
    {
        printf("  dg_sarbytes bytes carry case last byte incorrect, expected 0xfb, got %x\n", destbuf[8]);
    }

    if (destbuf[9] != 33)
    {
        printf("  dg_sarbytes carry case changed buffer after last character moved! expected 33, got %d\n", destbuf[9]);
    }
}


void testdg_rcrbytes()
{
    UINT64 i;
    unsigned char destbuf[64];
    const char* perror;
    UINT64 carryinout;

    printf("testing dg_rcrbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 2*((UINT8)i + 1);
    }
    
    carryinout = 0;

    perror = dg_rcrbytes( 
        destbuf, 
        9,
        &carryinout);

    if (perror != dg_success)
    {
        printf("  dg_rcrbytes no carry case failed with error %s\n", perror);
    }
    
    if (carryinout !=0)
    {
        printf("  dg_rcrbytes no carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryinout);
    }

    if (destbuf[0] != 1)
    {
        printf("  dg_rcrbytes no carry case first byte incorrect, expected 1, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 2)
    {
        printf("  dg_rcrbytes no carry case second byte incorrect, expected 2, got %d\n", destbuf[1]);
    }

    if (destbuf[8] != 9)
    {
        printf("  dg_rcrbytes no carry case last byte incorrect, expected 9, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 20)
    {
        printf("  dg_rcrbytes no carry case changed buffer after last character added! expected 20, got %d\n", destbuf[9]);
    }
    
    perror = dg_rcrbytes( 
        (unsigned char*)-0x1001, 
        9,
        &carryinout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_rcrbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_rcrbytes(
        (unsigned char*)destbuf, 
        9,
        (UINT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_rcrbytes bad memory at pcarryout case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 0xff - i; // ff fe fd fc fb fa f9 f8 f7 33
                               //  00 f7f8f9fafbfcfdfeff -> 7b fc 7c fd 7d fe 7e ff 7f 33
    }

    destbuf[9] = 33;
    
    carryinout = 1;

    perror = dg_rcrbytes( 
        destbuf, 
        9,
        &carryinout);

    if (perror != dg_success)
    {
        printf("  dg_rcrbytes carry case failed with error %s\n", perror);
    }
    
    if (carryinout != 1)
    {
        printf("  dg_rcrbytes bytes carry case carry out incorrect, expected 1, got %d\n", (UINT32)carryinout);
    }

    if (destbuf[0] != 0x7f)
    {
        printf("  dg_rcrbytes bytes carry case first byte incorrect, expected 0x7f, got %x\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0xff)
    {
        printf("  dg_rcrbytes bytes carry case second byte incorrect, expected 0xff, got %x\n", destbuf[1]);
    }

    if (destbuf[8] != 0xfb)
    {
        printf("  dg_rcrbytes bytes carry case last byte incorrect, expected 0xfb, got %x\n", destbuf[8]);
    }

    if (destbuf[9] != 33)
    {
        printf("  dg_rcrbytes carry case changed buffer after last character moved! expected 33, got %d\n", destbuf[9]);
    }
}


void testdg_notbytes()
{
    UINT64 i;
    unsigned char destbuf[64];
    const char* perror;

    printf("testing dg_notbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i + 2;
    }

    perror = dg_notbytes( 
        destbuf, 
        9);

    if (perror != dg_success)
    {
        printf("  dg_notbytes success case failed with error %s\n", perror);
    }

    if (destbuf[0] != 0xfd)
    {
        printf("  dg_notbytes success case first byte added incorrect, expected 0xfd, got %x\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0xfc)
    {
        printf("  dg_notbytes success case second byte added incorrect, expected 0xfe, got %x\n", destbuf[1]);
    }

    if (destbuf[8] != 0xf5)
    {
        printf("  dg_notbytes success case last byte added incorrect, expected 0xf5, got %x\n", destbuf[8]);
    }

    if (destbuf[9] != 11)
    {
        printf("  dg_notbytes success case buffer changed after last character! expected 11, got %d\n", destbuf[9]);
    }
    
    perror = dg_notbytes( 
        (unsigned char*)-0x1001, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_notbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_andbytes()
{
    UINT64 i;
    unsigned char srcbuf[64];
    unsigned char destbuf[64];
    const char* perror;

    printf("testing dg_andbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i;
        srcbuf[i] = 2*(UINT8)i + 1;
    }

    perror = dg_andbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        9);

    if (perror != dg_success)
    {
        printf("  dg_andbytes success case failed with error %s\n", perror);
    }

    if (destbuf[0] != 0)
    {
        printf("- FAIL!  dg_andbytes success case first byte incorrect, expected 0, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 1)
    {
        printf("- FAIL!  dg_andbytes success case second byte incorrect, expected 1, got %d\n", destbuf[1]);
    }
    
    if (destbuf[2] != 0)
    {
        printf("- FAIL!  dg_andbytes success case third byte incorrect, expected 0, got %d\n", destbuf[2]);
    }
    
    if (destbuf[3] != 3)
    {
        printf("- FAIL!  dg_andbytes success case fourth byte incorrect, expected 3, got %d\n", destbuf[3]);
    }
    
    if (destbuf[4] != 0)
    {
        printf("- FAIL!  dg_andbytes success case fifth byte incorrect, expected 0, got %d\n", destbuf[3]);
    }

    if (destbuf[8] != 0)
    {
        printf("- FAIL!  dg_andbytes success case last byte incorrect, expected 0, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 9)
    {
        printf("- FAIL! dg_andbytes success case buffer changed after last character added! expected 9, got %d\n", destbuf[9]);
    }
    
    perror = dg_andbytes(
        (unsigned char*)-0x1001, 
        destbuf, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_andbytes bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_andbytes(
        (unsigned char*)srcbuf, 
        (unsigned char*)-0x1001, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_addbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_orbytes()
{
    UINT64 i;
    unsigned char srcbuf[64];
    unsigned char destbuf[64];
    const char* perror;

    printf("testing dg_orbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i;
        srcbuf[i] = 2*(UINT8)i + 1;
    }

    perror = dg_orbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        9);

    if (perror != dg_success)
    {
        printf("  dg_orbytes success case failed with error %s\n", perror);
    }

    if (destbuf[0] != 1)
    {
        printf("- FAIL!  dg_orbytes success case first byte incorrect, expected 1, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 3)
    {
        printf("- FAIL!  dg_orbytes success case second byte incorrect, expected 3, got %d\n", destbuf[1]);
    }
    
    if (destbuf[2] != 7)
    {
        printf("- FAIL!  dg_orbytes success case third byte incorrect, expected 7, got %d\n", destbuf[2]);
    }
    
    if (destbuf[3] != 7)
    {
        printf("- FAIL!  dg_orbytes success case fourth byte incorrect, expected 7, got %d\n", destbuf[3]);
    }
    
    if (destbuf[4] != 13)
    {
        printf("- FAIL!  dg_orbytes success case fifth byte incorrect, expected 13, got %d\n", destbuf[3]);
    }

    if (destbuf[8] != 25)
    {
        printf("- FAIL!  dg_orbytes success case last byte incorrect, expected 25, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 9)
    {
        printf("- FAIL! dg_orbytes success case buffer changed after last character added! expected 9, got %d\n", destbuf[9]);
    }
    
    perror = dg_orbytes(
        (unsigned char*)-0x1001, 
        destbuf, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_orbytes bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_orbytes(
        (unsigned char*)srcbuf, 
        (unsigned char*)-0x1001, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_orbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_xorbytes()
{
    UINT64 i;
    unsigned char srcbuf[64];
    unsigned char destbuf[64];
    const char* perror;

    printf("testing dg_xorbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i;
        srcbuf[i] = 2*(UINT8)i + 1;
    }

    perror = dg_xorbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        9);

    if (perror != dg_success)
    {
        printf("  dg_xorbytes success case failed with error %s\n", perror);
    }

    if (destbuf[0] != 1)
    {
        printf("- FAIL!  dg_xorbytes success case first byte incorrect, expected 1, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 2)
    {
        printf("- FAIL!  dg_xorbytes success case second byte incorrect, expected 2, got %d\n", destbuf[1]);
    }
    
    if (destbuf[2] != 7)
    {
        printf("- FAIL!  dg_xorbytes success case third byte incorrect, expected 7, got %d\n", destbuf[2]);
    }
    
    if (destbuf[3] != 4)
    {
        printf("- FAIL!  dg_xorbytes success case fourth byte incorrect, expected 4, got %d\n", destbuf[3]);
    }
    
    if (destbuf[4] != 14)
    {
        printf("- FAIL!  dg_xorbytes success case fifth byte incorrect, expected 14, got %d\n", destbuf[3]);
    }

    if (destbuf[8] != 25)
    {
        printf("- FAIL!  dg_xorbytes success case last byte incorrect, expected 25, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 9)
    {
        printf("- FAIL! dg_xorbytes success case buffer changed after last character added! expected 9, got %d\n", destbuf[9]);
    }
    
    perror = dg_xorbytes(
        (unsigned char*)-0x1001, 
        destbuf, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_xorbytes bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_xorbytes(
        (unsigned char*)srcbuf, 
        (unsigned char*)-0x1001, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_xorbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_nandbytes()
{
    UINT64 i;
    unsigned char srcbuf[64];
    unsigned char destbuf[64];
    const char* perror;

    printf("testing dg_nandbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i;
        srcbuf[i] = 2*(UINT8)i + 1;
    }

    perror = dg_nandbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        9);

    if (perror != dg_success)
    {
        printf("  dg_nandbytes success case failed with error %s\n", perror);
    }

    if (destbuf[0] != 0xff)
    {
        printf("- FAIL!  dg_nandbytes success case first byte incorrect, expected 0xff, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0xfe)
    {
        printf("- FAIL!  dg_nandbytes success case second byte incorrect, expected 0xfe, got %d\n", destbuf[1]);
    }
    
    if (destbuf[2] != 0xff)
    {
        printf("- FAIL!  dg_nandbytes success case third byte incorrect, expected 0xff, got %d\n", destbuf[2]);
    }
    
    if (destbuf[3] != 0xfc)
    {
        printf("- FAIL!  dg_nandbytes success case fourth byte incorrect, expected 0xfc, got %d\n", destbuf[3]);
    }
    
    if (destbuf[4] != 0xff)
    {
        printf("- FAIL!  dg_nandbytes success case fifth byte incorrect, expected 0xff, got %d\n", destbuf[3]);
    }

    if (destbuf[8] != 0xff)
    {
        printf("- FAIL!  dg_nandbytes success case last byte incorrect, expected 0xff, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 9)
    {
        printf("- FAIL! dg_nandbytes success case buffer changed after last character added! expected 9, got %d\n", destbuf[9]);
    }
    
    perror = dg_nandbytes(
        (unsigned char*)-0x1001, 
        destbuf, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_nandbytes bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_nandbytes(
        (unsigned char*)srcbuf, 
        (unsigned char*)-0x1001, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_nandbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_norbytes()
{
    UINT64 i;
    unsigned char srcbuf[64];
    unsigned char destbuf[64];
    const char* perror;

    printf("testing dg_norbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i;
        srcbuf[i] = 2*(UINT8)i + 1;
    }

    perror = dg_norbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        9);

    if (perror != dg_success)
    {
        printf("  dg_norbytes success case failed with error %s\n", perror);
    }

    if (destbuf[0] != 0xfe)
    {
        printf("- FAIL!  dg_norbytes success case first byte incorrect, expected 0xfe, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0xfc)
    {
        printf("- FAIL!  dg_norbytes success case second byte incorrect, expected 0xfc, got %d\n", destbuf[1]);
    }
    
    if (destbuf[2] != 0xf8)
    {
        printf("- FAIL!  dg_norbytes success case third byte incorrect, expected 0xf8, got %d\n", destbuf[2]);
    }
    
    if (destbuf[3] != 0xf8)
    {
        printf("- FAIL!  dg_norbytes success case fourth byte incorrect, expected 0xf8, got %d\n", destbuf[3]);
    }
    
    if (destbuf[4] != 0xf2) // !0x0D
    {
        printf("- FAIL!  dg_norbytes success case fifth byte incorrect, expected 0xf2, got %d\n", destbuf[3]);
    }

    if (destbuf[8] != 0xE6) // !0x19
    {
        printf("- FAIL!  dg_norbytes success case last byte incorrect, expected 0xE6, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 9)
    {
        printf("- FAIL! dg_norbytes success case buffer changed after last character added! expected 9, got %d\n", destbuf[9]);
    }
    
    perror = dg_norbytes(
        (unsigned char*)-0x1001, 
        destbuf, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_norbytes bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_norbytes(
        (unsigned char*)srcbuf, 
        (unsigned char*)-0x1001, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_norbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_xnorbytes()
{
    UINT64 i;
    unsigned char srcbuf[64];
    unsigned char destbuf[64];
    const char* perror;

    printf("testing dg_xnorbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i;
        srcbuf[i] = 2*(UINT8)i + 1;
    }

    perror = dg_xnorbytes(
        (unsigned char*)srcbuf, 
        destbuf, 
        9);

    if (perror != dg_success)
    {
        printf("  dg_xnorbytes success case failed with error %s\n", perror);
    }

    if (destbuf[0] != 0xfe)
    {
        printf("- FAIL!  dg_xnorbytes success case first byte incorrect, expected 0xfe, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0xfd)
    {
        printf("- FAIL!  dg_xnorbytes success case second byte incorrect, expected 0xfd, got %d\n", destbuf[1]);
    }
    
    if (destbuf[2] != 0xf8)
    {
        printf("- FAIL!  dg_xnorbytes success case third byte incorrect, expected 0xf8, got %d\n", destbuf[2]);
    }
    
    if (destbuf[3] != 0xfb)
    {
        printf("- FAIL!  dg_xnorbytes success case fourth byte incorrect, expected 0xfb, got %d\n", destbuf[3]);
    }
    
    if (destbuf[4] != 0xf2) // !(4 | 9) !0x0d
    {
        printf("- FAIL!  dg_xnorbytes success case fifth byte incorrect, expected 0xf2, got %d\n", destbuf[3]);
    }

    if (destbuf[8] != 0xE6) // !0x19
    {
        printf("- FAIL!  dg_xnorbytes success case last byte incorrect, expected 0xE6, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 9)
    {
        printf("- FAIL! dg_xnorbytes success case buffer changed after last character added! expected 9, got %d\n", destbuf[9]);
    }
    
    perror = dg_xnorbytes(
        (unsigned char*)-0x1001, 
        destbuf, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_xnorbytes bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_xnorbytes(
        (unsigned char*)srcbuf, 
        (unsigned char*)-0x1001, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_xnorbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
}

void testdg_reversebytes()
{
    UINT64 i;
    unsigned char destbuf[64];
    const char* perror;

    printf("testing dg_reversebytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i + 2;
    }

    perror = dg_reversebytes( 
        destbuf, 
        9);

    if (perror != dg_success)
    {
        printf("  dg_reversebytes success case failed with error %s\n", perror);
    }

    if (destbuf[0] != 0x0a)
    {
        printf("  dg_reversebytes success case first byte added incorrect, expected 0x0a, got %x\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0x09)
    {
        printf("  dg_reversebytes success case second byte added incorrect, expected 0x09, got %x\n", destbuf[1]);
    }
    
    if (destbuf[2] != 0x08)
    {
        printf("  dg_reversebytes success case third byte added incorrect, expected 0x08, got %x\n", destbuf[2]);
    }
    
    if (destbuf[3] != 0x07)
    {
        printf("  dg_reversebytes success case fourth byte added incorrect, expected 0x07, got %x\n", destbuf[3]);
    }
    
    if (destbuf[4] != 0x06)
    {
        printf("  dg_reversebytes success case second byte added incorrect, expected 0x06, got %x\n", destbuf[4]);
    }
    
    if (destbuf[5] != 0x05)
    {
        printf("  dg_reversebytes success case second byte added incorrect, expected 0x05, got %x\n", destbuf[5]);
    }
    
    if (destbuf[6] != 0x04)
    {
        printf("  dg_reversebytes success case second byte added incorrect, expected 0x04, got %x\n", destbuf[6]);
    }
    
    if (destbuf[7] != 0x03)
    {
        printf("  dg_reversebytes success case second byte added incorrect, expected 0x03, got %x\n", destbuf[7]);
    }

    if (destbuf[8] != 0x02)
    {
        printf("  dg_reversebytes success case last byte added incorrect, expected 0x02, got %x\n", destbuf[8]);
    }

    if (destbuf[9] != 11)
    {
        printf("  dg_reversebytes success case buffer changed after last character! expected 11, got %d\n", destbuf[9]);
    }
    
    perror = dg_reversebytes( 
        (unsigned char*)-0x1001, 
        9);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_reversebytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i + 2;
    }

    perror = dg_reversebytes( 
        destbuf, 
        4);

    if (perror != dg_success)
    {
        printf("  dg_reversebytes success case failed with error %s\n", perror);
    }

    if (destbuf[0] != 0x05)
    {
        printf("  dg_reversebytes success case first byte added incorrect, expected 0x05, got %x\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0x04)
    {
        printf("  dg_reversebytes success case second byte added incorrect, expected 0x04, got %x\n", destbuf[1]);
    }
    
    if (destbuf[2] != 0x03)
    {
        printf("  dg_reversebytes success case third byte added incorrect, expected 0x03, got %x\n", destbuf[2]);
    }
    
    if (destbuf[3] != 0x02)
    {
        printf("  dg_reversebytes success case fourth byte added incorrect, expected 0x02, got %x\n", destbuf[3]);
    }

    if (destbuf[4] != 6)
    {
        printf("  dg_reversebytes success case buffer changed after last character! expected 6, got %d\n", destbuf[9]);
    }
    
    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i + 2;
    }

    perror = dg_reversebytes( 
        destbuf, 
        1);

    if (perror != dg_success)
    {
        printf("  dg_reversebytes success case length 1 failed with error %s\n", perror);
    }

    if (destbuf[0] != 0x02)
    {
        printf("  dg_reversebytes success case length 1 first byte incorrect, expected 0x02, got %x\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0x03)
    {
        printf("  dg_reversebytes success case length 1 second byte incorrect, expected 0x03, got %x\n", destbuf[1]);
    }
    
    if (destbuf[2] != 0x04)
    {
        printf("  dg_reversebytes success case length 1 third byte incorrect, expected 0x04, got %x\n", destbuf[2]);
    }
    
    if (destbuf[3] != 0x05)
    {
        printf("  dg_reversebytes success case length 1 fourth byte incorrect, expected 0x05, got %x\n", destbuf[3]);
    }

    if (destbuf[4] != 6)
    {
        printf("  dg_reversebytes success case length 1 fifth byte incorrect expected 6, got %d\n", destbuf[9]);
    }
    
    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i + 2;
    }

    perror = dg_reversebytes( 
        destbuf, 
        0);

    if (perror != dg_success)
    {
        printf("  dg_reversebytes success case length 0 failed with error %s\n", perror);
    }

    if (destbuf[0] != 0x02)
    {
        printf("  dg_reversebytes success case length 0 first byte incorrect, expected 0x02, got %x\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0x03)
    {
        printf("  dg_reversebytes success case length 0 second byte incorrect, expected 0x03, got %x\n", destbuf[1]);
    }
    
    if (destbuf[2] != 0x04)
    {
        printf("  dg_reversebytes success case length 0 third byte incorrect, expected 0x04, got %x\n", destbuf[2]);
    }
    
    if (destbuf[3] != 0x05)
    {
        printf("  dg_reversebytes success case length 0 fourth byte incorrect, expected 0x05, got %x\n", destbuf[3]);
    }

    if (destbuf[4] != 6)
    {
        printf("  dg_reversebytes success case length 0 fifth byte incorrect expected 6, got %d\n", destbuf[9]);
    }
}


void testdg_incbytes()
{
    UINT64 i;
    unsigned char destbuf[64];
    const char* perror;
    UINT64 carryout;

    printf("testing dg_incbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i + 2;
    }

    perror = dg_incbytes( 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_incbytes no carry case failed with error %s\n", perror);
    }
    
    if (carryout != 0)
    {
        printf("  dg_incbytes no carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 3)
    {
        printf("  dg_incbytes no carry case first byte added incorrect, expected 4, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 3)
    {
        printf("  dg_incbytes no carry case second byte added incorrect, expected 6, got %d\n", destbuf[1]);
    }

    if (destbuf[8] != 10)
    {
        printf("  dg_incbytes no carry case last byte added incorrect, expected 20, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 11)
    {
        printf("  dg_incbytes no carry case changed buffer after last character added! expected 11, got %d\n", destbuf[9]);
    }
    
    perror = dg_incbytes( 
        (unsigned char*)-0x1001, 
        9,
        &carryout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_incbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_incbytes(
        (unsigned char*)destbuf, 
        9,
        (UINT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_incbytes bad memory at pcarryout case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 0xff;
    }

    destbuf[9] = 0x33;

    perror = dg_incbytes( 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_incbytes carry case failed with error %s\n", perror);
    }
    
    if (carryout != 1)
    {
        printf("  dg_incbytes bytes carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 0x0)
    {
        printf("  dg_incbytes bytes carry case first byte added incorrect, expected 0xfc, got %x\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0x0)
    {
        printf("  dg_incbytes bytes carry case second byte added incorrect, expected 0xfb, got %x\n", destbuf[1]);
    }

    if (destbuf[8] != 0x0)
    {
        printf("  dg_incbytes bytes carry case last byte added incorrect, expected 0xed, got %x\n", destbuf[8]);
    }

    if (destbuf[9] != 0x33)
    {
        printf("  dg_incbytes carry case changed buffer after last character moved! expected 0x33, got %x\n", destbuf[9]);
    }
}


void testdg_decbytes()
{
    UINT64 i;
    unsigned char destbuf[64];
    const char* perror;
    UINT64 carryout;

    printf("testing dg_decbytes\n");

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = (UINT8)i + 2;
    }

    perror = dg_decbytes( 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_decbytes no carry case failed with error %s\n", perror);
    }
    
    if (carryout != 0)
    {
        printf("  dg_decbytes no carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 1)
    {
        printf("  dg_decbytes no carry case first byte added incorrect, expected 4, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 3)
    {
        printf("  dg_decbytes no carry case second byte added incorrect, expected 6, got %d\n", destbuf[1]);
    }

    if (destbuf[8] != 10)
    {
        printf("  dg_decbytes no carry case last byte added incorrect, expected 20, got %d\n", destbuf[8]);
    }

    if (destbuf[9] != 11)
    {
        printf("  dg_decbytes no carry case changed buffer after last character added! expected 11, got %d\n", destbuf[9]);
    }
    
    perror = dg_decbytes( 
        (unsigned char*)-0x1001, 
        9,
        &carryout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_decbytes bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_decbytes(
        (unsigned char*)destbuf, 
        9,
        (UINT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_decbytes bad memory at pcarryout case, expected %s got %s\n", dg_badmemoryerror, perror);
    }

    for (i = 0; i < 20; i++)
    {
        destbuf[i] = 0x00;
    }

    destbuf[9] = 0x33;

    perror = dg_decbytes( 
        destbuf, 
        9,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_decbytes carry case failed with error %s\n", perror);
    }
    
    if (carryout != 1)
    {
        printf("  dg_decbytes bytes carry case carry out incorrect, expected 0, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 0xff)
    {
        printf("  dg_decbytes bytes carry case first byte added incorrect, expected 0xfc, got %x\n", destbuf[0]);
    }
    
    if (destbuf[1] != 0xff)
    {
        printf("  dg_decbytes bytes carry case second byte added incorrect, expected 0xfb, got %x\n", destbuf[1]);
    }

    if (destbuf[8] != 0xff)
    {
        printf("  dg_decbytes bytes carry case last byte added incorrect, expected 0xed, got %x\n", destbuf[8]);
    }

    if (destbuf[9] != 0x33)
    {
        printf("  dg_decbytes carry case changed buffer after last character moved! expected 0x33, got %x\n", destbuf[9]);
    }
}


void testdg_mulu64tou64s()
{
    UINT64 i;
    UINT64 destbuf[16];
    UINT64 srcbuf[16];
    const char* perror;
    UINT64 x;
    UINT32 xlo, xhi;
    UINT64 carryout;

    printf("testing dg_mulu64tou64s\n");
    
    for (i = 0; i < 15; i++)
    {
        destbuf[i] = 0;
        srcbuf[i] = i + 2;
    }
    
    perror = dg_mulu64tou64s (
        destbuf,    // rdi // pdest is already offset and assumed large enough
        srcbuf,     // rsi 
        3,          // u,  // rdx 
        5,          // srclengthinu64s // rcx
        &carryout); // pcarryout

    if (perror != dg_success)
    {
        printf("  dg_mulu64tou64s no carry case failed with error %s\n", perror);
    }
    
    if (carryout != 0)
    {
        printf("  dg_mulu64tou64s no carry case carryout incorrect, expected 0, got %d\n", (UINT32)carryout);
    }

    if (destbuf[0] != 6)
    {
        printf("  dg_mulu64tou64s no carry case first uint64 incorrect, expected 6, got %d\n", (UINT32)destbuf[0]);
    }
    
    if (destbuf[1] != 9)
    {
        printf("  dg_mulu64tou64s no carry case second uint64 incorrect, expected 9, got %d\n", (UINT32)destbuf[1]);
    }

    if (destbuf[4] != 18)
    {
        printf("  dg_mulu64tou64s no carry case last uint64 incorrect, expected 18, got %d\n", (UINT32)destbuf[4]);
    }

    if (destbuf[5] != 0)
    {
        printf("  dg_mulu64tou64s no carry case buffer after last character changed! expected 0, got %d\n", (UINT32)destbuf[5]);
    }
    
    
    perror = dg_mulu64tou64s( 
        (UINT64*)-0x1001,
        srcbuf, 
        3,
        5,
        &carryout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_mulu64tou64s bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_mulu64tou64s(
        (UINT64*)destbuf,
        (UINT64*)-0x1001, 
        3,
        5,
        &carryout);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_mulu64tou64s bad memory at src case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_mulu64tou64s(
        (UINT64*)destbuf,
        (UINT64*)srcbuf, 
        3,
        5,
        (UINT64*)-0x1001);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_mulu64tou64s bad memory at carryout case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    
    for (i = 0; i < 15; i++)
    {
        srcbuf[i] = i + 2;       //  2  3  4  5  6  7  8  9 10 11 12 ...
        destbuf[i] = (UINT64)-1; // -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 -1 ...
    }
                                 

    perror = dg_mulu64tou64s(    //  5  9 12 15 18  8  8
        (UINT64*)destbuf,
        (UINT64*)srcbuf, 
        3,
        5,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_mulu64tou64s carry case failed with error %s\n", perror);
    }

    if (destbuf[0] != 5)
    {
        printf("  dg_mulu64tou64s carry case first uint64 incorrect, expected 5, got %x\n", (UINT32)destbuf[0]);
    }
    
    if (destbuf[1] != 9)
    {
        printf("  dg_mulu64tou64s carry case second uint64 incorrect, expected 8, got %x\n", (UINT32)destbuf[1]);
    }
    
    if (carryout != 1)
    {
        printf("  dg_mulu64tou64s carry case carryout incorrect, expected 1, got %x\n", (UINT32)carryout);
    }
    
    x = destbuf[2];
    if (x != 12)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_mulu64tou64s carry case last uint64 incorrect, expected 12, got %08x%08x\n", xhi, xlo);
    }
    
    x = destbuf[3];
    if (x != 15)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_mulu64tou64s carry case last uint64 incorrect, expected 15, got %08x%08x\n", xhi, xlo);
    }

    x = destbuf[4];
    if (x != 18)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_mulu64tou64s carry case last uint64 incorrect, expected 18, got %08x%08x\n", xhi, xlo);
    }
    
    x = destbuf[5];
    if (x != 0)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_mulu64tou64s carry case last uint64 incorrect, expected 0, got %08x%08x\n", xhi, xlo);
    }

    if (destbuf[6] != (UINT64)-1)
    {
        printf("  dg_mulu64tou64s carry case buffer after last character changed! expected -1, got %x\n", (UINT32)destbuf[5]);
    }
    
    
    for (i = 0; i < 15; i++)
    {
        srcbuf[i] = (UINT64)-1;       
        destbuf[i] = 0; 
    }
                                 

    perror = dg_mulu64tou64s(    
        (UINT64*)destbuf,
        (UINT64*)srcbuf, 
        (UINT64)-1,
        2,
        &carryout);

    if (perror != dg_success)
    {
        printf("  dg_mulu64tou64s max 128 bit x max 64 bit case failed with error %s\n", perror);
    }
    
    if (carryout != 0)
    {
        printf("  dg_mulu64tou64s max 128 bit x max 64 bit case carryout incorrect, expected 0, got %x\n", (UINT32)carryout);
    }

    if (destbuf[0] != 1)
    {
        printf("  dg_mulu64tou64s max 128 bit x max 64 bit case first uint64 incorrect, expected 1, got %x\n", (UINT32)destbuf[0]);
    }
    
    x = destbuf[1];
    if (x != (UINT64)-1)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_mulu64tou64s max 128 bit x max 64 bit case last uint64 incorrect, expected -1, got %08x%08x\n", xhi, xlo);
    }
    
    x = destbuf[2];
    if (x != (UINT64)-2)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_mulu64tou64s max 128 bit x max 64 bit case last uint64 incorrect, expected -2, got %08x%08x\n", xhi, xlo);
    }
    
    x = destbuf[3];
    if (x != 0)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_mulu64tou64s max 128 bit x max 64 bit case last uint64 incorrect, expected 0, got %08x%08x\n", xhi, xlo);
    }
}


void testdg_divu64sbyu64()
{
    UINT64 i;
    UINT64 srcbuf[16];
    UINT64 destbuf[16];
    const char* perror;
    UINT64 x;
    UINT32 xlo, xhi;
    UINT64 remainder;

    printf("testing dg_divu64sbyu64\n");
    
    for (i = 0; i < 15; i++)
    {
        destbuf[i] = (2*i) + 2;
    }
    
    perror = dg_divu64sbyu64 (
        destbuf,     // rdi // pdest is already offset and assumed large enough
        &remainder,  // rsi // premainder
        2,           // u,  // rdx 
        5);          // srclengthinu64s // rcx

    if (perror != dg_success)
    {
        printf("  dg_divu64sbyu64 no remainder success case failed with error %s\n", perror);
    }
    
    if (remainder != 0)
    {
        printf("  dg_divu64sbyu64 no remainder success case remainder incorrect, expected 0, got %d\n", (UINT32)remainder);
    }

    if (destbuf[0] != 1)
    {
        printf("  dg_divu64sbyu64 no remainder success case first uint64 incorrect, expected 1, got %d\n", (UINT32)destbuf[0]);
    }
    
    if (destbuf[1] !=  2)
    {
        printf("  dg_divu64sbyu64 no remainder success case second uint64 incorrect, expected 2, got %d\n", (UINT32)destbuf[1]);
    }

    if (destbuf[4] != 5)
    {
        printf("  dg_divu64sbyu64 no remainder success case last uint64 incorrect, expected 5, got %d\n", (UINT32)destbuf[4]);
    }

    if (destbuf[5] != 12)
    {
        printf("  dg_divu64sbyu64 no remainder success case buffer after last character changed! expected 12, got %d\n", (UINT32)destbuf[5]);
    }
    
    
    perror = dg_divu64sbyu64( 
        (UINT64*)-0x1001,
        &remainder, 
        3,
        5);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_divu64sbyu64 bad memory at dest case, expected %s got %s\n", dg_badmemoryerror, perror);
    }
    
    perror = dg_divu64sbyu64(
        (UINT64*)destbuf,
        (UINT64*)-0x1001, 
        3,
        5);

    if (perror != dg_badmemoryerror)
    {
        printf("- FAIL! dg_divu64sbyu64 bad memory at premainder case, expected %s got %s\n", dg_badmemoryerror, perror);
    }    
    
    for (i = 0; i < 15; i++)
    {
        destbuf[i] = (2*i) + 2;
    }
    
    destbuf[0] = destbuf[0] + 1;
    
    perror = dg_divu64sbyu64 (
        destbuf,     // rdi // pdest is already offset and assumed large enough
        &remainder,  // rsi 
        2,           // u,  // rdx 
        5);          // srclengthinu64s // rcx

    if (perror != dg_success)
    {
        printf("  dg_divu64sbyu64 remainder success case failed with error %s\n", perror);
    }
    
    if (remainder != 1)
    {
        printf("  dg_divu64sbyu64 remainder success case remainder incorrect, expected 1, got %d\n", (UINT32)remainder);
    }

    if (destbuf[0] != 1)
    {
        printf("  dg_divu64sbyu64 remainder success case first uint64 incorrect, expected 1, got %d\n", (UINT32)destbuf[0]);
    }
    
    if (destbuf[1] !=  2)
    {
        printf("  dg_divu64sbyu64 remainder success case second uint64 incorrect, expected 2, got %d\n", (UINT32)destbuf[1]);
    }

    if (destbuf[4] != 5)
    {
        printf("  dg_divu64sbyu64 remainder success case last uint64 incorrect, expected 5, got %d\n", (UINT32)destbuf[4]);
    }

    if (destbuf[5] != 12)
    {
        printf("  dg_divu64sbyu64 remainder success case buffer after last character changed! expected 12, got %d\n", (UINT32)destbuf[5]);
    }
    
    
    for (i = 0; i < 15; i++)
    {
        destbuf[i] = 0;
    }
    
    destbuf[0] = 1;
    destbuf[1] = (UINT64)-2;
    
    perror = dg_divu64sbyu64 (
        destbuf,     // rdi // pdest is already offset and assumed large enough
        &remainder,  // rsi 
        (UINT64)-1,  // u,  // rdx 
        2);          // srclengthinu64s // rcx

    if (perror != dg_success)
    {
        printf("  dg_divu64sbyu64 1 -2 / -1 success case failed with error %s\n", perror);
    }
    
    if (remainder != 0)
    {
        printf("  dg_divu64sbyu64 1 -2 / -1 success case remainder incorrect, expected 1, got %d\n", (UINT32)remainder);
    }

    if (destbuf[0] != (UINT64)-1)
    {
        printf("  dg_divu64sbyu64 1 -2 / -1 success case first uint64 incorrect, expected 1, got %d\n", (UINT32)destbuf[0]);
    }
    
    if (destbuf[1] !=  0)
    {
        printf("  dg_divu64sbyu64 1 -2 / -1 success case second uint64 incorrect, expected 2, got %d\n", (UINT32)destbuf[1]);
    }

    if (destbuf[4] != 0)
    {
        printf("  dg_divu64sbyu64 1 -2 / -1 success case last uint64 incorrect, expected 5, got %d\n", (UINT32)destbuf[4]);
    }

    if (destbuf[5] != 0)
    {
        printf("  dg_divu64sbyu64 1 -2 / -1 success case buffer after last character changed! expected 0, got %d\n", (UINT32)destbuf[5]);
    }
    
    for (i = 0; i < 15; i++)
    {
        destbuf[i] = 0;
        srcbuf[i] = ((UINT64)-1) - i;
    }
    
    perror = dg_mulu64tou64s(    
        (UINT64*)destbuf,
        (UINT64*)srcbuf, 
        (UINT64)-3,
        4,
        &remainder);

    if (perror != dg_success)
    {
        printf("  dg_divu64sbyu64 complicated success case failed with error %s\n", perror);
    }
    
    perror = dg_divu64sbyu64 (
        destbuf,     // rdi // pdest is already offset and assumed large enough
        &remainder,  // rsi 
        (UINT64)-3,  // u,  // rdx 
        5);          // srclengthinu64s // rcx

    if (perror != dg_success)
    {
        printf("  dg_divu64sbyu64 complicated success case failed with error %s\n", perror);
    }
    
    if (remainder != 0)
    {
        printf("  dg_divu64sbyu64 complicated success case remainder incorrect, expected 1, got %d\n", (UINT32)remainder);
    }

    if (destbuf[0] != ((UINT64)-1) - 0)
    {
        printf("  dg_divu64sbyu64 complicated success case first uint64 incorrect, expected ((UINT64)-1) - 0, got %d\n", (UINT32)destbuf[0]);
    }
    
    if (destbuf[1] !=  ((UINT64)-1) - 1)
    {
        printf("  dg_divu64sbyu64 complicated success case second uint64 incorrect, expected ((UINT64)-1) - 1, got %d\n", (UINT32)destbuf[1]);
    }

    if (destbuf[4] != 0)
    {
        printf("  dg_divu64sbyu64 complicated success case last uint64 incorrect, expected 0, got %d\n", (UINT32)destbuf[4]);
    }

    if (destbuf[5] != 0)
    {
        printf("  dg_divu64sbyu64 complicated success case buffer after last character changed! expected 0, got %d\n", (UINT32)destbuf[5]);
    }
    
    for (i = 0; i < 15; i++)
    {
        destbuf[i] = 0;
    }
    
    destbuf[0] = 1;
    destbuf[1] = (UINT64)-2;
    
    perror = dg_divu64sbyu64 (
        destbuf,     // rdi // pdest is already offset and assumed large enough
        &remainder,  // rsi 
        0,    // u,  // rdx 
        2);          // srclengthinu64s // rcx

    if (perror != dg_success)
    {
        printf("  dg_divu64sbyu64 /0 success case failed with error %s\n", perror);
    }
    
    if (remainder != (UINT64)-1)
    {
        printf("  dg_divu64sbyu64 /0 success case remainder incorrect, expected -1, got %d\n", (UINT32)remainder);
    }

    if (destbuf[0] != 1)
    {
        printf("  dg_divu64sbyu64 /0 success case first uint64 incorrect, expected 1, got %d\n", (UINT32)destbuf[0]);
    }
    
    if (destbuf[1] !=  (UINT64)-2)
    {
        printf("  dg_divu64sbyu64 /0 success case second uint64 incorrect, expected -2, got %d\n", (UINT32)destbuf[1]);
    }
}


void testdg_newmutexanddg_freemutex()
{
    UINT64 x;
    const char* perror;
    
    struct DG_Mutex_Holder mymutexholder;
    
    printf("testing dg_newmutex and dg_freemutex\n");
    
    // success case
    perror = dg_newmutex(
        &mymutexholder,     
        dg_success);

    if (perror != dg_success)
    {
        printf("  dg_newmutex failed with error %s", perror);
    }
    
    if (mymutexholder.aftermutexmem != 0)
    {
       printf("  dg_newmutex failed - memory after mutexmem changed... should be 0\n");
    }

    perror = dg_freemutex(
        &mymutexholder,
        dg_success);

    if (perror != dg_success)
    {
        printf("  dg_freemutex failed with error %s", perror);
        printf("\n");
    }
    
    // trying to free a bad id should give an error
    perror = dg_freemutex(
        &mymutexholder,
        dg_success);

    if (perror == dg_success)
    {
        printf("  doing dg_freemutex on already freed mutex did not give an error.\n");
    }
}

void testdg_lockmutexanddg_unlockmutex()
{
    UINT64 x;
    const char* perror;
    
    struct DG_Mutex_Holder mymutexholder;
    
    printf("testing dg_lockmutex and dg_unlockmutex\n");

    perror = dg_newmutex(
        &mymutexholder,
        dg_success);

    if (perror != dg_success)
    {
        printf("  dg_newmutex failed with error %s", perror);
    }

    perror = dg_lockmutex(
        &mymutexholder,
        dg_success);

    if (perror != dg_success)
    {
        printf("  dg_lockmutex failed with error %s", perror);
        
        perror = dg_freemutex(
            &mymutexholder,
            dg_success);

        if (perror != dg_success)
        {
            printf("  dg_freemutex failed with error %s", perror);
            printf("\n");
        }
        
        return;
    }
    
    if (mymutexholder.aftermutexmem != 0)
    {
        printf("  dg_lockmutex failed - memory after mutexmem changed, should still be 0\n");
    }
    
    // trying to lock mutex twice should cause an error
    //   this test causes process to hang on mac os x
    // perror = dg_lockmutex(pmutexmem, dg_success);
    
    // if (perror == dg_success)
    // {
    //    printf("  doing dg_lockmutex on locked mutex did not give an error.\n");
    // }
    
    // trying to free a locked mutex should cause an error
    perror = dg_freemutex(
        &mymutexholder,
        dg_success);
    
    if (perror == dg_success)
    {
        printf("  doing dg_freemutex on locked mutex should give an error.\n");
    }
    
    perror = dg_unlockmutex(
        &mymutexholder,
        dg_success);
    
    if (perror != dg_success)
    {
        printf("  dg_unlockmutex returned an error, got error %s", perror);
    }
    
    if (mymutexholder.aftermutexmem != 0)
    {
        printf("  dg_unlockmutex failed - memory after mutexmem changed, it should still be 0\n");
    }
    
    perror = dg_freemutex(
        &mymutexholder,
        dg_success);

    if (perror != dg_success)
    {
        printf("  dg_freemutex failed with error %s", perror);
        printf("\n");
    }
}

void testdg_uaddclipped()
{
    UINT64 x;
    UINT32 xlo, xhi;

    printf("testing dg_uaddclipped\n");

    x = dg_uaddclipped(5,3);

    if (x != 8)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf("  dg_uaddclipped(5, 3) fail! - expected 8, got %08x%08x\n", xhi, xlo);
    }

    x = dg_uaddclipped((UINT64)-3, 1);

    if (x != (UINT64)-2)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf(" dg_uaddclipped(-3, 1) fail!, expected -2, got %08x%08x\n", xhi, xlo);
    }
    
    x = dg_uaddclipped((UINT64)-3, 2);

    if (x != (UINT64)-1)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf(" dg_uaddclipped(-3, 2) fail!, expected -1, got %08x%08x\n", xhi, xlo);
    }
    
    x = dg_uaddclipped((UINT64)-3, 3);

    if (x != (UINT64)-1)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf(" dg_uaddclipped(-3, 3) fail!, expected -1, got %08x%08x\n", xhi, xlo);
    }
    
    x = dg_uaddclipped((UINT64)-3, 4);

    if (x != (UINT64)-1)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf(" dg_uaddclipped(-3, 4) fail!, expected -1, got %08x%08x\n", xhi, xlo);
    }
}

void* testfunctioninc(void* px)
{
    (*((UINT64*)px))++;
    return ((void*)NULL);
}

void testdg_callfunctionasync()
{
    UINT64 threadhandle;
    const char* pError;
    UINT64 x = 0;
    UINT32 xlo, xhi;
    
    void* (*functionptr)(void*) = &testfunctioninc;
    
    printf("testing dg_callfunctionasync\n");
    
    // success case
    pError = dg_callfunctionasync(
        &threadhandle,
        functionptr, 
        &x);
        
    if (pError != dg_success)
    {
        printf(" dg_callfunctionasync success case, got error calling test inc function\n");
    }
    
    printf("   ... waiting 1 second to let child thread run ... ");
#ifdef DGLU_OS_FREEBSD
    usleep(1000); // wait a second
#endif
#ifdef DGLU_OS_WIN64
    SleepEx(1000, false); // wait a second
#endif
    if (x != 1)
    {
        xlo = x & 0xffffffff;
        xhi = (x >> 32) & 0xffffffff;
        printf(" dg_callfunctionasync success case fail!, expected 1 after 1 second, got %08x%08x\n", xhi, xlo);
    }
    
    printf("   ... it worked ... \n");
}


int main(int argc, char* argv[])
{ 
    /*
   
    printf("testing dg_testasmimport\n");
    
    perror = dg_testasmimport();
    
    if (perror != dg_success)
    {
        printf(" - FAIL! dg_testasmimport, expected %s got %s\n", dg_success, perror);
    }
    
    
    */



/*
    printf("\n");
	printf("testing assembler function import linking using dg_testasm\n");

    if (dg_testasm(0x01020304) != 0x01020305)
    {
        printf("  function import failed\n");
    }
    else
    {
        printf("  function import succeeded\n");
    }
    */
	

testdg_initpbharrayhead();
testdg_testasm();
testdg_bswap();
testdg_lobit();
testdg_hibit();
testdg_countbits();
testdg_twoslash();
testdg_lshift();
testdg_rshift();
testdg_udmslashmod();
// testdg_umslashmod();  // need test
testdg_mstar();
testdg_umstar();
testdg_mstarslash();  
testdg_shrd();
testdg_ashrd();
testdg_shld();

testdg_dabs();
testdg_dnegate();
testdg_f64sincos();
testdg_dplus();
testdg_dminus();
testdg_dulessthan();
testdg_dugreaterequalthan();
testdg_dlessthan();
testdg_dgreaterequalthan();
testdg_dumin();
testdg_dumax();
testdg_dmin();
testdg_dmax();

testdg_tentothex();
testdg_i64tof64();
// testdg_timeslog2();  // need test
testdg_f64toi64();
testdg_roundf64tonearesteven();
testdg_roundf64tonegativeinfinity();
// testdg_f64fyl2x // need test
// testdg_f64fyl2xp1 // need test
// testdg_f64f2xm1  // need test
testdg_truncatef64();
testdg_f64getfractional();
testdg_f64logbase2of10();
testdg_f64logbase2ofe(); 
// testdg_f64fpatan // need test
testdg_f64tof32(); 
testdg_f32tof64(); 
testdg_f64sqrt();
testdg_f64sin();
testdg_f64cos();
testdg_f64tan();

testdg_getbyte();
testdg_getuint16();
testdg_getuint32();
testdg_getuint64();
testdg_putbyte();
testdg_putuint16();
testdg_putuint32();
testdg_putuint64();
testdg_movebytes();
testdg_moveuint64s();
testdg_movebytes2();
testdg_movebytesforward();
testdg_movebytesreverse();
testdg_movebytesskipdestination();
testdg_scanforbyte();
testdg_scanforbyte2();
testdg_scanfornotbytereverse();
testdg_scanforuint64();
testdg_comparebytes();
testdg_fillwithbyte();
testdg_readallbytes();
testdg_search();
testdg_search2();



testdg_chartodigit();
testdg_pchartonumber();
testdg_hexdectonumber();
testdg_pchartonumberskipperiod();
testdg_pchartobase10numberandexponent();
testdg_u64times10totheu64tof64();
testdg_pchartof64();

testdg_getsenvnamevalue();

testdg_getuleb128size();
testdg_getlengthwithuleb128length();
testdg_getlengthwithuleb128length2();
testdg_touleb128();
testdg_hctwostore();
testdg_gethctwolength();
// testdg_pushhctwotobuffer(); // this test needs to be in another file... and need test?

testdg_getpagesize();
testdg_mallocanddg_free();
testdg_realloc();

testdg_gethstdin();
testdg_gethstdout();
testdg_gethstderror();
testdg_openfileforwritenewanddg_closefile();
testdg_writefile();
testdg_getfilelength();
testdg_openfileforread();
testdg_readfile();
testdg_writestdoutraw();
testdg_getfiletype();
testdg_writefilewithlargemessage();
testdg_readfilewithlargemessage();
testdg_openfileforwritenewwithexistingfile();
testdg_getenvironmentvariable();

testdg_addbytes();
testdg_adcbytes();
testdg_sbbbytes();
testdg_shlbytes();
testdg_shrbytes();
testdg_rclbytes();
testdg_rcrbytes();
testdg_sarbytes();
testdg_notbytes();
testdg_andbytes();
testdg_orbytes();
testdg_nandbytes();
testdg_norbytes();
testdg_xnorbytes();
testdg_reversebytes();
testdg_incbytes();
testdg_decbytes();
testdg_mulu64tou64s();
testdg_divu64sbyu64();

testdg_newmutexanddg_freemutex();
testdg_lockmutexanddg_unlockmutex();
testdg_uaddclipped();

testdg_callfunctionasync();

testmaxu32comparecompilation();
testu64constantcompilation();
testneg1constantcompilation();
// testmaxnegi32constantcompilation();

testdg_n8ton64();
testdg_n16ton64();
testdg_n32ton64();

testdg_twototheu();
testdg_setbit();
testdg_clrbit();
testdg_notbit();

testdg_scanforuthsetbit();
testdg_getulowestsetbits();
testdg_getulowestbits();
testdg_getulowestbitsmask();

testdg_compareforconditionsub();



/*
    testdg_makedototobuf();
    
    // testdg_makesharedlibtobuf();
    testdg_runfileandwait();
*/
        printf("   \n  All tests done. \n");    

	return(0);
}



// testdg_calcoffsettovalue
// testdg_makemachotrieforlt256
// testdg_makedototobufsub

