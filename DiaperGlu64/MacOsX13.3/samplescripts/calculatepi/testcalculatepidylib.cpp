// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.10.
//
//    DiaperGlu v5.10 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.10 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.10; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// May 5, 2023                //
// version 5.10               //
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

extern "C" UINT64 dg_adduint64s(
    UINT64* pdest,
    UINT64* psrc,
    UINT64 lengthinuint64s);
    
extern "C" UINT64 dg_subuint64s(
    UINT64* pdest,
    UINT64* psrc,
    UINT64 lengthinuint64s);
    
extern "C" UINT64 dg_shluint64s(
    UINT64* psrc,
    UINT64* pdest,
    UINT64 lengthinuint64s,
    UINT64 shiftcount);
    
extern "C" UINT64 dg_shruint64s(
    UINT64* psrc,
    UINT64* pdest,
    UINT64 lengthinuint64s,
    UINT64 shiftcount);
    
extern "C" UINT64 dg_shradduint64s(
    UINT64* psrc,
    UINT64* pdest,
    UINT64 lengthinuint64s,
    UINT64 shiftcount);
    
extern "C" UINT64 dg_shradduint64ssub(
    UINT64* psrc,
    UINT64* pdest,
    UINT64 lengthinuint64s,
    UINT64 shiftcountinbits,
    UINT64 shiftcountinuint64s);
    
extern "C" UINT64 dg_shladduint64s(
    UINT64* psrc,
    UINT64* pdest,
    UINT64 lengthinuint64s,
    UINT64 shiftcount);
    
extern "C" UINT64 dg_shladduint64ssub(
    UINT64* psrc,
    UINT64* pdest,
    UINT64 lengthinuint64s,
    UINT64 shiftcountinbits,
    UINT64 shiftcountinuint64s);
    
extern "C" UINT64 dg_addbitinuint64s( 
    UINT64* pdestuint64s,
    UINT64 lengthinuint64s,
    UINT64 bitposition);
    
extern "C" UINT64 dg_add2abplusbsquaredtouint64s(
     UINT64* pa, 
     UINT64* pdestuint64s, 
     UINT64 lengthinuint64s,               
     UINT64 indexinbits,
     UINT64 indexinuint64s, 
     UINT64 fractionalbits);
     
extern "C" UINT128 dg_getshiftplusone(
    UINT64 shiftinbits, 
    UINT64 shiftinuint64s);
    
extern "C" UINT128 dg_getshiftdoubled(
    UINT64 shiftinbits, 
    UINT64 shiftinuint64s,
    UINT64 fractionaluint64s);
    
extern "C" UINT64 dg_indextopowerof2(
    UINT64 shiftinuint64s,
    UINT64 fractionaluint64s);
    
extern "C" UINT64 dg_powerof2toindex( 
    UINT64 shiftinuint64s,
    UINT64 fractionaluint64s);
    
extern "C" UINT128 dg_findhighestbitinuint64s( 
    UINT64* psrc,
    UINT64 lengthinuint64s);

extern "C" UINT64 dg_sqrtuint64s( 
    UINT64* pr,
    UINT64* psqrtr,
    UINT64* prguess,
    UINT64* prguesscopy,
    UINT64 lengthinuint64s,  // of pr, psqrtr, prguess, and prguesscopy
    UINT64 fractionaluint64s);

extern "C" UINT128 dg_findhighestbitinuint64s( 
    UINT64* psrc,
    UINT64 lengthinuint64s); 
    
extern "C" UINT64 dg_compareuint64sreverse( 
    UINT64* pdest,
    UINT64* psrc,
    UINT64 lengthinuint64s); 
    
extern "C" UINT64 dg_copyuint64s( 
    UINT64* pdest,
    UINT64* psrc,
    UINT64 lengthinuint64s); 
    
extern "C" UINT64 dg_clearuint64s(
    UINT64* pdest,
    UINT64 lengthinuint64s);
    
void dg_printarray(
    UINT64* px,
    UINT64 lengthinuint64s,
    UINT64 fractionaluint64s)
{
    UINT64 u;
    UINT64 x;
    
    printf("0x ");
    
    u = lengthinuint64s;
    
    while(true)
    {
        u--;
        x = px[u];
        printf(" %08x%08x",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        if (u == fractionaluint64s)
        {
            break;
        }
    }
    
    printf(" . ");
    
    while(true)
    {
        u--;
        x = px[u];
        printf(" %08x%08x",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        if (u == 0)
        {
            break;
        }
    }
    
    printf("\n");
}


void testdg_copyuint64s()
{
    UINT64 pdest[64];
    UINT64 psrc[64];
    UINT64 lengthinuint64s;
    UINT64 x;
    
    printf("  testing dg_copyuint64s\n");
    
    printf("  testing dg_copyuint64s length 0 case \n");
    
    pdest[0] = 1;
    pdest[1] = 2;
    pdest[2] = 3;
    
    psrc[0] = 4;
    psrc[1] = 5;
    psrc[2] = 6;
    
    dg_copyuint64s(
        pdest,
        psrc,
        0); 
    
    x = pdest[0];
    if (x != 1)
    {
        printf("  FAIL! dg_copyuint64s length 0 case - expected pdest[0] = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    printf("  testing dg_copyuint64s length 3 case \n");
    
    dg_copyuint64s(
        pdest,
        psrc,
        3); 
    
    x = pdest[0];
    if (x != 4)
    {
        printf("  FAIL! dg_copyuint64s length 0 case - expected pdest[0] = 4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = pdest[1];
    if (x != 5)
    {
        printf("  FAIL! dg_copyuint64s length 0 case - expected pdest[1] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = pdest[2];
    if (x != 6)
    {
        printf("  FAIL! dg_copyuint64s length 0 case - expected pdest[2] = 6, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}
    
void testdg_compareuint64sreverse()
{
    UINT64 pdest[64];
    UINT64 psrc[64];
    UINT64 lengthinuint64s;
    UINT64 x;
    
    printf("  testing dg_compareuint64sreverse\n");
    
    printf("  testing dg_compareuint64sreverse length 0 case \n");
    
    pdest[0] = 0;
    pdest[1] = 0;
    pdest[2] = 0;
    
    psrc[0] = 0;
    psrc[1] = 0;
    psrc[2] = 0;
    
    x = dg_compareuint64sreverse(
        pdest,
        psrc,
        0); 
    
    if (x != (UINT64)-2)
    {
        printf("  FAIL! dg_compareuint64sreverse length 0 case - expected flag = -2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    pdest[0] = 0;
    pdest[1] = 0;
    pdest[2] = 0;
    
    psrc[0] = 0;
    psrc[1] = 0;
    psrc[2] = 0;
    
    x = dg_compareuint64sreverse(
        pdest,
        psrc,
        3); 
    
    if (x != 0)
    {
        printf("  FAIL! dg_compareuint64sreverse length 3 0 == 0 case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    pdest[0] = 1;
    pdest[1] = 0;
    pdest[2] = 0;
    
    psrc[0] = 1;
    psrc[1] = 0;
    psrc[2] = 0;
    
    x = dg_compareuint64sreverse(
        pdest,
        psrc,
        3); 
    
    if (x != 0)
    {
        printf("  FAIL! dg_compareuint64sreverse length 3 0 0 1 == 0 0 1 case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    pdest[0] = 0;
    pdest[1] = 1;
    pdest[2] = 0;
    
    psrc[0] = 0;
    psrc[1] = 1;
    psrc[2] = 0;
    
    x = dg_compareuint64sreverse(
        pdest,
        psrc,
        3); 
    
    if (x != 0)
    {
        printf("  FAIL! dg_compareuint64sreverse length 3 0 1 0 == 0 1 0 case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    pdest[0] = 0;
    pdest[1] = 0;
    pdest[2] = 1;
    
    psrc[0] = 0;
    psrc[1] = 0;
    psrc[2] = 1;
    
    x = dg_compareuint64sreverse(
        pdest,
        psrc,
        3); 
    
    if (x != 0)
    {
        printf("  FAIL! dg_compareuint64sreverse length 3 0 0 1 == 0 0 1 case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    pdest[0] = 0;
    pdest[1] = 0;
    pdest[2] = 2;
    
    psrc[0] = 0;
    psrc[1] = 0;
    psrc[2] = 1;
    
    x = dg_compareuint64sreverse(
        pdest,
        psrc,
        3); 
    
    if (x != 1)
    {
        printf("  FAIL! dg_compareuint64sreverse length 3 0 0 1 == 0 0 2 case - expected flag = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    pdest[0] = 0;
    pdest[1] = 0;
    pdest[2] = 0;
    
    psrc[0] = 0;
    psrc[1] = 0;
    psrc[2] = 1;
    
    x = dg_compareuint64sreverse(
        pdest,
        psrc,
        3); 
    
    if (x != (UINT64)-1)
    {
        printf("  FAIL! dg_compareuint64sreverse length 3 0 0 1 == 0 0 0 case - expected flag = -1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    pdest[0] = 0;
    pdest[1] = 0;
    pdest[2] = 0;
    
    psrc[0] = 0;
    psrc[1] = 1;
    psrc[2] = 0;
    
    x = dg_compareuint64sreverse(
        pdest,
        psrc,
        3); 
    
    if (x != (UINT64)-1)
    {
        printf("  FAIL! dg_compareuint64sreverse length 3 0 1 0 == 0 0 0 case - expected flag = -1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    pdest[0] = 0;
    pdest[1] = 0;
    pdest[2] = 0;
    
    psrc[0] = 1;
    psrc[1] = 0;
    psrc[2] = 0;
    
    x = dg_compareuint64sreverse(
        pdest,
        psrc,
        3); 
    
    if (x != (UINT64)-1)
    {
        printf("  FAIL! dg_compareuint64sreverse length 3 1 0 0 == 0 0 0 case - expected flag = -1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    pdest[0] = 0;
    pdest[1] = 0;
    pdest[2] = 1;
    
    psrc[0] = 1;
    psrc[1] = 0;
    psrc[2] = 0;
    
    x = dg_compareuint64sreverse(
        pdest,
        psrc,
        3); 
    
    if (x != 1)
    {
        printf("  FAIL! dg_compareuint64sreverse length 3 1 0 0 == 1 0 0 case - expected flag = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    pdest[0] = 0;
    pdest[1] = 0;
    pdest[2] = 0;
    pdest[3] = 0;
    
    psrc[0] = 1;
    psrc[1] = 0;
    psrc[2] = 0;
    psrc[3] = 1;
    
    x = dg_compareuint64sreverse(
        pdest + 1,
        psrc + 1,
        2); 
    
    if (x != 0)
    {
        printf("  FAIL! dg_compareuint64sreverse length 2 0 0 == 0 0 case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}
    
void testdg_findhighestbitinuint64s()
{
    UINT64 pr[64];
    UINT64 lengthinuint64s;
    UINT64 x;
    UINT128 y;
    
    printf("  testing dg_findhighestbitinuint64s\n");
    
    printf("  testing dg_findhighestbitinuint64s length 3 n = 0 0 0 case \n");
    
    pr[0] = 0;
    pr[1] = 0;
    pr[2] = 0;
    
    y = dg_findhighestbitinuint64s(
        pr,
        3); 
    
    x = ((UINT64*)(&y))[0];
    if (x != (UINT64)-1)
    {
       
       printf("  FAIL! dg_findhighestbitinuint64s length 3 n = 0 0 0 case - expected y[0] = -1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    if (pr[1] != 0)
    {
       printf("  FAIL! dg_findhighestbitinuint64s length 3 n = 0 0 0 case - expected y[1] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    printf("  testing dg_findhighestbitinuint64s length 3 n = 1 0 0 case \n");
    
    pr[0] = 0;
    pr[1] = 0;
    pr[2] = 1;
    
    y = dg_findhighestbitinuint64s(
        pr,
        3); 
    
    x = ((UINT64*)(&y))[0];
    if (x != 0)
    {
       
       printf("  FAIL! dg_findhighestbitinuint64s length 3 n = 1 0 0 case - expected y[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    if (x != 2)
    {
       printf("  FAIL! dg_findhighestbitinuint64s length 3 n = 1 0 0 case - expected y[1] = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    printf("  testing dg_findhighestbitinuint64s length 3 n = 2 0 0 case \n");
    
    pr[0] = 0;
    pr[1] = 0;
    pr[2] = 2;
    
    y = dg_findhighestbitinuint64s(
        pr,
        3); 
    
    x = ((UINT64*)(&y))[0];
    if (x != 1)
    {
       
       printf("  FAIL! dg_findhighestbitinuint64s length 3 n = 2 0 0 case - expected y[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    if (x != 2)
    {
       printf("  FAIL! dg_findhighestbitinuint64s length 3 n = 2 0 0 case - expected y[1] = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}

void testdg_sqrtuint64s()
{
    UINT64 pr[64];
    UINT64 psqrtr[64];
    UINT64 prguess[64];
    UINT64 prguesscopy[64];
    UINT64 x;
    UINT64 flag;
    
    printf("  testing dg_sqrtuint64s\n");
    
    printf("  testing dg_sqrtuint64s sqrt 0 . 0 0 case \n");
    
    pr[0] = 0;
    pr[1] = 0;
    pr[2] = 0;
    
    flag = dg_sqrtuint64s(
        pr,
        psqrtr,
        prguess,
        prguesscopy,
        3,  // length in uint64s
        2); // fractional uint64s
        
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 0 . 0 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[0] != 0)
    {
       x = psqrtr[0];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 0 . 0 0 success case - expected psqrt[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[1] != 0)
    {
       x = psqrtr[1];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 0 . 0 0 success case - expected psqrt[1] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[2] != 0)
    {
       x = psqrtr[2];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 0 . 0 0 success case - expected psqrt[2] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    printf("  testing dg_sqrtuint64s length 3 sqrt 1 . 0 0 success case\n");
    
    pr[0] = 0;
    pr[1] = 0;
    pr[2] = 1;
    
    flag = dg_sqrtuint64s(
        pr,
        psqrtr,
        prguess,
        prguesscopy,
        3,  // length in uint64s
        2); // fractional uint64s
        
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 1 . 0 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
    }
    
    if (psqrtr[0] != 0)
    {
       x = psqrtr[0];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 1 . 0 0 success case - expected psqrt[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        x = prguess[0];
        printf("   rguess[0] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguess[1];
        printf("   rguess[1] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguess[2];
        printf("   rguess[2] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguesscopy[0];
        printf("   rguesscopy[0] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguesscopy[1];
        printf("   rguesscopy[1] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguesscopy[2];
        printf("   rguesscopy[2] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[1] != 0)
    {
       x = psqrtr[1];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 1 . 0 0 success case - expected psqrt[1] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        x = prguess[0];
        printf("   rguess[0] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguess[1];
        printf("   rguess[1] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguess[2];
        printf("   rguess[2] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguesscopy[0];
        printf("   rguesscopy[0] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguesscopy[1];
        printf("   rguesscopy[1] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguesscopy[2];
        printf("   rguesscopy[2] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[2] != 1)
    {
       x = psqrtr[2];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 1 . 0 0 success case - expected psqrt[2] = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        x = prguess[0];
        printf("   rguess[0] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguess[1];
        printf("   rguess[1] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguess[2];
        printf("   rguess[2] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguesscopy[0];
        printf("   rguesscopy[0] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguesscopy[1];
        printf("   rguesscopy[1] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
          
        x = prguesscopy[2];
        printf("   rguesscopy[2] = 0x%08x%08x\n",
          ((UINT32*)(&x))[1],
          ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    printf("  testing dg_sqrtuint64s length 3 sqrt 4 . 0 0 success case\n");
    
    pr[0] = 0;
    pr[1] = 0;
    pr[2] = 4;
    
    flag = dg_sqrtuint64s(
        pr,
        psqrtr,
        prguess,
        prguesscopy,
        3,  // length in uint64s
        2); // fractional uint64s
    
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 4 . 0 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[0] != 0)
    {
       x = psqrtr[0];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 4 . 0 0 success case - expected psqrt[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[1] != 0)
    {
       x = psqrtr[1];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 4 . 0 0 success case - expected psqrt[1] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[2] != 2)
    {
       x = psqrtr[2];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 4 . 0 0 success case - expected psqrt[2] = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    printf("  testing dg_sqrtuint64s length 3 sqrt 9 . 0 0 success case\n");
    
    pr[0] = 0;
    pr[1] = 0;
    pr[2] = 9;
    
    flag = dg_sqrtuint64s(
        pr,
        psqrtr,
        prguess,
        prguesscopy,
        3,  // length in uint64s
        2); // fractional uint64s
        
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 9 . 0 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[0] != 0)
    {
       x = psqrtr[0];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 9 . 0 0 success case - expected psqrt[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[1] != 0)
    {
       x = psqrtr[1];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 9 . 0 0 success case - expected psqrt[1] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[2] != 3)
    {
       x = psqrtr[2];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 9 . 0 0 success case - expected psqrt[2] = 3, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    printf("  testing dg_sqrtuint64s length 3 sqrt 16 . 0 0 success case\n");
    
    pr[0] = 0;
    pr[1] = 0;
    pr[2] = 16;
    
    flag = dg_sqrtuint64s(
        pr,
        psqrtr,
        prguess,
        prguesscopy,
        3,  // length in uint64s
        2); // fractional uint64s
        
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 16 . 0 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[0] != 0)
    {
       x = psqrtr[0];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 16 . 0 0 success case - expected psqrt[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[1] != 0)
    {
       x = psqrtr[1];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 16 . 0 0 success case - expected psqrt[1] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[2] != 4)
    {
       x = psqrtr[2];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 16 . 0 0 success case - expected psqrt[2] = 4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    printf("  testing dg_sqrtuint64s length 3 sqrt 49 . 0 0 success case\n");
    
    pr[0] = 0;
    pr[1] = 0;
    pr[2] = 49;
    
    flag = dg_sqrtuint64s(
        pr,
        psqrtr,
        prguess,
        prguesscopy,
        3,  // length in uint64s
        2); // fractional uint64s
        
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 49 . 0 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[0] != 0)
    {
       x = psqrtr[0];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 49 . 0 0 success case - expected psqrt[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[1] != 0)
    {
       x = psqrtr[1];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 49 . 0 0 success case - expected psqrt[1] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[2] != 7)
    {
       x = psqrtr[2];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 49 . 0 0 success case - expected psqrt[2] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    printf("  testing dg_sqrtuint64s length 3 sqrt 25 . 0 0 success case\n");
    
    pr[0] = 0;
    pr[1] = 0;
    pr[2] = 25;
    
    flag = dg_sqrtuint64s(
        pr,
        psqrtr,
        prguess,
        prguesscopy,
        3,  // length in uint64s
        2); // fractional uint64s
        
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 25 . 0 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
       x = psqrtr[0];
       printf("   sqrtr[0] = 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
       x = psqrtr[1];
       printf("   sqrtr[1] = 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
       x = psqrtr[2];
       printf("   sqrtr[2] = 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
       x = prguess[0];
       printf("   rguess[0] = 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
       x = prguess[1];
       printf("   rguess[1] = 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
       x = prguess[2];
       printf("   rguess[2] = 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
       x = prguesscopy[0];
       printf("   rguesscopy[0] = 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
       x = prguesscopy[1];
       printf("   rguesscopy[1] = 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
       x = prguesscopy[2];
       printf("   rguesscopy[2] = 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
       return;
    }
    
    if (psqrtr[0] != 0)
    {
       x = psqrtr[0];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 25 . 0 0 success case - expected psqrt[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[1] != 0)
    {
       x = psqrtr[1];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 25 . 0 0 success case - expected psqrt[1] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[2] != 5)
    {
       x = psqrtr[2];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 25 . 0 0 success case - expected psqrt[2] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    printf("  testing dg_sqrtuint64s length 3 sqrt 36 . 0 0 success case\n");
    
    pr[0] = 0;
    pr[1] = 0;
    pr[2] = 36;
    
    flag = dg_sqrtuint64s(
        pr,
        psqrtr,
        prguess,
        prguesscopy,
        3,  // length in uint64s
        2); // fractional uint64s
        
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 36 . 0 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[0] != 0)
    {
       x = psqrtr[0];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 36 . 0 0 success case - expected psqrt[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[1] != 0)
    {
       x = psqrtr[1];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 36 . 0 0 success case - expected psqrt[1] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[2] != 6)
    {
       x = psqrtr[2];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 36 . 0 0 success case - expected psqrt[2] = 6, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    printf("  testing dg_sqrtuint64s length 3 sqrt 0 . 0x4000000000000000 0 success case\n");
    
    pr[0] = 0;
    pr[1] = 0x4000000000000000;
    pr[2] = 0;
    
    flag = dg_sqrtuint64s(
        pr,
        psqrtr,
        prguess,
        prguesscopy,
        3,  // length in uint64s
        2); // fractional uint64s
        
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 0 . 0x4000000000000000 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[0] != 0)
    {
       x = psqrtr[0];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 0 . 0x4000000000000000 0 success case - expected psqrt[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[1] != 0x8000000000000000)
    {
       x = psqrtr[1];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 0 . 0x4000000000000000 0 success case - expected psqrt[1] = 0x8000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[2] != 0)
    {
       x = psqrtr[2];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 0 . 0x4000000000000000 0 success case - expected psqrt[2] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    /*
    printf("  testing dg_sqrtuint64s length 3 sqrt 0 . 0x9000000000000000 0 success case\n");
    
    pr[0] = 0;
    pr[1] = 0x9000000000000000;
    pr[2] = 0;
    
    flag = dg_sqrtuint64s(
        pr,
        psqrtr,
        prguess,
        prguesscopy,
        3,  // length in uint64s
        2); // fractional uint64s
        
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 0 . 0x9000000000000000 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[0] != 0)
    {
       x = psqrtr[0];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 0 . 0x9000000000000000 0 success case - expected psqrt[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[1] != 0xC000000000000000)
    {
       x = psqrtr[1];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 0 . 0x9000000000000000 0 success case - expected psqrt[1] = 0xC000000000000000, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[2] != 0)
    {
       x = psqrtr[2];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 0 . 0x9000000000000000 0 success case - expected psqrt[2] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    */
    printf("  testing dg_sqrtuint64s length 2 sqrt 5 . 0 0 success case\n");
    
    pr[0] = 0;
    pr[1] = 5;
    pr[2] = 0;
    
    flag = dg_sqrtuint64s(
        pr,
        psqrtr,
        prguess,
        prguesscopy,
        3,  // length in uint64s
        1); // fractional uint64s
        
    if (flag != (UINT64)-1)
    {
       x = flag;
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 5 . 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[0] != 0x3c6ef37200000000)
    {
       x = psqrtr[0];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 5 . 0 success case - expected psqrt[0] = 0x3c6ef372, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
       x = psqrtr[1];
       printf(" psqrt[1] = 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
       x = psqrtr[2];
       printf(" psqrt[2] = 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[1] != 2)
    {
       x = psqrtr[1];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 5 . 0 success case - expected psqrt[1] = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (psqrtr[2] != 0)
    {
       x = psqrtr[2];
       printf("  FAIL! dg_sqrtuint64s length 3 sqrt of 5 . 0 success case - expected psqrt[2] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    dg_clearuint64s(
        pr,
        16);
    
    pr[12] = 5;
    
    flag = dg_sqrtuint64s(
        pr,
        psqrtr,
        prguess,
        prguesscopy,
        16,  // length in uint64s
        12); // fractional uint64s
        
    if (flag != (UINT64)-1)
    {
       x = flag;
       printf("  FAIL! dg_sqrtuint64s length 16 sqrt of 5 . 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    printf(" sqrt(5) = ");
    
    dg_printarray(
        psqrtr,
        16,
        12);
    
    printf("\n");
}

/*
void testdg_powerof2toindex()
{
    UINT64 destination[64];
    UINT128 y;
    UINT64 x;
    
    printf("  testing dg_powerof2toindex\n");

    y = dg_powerof2toindex(
        0,
        0,
        0);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0)
    {
       printf("  FAIL! dg_powerof2toindex bitoffset 0 uint64offset 0 fractionaluint64s 0 - expected bitoffset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 0)
    {
       printf("  FAIL! dg_powerof2toindex bitoffset 0 uint64offset 0 fractionaluint64s 0 - expected uint64offset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_powerof2toindex(
        1,
        0,
        0);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 1)
    {
       printf("  FAIL! dg_powerof2toindex bitoffset 1 uint64offset 0 fractionaluint64s 0 - expected bitoffset = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 0)
    {
       printf("  FAIL! dg_powerof2toindex bitoffset 1 uint64offset 0 fractionaluint64s 0 - expected uint64offset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_powerof2toindex(
        0,
        1,
        0);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0)
    {
       printf("  FAIL! dg_powerof2toindex bitoffset 0 uint64offset 1 fractionaluint64s 0 - expected bitoffset = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 1)
    {
       printf("  FAIL! dg_powerof2toindex bitoffset 0 uint64offset 1 fractionaluint64s 0 - expected uint64offset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_powerof2toindex(
        0x3f,
        (UINT64)-1,
        1);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0)
    {
       printf("  FAIL! dg_powerof2toindex bitoffset 0x3f uint64offset -1 fractionaluint64s 1 - expected bitoffset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 0)
    {
       printf("  FAIL! dg_powerof2toindex bitoffset 0x3f uint64offset -1 fractionaluint64s 1 - expected uint64offset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_powerof2toindex(
        1,
        (UINT64)-2,
        3);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0x3e)
    {
       printf("  FAIL! dg_indextopowerof2 bitoffset 1 uint64offset -2 fractionaluint64s 3 - expected bitoffset = 0x3e, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 1)
    {
       printf("  FAIL! dg_indextopowerof2 bitoffset 1 uint64offset -2 fractionaluint64s 3 - expected uint64offset = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}
    
void testdg_indextopowerof2()
{
    UINT64 destination[64];
    UINT128 y;
    UINT64 x;
    
    printf("  testing dg_indextopowerof2\n");

    y = dg_indextopowerof2(
        0,
        0,
        0);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0)
    {
       printf("  FAIL! dg_indextopowerof2 bitoffset 0 uint64offset 0 fractionaluint64s 0 - expected bitoffset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 0)
    {
       printf("  FAIL! dg_indextopowerof2 bitoffset 0 uint64offset 0 fractionaluint64s 0 - expected uint64offset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_indextopowerof2(
        1,
        0,
        0);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 1)
    {
       printf("  FAIL! dg_indextopowerof2 bitoffset 1 uint64offset 0 fractionaluint64s 0 - expected bitoffset = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 0)
    {
       printf("  FAIL! dg_indextopowerof2 bitoffset 1 uint64offset 0 fractionaluint64s 0 - expected uint64offset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_indextopowerof2(
        0,
        1,
        0);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0)
    {
       printf("  FAIL! dg_indextopowerof2 bitoffset 0 uint64offset 1 fractionaluint64s 0 - expected bitoffset = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 1)
    {
       printf("  FAIL! dg_indextopowerof2 bitoffset 0 uint64offset 1 fractionaluint64s 0 - expected uint64offset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_indextopowerof2(
        0,
        0,
        1);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0x3f)
    {
       printf("  FAIL! dg_indextopowerof2 bitoffset 0 uint64offset 0 fractionaluint64s 1 - expected bitoffset = 0x3f, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != (UINT64)-1)
    {
       printf("  FAIL! dg_indextopowerof2 bitoffset 0 uint64offset 0 fractionaluint64s 1 - expected uint64offset = -1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_indextopowerof2(
        0x3e,
        1,
        3);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 1)
    {
       printf("  FAIL! dg_indextopowerof2 bitoffset 0x3e uint64offset 1 fractionaluint64s 3 - expected bitoffset = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != (UINT64)-2)
    {
       printf("  FAIL! dg_indextopowerof2 bitoffset 0x3e uint64offset 1 fractionaluint64s 3 - expected uint64offset = -2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}
*/
void testdg_getshiftdoubled()
{
    UINT64 destination[64];
    UINT128 y;
    UINT64 x;
    
    printf("  testing dg_getshiftdoubled\n");

    y = dg_getshiftdoubled(
        0,  // index in bits
        0,  // index in uint64s
        0); // fractional uint64s
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0 uint64offset 0 fractionaluint64s 0 - expected bitoffset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 0)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0 uint64offset 0 fractionaluint64s 0 - expected uint64offset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_getshiftdoubled(
        1,
        0,
        0);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 2)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 1 uint64offset 0 fractionaluint64s 0 - expected bitoffset = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 0)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 1 uint64offset 0 fractionaluint64s 0 - expected uint64offset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_getshiftdoubled(
        0,
        1,
        0);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0 uint64offset 1 fractionaluint64s 0 - expected bitoffset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 2)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0 uint64offset 1 fractionaluint64s 0 - expected uint64offset = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_getshiftdoubled(
        0,  // index in bits
        2,  // index in uint64s
        1); // fractional uint64s
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0 uint64offset 2 fractionaluint64s 1 - expected bitoffset = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 3)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0 uint64offset 2 fractionaluint64s 1 - expected uint64offset = 3, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_getshiftdoubled(
        2, // index in bits
        5, // index in uint64s
        3); // fractional uint64s
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 4)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 2 uint64offset 5 fractionaluint64s 3 - expected bitoffset = 4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 7)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 2 uint64offset 5 fractionaluint64s 3 - expected uint64offset = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_getshiftdoubled(
        0x39, // index in bits
        5,    // index in uint64s
        6);   // fractional uint64s
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0x32)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0x39 uint64offset 5 fractionaluint64s 6 - expected bitoffset = 0x32, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 5)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0x39 uint64offset 5 fractionaluint64s 6 - expected uint64offset = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_getshiftdoubled(
        0x1F,
        5,
        6);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0x3E)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0x1F uint64offset 5 fractionaluint64s 6 - expected bitoffset = 0x3E, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 4)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0x1F uint64offset 5 fractionaluint64s 6 - expected uint64offset = 4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_getshiftdoubled(
        0x21,
        2,
        1);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 2)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0x21 uint64offset 2 fractionaluint64s 1 - expected bitoffset = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 4)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0x21 uint64offset 2 fractionaluint64s 1 - expected uint64offset = 4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    y = dg_getshiftdoubled(
        1,
        2,
        2);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 2)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 1 uint64offset 1 fractionaluint64s 2 - expected bitoffset = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 2)
    {
       printf("  FAIL! dg_getshiftdoubled bitoffset 0x21 uint64offset 1 fractionaluint64s 2 - expected uint64offset = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}
    
void dg_testdg_getshiftplusone()
{
    UINT64 destination[64];
    UINT128 y;
    UINT64 x;
    
    printf("  testing dg_getshiftplusone\n");

    y = dg_getshiftplusone(
        0,
        0);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 1)
    {
       printf("  FAIL! dg_getshiftplusone bitoffset 0 uint64offset 0 - expected bitoffset = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 0)
    {
       printf("  FAIL! dg_getshiftplusone bitoffset 0 uint64offset 0 - expected uint64offset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_getshiftplusone(
        63,
        0);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0)
    {
       printf("  FAIL! dg_getshiftplusone bitoffset 63 uint64offset 0 - expected bitoffset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 1)
    {
       printf("  FAIL! dg_getshiftplusone bitoffset 63 uint64offset 0 - expected uint64offset = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_getshiftplusone(
        63,
        1);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0)
    {
       printf("  FAIL! dg_getshiftplusone bitoffset 63 uint64offset 1 - expected bitoffset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 2)
    {
       printf("  FAIL! dg_getshiftplusone bitoffset 63 uint64offset 1 - expected uint64offset = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    y = dg_getshiftplusone(
        63,
        -1);
        
    x = ((UINT64*)(&y))[0];
    
    if (x != 0)
    {
       printf("  FAIL! dg_getshiftplusone bitoffset 63 uint64offset -1 - expected bitoffset = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    x = ((UINT64*)(&y))[1];
    
    if (x != 0)
    {
       printf("  FAIL! dg_getshiftplusone bitoffset 63 uint64offset -1 - expected uint64offset = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}
     
void dg_testdg_addbitinuint64s()
{
    UINT64 destination[64];
    UINT64 x;
    
    printf("  testing dg_addbitinuint64s\n");
    
    printf("  testing dg_addbitinuint64s length 0 success case\n");
    
    destination[0] = 5;
    destination[1] = 7;
    destination[2] = 9;

    dg_addbitinuint64s(
        destination,
        0,
        0);
    
    if (destination[0] != 5)
    {
       x = destination[0];
       printf("  FAIL! dg_addbitinuint64s length 0 success case - expected destination[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 7)
    {
       x = destination[1];
       printf("  FAIL! dg_addbitinuint64s length 0 success case - expected destination[0] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 9)
    {
       x = destination[2];
       printf("  FAIL! dg_addbitinuint64s length 0 success case - expected destination[0] = 9, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    printf("  testing dg_addbitinuint64s length 3 pos 0 success case\n");
    
    destination[0] = 5;
    destination[1] = 7;
    destination[2] = 9;

    dg_addbitinuint64s(
        destination,
        3,
        0);
    
    if (destination[0] != 6)
    {
       x = destination[0];
       printf("  FAIL! dg_addbitinuint64s length 3 pos 0 success case - expected destination[0] = 6, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 7)
    {
       x = destination[1];
       printf("  FAIL! dg_addbitinuint64s length 3 pos 0 success case - expected destination[1] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 9)
    {
       x = destination[2];
       printf("  FAIL! dg_addbitinuint64s length 3 pos 0 success case - expected destination[2] = 9, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    printf("  testing dg_addbitinuint64s length 3 pos 1 success case\n");
    
    destination[0] = 3;
    destination[1] = 7;
    destination[2] = 9;

    dg_addbitinuint64s(
        destination,
        3,
        1);
    
    if (destination[0] != 5)
    {
       x = destination[0];
       printf("  FAIL! dg_addbitinuint64s length 3 pos 1 success case - expected destination[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 7)
    {
       x = destination[1];
       printf("  FAIL! dg_addbitinuint64s length 3 pos 1 success case - expected destination[1] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 9)
    {
       x = destination[2];
       printf("  FAIL! dg_addbitinuint64s length 3 pos 1 success case - expected destination[2] = 9, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    printf("  testing dg_addbitinuint64s length 3 pos 64 success case\n");
    
    destination[0] = 5;
    destination[1] = 7;
    destination[2] = 9;

    dg_addbitinuint64s(
        destination,
        3,
        64);
    
    if (destination[0] != 5)
    {
       x = destination[0];
       printf("  FAIL! dg_addbitinuint64s length 3 pos 64 success case - expected destination[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 8)
    {
       x = destination[1];
       printf("  FAIL! dg_addbitinuint64s length 3 pos 64 success case - expected destination[1] = 8, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 9)
    {
       x = destination[2];
       printf("  FAIL! dg_addbitinuint64s length 3 pos 64 success case - expected destination[2] = 9, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    printf("  testing dg_addbitinuint64s length 3 pos 127 success case\n");
    
    destination[0] = 5;
    destination[1] = 0x8000000000000007;
    destination[2] = 9;

    dg_addbitinuint64s(
        destination,
        3,
        127);
    
    if (destination[0] != 5)
    {
       x = destination[0];
       printf("  FAIL! dg_addbitinuint64s length 3 pos 127 success case - expected destination[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 7)
    {
       x = destination[1];
       printf("  FAIL! dg_addbitinuint64s length 3 pos 127 success case - expected destination[1] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 10)
    {
       x = destination[2];
       printf("  FAIL! dg_addbitinuint64s length 3 pos 127 success case - expected destination[2] = 10, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}
     
void testdg_add2abplusbsquaredtouint64s()
{
    UINT64 source[64];
    UINT64 destination[64];
    UINT64 x;
    UINT64 flag;
    
    printf("  testing dg_add2abplusbsquaredtouint64s\n");
    
    printf("  testing dg_add2abplusbsquaredtouint64s length 0 success case\n");
    
    source[0] = 5;
    source[1] = 0;
    source[2] = 0;
    destination[0] = 3;
    destination[1] = 7;
    destination[2] = 9;

    flag = dg_add2abplusbsquaredtouint64s(
        source,
        destination,
        0,
        0,
        0,
        0);
    
    if (destination[0] != 3)
    {
       x = destination[0];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 0 success case - expected destination[0] = 3, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (flag != (UINT64)-1)
    {
       x = flag;
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 0 success case - expected flag = -1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    printf("  testing dg_add2abplusbsquaredtouint64s length 3 n 0 fractional 0 success case\n");
    
    source[0] = 5;
    source[1] = 0;
    source[2] = 0;
    destination[0] = 3;
    destination[1] = 0;
    destination[2] = 0;

    flag = dg_add2abplusbsquaredtouint64s(
        source,             // pa
        destination,        // pdest
        3,                  // lengthinuint64s
        0,                  // indexinbits
        0,                  // indexinuint64s
        0);                 // fractionaluint64s
        
    
    if (destination[0] != 14)
    {
       x = destination[0];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0 0 fractional 0 success case - expected destination[0] = 14, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 0)
    {
       x = destination[1];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0 0 fractional 0 success case - expected destination[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 0)
    {
       x = destination[2];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0 0 fractional 0 success case - expected destination[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0 0 fractional 0 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    printf("  testing dg_add2abplusbsquaredtouint64s length 3 n 0 2 fractional 2 success case\n");
    
    source[0] = 0;
    source[1] = 0;
    source[2] = 5;
    destination[0] = 3;
    destination[1] = 5;
    destination[2] = 1;

    flag = dg_add2abplusbsquaredtouint64s(
        source,
        destination,
        3,  // length
        0,  // index in bits
        2,  // index in uint64s
        2); // fractional uint64s
        
    // n = 0, b = 2^0 = 1, 2ab = 2a = 10 0 0, b^2 = 1 = 1 0 0 
    
    if (destination[0] != 3)
    {
       x = destination[0];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0 2 fractional 2 success case - expected destination[0] = 3, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 5)
    {
       x = destination[1];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0 2 fractional 2 success case - expected destination[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 12)
    {
       x = destination[2];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0 2 fractional 2 success case - expected destination[0] = 12, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0 2 fractional 2 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    printf("  testing dg_add2abplusbsquaredtouint64s length 3 n 1 2 fractional 2 success case\n");
    
    source[0] = 0;
    source[1] = 0;
    source[2] = 5;  
    destination[0] = 3;
    destination[1] = 5;
    destination[2] = 1; 

    flag = dg_add2abplusbsquaredtouint64s(
        source,
        destination,
        3,
        1,  // position in bits      so n = (2-2)*64 + 1 = 1, b = 2^n = 2
        2,  // position in uint64s
        2); // fractional uint64s
        
        // 2ab = 4 * (5) = (20), b^2 = 4 // this is relative to fractional bits = 2 
    
    if (destination[0] != 3)
    {
       x = destination[0];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 1 2 fractional 2 success case - expected destination[0] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 5)
    {
       x = destination[1];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 1 2 fractional 2 success case - expected destination[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 25)
    {
       x = destination[2];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 1 2 fractional 2 success case - expected destination[0] = 25, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 1 2 fractional 2 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    source[0] = 7;
    source[1] = 4;
    source[2] = 5;  
    destination[0] = 3;
    destination[1] = 5;
    destination[2] = 1; 
    
    flag = dg_add2abplusbsquaredtouint64s(
        source,
        destination,
        3,
        0x3f,
        1,
        2);
        
    // n = -1 so 2ab = just a so 5 4 7 , and b^2 = 2 ^ (2*-1) = 2^-2 // relative to fractional uint64s
    
    
    if (destination[0] != 10)
    {
       x = destination[0];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0x3f 1 fractional 2 success case - expected destination[0] = 10, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 0x4000000000000009)
    {
       x = destination[1];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0x3f 1 fractional 2 success case - expected destination[1] = 0x4000000000000009, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 6)
    {
       x = destination[2];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0x3f 1 fractional 2 success case - expected destination[2] = 6, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0x3f 1 fractional 2 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    source[0] = 7;
    source[1] = 4;
    source[2] = 5;  
    destination[0] = 3;
    destination[1] = 5;
    destination[2] = 1; 
    
    flag = dg_add2abplusbsquaredtouint64s(
        source,
        destination,
        3,
        0x3e,
        1,
        2);
        
    // n = -2 so 2ab = a/2 so 2 0x8000000000000002 3 , and b^2 = 2 ^ (2*-2) = 2^-4 // relative to fractional uint64s
    
    
    if (destination[0] != 6)
    {
       x = destination[0];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0x3e 1 fractional 2 success case - expected destination[0] = 6, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
      x = destination[1];
      printf("  destination[1] = 0x%08x%08x\n",
        ((UINT32*)(&x))[1],
        ((UINT32*)(&x))[0]);
        
      x = destination[2];
      printf("  destination[2] = 0x%08x%08x\n",
        ((UINT32*)(&x))[1],
        ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 0x9000000000000007)
    {
       x = destination[1];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0x3e 1 fractional 2 success case - expected destination[1] = 0x9000000000000007, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 3)
    {
       x = destination[2];
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0x3e 1 fractional 2 success case - expected destination[2] = 3, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (flag != 0)
    {
       x = flag;
       printf("  FAIL! dg_add2abplusbsquaredtouint64s length 3 n 0x3e 1 fractional 2 success case - expected flag = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}
    
void dg_testshladdint64s()
{
    UINT64 source[64];
    UINT64 destination[64];
    UINT64 x;
    
    printf("  testing dg_shladdint64s\n");
    
    // printf("  testing dg_shladduint64s length 0 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;

    dg_shladduint64s(
        source,
        destination,
        0,
        64);
    
    if (destination[0] != 2)
    {
       x = destination[0];
       printf("  FAIL! dg_shladduint64s length 0 success case - expected destination[0] = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (source[0] != 5)
    {
       x = source[0];
       printf("  FAIL! dg_shladduint64s length 0 success case - expected source[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    // printf("  testing dg_shladduint64s length 3 shift 64 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 9;

    dg_shladduint64s(
        source,
        destination,
        3,
        64);
    
    if (destination[0] != 2)
    {
       x = destination[0];
       printf("  FAIL! dg_shladduint64s length 3 shift 64 success case - expected destination[0] = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 9)
    {
       x = destination[1];
       printf("  FAIL! dg_shladduint64s length 3 shift 64 success case - expected destination[1] = 9, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 19)
    {
       x = destination[2];
       printf("  FAIL! dg_shladduint64s length 3 shift 64 success case - expected destination[2] = 19, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 9)
    {
       x = destination[3];
       printf("  FAIL! dg_shladduint64s length 3 shift 64 success case - expected destination[3] = 9, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    // printf("  testing dg_shladduint64s length 3 shift 1 success case\n");
    
    source[0] = 0xC000000000000005;
    source[1] = 0x800000000000000B;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shladduint64s(
        source,
        destination,
        3,
        1);
    
    if (destination[0] != 0x800000000000000C)
    {
       x = destination[0];
       printf("  FAIL! dg_shladduint64s length 3 shift 1 success case - expected destination[0] = 0x800000000000000C, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 0x000000000000001B)
    {
       x = destination[1];
       printf("  FAIL! dg_shladduint64s length 3 shift 1 success case - expected destination[1] = 0x000000000000001B, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 47)
    {
       x = destination[2];
       printf("  FAIL! dg_shladduint64s length 3 shift 1 success case - expected destination[2] = 47, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shladduint64s length 3 shift 1 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    // printf("  testing dg_shladduint64s length 3 shift 0 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shladduint64s(
        source,
        destination,
        3,
        0);
    
    if (destination[0] != 7)
    {
       x = destination[0];
       printf("  FAIL! dg_shladduint64s length 3 shift 0 success case - expected destination[0] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 15)
    {
       x = destination[1];
       printf("  FAIL! dg_shladduint64s length 3 shift 0 success case - expected destination[1] = 15, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 27)
    {
       x = destination[2];
       printf("  FAIL! dg_shladduint64s length 3 shift 0 success case - expected destination[2] = 27, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shladduint64s length 3 shift 0 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    // printf("  testing dg_shladduint64s length 3 shift 192 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shladduint64s(
        source,
        destination,
        3,
        192);
    
    if (destination[0] != 2)
    {
       x = destination[0];
       printf("  FAIL! dg_shladduint64s length 3 shift 192 success case - expected destination[0] = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 4)
    {
       x = destination[1];
       printf("  FAIL! dg_shladduint64s length 3 shift 192 success case - expected destination[1] = 4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 8)
    {
       x = destination[2];
       printf("  FAIL! dg_shladduint64s length 3 shift 192 success case - expected destination[2] = 8, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shladduint64s length 3 shift 192 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    // printf("  testing dg_shladduint64s length 1 shift 4 success case\n");
    
    source[0] = 0x53;
    source[1] = 0xAB;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shladduint64s(
        source,
        destination,
        1,
        4);
    
    if (destination[0] != 0x532)
    {
       x = destination[0];
       printf("  FAIL! dg_shladduint64s length 1 shift 4 success case - expected destination[0] = 0x532, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 0x4)
    {
       x = destination[1];
       printf("  FAIL! dg_shladduint64s length 1 shift 4 success case - expected destination[1] = 0x4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 0x8)
    {
       x = destination[2];
       printf("  FAIL! dg_shladduint64s length 1 shift 4 success case - expected destination[2] = 0x8, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shladduint64s length 1 shift 4 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}

void dg_testshraddint64s()
{
    UINT64 source[64];
    UINT64 destination[64];
    UINT64 x;
    
    printf("  testing dg_shradduint64s\n");
    
    // printf("  testing dg_shradduint64s length 0 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;

    dg_shradduint64s(
        source,
        destination,
        0,   // length in uint64s
        64); // shift count in bits
    
    if (destination[0] != 2)
    {
       x = destination[0];
       printf("  FAIL! dg_shradduint64s length 0 success case - expected destination[0] = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (source[0] != 5)
    {
       x = source[0];
       printf("  FAIL! dg_shradduint64s length 0 success case - expected source[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    // printf("  testing dg_shradduint64s length 3 shift 64 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 9;

    dg_shradduint64s(
        source,
        destination,
        3,
        64);
    
    if (destination[0] != 13)
    {
       x = destination[0];
       printf("  FAIL! dg_shradduint64s length 3 shift 64 success case - expected destination[0] = 13, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 23)
    {
       x = destination[1];
       printf("  FAIL! dg_shradduint64s length 3 shift 64 success case - expected destination[1] = 23, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 8)
    {
       x = destination[2];
       printf("  FAIL! dg_shradduint64s length 3 shift 64 success case - expected destination[2] = 8, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 9)
    {
       x = destination[3];
       printf("  FAIL! dg_shradduint64s length 3 shift 64 success case - expected destination[3] = 9, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    // printf("  testing dg_shradduint64s length 3 shift 1 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shradduint64s(
        source,
        destination,
        3,
        1);
    
    if (destination[0] != 0x8000000000000004)
    {
       x = destination[0];
       printf("  FAIL! dg_shradduint64s length 3 shift 1 success case - expected destination[0] = 0x8000000000000004, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 0x8000000000000009)
    {
       x = destination[1];
       printf("  FAIL! dg_shradduint64s length 3 shift 1 success case - expected destination[1] = 0x8000000000000009, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 17)
    {
       x = destination[2];
       printf("  FAIL! dg_shradduint64s length 3 shift 1 success case - expected destination[2] = 17, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shradduint64s length 3 shift 1 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    // printf("  testing dg_shradduint64s length 3 shift 0 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shradduint64s(
        source,
        destination,
        3,
        0);
    
    if (destination[0] != 7)
    {
       x = destination[0];
       printf("  FAIL! dg_shradduint64s length 3 shift 0 success case - expected destination[0] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 15)
    {
       x = destination[1];
       printf("  FAIL! dg_shradduint64s length 3 shift 0 success case - expected destination[1] = 15, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 27)
    {
       x = destination[2];
       printf("  FAIL! dg_shradduint64s length 3 shift 0 success case - expected destination[2] = 27, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shradduint64s length 3 shift 0 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shradduint64ssub(
        source,
        destination,
        3,
        0,
        0);
    
    if (destination[0] != 7)
    {
       x = destination[0];
       printf("  FAIL! dg_shradduint64ssub length 3 shift 0 0 success case - expected destination[0] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 15)
    {
       x = destination[1];
       printf("  FAIL! dg_shradduint64ssub length 3 shift 0 0 success case - expected destination[1] = 15, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 27)
    {
       x = destination[2];
       printf("  FAIL! dg_shradduint64ssub length 3 shift 0 0 success case - expected destination[2] = 27, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shradduint64ssub length 3 shift 0 0 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    // printf("  testing dg_shradduint64s length 3 shift 192 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shradduint64s(
        source,
        destination,
        3,
        192);
    
    if (destination[0] != 2)
    {
       x = destination[0];
       printf("  FAIL! dg_shradduint64s length 3 shift 192 success case - expected destination[0] = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 4)
    {
       x = destination[1];
       printf("  FAIL! dg_shradduint64s length 3 shift 192 success case - expected destination[1] = 4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 8)
    {
       x = destination[2];
       printf("  FAIL! dg_shradduint64s length 3 shift 192 success case - expected destination[2] = 8, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shradduint64s length 3 shift 192 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    // printf("  testing dg_shradduint64s length 1 shift 4 success case\n");
    
    source[0] = 0x53;
    source[1] = 0xAB;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shradduint64s(
        source,
        destination,
        1,
        4);
    
    if (destination[0] != 7)
    {
       x = destination[0];
       printf("  FAIL! dg_shradduint64s length 1 shift 4 success case - expected destination[0] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 4)
    {
       x = destination[1];
       printf("  FAIL! dg_shradduint64s length 1 shift 4 success case - expected destination[1] = 4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 8)
    {
       x = destination[2];
       printf("  FAIL! dg_shradduint64s length 1 shift 4 success case - expected destination[2] = 8, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shradduint64s length 1 shift 4 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}

void dg_testshluint64s()
{
    UINT64 source[64];
    UINT64 destination[64];
    UINT64 x;
    
    printf("  testing dg_shluint64s\n");
    
    // printf("  testing dg_shluint64s length 0 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;

    dg_shluint64s(
        source,
        destination,
        0,
        64);
    
    if (destination[0] != 2)
    {
       x = destination[0];
       printf("  FAIL! dg_shluint64s length 0 success case - expected destination[0] = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (source[0] != 5)
    {
       x = source[0];
       printf("  FAIL! dg_shluint64s length 0 success case - expected source[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    // printf("  testing dg_shluint64s length 3 shift 64 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 9;

    dg_shluint64s(
        source,
        destination,
        3,
        64);
    
    if (destination[0] != 0)
    {
       x = destination[0];
       printf("  FAIL! dg_shluint64s length 3 shift 64 success case - expected destination[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 5)
    {
       x = destination[1];
       printf("  FAIL! dg_shluint64s length 3 shift 64 success case - expected destination[1] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 11)
    {
       x = destination[2];
       printf("  FAIL! dg_shluint64s length 3 shift 64 success case - expected destination[2] = 11, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 9)
    {
       x = destination[3];
       printf("  FAIL! dg_shluint64s length 3 shift 64 success case - expected destination[3] = 9, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    // printf("  testing dg_shluint64s length 3 shift 1 success case\n");
    
    source[0] = 0x8000000000000005;
    source[1] = 0xC00000000000000B;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shluint64s(
        source,
        destination,
        3,
        1);
    
    if (destination[0] != 0x0A)
    {
       x = destination[0];
       printf("  FAIL! dg_shluint64s length 3 shift 1 success case - expected destination[0] = 0x0A, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 0x8000000000000017)
    {
       x = destination[1];
       printf("  FAIL! dg_shluint64s length 3 shift 1 success case - expected destination[1] = 0x8000000000000017, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 39)
    {
       x = destination[2];
       printf("  FAIL! dg_shluint64s length 3 shift 1 success case - expected destination[2] = 39, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shluint64s length 3 shift 1 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    // printf("  testing dg_shluint64s length 3 shift 0 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shluint64s(
        source,
        destination,
        3,
        0);
    
    if (destination[0] != 5)
    {
       x = destination[0];
       printf("  FAIL! dg_shluint64s length 3 shift 0 success case - expected destination[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 11)
    {
       x = destination[1];
       printf("  FAIL! dg_shluint64s length 3 shift 0 success case - expected destination[1] = 11, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 19)
    {
       x = destination[2];
       printf("  FAIL! dg_shluint64s length 3 shift 0 success case - expected destination[2] = 19, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shluint64s length 3 shift 0 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    // printf("  testing dg_shluint64s length 3 shift 192 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shluint64s(
        source,
        destination,
        3,
        192);
    
    if (destination[0] != 0)
    {
       x = destination[0];
       printf("  FAIL! dg_shluint64s length 3 shift 192 success case - expected destination[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 0)
    {
       x = destination[1];
       printf("  FAIL! dg_shluint64s length 3 shift 192 success case - expected destination[1] = 192, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 0)
    {
       x = destination[2];
       printf("  FAIL! dg_shluint64s length 3 shift 192 success case - expected destination[2] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shluint64s length 3 shift 192 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    // printf("  testing dg_shluint64s length 1 shift 4 success case\n");
    
    source[0] = 0x53;
    source[1] = 0xAB;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shluint64s(
        source,
        destination,
        1,
        4);
    
    if (destination[0] != 0x530)
    {
       x = destination[0];
       printf("  FAIL! dg_shluint64s length 1 shift 4 success case - expected destination[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 4)
    {
       x = destination[1];
       printf("  FAIL! dg_shluint64s length 1 shift 4 success case - expected destination[1] = 4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 8)
    {
       x = destination[2];
       printf("  FAIL! dg_shluint64s length 1 shift 4 success case - expected destination[2] = 8, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shluint64s length 1 shift 4 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}

void dg_testshruint64s()
{
    UINT64 source[64];
    UINT64 destination[64];
    UINT64 x;
    
    printf("  testing dg_shruint64s\n");
    
    // printf("  testing dg_shruint64s length 0 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;

    dg_shruint64s(
        source,
        destination,
        0,
        64);
    
    if (destination[0] != 2)
    {
       x = destination[0];
       printf("  FAIL! dg_shruint64s length 0 success case - expected destination[0] = 2, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (source[0] != 5)
    {
       x = source[0];
       printf("  FAIL! dg_shruint64s length 0 success case - expected source[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    // printf("  testing dg_shruint64s length 3 shift 64 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 9;

    dg_shruint64s(
        source,
        destination,
        3,
        64);
    
    if (destination[0] != 11)
    {
       x = destination[0];
       printf("  FAIL! dg_shruint64s length 3 shift 64 success case - expected destination[0] = 11, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 19)
    {
       x = destination[1];
       printf("  FAIL! dg_shruint64s length 3 shift 64 success case - expected destination[1] = 19, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 0)
    {
       x = destination[2];
       printf("  FAIL! dg_shruint64s length 3 shift 64 success case - expected destination[2] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 9)
    {
       x = destination[3];
       printf("  FAIL! dg_shruint64s length 3 shift 64 success case - expected destination[3] = 9, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    // printf("  testing dg_shruint64s length 3 shift 1 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shruint64s(
        source,
        destination,
        3,
        1);
    
    if (destination[0] != 0x8000000000000002)
    {
       x = destination[0];
       printf("  FAIL! dg_shruint64s length 3 shift 1 success case - expected destination[0] = 0x8000000000000004, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 0x8000000000000005)
    {
       x = destination[1];
       printf("  FAIL! dg_shruint64s length 3 shift 1 success case - expected destination[1] = 0x8000000000000005, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 9)
    {
       x = destination[2];
       printf("  FAIL! dg_shruint64s length 3 shift 1 success case - expected destination[2] = 9, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shruint64s length 3 shift 1 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    // printf("  testing dg_shruint64s length 3 shift 0 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shruint64s(
        source,
        destination,
        3,
        0);
    
    if (destination[0] != 5)
    {
       x = destination[0];
       printf("  FAIL! dg_shruint64s length 3 shift 0 success case - expected destination[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 11)
    {
       x = destination[1];
       printf("  FAIL! dg_shruint64s length 3 shift 0 success case - expected destination[1] = 11, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 19)
    {
       x = destination[2];
       printf("  FAIL! dg_shruint64s length 3 shift 0 success case - expected destination[2] = 19, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shruint64s length 3 shift 0 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    // printf("  testing dg_shruint64s length 3 shift 192 success case\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shruint64s(
        source,
        destination,
        3,
        192);
    
    if (destination[0] != 0)
    {
       x = destination[0];
       printf("  FAIL! dg_shruint64s length 3 shift 192 success case - expected destination[0] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 0)
    {
       x = destination[1];
       printf("  FAIL! dg_shruint64s length 3 shift 192 success case - expected destination[1] = 192, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 0)
    {
       x = destination[2];
       printf("  FAIL! dg_shruint64s length 3 shift 192 success case - expected destination[2] = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shruint64s length 3 shift 192 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    
    // printf("  testing dg_shruint64s length 1 shift 4 success case\n");
    
    source[0] = 0x53;
    source[1] = 0xAB;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;
    destination[3] = 7;

    dg_shruint64s(
        source,
        destination,
        1,
        4);
    
    if (destination[0] != 5)
    {
       x = destination[0];
       printf("  FAIL! dg_shruint64s length 1 shift 4 success case - expected destination[0] = 5, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 4)
    {
       x = destination[1];
       printf("  FAIL! dg_shruint64s length 1 shift 4 success case - expected destination[1] = 4, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 8)
    {
       x = destination[2];
       printf("  FAIL! dg_shruint64s length 1 shift 4 success case - expected destination[2] = 8, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[3] != 7)
    {
       x = destination[3];
       printf("  FAIL! dg_shruint64s length 1 shift 4 success case - expected destination[3] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}

    
void dg_testadduint64s()
{
    UINT64 source[64];
    UINT64 destination[64];
    UINT64 x;
    UINT64 carryout;
    
    printf("  testing dg_adduint64s\n");
    
    source[0] = 5;
    source[1] = 11;
    source[2] = 19;
    destination[0] = 2;
    destination[1] = 4;
    destination[2] = 8;

    carryout = dg_adduint64s(
        destination,
        source,
        3);
    
    if (destination[0] != 7)
    {
       x = destination[0];
       printf("  FAIL! dg_adduint64s length 3 success case - expected destination[0] = 7, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 15)
    {
       x = destination[1];
       printf("  FAIL! dg_adduint64s length 3 success case - expected destination[0] = 15, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 27)
    {
       x = destination[2];
       printf("  FAIL! dg_adduint64s length 3 success case - expected destination[0] = 27, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (carryout != 0)
    {
       x = carryout;
       printf("  FAIL! dg_adduint64s length 3 success case - expected carryout = 0, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    source[0] = (UINT64)-1;
    source[1] = (UINT64)-2;
    source[2] = (UINT64)-3;
    destination[0] = 2; // -1 + 2 = 1 carry 1
    destination[1] = 4; // -2 + 4 + carry = 3 carry 1
    destination[2] = 8; // -3 + 8 + carry = 6 carry 1

    carryout = dg_adduint64s(
        destination,
        source,
        3);
    
    if (destination[0] != 1)
    {
       x = destination[0];
       printf("  FAIL! dg_adduint64s length 3 success case b - expected destination[0] = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[1] != 3)
    {
       x = destination[1];
       printf("  FAIL! dg_adduint64s length 3 success case b - expected destination[1] = 3, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (destination[2] != 6)
    {
       x = destination[2];
       printf("  FAIL! dg_adduint64s length 3 success case b - expected destination[2] = 6, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
    
    if (carryout != 1)
    {
       x = carryout;
       printf("  FAIL! dg_adduint64s length 3 success case - expected carryout = 1, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);
         
        return;
    }
}

// for i = 0 to r-1
// sum r^2 - i^2
// (r+1)^2 - r^2 = 2r + 1

// pi = (1/(r^2)) * [sqrt((r^2) - (0^2)) + sqrt((r^2) - (1^2)) + sqrt((r^2) - (2^2)) + ... sqrt((r^2) - ((r^2))]

// so...
// if r is an even power of 2... then
// rsquaredminusisquared = rsquared
// piover4 = r (to start)
// i = 1
// while (i<r) 
// {
//   rsquaredminusisquared -= 2i + 1
//   sqrtofrsquaredminusisquared = sqrt(rsquaredminusisquared)
//   piover4 += sqrtofrsquaredminusisquared
//   i++
// }
// then divide piover4 by rsquared
// then multiply by 4 to get pi

// or... you can go from i = r-1 to 0 and do
//  rsquaredminusisquared += 2i+1
//  sqrtofrsquaredminusisquared = sqrt(rsquaredminusisquared)
//  piover4 += sqrtofrsquaredminusisquared
//  i--
//  


void dg_dointregal(
    UINT64* pa, // r
    // UINT64* pb, // 0
    UINT64* pi,
    UINT64* pstepsize, 
    UINT64* prquaredminusisquared,
    UINT64* psqrtofrsquaredminusisquared,
    UINT64* presult,
    UINT64* ptempx, // for squareroot calculation
    UINT64* ptempy, // for squareroot calculation
    UINT64 lengthinuint64s,
    UINT64 fractionaluint64s)
{
    UINT64 flag;
    
    dg_clearuint64s(
        prquaredminusisquared,
        lengthinuint64s);
    
    dg_clearuint64s(
        presult,
        lengthinuint64s);
        
    dg_copyuint64s(
        pi,
        pa,
        lengthinuint64s);
        
    while(true)
    {
        // while i >= stepsize... keep going ... really be better to use b...
        flag = dg_compareuint64sreverse(
            pi,
            pstepsize,
            lengthinuint64s);
            
        if ((flag == (UINT64)-1) || (flag == 0))
        {
            break;
        }
        
        // add stepsize to i
        dg_subuint64s(
            pi,
            pstepsize,
            lengthinuint64s);
            
        // add 2i+1 to
         dg_add2abplusbsquaredtouint64s(
            pi, 
            prquaredminusisquared, 
            lengthinuint64s,               
            0, // indexinbits,
            fractionaluint64s,   // indexinuint64s, 
            fractionaluint64s);  // fractionalbits)
            
        // printf(" prsquar = ");
        
        // dg_printarray(
        //    prquaredminusisquared,
        //    lengthinuint64s,
        //    fractionaluint64s);
        
        // printf("\n");
        
        // get squareroot of (r^2 - i^2)    
        dg_sqrtuint64s( 
            prquaredminusisquared,
            psqrtofrsquaredminusisquared,
            ptempx,
            ptempy,
            lengthinuint64s,  // of pr, psqrtr, prguess, and prguesscopy
            fractionaluint64s);
            
        // printf(" psqrt.. = ");
        
        // dg_printarray(
        //    psqrtofrsquaredminusisquared,
        //    lengthinuint64s,
        //    fractionaluint64s);
        
        // printf("\n");
            
        // add the squareroot result to the summation
        dg_adduint64s(
            presult,
            psqrtofrsquaredminusisquared,
            lengthinuint64s);
            
        // printf(" presult = ");
        
        // dg_printarray(
        //    presult,
        //    lengthinuint64s,
        //    fractionaluint64s);
        
        // printf("\n");
    }
}

#define myarraysize (8)
#define myfractionaluint64s (4)
void dg_calculatepi()
{
    printf(" Calculating PI\n");
    UINT64 pa[myarraysize]; // this is the radius of the circle
    UINT64 pi[myarraysize];
    UINT64 pstepsize[myarraysize];
    UINT64 prquaredminusisquared[myarraysize];
    UINT64 psqrtofrsquaredminusisquared[myarraysize];
    UINT64 presult[myarraysize];
    UINT64 ptempx[myarraysize];
    UINT64 ptempy[myarraysize];
    
    UINT64 u;
    UINT64 x;
    
    dg_clearuint64s(
        pa,
        myarraysize);
    
    // need to set a to a power of 2...
    pa[myfractionaluint64s] = 0x1000000;
    
    dg_clearuint64s(
        pstepsize,
        myarraysize);
    
    pstepsize[myfractionaluint64s] = 1;
    
    dg_dointregal(
        pa, // r
        // UINT64* pb, // 0
        pi,
        pstepsize, // should be -1
        prquaredminusisquared,
        psqrtofrsquaredminusisquared,
        presult,
        ptempx, // for squareroot calculation
        ptempy, // for squareroot calculation
        myarraysize, // lengthinuint64s,
        myfractionaluint64s); // fractionaluint64s)
    
    dg_shluint64s(
        presult,      // psrc
        presult,      // pdest
        myarraysize,  // lengthinuint64s,
        2);           // shiftcount);
    
    printf(" pi = ");
    
    dg_printarray(
        presult,
        myarraysize,
        myfractionaluint64s);
    
    printf("\n");
}

int main(int argc, char* argv[])
{
    printf("testing calculatepi.dylib\n");
    
    dg_testadduint64s();
    dg_testshruint64s();
    dg_testshraddint64s();
    dg_testshluint64s();
    dg_testshladdint64s();
    dg_testdg_addbitinuint64s();
    // testdg_indextopowerof2();
    // testdg_powerof2toindex();
    dg_testdg_getshiftplusone();
    testdg_getshiftdoubled();
    testdg_add2abplusbsquaredtouint64s();
    testdg_findhighestbitinuint64s();
    testdg_compareuint64sreverse();
    testdg_copyuint64s();
    testdg_sqrtuint64s();
    
    dg_calculatepi();

	return(0);
}
