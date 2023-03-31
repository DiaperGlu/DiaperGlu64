// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2020 James Patrick Norris
//
//    This file is part of LifeLib v1.0.
//
//    LifeLib v1.0 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    LifeLib v1.0 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with LifeLib v1.0; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// thaine@mail87.pair.com     //
// April 28, 2020             //
// version 1.0                //
// /////////////////////////////

#if !defined(_INC_liblife)
#define _INC_liblife

#ifdef  __cplusplus
extern "C" {
#endif

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

UINT128 dg_getoverlapsegment(
  UINT64 ASX,          // RDI
  UINT64 AL,           // RSI
  UINT64 BSX,          // RDX
  UINT64 BL);          // RCX

void dg_calcNeighborsForRowFast(
  UINT8* prowbits,                // RDI
  UINT8* pthisrownneighbors,      // RSI
  UINT8* pnextrownneighbors,      // RDX
  UINT64 qwordsperrowofneighbors, // RCX
  UINT8* pthisrownneighborsend,   // R8
  UINT8* pnextrownneighborsend);   // R9

void dg_calcNeighborsForRow(
  UINT8* prowbits,                       // RDI
  UINT8* pthisrownneighbors,             // RSI
  UINT8* pnextrownneighbors,             // RDX
  UINT64 dwordsperrowperrowofneighbors,  // RCX
  UINT8* pthisrownneighborsend,          // R8
  UINT8* pnextrownneighborsend);         // R9

void dg_updateCellsForRow(
  UINT8* prowbits,                //  RDI
  UINT8* ppreviousrownneighbors,  //  RSI
  UINT8* pnextrownneighbors,      //  RDX
  UINT64 dwordsperrowofcells,     //  RCX
  UINT64 logicfunction);          //  R8

void dg_clearNeighbors(
  UINT8* ppreviousrownneighbors,    //  RDI
  UINT8* pthisneighborsbuffer,      //  RSI
  UINT8* pnextrownneighbors,        //  RDX
  UINT64 qwordsperrowofneighbors);  //  RCX

void dg_copyNeighbors(
  UINT8* ppreviousrownneighbors,    //  RDI
  UINT8* pthisneighborsbuffer,      //  RSI
  UINT8* pnextrownneighbors,        //  RDX
  UINT64 qwordsperrowofneighbors); //  RCX
  
void dg_moveQwords(
  UINT64* pdest,           // RDI
  UINT64* psrc,            // RSI
  UINT64  lengthinqwords);  // RDX
  
void dg_calcNeighborsForRowN(
  UINT64  rowN,                   //  RDI
  UINT8*  pthisrownneighbors,     //  RSI
  UINT8*  pnextrownneighbors,     //  RDX
  UINT64  cellsperrow,            //  RCX
  UINT8*  pmypixelbuffer);        //  R8
  
void dg_updateCellsForRowN(
  UINT64 rowN,                   // RDI
  UINT8* ppreviousrowneighbors,  // RSI
  UINT8* pnextrownneighbors,     // RDX
  UINT64 cellsperrow,            // RCX
  UINT8* pmypixelbuffer,         // R8
  UINT64 logicfunction);         // R9
  
UINT64 dg_lifeBitMapOnce(
  UINT8*  ppreviousrowneighbors,  //  RDI
  UINT8*  pthisrowneighbors,      //  RSI
  UINT8*  pnextrownneighbors,     //  RDX
  UINT64  cellsperrow,            //  RCX
  UINT64  numberofrows,           //  R8
  UINT8*  pmypixelbuffer,         //  R9
  UINT64  logicfunction,          //  [RBP + 10]
  UINT8*  ptoprowneighbors);      //  [RBP + 18]

void dg_areaXor(
  UINT8*  pdest,                   //  RDI
  UINT8*  psrc,                    //  RSI
  UINT64  xorheightinbits,         //  RDX
  UINT64  xorwidthinbits,          //  RCX
  UINT64  srcxinbitsdestxinbits,   //  R8 (low 8 bits = destx,
                                   //   next 8 bits = srcx, 0-63)
  UINT64  destwidthinbits,         //  R9
  UINT64  lastqwordinrowmask,      //  [RBP + 10]
  UINT64  srcendofrowbumpinbytes); //  [RBP + 18]
  
void dg_areaOr(
  UINT8*  pdest,                   //  RDI
  UINT8*  psrc,                    //  RSI
  UINT64  orheightinbits,          //  RDX
  UINT64  orwidthinbits,           //  RCX
  UINT64  srcxinbitsdestxinbits,   //  R8 (low 8 bits = destx,
                                   //   next 8 bits = srcx, 0-63)
  UINT64  destwidthinbits,         //  R9
  UINT64  lastqwordinrowmask,      //  [RBP + 10]
  UINT64  srcendofrowbumpinbytes); //  [RBP + 18]
  
void dg_areaAnd(
  UINT8*  pdest,                   //  RDI
  UINT8*  psrc,                    //  RSI
  UINT64  orheightinbits,          //  RDX
  UINT64  orwidthinbits,           //  RCX
  UINT64  srcxinbitsdestxinbits,   //  R8 (low 8 bits = destx,
                                   //   next 8 bits = srcx, 0-63)
  UINT64  destwidthinbits,         //  R9
  UINT64  lastqwordinrowmask,      //  [RBP + 10]
  UINT64  srcendofrowbumpinbytes); //  [RBP + 18]

void dg_areaNotSourceAnd(
  UINT8*  pdest,                     //  RDI
  UINT8*  psrc,                      //  RSI
  UINT64  notsourceandheightinbits,  //  RDX
  UINT64  notsourceandwidthinbits,   //  RCX
  UINT64  srcxinbitsdestxinbits,     //  R8 (low 8 bits = destx,
                                     //   next 8 bits = srcx, 0-63)
  UINT64  destwidthinbits,           //  R9
  UINT64  lastqwordinrowmask,        //  [RBP + 10]
  UINT64  srcendofrowbumpinbytes);   //  [RBP + 18]

void dg_getOverlapOffset(
  UINT64  srcwidth,                   //  RDI
  UINT64  destwidth,                  //  RSI
  UINT64  destx);                     //  RDX
  
const static unsigned char* dg_thisneighborsaddtbl;
const static unsigned char* dg_nextneighborsaddtbl;

// for lastqwordinrowmask
//  the index is the number of bits in the last qword you are using
const static UINT64 lifebitmasktable[64] = {
    0xFFFFFFFFFFFFFFFF,
    0x8000000000000000,
    0xC000000000000000,
    0xE000000000000000,
    0xF000000000000000,

    0xF800000000000000,
    0xFC00000000000000,
    0xFE00000000000000,
    0xFF00000000000000,

    0xFF80000000000000,
    0xFFC0000000000000,
    0xFFE0000000000000,
    0xFFF0000000000000,

    0xFFF8000000000000,
    0xFFFC000000000000,
    0xFFFE000000000000,
    0xFFFF000000000000,


    0xFFFF800000000000,
    0xFFFFC00000000000,
    0xFFFFE00000000000,
    0xFFFFF00000000000,

    0xFFFFF80000000000,
    0xFFFFFC0000000000,
    0xFFFFFE0000000000,
    0xFFFFFF0000000000,

    0xFFFFFF8000000000,
    0xFFFFFFC000000000,
    0xFFFFFFE000000000,
    0xFFFFFFF000000000,

    0xFFFFFFF800000000,
    0xFFFFFFFC00000000,
    0xFFFFFFFE00000000,
    0xFFFFFFFF00000000,


    0xFFFFFFFF80000000,
    0xFFFFFFFFC0000000,
    0xFFFFFFFFE0000000,
    0xFFFFFFFFF0000000,

    0xFFFFFFFFF8000000,
    0xFFFFFFFFFC000000,
    0xFFFFFFFFFE000000,
    0xFFFFFFFFFF000000,

    0xFFFFFFFFFF800000,
    0xFFFFFFFFFFC00000,
    0xFFFFFFFFFFE00000,
    0xFFFFFFFFFFF00000,

    0xFFFFFFFFFFF80000,
    0xFFFFFFFFFFFC0000,
    0xFFFFFFFFFFFE0000,
    0xFFFFFFFFFFFF0000,


    0xFFFFFFFFFFFF8000,
    0xFFFFFFFFFFFFC000,
    0xFFFFFFFFFFFFE000,
    0xFFFFFFFFFFFFF000,

    0xFFFFFFFFFFFFF800,
    0xFFFFFFFFFFFFFC00,
    0xFFFFFFFFFFFFFE00,
    0xFFFFFFFFFFFFFF00,

    0xFFFFFFFFFFFFFF80,
    0xFFFFFFFFFFFFFFC0,
    0xFFFFFFFFFFFFFFE0,
    0xFFFFFFFFFFFFFFF0,

    0xFFFFFFFFFFFFFFF8,
    0xFFFFFFFFFFFFFFFC,
    0xFFFFFFFFFFFFFFFE};

#ifdef  __cplusplus
}
#endif


#endif  /* _INC_liblife */
