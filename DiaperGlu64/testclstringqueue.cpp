// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.7.
//
//    DiaperGlu v5.7 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.7 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.7; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// August 26, 2022            //
// version 5.7                //
// /////////////////////////////

#include "diapergluforth.h"
#include "testdglu.h"

/*
    void dg_initlstringqueue (
        Bufferhandle *pBHarrayhead,
        UINT64 growby,
        UINT64 maxsize,
        UINT64 switchlength,
        Lstringqueueheader* pLstringqueueheader)
*/

void testdg_initlstringqueue()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    
    Lstringqueueheader mylsqheader;
    
    UINT64 i = 0;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n---\ntesting dg_initlstringqueue\n");

#ifndef DGLU_NO_DIAPER

    // bad memory at header case
    dg_initerrors(&BHarrayhead, 100, &pError);

    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        (Lstringqueueheader*)badbufferhandle); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_initlstringqueuename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue bad memory at header case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_fillwithbytename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue bad memory at header case - got wrong error one below top\n");
    }

    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);

#endif

    // bad switchlength case
    dg_initerrors(&BHarrayhead, 100, &pError);

    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        (UINT64)-1,    // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_initlstringqueuename)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue bad switchlength case - got wrong error on top\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_queueswitchlengthtoobigerror)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue bad switchlength case - got wrong error one below top\n");
    }

    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    // success case
    dg_initerrors(&BHarrayhead, 100, &pError);

    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case - got an error\n");
    }

    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case - got an error\n");
    }
    
    if (mylsqheader.lstringoffsetbufferida != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case - got wrong 1st buffer id\n");
    }
    
    if (mylsqheader.lstringstringbufferida != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case - got wrong 2nd buffer id\n");
    }
    
    if (mylsqheader.lstringoffsetbufferidb != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case - got wrong 1st buffer id\n");
    }
    
    if (mylsqheader.lstringstringbufferidb != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case - got wrong 2nd buffer id\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case - got wrong pop index\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}

/*
void dg_pushlstringqueuehead (
    Bufferhandle* pBHarrayhead,
    Lstringqueueheader* pLstringqueueheader,
    unsigned char* pstring,
    UINT64 stringlength)
*/

void testdg_pushlstringqueuehead()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    
    Lstringqueueheader mylsqheader;
    
    UINT64 i = 0;
    
    unsigned char* plstring;
    UINT64 lstringlength;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushlstringqueuehead\n");


    // success case 1st push fits
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push fits - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"dog",
        3);

    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push fits - got an error\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 1st push fits - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 1st push fits - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 1st push fits - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 1st push fits - got wrong pop index\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferida,
		    mylsqheader.lstringstringbufferida,
		    0,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push fits - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push fits - lstring0[0] wrong\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push fits - lstring0[1] wrong\n");
    }
    
    if (plstring[2] != 'g')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push fits - lstring0[2] wrong\n");
    }
    
    if (lstringlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push fits - lstring0 length wrong\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 1st push doesn't fit
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        8,           // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push doesn't fit - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"dogcatzebra",
        11);

    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push doesn't fit - got an error\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 1st push doesn't fit - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 8)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 1st push doesn't fit - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 1st push doesn't fit - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 1st push doesn't fit - got wrong pop index\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferida,
		    mylsqheader.lstringstringbufferida,
		    0,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push doesn't fit - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push doesn't fit - lstring0[0] wrong\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push doesn't fit - lstring0[1] wrong\n");
    }
    
    if (plstring[2] != 'g')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push doesn't fit - lstring0[2] wrong\n");
    }
    
    if (plstring[3] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push doesn't fit - lstring0[3] wrong\n");
    }
    
    if (plstring[4] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push doesn't fit - lstring0[4] wrong\n");
    }
    
    if (plstring[5] != 't')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push doesn't fit - lstring0[5] wrong\n");
    }
    
    if (plstring[6] != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push doesn't fit - lstring0[6] wrong\n");
    }
    
    if (plstring[10] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push doesn't fit - lstring0[10] wrong\n");
    }
    
    if (lstringlength != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 1st push doesn't fit - lstring0 length wrong\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 2nd push fits
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"dog",
        3);

    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - got an error\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - got an error\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 2nd push fits - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 2nd push fits - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 2nd push fits - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 2nd push fits - got wrong pop index\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferida,
		    mylsqheader.lstringstringbufferida,
		    0,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - lstring0[0] wrong\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - lstring0[1] wrong\n");
    }
    
    if (plstring[2] != 'g')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - lstring0[2] wrong\n");
    }
    
    if (lstringlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - lstring0 length wrong\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferida,
		    mylsqheader.lstringstringbufferida,
		    1,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - lstring1[0] wrong\n");
    }
    
    if (plstring[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - lstring1[1] wrong\n");
    }
    
    if (plstring[2] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - lstring1[2] wrong\n");
    }
    
    if (plstring[3] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - lstring1[3] wrong\n");
    }
    
    if (plstring[4] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - lstring1[4] wrong\n");
    }
    
    if (lstringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - lstring0 length wrong\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 2nd push doesn't fit
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        7,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"dog",
        3);

    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - got an error\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - got an error\n");
    }
    
    if (mylsqheader.pusharray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 2nd push doesn't fit - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 2nd push doesn't doesn't fit - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 2nd push doesn't doesn't fit - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 2nd push doesn't doesn't fit - got wrong pop index\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferida,
		    mylsqheader.lstringstringbufferida,
		    0,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - lstring0[0] wrong\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - lstring0[1] wrong\n");
    }
    
    if (plstring[2] != 'g')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - lstring0[2] wrong\n");
    }
    
    if (lstringlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push fits - lstring0 length wrong\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferidb,
		    mylsqheader.lstringstringbufferidb,
		    0,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - lstring1[0] wrong\n");
    }
    
    if (plstring[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - lstring1[1] wrong\n");
    }
    
    if (plstring[2] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - lstring1[2] wrong\n");
    }
    
    if (plstring[3] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - lstring1[3] wrong\n");
    }
    
    if (plstring[4] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - lstring1[4] wrong\n");
    }
    
    if (lstringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 2nd push doesn't fit - lstring0 length wrong\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 3rd push doesn't fit
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        7,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"dog",
        3);

    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - got an error\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - got an error\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - got an error getting pointer to lstring\n");
    }
    
    if (mylsqheader.pusharray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 3rd push doesn't fit - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 3rd push doesn't doesn't fit - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 3rd push doesn't doesn't fit - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 3rd push doesn't doesn't fit - got wrong pop index\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferida,
		    mylsqheader.lstringstringbufferida,
		    0,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'd')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring0[0] wrong\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring0[1] wrong\n");
    }
    
    if (plstring[2] != 'g')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring0[2] wrong\n");
    }
    
    if (lstringlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push fits - lstring0 length wrong\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferidb,
		    mylsqheader.lstringstringbufferidb,
		    0,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring1[0] wrong\n");
    }
    
    if (plstring[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring1[1] wrong\n");
    }
    
    if (plstring[2] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring1[2] wrong\n");
    }
    
    if (plstring[3] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring1[3] wrong\n");
    }
    
    if (plstring[4] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring1[4] wrong\n");
    }
    
    if (lstringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring0 length wrong\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferidb,
		    mylsqheader.lstringstringbufferidb,
		    1,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit a - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring2[0] wrong\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring2[1] wrong\n");
    }
    
    if (plstring[2] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring2[2] wrong\n");
    }
    
    if (plstring[3] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring2[3] wrong\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring0 length wrong\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 3rd push doesn't fit b
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        7,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"dog",
        3);

    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - got an error\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (mylsqheader.magic != dg_lstringqueuemagic)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - got an error\n");
    }
    
    // switching pop index to b
    mylsqheader.poparray = 1;
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - got an error pushing lstring\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 3rd push doesn't fit b - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 3rd push doesn't doesn't fit b - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 3rd push doesn't doesn't fit b - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 3rd push doesn't doesn't fit b - got wrong pop index\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferida,
		    mylsqheader.lstringstringbufferida,
		    0,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - lstring0[0] wrong\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - lstring0[1] wrong\n");
    }
    
    if (plstring[2] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - lstring0[2] wrong\n");
    }
    
    if (plstring[3] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - lstring0[2] wrong\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push fits b - lstring0 length wrong\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferidb,
		    mylsqheader.lstringstringbufferidb,
		    0,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - lstring1[0] wrong\n");
    }
    
    if (plstring[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - lstring1[1] wrong\n");
    }
    
    if (plstring[2] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - lstring1[2] wrong\n");
    }
    
    if (plstring[3] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - lstring1[3] wrong\n");
    }
    
    if (plstring[4] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - lstring1[4] wrong\n");
    }
    
    if (lstringlength != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit b - lstring1 length wrong\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case 3rd push doesn't fit c
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        7,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"dog",
        3);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - got an error pushing head\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - got an error pushing head\n");
    }
    
    // switching pop index to b
    mylsqheader.poparray = 1;
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - got an error initializing lstringqueue\n");
    }
    
    // switching pop array back to a
    mylsqheader.poparray = 0;
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"giraffe",
        7);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - got an error pushing lstring\n");
    }
    
    if (mylsqheader.pusharray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 3rd push doesn't fit c - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 3rd push doesn't doesn't fit c - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 3rd push doesn't doesn't fit c - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_initlstringqueue success case 3rd push doesn't doesn't fit c - got wrong pop index\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferida,
		    mylsqheader.lstringstringbufferida,
		    0,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - lstring0[0] wrong\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - lstring0[1] wrong\n");
    }
    
    if (plstring[2] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - lstring0[2] wrong\n");
    }
    
    if (plstring[3] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - lstring0[2] wrong\n");
    }
    
    if (lstringlength != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push fits c - lstring0 length wrong\n");
    }
    
    plstring = dg_getplstring(
            &BHarrayhead,
		    mylsqheader.lstringoffsetbufferidb,
		    mylsqheader.lstringstringbufferidb,
		    0,
		    &lstringlength);
      
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - got an error getting pointer to lstring\n");
    }
    
    if (plstring[0] != 'g')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - lstring1[0] wrong\n");
    }
    
    if (plstring[1] != 'i')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - lstring1[1] wrong\n");
    }
    
    if (plstring[2] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - lstring1[2] wrong\n");
    }
    
    if (plstring[3] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - lstring1[3] wrong\n");
    }
    
    if (plstring[4] != 'f')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - lstring1[4] wrong\n");
    }
    
    if (plstring[5] != 'f')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - lstring1[5] wrong\n");
    }
    
    if (plstring[6] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit c - lstring1[6] wrong\n");
    }
    
    if (lstringlength != 7)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushlstringqueuehead success case 3rd push doesn't fit - lstring1 length wrong\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_poplstringqueuetail()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    
    Lstringqueueheader mylsqheader;
    
    UINT64 i = 0;
    
    unsigned char* plstring;
    UINT64 lstringlength;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_poplstringqueuetail\n");


    // success case empty queue
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case empty queue - got an error initializing lstringqueue\n");
    }
    
    plstring = dg_poplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case empty queue - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case empty queue - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case empty queue - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case empty queue - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case empty queue - got wrong pop index\n");
    }
    
    if (plstring != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case empty queue - got wrong pointer to lstring\n");
    }
    
    if (lstringlength != 0)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case     empty queue got wrong lstring length\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case one thing in queue
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case one thing in queue - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case one thing in queue - got an error pushing 1st thing to queue\n");
    }
    
    plstring = dg_poplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case one thing in queue - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case one thing in queue - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case one thing in queue - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case one thing in queue - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case one thing in queue - got wrong pop index\n");
    }
    
    if (plstring[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case one thing in queue - got wrong first character\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case one thing in queue - got wrong second character\n");
    }
    
    if (plstring[2] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case one thing in queue - got wrong third character\n");
    }
    
    if (plstring[3] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case one thing in queue - got wrong fourth character\n");
    }
    
    if (lstringlength != 4)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case     one thing in queue got wrong lstring length\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case two things in queue
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue - got an error pushing 1st thing to queue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue - got an error pushing 2nd thing to queue\n");
    }
    
    plstring = dg_poplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue - got wrong pop index\n");
    }
    
    if (plstring[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue - got wrong first character\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue - got wrong second character\n");
    }
    
    if (plstring[2] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue - got wrong third character\n");
    }
    
    if (plstring[3] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue - got wrong fourth character\n");
    }
    
    if (lstringlength != 4)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case     two things in queue got wrong lstring length\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
   
    // success case two things in queue b
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuehead success case two things in queue b - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuehead success case two things in queue b - got an error pushing 1st thing to queue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuehead success case two things in queue b - got an error pushing 2nd thing to queue\n");
    }
    
    plstring = dg_poplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuehead success case two things in queue b - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong pop index\n");
    }
    
    if (plstring[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong first character\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong second character\n");
    }
    
    if (plstring[2] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong third character\n");
    }
    
    if (plstring[3] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong fourth character\n");
    }
    
    if (lstringlength != 4)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case     two things in queue b got wrong lstring length\n");
    }
    
    plstring = dg_poplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got an error popping queue 2nd time\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong pop index\n");
    }
    
    if (plstring[0] != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong first character\n");
    }
    
    if (plstring[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong second character\n");
    }
    
    if (plstring[2] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong third character\n");
    }
    
    if (plstring[3] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong fourth character\n");
    }
    
    if (plstring[4] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong fourth character\n");
    }
    
    if (lstringlength != 5)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case     two things in queue b got wrong lstring length\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case two things in queue c
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        3,           // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got an error pushing 1st thing to queue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got an error pushing 2nd thing to queue\n");
    }
    
    plstring = dg_poplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue b - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong pop index\n");
    }
    
    if (plstring[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong first character\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong second character\n");
    }
    
    if (plstring[2] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong third character\n");
    }
    
    if (plstring[3] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong fourth character\n");
    }
    
    if (lstringlength != 4)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case     two things in queue c got wrong lstring length\n");
    }
    
    plstring = dg_poplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got an error popping queue 2nd time\n");
    }
    
    if (mylsqheader.pusharray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong pop index\n");
    }
    
    if (plstring[0] != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong first character\n");
    }
    
    if (plstring[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong second character\n");
    }
    
    if (plstring[2] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong third character\n");
    }
    
    if (plstring[3] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong fourth character\n");
    }
    
    if (plstring[4] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case two things in queue c - got wrong fourth character\n");
    }
    
    if (lstringlength != 5)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_poplstringqueuetail success case     two things in queue c got wrong lstring length\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_getslstringqueuetail()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    
    Lstringqueueheader mylsqheader;
    
    UINT64 i = 0;
    
    unsigned char* plstring;
    UINT64 lstringlength;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_getslstringqueuetail\n");


    // structure too small case
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail structure too small case - got an error initializing lstringqueue\n");
    }
    
    plstring = dg_getslstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader) - 1,
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError == dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail structure too small case - didn't get an error\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    // bad memory at queu header case
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    plstring = dg_getslstringqueuetail (
        &BHarrayhead,
        (Lstringqueueheader*)-1, // &mylsqheader,
        sizeof(Lstringqueueheader),
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError == dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail structure too small case - didn't get an error\n");
    }
    
    // success case empty queue
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case empty queue - got an error initializing lstringqueue\n");
    }
    
    plstring = dg_getslstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader),
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case empty queue - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case empty queue - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case empty queue - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case empty queue - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case empty queue - got wrong pop index\n");
    }
    
    if (plstring != (unsigned char*)badbufferhandle)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case empty queue - got wrong pointer to lstring\n");
    }
    
    if (lstringlength != 0)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case     empty queue got wrong lstring length\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case one thing in queue
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case one thing in queue - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case one thing in queue - got an error pushing 1st thing to queue\n");
    }
    
    plstring = dg_getslstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader),
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case one thing in queue - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case one thing in queue - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case one thing in queue - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case one thing in queue - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case one thing in queue - got wrong pop index\n");
    }
    
    if (plstring[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case one thing in queue - got wrong first character\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case one thing in queue - got wrong second character\n");
    }
    
    if (plstring[2] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case one thing in queue - got wrong third character\n");
    }
    
    if (plstring[3] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case one thing in queue - got wrong fourth character\n");
    }
    
    if (lstringlength != 4)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case     one thing in queue got wrong lstring length\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case two things in queue
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue - got an error pushing 1st thing to queue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue - got an error pushing 2nd thing to queue\n");
    }
    
    plstring = dg_getslstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader),
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue - got wrong pop index\n");
    }
    
    if (plstring[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue - got wrong first character\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue - got wrong second character\n");
    }
    
    if (plstring[2] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue - got wrong third character\n");
    }
    
    if (plstring[3] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue - got wrong fourth character\n");
    }
    
    if (lstringlength != 4)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case     two things in queue got wrong lstring length\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
   
    // success case two things in queue b
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got an error pushing 1st thing to queue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got an error pushing 2nd thing to queue\n");
    }
    
    plstring = dg_getslstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader),
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong pop index\n");
    }
    
    if (plstring[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong first character\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong second character\n");
    }
    
    if (plstring[2] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong third character\n");
    }
    
    if (plstring[3] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong fourth character\n");
    }
    
    if (lstringlength != 4)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case     two things in queue b got wrong lstring length\n");
    }
    
    mylsqheader.popindex++;
    
    plstring = dg_getslstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader),
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got an error popping queue 2nd time\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong pop index\n");
    }
    
    if (plstring[0] != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong first character\n");
    }
    
    if (plstring[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong second character\n");
    }
    
    if (plstring[2] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong third character\n");
    }
    
    if (plstring[3] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong fourth character\n");
    }
    
    if (plstring[4] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong fourth character\n");
    }
    
    if (lstringlength != 5)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case     two things in queue b got wrong lstring length\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case two things in queue c
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        3,           // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got an error pushing 1st thing to queue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got an error pushing 2nd thing to queue\n");
    }
    
    plstring = dg_getslstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader),
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue b - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong pop index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mylsqheader.popindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (plstring[0] != 'c')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong first character\n");
    }
    
    if (plstring[1] != 'o')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong second character\n");
    }
    
    if (plstring[2] != 'w')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong third character\n");
    }
    
    if (plstring[3] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong fourth character\n");
    }
    
    if (lstringlength != 4)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case     two things in queue c got wrong lstring length\n");
    }
    
    mylsqheader.popindex++;
    
    plstring = dg_getslstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader),
        &lstringlength);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got an error popping queue 2nd time\n");
    }
    
    if (mylsqheader.pusharray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong pop index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mylsqheader.popindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    if (plstring[0] != 'z')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong first character\n");
    }
    
    if (plstring[1] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong second character\n");
    }
    
    if (plstring[2] != 'b')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong third character\n");
    }
    
    if (plstring[3] != 'r')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong fourth character\n");
    }
    
    if (plstring[4] != 'a')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case two things in queue c - got wrong fourth character\n");
    }
    
    if (lstringlength != 5)
    {   dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_getslstringqueuetail success case     two things in queue c got wrong lstring length\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}


void testdg_dropslstringqueuetail()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    
    Lstringqueueheader mylsqheader;
    
    UINT64 i = 0;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_dropslstringqueuetail\n");


    // structure too small case
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail structure too small case - got an error initializing lstringqueue\n");
    }
        
    dg_droplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader) - 1);

    pError = dg_poperror(&BHarrayhead);

    if (pError == dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail structure too small case - didn't get an error\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    // bad memory at queu header case
    dg_initerrors(&BHarrayhead, 100, &pError);
        
    dg_droplstringqueuetail (
        &BHarrayhead,
        (Lstringqueueheader*)-1,
        sizeof(Lstringqueueheader));

    pError = dg_poperror(&BHarrayhead);

    if (pError == dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail structure too small case - didn't get an error\n");
    }
    
    // success case empty queue
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case empty queue - got an error initializing lstringqueue\n");
    }
        
    dg_droplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader));

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case empty queue - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case empty queue - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case empty queue - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case empty queue - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case empty queue - got wrong pop index\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case one thing in queue
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case one thing in queue - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case one thing in queue - got an error pushing 1st thing to queue\n");
    }
    
    dg_droplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader));

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case one thing in queue - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case one thing in queue - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case one thing in queue - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case one thing in queue - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case one thing in queue - got wrong pop index\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case two things in queue
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue - got an error pushing 1st thing to queue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue - got an error pushing 2nd thing to queue\n");
    }
    
    dg_droplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader));

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue - got wrong pop index\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
   
    // success case two things in queue b
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        0x2000,      // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got an error pushing 1st thing to queue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got an error pushing 2nd thing to queue\n");
    }
    
    dg_droplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader));

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got wrong pop index\n");
    }
    
    dg_droplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader));

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got an error popping queue 2nd time\n");
    }
    
    if (mylsqheader.pusharray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 0x2000)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got wrong pop index\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
    
    
    // success case two things in queue c
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    dg_initlstringqueue (
        &BHarrayhead,
	    0x1000,      // growby,
        (UINT64)-1,  // maxsize,
        3,           // switchlength,
        &mylsqheader); // pLstringqueueheader)

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue c - got an error initializing lstringqueue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"cows",
        4);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue c - got an error pushing 1st thing to queue\n");
    }
    
    dg_pushlstringqueuehead (
        &BHarrayhead,
        &mylsqheader,
        (unsigned char*)"zebra",
        5);

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue c - got an error pushing 2nd thing to queue\n");
    }
    
    dg_droplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader));

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue c - got an error popping queue\n");
    }
    
    if (mylsqheader.pusharray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue c - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue b - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue c - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue c - got wrong pop index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mylsqheader.popindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    dg_droplstringqueuetail (
        &BHarrayhead,
        &mylsqheader,
        sizeof(Lstringqueueheader));

    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue c - got an error popping queue 2nd time\n");
    }
    
    if (mylsqheader.pusharray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue c - got wrong push array\n");
    }
    
    if (mylsqheader.switchlength != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue c - got wrong switchlength\n");
    }
    
    if (mylsqheader.poparray != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue c - got wrong pop array\n");
    }
    
    if (mylsqheader.popindex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_dropslstringqueuetail success case two things in queue c - got wrong pop index, expected 0, got ");
        dg_writestdoutuinttodec(&BHarrayhead, mylsqheader.popindex);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}

void testdg_newfreesharedlstringqueue()
{
    const char* pError = NULL;

    Bufferhandle BHarrayhead;
    
    UINT64 sharedquehandlebufferid;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_newsharedlstringqueue and dg_freesharedlstringqueue\n");

    // success case
    dg_initerrors(&BHarrayhead, 100, &pError);
    
    sharedquehandlebufferid = dg_newsharedlstringqueue(
        &BHarrayhead,
        0x1000,      // growby,       // of the shared queue buffers
        (UINT64)-1,  // maxsize,      // ""
        0x800);      // switchlength) // ""
        
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_new and free sharedlstringqueue success case - got an error doing dg_newsharedlstringqueue\n");
    }
    
    dg_freesharedlstringqueue(
        &BHarrayhead,
        sharedquehandlebufferid);
        
    pError = dg_poperror(&BHarrayhead);

    if (pError != dg_noerrors)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_new and free sharedlstringqueue success case - got an error doing dg_freesharedlstringqueue\n");
    }
    
    // cleanup
    dg_clearerrors(&BHarrayhead);
    dg_freeallbuffers(&BHarrayhead);
}

// newsharedlstringqueue
// pushsharedlstringqueue
// lockpopsharedlstringqueue
// unlocksharedlstringqueue
// freesharedlstringqueue
