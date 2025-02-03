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

extern "C" UINT64 dg_firstfunction();
extern "C" UINT64 dg_secondfunction();

int main(int argc, char* argv[])
{
       UINT64 x;

       printf("testing the .o file made by the make .o function\n");

       x = dg_firstfunction();
    
       printf("  called dg_firstfunction() - expected 0x1122334455667788, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);       

       x = dg_secondfunction();

       printf("  called dg_secondfunction() - expected 0x1213141516171819, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]); 

	return(0);
}
