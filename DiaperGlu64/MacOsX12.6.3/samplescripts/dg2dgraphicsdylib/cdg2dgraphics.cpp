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


#include "dg2dgraphics.h"

// ///////////////
// 2D Graphics  //
// ///////////////

UINT64 dg_getnearesthighestmultiple (
    UINT64 n,
    UINT64 pagesize)
{
    // hopefully no one will do this, but if they do, gonna use a pagesize of 1 and return n
    if (0 == pagesize)
    {
        return (n);
    }
    
    // if n is 0, calculation would underflow, handling this case here
    if (0 == n)
    {
        return(pagesize);
    }
    
    // if calculation would overflow, round down
    if (n > (UINT64)(0 - pagesize))
    {
        return (pagesize * (UINT64)(n/pagesize));
    }
    
    // normal case, return multiple of pagesize >= n
    return (((UINT64)((n - 1) / pagesize) + 1)* pagesize);
}

void dg_maskedmovenrowsuint32s (
    unsigned char* pdest,
    unsigned char* psrc,
    unsigned char* pmask,
    UINT64 width,            // in pixels (which are 4 bytes each)
    UINT64 height,           // in pixels
    UINT64 maskstartbitoffset, // in pixels (0-63, 1 bit each)
    UINT64 destrowsize, // in bytes
    UINT64 srcrowsize,  // in bytes
    UINT64 maskrowsize) // in bytes
{
    unsigned char* pdest2 = pdest;
    unsigned char* psrc2 = psrc;
    unsigned char* pmask2 = pmask;
    UINT64 i;
    
    if ((0 == height) || (0 == width))
    {
        return;
    }
    
    for(i = 0; i < height; i++)
    {
        dg_maskedmoveuint32s (
            pdest2,
            psrc2,
            width, // lengthinuint32s,
            maskstartbitoffset,
            pmask2);
            
        pdest2 += destrowsize;
        psrc2 += srcrowsize;
        pmask2 += maskrowsize;
    }
}

void dg_copymaskeduint32sarea (
    unsigned char* pdest,
    UINT64 destwidth,     // in pixels 
    UINT64 destheight,    // in pixels
    unsigned char* psrc,  
    UINT64 srcwidth,      // in pixels 
    UINT64 srcheight,     // in pixels and also maskheight
    unsigned char* pmask, // maskwidth = srcwidth rounded up to nearest multiple of 64
    INT64 xoffsetindest,  // left edge of src is here relative to left edge of dest
    INT64 yoffsetindest)  // top edge of src is here relative to top edge of dest
{
    
    UINT128 xoverlapsegment;
    UINT128 yoverlapsegment;
    
    unsigned char* psrc2;
    unsigned char* pdest2;
    unsigned char* pmask2;
    
    UINT64 overlapwidth, overlapheight; // in pixels
    
    
    UINT64 startxinsrc, startxindest,  startxinmask; // in pixels
    UINT64 startyinsrc, startyindest; // in pixels
    
    UINT64 maskwidth; // in pixels
    
    UINT64 maskstartbitoffset; // in pixels
    
    UINT64 destendofrowbump, srcendofrowbump, maskendofrowbump; // in bytes
    
    maskwidth = dg_getnearesthighestmultiple (
        srcwidth,
        64); 
    
    xoverlapsegment = dg_getoverlapsegment (
        xoffsetindest,  // asx
        srcwidth,       // al
        0,              // bsx,
        destwidth);     // bl)
        
    yoverlapsegment = dg_getoverlapsegment (
        yoffsetindest,  // asx
        srcheight,      // al
        0,              // bsx,
        destheight);    // bl)
        
    overlapwidth = ((UINT64*)&xoverlapsegment)[0];
    overlapheight = ((UINT64*)&yoverlapsegment)[0];
        
    if ( (0 == overlapwidth) ||
         (0 == overlapheight) )
    {
        return;
    }
    
    startxinsrc  = ((UINT64*)&xoverlapsegment)[1] - xoffsetindest;
    startyinsrc  = ((UINT64*)&yoverlapsegment)[1] - yoffsetindest;
    startxindest = ((UINT64*)&xoverlapsegment)[1];
    startyindest = ((UINT64*)&yoverlapsegment)[1];
    
    startxinmask = startxinsrc & 0xFFFFFFFFFFFFFFC0; // truncate
    maskstartbitoffset = startxinsrc % 64;
    
    psrc2  = psrc  + (startyinsrc  * (srcwidth  << 2)) + (startxinsrc  << 2);
    pdest2 = pdest + (startyindest * (destwidth << 2)) + (startxindest << 2);
    pmask2 = pmask + (startyinsrc  * (maskwidth >> 3)) + (startxinmask >> 3);
    
     
    
    srcendofrowbump  = srcwidth  << 2;   // 4 bytes per pixel
    destendofrowbump = destwidth << 2;  // 4 bytes per pixel
    maskendofrowbump = maskwidth >> 3;  // 8 pixels per byte
    
    dg_maskedmovenrowsuint32s (
        pdest2,
        psrc2,
        pmask2,
        overlapwidth,
        overlapheight,
        maskstartbitoffset,
        destendofrowbump,
        srcendofrowbump,
        maskendofrowbump);
}

