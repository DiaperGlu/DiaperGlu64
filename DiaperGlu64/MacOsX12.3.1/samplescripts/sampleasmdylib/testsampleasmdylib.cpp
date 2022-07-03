// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.5.
//
//    DiaperGlu v5.5 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.5 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.5; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// July 2, 2022               //
// version 5.5                //
// /////////////////////////////

#include <stdio.h>
#include <sys/types.h>

#define UINT8 unsigned char
#define INT8 char

#define UINT16 __uint16_t 
#define INT16 __int16_t
	
#define UINT32 __uint32_t 
#define INT32 __int32_t

#define UINT64 __uint64_t
#define INT64 __int64_t

#define UINT128 __uint128_t
#define INT128 __int128_t

#define FLOAT64 double

extern "C" UINT64 dg_bswap(UINT64 u);
extern "C" UINT64 dg_udmslashmod(UINT64* pints);
extern "C" UINT64 dg_inc(UINT64 u);
extern "C" UINT64 dg_twoslash(UINT64 u);
extern "C" UINT64 dg_lshift(
    UINT64 u,
    UINT64 shiftcount);
extern "C" UINT128 dg_touleb128(UINT64 u);
extern "C" UINT128 dg_shrd(UINT128 u, UINT64 shiftcount);
extern "C" FLOAT64 dg_tentothex(UINT64 x);
extern "C" UINT128 dg_f64timesf64tof128(UINT64 x, UINT64 y);

int main(int argc, char* argv[])
{
    UINT64 x;
    UINT128 ud;
    
    INT64 n;
    UINT32 xhi, xlo;
    INT32 nlo;
    
    UINT64 pints[4];
    
    FLOAT64 df;

    printf("testing sampleasmdylib.dylib\n");
    
    printf("  testing dg_bswap\n");

    x = dg_bswap(0x8877665544332211);
    
    if (x != 0x1122334455667788)
    {
    
       printf("  FAIL! dg_bswap(0x8877665544332211) success test - expected 0x1122334455667788, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }
    
    
    printf("  testing dg_udmslashmod\n");
    
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
    
    
    printf("  testing dg_inc\n");

    x = dg_inc(0x8877665544332211);
    
    if (x != 0x8877665544332212)
    {
    
       printf("  FAIL! dg_inc(0x8877665544332211) success test - expected 0x8877665544332212, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }
    
    
    printf("  testing dg_twoslash\n");

    x = dg_twoslash(0x8877665544332211);
    
    if (x !=        0xC43BB32AA2199108)
    {
    
       printf("  FAIL! dg_twoslash(0x8877665544332211) success test - expected 0xC43BB32AA2199108, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }
    
    x = dg_twoslash(0);
    
    if (x != 0)
    {
    
       printf("  FAIL! dg_twoslash(0) success test - expected 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }
    
    
    printf("  testing dg_lshift\n");

    x = dg_lshift(0x8877665544332211, 4);
    
    if (x != 0x8776655443322110)
    {
    
       printf("  FAIL! dg_lshift(0x8877665544332211, 4) success test - expected 0x8776655443322110, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
        
        return(1);

    }
    
    printf("  testing dg_touleb128\n");
    
    ud = dg_touleb128(0);
    
    if ( ( ((UINT64*)(&ud))[1] != 0x0100000000000000) ||
         ( ((UINT64*)(&ud))[0] != 0x0000000000000000) )
    {
        printf("  dg_touleb128(0) fail! - expected 0x010000000000000000000000000000000, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(1);

    if ( ( ((UINT64*)(&ud))[1] != 0x0100000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x0000000000000001 )  )
    {
        printf("  dg_touleb128(1) fail! - expected 0x01000000000000000000000000000001, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x7F);

    if ( ( ((UINT64*)(&ud))[1] != 0x0100000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x000000000000007F )  )
    {
        printf("  dg_touleb128(0x7F) fail! - expected 0x0100000000000000000000000000007F, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x80);

    if ( ( ((UINT64*)(&ud))[1] != 0x0200000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x0000000000000180 )  )
    {
        printf("  dg_touleb128(0x80) fail! - expected 0x02000000000000000000000000000180, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x3FFF);

    if ( ( ((UINT64*)(&ud))[1] != 0x0200000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x0000000000007FFF )  )
    {
        printf("  dg_touleb128(0x3FFF) fail! - expected 0x02000000000000000000000000007FFF, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x4000);

    if ( ( ((UINT64*)(&ud))[1] != 0x0300000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x0000000000018080 )  )
    {
        printf("  dg_touleb128(0x4000) fail! - expected 0x03000000000000000000000000018080, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x1FFFFF);

    if ( ( ((UINT64*)(&ud))[1] != 0x0300000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x00000000007FFFFF )  )
    {
        printf("  dg_touleb128(0x1FFFFF) fail! - expected 0x030000000000000000000000007FFFFF, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x200000);

    if ( ( ((UINT64*)(&ud))[1] != 0x0400000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x0000000001808080 )  )
    {
        printf("  dg_touleb128(0x200000) fail! - expected 0x04000000000000000000000001808080, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0xFFFFFFF);

    if ( ( ((UINT64*)(&ud))[1] != 0x0400000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x000000007FFFFFFF )  )
    {
        printf("  dg_touleb128(0xFFFFFFF) fail! - expected 0x0400000000000000000000007FFFFFFF, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x10000000);

    if ( ( ((UINT64*)(&ud))[1] != 0x0500000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x0000000180808080 )  )
    {
        printf("  dg_touleb128(0x10000000) fail! - expected 0x05000000000000000000000180808080, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x7FFFFFFFF);

    if ( ( ((UINT64*)(&ud))[1] != 0x0500000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x0000007FFFFFFFFF )  )
    {
        printf("  dg_touleb128(0x7FFFFFFFF) fail! - expected 0x05000000000000000000007FFFFFFFFF, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x800000000);

    if ( ( ((UINT64*)(&ud))[1] != 0x0600000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x0000018080808080 )  )
    {
        printf("  dg_touleb128(0x800000000) fail! - expected 0x06000000000000000000018080808080, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x3FFFFFFFFFF);

    if ( ( ((UINT64*)(&ud))[1] != 0x0600000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x00007FFFFFFFFFFF )  )
    {
        printf("  dg_touleb128(0x3FFFFFFFFFF) fail! - expected 0x060000000000000000007FFFFFFFFFFF, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x40000000000);

    if ( ( ((UINT64*)(&ud))[1] != 0x0700000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x0001808080808080 )  )
    {
        printf("  dg_touleb128(0x40000000000) fail! - expected 0x07000000000000000001808080808080, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x1FFFFFFFFFFFF);

    if ( ( ((UINT64*)(&ud))[1] != 0x0700000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x007FFFFFFFFFFFFF )  )
    {
        printf("  dg_touleb128(0x1FFFFFFFFFFFF) fail! - expected 0x0700000000000000007FFFFFFFFFFFFF, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x2000000000000);

    if ( ( ((UINT64*)(&ud))[1] != 0x0800000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x0180808080808080 )  )
    {
        printf("  dg_touleb128(0x2000000000000) fail! - expected 0x08000000000000000180808080808080, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0xFFFFFFFFFFFFFF);

    if ( ( ((UINT64*)(&ud))[1] != 0x0800000000000000 )  ||
         ( ((UINT64*)(&ud))[0] != 0x7FFFFFFFFFFFFFFF )  )
    {
        printf("  dg_touleb128(0xFFFFFFFFFFFFFF) fail! - expected 0x07000000000000007FFFFFFFFFFFFFFF, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x0100000000000000);

    if ( ( ((UINT64*)(&ud))[1] != 0x0900000000000001 )  ||
         ( ((UINT64*)(&ud))[0] != 0x8080808080808080 )  )
    {
        printf("  dg_touleb128(0x0100000000000000) fail! - expected 0x09000000000000018080808080808080, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x7FFFFFFFFFFFFFFF);

    if ( ( ((UINT64*)(&ud))[1] != 0x090000000000007F )  ||
         ( ((UINT64*)(&ud))[0] != 0xFFFFFFFFFFFFFFFF )  )
    {
        printf("  dg_touleb128(0x7FFFFFFFFFFFFFFF) fail! - expected 0x090000000000007FFFFFFFFFFFFFFFFF, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0x8000000000000000);

    if ( ( ((UINT64*)(&ud))[1] != 0x0A00000000000180 )  ||
         ( ((UINT64*)(&ud))[0] != 0x8080808080808080 )  )
    {
        printf("  dg_touleb128(0x8000000000000000) fail! - expected 0x0A0000000000018080808080808080, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ud = dg_touleb128(0xFFFFFFFFFFFFFFFF);

    if ( ( ((UINT64*)(&ud))[1] != 0x0A000000000001FF )  ||
         ( ((UINT64*)(&ud))[0] != 0xFFFFFFFFFFFFFFFF )  )
    {
        printf("  dg_touleb128(0xFFFFFFFFFFFFFFFF) fail! - expected 0x0A000000000001FFFFFFFFFFFFFFFFF, instead got %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }
    
    
    printf("  testing dg_shrd\n");

    ((UINT64*)(&ud))[1] = 0x0F7F6E5D4C3B2A19;
    ((UINT64*)(&ud))[0] = 0x0817263544536271;

    ud = dg_shrd(ud, 4);

    if ( ( (((UINT64*)(&ud))[0]) != 0x9081726354453627)  ||
         ( (((UINT64*)(&ud))[1]) != 0x00F7F6E5D4C3B2A1)  )
    {
        printf("  dg_shrd(0x0F7F6E5D 4C3B2A19 08172635 44536271, 4) fail! - expected 0x 00F7F6E5 D4C3B2A1 90817263 54453627, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ((UINT64*)(&ud))[1] = 0x8F7F6E5D4C3B2A19;
    ((UINT64*)(&ud))[0] = 0x0817263544536271;

    ud = dg_shrd(ud, 8);

    if ( ( (((UINT64*)(&ud))[0]) != 0x1908172635445362)  ||
         ( (((UINT64*)(&ud))[1]) != 0x008F7F6E5D4C3B2A)  )
    {
        printf("  dg_shrd(0x8F7F6E5D 4C3B2A19 08172635 44536271, 8) fail! - expected 0x 008F7F6E 5D4C3B2A 19081726 35445362, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ((UINT64*)(&ud))[1] = 0x8F7F6E5D4C3B2A19;
    ((UINT64*)(&ud))[0] = 0x0817263544536271;

    ud = dg_shrd(ud, 0x3C);

    if ( ( (((UINT64*)(&ud))[0]) != 0xF7F6E5D4C3B2A190)  ||
         ( (((UINT64*)(&ud))[1]) != 0x0000000000000008)  )
    {
        printf("  dg_shrd(0x8F7F6E5D 4C3B2A19 08172635 44536271, 0x3C) fail! - expected 0x 00000000 00000008 F7F6E5D4 C3B2A190, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ((UINT64*)(&ud))[1] = 0x8000000000000002;
    ((UINT64*)(&ud))[0] = 0x0817263544536271;

    ud = dg_shrd(ud, 0x3F);

    if ( ( (((UINT64*)(&ud))[0]) != 0x0000000000000004)  ||
         ( (((UINT64*)(&ud))[1]) != 0x0000000000000001)  )
    {
        printf("  dg_shrd(0x80000000 00000001 08172635 44536271, 0x44) fail! - expected 0x 00000000 00000001 00000000 00000004, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ((UINT64*)(&ud))[1] = 0x8F7F6E5D4C3B2A19;
    ((UINT64*)(&ud))[0] = 0x0817263544536271;

    ud = dg_shrd(ud, 0x40);

    if ( ( (((UINT64*)(&ud))[0]) != 0x8F7F6E5D4C3B2A19)  ||
         ( (((UINT64*)(&ud))[1]) != 0x0)  )
    {
        printf("  dg_shrd(0x8F7F6E5D 4C3B2A19 08172635 44536271, 0x40) fail! - expected 0x 00000000 00000000 8F7F6E5D 4C3B2A19, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

    ((UINT64*)(&ud))[1] = 0x8F7F6E5D4C3B2A19;
    ((UINT64*)(&ud))[0] = 0x0817263544536271;

    ud = dg_shrd(ud, 0x44);

    if ( ( (((UINT64*)(&ud))[0]) != 0x08F7F6E5D4C3B2A1)  ||
         ( (((UINT64*)(&ud))[1]) != 0x0)  )
    {
        printf("  dg_shrd(0x8F7F6E5D 4C3B2A19 08172635 44536271, 0x44) fail! - expected 0x 00000000 00000000 08F7F6E5 D4C3B2A1, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }
    
    printf("  testing dg_tentothex\n");
    
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
    

// C000000000000000 CONSTANT FPD-2.0

// 3FF0000000000000 CONSTANT FPD1.0
// 3FF8000000000000 CONSTANT FPD1.5
// 4000000000000000 CONSTANT FPD2.0
// 4004000000000000 CONSTANT FPD2.5
// 4008000000000000 CONSTANT FPD3.0
// 4010000000000000 CONSTANT FPD4.0
// 4012000000000000 CONSTANT FPD4.5
// 4014000000000000 CONSTANT FPD5.0
// 4018000000000000 CONSTANT FPD6.0
// 4020000000000000 CONSTANT FPD8.0
// 4022000000000000 CONSTANT FPD9.0    
    
    printf("  testing dg_f64timesf64tof128\n");
    
    ud = dg_f64timesf64tof128(0, 0);
    
    if ( ( (((UINT64*)(&ud))[0]) != 0)  ||
         ( (((UINT64*)(&ud))[1]) != 0)  )
    {
        printf("  dg_f64timesf64tof128(0, 0) fail! - expected 0, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }
    
    ud = dg_f64timesf64tof128(0x3FF0000000000000, 0);
    
    if ( ( (((UINT64*)(&ud))[0]) != 0)  ||
         ( (((UINT64*)(&ud))[1]) != 0)  )
    {
        printf("  dg_f64timesf64tof128(3FF0000000000000, 0) fail! - expected 0, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }
    
    ud = dg_f64timesf64tof128(0, 0x3FF0000000000000);
    
    if ( ( (((UINT64*)(&ud))[0]) != 0)  ||
         ( (((UINT64*)(&ud))[1]) != 0)  )
    {
        printf("  dg_f64timesf64tof128(0, 0x3FF0000000000000) fail! - expected 0, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }
    
    ud = dg_f64timesf64tof128(0x4000000000000000, 0x3FF0000000000000);
    
    if ( ( (((UINT64*)(&ud))[1]) != 0x4000000000000000)  ||
         ( (((UINT64*)(&ud))[0]) != 0)  )
    {
        printf("  dg_f64timesf64tof128(0x4000000000000000, 0x3FF0000000000000) fail! - expected 0x 0x40000000 0x00000000 0x00000000 0x00000000, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }
    
    ud = dg_f64timesf64tof128(0x4000000000000000, 0x4000000000000000);
    
    if ( ( (((UINT64*)(&ud))[1]) != 0x4001000000000000)  ||
         ( (((UINT64*)(&ud))[0]) != 0)  )
    {
        printf("  dg_f64timesf64tof128(0x4000000000000000, 0x4000000000000000) fail! - expected 0x 0x40000000 0x00000000 0x00000000 0x00000000, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }
    
    ud = dg_f64timesf64tof128(0x4008000000000000, 0x4000000000000000);
    
    if ( ( (((UINT64*)(&ud))[1]) != 0x4001800000000000)  ||
         ( (((UINT64*)(&ud))[0]) != 0)  )
    {
        printf("  dg_f64timesf64tof128(0x4000800000000000, 0x4000000000000000) fail! - expected 0x 0x40018000 0x00000000 0x00000000 0x00000000, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }
    
    ud = dg_f64timesf64tof128(0x4008000000000000, 0x4008000000000000);
    
    if ( ( (((UINT64*)(&ud))[1]) != 0x4002200000000000)  ||
         ( (((UINT64*)(&ud))[0]) != 0)  )
    {
        printf("  dg_f64timesf64tof128(0x4002200000000000, 0x4008000000000000) fail! - expected 0x 0x40018000 0x00000000 0x00000000 0x00000000, instead got 0x %08x %08x %08x %08x\n",
         ((UINT32*)(&ud))[3],
         ((UINT32*)(&ud))[2],
         ((UINT32*)(&ud))[1],
         ((UINT32*)(&ud))[0]);
    }

	return(0);
}
