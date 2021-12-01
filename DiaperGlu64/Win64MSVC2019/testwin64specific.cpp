// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2021 James Patrick Norris
//
//    This file is part of DiaperGlu v5.0.
//
//    DiaperGlu v5.0 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.0 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.0; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// January 9, 2021            //
// version 5.0                //
// /////////////////////////////

#include "../diapergluforth.h"
#include "../testdglu.h"


void testdg_pushsymboltowin64coffsymboltable()
{
    Bufferhandle BHarrayhead;
    const char* pError;

    unsigned char* pbuffer;
    UINT64* pbufferlength;

    UINT64 symboltablebufferid;
    UINT64 oversizesymbolnamebufferid;
    unsigned char* psymbolname;
    UINT64 symbolnamelength;
    DWORD value;
    SHORT sectionnumber;
    WORD type;
    BYTE storageclass;
    BYTE numberofauxsymbols;

    IMAGE_SYMBOL* pmyimagesymbol;
    
    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushsymboltowin64coffsymboltable\n");
    
    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    symboltablebufferid = dg_newbuffer(
        &BHarrayhead,
        0x400,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable success case - got error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    oversizesymbolnamebufferid = dg_newbuffer(
        &BHarrayhead,
        0x400,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable success case - got error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    psymbolname = (unsigned char*)"shortie";
    symbolnamelength = 7;
    value = 0x123456;
    sectionnumber = 5;
    type = 11;
    storageclass = 13;
    numberofauxsymbols = 17;

    dg_pushsymboltowin64coffsymboltable(
        &BHarrayhead,
        symboltablebufferid,
        oversizesymbolnamebufferid,
         psymbolname,
        symbolnamelength,
        value,
        sectionnumber,
        type,
        storageclass,
        numberofauxsymbols);
          
    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - got error doing dg_pushsymboltowin64coffsymboltable, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        symboltablebufferid,
        &pbufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - got error getting pointer to symbol table buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (*pbufferlength != IMAGE_SIZEOF_SYMBOL)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - length of symbol table buffer wrong\n");
    }

    pmyimagesymbol = &(((IMAGE_SYMBOL*)pbuffer)[0]);

    if (pmyimagesymbol->N.ShortName[0] != 's')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - first letter of name is wrong\n");
    }

    if (pmyimagesymbol->N.ShortName[6] != 'e')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - last letter of name is wrong\n");
    }

    if (pmyimagesymbol->N.ShortName[7] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - null after last letter of name is wrong\n");
    }

    if (pmyimagesymbol->Value != 0x123456)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - value is wrong\n");
    }

    if (pmyimagesymbol->SectionNumber != 5)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - section number is wrong\n");
    }

    if (pmyimagesymbol->Type != 11)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - type is wrong\n");
    }

    if (pmyimagesymbol->StorageClass != 13)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - storage class is wrong\n");
    }

    if (pmyimagesymbol->NumberOfAuxSymbols != 17)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - number of aux symbols is wrong\n");
    }

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        oversizesymbolnamebufferid,
        &pbufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - got error getting pointer to oversized symbol name buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (*pbufferlength != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable short name success case - length of oversized symbol name buffer not 0\n");
    }

    // oversize name success case

    dg_pushbufferuint32(
        &BHarrayhead,
        oversizesymbolnamebufferid,
        0x12837);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - got error pushing to oversized symbol name buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    psymbolname = (unsigned char*)"oversized";
    symbolnamelength = 9;
    value = 0x9123456;
    sectionnumber = 25;
    type = 31;
    storageclass = 43;
    numberofauxsymbols = 87;

    dg_pushsymboltowin64coffsymboltable(
        &BHarrayhead,
        symboltablebufferid,
        oversizesymbolnamebufferid,
        psymbolname,
        symbolnamelength,
        value,
        sectionnumber,
        type,
        storageclass,
        numberofauxsymbols);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - got error doing dg_pushsymboltowin64coffsymboltable, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        symboltablebufferid,
        &pbufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - got error getting pointer to symbol table buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (*pbufferlength != (2 * IMAGE_SIZEOF_SYMBOL))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - length of symbol table buffer wrong\n");
    }

    pmyimagesymbol = &(((IMAGE_SYMBOL*)pbuffer)[1]);

    if (pmyimagesymbol->N.LongName[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - oversize name indicator not 0\n");
    }

    if (pmyimagesymbol->N.LongName[1] != sizeof(UINT32))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - oversize name offset is wrong\n");
    }

    if (pmyimagesymbol->Value != 0x9123456)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - value is wrong\n");
    }

    if (pmyimagesymbol->SectionNumber != 25)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - section number is wrong\n");
    }

    if (pmyimagesymbol->Type != 31)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - type is wrong\n");
    }

    if (pmyimagesymbol->StorageClass != 43)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - storage class is wrong\n");
    }

    if (pmyimagesymbol->NumberOfAuxSymbols != 87)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - number of aux symbols is wrong\n");
    }

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        oversizesymbolnamebufferid,
        &pbufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - got error getting pointer to oversized symbol name buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (*pbufferlength != sizeof(UINT32) + symbolnamelength + 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsymboltowin64coffsymboltable oversized name success case - length of oversized symbol name buffer wrong\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_pushsectionlengthtowin64coffsymboltable()
{
    Bufferhandle BHarrayhead;
    const char* pError;

    unsigned char* pbuffer;
    UINT64* pbufferlength;

    UINT64 symboltablebufferid;

    UINT64 sectionlength;


    IMAGE_SYMBOL* pmyimagesymbol;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushsectionlengthtowin64coffsymboltable\n");

    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    symboltablebufferid = dg_newbuffer(
        &BHarrayhead,
        0x400,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsectionlengthtowin64coffsymboltable success case - got error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    sectionlength = 0x37823;

    dg_pushsectionlengthtowin64coffsymboltable(
        &BHarrayhead,
        symboltablebufferid,
        sectionlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsectionlengthtowin64coffsymboltable success case - got error doing dg_pushsectionlengthtowin64coffsymboltable, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        symboltablebufferid,
        &pbufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsectionlengthtowin64coffsymboltable success case - got error getting pointer to symbol table buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (*pbufferlength != IMAGE_SIZEOF_SYMBOL)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsectionlengthtowin64coffsymboltable success case - length of symbol table buffer wrong\n");
    }

    pmyimagesymbol = &(((IMAGE_SYMBOL*)pbuffer)[0]);

    if (pmyimagesymbol->N.LongName[0] != sectionlength)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsectionlengthtowin64coffsymboltable success case - section length is wrong\n");
    }

    if (pmyimagesymbol->N.LongName[1] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsectionlengthtowin64coffsymboltable success case - longname[1] is wrong\n");
    }

    if (pmyimagesymbol->Value != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsectionlengthtowin64coffsymboltable success case - value is wrong\n");
    }

    if (pmyimagesymbol->SectionNumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsectionlengthtowin64coffsymboltable success case - section number is wrong\n");
    }

    if (pmyimagesymbol->Type != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsectionlengthtowin64coffsymboltable success case - type is wrong\n");
    }

    if (pmyimagesymbol->StorageClass != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsectionlengthtowin64coffsymboltable success case - storage class is wrong\n");
    }

    if (pmyimagesymbol->NumberOfAuxSymbols != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushsectionlengthtowin64coffsymboltable short name success case - number of aux symbols is wrong\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_pushexportsymbolstowin64coffbuffers()
{
    Bufferhandle BHarrayhead;
    const char* pError;

    unsigned char* pbuffer;
    UINT64* pbufferlength;

    UINT64 symboltablebufferid;
    UINT64 oversizesymbolnamebufferid;
    UINT64 dotdrectvebufferid;
    unsigned char* pname;
    UINT64 namelength;
    DWORD value;
    SHORT sectionnumber;
    WORD type;
    BYTE storageclass;
    BYTE numberofauxsymbols;

    IMAGE_SYMBOL* pmyimagesymbol;

    UINT64 myhlistid;
    UINT64 myvalue;

    UINT64 myelementid1;
    UINT64 myelementid2;
    UINT64 myelementid3;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushexportsymbolstowin64coffbuffers\n");

    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    dg_inithlists(&BHarrayhead); 


    myhlistid = dg_newhlist(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);

        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers  success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myelementid1 = dg_newhlistelement(
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_rootelementname, // pname, // function name
        DG_ROOTELEMENTNAMELENGTH, // namelength,
        (unsigned char*)&myvalue, // pvalue, // offset in buffer to patch
        0); // valuelength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);

        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers success case - got an error making first new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    myvalue = 13;
    pname = (unsigned char*)"kymbol1"; // since they get sorted, using k because I want this name first
    namelength = 7;

    myelementid2 = dg_newhlistelement(
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        pname, 
        namelength, 
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);

        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers success case - got an error making second new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myvalue = 91;
    pname = (unsigned char*)"longsymbol2";
    namelength = 11;

    myelementid3 = dg_newhlistelement(
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        pname,
        namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);

        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers success case - got an error making third new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    symboltablebufferid = dg_newbuffer(
        &BHarrayhead,
        0x400,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers success case - got error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    oversizesymbolnamebufferid = dg_newbuffer(
        &BHarrayhead,
        0x400,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers success case - got error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dotdrectvebufferid = dg_newbuffer(
        &BHarrayhead,
        0x400,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers success case - got error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_pushbufferuint32(
        &BHarrayhead,
        oversizesymbolnamebufferid,
        0x98324);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers success case - got error pushing uint32 to oversize symbol buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_pushexportsymbolstowin64coffbuffers(
        &BHarrayhead,
        myhlistid, // exportsymbollisthlistid,
        myelementid1, // exportsymbollistparentelementid,
        symboltablebufferid,
        oversizesymbolnamebufferid,
        dotdrectvebufferid,
        3); //  dottextsectionnumber);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers short name success case - got error doing dg_pushsymboltowin64coffsymboltable, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        symboltablebufferid,
        &pbufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers short name success case - got error getting pointer to symbol table buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (*pbufferlength != (2 * IMAGE_SIZEOF_SYMBOL))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers short name success case - length of symbol table buffer wrong\n");
    }

    pmyimagesymbol = &(((IMAGE_SYMBOL*)pbuffer)[0]);

    if (pmyimagesymbol->N.ShortName[0] != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers short name success case - first letter of name is wrong\n");
    }

    if (pmyimagesymbol->N.ShortName[6] != '1')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers short name success case - last letter of name is wrong\n");
    }

    if (pmyimagesymbol->N.ShortName[7] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers short name success case - null after last letter of name is wrong\n");
    }

    if (pmyimagesymbol->Value != 13)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers short name success case - value is wrong\n");
    }

    if (pmyimagesymbol->SectionNumber != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers short name success case - section number is wrong\n");
    }

    if (pmyimagesymbol->Type != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers short name success case - type is wrong\n");
    }

    if (pmyimagesymbol->StorageClass != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers short name success case - storage class is wrong\n");
    }

    if (pmyimagesymbol->NumberOfAuxSymbols != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers short name success case - number of aux symbols is wrong\n");
    }


    pmyimagesymbol = &(((IMAGE_SYMBOL*)pbuffer)[1]);

    if (pmyimagesymbol->N.LongName[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - longname[0] not 0\n");
    }

    if (pmyimagesymbol->N.LongName[1] != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - offset in oversized name buffer incorrect\n");
    }

    if (pmyimagesymbol->Value != 91)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - value is wrong\n");
    }

    if (pmyimagesymbol->SectionNumber != 3)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - section number is wrong\n");
    }

    if (pmyimagesymbol->Type != 0x20)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - type is wrong\n");
    }

    if (pmyimagesymbol->StorageClass != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - storage class is wrong\n");
    }

    if (pmyimagesymbol->NumberOfAuxSymbols != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - number of aux symbols is wrong\n");
    }


    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        oversizesymbolnamebufferid,
        &pbufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - got error getting pointer to oversized symbol name buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (*pbufferlength != sizeof(UINT32) + namelength + 1) // namelength should still be length of oversized name
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - length of oversized symbol name buffer not correct\n");
    }

    if (pbuffer[4] != 'l')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - 1st letter of oversized name is wrong\n");
    }

    if (pbuffer[namelength + 3] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - last letter of oversized name is wrong\n");
    }

    if (pbuffer[namelength + 4] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - null after last letter of oversized name is wrong\n");
    }

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        dotdrectvebufferid,
        &pbufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - got error getting pointer to dotdirective buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (*pbufferlength != (namelength + 1) + (7 + 1) + (2*8)) // namelength should still be length of oversized name
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - length of oversized dotdirective buffer not correct\n");
    }

    if (pbuffer[0] != '/')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case -  dotdirective buffer[0] is wrong\n");
    }

    if (pbuffer[1] != 'E')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - dotdirective buffer[1] is wrong\n");
    }

    if (pbuffer[7] != ':')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - dotdirective buffer[7] is wrong\n");
    }

    if (pbuffer[7] != ':')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - dotdirective buffer[7] is wrong\n");
    }

    if (pbuffer[8] != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - dotdirective buffer[8] is wrong\n");
    }

    if (pbuffer[14] != '1')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - dotdirective buffer[14] is wrong\n");
    }

    if (pbuffer[15] != ' ')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - dotdirective buffer[15] is wrong\n");
    }

    if (pbuffer[16] != '/')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - dotdirective buffer[16] is wrong\n");
    }

    if (pbuffer[23] != ':')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - dotdirective buffer[23] is wrong\n");
    }

    if (pbuffer[24] != 'l')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - dotdirective buffer[24] is wrong\n");
    }

    if (pbuffer[34] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - dotdirective buffer[34] is wrong\n");
    }

    if (pbuffer[35] != ' ')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushexportsymbolstowin64coffbuffers long name success case - dotdirective buffer[35] is wrong\n");
    }
    

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}


void testdg_pushimportsymbolstowin64coffbuffers()
{
    Bufferhandle BHarrayhead;
    const char* pError;

    unsigned char* pbuffer;
    UINT64* pbufferlength;

    UINT64 symboltablebufferid;
    UINT64 oversizesymbolnamebufferid;
    UINT64 relocationtablebufferid;
    unsigned char* pname;
    UINT64 namelength;
    DWORD value;
    SHORT sectionnumber;
    WORD type;
    BYTE storageclass;
    BYTE numberofauxsymbols;

    IMAGE_SYMBOL* pmyimagesymbol;
    IMAGE_RELOCATION* pmyrelocations;

    UINT64 myhlistid;
    UINT64 myvalue;

    UINT64 myelementid1;
    UINT64 myelementid2;
    UINT64 myelementid3;
    UINT64 myelementid4;
    UINT64 myelementid5;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_pushimportsymbolstowin64coffbuffers\n");

    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    dg_inithlists(&BHarrayhead);


    myhlistid = dg_newhlist(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);

        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers  success case - got an error making a new hlist, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myelementid1 = dg_newhlistelement(
        &BHarrayhead,
        myhlistid, // hlistid,
        DG_ENDOFLIST, // parentelementid,
        (unsigned char*)dg_rootelementname, // pname, // function name
        DG_ROOTELEMENTNAMELENGTH, // namelength,
        (unsigned char*)&myvalue, // pvalue, // offset in buffer to patch
        0); // valuelength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);

        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers success case - got an error making first new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }


    myvalue = 13;
    pname = (unsigned char*)"kymbol1"; // since they get sorted, using k because I want this name first
    namelength = 7;

    myelementid2 = dg_newhlistelement(
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        pname,
        namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);

        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers success case - got an error making second new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myvalue = 91;
    pname = (unsigned char*)"longsymbol2";
    namelength = 11;

    myelementid3 = dg_newhlistelement(
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        pname,
        namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);

        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers success case - got an error making third new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myvalue = 137;
    pname = (unsigned char*)"kymbol1"; // since they get sorted, using k because I want this name first
    namelength = 7;

    myelementid4 = dg_newhlistelement(
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        pname,
        namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);

        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers success case - got an error making second new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    myvalue = 96731;
    pname = (unsigned char*)"longsymbol2";
    namelength = 11;

    myelementid5 = dg_newhlistelement(
        &BHarrayhead,
        myhlistid, // hlistid,
        myelementid1, // parentelementid,
        pname,
        namelength,
        (unsigned char*)&myvalue, // pvalue,
        sizeof(UINT64)); // valuelength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);

        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers success case - got an error making third new hlist element, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    symboltablebufferid = dg_newbuffer(
        &BHarrayhead,
        0x400,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers success case - got error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    oversizesymbolnamebufferid = dg_newbuffer(
        &BHarrayhead,
        0x400,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers success case - got error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    relocationtablebufferid = dg_newbuffer(
        &BHarrayhead,
        0x400,
        (UINT64)-1,
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers success case - got error making a new buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_pushbufferuint32(
        &BHarrayhead,
        oversizesymbolnamebufferid,
        0x98324);

    if (pError != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers success case - got error pushing uint32 to oversize symbol buffer, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_pushimportsymbolstowin64coffbuffers(
        &BHarrayhead,
        myhlistid, // importsymbollisthlistid,
        myelementid1, // importsymbollistparentelementid,
        symboltablebufferid,
        oversizesymbolnamebufferid,
        relocationtablebufferid); 

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers short name success case - got error doing dg_pushsymboltowin64coffsymboltable, got:\n");
        // pError = dg_poperror(&BHarrayhead);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_forthdoterrors(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        symboltablebufferid,
        &pbufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers short name success case - got error getting pointer to symbol table buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (*pbufferlength != (2 * IMAGE_SIZEOF_SYMBOL))
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers short name success case - length of symbol table buffer wrong\n");
    }

    pmyimagesymbol = &(((IMAGE_SYMBOL*)pbuffer)[0]);

    if (pmyimagesymbol->N.ShortName[0] != 'k')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers short name success case - first letter of name is wrong\n");
    }

    if (pmyimagesymbol->N.ShortName[6] != '1')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers short name success case - last letter of name is wrong\n");
    }

    if (pmyimagesymbol->N.ShortName[7] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers short name success case - null after last letter of name is wrong\n");
    }

    if (pmyimagesymbol->Value != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers short name success case - value is wrong\n");
    }

    if (pmyimagesymbol->SectionNumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers short name success case - section number is wrong\n");
    }

    if (pmyimagesymbol->Type != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers short name success case - type is wrong\n");
    }

    if (pmyimagesymbol->StorageClass != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers short name success case - storage class is wrong\n");
    }

    if (pmyimagesymbol->NumberOfAuxSymbols != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers short name success case - number of aux symbols is wrong\n");
    }


    pmyimagesymbol = &(((IMAGE_SYMBOL*)pbuffer)[1]);

    if (pmyimagesymbol->N.LongName[0] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - longname[0] not 0\n");
    }

    if (pmyimagesymbol->N.LongName[1] != 4)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - offset in oversized name buffer incorrect\n");
    }

    if (pmyimagesymbol->Value != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - value is wrong\n");
    }

    if (pmyimagesymbol->SectionNumber != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - section number is wrong\n");
    }

    if (pmyimagesymbol->Type != 0x0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - type is wrong\n");
    }

    if (pmyimagesymbol->StorageClass != 2)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - storage class is wrong\n");
    }

    if (pmyimagesymbol->NumberOfAuxSymbols != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - number of aux symbols is wrong\n");
    }


    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        oversizesymbolnamebufferid,
        &pbufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - got error getting pointer to oversized symbol name buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (*pbufferlength != sizeof(UINT32) + namelength + 1) // namelength should still be length of oversized name
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - length of oversized symbol name buffer not correct\n");
    }

    if (pbuffer[4] != 'l')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - 1st letter of oversized name is wrong\n");
    }

    if (pbuffer[namelength + 3] != '2')
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - last letter of oversized name is wrong\n");
    }

    if (pbuffer[namelength + 4] != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - null after last letter of oversized name is wrong\n");
    }

    pbuffer = dg_getpbuffer(
        &BHarrayhead,
        relocationtablebufferid,
        &pbufferlength);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - got error getting pointer to dotdirective buffer, got ");
        pError = dg_poperror(&BHarrayhead);
        dg_printzerostring(&BHarrayhead, (unsigned char*)pError);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    if (*pbufferlength != (4 * sizeof(IMAGE_RELOCATION))) 
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case - length of relocation buffer not correct\n");
    }

    // pmyrelocations = (IMAGE_RELOCATION*)pbuffer;
    pmyrelocations = &(((IMAGE_RELOCATION*)pbuffer)[0]);

    if (pmyrelocations->VirtualAddress != 13)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case -  relocation[0] virtual address not correct\n");
    }

    if (pmyrelocations->SymbolTableIndex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case -  relocation[0] symbol table index not correct\n");
    }

    if (pmyrelocations->Type != IMAGE_REL_AMD64_ADDR64)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case -  relocation[0] type not correct\n");
    }

    pmyrelocations = &(((IMAGE_RELOCATION*)pbuffer)[1]);

    if (pmyrelocations->VirtualAddress != 137) // since they are sorted alphabetically, this one is second
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case -  relocation[1] virtual address not correct\n");
    }

    if (pmyrelocations->SymbolTableIndex != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case -  relocation[1] symbol table index not correct\n");
    }

    if (pmyrelocations->Type != IMAGE_REL_AMD64_ADDR64)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case -  relocation[1] type not correct\n");
    }

    pmyrelocations = &(((IMAGE_RELOCATION*)pbuffer)[2]);

    if (pmyrelocations->VirtualAddress != 91)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case -  relocation[2] virtual address not correct\n");
    }

    if (pmyrelocations->SymbolTableIndex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case -  relocation[2] symbol table index not correct\n");
    }

    if (pmyrelocations->Type != IMAGE_REL_AMD64_ADDR64)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case -  relocation[2] type not correct\n");
    }

    pmyrelocations = &(((IMAGE_RELOCATION*)pbuffer)[3]);

    if (pmyrelocations->VirtualAddress != 96731)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case -  relocation[3] virtual address not correct\n");
    }

    if (pmyrelocations->SymbolTableIndex != 1)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case -  relocation[3] symbol table index not correct\n");
    }  

    if (pmyrelocations->Type != IMAGE_REL_AMD64_ADDR64)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_pushimportsymbolstowin64coffbuffers long name success case -  relocation[3] type not correct\n");
    }

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthfindlibrarysymbol()
{
    Bufferhandle BHarrayhead;
    const char* perror;
    UINT64 hlibrary;
    UINT64 x;
    UINT64 (*symboladdress)(UINT64);

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthfindlibrarysymbol\n");

    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    perror = dg_loadlibrary(
        (const char*)"diapergluosapi.dll",
        &hlibrary,
        dg_success);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthfindlibrarysymbol success case - got error opening diapergluosapi.dll, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_pushdatastack(
        &BHarrayhead,
        hlibrary);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthfindlibrarysymbol success case - got error pushing library handle to data stack.\n ");

    }

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        10,
        (unsigned char*)"dg_testasm");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthfindlibrarysymbol success case - got error pushing symbol name to string stack.\n ");

    }

    dg_forthfindlibrarysymbol(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthfindlibrarysymbol success case - got error doing dg_forthfindlibrarysymbol.\n ");

    }

    symboladdress = (UINT64(*)(UINT64))dg_popdatastack(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthfindlibrarysymbol success case - got error popping symbol address off data stack.\n ");
    }

    x = (*symboladdress)(0x123456789ABCDEF);

    if (x != 0x123456789ABCDF0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthfindlibrarysymbol success case - got wrong result.\n ");
    }

    dg_freelibrary(
        hlibrary,
        dg_success);

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthcallprocaddress()
{
    Bufferhandle BHarrayhead;
    const char* perror;
    UINT64 hlibrary;
    UINT64 x;
    UINT64 symboladdress;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthcallprocaddress\n");

    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    perror = dg_loadlibrary(
        (const char*)"diapergluosapi.dll",
        &hlibrary,
        dg_success);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddress success case - got error opening diapergluosapi.dll, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_pushdatastack(
        &BHarrayhead,
        hlibrary);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddress success case - got error pushing library handle to data stack.\n ");

    }

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        10,
        (unsigned char*)"dg_testasm");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddress success case - got error pushing symbol name to string stack.\n ");

    }

    dg_forthfindlibrarysymbol(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddress success case - got error doing dg_forthfindlibrarysymbol.\n ");

    }

    symboladdress = dg_popdatastack(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddress success case - got error popping symbol address off data stack.\n ");
    }

    dg_pushdatastack(
        &BHarrayhead,
        0x123456789ABCDEF);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddress success case - got error pushing test value to data stack.\n ");
    }

    dg_pushdatastack(
        &BHarrayhead,
        1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddress success case - got error pushing number of parameters to data stack.\n ");
    }

    dg_pushdatastack(
        &BHarrayhead,
        symboladdress);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddress success case - got error pushing number of parameters to data stack.\n ");
    }

    dg_forthcallprocaddress(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddress success case - got error doing dg_forthcallprocaddress.\n ");
    }

    x = dg_popdatastack(&BHarrayhead);

    if (x != 0x123456789ABCDF0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddress success case - got wrong result.\n ");
    }

    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddress success case - got error getting data stack buffer length.\n ");
    }

    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddress success case - data stack not empty after test.\n ");
    }

    dg_freelibrary(
        hlibrary,
        dg_success);

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthcallprocaddressretuint128()
{
    Bufferhandle BHarrayhead;
    const char* perror;
    UINT64 hlibrary;
    UINT64 x;
    UINT64 symboladdress;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthcallprocaddressretuint128\n");

    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    perror = dg_loadlibrary(
        (const char*)"diapergluosapi.dll",
        &hlibrary,
        dg_success);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - got error opening diapergluosapi.dll, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_pushdatastack(
        &BHarrayhead,
        hlibrary);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - got error pushing library handle to data stack.\n ");

    }

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        20,
        (unsigned char*)"dg_testasmretuint128");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - got error pushing symbol name to string stack.\n ");

    }

    dg_forthfindlibrarysymbol(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - got error doing dg_forthfindlibrarysymbol.\n ");

    }

    symboladdress = dg_popdatastack(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - got error popping symbol address off data stack.\n ");
    }

    dg_pushdatastack(
        &BHarrayhead,
        0x123456789ABCDEF);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - got error pushing test value to data stack.\n ");
    }

    dg_pushdatastack(
        &BHarrayhead,
        1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - got error pushing number of parameters to data stack.\n ");
    }

    dg_pushdatastack(
        &BHarrayhead,
        symboladdress);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - got error pushing number of parameters to data stack.\n ");
    }

    dg_forthcallprocaddressretuint128(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - got error doing dg_forthcallprocaddress.\n ");
    }

    x = dg_popdatastack(&BHarrayhead);

    if (x != 0x123456789ABCDEE)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - got wrong hi result, expected 0x123456789ABCDEE got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_popdatastack(&BHarrayhead);

    if (x != 0x123456789ABCDF0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - got wrong lo result, expected 0x123456789ABCDF0 got ");
        dg_writestdoutuint64tohex(&BHarrayhead, x);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    }

    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - got error getting data stack buffer length.\n ");
    }

    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcallprocaddressretuint128 success case - data stack not empty after test.\n ");
    }

    dg_freelibrary(
        hlibrary,
        dg_success);

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthcalldfpprocaddress()
{
    // open diaperglu.dll and call a function with mixed floating point and integer parameters

    Bufferhandle BHarrayhead;
    const char* perror;
    UINT64 hlibrary;
    UINT64 x;
    UINT64 symboladdress;

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthcalldfpprocaddress\n");

    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);

    perror = dg_loadlibrary(
        (const char*)"diapergluosapi.dll",
        &hlibrary,
        dg_success);

    if (perror != dg_success)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - got error opening diapergluosapi.dll, got ");
        dg_printzerostring(&BHarrayhead, (unsigned char*)perror);
        dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        return;
    }

    dg_pushdatastack(
        &BHarrayhead,
        hlibrary);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - got error pushing library handle to data stack.\n ");

    }

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        10,
        (unsigned char*)"dg_f64sqrt");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - got error pushing symbol name to string stack.\n ");

    }

    dg_forthfindlibrarysymbol(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - got error doing dg_forthfindlibrarysymbol.\n ");

    }

    symboladdress = dg_popdatastack(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - got error popping symbol address off data stack.\n ");
    }

    *((FLOAT64*)(&x)) = 16.0;
    // push 4.0 to floating point stack
    dg_pushdatastack(
        &BHarrayhead,
        x);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - got error pushing 16.0 to data stack.\n ");
    }

    dg_pushdatastack(
        &BHarrayhead,
        1);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - got error pushing number of floating point parameters to data stack.\n ");
    }

    dg_pushdatastack(
        &BHarrayhead,
        0);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - got error pushing number of integer parameters to data stack.\n ");
    }

    dg_pushdatastack(
        &BHarrayhead,
        symboladdress);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - got error pushing number of parameters to data stack.\n ");
    }

    dg_forthcalldfpprocaddress(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - got error doing dg_forthcallprocaddress.\n ");
    }

    x = dg_popdatastack(&BHarrayhead);

    if (*((FLOAT64*)(&x)) != 4.0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - got wrong result.\n ");
    }

    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - got error getting data stack buffer length.\n ");
    }

    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthcalldfpprocaddress success case - data stack not empty after test.\n ");
    }

    dg_freelibrary(
        hlibrary,
        dg_success);

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void testdg_forthopenlibrarystring()
{
    Bufferhandle BHarrayhead;
    const char* perror;
    UINT64 hlibrary;
    UINT64 x;
    UINT64(*symboladdress)(UINT64);

    dg_initpbharrayhead(&BHarrayhead);

    dg_printzerostring(&BHarrayhead, (unsigned char*)"testing dg_forthopenlibrarystring\n");

    // sucess case
    dg_initbuffers(&BHarrayhead);
    dg_initvariables(&BHarrayhead);
    dg_inithlists(&BHarrayhead); // open library string makes a new wordlist... so need this...

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        18,
        (unsigned char*)"diapergluosapi.dll");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthopenlibrarystring success case - got error pushing library name to string stack.\n ");
        return;
    }

    dg_forthopenlibrarystring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthopenlibrarystring success case - got error doing dg_forthopenlibrarystring.\n ");
        return;
    }

    hlibrary = dg_popdatastack(&BHarrayhead);

    dg_pushdatastack(&BHarrayhead, hlibrary);

    // library handle should be on top of data stack

    dg_pushlstring(
        &BHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        10,
        (unsigned char*)"dg_testasm");

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthopenlibrarystring success case - got error pushing symbol name to string stack.\n ");

    }

    dg_forthfindlibrarysymbol(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthopenlibrarystring success case - got error doing dg_forthfindlibrarysymbol.\n ");

    }

    symboladdress = (UINT64(*)(UINT64))dg_popdatastack(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthopenlibrarystring success case - got error popping symbol address off data stack.\n ");
    }

    x = (*symboladdress)(0x123456789ABCDEF);

    if (x != 0x123456789ABCDF0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthopenlibrarystring success case - got wrong result.\n ");
    }

    dg_forthdrop(&BHarrayhead); // dropping word list id

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthopenlibrarystring success case - got error doing drop.\n ");
    }

    x = dg_getbufferlength(
        &BHarrayhead,
        DG_DATASTACK_BUFFERID);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthopenlibrarystring success case - got error getting data stack buffer length.\n ");
    }

    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthopenlibrarystring success case - data stack not empty after test.\n ");
    }

    dg_forthdepthstring(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthopenlibrarystring success case - got error getting string stack depth.\n ");
    }

    x = dg_popdatastack(&BHarrayhead);

    if (dg_geterrorcount(&BHarrayhead) != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthopenlibrarystring success case - got error popping data stack.\n ");
    }

    if (x != 0)
    {
        dg_printzerostring(&BHarrayhead, (unsigned char*)"FAIL dg_forthopenlibrarystring success case - string stack not empty after test.\n ");
    }

    dg_freelibrary(
        hlibrary,
        dg_success);

    dg_clearerrors(&BHarrayhead);   dg_freeallbuffers(&BHarrayhead);
}

void dg_forthfixpathstring()
{
    // I'll have to figure this one out...
    //  I didn't write down what this does... I think it has something to do with the back slashes and default path..
}

void testdg_forthrunfileandwait()
{
    //  this is tested in the sample scripts except I didn't test passing in env
}

void testdg_forthrunfileandwaitnoenvstring()
{
    // could have this run diaperglu and pass it a script file that prints out a message
    //  this is tested in the sample scripts..
}

void testdg_forthrunfileandwaitnoenvquotes()
{
    // could have this run diaperglu and pass it a script file that prints out a message
    //  this is tested in the sample scripts
}

// dg_forthdocompiletyperunfileandwaitnoenvquotes test this one from script?

void testdg_makedototobuf()
{
    // could do testasmimport script example in c code...
    //  this is tested in the sample scripts
}

