// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2025 James Patrick Norris
//
//    This file is part of DiaperGlu v5.14.
//
//    DiaperGlu v5.14 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.14 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.14; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// February 20, 2025          //
// version 5.14               //
// /////////////////////////////

#include "diapergluforth.h"
#include "testdglu.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
	printf("entering test\n");

	Bufferhandle BHarrayhead;

	dg_initpbharrayhead(&BHarrayhead);

	dg_printzerostring(&BHarrayhead, (unsigned char*)" Starting tests\n");
	
        dg_forthselftest();

        dg_printzerostring(&BHarrayhead, (unsigned char*)" \n All tests done.\n");

	return(0);
}
