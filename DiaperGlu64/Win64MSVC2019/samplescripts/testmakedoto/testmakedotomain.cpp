// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.1.
//
//    DiaperGlu v5.1 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.1 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.1; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// January 22, 2022           //
// version 5.1                //
// /////////////////////////////

#include <stdio.h>
#include "windows.h"

// typedef __int16 INT16;
// typedef unsigned __int16 UINT16;

// typedef __int32 INT32;
// typedef unsigned __int32 UINT32;

// typedef __int64 INT64;
// typedef unsigned __int64 UINT64;

extern "C" __declspec(dllimport) UINT64 dg_firstfunction();
extern "C" __declspec(dllimport) UINT64 dg_secondfunction();

int main(int argc, char* argv[])
{
       UINT64 x;

       printf("\n\nTesting having a .cpp file call functions in a .dll made by the make .o buf function:\n\n");

       x = dg_firstfunction();
    
       printf("  called dg_firstfunction() - expected 0x1122334455667788, got 0x%08x%08x\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]);       

       x = dg_secondfunction();

       printf("  called dg_secondfunction() - expected 0x1213141516171819, got 0x%08x%08x\n\n",
         ((UINT32*)(&x))[1],
         ((UINT32*)(&x))[0]); 

	return(0);
}
