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
// April 11, 2022             //
// version 5.2                //
// /////////////////////////////

#include "dg2dgraphics.h"
#include <stdio.h>

void testdg_maskedmovenrowsuint32s ()
{
    UINT32 srcbuf[12];    // 3*4
    UINT32 destbuf[35];   // 5*7
    UINT64 maskbuf[4];    // ((1 * 64)/ 8) * 4  (each mask row is 8 bytes for this src)    
    UINT64 aftermask = 0;
    UINT64 i;
    
    printf("testing dg_maskedmovenrowsuint32s\n");
    
    // success mask = 0 case (nothing gets copied)
    for (i = 0; i < 12; i++)
    {
        srcbuf[i] = i;
    }
    
    for (i = 0; i < 35; i++)
    {
        destbuf[i] = 100 + i;
    }
    
    for (i = 0; i < 4; i++)
    {
        maskbuf[i] = 0;
    }
    
    dg_maskedmovenrowsuint32s (
        (unsigned char*)destbuf,
        (unsigned char*)srcbuf,
        (unsigned char*)maskbuf,
        3,  // width,               // in pixels (which are 4 bytes each)
        2,  // height,              // in pixels
        0,  // maskstartbitoffset,  // in pixels (0-63, 1 bit each)
        20, // destrowsize,         // in bytes
        12, // srcrowsize,          // in bytes
        1); // maskrowsize)         // in bytes
        
    for (i = 0; i < 35; i++)
    {
        if (destbuf[i] != 100 + i)
        {
            printf("  Fail! dg_maskedmovenrowsuint32s success mask = 0 case, destination changed\n");
            break;
        }
    }
    
    // success width = 0 case (nothing gets copied)
    for (i = 0; i < 12; i++)
    {
        srcbuf[i] = i;
    }
    
    for (i = 0; i < 35; i++)
    {
        destbuf[i] = 100 + i;
    }
    
    for (i = 0; i < 4; i++)
    {
        maskbuf[i] = (UINT64)-1;
    }
    
    dg_maskedmovenrowsuint32s (
        (unsigned char*)destbuf,
        (unsigned char*)srcbuf,
        (unsigned char*)maskbuf,
        0,  // width,               // in pixels (which are 4 bytes each)
        2,  // height,              // in pixels
        0,  // maskstartbitoffset,  // in pixels (0-63, 1 bit each)
        20, // destrowsize,         // in bytes
        12, // srcrowsize,          // in bytes
        1); // maskrowsize)         // in bytes
        
    for (i = 0; i < 35; i++)
    {
        if (destbuf[i] != 100 + i)
        {
            printf("  Fail! dg_maskedmovenrowsuint32s success width = 0 case, destination changed\n");
            break;
        }
    }
    
    // success height = 0 case (nothing gets copied)
    for (i = 0; i < 12; i++)
    {
        srcbuf[i] = i;
    }
    
    for (i = 0; i < 35; i++)
    {
        destbuf[i] = 100 + i;
    }
    
    for (i = 0; i < 4; i++)
    {
        maskbuf[i] = (UINT64)-1;
    }
    
    dg_maskedmovenrowsuint32s (
        (unsigned char*)destbuf,
        (unsigned char*)srcbuf,
        (unsigned char*)maskbuf,
        3,  // width,               // in pixels (which are 4 bytes each)
        0,  // height,              // in pixels
        0,  // maskstartbitoffset,  // in pixels (0-63, 1 bit each)
        20, // destrowsize,         // in bytes
        12, // srcrowsize,          // in bytes
        1); // maskrowsize)         // in bytes
        
    for (i = 0; i < 35; i++)
    {
        if (destbuf[i] != 100 + i)
        {
            printf("  Fail! dg_maskedmovenrowsuint32s success height = 0 case, destination changed\n");
            break;
        }
    }
    
    // success bit offset 0 full mask case 
    for (i = 0; i < 12; i++)
    {
        srcbuf[i] = i;
    }
    
    for (i = 0; i < 35; i++)
    {
        destbuf[i] = 100 + i;
    }
    
    for (i = 0; i < 4; i++)
    {
        maskbuf[i] = (UINT64)-1;
    }
    
    dg_maskedmovenrowsuint32s (
        (unsigned char*)destbuf,
        (unsigned char*)srcbuf,
        (unsigned char*)maskbuf,
        3,  // width,               // in pixels (which are 4 bytes each)
        2,  // height,              // in pixels
        0,  // maskstartbitoffset,  // in pixels (0-63, 1 bit each)
        20, // destrowsize,         // in bytes
        12, // srcrowsize,          // in bytes
        1); // maskrowsize)         // in bytes
    
    if (destbuf[0] != 0)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 full mask case, destination (0, 0) wrong\n");
    }
    
    if (destbuf[1] != 1)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 full mask case, destination (0, 1) wrong\n");
    }
    
    if (destbuf[2] != 2)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 full mask case, destination (0, 2) wrong\n");
    }
    
    if (destbuf[3] != 103)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 full mask case, destination (0, 3) wrong\n");
    }
    
    if (destbuf[4] != 104)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 full mask case, destination (0, 4) wrong\n");
    }
    
    
    if (destbuf[5] != 3)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 full mask case, destination (1, 0) wrong\n");
    }
    
    if (destbuf[6] != 4)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 full mask case, destination (1, 1) wrong\n");
    }
    
    if (destbuf[7] != 5)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 full mask case, destination (1, 2) wrong\n");
    }
    
    if (destbuf[8] != 108)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 full mask case, destination (1, 3) wrong\n");
    }
    
    if (destbuf[9] != 109)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 full mask case, destination (1, 4) wrong\n");
    }
    
    if (destbuf[10] != 110)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 full mask case, destination (2, 0) wrong\n");
    }
    
    // success bit offset 0 partial mask case 
    for (i = 0; i < 12; i++)
    {
        srcbuf[i] = i;
    }
    
    for (i = 0; i < 35; i++)
    {
        destbuf[i] = 100 + i;
    }
    
    maskbuf[0] = 0xa0; // after bswap it's 0xa000000000000000
    maskbuf[1] = 0x40; // after bswap it's 0x4000000000000000
    maskbuf[2] = (UINT64)-1;
    maskbuf[3] = (UINT64)-1;
    
    dg_maskedmovenrowsuint32s (
        (unsigned char*)destbuf,
        (unsigned char*)srcbuf,
        (unsigned char*)maskbuf,
        3,  // width,               // in pixels (which are 4 bytes each)
        2,  // height,              // in pixels
        0,  // maskstartbitoffset,  // in pixels (0-63, 1 bit each)
        20, // destrowsize,         // in bytes
        12, // srcrowsize,          // in bytes
        8); // maskrowsize)         // in bytes
    
    if (destbuf[0] != 0)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask case, destination (0, 0) wrong\n");
    }
    
    if (destbuf[1] != 101)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask case, destination (0, 1) wrong\n");
    }
    
    if (destbuf[2] != 2)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask case, destination (0, 2) wrong\n");
    }
    
    if (destbuf[3] != 103)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask case, destination (0, 3) wrong\n");
    }
    
    if (destbuf[4] != 104)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask case, destination (0, 4) wrong\n");
    }
    
    
    if (destbuf[5] != 105)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask case, destination (1, 0) wrong\n");
    }
    
    if (destbuf[6] != 4)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask case, destination (1, 1) wrong, expected 4, got %d\n", destbuf[6]);
    }
    
    if (destbuf[7] != 107)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask case, destination (1, 2) wrong\n");
    }
    
    if (destbuf[8] != 108)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask case, destination (1, 3) wrong\n");
    }
    
    if (destbuf[9] != 109)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask case, destination (1, 4) wrong\n");
    }
    
    if (destbuf[10] != 110)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask case, destination (2, 0) wrong\n");
    }
    
    // success bit offset 0 partial mask maskstartbitoffset 1 case 
    for (i = 0; i < 12; i++)
    {
        srcbuf[i] = i;
    }
    
    for (i = 0; i < 35; i++)
    {
        destbuf[i] = 100 + i;
    }
    
    maskbuf[0] = 0xa0; // after bswap it's 0xa000000000000000
    maskbuf[1] = 0x40; // after bswap it's 0x4000000000000000
    maskbuf[2] = (UINT64)-1;
    maskbuf[3] = (UINT64)-1;
    
    dg_maskedmovenrowsuint32s (
        (unsigned char*)destbuf,
        (unsigned char*)srcbuf,
        (unsigned char*)maskbuf,
        3,  // width,               // in pixels (which are 4 bytes each)
        2,  // height,              // in pixels
        1,  // maskstartbitoffset,  // in pixels (0-63, 1 bit each)
        20, // destrowsize,         // in bytes
        12, // srcrowsize,          // in bytes
        8); // maskrowsize)         // in bytes
    
    if (destbuf[0] != 100)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask maskstartbitoffset 1 case, destination (0, 0) wrong\n");
    }
    
    if (destbuf[1] != 1)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask maskstartbitoffset 1 case, destination (0, 1) wrong\n");
    }
    
    if (destbuf[2] != 102)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask maskstartbitoffset 1 case, destination (0, 2) wrong\n");
    }
    
    if (destbuf[3] != 103)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask maskstartbitoffset 1 case, destination (0, 3) wrong\n");
    }
    
    if (destbuf[4] != 104)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask maskstartbitoffset 1 case, destination (0, 4) wrong\n");
    }
    
    
    if (destbuf[5] != 3)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask maskstartbitoffset 1 case, destination (1, 0) wrong\n");
    }
    
    if (destbuf[6] != 106)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask maskstartbitoffset 1 case, destination (1, 1) wrong, expected 4, got %d\n", destbuf[6]);
    }
    
    if (destbuf[7] != 107)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask maskstartbitoffset 1 case, destination (1, 2) wrong\n");
    }
    
    if (destbuf[8] != 108)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask maskstartbitoffset 1 case, destination (1, 3) wrong\n");
    }
    
    if (destbuf[9] != 109)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask maskstartbitoffset 1 case, destination (1, 4) wrong\n");
    }
    
    if (destbuf[10] != 110)
    {
        printf("  Fail! dg_maskedmovenrowsuint32s success bit offset 0 partial mask maskstartbitoffset 1 case, destination (2, 0) wrong\n");
    }
    
}

void testdg_copymaskeduint32sarea ()
{
    UINT32 srcbuf[12];    // 3*4
    UINT32 destbuf[35];   // 5*7
    UINT64 maskbuf[4];    // ((1 * 64)/ 8) * 4  (each mask row is 8 bytes for this src)    
    UINT64 aftermask = 0;
    UINT64 i;
    
    printf("testing dg_copymaskeduint32sarea\n");
    
    // success mask = 0 case (nothing gets copied)
    for (i = 0; i < 12; i++)
    {
        srcbuf[i] = i;
    }
    
    for (i = 0; i < 35; i++)
    {
        destbuf[i] = 100 + i;
    }
    
    for (i = 0; i < 4; i++)
    {
        maskbuf[i] = 0;
    }
    
    dg_copymaskeduint32sarea (
        (unsigned char*)destbuf, // pdest
        5, // destwidth,     // in pixels 
        7, // destheight,    // in pixels
        (unsigned char*)srcbuf, // psrc,  
        3, // srcwidth,      // in pixels 
        4, // srcheight,     // in pixels and also maskheight
        (unsigned char*)maskbuf, //  pmask, // maskwidth = srcwidth rounded up to nearest multiple of 64
        0, // xoffsetindest,  // left edge of src is here relative to left edge of dest
        0); // yoffsetindest)
        
    for (i = 0; i < 35; i++)
    {
        if (destbuf[i] != 100 + i)
        {
            printf("  Fail! dg_copymaskeduint32sarea success mask = 0 case, destination changed\n");
            break;
        }
    }
    
    // success srcwidth = 0 case (nothing gets copied)
    for (i = 0; i < 12; i++)
    {
        srcbuf[i] = i;
    }
    
    for (i = 0; i < 35; i++)
    {
        destbuf[i] = 100 + i;
    }
    
    for (i = 0; i < 4; i++)
    {
        maskbuf[i] = (UINT64)-1;
    }
    
    dg_copymaskeduint32sarea (
        (unsigned char*)destbuf, // pdest
        5, // destwidth,     // in pixels 
        7, // destheight,    // in pixels
        (unsigned char*)srcbuf, // psrc,  
        0, // srcwidth,      // in pixels 
        4, // srcheight,     // in pixels and also maskheight
        (unsigned char*)maskbuf, //  pmask, // maskwidth = srcwidth rounded up to nearest multiple of 64
        0, // xoffsetindest,  // left edge of src is here relative to left edge of dest
        0); // yoffsetindest)
        
    for (i = 0; i < 35; i++)
    {
        if (destbuf[i] != 100 + i)
        {
            printf("  Fail! dg_copymaskeduint32sarea success srcwidth = 0 case, destination changed\n");
            break;
        }
    }

    // success srcheight = 0 case (nothing gets copied)
    for (i = 0; i < 12; i++)
    {
        srcbuf[i] = i;
    }
    
    for (i = 0; i < 35; i++)
    {
        destbuf[i] = 100 + i;
    }
    
    for (i = 0; i < 4; i++)
    {
        maskbuf[i] = (UINT64)-1;
    }
    
    dg_copymaskeduint32sarea (
        (unsigned char*)destbuf, // pdest
        5, // destwidth,     // in pixels 
        7, // destheight,    // in pixels
        (unsigned char*)srcbuf, // psrc,  
        3, // srcwidth,      // in pixels 
        0, // srcheight,     // in pixels and also maskheight
        (unsigned char*)maskbuf, //  pmask, // maskwidth = srcwidth rounded up to nearest multiple of 64
        0, // xoffsetindest,  // left edge of src is here relative to left edge of dest
        0); // yoffsetindest)
        
    for (i = 0; i < 35; i++)
    {
        if (destbuf[i] != 100 + i)
        {
            printf("  Fail! dg_copymaskeduint32sarea success srcheight = 0 case, destination changed\n");
            break;
        }
    }
    
    // success destwidth = 0 case (nothing gets copied)
    for (i = 0; i < 12; i++)
    {
        srcbuf[i] = i;
    }
    
    for (i = 0; i < 35; i++)
    {
        destbuf[i] = 100 + i;
    }
    
    for (i = 0; i < 4; i++)
    {
        maskbuf[i] = (UINT64)-1;
    }
    
    dg_copymaskeduint32sarea (
        (unsigned char*)destbuf, // pdest
        0, // destwidth,     // in pixels 
        7, // destheight,    // in pixels
        (unsigned char*)srcbuf, // psrc,  
        3, // srcwidth,      // in pixels 
        4, // srcheight,     // in pixels and also maskheight
        (unsigned char*)maskbuf, //  pmask, // maskwidth = srcwidth rounded up to nearest multiple of 64
        0, // xoffsetindest,  // left edge of src is here relative to left edge of dest
        0); // yoffsetindest)
        
    for (i = 0; i < 35; i++)
    {
        if (destbuf[i] != 100 + i)
        {
            printf("  Fail! dg_copymaskeduint32sarea success destwidth = 0 case, destination changed\n");
            break;
        }
    }
    
    // success destheight = 0 case (nothing gets copied)
    for (i = 0; i < 12; i++)
    {
        srcbuf[i] = i;
    }
    
    for (i = 0; i < 35; i++)
    {
        destbuf[i] = 100 + i;
    }
    
    for (i = 0; i < 4; i++)
    {
        maskbuf[i] = (UINT64)-1;
    }
    
    dg_copymaskeduint32sarea (
        (unsigned char*)destbuf, // pdest
        5, // destwidth,     // in pixels 
        0, // destheight,    // in pixels
        (unsigned char*)srcbuf, // psrc,  
        3, // srcwidth,      // in pixels 
        4, // srcheight,     // in pixels and also maskheight
        (unsigned char*)maskbuf, //  pmask, // maskwidth = srcwidth rounded up to nearest multiple of 64
        0, // xoffsetindest,  // left edge of src is here relative to left edge of dest
        0); // yoffsetindest)
        
    for (i = 0; i < 35; i++)
    {
        if (destbuf[i] != 100 + i)
        {
            printf("  Fail! dg_copymaskeduint32sarea success destheight = 0 case, destination changed\n");
            break;
        }
    }
    
    // success 0 0 copyall case 
    for (i = 0; i < 12; i++)       // 0 1 2
    {                              // 3 4 5
        srcbuf[i] = i;             // 6 7 8
    }                              // 9 10 11
    
    for (i = 0; i < 35; i++)       // 100 101 102 103 104
    {                              // 105 106 107 108 109
        destbuf[i] = 100 + i;      // 110 111 112 113 114
    }                              // 115 116 117 118 119
                                   // 120 121 122 123 124
                                   // 125 126 127 128 129
                                   // 130 131 132 133 134
                                   
    for (i = 0; i < 4; i++)        // E000000000000000  (bswapped)
    {                              // E000000000000000  (bswapped)
        maskbuf[i] = 0xE0;         // E000000000000000  (bswapped)
    }                              // E000000000000000  (bswapped)
    
    dg_copymaskeduint32sarea (
        (unsigned char*)destbuf, // pdest
        5, // destwidth,     // in pixels 
        7, // destheight,    // in pixels
        (unsigned char*)srcbuf, // psrc,  
        3, // srcwidth,      // in pixels 
        4, // srcheight,     // in pixels and also maskheight
        (unsigned char*)maskbuf, //  pmask, // maskwidth = srcwidth rounded up to nearest multiple of 64
        0, // xoffsetindest,  // left edge of src is here relative to left edge of dest
        0); // yoffsetindest)
        
    if (destbuf[0] != 0)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (0, 0) wrong. Expected 0, got %d\n", destbuf[0]);
    }
    
    if (destbuf[1] != 1)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (0, 1) wrong. Expected 1, got %d\n", destbuf[1]);
    }
    
    if (destbuf[2] != 2)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (0, 2) wrong. Expected 2, got %d\n", destbuf[2]);
    }
    
    if (destbuf[3] != 103)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (0, 3) wrong. Expected 103, got %d\n", destbuf[3]);
    }
    
    if (destbuf[5] != 3)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (1, 0) wrong\n");
    }
    
    if (destbuf[6] != 4)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (1, 1) wrong\n");
    }
    
    if (destbuf[7] != 5)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (1, 2) wrong\n");
    }
    
    if (destbuf[8] != 108)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (1, 3) wrong\n");
    }
    
    if (destbuf[10] != 6)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (2, 0) wrong\n");
    }
    
    if (destbuf[11] != 7)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (2, 1) wrong\n");
    }
    
    if (destbuf[12] != 8)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (2, 2) wrong\n");
    }
    
    if (destbuf[13] != 113)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (2, 3) wrong\n");
    }
    
    if (destbuf[15] != 9)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (3, 0) wrong. Expected 9, got %d\n", destbuf[15]);
    }
    
    if (destbuf[16] != 10)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (3, 1) wrong. Expected 10, got %d\n", destbuf[16]);
    }
    
    if (destbuf[17] != 11)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (3, 2) wrong. Expected 11, got %d\n", destbuf[17]);
    }
    
    if (destbuf[18] != 118)
    {
        printf("  Fail! dg_copymaskeduint32sarea success 0 0 copyall case, destination (3, 3) wrong. Expected 118, got %d\n", destbuf[18]);
    }
    
    // success -1 -2 copyall case 
    for (i = 0; i < 12; i++)
    {
        srcbuf[i] = i;
    }
    
    for (i = 0; i < 35; i++)
    {
        destbuf[i] = 100 + i;
    }
    
    for (i = 0; i < 4; i++)
    {
        maskbuf[i] = (UINT64)-1;
    }
    
    dg_copymaskeduint32sarea (
        (unsigned char*)destbuf, // pdest
        5, // destwidth,     // in pixels 
        7, // destheight,    // in pixels
        (unsigned char*)srcbuf, // psrc,  
        3, // srcwidth,      // in pixels 
        4, // srcheight,     // in pixels and also maskheight
        (unsigned char*)maskbuf, //  pmask, // maskwidth = srcwidth rounded up to nearest multiple of 64
        -1, // xoffsetindest,  // left edge of src is here relative to left edge of dest
        -2); // yoffsetindest)
        
    if (destbuf[0] != 7)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (0, 0) wrong\n");
    }
    
    if (destbuf[1] != 8)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (0, 1) wrong\n");
    }
    
    if (destbuf[2] != 102)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (0, 2) wrong\n");
    }
    
    if (destbuf[3] != 103)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (0, 3) wrong\n");
    }
    
    if (destbuf[4] != 104)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (0, 4) wrong\n");
    }
    
    if (destbuf[5] != 10)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (1, 0) wrong\n");
    }
    
    if (destbuf[6] != 11)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (1, 1) wrong\n");
    }
    
    if (destbuf[7] != 107)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (1, 2) wrong\n");
    }
    
    if (destbuf[8] != 108)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (1, 3) wrong\n");
    }
    
    if (destbuf[9] != 109)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (1, 4) wrong\n");
    }
    
    if (destbuf[10] != 110)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (2, 0) wrong\n");
    }
    
    if (destbuf[11] != 111)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (2, 1) wrong\n");
    }
    
    if (destbuf[12] != 112)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (2, 2) wrong\n");
    }
    
    if (destbuf[13] != 113)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (2, 3) wrong\n");
    }
    
    if (destbuf[14] != 114)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (2, 4) wrong\n");
    }
    
    if (destbuf[15] != 115)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (3, 0) wrong\n");
    }
    
    if (destbuf[16] != 116)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (3, 1) wrong\n");
    }
    
    if (destbuf[17] != 117)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (3, 2) wrong\n");
    }
    
    if (destbuf[18] != 118)
    {
        printf("  Fail! dg_copymaskeduint32sarea success -1 -2 copyall case, destination (3, 3) wrong\n");
    }
}


int main(int argc, char* argv[])
{
    testdg_maskedmovenrowsuint32s ();
    testdg_copymaskeduint32sarea ();

	return(0);
}
