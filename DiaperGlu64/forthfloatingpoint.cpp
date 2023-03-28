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



#include "diapergluforth.h"

const char dg_pushf64tof64stackname[] = "dg_pushf64tof64stack";

void dg_pushf64tof64stack(
    Bufferhandle* pBHarrayhead,
    FLOAT64 r)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthf64stackbuffername);
        dg_pusherror(pBHarrayhead, dg_pushf64tof64stackname);
        return;
    } 
}

const char dg_popf64fromf64stackname[] = "dg_popf64fromf64stack";

FLOAT64 dg_popf64fromf64stack(Bufferhandle* pBHarrayhead)
{
    FLOAT64 r = 0.0;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    *((UINT64*)(&r)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthf64stackbuffername);
        dg_pusherror(pBHarrayhead, dg_popf64fromf64stackname);
        return(r);
    } 
    
    return(r);
}

void dg_forthtofloat (Bufferhandle* pBHarrayhead)
//     ( pstring length -- conversionflag )
//     ( -f64- f64result | )
{
    unsigned char* pstring;
    UINT64 length;
    UINT64 conversionflag;
    
	FLOAT64 result;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);


    length = dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthf64stackbuffername);
        dg_pusherror(pBHarrayhead, dg_forthtofloatname);
        return;
    } 
    
    
	pstring = (unsigned char*)dg_popdatastack(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthtofloatname);
		return;
	}
 
	result = dg_pchartof64 (
        pstring,
        length,
        &conversionflag);
        
    dg_pushdatastack(
        pBHarrayhead, 
        conversionflag);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthtofloatname);
        return;
    }
    
    if (conversionflag != FORTH_FALSE)
    {
        dg_pushbufferuint64 (
            pBHarrayhead,
            DG_F64STACK_BUFFERID,
            *((UINT64*)(&result)));  // can't cast the F64 directly to U64 because it will do a conversion
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            // dg_pusherror(pBHarrayhead, dg_forthf64stackbuffername);
            dg_pusherror(pBHarrayhead, dg_forthtofloatname);
            return;
        }
    }
}

void dg_forthfliteral (Bufferhandle* pBHarrayhead)
//                ( f1 -f- )
{
    // compile push f1 to the floating point stack
    UINT64 n;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    n = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfliteralname);
        return;
    }
    
    dg_compilepushntof64stack (
        pBHarrayhead,
        n);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfliteralname);
        return;
    }
}

void dg_forthfstore (Bufferhandle* pBHarrayhead)
{
    UINT64* addr;
    UINT64 n;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    addr = (UINT64*)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfstorename);
        return;
    }

    n = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfstorename);
        return;
    }
    
    perror = dg_putuint64(addr, n);
    
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_forthfstorename);
    }
}

void dg_forthfstar (Bufferhandle* pBHarrayhead)
{
    UINT64 n1, n2, n3;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    n1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfstarname);
        return;
    }
    
    n2 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfstarname);
        return;
    }
    
    (*((FLOAT64*)(&n3))) = (*((FLOAT64*)(&n1))) * (*((FLOAT64*)(&n2)));
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        n3);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfstarname);
        return;
    }
}

void dg_forthfplus (Bufferhandle* pBHarrayhead)
{
    UINT64 n1, n2, n3;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    n2 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfplusname);
        return;
    }
    
    n1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfplusname);
        return;
    }
    
    (*((FLOAT64*)(&n3))) = (*((FLOAT64*)(&n1))) + (*((FLOAT64*)(&n2)));
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        n3);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfplusname);
        return;
    }
}

void dg_forthfminus (Bufferhandle* pBHarrayhead)
{
    UINT64 n1, n2, n3;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    n2 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfminusname);
        return;
    }
    
    n1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfminusname);
        return;
    }
    
    (*((FLOAT64*)(&n3))) = (*((FLOAT64*)(&n1))) - (*((FLOAT64*)(&n2)));
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        n3);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfminusname);
        return;
    }
}

void dg_forthfslash (Bufferhandle* pBHarrayhead)
{
    UINT64* addr;
    UINT64 n1, n2, n3;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    n2 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfslashname);
        return;
    }
    
    n1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfslashname);
        return;
    }
    
    (*((FLOAT64*)(&n3))) = (*((FLOAT64*)(&n1))) / (*((FLOAT64*)(&n2)));
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        n3);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfslashname);
        return;
    }
}

void dg_forthfzerolessthan (Bufferhandle* pBHarrayhead)
{
    UINT64 n1, n2;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    n1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfzerolessthanname);
        return;
    }
    
    if ((*((FLOAT64*)(&n1))) < 0.0) // could just check the sign bit...
    {
        n2 = FORTH_TRUE;
    }
    else
    {
        n2 = FORTH_FALSE;
    }
    
    dg_pushdatastack(pBHarrayhead, n2);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfzerolessthanname);
        return;
    }
}

void dg_forthfzeroequals (Bufferhandle* pBHarrayhead)
{
    UINT64 n1, n2;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    n1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfzeroequalsname);
        return;
    }
    
    if ((*((FLOAT64*)(&n1))) == 0.0) // could just check the sign bit...
    {
        n2 = FORTH_TRUE;
    }
    else
    {
        n2 = FORTH_FALSE;
    }
    
    dg_pushdatastack(pBHarrayhead, n2);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfzeroequalsname);
        return;
    }
}

void dg_forthflessthan (Bufferhandle* pBHarrayhead)
{
    UINT64 n1, n2, n3;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    n2 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthflessthanname);
        return;
    }
    
    n1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthflessthanname);
        return;
    }
    
    if ((*((FLOAT64*)(&n1))) < (*((FLOAT64*)(&n2)))) // could just check the sign bit...
    {
        n3 = FORTH_TRUE;
    }
    else
    {
        n3 = FORTH_FALSE;
    }
    
    dg_pushdatastack(pBHarrayhead, n3);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthflessthanname);
        return;
    }
}

void dg_forthffetch (Bufferhandle* pBHarrayhead)
{
    UINT64* addr;
    UINT64 n;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    addr = (UINT64*)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthffetchname);
        return;
    }
    
    perror = dg_getuint64(addr, &n);
    
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_putuint64name);
        dg_pusherror(pBHarrayhead, dg_forthfstorename);
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        n);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthffetchname);
        return;
    }
}

void dg_forthfdepth (Bufferhandle* pBHarrayhead)
{
    UINT64 bufferlength;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    bufferlength = dg_getbufferlength(pBHarrayhead, DG_F64STACK_BUFFERID); 

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfdepthname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        bufferlength / sizeof(UINT64));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfdepthname);
        return;
    }
}

void dg_forthfdrop (Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfdropname);
        return;
    }
}

void dg_forthfdup (Bufferhandle* pBHarrayhead)
{
    UINT64 n;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    n = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfdupname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_F64STACK_BUFFERID, 
        n);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfdupname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_F64STACK_BUFFERID, 
        n);
            
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfdupname);
        return;
    }
}


void dg_forthfmax (Bufferhandle* pBHarrayhead)
{
    UINT64 n1, n2;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    n2 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfmaxname);
        return;
    }
    
    n1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfmaxname);
        return;
    }
    
    if ( *((FLOAT64*)(&n1)) > *((FLOAT64*)(&n2)) )
    {
        dg_pushbufferuint64(
            pBHarrayhead, 
            DG_F64STACK_BUFFERID, 
            n1);
    }
    else
    {
        dg_pushbufferuint64(
            pBHarrayhead, 
            DG_F64STACK_BUFFERID, 
            n2);
    }
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfmaxname);
        return;
    }
}

void dg_forthfmin (Bufferhandle* pBHarrayhead)
{
    UINT64 n1, n2;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    n2 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfminname);
        return;
    }
    
    n1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfminname);
        return;
    }
    
    if ( *((FLOAT64*)(&n1)) < *((FLOAT64*)(&n2)) )
    {
        dg_pushbufferuint64(
            pBHarrayhead, 
            DG_F64STACK_BUFFERID, 
            n1);
    }
    else
    {
        dg_pushbufferuint64(
            pBHarrayhead, 
            DG_F64STACK_BUFFERID, 
            n2);
    }
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfminname);
        return;
    }
}

void dg_forthfnegate (Bufferhandle* pBHarrayhead)
{
   UINT64 x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    x = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfnegatename);
        return;
    }
    
    x = x ^ largestnegativeint; // toggle the sign bit
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        x);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfnegatename);
        return;
    }
}

void dg_forthfswap (Bufferhandle* pBHarrayhead)
{
    UINT64 n1, n2;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    n2 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfswapname);
        return;
    }
    
    n1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfswapname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_F64STACK_BUFFERID, 
        n2);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfswapname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_F64STACK_BUFFERID, 
        n1);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfswapname);
        return;
    }
}

void dg_forthfrot (Bufferhandle* pBHarrayhead)
{
    UINT64 n1, n2, n3;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    n3 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfrotname);
        return;
    }
    
    n2 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfrotname);
        return;
    }
    
    n1 = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfrotname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_F64STACK_BUFFERID, 
        n2);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfrotname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_F64STACK_BUFFERID, 
        n3);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfrotname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead, 
        DG_F64STACK_BUFFERID, 
        n1);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
       //  dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfrotname);
        return;
    }
}

void dg_forthfconstant (Bufferhandle* pBHarrayhead)
//                 ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
//                 ( r1 -f- )
{
    

    UINT64 data;

    UINT64 namelength;
    unsigned char* pname;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    data = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfconstantname);
        return;
    }

    pname = dg_parseword(
        pBHarrayhead,
        &namelength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfconstantname);
        return;
    }

    if (namelength == 0)
    {
        dg_pusherror(pBHarrayhead, dg_wordlength0error);
        dg_pusherror(pBHarrayhead, dg_forthfconstantname);
        return;
    }

    dg_createfconstantdef(
        pBHarrayhead,
        data,
        pname,
        namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfconstantname);
        return;
    }
}

void dg_unpackdf(
    FLOAT64 df,
    UINT64* pmantissa,
    INT64* pexponent,
    INT64* psign)
{
    *pmantissa = *((UINT64*)(&df));
    
    // in assembly you can take the result of the and sign extend it in one instruction
    if ( (*pmantissa & 0x8000000000000000) != 0 )
    {
        *psign = (INT64)largestunsignedint;
    }
    else
    {
        *psign = 0;
    }
    
    *pexponent = (*pmantissa >> 52) & 0x7ff;
    
    *pmantissa = *pmantissa & 0x000fffffffffffff;
}

FLOAT64 dg_packdf(
    UINT64 mantissa,
    INT64 exponent,
    INT64 sign)
{
    FLOAT64 df;
    
    // not worring about mantissas that are too big
    mantissa = mantissa & 0x000fffffffffffff;
    
    if (sign < 0)
    {
        mantissa = mantissa | 0x8000000000000000;
    }
        
    if (exponent < 0) 
    { 
        exponent = 0; 
    }
    
    exponent = exponent & 0x7ff;
    
    *((UINT64*)(&df)) = mantissa | (exponent << 52);
    
    return(df);
}

void dg_f64tof64rootf642expf6410exp(   
    FLOAT64  f64,
    FLOAT64* pf64root,
    FLOAT64* pf642exp,
    FLOAT64* pf6410exp,
    INT64*   pbase10exponent,
    INT64*   psign)
{
    INT64 base2exponent;
    
    UINT64 rmantissa;
    INT64 rexponent;
    
    dg_unpackdf(
        f64,
        &rmantissa,
        &rexponent,
        psign);
        
    if (rexponent == 0) 
    {
        *((UINT64*)(pf64root)) = rmantissa;
        *pf642exp = 0.0; // numerator
        *pf6410exp = 1.0; // denominator
        *pbase10exponent = 0x8000000000000000;
        return; // 0
    }
    
    if (rexponent == 0x7ff)
    {
        *((UINT64*)(pf64root)) = rmantissa;
        *pf642exp = 1.0; // numerator
        *pf6410exp = 0.0; // denominator
        *pbase10exponent = largestsignedint;
        return; // infinity
    }
    
    base2exponent = rexponent - 0x3FF;
    
    *pf64root = dg_packdf(
        rmantissa,
        0x3ff,
        0);
        
    *pf642exp = dg_packdf(
        0,
        rexponent,
        0);

    *pbase10exponent = dg_timeslog2(base2exponent);
    
    if (*pbase10exponent >= 0)
    {
        *pf6410exp = dg_tentothex(*pbase10exponent);
    }
    else
    {
        *pf6410exp = 1/(dg_tentothex(0 - (*pbase10exponent)));
    }
}

FLOAT64 dg_f64tobase10 (
    FLOAT64 r,
    INT64* pbase10exponent,
    INT64* psign)
{
    FLOAT64 f64root;
    FLOAT64 f642exp;
    FLOAT64 f6410exp;
     
    dg_f64tof64rootf642expf6410exp(   
        r,
        &f64root,
        &f642exp,
        &f6410exp,
        pbase10exponent,
        psign);
    
    // check for infinity, 0, denormal, and NaN
    if ((*pbase10exponent == largestsignedint) ||
        (*pbase10exponent == 0x8000000000000000))
    {
        return(f64root);
    }
        
    return(f64root * (f642exp/f6410exp));
}

// get mantissa and exponent
// shift 64 to 128 with decimal on 64 bit boundary
void dg_f64tofixedint128 (   // assumes f64 will fit into a fixed int 128]
    FLOAT64 r, 
    UINT64* presult)  // really a pointer to a UINT128                               
{
    UINT64 rmantissa;
    INT64 rexponent;
    INT64 rsign;
    
    dg_unpackdf(
        r,
        &rmantissa,
        &rexponent,
        &rsign);
        
    rmantissa = rmantissa | 0x0010000000000000; // adding in leading 1

    presult[0] = rmantissa;
    presult[1] = 0;
    
    dg_shld(presult, 12 + (rexponent - 0x3ff));
    
    return;
}

UINT64 dg_popleadingbase10fractionaldigit(UINT64* pfractionalnumber)
{
    UINT64 px[2];
    
    dg_umstar (
        *pfractionalnumber,
        10,
        px);
    *pfractionalnumber = px[0];
    return(px[1]);
}


// UINT64 dg_fixedpointu128todecimalstring(
//   unsigned char* pstring,
//   UINT64 stringlength,
//   UINT64 whole, 
//   UINT64 fractional,
//   INT64 sign);
 
UINT64 dg_fixedpointu128todecimalstring(
    unsigned char* pstring,
    UINT64 stringlength,
    UINT64 whole, 
    UINT64 fractional,
    INT64 sign)
{
    unsigned char buf[64];
    UINT64 r;
    UINT64 n=0;
    UINT64 j=0;
    UINT64 wholenumber = whole;
    UINT64 fractionalnumber = fractional;
    
    if (stringlength == 0)
    {
        return (0);
    }

    if (0 == wholenumber)
    {
        buf[19-n] = 0x30;
        n++;
    }

    while ((wholenumber) > 0)
    {
        r = wholenumber % 10;
        wholenumber = (wholenumber) / 10;
        buf[19-n] = (unsigned char)(r + 0x30);
        n++;
    }
    
    if (sign != 0)
    {
        pstring[0] = '-'; // already checked for stringlength of 0 so this should work
        j++;
    }
    
    if (n > (stringlength - j)) // already checked for stringlength of 0 so this should work
    {
        pstring[0] = '?';
        return(1);
    }

    for (r = 20 - n; r < 20; r++)
    {
        if (j < stringlength)
        {
            pstring[j] = buf[r];
            j++;
        }
    }
    
    if (fractionalnumber == 0)
    {
        return(j);
    }
    
    if (j < stringlength)
    {
        pstring[j] = '.';
        j++;
    }
    
    while ((fractionalnumber > 0) && (j < stringlength))
    {
        r = dg_popleadingbase10fractionaldigit(&fractionalnumber);
        
        pstring[j] = r + 0x30;
        j++;
    }
    
    return (j);
}


UINT64 dg_f64todecimalstring(
    FLOAT64 r,
    unsigned char* pstring,
    UINT64 stringlength)
{
    FLOAT64 rbase;
    INT64 base10exponent;
    UINT64 currentlength;
    UINT64 pfixedpointbase[2];
    INT64 sign;
    UINT64 length = stringlength ;
    const char* perror;
    
    rbase = dg_f64tobase10 (
        r,
        &base10exponent,
        &sign);
        
    if (base10exponent == largestsignedint)
    {
        if ( *((UINT64*)(&rbase)) == 0x000FFFFFFFFFFFFF)
        {
            if (8 < stringlength)
            {
                length = 8;
            }
            else
            {
                length = stringlength;
            }
            
            perror = dg_movebytes (
                (unsigned char*)"Infinity", 
                pstring,
                length);
                
            // ignoring errors....
            return(length);
        }
        else
        {
           if (3 < stringlength)
            {
                length = 3;
            }
            else
            {
                length = stringlength;
            }
            
            perror = dg_movebytes (
                (unsigned char*)"NaN", 
                pstring,
                length);
                
            // ignoring errors....
            return(length); 
        }
    }
        
    if (base10exponent == 0x8000000000000000)
    {
        if ( *((UINT64*)(&rbase)) == 0)
        {
            if (3 < stringlength)
            {
                length = 3;
            }
            else
            {
                length = stringlength;
            }
            
            perror = dg_movebytes (
                (unsigned char*)"0.0", 
                pstring,
                length);
                
            // ignoring errors....
            return(length);
        }
        else
        {
            if (8 < stringlength)
            {
                length = 8;
            }
            else
            {
                length = stringlength;
            }
            
            perror = dg_movebytes (
                (unsigned char*)"Denormal", 
                pstring,
                length);
                
            // ignoring errors....
            return(length);
        }
    }
    
    dg_f64tofixedint128 (rbase, pfixedpointbase);
    
    currentlength = dg_fixedpointu128todecimalstring(
        pstring,
        stringlength,
        pfixedpointbase[1],  // wholenumber, 
        pfixedpointbase[0],  // fractionalnumber
        sign);
        
    if (currentlength >= stringlength)
    {
        return(currentlength);
    }
    
    pstring[currentlength] = 'E';
    currentlength++;
    
    if (base10exponent < 0)
    {
        currentlength = dg_fixedpointu128todecimalstring(
            pstring,
            stringlength,
            0 - base10exponent,  // wholenumber, 
            0,                   // fractionalnumber
            (INT64)largestunsignedint);
    }
    else
    {
        currentlength = dg_fixedpointu128todecimalstring(
            pstring,
            stringlength,
            base10exponent,  // wholenumber, 
            0,               // fractionalnumber
            0);
    }
    
    return(currentlength);
}

unsigned char dg_incdecimaldigit(unsigned char x)
{
    if (x < 0x39)
    {
        return(x+1);
    }
    
    return(0x30);
}

UINT64 dg_roundupdecimalstring(
    unsigned char* pstring,
    UINT64 stringlength)
{
    UINT64 i = 0;
    unsigned char currentdigit;
    
    // going to assume the string is valid
    for (i = 0; i < stringlength; i++)
    {
        currentdigit = pstring[(stringlength - 1) - i];
        
        currentdigit = dg_incdecimaldigit(currentdigit);
        
        pstring[(stringlength - 1) - i] = currentdigit;
        
        if (currentdigit != 0x30)
        {
            return(0);
        }
    }
    
    // if we get here and current digit is 0 then we had a carry...
    if (currentdigit != 0x30)
    {
        return(0);
    }
    
    pstring[(stringlength - 1) - i] = 0x31;
    
    return(1); // need to bump exponent
}


INT64 dg_represent(
    FLOAT64 r,
    unsigned char* pstring,
    UINT64 stringlength,
    INT64* psign,
    UINT64* pfractionalremainder)  // passing this out to make testing easier
{
    FLOAT64 rbase;
    UINT64 currentlength = 0;
    UINT64 pfixedpointbase[2];
    INT64 base10exponent;
    UINT64 currentdigit;
    // UINT64 fractionalnumber;
    UINT64 i = 0;
    UINT64 roundupcarry = 0;
    UINT64 length = stringlength ;
    const char* perror;
    
    rbase = dg_f64tobase10 (
        r,
        &base10exponent,
        psign);
        
    if (stringlength == 0)
    {
        return(base10exponent);
    }
        
    if (base10exponent == largestsignedint)
    {
        if ( *((UINT64*)(&rbase)) == 0)
        {
            if (8 < stringlength)
            {
                length = 8;
            }
            else
            {
                length = stringlength;
            }
            
            perror = dg_movebytes (
                (unsigned char*)"Infinity", 
                pstring,
                length);
                
            perror = dg_fillwithbyte (
                pstring + length,
                stringlength - length,
                0x20);
                
            // ignoring errors....
            return(base10exponent);
        }
        else
        {
           if (3 < stringlength)
            {
                length = 3;
            }
            else
            {
                length = stringlength;
            }
            
            perror = dg_movebytes (
                (unsigned char*)"NaN", 
                pstring,
                length);
                
            perror = dg_fillwithbyte (
                pstring + length,
                stringlength - length,
                0x20);
                
            // ignoring errors....
            return(base10exponent); 
        }
    }
        
    if (base10exponent == 0x8000000000000000)
    {
        if ( *((UINT64*)(&rbase)) == 0)
        {
            perror = dg_fillwithbyte (
                pstring,
                stringlength,
                0x30);
                
            // ignoring errors....
            return(0);
        }
        else
        {
            if (8 < stringlength)
            {
                length = 8;
            }
            else
            {
                length = stringlength;
            }
            
            perror = dg_movebytes (
                (unsigned char*)"Denormal", 
                pstring,
                length);
                
            perror = dg_fillwithbyte (
                pstring + length,
                stringlength - length,
                0x20);
                
            // ignoring errors....
            return(base10exponent);
        }
    }
    
    while (rbase >= 1.0)
    {
        rbase = rbase/10;
        base10exponent++;
    }
    
    dg_f64tofixedint128 (rbase, pfixedpointbase);
    
    if ((pfixedpointbase[0] == 0) && (pfixedpointbase[1]))
    {
        for (i = 0; i < stringlength; i++)
        {
            pstring[i] = '0';
        }
        
        return(base10exponent);
    }
    
    *pfractionalremainder = pfixedpointbase[0];
    
    while(i < stringlength)
    {
        currentdigit = dg_popleadingbase10fractionaldigit(pfractionalremainder);
        
        pstring[i] = 0x30 + currentdigit;
        
        i++;
    }
    
    // I think forth standard is specifying round to even in the event of a tie
    //  so only need to round if its odd
    if ((*pfractionalremainder == 0x8000000000000000) &&
        ((currentdigit & 1) == 1))  
    {
        roundupcarry = dg_roundupdecimalstring(
            pstring,
            stringlength);
            
        if (roundupcarry != 0)
        {
            base10exponent++;
        }
            
        return(base10exponent);
    }
    
    if (*pfractionalremainder > 0x8000000000000000)  
    {
        roundupcarry = dg_roundupdecimalstring(
            pstring,
            stringlength);
            
        if (roundupcarry != 0)
        {
            base10exponent++;
        }
            
        return(base10exponent);
    }
    
    return(base10exponent);
}


void dg_forthfsdot(Bufferhandle* pBHarrayhead)
{
    FLOAT64 r;
    INT64 sign;
    INT64 base10exponent;
    UINT64 fractionalremainder;
    const char* perror;
    unsigned char mybuf[dg_maxprecision];
    UINT64 precision;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    precision = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_precision);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdataspacebufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfsdotname);
        return;
    }
    
    if (precision > dg_maxprecision)
    {
        precision = dg_maxprecision;
    }
    
    *((UINT64*)(&r)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfsdotname);
        return;
    }
    
    if (precision == 0)
    {
        return;
    }
    
    // going to make the number of displayed characters come from a variable
    base10exponent = dg_represent(
        r,
        mybuf,
        precision,
        &sign,
        &fractionalremainder);  
        
    if (sign != 0)
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)"-",
            1);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfsdotname);
            return;
        }
    }
        
    if ((base10exponent == largestsignedint) ||
        (base10exponent == 0x8000000000000000))
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)mybuf,
            precision);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfsdotname);
            return;
        }
        
        return;
    }
    
    base10exponent--;
        
    perror = dg_writestdout(
        pBHarrayhead,
        (unsigned char*)mybuf,
        1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfsdotname);
        return;
    }
    
    perror = dg_writestdout(
        pBHarrayhead,
        (unsigned char*)".",
        1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfsdotname);
        return;
    }
    
    perror = dg_writestdout(
        pBHarrayhead,
        mybuf + 1,
        precision - 1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfsdotname);
        return;
    }
    
    perror = dg_writestdout(
        pBHarrayhead,
        (unsigned char*)"E",
        1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfsdotname);
        return;
    }
    
    if (base10exponent < 0)
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)"-",
            1);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfsdotname);
            return;
        }
        
        dg_writestdoutuinttodec(
            pBHarrayhead, 
            0 - base10exponent);
    }
    else
    {
        dg_writestdoutuinttodec(
            pBHarrayhead, 
            base10exponent);
    }
    
    perror = dg_writestdout(
        pBHarrayhead,
        (unsigned char*)" ",
        1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfsdotname);
        return;
    }
}

void dg_forthdtof (Bufferhandle* pBHarrayhead)
{
    FLOAT64 df;
    
    UINT64 ud[2];
    INT64 rsign = 0;
    UINT64 index;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    ud[1] = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdtofname);
        return;
    }
    
    ud[0] = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdtofname);
        return;
    }
    
    if ((INT64)ud[1] < 0)
    {
        rsign -= 1;
        dg_dnegate((INT64*)ud); 
    }
    
    index = dg_hibitd(
        ud[0],
        ud[1]);
        
    if (index > 127)
    {
        df = 0.0;
    }
    else
    {
        if (index > (64 + 52))
        {
            dg_shrd((UINT64*)ud, index - (64 + 52));
        }
        
        if (index < (64 + 52))
        {
            dg_shld((UINT64*)ud, (64 + 52) - index);
        }
        
        df = dg_packdf(
            ud[1] & 0xFFFFFFFFFFFFF, // mantissa,
            index + 0x3ff, // exponent,
            rsign);
        
    }
    
    dg_pushf64tof64stack(pBHarrayhead, df);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdtofname);
        return;
    }
} 

void dg_forthstof (Bufferhandle* pBHarrayhead)
{
    FLOAT64 df;
    INT64 n;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    n = (INT64)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstofname);
        return;
    }
    
    df = (FLOAT64)n;

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&df)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthstofname);
        return;
    }
}

void dg_forthftod (Bufferhandle* pBHarrayhead)
{
    
    FLOAT64 df;
    UINT64 presult[2];
    
    UINT64 rmantissa;
    INT64 rexponent;
    INT64 rsign;
    
    INT64 shiftamount;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    df = dg_popf64fromf64stack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthftodname);
        return;
    }
    
    dg_unpackdf(
        df,
        &rmantissa,
        &rexponent,
        &rsign);
    
    if (rexponent == 0)
    {
        // subnormal and 0 case... returning 0 for both
        presult[0] = 0;
        presult[1] = 0;
    }
    else 
    {
        if (rexponent == 0x7ff)
        {   
            if (rsign != 0)
            {
                presult[0] = 0;
                presult[1] = largestnegativeint;    
            }
            else
            {  
                presult[0] = largestunsignedint;
                presult[1] = largestsignedint;
            }
        }
        else
        {
            // regular case
            rmantissa = rmantissa | 0x0010000000000000; // adding in leading 1
    
            presult[0] = rmantissa;
            presult[1] = 0;
    
            shiftamount = rexponent - (0x3ff + (64 - 12));
    
            if (shiftamount < 0)
            {
                shiftamount *= -1;
        
                if (shiftamount <= (64-12))
                {
                    dg_shrd((UINT64*)presult, shiftamount);

                    if (rsign != 0)
                    {
                        dg_dnegate((INT64*)presult);
                    }
                }
                else
                {
                    presult[0] = 0;
                    presult[1] = 0;
                }
           }
           else
           {
               if (shiftamount < (12 + 63))
               {
                   dg_shld((UINT64*)presult, shiftamount);

                   if (rsign != 0)
                   {
                       dg_dnegate((INT64*)presult);
                   }
               }
               else
               {
                   if (rsign != 0)
                   {
                       presult[0] = 0;
                       presult[1] = largestnegativeint;    
                   }
                   else
                   {  
                       presult[0] = largestunsignedint;
                       presult[1] = largestsignedint;
                   }
               }
           }
        }
    }
    
    dg_pushdatastack(pBHarrayhead, presult[0]);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthftodname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, presult[1]);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthftodname);
        return;
    }
    
    return;
    
}

void dg_forthftos (Bufferhandle* pBHarrayhead)
{
    FLOAT64 df;
    INT64 n;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    df = dg_popf64fromf64stack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthftosname);
        return;
    }
    
    n = dg_f64toi64(df);

    dg_pushdatastack(pBHarrayhead, n);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthftosname);
        return;
    }
}


void dg_forthfloor (Bufferhandle* pBHarrayhead)
{
    FLOAT64 df;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    df = dg_popf64fromf64stack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfloorname);
        return;
    }
    
    df = dg_roundf64tonegativeinfinity(df);
    
    dg_pushf64tof64stack(pBHarrayhead, df);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfloorname);
        return;
    }
}


void dg_forthfround (Bufferhandle* pBHarrayhead)
{
    FLOAT64 df;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    df = dg_popf64fromf64stack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfroundname);
        return;
    }
    
    df = dg_roundf64tonearesteven(df);
    
    dg_pushf64tof64stack(pBHarrayhead, df);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthftodname);
        return;
    }
}


void dg_forthsetprecision(Bufferhandle* pBHarrayhead)
{
    UINT64 x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    x = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsetprecisionname);
        return;
    }
    
    dg_putbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_precision,
        x);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsetprecisionname);
        return;
    }
}


void dg_forthprecision(Bufferhandle* pBHarrayhead)
{
    UINT64 x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    x = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_precision);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthprecisionname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        x);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthprecisionname);
        return;
    }
}


void dg_forthfabs (Bufferhandle* pBHarrayhead)
{
   UINT64 x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    x = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfabsname);
        return;
    }
    
    x = x & largestsignedint; // clear the sign bit
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        x);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfabsname);
        return;
    }
}


void dg_forthfcos (Bufferhandle* pBHarrayhead)
{
    UINT64 x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    x = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfcosname);
        return;
    }
    
    *((FLOAT64*)(&x)) = dg_f64cos(*((FLOAT64*)(&x))); // clear the sign bit
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        x);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfcosname);
        return;
    }
}


void dg_forthfsin (Bufferhandle* pBHarrayhead)
{
    UINT64 x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    x = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfsinname);
        return;
    }
    
    *((FLOAT64*)(&x)) = dg_f64sin(*((FLOAT64*)(&x))); // clear the sign bit
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        x);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfsinname);
        return;
    }
}


void dg_forthftan (Bufferhandle* pBHarrayhead)
{
    UINT64 x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    x = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthftanname);
        return;
    }
    
    *((FLOAT64*)(&x)) = dg_f64tan(*((FLOAT64*)(&x))); // clear the sign bit
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        x);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthftanname);
        return;
    }
}


void dg_forthfsincos (Bufferhandle* pBHarrayhead)
{
    FLOAT64 r, cosresult, sinresult;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    *((UINT64*)(&r)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfsincosname);
        return;
    }
    
    cosresult = dg_f64sincos(r, &sinresult); 
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&sinresult)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfsincosname);
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&cosresult)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfsincosname);
        return;
    }
}

void dg_forthfln (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x,y,r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    y = 1.0/dg_f64fyl2x(2.718281828459,1.0); // move this to a constant later
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthflnname);
        return;
    }
    
    r = dg_f64fyl2x(x,y); 
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthflnname);
        return;
    }
}

void dg_forthflnp1 (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x,y,r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    y = 1.0/dg_f64fyl2x(2.718281828459, 1.0); // move this to a constant later
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthflnp1name);
        return;
    }
    
    r = dg_f64fyl2x(x + 1.0, y); 
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthflnp1name);
        return;
    }
}

void dg_forthflog (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x,y,r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    y = 1.0/dg_f64fyl2x(10.0,1.0);  // move this to a constant later
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthflogname);
        return;
    }
    
    r = dg_f64fyl2x(x,y); 
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthflogname);
        return;
    }
}

FLOAT64 dg_f64twotothex(FLOAT64 x)
{
    // get the sign.... what do we do with the sign?
    FLOAT64 whole;
    FLOAT64 fractional;
    FLOAT64 result = 0.0;
    INT64 nwhole;
    
    whole = dg_truncatef64(x);
    fractional = dg_f64getfractional(x);
    
    // check for infinity, 0.0, denormal, and NaN
    
    // turn the whole number into an integer
    nwhole = dg_f64toi64(whole);
    
    //  if it's in range, make it the exponent of a floating point number
    if (nwhole > 0x3ff)
    {
        *((UINT64*)(&result)) = dg_f64infinity;
        return(result);
    }
    
    if (nwhole < -0x3fe)
    {
        *((UINT64*)(&result)) = dg_f64denormal;
        return(result);
    }
    
    result = dg_packdf(
        0, // mantissa,
        nwhole + 0x3ff, // exponent,
        0);
   
    result = result * (dg_f64f2xm1(fractional) + 1.0);
    
    return (result);
}

void dg_forthfexp (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x,y,r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    y = dg_f64logbase2ofe();  // move this to a constant later
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfexpname);
        return;
    }
    
    y = x * y;
    
    r = dg_f64twotothex(y);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfexpname);
        return;
    }
}

void dg_forthfexpm1 (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x,y,r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    y = dg_f64logbase2ofe();  // move this to a constant later
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfexpm1name);
        return;
    }
    
    y = x * y;
    
    r = dg_f64twotothex(y);
    
    r = r - 1.0;
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfexpm1name);
        return;
    }
}

void dg_forthfalog (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x,y,r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    y = dg_f64logbase2of10();  // move this to a constant later
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfalogname);
        return;
    }
    
    y = x * y;
    
    r = dg_f64twotothex(y);
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfalogname);
        return;
    }
}

void dg_forthfstarstar (Bufferhandle* pBHarrayhead)
{
    FLOAT64 base,exponent,x,r, halfexponent;
    // UINT64 pfixedpointbase[2];
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    *((UINT64*)(&exponent)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfstarstarname);
        return;
    }
    
    *((UINT64*)(&base)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfstarstarname);
        return;
    }
    
    if (base < 0)
    {
        // we can only do it if the exponent does not have a fractional part
        //  because the denominator of a fractional part of the exponent is even
        //  (floating point number exponent is divided by power of two... so denominator is even)
        // so...
        //  exponent is integer and even result is even
        //  exponent is integer and odd result is odd
        //  exponent is not integer result is NaN
        if ( ( (exponent - dg_truncatef64(exponent)) !=  0.0 ) ||
             ( (exponent - dg_truncatef64(exponent)) != -0.0 ) )
        {
            r = dg_f64NaN; // exponent is not integer
        }
        else
        {
            halfexponent = exponent / 2.0;
            
            x = dg_f64fyl2x(0.0 - base, exponent);
            
            if ( ((halfexponent - dg_truncatef64(halfexponent)) != 0.0) ||
                 ((halfexponent - dg_truncatef64(halfexponent)) != -0.0) )
            {
                // odd integer exponent
                r = 0.0 - dg_f64twotothex(x);
            }
            else
            {
                // even integer exponent
                r = dg_f64twotothex(x);
            }
        }
    }
    else
    {
        x = dg_f64fyl2x(base, exponent);
        r = dg_f64twotothex(x);
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfstarstarname);
        return;
    }
}

void dg_forthfatan2 (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x,y,r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfatan2name);
        return;
    }
    
    *((UINT64*)(&y)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfatan2name);
        return;
    }
    
    r = dg_f64fpatan(x,y);  
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfatan2name);
        return;
    }
}

void dg_forthfatan (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x = 1.0;
    FLOAT64 y, r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    *((UINT64*)(&y)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfatanname);
        return;
    }
    
    r = dg_f64fpatan(x,y);  
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfatanname);
        return;
    }
}

void dg_forthfasin (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x = 0.0;
    FLOAT64 y, r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    *((UINT64*)(&y)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfasinname);
        return;
    }
    
    if ((y > 1.0) || (y < -1.0))
    {
        r = dg_f64NaN;
    }
    else
    {
        x = dg_f64sqrt(1.0 - (y*y));
    
        r = dg_f64fpatan(x,y);
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfasinname);
        return;
    }
}

void dg_forthfacos (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x;
    FLOAT64 y, r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfacosname);
        return;
    }
    
    if ((x > 1.0) || (x < -1.0))
    {
        r = dg_f64NaN;
    }
    else
    {
        y = dg_f64sqrt(1.0 - (x*x));
    
        r = dg_f64fpatan(x,y);  
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfacosname);
        return;
    }
}

void dg_forthfsinh (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x;
    FLOAT64 y, r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfsinhname);
        return;
    }
    
    y = dg_f64logbase2ofe();  // move this to a constant later
    
    y = x * y;
    
    x = dg_f64twotothex(y); // x = (e^a); 
    
    y = x - 1.0; // y = (e^a) - 1 
    
    r = y/x; // r = ((e^a) - 1)/(e^a)
    
    r = (r + y)/2.0; 
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfsinhname);
        return;
    }
}

void dg_forthfcosh (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x;
    FLOAT64 y, r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfcoshname);
        return;
    }
    
    y = dg_f64logbase2ofe();  // move this to a constant later
    
    y = x * y;
    
    x = dg_f64twotothex(y); // x = (e^a); 
    
    y = x - 1.0; // y = (e^a) - 1 
    
    r = (x + 1.0)/x; // r = ((e^a) + 1)/(e^a)
    
    r = (r + y)/2.0; 
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfcoshname);
        return;
    }
}

void dg_forthftanh (Bufferhandle* pBHarrayhead)
{
    FLOAT64 fsinh, fcosh;
    FLOAT64 x;
    FLOAT64 y, r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthftanhname);
        return;
    }
    
    y = dg_f64logbase2ofe();  // move this to a constant later
    
    y = x * y;
    
    x = dg_f64twotothex(y); // x = (e^a); 
    
    y = x - 1.0; // y = (e^a) - 1 
    
    r = (x + 1.0)/x; // r = ((e^a) + 1)/(e^a)
    
    fcosh = (r + y)/2.0; 
    
    r = y/x; // r = ((e^a) - 1)/(e^a)
    
    fsinh = (r + y)/2.0; 
    
    r = fsinh/fcosh;
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthftanhname);
        return;
    }
}

void dg_forthfasinh (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x;
    FLOAT64 y, r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfasinhname);
        return;
    }
    
    y = (x * x) + 1;
    
    x = x + dg_f64sqrt(y);
    
    y = 1.0/dg_f64fyl2x(2.718281828459,1.0); // move this to a constant later
    
    r = dg_f64fyl2x(x,y); 
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfasinhname);
        return;
    }
}

void dg_forthfacosh (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x;
    FLOAT64 y, r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfacoshname);
        return;
    }
    
    if (x < 1.0)
    {
        r = dg_f64NaN;
    }
    else
    {
        y = (x * x) - 1;
        
        x = x + dg_f64sqrt(y);
        
        y = 1.0/dg_f64fyl2x(2.718281828459,1.0); // move this to a constant later
        
        r = dg_f64fyl2x(x,y); 
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfacoshname);
        return;
    }
}

void dg_forthfatanh (Bufferhandle* pBHarrayhead)
{
    FLOAT64 x;
    FLOAT64 y, r;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    *((UINT64*)(&x)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfatanhname);
        return;
    }
    
    if (x >= 1.0)
    {
        r = dg_f64NaN;
    }
    else
    {
        x = (1.0 + x)/(1.0 - x);
        
        y = 1.0/dg_f64fyl2x(2.718281828459,1.0); // move this to a constant later
        
        r = dg_f64fyl2x(x,y)/2.0; 
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        *((UINT64*)(&r)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfatanhname);
        return;
    }
}

void dg_forthfedot(Bufferhandle* pBHarrayhead)
{
    FLOAT64 r;
    INT64 sign;
    INT64 base10exponent;
    UINT64 fractionalremainder;
    const char* perror;
    unsigned char mybuf[dg_maxprecision];
    UINT64 precision;
    UINT64 base10exponentbumps = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    precision = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_precision);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdataspacebufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfedotname);
        return;
    }
    
    if (precision > dg_maxprecision)
    {
        precision = dg_maxprecision;
    }
    
    *((UINT64*)(&r)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfedotname);
        return;
    }
    
    // could make it so it just shows the exponent.... and the sign...
    if (precision == 0)
    {
        return;
    }
    
    // going to make the number of displayed characters come from a variable
    base10exponent = dg_represent(
        r,
        mybuf,
        precision,
        &sign,
        &fractionalremainder); 
        
    if (sign != 0)
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)"-",
            1);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfedotname);
            return;
        }
    }
        
    if ((base10exponent == largestsignedint) ||
        (base10exponent == 0x8000000000000000))
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)mybuf,
            precision);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfedotname);
            return;
        }
        
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)" ",
            1);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfedotname);
            return;
        }
        
        return;
    }
    
    // need dec base exponent 1 to 3 times... until it's a multiple of 3
    
    base10exponent--;
    base10exponentbumps++;
    
    while ((base10exponent % 3) != 0)
    {
        base10exponent--;
        base10exponentbumps++;
    }
    
    if (precision >= base10exponentbumps)
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)mybuf,
            base10exponentbumps);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfedotname);
            return;
        }
    }
    else
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)mybuf,
            precision);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfedotname);
            return;
        }
            
        perror = dg_writestdout( // this will give one extra character over the precision....
            pBHarrayhead,
            (unsigned char*)"?",
            1);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfedotname);
            return;
        }
    }
        
    perror = dg_writestdout(
        pBHarrayhead,
        (unsigned char*)".",
        1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfedotname);
        return;
    }
    
    if (precision >= base10exponentbumps)
    {
        perror = dg_writestdout(
            pBHarrayhead,
            mybuf + base10exponentbumps,
            precision - base10exponentbumps);
        
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfedotname);
            return;
        }
    }
    
    perror = dg_writestdout(
        pBHarrayhead,
        (unsigned char*)"E",
        1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfedotname);
        return;
    }
    
    if (base10exponent < 0)
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)"-",
            1);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfedotname);
            return;
        }
        
        dg_writestdoutuinttodec(
            pBHarrayhead, 
            0 - base10exponent);
    }
    else
    {
        dg_writestdoutuinttodec(
            pBHarrayhead, 
            base10exponent);
    }
    
    perror = dg_writestdout(
        pBHarrayhead,
        (unsigned char*)" ",
        1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfedotname);
        return;
    }
}

void dg_forthfdot(Bufferhandle* pBHarrayhead)
{
    FLOAT64 r;
    INT64 sign;
    INT64 base10exponent;
    UINT64 fractionalremainder;
    const char* perror;
    unsigned char mybuf[dg_maxprecision];
    UINT64 precision;
    UINT64 i = 0;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    precision = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        dg_precision);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthdataspacebufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfdotname);
        return;
    }
    
    if (precision > dg_maxprecision)
    {
        precision = dg_maxprecision;
    }
    
    *((UINT64*)(&r)) = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfdotname);
        return;
    }
    
    // could make it so it just shows the exponent.... and the sign...
    if (precision == 0)
    {
        return;
    }
    
    // going to make the number of displayed characters come from a variable
    base10exponent = dg_represent(
        r,
        mybuf,
        precision,
        &sign,
        &fractionalremainder); 
        
    if (sign != 0)
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)"-",
            1);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfdotname);
            return;
        }
    }
        
    if ((base10exponent == largestsignedint) ||
        (base10exponent == 0x8000000000000000))
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)mybuf,
            precision);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfdotname);
            return;
        }
        
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)" ",
            1);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfsdotname);
            return;
        }
        
        return;
    }
    
    if ((base10exponent > 0) &&
        (base10exponent <= precision))
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)mybuf,
            base10exponent);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfdotname);
            return;
        }
        
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)".",
            1);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfdotname);
            return;
        }
        
        perror = dg_writestdout(
            pBHarrayhead,
            mybuf + base10exponent,
            precision - base10exponent);
        
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfdotname);
            return;
        }
        
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)"E0 ",
            2);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfdotname);
            return;
        }
        
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)" ",
            1);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfsdotname);
            return;
        }
        
        return;
    }
    
    if ((base10exponent <= 0) &&
        (base10exponent >= -(INT64)precision)) // probably should be +3 or something to see at least 3 digits...
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)"0.",
            2);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfdotname);
            return;
        }
        
        // need 1 zero for each
        for (i = 0; i < -base10exponent; i++)
        {
            perror = dg_writestdout(
                pBHarrayhead,
                (unsigned char*)"0",
                1);
                
            if (perror != dg_success)
            {
                dg_pusherror(pBHarrayhead, perror);
                dg_pusherror(pBHarrayhead, dg_writestdoutname);
                dg_pusherror(pBHarrayhead, dg_forthfdotname);
                return;
            }
        }
        
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)mybuf,
            precision + base10exponent);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfdotname);
            return;
        }
        
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)"E0 ",
            2);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfdotname);
            return;
        }
        
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)" ",
            1);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfsdotname);
            return;
        }
        
        return;
    }
    
    base10exponent--;
    
    perror = dg_writestdout(
        pBHarrayhead,
        (unsigned char*)mybuf,
        1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfsdotname);
        return;
    }
    
    perror = dg_writestdout(
        pBHarrayhead,
        (unsigned char*)".",
        1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfsdotname);
        return;
    }
    
    perror = dg_writestdout(
        pBHarrayhead,
        mybuf + 1,
        precision - 1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfsdotname);
        return;
    }
    
    perror = dg_writestdout(
        pBHarrayhead,
        (unsigned char*)"E",
        1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfsdotname);
        return;
    }
    
    if (base10exponent < 0)
    {
        perror = dg_writestdout(
            pBHarrayhead,
            (unsigned char*)"-",
            1);
            
        if (perror != dg_success)
        {
            dg_pusherror(pBHarrayhead, perror);
            dg_pusherror(pBHarrayhead, dg_writestdoutname);
            dg_pusherror(pBHarrayhead, dg_forthfsdotname);
            return;
        }
        
        dg_writestdoutuinttodec(
            pBHarrayhead, 
            0 - base10exponent);
    }
    else
    {
        dg_writestdoutuinttodec(
            pBHarrayhead, 
            base10exponent);
    }
    
    perror = dg_writestdout(
        pBHarrayhead,
        (unsigned char*)" ",
        1);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_writestdoutname);
        dg_pusherror(pBHarrayhead, dg_forthfsdotname);
        return;
    }
}

void dg_forthfproximate(Bufferhandle* pBHarrayhead)
{
    UINT64 flag = FORTH_FALSE;
    FLOAT64 r1, r2, r3, rt, rv;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    r3 = dg_popf64fromf64stack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfproximatename);
        return;
    }
    
    r2 = dg_popf64fromf64stack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfproximatename);
        return;
    }
    
    r1 = dg_popf64fromf64stack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfproximatename);
        return;
    }
    
    if (r3 == 0.0)
    {
        if ( *((UINT64*)(&r2)) == *((UINT64*)(&r1)) )
        {
            flag = FORTH_TRUE;
        }
        
        dg_pushdatastack(
            pBHarrayhead,
            flag);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthfproximatename);
            return;
        }
        
        return;
    }
    
    if (r3 > 0.0)
    {
        rt = r1 - r2;
        
        *((UINT64*)(&rt)) = *((UINT64*)(&rt)) & largestsignedint;
        
        if (rt < r3)
        {
            flag = FORTH_TRUE;
        }
        
        dg_pushdatastack(
            pBHarrayhead,
            flag);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_forthfproximatename);
            return;
        }
        
        return;
    }
    
    rt = r1 - r2;
    
    *((UINT64*)(&rt)) = *((UINT64*)(&rt)) & largestsignedint;
    
    
    *((UINT64*)(&r1)) = *((UINT64*)(&r1)) & largestsignedint;
    
    *((UINT64*)(&r2)) = *((UINT64*)(&r2)) & largestsignedint;
    
    rv = r3 * (r1 + r2);
    
    *((UINT64*)(&rv)) = *((UINT64*)(&rv)) & largestsignedint;
    
    if (rt < rv)
    {
        flag = FORTH_TRUE;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        flag);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfproximatename);
        return;
    }
    
    return;
}

void dg_forthsfstore (Bufferhandle* pBHarrayhead)
{
    FLOAT64 r64;
    FLOAT32 r32;
    UINT32* paddress;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    r64 = dg_popf64fromf64stack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsfstorename);
        return;
    }
    
    paddress = (UINT32*)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsfstorename);
        return;
    }
    
    r32 = dg_f64tof32(r64);
    
    perror = dg_putuint32(paddress, *((UINT32*)(&r32)));
    
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_putuint32name);
        dg_pusherror(pBHarrayhead, dg_forthsfstorename);
        return;
    }
}

void dg_forthsffetch (Bufferhandle* pBHarrayhead)
{
    FLOAT64 r64;
    FLOAT32 r32;
    UINT32* paddress;
    const char* perror;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    paddress = (UINT32*)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsffetchname);
        return;
    }
    
    perror = dg_getuint32(paddress, (UINT32*)&r32);
    
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_getuint32name);
        dg_pusherror(pBHarrayhead, dg_forthsffetchname);
        return;
    }
    
    r64 = dg_f32tof64(r32);
    
    dg_pushf64tof64stack(pBHarrayhead, r64);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsffetchname);
        return;
    }
}

void dg_forthsfalign (Bufferhandle* pBHarrayhead)
//              ( -- )
{
    unsigned char* pdataspacebuf = NULL;
    UINT64* pdataspacelength = NULL;

    UINT64 remainder = 0;
    UINT64 amounttogrow = 0;

    UINT64 cdsbufid = 0;

    const char* pError = NULL;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    cdsbufid = dg_getbufferuint64(
        pBHarrayhead,
        DG_DATASPACE_BUFFERID,
        currentvariablebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthsfalignname);
        return;
    }

    pdataspacebuf = dg_getpbuffer(
        pBHarrayhead,
        cdsbufid,
        &pdataspacelength);

    if (pdataspacebuf == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthsfalignname);
        return;
    }

    remainder = *pdataspacelength % sizeof(FLOAT32);
    
     // amounttogrow will be 4 when remainder is 0, but we will catch this below
    amounttogrow = sizeof(FLOAT32) - remainder;

    if (remainder != 0)
    {
        dg_growbuffer(
            pBHarrayhead,
            cdsbufid,
            amounttogrow,
            &pError,
            false);

        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_growbuffername);
            dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
            dg_pusherror(pBHarrayhead, dg_forthsfalignname);
        }
    }
}

void dg_forthsfaligned (Bufferhandle* pBHarrayhead)
//                ( addr -- a-addr )
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;

    UINT64 addr = 0;

    UINT64 remainder = 0;
    UINT64 amounttogrow = 0;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsfalignedname);
        return;
    }

    if ((*pdatastacklength) < (sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthsfalignedname);
        return;
    }

    addr = *((UINT64*)(pdatastack + *pdatastacklength - (sizeof(UINT64))));

    remainder = addr % sizeof(FLOAT32);
    
     // amounttogrow will be 4 when remainder is 0, but we will catch this below
    amounttogrow = sizeof(FLOAT32) - remainder;

    if (remainder != 0)
    {
        addr += amounttogrow;
        *((UINT64*)(pdatastack + *pdatastacklength - (sizeof(UINT64)))) = addr;
    }
}

void dg_forthsfloatplus (Bufferhandle* pBHarrayhead)
//                ( addr -- addr+4 )
{
    unsigned char* pdatastack = NULL;
    UINT64* pdatastacklength = NULL;

    UINT64 addr = 0;

    pdatastack = dg_getpbuffer(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        &pdatastacklength);

    if (pdatastack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthsfloatplusname);
        return;
    }

    if ((*pdatastacklength) < (sizeof(UINT64)))
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthsfloatplusname);
        return;
    }

    addr = *((UINT64*)(pdatastack + *pdatastacklength - (sizeof(UINT64))));
    
    *((UINT64*)(pdatastack + *pdatastacklength - (sizeof(UINT64)))) = addr + sizeof(FLOAT32);
}

void dg_forthsfloats (Bufferhandle* pBHarrayhead)
{
    INT64 n;
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    n = (INT64)dg_popdatastack(pBHarrayhead);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthsfloatsname);
        return;
    }
    
    if (n > 0) // not sure why this is needed... but if it isn't there it doesn't work on MacOSX
    {
        if ( n > ((INT64)largestsignedint)/sizeof(FLOAT32) )
        {
            dg_pusherror(pBHarrayhead, dg_signedvaluetoobigerror);
            dg_pusherror(pBHarrayhead, dg_forthsfloatsname);
            return;
        }
    }
    else
    {
        if (n < ((INT64)largestnegativeint)/(INT64)sizeof(FLOAT32) )
        {
            dg_pusherror(pBHarrayhead, dg_signedvaluetoobigerror);
            dg_pusherror(pBHarrayhead, dg_forthfloatsname);
            return;
        }
    }
    
    dg_pushdatastack(
        pBHarrayhead, 
        (UINT64)(n * sizeof(FLOAT32)));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfloatsname);
        return;
    }
}

void dg_forthfover (Bufferhandle* pBHarrayhead)          
//     ( df1 df0 -f64- df1 df0 df1 )
{
    UINT64* pbuflength;
    unsigned char* pf64stack;

    UINT64* pints;
    UINT64 n1;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pf64stack = dg_getpbuffer(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfovername);
        return;
    }

    if (*pbuflength < (2 * sizeof(UINT64)) )
    {
        // dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthfovername);
        return;
    }

    // could check for misaligned data stack here
    pints = (UINT64*)(pf64stack + *pbuflength - (2 * sizeof(UINT64)));

    n1 = pints[0];


    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        n1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthfovername);
    }
}

void dg_forthrepresent (Bufferhandle* pBHarrayhead)          
//     ( df0 -f64-  )
//     ( addr length -- base10exponent flag1 flag2 )
{
    unsigned char* pstring;
    UINT64 stringlength;
    FLOAT64 r;
    INT64 sign;
    UINT64 fractionalremainder;
    UINT64 base10exponent;
    UINT64 flag2 = FORTH_TRUE;
    const char* perror;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    stringlength = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrepresentname);
        return;
    }
    
    pstring = (unsigned char*)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrepresentname);
        return;
    }
    
    r = dg_popf64fromf64stack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrepresentname);
        return;
    }
    
    // checking memory at pstring
    perror = dg_fillwithbyte(
        pstring,
        stringlength,
        0x20);
        
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_fillwithbytename);
        dg_pusherror(pBHarrayhead, dg_forthrepresentname);
        return;
    }

    base10exponent = dg_represent(
        r,
        pstring,
        stringlength,
        &sign,
        &fractionalremainder);
        
    dg_pushdatastack(
        pBHarrayhead,
        base10exponent);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrepresentname);
        return;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        (UINT64)sign);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrepresentname);
        return;
    }
    
    if ((base10exponent == largestsignedint) ||
        (base10exponent == largestnegativeint))
    {
        flag2 = FORTH_FALSE;
    }
    
    dg_pushdatastack(
        pBHarrayhead,
        flag2);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrepresentname);
        return;
    }
}

void dg_forthfsqrt (Bufferhandle* pBHarrayhead)
{
    UINT64 x;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    x = dg_popbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfsqrtname);
        return;
    }
    
    *((FLOAT64*)(&x)) = dg_f64sqrt(*((FLOAT64*)(&x))); // clear the sign bit
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_F64STACK_BUFFERID,
        x);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthfsqrtname);
        return;
    }
}

void dg_forthf64comma (Bufferhandle* pBHarrayhead)
//         ( f1 -f64- )
//         ( -currentdataspacebuffer- f1 )
{
    UINT64* pbuflength = NULL;
    unsigned char* pf64stack = NULL;

    UINT64* pints = NULL;

    UINT64 n1 = 0;
    UINT64 f64bufid = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    pf64stack = dg_getpbuffer(
        pBHarrayhead, 
        DG_F64STACK_BUFFERID, 
        &pbuflength);

    if (pf64stack == (unsigned char*)badbufferhandle)
    {
        dg_pusherror(pBHarrayhead, dg_forthf64stackbufferidname);
        dg_pusherror(pBHarrayhead, dg_forthf64commaname);
        return;
    }

    if (*pbuflength < (1 * sizeof(UINT64)) )
    {
        dg_pusherror(pBHarrayhead, dg_datastackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthf64commaname);
        return;
    }

    // could check for misaligned data stack here

    pints = (UINT64*)(pf64stack + *pbuflength - sizeof(UINT64));

    n1 = pints[0];

    f64bufid = dg_getbufferuint64(
        pBHarrayhead, 
        DG_DATASPACE_BUFFERID, 
        currentvariablebuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthpcurrentnewvariablebuffername);
        dg_pusherror(pBHarrayhead, dg_forthf64commaname);
        return;
    }

    dg_pushbufferuint64(
        pBHarrayhead,
        f64bufid, 
        n1);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // error pushing to current new variable buffer
        dg_pusherror(pBHarrayhead, dg_forthf64commaname);
        return;
    }

    *pbuflength = *pbuflength - sizeof(UINT64);
}

// go through legacy floating point words and make sure the ones that
//  can use the f64 stack do use the f64 stack

// make words to move stuff data stack <-> f64 stack.. >F64STACK F64STACK> ?



