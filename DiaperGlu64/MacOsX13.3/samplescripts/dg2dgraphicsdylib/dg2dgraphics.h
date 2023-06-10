// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.11.
//
//    DiaperGlu v5.11 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.11 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.11; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// June 10, 2023              //
// version 5.11               //
// /////////////////////////////

#if !defined(_INC_dg2dgraphics)
#define _INC_dg2dgraphics

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

UINT128 dg_getoverlapsegment (
    UINT64 asx,
    UINT64 al,
    UINT64 bsx,
    UINT64 bl);
    
void dg_maskedmoveuint32s (
    unsigned char* pdest,
    unsigned char* psrc,
    UINT64 lengthinuint32s,
    UINT64 maskstartoffset,
    unsigned char* pmask);

void dg_maskedmovenrowsuint32s (
    unsigned char* pdest,
    unsigned char* psrc,
    unsigned char* pmask,
    UINT64 width,
    UINT64 height,
    UINT64 maskstartoffset,
    UINT64 srcendofrowbump,
    UINT64 destendofrowbump,
    UINT64 maskendofrowbump);
    
void dg_copymaskeduint32sarea (
    unsigned char* pdest,
    UINT64 destwidth,     // in pixels 
    UINT64 destheight,    // in pixels
    unsigned char* psrc,  
    UINT64 srcwidth,      // in pixels 
    UINT64 srcheight,     // in pixels and also maskheight
    unsigned char* pmask, // maskwidth = srcwidth rounded up to nearest multiple of 64
    INT64 xoffsetindest,  // left edge of src is here relative to left edge of dest
    INT64 yoffsetindest); // top edge of src is here relative to top edge of dest

#ifdef  __cplusplus
}
#endif


#endif  /* _INC_dg2dgraphics */
