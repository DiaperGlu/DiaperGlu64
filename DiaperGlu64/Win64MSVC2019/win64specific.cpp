// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.4.
//
//    DiaperGlu v5.4 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.4 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.4; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// June 5, 2022               //
// version 5.4                //
// /////////////////////////////

  
#include "../diapergluforth.h"

const char dg_pushhctwotobuffername[] = "dg_pushhctwotobuffer";

void dg_pushhctwotobuffer(
	Bufferhandle* pBHarrayhead,
	UINT64 bufferid,
	UINT64* pud) // really UINT128*
{
	UINT64 hclength;
	unsigned char* pbuffer;
	UINT64 oldbufferlength;
	UINT64* pnewbufferlength;
	const char* perror;
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	if (DG_ERRORSTACK_BUFFERID == bufferid)
	{
		dg_pusherror(pBHarrayhead, dg_bufferidisforerrorstack);
		dg_pusherror(pBHarrayhead, dg_pushhctwotobuffername);
		return;
	}

	hclength = dg_gethctwolength(pud);

	oldbufferlength = dg_growbuffer(
		pBHarrayhead,
		bufferid,
		hclength,  // in bytes
		&perror,
		FORTH_FALSE);

	if (perror != dg_success)
	{
		dg_pusherror(pBHarrayhead, perror);
		dg_pusherror(pBHarrayhead, dg_growbuffername);
		dg_pusherror(pBHarrayhead, dg_pushhctwotobuffername);
		return;
	}

	pbuffer = dg_getpbuffer(
		pBHarrayhead,
		bufferid,
		&pnewbufferlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pushhctwotobuffername);
		return;
	}

	perror = dg_hctwostore(pbuffer + oldbufferlength, pud);

	if (perror != dg_success)
	{
		dg_pusherror(pBHarrayhead, perror);
		dg_pusherror(pBHarrayhead, dg_hctwostorename);
		dg_pusherror(pBHarrayhead, dg_pushhctwotobuffername);
		return;
	}
}


void dg_forthfindlibrarysymbol (Bufferhandle* pBHarrayhead)
//    ( libraryhandle -- symboladdress|NULL )
//    ( symbolname$ -$- )
{
    UINT64 libraryhandle;
    
    UINT64 numberofstringsonstack = 0;
	unsigned char* pnametofind = NULL;
	UINT64 nametofindlength = 0;
	const char* flag;
    INT64 compareflag;
    
    UINT64 numberofnames;

	UINT64 j = 0;
	UINT64 namestart = 0;
	UINT64 nameend = 0;

	UINT64 namelength = 0;

	FARPROC procaddress = NULL;

	LPCSTR pname = NULL;

	const char* symboltype;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    libraryhandle = dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
		return;
	}

    numberofstringsonstack = dg_getnumberoflstringsonstack(pBHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
		return;
	}

	if (numberofstringsonstack < 1)
	{
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
		return;
	}

	dg_forthturnstringinto0string(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
		return;
	}

	pnametofind = dg_getplstring(pBHarrayhead, 
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		numberofstringsonstack - 1,
		&nametofindlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
		return;
	}

	__try
	{
		procaddress = GetProcAddress(
			(HMODULE)libraryhandle,
			(LPCSTR)pnametofind);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		procaddress = NULL;
	}

	dg_pushdatastack(pBHarrayhead, (UINT64)procaddress);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
		return;
	}

	dg_forthdropstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
		return;
	}
}


void dg_forthcallprocaddress (Bufferhandle* pBHarrayhead)
//                     ( paramn paramn-1 paramn-2 ... param1 n procaddress -- returnvalue )
{
	UINT64* address;
	UINT64 n;

	UINT64* plength;
	unsigned char* pbuffer;

	UINT64* pints;

	UINT64 returnvalue;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	pbuffer = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &plength);

	if (pbuffer == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
		return;
	}

	if (*plength < 2 * sizeof (UINT64))
	{
		dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
		return;
	}

	n = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
	address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

	if (((*plength) / sizeof(UINT64)) < n+2 ) // pretty sure overflow indexing is caught by this
	{
		dg_pusherror(pBHarrayhead, dg_procparamsmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
		return;
	}

	pints = (UINT64*)(pbuffer + *plength - (n+2)*sizeof(UINT64));

	__try  
	{
		// I put this code in a subroutine because VC6.0 doesn't like jumps inside a try block
        //***align16*** in case this function is used to call 64bit dll
		returnvalue = dg_callprocaddress(pints, n, plength, address);

	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		dg_pusherror(pBHarrayhead, dg_osexception);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
	}

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		return;
	}

	// moving drop data stack to out here so we can see the stack frame when there is an error
	//*plength -= (n+2) * sizeof(UINT32);

	dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, returnvalue);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
		return;
	}
}



// for linux/freebsd/macosx compatibility
void dg_forthcallprocaddressretuint128 (Bufferhandle* pBHarrayhead)
//                     ( paramn paramn-1 paramn-2 ... param1 n procaddress -- returnvaluelo returnvaluehi )
{
	UINT64* address;
	UINT64 n;

	UINT64* plength;
	unsigned char* pbuffer;

	UINT64* pints;

	UINT64 returnvalue, hireturnvalue;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	pbuffer = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &plength);

	if (pbuffer == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
		return;
	}

	if (*plength < 2 * sizeof (UINT64))
	{
		dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
		return;
	}

	n = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
	address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

	if (((*plength) / sizeof(UINT64)) < (n+2) ) // pretty sure overflow indexing is caught by this
	{
		dg_pusherror(pBHarrayhead, dg_procparamsmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
		return;
	}

	pints = (UINT64*)(pbuffer + *plength - (n+2)*sizeof(UINT64));

    __try  
	{
		// I put this code in a subroutine because VC6.0 doesn't like jumps inside a try block
        //***align16*** in case this function is used to call 64bit dll
		returnvalue = dg_callprocaddressretuint128(pints, n, plength, address, &hireturnvalue);
	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		dg_pusherror(pBHarrayhead, dg_osexception);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
	}

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		return;
	}

	// moving drop data stack to out here so we can see the stack frame when there is an error
	//*plength -= (n+2) * sizeof(UINT32);

	dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, returnvalue);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
		return;
	}

    dg_pushbufferuint64(pBHarrayhead, DG_DATASTACK_BUFFERID, hireturnvalue);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
		return;
	}
}

void dg_forthcalldfpprocaddress(Bufferhandle* pBHarrayhead)
//     ( dfparamn dfparamn-1 ... dfparam1
//       paramn paramn-1 paramn-2 ... param1
//       nfloats n procaddress -- uint64returnvalue dfpreturnvalue )
{
	UINT64* address;
	UINT64 n, nfloats;

	UINT64* plength;
	unsigned char* pbuffer;

	UINT64* pints;

	FLOAT64 result;
	FLOAT64* presult = &result;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	pbuffer = dg_getpbuffer(
		pBHarrayhead,
		DG_DATASTACK_BUFFERID,
		&plength);

	if (pbuffer == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcalldfpprocname);
		return;
	}

	if (*plength < (3 * sizeof(UINT64)))
	{
		dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcalldfpprocname);
		return;
	}

	nfloats = *((UINT64*)(pbuffer + *plength - (3 * sizeof(UINT64))));
	n = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
	address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

	if (((*plength) / sizeof(UINT64)) < (n + nfloats + 3)) // pretty sure overflow indexing is caught by this
	{
		dg_pusherror(pBHarrayhead, dg_dfpprocparamsmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcalldfpprocname);
		return;
	}

	pints = (UINT64*)(pbuffer + *plength - ((n + nfloats + 3) * sizeof(UINT64)));

	result = dg_calldfpprocaddress(
		pints,
		n,
		plength,
		address,
		nfloats);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		return;
	}

	dg_pushdatastack(
		pBHarrayhead,
		*((UINT64*)presult));

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthcalldfpprocname);
	}
}

/*
void dg_forthcallcppmemberfunction (Bufferhandle* pBHarrayhead)
//     ( paramn paramn-1 paramn-2 ... param1 n procaddress -- returnvalue )
//     ( param1 is the object handle )
{
	UINT32* address;
	UINT32 n;

	UINT32* plength;
	unsigned char* pbuffer;

	UINT32* pints;

	UINT32 returnvalue;

	UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);

	pbuffer = dg_getpbuffer(pBHarrayhead, DG_DATASTACK_BUFFERID, &plength);

	if (pbuffer == (unsigned char*)badbufferhandle)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
		return;
	}

	if (*plength < 2 * sizeof (UINT32))
	{
		dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
		return;
	}

	n = *((UINT32*)(pbuffer + *plength - (2 * sizeof(UINT32))));
	address = *((UINT32**)(pbuffer + *plength - (sizeof(UINT32))));

	if (((*plength) / sizeof(UINT32)) < n+2 ) // pretty sure overflow indexing is caught by this
	{
		dg_pusherror(pBHarrayhead, dg_procparamsmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
		return;
	}

	if (0 == n) // checking missing object handle case
	{
		dg_pusherror(pBHarrayhead, dg_missingobjecthandleerror);
		dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
		return;
	}

	pints = (UINT32*)(pbuffer + *plength - (n+2)*sizeof(UINT32));

	__try  
	{
        //***align16*** in case this function is used to call 64bit dll
		returnvalue = dg_callcppmemberwin32(pints, n, plength, address);

	}
	__except(EXCEPTION_EXECUTE_HANDLER)
	{
		dg_pusherror(pBHarrayhead, dg_osexception);
		dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
	}

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		return;
	}

	dg_pushbufferdword(pBHarrayhead, DG_DATASTACK_BUFFERID, returnvalue);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
		return;
	}
}
*/

void dg_forthfixpathstring(Bufferhandle* pBHarrayhead)
//     ( filename$ -$- filename$' )
{
	UINT64 stringstackdepth;

	unsigned char* scriptpath;
	UINT64* pscriptpathlength;

	const char* result;
	unsigned char c = ' ';

	unsigned char* pnamelstring;
	UINT64 namelength;

	UINT64 scanlength;
	UINT64 i = 0;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	stringstackdepth = dg_getnumberoflstringsonstack(
		pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfixpathstringname);
		return;
	}

	if (stringstackdepth < 1)
	{
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthfixpathstringname);
		return;
	}

	// check to see if in cgi/isapi mode
	  // it seems I don't use this

	// if there is a colon in filename string, do not need to fix path
	pnamelstring = dg_getplstring(
		pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		stringstackdepth - 1,
		&namelength);

	if (pBHarrayhead->errorcount != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfixpathstringname);
		return;
	}

	scanlength = namelength;

	result = dg_scanforbyte(pnamelstring, &scanlength, ':');

	if (result != dg_success)
	{
		dg_pusherror(pBHarrayhead, result);
		dg_pusherror(pBHarrayhead, dg_scanforbytename);
		dg_pusherror(pBHarrayhead, dg_forthfixpathstringname);
	}

	// if : was found...
	if (scanlength < namelength)
	{
		return;
	}

	// get script file's full path from args buffer
	scriptpath = dg_getpbuffer(pBHarrayhead, DG_ARGS_BUFFERID, &pscriptpathlength);

	// need to scan back from end of string for \
	// then need to push everything from beginning up to and including \ 
	//  to string stack

	i = *pscriptpathlength;

	while (i > 0)
	{
		c = scriptpath[i - 1];

		if ('\\' == c)
		{
			break;
		}

		i--;
	}

	if (i < 1)
	{
		return;
	}

	dg_pushlstring(
		pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		i,
		scriptpath);

	dg_forthswapstring(pBHarrayhead);

	dg_forthcatstring(pBHarrayhead);
}


void dg_forthopenlibrarystring (Bufferhandle* pBHarrayhead)
//                 ( libraryname$ -$- )
//                 ( -openlibraryhandlestack- libraryhandle )
//                 ( -- wordlistid libraryhandle )
{
	UINT64 libraryhandle;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	dg_forthloadlibrarystringsub(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		// error is pushed in subroutine
		return;
	}

	libraryhandle = dg_popbufferuint64(pBHarrayhead, DG_LIBHANDLE_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
		return;
	}

	dg_pushbufferuint64(pBHarrayhead, DG_LIBHANDLE_BUFFERID, libraryhandle);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
		return;
	}

	dg_forthwordlist(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
		return;
	}

	dg_pushdatastack(pBHarrayhead, libraryhandle);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
		return;
	}

	// dg_forthdropstring(pBHarrayhead);
	return;
}


void dg_forthrunfileandwait(Bufferhandle* pBHarrayhead)
{
	const char* perror;
	unsigned char* pfilename;
	char** argv;
	char** envp;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	pfilename = (unsigned char*)dg_popbufferuint64(
		pBHarrayhead,
		DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitname);
		return;
	}

	envp = (char**)dg_popbufferuint64(
		pBHarrayhead,
		DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitname);
		return;
	}

	argv = (char**)dg_popbufferuint64(
		pBHarrayhead,
		DG_DATASTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitname);
		return;
	}

	perror = dg_runfileandwait(
		pBHarrayhead,
		pfilename,
		argv,
		envp,
		dg_success);

	if (perror != dg_success)
	{
		dg_pusherror(pBHarrayhead, perror);
		dg_pusherror(pBHarrayhead, dg_runfileandwaitname);
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitname);
		return;
	}

	return;
}


void dg_forthrunfileandwaitnoenvstring(Bufferhandle* pBHarrayhead)
{
	const char* perror;
	unsigned char* pstring;
	UINT64 stringlength;
	UINT64 stringstackdepth;
	UINT64 myrsp;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	stringstackdepth = dg_getnumberoflstringsonstack(
		pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvstringname);
		return;
	}

	if (stringstackdepth < 1)
	{
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvstringname);
		return;
	}

	dg_forthturnstringinto0string(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvstringname);
		return;
	}

	// get a pointer to the string
	pstring = dg_getplstring(
		pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		stringstackdepth - 1,
		&stringlength);

	if (stringlength == 0)
	{
		return;
	}

	// myrsp = (UINT64)dg_getretstackpointer();

	// dg_printzerostring(pBHarrayhead, (unsigned char*)"Return stack pointer just before calling a subroutine before dg_runfileandwait = ");
	// dg_writestdoutuint64tohex(pBHarrayhead, myrsp);
	// dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

	perror = dg_runfileandwait(
		pBHarrayhead,
		pstring,    // pfilename,   really the command line
		NULL,       // argv[],
		NULL,       // envp[],
		dg_success);


	if (perror != dg_success)
	{
		dg_pusherror(pBHarrayhead, perror);
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvstringname);
		return;
	}

	dg_forthdropstring(pBHarrayhead);
}

void dg_forthrunfileandwaitnoenvquotes(Bufferhandle* pBHarrayhead)
{
	const char* perror;
	const char* pcommandline;
	UINT64 commandlinelength;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	// dg_printzerostring(pBHarrayhead, (unsigned char*)"got there\n");

	// get a pointer to the command line
	pcommandline = (const char*)dg_parse(
		pBHarrayhead,
		&commandlinelength,
		'"');

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
		return;
	}

	if (commandlinelength == 0)
	{
		return;
	}

	// dg_printzerostring(pBHarrayhead, (unsigned char*)"trying command line='");
	// dg_writestdout(pBHarrayhead, (unsigned char*)pcommandline, commandlinelength);
	// dg_printzerostring(pBHarrayhead, (unsigned char*)"'\n");

	// copying string to string stack so I can append a null terminator
	dg_stonewstring(
		pBHarrayhead,
		(unsigned char*)pcommandline,
		commandlinelength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
		return;
	}

	dg_forthrunfileandwaitnoenvstring(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
		return;
	}
}

void dg_forthdocompiletyperunfileandwaitnoenvquotes(Bufferhandle* pBHarrayhead)
//                         ( dataoffset databufid -- )
{
	const char* state;
	const char* pstring;
	UINT64 stringlength = 0;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	dg_forthtwodrop(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthodocompiletyperunfileandwaitnoenvquotesname);
		return;
	}

	state = (const char*)dg_getbufferuint64(
		pBHarrayhead,
		DG_DATASPACE_BUFFERID,
		statevariable);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthstatename);
		dg_pusherror(pBHarrayhead, dg_forthodocompiletyperunfileandwaitnoenvquotesname);
		return;
	}

	if (state == dg_stateexecute)
	{
		dg_forthrunfileandwaitnoenvquotes(pBHarrayhead);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_forthodocompiletyperunfileandwaitnoenvquotesname);
			return;
		}

	}
	else
	{
		if (state == dg_statecompile)
		{
			// get a pointer to the command line
			pstring = (const char*)dg_parse(
				pBHarrayhead,
				&stringlength,
				'"');

			if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
			{
				dg_pusherror(pBHarrayhead, dg_forthodocompiletyperunfileandwaitnoenvquotesname);
				return;
			}

			if (stringlength == 0)
			{
				return;
			}

			dg_compilecopystonewstring(
				pBHarrayhead,
				pstring,
				stringlength);
			
			// I need to compile a call to a function that uses a string on the top of the string stack
			dg_compilecallcore(
				pBHarrayhead,
				(UINT64)(&dg_forthrunfileandwaitnoenvstring));

			if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
			{
				dg_pusherror(pBHarrayhead, dg_forthodocompiletyperunfileandwaitnoenvquotesname);
				return;
			}
		}
		else
		{
			// unknown state do nothing
		}
	}
}


const char* dg_callbuffername = "dg_callbuffer";

UINT64 dg_callbuffer(
	Bufferhandle* pBHarrayhead,
	UINT64 bufferid,
	UINT64 offset)
{
	// UINT64 myrsp;
	unsigned char* addr;
	UINT64 result = (UINT64)-1;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return(result);
	}

	// dg_printzerostring(pBHarrayhead, (unsigned char*)"got here...\n");

	addr = dg_getpbufferoffset(pBHarrayhead, bufferid, offset);

	if (dg_geterrorcount(pBHarrayhead) == olderrorcount)
	{
		__try
		{
			// myrsp = (UINT64)dg_getretstackpointer();

			// dg_printzerostring(pBHarrayhead, (unsigned char*)"Return stack pointer just before calling a forth buffer routine = ");
			// dg_writestdoutuint64tohex(pBHarrayhead, myrsp);
			// dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

			result = dg_callcoreforthroutine(pBHarrayhead, (UINT64)addr);
		}
	    __except (EXCEPTION_EXECUTE_HANDLER)
		{
	       dg_pusherror(pBHarrayhead, dg_osexception);
		   dg_pusherror(pBHarrayhead, dg_callbuffername);
		}
	}
	else
	{
		dg_pusherror(pBHarrayhead, dg_callbuffername);
	}

	return(result); // making this function return a value for testing purposes


	// dg_printzerostring(pBHarrayhead, (unsigned char*)"and here...\n");
}


const char dg_pushsymboltowin64coffsymboltablename[] = " dg_pushsymboltowin64coffsymboltable";

void  dg_pushsymboltowin64coffsymboltable(
	Bufferhandle* pBHarrayhead,
	UINT64 symboltablebufferid,
	UINT64 oversizesymbolnamebufferid,
	unsigned char* psymbolname,
	UINT64 symbolnamelength,
	DWORD value,
	SHORT sectionnumber,
	WORD type,
	BYTE storageclass,
	BYTE numberofauxsymbols)
{
	const char* perror;
	UINT64 oldoversizebufferlength;

	IMAGE_SYMBOL myimagesymbol;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	if (symbolnamelength > 8)
	{
		oldoversizebufferlength = dg_getbufferlength(
			pBHarrayhead,
			oversizesymbolnamebufferid);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_pushsymboltowin64coffsymboltablename);
			return;
		}

		dg_pushbuffersegment(
			pBHarrayhead,
			oversizesymbolnamebufferid,
			symbolnamelength,
			psymbolname);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_pushsymboltowin64coffsymboltablename);
			return;
		}

		// null terminator
		dg_pushbufferbyte(
			pBHarrayhead,
			oversizesymbolnamebufferid,
			0);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_pushsymboltowin64coffsymboltablename);
			return;
		}

		myimagesymbol.N.LongName[0] = 0;
		myimagesymbol.N.LongName[1] = oldoversizebufferlength;
	}
	else
	{
		// unused bytes of short name are supposed to be 0 I think
		myimagesymbol.N.LongName[0] = 0;
		myimagesymbol.N.LongName[1] = 0;

		perror = dg_movebytes(
			psymbolname,
			(unsigned char*)myimagesymbol.N.ShortName,
			symbolnamelength);

		if (perror != dg_success)
		{
			dg_pusherror(pBHarrayhead, perror);
			dg_pusherror(pBHarrayhead, dg_movebytesname);
			dg_pusherror(pBHarrayhead, dg_pushsymboltowin64coffsymboltablename);
			return;
		}
	}

	myimagesymbol.Value = value;
	myimagesymbol.SectionNumber = sectionnumber;
	myimagesymbol.Type = type;
	myimagesymbol.StorageClass = storageclass;
	myimagesymbol.NumberOfAuxSymbols = numberofauxsymbols;

	dg_pushbuffersegment(
		pBHarrayhead,
		symboltablebufferid,
		sizeof(myimagesymbol),
		(unsigned char*)&myimagesymbol);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pushsymboltowin64coffsymboltablename);
		return;
	}
}

const char dg_pushsectionlengthtowin64coffsymboltablename[] = "dg_pushsectionlengthtowin64coffsymboltable";

void dg_pushsectionlengthtowin64coffsymboltable(
	Bufferhandle * pBHarrayhead,
	UINT64 symboltablebufferid,
	UINT64 sectionlength)
{
	IMAGE_SYMBOL myimagesymbol;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	myimagesymbol.N.LongName[0] = sectionlength;
	myimagesymbol.N.LongName[1] = 0;
	myimagesymbol.Value = 0;
	myimagesymbol.SectionNumber = 0;
	myimagesymbol.Type = 0;
	myimagesymbol.StorageClass = 0;
	myimagesymbol.NumberOfAuxSymbols = 0;

	dg_pushbuffersegment(
		pBHarrayhead,
		symboltablebufferid,
		sizeof(myimagesymbol),
		(unsigned char*)&myimagesymbol);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pushsectionlengthtowin64coffsymboltablename);
		return;
	}
}

const char dg_pushexportsymbolstowin64coffbuffersname[] = "dg_pushexportsymbolstowin64coffbuffers";

void dg_pushexportsymbolstowin64coffbuffers(
	Bufferhandle* pBHarrayhead,
	UINT64 exportsymbollisthlistid,
	UINT64 exportsymbollistparentelementid,
	UINT64 symboltablebufferid,
	UINT64 oversizesymbolnamebufferid,
	UINT64 dotdrectvebufferid,
	UINT64 dottextsectionnumber)
{
	unsigned char* pname;
	UINT64 namelength;
	unsigned char* pvalue;
	UINT64 valuelength;
	UINT64 value;
	UINT64 storageclass;

	Hlistheader myexportsymbolhlistheader;
	UINT64 exportsymbolsortedkeyslstringlength = 0;
	unsigned char* pexportsymbolsortedkeyslstring;
	UINT64 numberofexportsymbols = 0;

	UINT64 srcchildelementid;
        UINT64 foundflag;
        UINT64 indexofkeyaftermatch;
        UINT64 sortkey;

	UINT64 i;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	// need to check for the not using export hlist case
	if (exportsymbollisthlistid == (UINT64)-1)
	{
		return;
	}

	// using this function so that we know the memory at the hlist header is valid
	dg_gethlistheader(
		pBHarrayhead,
		exportsymbollisthlistid,
		&myexportsymbolhlistheader,
		sizeof(Hlistheader));

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
		return;
	}

	// export symbol list
	pexportsymbolsortedkeyslstring = dg_getplstring(
		pBHarrayhead,
		myexportsymbolhlistheader.sortedchildidslstroffsetbufid,
		myexportsymbolhlistheader.sortedchildidslstrstringbufid,
		exportsymbollistparentelementid,
		&exportsymbolsortedkeyslstringlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
		dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
		return;
	}

	if ((exportsymbolsortedkeyslstringlength % sizeof(UINT64)) != 0)
	{
		dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
		dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
		dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
		return;
	}

	numberofexportsymbols = exportsymbolsortedkeyslstringlength >> 3;


	//if (0 == numberofexportsymbols)
	//{
	//	return;
	// }

	// calculate length of all export directives
	//  and build export directive string table
	// totallengthofsymbolnames = 0;

	// this goes through children alphabetically
	for (i = 0; i < numberofexportsymbols; i++)
	{
		srcchildelementid = ((UINT64*)pexportsymbolsortedkeyslstring)[i];

                // need to see if element has a child named 'ENTRY'
                foundflag = dg_findsortedhlistchild (
                    pBHarrayhead,
                    (unsigned char*)"ENTRY", // pname
                    5, // namelength,  
                    exportsymbollisthlistid, 
                    srcchildelementid, // parentelementid,      
                    &indexofkeyaftermatch, // index in sort key lstring after match
                    &sortkey); 

		if (foundflag != 0)
		{
		    storageclass = 0x02; // is an export symbol

                    // push string onto end of export directives
                    dg_pushbuffersegment(
                        pBHarrayhead,
                        dotdrectvebufferid,
                        8,
                        (unsigned char*)"/EXPORT:");

		    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                    {
                        dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
                        return;
                    }
		}
		else
		{
		    storageclass = 0x02; // is the entry symbol e.g. main

                    // push string onto end of export directives
                    dg_pushbuffersegment(
                        pBHarrayhead,
                        dotdrectvebufferid,
                        7,
                        (unsigned char*)"/ENTRY:");

		    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		    {
			dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
			return;
		    }
		}

		// find the child's name in the source hlist
		pname = dg_getshlistelementnom(
			pBHarrayhead,
			exportsymbollisthlistid,
			srcchildelementid,
			&namelength);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
			return;
		}

		dg_pushbuffersegment(
			pBHarrayhead,
			dotdrectvebufferid,
			namelength,
			pname);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
			return;
		}

		dg_pushbuffersegment(
			pBHarrayhead,
			dotdrectvebufferid,
			1,
			(unsigned char*)" ");

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
			return;
		}

		pvalue = dg_getshlistelementvalue(
			pBHarrayhead,
			exportsymbollisthlistid,
			srcchildelementid,
			&valuelength);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
			return;
		}

		if (valuelength < sizeof(UINT64))
		{
			// need a better error here... something like hlist value too small
			// or patch offset missing or corrupt
			dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
			dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
			return;
		}

		value = *((UINT64*)pvalue);

		// could make sure value fits into a UINT32...
		if (value > 0xFFFFFFFF)
		{
			dg_pusherror(pBHarrayhead, dg_toobigfordesterror);
			dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
			return;
		}

		// totallengthofsymbolnames += namelength;
		dg_pushsymboltowin64coffsymboltable(
			pBHarrayhead,
			symboltablebufferid,
			oversizesymbolnamebufferid,
			pname,
			namelength,
			(DWORD)value,
			dottextsectionnumber,
			0x20, // WORD type,
			storageclass, // BYTE storageclass,
			0);   //  BYTE numberofauxsymbols);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_pushexportsymbolstowin64coffbuffersname);
			return;
		}
	}
}

const char dg_pushimportymbolstowin64coffbuffersname[] = "dg_pushimportsymbolstowin64coffbuffers";

UINT64 dg_pushimportsymbolstowin64coffbuffers(
	Bufferhandle* pBHarrayhead,
	UINT64 importsymbollisthlistid,
	UINT64 importsymbollistparentelementid,
	UINT64 symboltablebufferid,
	UINT64 oversizesymbolnamebufferid,
	UINT64 relocationtablebufferid)
{
	unsigned char* pname;
	UINT64 namelength;
	unsigned char* pvalue;
	UINT64 valuelength;
	UINT64 value;

	unsigned char* plastimportname = (unsigned char*)"";
	UINT64 lastimportnamelength = (UINT64)-1;  // making this -1 in case someone defines an empty string
											   //  as the first import symbol name... so that the empty
											   //  string will be seen as a new import symbol name

	// UINT64 totallengthofsymbolnames;

	UINT64 i, srcchildelementid;
	UINT64 srcsortedkeyslstringlength;

	Hlistheader myimportsymbolhlistheader;
	UINT64 importsymbolsortedkeyslstringlength = 0;
	unsigned char* pimportsymbolsortedkeyslstring;
	UINT64 numberofrelocationentries = 0;
	UINT64 numberofsymbols = 0;

	INT64 compareflag;

	const char* pError;

	IMAGE_RELOCATION myrelocationarrayelement;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return(numberofrelocationentries);
	}

	// import symbol list
    // need to check for the not using import hlist case
	if (importsymbollisthlistid == (UINT64)-1)
	{
		return(numberofrelocationentries);
	}

	// using this function so that we know the memory at the hlist header is valid
	dg_gethlistheader(
		pBHarrayhead,
		importsymbollisthlistid,
		&myimportsymbolhlistheader,
		sizeof(Hlistheader));

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
		return(numberofrelocationentries);
	}

	pimportsymbolsortedkeyslstring = dg_getplstring(
		pBHarrayhead,
		myimportsymbolhlistheader.sortedchildidslstroffsetbufid,
		myimportsymbolhlistheader.sortedchildidslstrstringbufid,
		importsymbollistparentelementid,
		&srcsortedkeyslstringlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
		dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
		return(numberofrelocationentries);
	}

	if ((srcsortedkeyslstringlength % sizeof(UINT64)) != 0)
	{
		dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
		dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
		dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
		return(numberofrelocationentries);
	}

	numberofrelocationentries = srcsortedkeyslstringlength >> 3;

	// it should already be clear, but just in case
	dg_clearbuffer(
		pBHarrayhead,
		relocationtablebufferid);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
		return(numberofrelocationentries);
	}

	// this goes through children alphabetically
	//  if numberofimportsymbols is 0, this for loop should not go....
	for (i = 0; i < numberofrelocationentries; i++)
	{
		// if this is a new import symbol name, then this symbol name
		//   needs to get added to the import symbol list

		srcchildelementid = ((UINT64*)pimportsymbolsortedkeyslstring)[i];

		// find the child's name in the source hlist
		pname = dg_getshlistelementnom(
			pBHarrayhead,
			importsymbollisthlistid,
			srcchildelementid,
			&namelength);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
			return(numberofrelocationentries);
		}

		pError = dg_comparebytes(
			(unsigned char*)pname,
			namelength,
			(unsigned char*)plastimportname,
			lastimportnamelength,
			&compareflag);

		// this shouldn't happen
		if (pError != dg_success)
		{
			dg_pusherror(pBHarrayhead, dg_comparebytesname);
			dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
			return(numberofrelocationentries);
		}

		// if they don't match then we need to add a symbol to the symbol table
		if (0 != compareflag)
		{
			// we have a new symbol name
			plastimportname = pname;
			lastimportnamelength = namelength;

			dg_pushsymboltowin64coffsymboltable(
				pBHarrayhead,
				symboltablebufferid,
				oversizesymbolnamebufferid,
				pname,
				namelength,
				0, // DWORD value,
				0, // sectionnumber, import symbols have a section number of 0
				0, // WORD type,
				2, // BYTE storageclass,
				0); //  numberofauxsymbols);

			if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
			{
				dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
				return(numberofrelocationentries);
			}

			if ((dg_getbufferlength(
				pBHarrayhead,
				symboltablebufferid) % sizeof(IMAGE_SYMBOL)) != 0)
			{
				dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
				dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
				return(numberofrelocationentries);
			}

			numberofsymbols = dg_getbufferlength(
				pBHarrayhead,
				symboltablebufferid) / sizeof(IMAGE_SYMBOL);

			if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
			{
				dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
				return(numberofrelocationentries);
			}
		}

		// need to add the relocation entry
		// srcchildelementid = ((UINT64*)pimportsymbolsortedkeyslstring)[i];

		// get the source child element's value. This is the offset in the buffer to be patched.
		pvalue = dg_getshlistelementvalue(
			pBHarrayhead,
			importsymbollisthlistid,
			srcchildelementid,
			&valuelength);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
			return(numberofrelocationentries);
		}

		if (valuelength < sizeof(UINT64))
		{
			// need a better error here... something like hlist value too small
			// or patch offset missing or corrupt
			dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
			dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
			return(numberofrelocationentries);
		}

		value = *((UINT64*)pvalue);

		// could make sure that value fits into an UINT32
		myrelocationarrayelement.VirtualAddress = (DWORD)value;
		myrelocationarrayelement.SymbolTableIndex = numberofsymbols - 1; // 0 based
		myrelocationarrayelement.Type = IMAGE_REL_AMD64_ADDR64; // IMAGE_REL_AMD64_REL32;
		
		// need to push this to a temporary buffer...
		dg_pushbuffersegment(
			pBHarrayhead,
			relocationtablebufferid,
			sizeof(myrelocationarrayelement),
			(unsigned char*)&myrelocationarrayelement);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_pushimportymbolstowin64coffbuffersname);
			return(numberofrelocationentries);
		}
	}

	return(numberofrelocationentries);
}


const char dg_makedototobufsubname[] = "dg_makedototobufsub";

void dg_makedototobufsub(
	Bufferhandle* pBHarrayhead,
	unsigned char* pcode,
	UINT64 codelength,
	UINT64 exportsymbollisthlistid,
	UINT64 exportsymbollistparentelementid,
	UINT64 importsymbollisthlistid,
	UINT64 importsymbollistparentelementid,
	UINT64 destbuf,
	UINT64 symboltablebufferid,
	UINT64 oversizesymbolnamebufferid,
	UINT64 relocationtablebufferid,
	UINT64 dotdrectvebufferid)
{
	IMAGE_FILE_HEADER myimagefileheader;
	IMAGE_SECTION_HEADER mytextsectionheader;
	IMAGE_SECTION_HEADER mydatasectionheader;
	IMAGE_SECTION_HEADER mydotdrectvesectionheader;
	UINT64 numberofrelocationentries = 0;
	UINT64 dotdrectvelength = 0;
	UINT64 x;
	UINT64 textsectionpadding = 0; // to align to UINT16
	UINT64 dotdrectvesectionpadding = 0; // to align to UINT16

	ULARGE_INTEGER mysecondssince1601jan01;

	unsigned char* pbuffer;
	UINT64* pbufferlength;

	const char* perror;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	textsectionpadding = (codelength % 1);

	// need to make room for the length of the oversize symbol name buffer
	dg_pushbufferuint32(
		pBHarrayhead,
		oversizesymbolnamebufferid,
		0);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	// need to push the section symbol names along with their lengths...

	// push .text$mn symbol
	dg_pushsymboltowin64coffsymboltable(
		pBHarrayhead,
		symboltablebufferid,
		oversizesymbolnamebufferid,
		(unsigned char*)".text$mn", // pname,
		8,                          // namelength,
		0,                          // (DWORD)value,
		1,                          // dottextsectionnumber,
		0, // WORD type,
		0x03, // BYTE storageclass,
		1);   //  BYTE numberofauxsymbols);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	// push extra symbol data for text section length
	dg_pushsectionlengthtowin64coffsymboltable(
		pBHarrayhead,
		symboltablebufferid,
		codelength); // sectionlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	// push .data symbol
	// push extra symbol data for data section length
	dg_pushsymboltowin64coffsymboltable(
		pBHarrayhead,
		symboltablebufferid,
		oversizesymbolnamebufferid,
		(unsigned char*)".data", // pname,
		5,                          // namelength,
		0,                          // (DWORD)value,
		2,                          // dottextsectionnumber,
		0, // WORD type,
		0x03, // BYTE storageclass,
		1);   //  BYTE numberofauxsymbols);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	dg_pushsectionlengthtowin64coffsymboltable(
		pBHarrayhead,
		symboltablebufferid,
		0); // sectionlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	// push the import symbols
	numberofrelocationentries = dg_pushimportsymbolstowin64coffbuffers(
		pBHarrayhead,
		importsymbollisthlistid,
		importsymbollistparentelementid,
		symboltablebufferid,
		oversizesymbolnamebufferid,
		relocationtablebufferid);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	// push the export symbols
	dg_pushexportsymbolstowin64coffbuffers(
		pBHarrayhead,
		exportsymbollisthlistid,
		exportsymbollistparentelementid,
		symboltablebufferid,
		oversizesymbolnamebufferid,
		dotdrectvebufferid,
		1); //  dottextsectionnumber);

	x = dg_getbufferlength(
		pBHarrayhead,
		dotdrectvebufferid);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	// push .drectve symbol
	// push extra symbol data for .drectve section length
	dg_pushsymboltowin64coffsymboltable(
		pBHarrayhead,
		symboltablebufferid,
		oversizesymbolnamebufferid,
		(unsigned char*)".drectve", // pname,
		8,                          // namelength,
		0,                          // (DWORD)value,
		3,                          // dottextsectionnumber,
		0, // WORD type,
		0x03, // BYTE storageclass,
		1);   //  BYTE numberofauxsymbols);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	dg_pushsectionlengthtowin64coffsymboltable(
		pBHarrayhead,
		symboltablebufferid,
		x); // sectionlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	// set the oversize symbol name buffer length variable
	x = dg_getbufferlength(
		pBHarrayhead,
		oversizesymbolnamebufferid);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	dg_putbufferuint32(
		pBHarrayhead,
		oversizesymbolnamebufferid,
		0, //  offset,
		x); // data);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	// setting up section header 1
	perror = dg_movebytes(
		(unsigned char*)".text$mn",
		mytextsectionheader.Name,
		8);

	if (perror != dg_success)
	{
		dg_pusherror(pBHarrayhead, perror);
		dg_pusherror(pBHarrayhead, dg_movebytesname);
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	// text section is first after section headers
	mytextsectionheader.Misc.PhysicalAddress = 0;
	mytextsectionheader.VirtualAddress = 0;
	mytextsectionheader.SizeOfRawData = codelength;
	mytextsectionheader.PointerToRawData = sizeof(IMAGE_FILE_HEADER) + (3 * sizeof(IMAGE_SECTION_HEADER)); // fileheadersize + 3 * sectionheader size
	mytextsectionheader.PointerToRelocations = mytextsectionheader.PointerToRawData + codelength + textsectionpadding; // aligning to 2 byte boundary because that's what ML64.exe does
	mytextsectionheader.NumberOfRelocations = numberofrelocationentries;
	mytextsectionheader.NumberOfLinenumbers = 0;
	mytextsectionheader.Characteristics = 0x60500020;

	// setting up section header 2
	perror = dg_movebytes(
		(unsigned char*)".data\0\0\0",
		mydatasectionheader.Name,
		8);

	if (perror != dg_success)
	{
		dg_pusherror(pBHarrayhead, perror);
		dg_pusherror(pBHarrayhead, dg_movebytesname);
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	// text relocations are next

	mydatasectionheader.Misc.PhysicalAddress = 0;
	mydatasectionheader.VirtualAddress = 0;
	mydatasectionheader.SizeOfRawData = 0;
	mydatasectionheader.PointerToRawData = 0;  
	mydatasectionheader.PointerToRelocations = 0; 
	mydatasectionheader.NumberOfRelocations = 0;
	mydatasectionheader.NumberOfLinenumbers = 0;
	mydatasectionheader.Characteristics = 0xC0500040;

	// there is no data section

	// setting up section header 3
	// .drectve section is next
	dotdrectvelength = dg_getbufferlength(
		pBHarrayhead,
		dotdrectvebufferid);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	dotdrectvesectionpadding = dotdrectvelength % 1;

	perror = dg_movebytes(
		(unsigned char*)".drectve",
		mydotdrectvesectionheader.Name,
		8);

	if (perror != dg_success)
	{
		dg_pusherror(pBHarrayhead, perror);
		dg_pusherror(pBHarrayhead, dg_movebytesname);
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	mydotdrectvesectionheader.Misc.PhysicalAddress = 0;
	mydotdrectvesectionheader.VirtualAddress = 0;
	mydotdrectvesectionheader.SizeOfRawData = dotdrectvelength;
	mydotdrectvesectionheader.PointerToRawData = mytextsectionheader.PointerToRelocations + (numberofrelocationentries * sizeof(IMAGE_RELOCATION)); // probaby need to align this to an even byte
	mydotdrectvesectionheader.PointerToRelocations = 0;
	mydotdrectvesectionheader.NumberOfRelocations = 0;
	mydotdrectvesectionheader.NumberOfLinenumbers = 0;
	mydotdrectvesectionheader.Characteristics = 0xA00;

	x = dg_getbufferlength(
		pBHarrayhead,
		symboltablebufferid);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	if ((x % IMAGE_SIZEOF_SYMBOL) != 0)
	{
		dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	mysecondssince1601jan01.QuadPart = dg_getmicrosecondssince1970Jan01() / 1000000;

	// soo do we have to worry about mysecondssince1601jan01 not fitting into a 32 bit integer in about 80 years?
	
	// setting up the file header
	myimagefileheader.Machine = IMAGE_FILE_MACHINE_AMD64; // 0x8664
	myimagefileheader.NumberOfSections = 3;
	myimagefileheader.TimeDateStamp = mysecondssince1601jan01.LowPart;
	myimagefileheader.PointerToSymbolTable = mydotdrectvesectionheader.PointerToRawData + dotdrectvelength + dotdrectvesectionpadding; // aligning to 2 byte boundary
	myimagefileheader.NumberOfSymbols = x / IMAGE_SIZEOF_SYMBOL; // total number of entries in table, not just the symbols
	myimagefileheader.SizeOfOptionalHeader = 0;
	myimagefileheader.Characteristics = 0;

	dg_pushbuffersegment(
		pBHarrayhead,
		destbuf,
		sizeof(IMAGE_FILE_HEADER),
		(unsigned char*)&myimagefileheader);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	dg_pushbuffersegment(
		pBHarrayhead,
		destbuf,
		sizeof(IMAGE_SECTION_HEADER),
		(unsigned char*)&mytextsectionheader);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	dg_pushbuffersegment(
		pBHarrayhead,
		destbuf,
		sizeof(IMAGE_SECTION_HEADER),
		(unsigned char*)&mydatasectionheader);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	dg_pushbuffersegment(
		pBHarrayhead,
		destbuf,
		sizeof(IMAGE_SECTION_HEADER),
		(unsigned char*)&mydotdrectvesectionheader);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	dg_pushbuffersegment(
		pBHarrayhead,
		destbuf,
		codelength,
		pcode);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	if (textsectionpadding != 0)
	{
		dg_pushbufferbyte(
			pBHarrayhead,
			destbuf,
			0);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
			return;
		}
	}

	// push relocation buffer to destbuf
	pbuffer = dg_getpbuffer(
		pBHarrayhead,
		relocationtablebufferid,
		&pbufferlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	dg_pushbuffersegment(
		pBHarrayhead,
		destbuf,
		*pbufferlength,
		pbuffer);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	// there is no data section to push
	
	// push dotdrectve buffer to destbuf
	pbuffer = dg_getpbuffer(
		pBHarrayhead,
		dotdrectvebufferid,
		&pbufferlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	dg_pushbuffersegment(
		pBHarrayhead,
		destbuf,
		*pbufferlength,
		pbuffer);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	if (dotdrectvesectionpadding != 0)
	{
		dg_pushbufferbyte(
			pBHarrayhead,
			destbuf,
			0);

		if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
		{
			dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
			return;
		}
	}

	// push symbol table buffer to destbuf
	pbuffer = dg_getpbuffer(
		pBHarrayhead,
		symboltablebufferid,
		&pbufferlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	dg_pushbuffersegment(
		pBHarrayhead,
		destbuf,
		*pbufferlength,
		pbuffer);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	// push oversize symbol name buffer to destbuf
	pbuffer = dg_getpbuffer(
		pBHarrayhead,
		oversizesymbolnamebufferid,
		&pbufferlength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}

	dg_pushbuffersegment(
		pBHarrayhead,
		destbuf,
		*pbufferlength,
		pbuffer);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
		return;
	}
}


// looks like Windows no longer requires the .drectve buffer, but it still works if you leave it in
//  J.N. 2022 May 22
const char dg_makedototobufname[] = "dg_makedototobuf";

void dg_makedototobuf(
	Bufferhandle* pBHarrayhead,
	unsigned char* pcode,
	UINT64 codelength,
	UINT64 exportsymbollisthlistid,
	UINT64 exportsymbollistparentelementid,
	UINT64 importsymbollisthlistid,          // largestunsignedint means not using imports
	UINT64 importsymbollistparentelementid,
	UINT64 destbufid)
{
	const char* pError;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	UINT64 symboltablebufferid;
	UINT64 oversizesymbolnamebufferid;
	UINT64 relocationtablebufferid;
	UINT64 dotdrectvebufferid;

	symboltablebufferid = dg_newbuffer(
		pBHarrayhead,
		0x1000, // growby,
		largestsignedint, // maxsize,
		&pError, // const char** pError,
		FORTH_FALSE); // forceoutofmemory) )

	if (pError != dg_success)
	{
		dg_pusherror(pBHarrayhead, pError);
		dg_pusherror(pBHarrayhead, dg_newbuffername);
		dg_pusherror(pBHarrayhead, dg_makedototobufname);
		return;
	}

	oversizesymbolnamebufferid = dg_newbuffer(
		pBHarrayhead,
		0x1000, // growby,
		largestsignedint, // maxsize,
		&pError, // const char** pError,
		FORTH_FALSE); // forceoutofmemory) )

	if (pError != dg_success)
	{
		dg_freebuffer(pBHarrayhead, symboltablebufferid);

		dg_pusherror(pBHarrayhead, pError);
		dg_pusherror(pBHarrayhead, dg_newbuffername);
		dg_pusherror(pBHarrayhead, dg_makedototobufname);
		return;
	}

	relocationtablebufferid = dg_newbuffer(
		pBHarrayhead,
		0x1000, // growby,
		largestsignedint, // maxsize,
		&pError, // const char** pError,
		FORTH_FALSE); // forceoutofmemory) )

	if (pError != dg_success)
	{
		dg_freebuffer(pBHarrayhead, symboltablebufferid);
		dg_freebuffer(pBHarrayhead, oversizesymbolnamebufferid);

		dg_pusherror(pBHarrayhead, pError);
		dg_pusherror(pBHarrayhead, dg_newbuffername);
		dg_pusherror(pBHarrayhead, dg_makedototobufname);
		return;
	}

	dotdrectvebufferid = dg_newbuffer(
		pBHarrayhead,
		0x1000, // growby,
		largestsignedint, // maxsize,
		&pError, // const char** pError,
		FORTH_FALSE); // forceoutofmemory) )

	if (pError != dg_success)
	{
		dg_freebuffer(pBHarrayhead, symboltablebufferid);
		dg_freebuffer(pBHarrayhead, oversizesymbolnamebufferid);
		dg_freebuffer(pBHarrayhead, relocationtablebufferid);

		dg_pusherror(pBHarrayhead, pError);
		dg_pusherror(pBHarrayhead, dg_newbuffername);
		dg_pusherror(pBHarrayhead, dg_makedototobufname);
		return;
	}

	dg_makedototobufsub(
		pBHarrayhead,
		pcode,
		codelength,
		exportsymbollisthlistid,
		exportsymbollistparentelementid,
		importsymbollisthlistid,
		importsymbollistparentelementid,
		destbufid,
		symboltablebufferid,
		oversizesymbolnamebufferid,
		relocationtablebufferid,
		dotdrectvebufferid);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_makedototobufname);
		// not returning here on purpose so the buffers will be freed
	}

	// if the buffer wasn't allocated, the id should be dg_badbufferid
	  // dg_freebuffer will not give an error or try to free dg_badbufferid
	dg_freebuffer(pBHarrayhead, symboltablebufferid);
	dg_freebuffer(pBHarrayhead, oversizesymbolnamebufferid);
	dg_freebuffer(pBHarrayhead, relocationtablebufferid);
	dg_freebuffer(pBHarrayhead, dotdrectvebufferid);
}

DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK* lpECB)
{
	Bufferhandle* pBHarrayhead = NULL;
	char strStatus[20] = "200 OK\r\n\r\n";
	char strMoreStatus[20] = "";
	char strHeader[1] = "";

	HSE_SEND_HEADER_EX_INFO myhsesendheaderexinfo;

	BOOL flag = true;;
	UINT32 errorcode;
	UINT32 gotexception = FORTH_FALSE;

	UINT64 hfile;
	// const char* perror;

	// ::MessageBeep(0xFFFFFFFF);

	pBHarrayhead = dg_init(0, (char**)-1);

	if (badbufferhandle == (void*)pBHarrayhead)
	{
		return(HSE_STATUS_ERROR);
	}

	pBHarrayhead->pisapiecb = lpECB;

	// Apache doesn't use PATH_TRANSLATED so you can't assume 
	  // lpszPathTranslated will always be there. (found this one out the hard way)
	  // actually, it's supposed to be there... looked in Apache source code
	  // for some reason Apache is not initializing correctly in the latest version
	  // I have. 6/27/2013

	dg_clearbuffer(pBHarrayhead, DG_ARGS_BUFFERID);

	if (0 != lpECB->lpszPathTranslated)
	{
		dg_push0stringtobuffersegment(
			pBHarrayhead,
			DG_ARGS_BUFFERID,
			(unsigned char*)lpECB->lpszPathTranslated);

		// error count should be 0 here since we just started
		if (dg_geterrorcount(pBHarrayhead) != 0)
		{
			return(HSE_STATUS_ERROR);
		}
	}

	// dg_openfileforwritenew((const char*)"c:\\Users\\thain\\desktop\\gothere.txt", &hfile, dg_success);
	// dg_writefile(pBHarrayhead, hfile, (unsigned char*)"got here", 8, dg_success);
	// dg_closefile(hfile, dg_success);

		// Send HTTP headers back to the client
		// Windows will send a default header unless you call this function with a pointer to a header string
		//  an empty string works.
		// The default header is a problem because in CGI mode a default header is not sent so
		//  the scripts would have to be different for ISAPI and CGI if this function call were not here.
		// Still sending the response "200 OK" because that is sent in CGI mode.

		//***align16here***
		// flag = lpECB->ServerSupportFunction(
		//  lpECB->ConnID,
		//  HSE_REQ_SEND_RESPONSE_HEADER,
		//  (char*)strStatus,
		//  0,
		//  NULL);

	if (0 == lpECB->ServerSupportFunction)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"200 OK\r\n\r\n");
		dg_printzerostring(pBHarrayhead, (unsigned char*)"Content-type: text/html\r\n\r\n");
		dg_printzerostring(pBHarrayhead, (unsigned char*)"<html><head></head><body><h2>Got Server Error</h2>");
		dg_printzerostring(
			pBHarrayhead,
			(unsigned char*)"<html><head></head><body>");
		dg_printzerostring(
			pBHarrayhead,
			(unsigned char*)"<p>The server's ServerSupportFunction is missing! Diaperglu needs this function so that you can use the same scripts in CGI and ISAPI mode.</p>");
		dg_printzerostring(pBHarrayhead, (unsigned char*)"</body></html>");

		dg_cleanup(pBHarrayhead);
	}

	gotexception = FORTH_FALSE;

	myhsesendheaderexinfo.pszStatus = strStatus;
	myhsesendheaderexinfo.pszHeader = strHeader;
	myhsesendheaderexinfo.cchStatus = 7;
	myhsesendheaderexinfo.cchHeader = 0;
	myhsesendheaderexinfo.fKeepConn = false;


	__try
	{
		// flag = dg_callprocaddressalign16(
		//    (UINT32*)(lpECB->ServerSupportFunction), // apparently & not required
		//    5,
		//    lpECB->ConnID,
		//    HSE_REQ_SEND_RESPONSE_HEADER,
		//    strStatus,
		//    7, // length of strStatus including null terminator, supposedly not used
		//    strMoreStatus); // required for Apache to work I think

		lpECB->ServerSupportFunction(
			lpECB->ConnID,
			HSE_REQ_SEND_RESPONSE_HEADER,
		    (LPDWORD)strStatus,
		    NULL, 
			(LPDWORD)strMoreStatus);

		// lpECB->ServerSupportFunction(
		//	lpECB->ConnID,
		//	HSE_REQ_SEND_RESPONSE_HEADER_EX,
		//	&myhsesendheaderexinfo,
		//	0, 
		//	NULL);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		gotexception = FORTH_TRUE;
	}

	if (gotexception != FORTH_FALSE)
	{
		dg_printzerostring(pBHarrayhead, (unsigned char*)"200 OK\r\n\r\n");
		dg_printzerostring(pBHarrayhead, (unsigned char*)"Content-type: text/html\r\n\r\n");
		dg_printzerostring(pBHarrayhead, (unsigned char*)"<html><head></head><body><h2>Got Server Error</h2>");
		dg_printzerostring(
			pBHarrayhead,
			(unsigned char*)"<html><head></head><body>");
		dg_printzerostring(
			pBHarrayhead,
			(unsigned char*)"<p>Got an exception trying to call the server's ServerSupportFunction with the code to send the response header.</p>");
		dg_printzerostring(pBHarrayhead, (unsigned char*)"</body></html>");

		dg_cleanup(pBHarrayhead);
	}

	if (false == flag)
	{
		errorcode = ::GetLastError();

		// could not send response header
		  // something is really wrong with the server
		  // sending error page
		dg_printzerostring(pBHarrayhead, (unsigned char*)"200 OK\r\n\r\n");
		dg_printzerostring(pBHarrayhead, (unsigned char*)"Content-type: text/html\r\n\r\n");
		dg_printzerostring(pBHarrayhead, (unsigned char*)"<html><head></head><body><h2>Got Server Error</h2>");
		dg_printzerostring(
			pBHarrayhead,
			(unsigned char*)"<html><head></head><body>");
		dg_printzerostring(
			pBHarrayhead,
			(unsigned char*)"<p>Got an error trying to call the server's ServerSupportFunction with the code to send the response header.</p>");
		dg_printzerostring(pBHarrayhead, (unsigned char*)"</body></html>");

		dg_cleanup(pBHarrayhead);

		return (HSE_STATUS_ERROR);
	}

	// dg_printzerostring(pBHarrayhead, (unsigned char*)"200 OK\r\n\r\n");
	// dg_printzerostring(pBHarrayhead, (unsigned char*)"Content-type: text/html\r\n\r\n");
	// dg_printzerostring(pBHarrayhead, (unsigned char*)"<html><head></head><body>test2<br>");
	// dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n<br>path =");
	// dg_printzerostring(pBHarrayhead, (unsigned char*)lpECB->lpszPathTranslated);
	// dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n<br>url =");
	// dg_printzerostring(pBHarrayhead, (unsigned char*)lpECB->lpszQueryString);
	// dg_printzerostring(pBHarrayhead, (unsigned char*)"\r\n<br>method =");
	// dg_printzerostring(pBHarrayhead, (unsigned char*)lpECB->lpszMethod);
	// dg_printzerostring(pBHarrayhead, (unsigned char*)"</body></html>");

	dg_forthquit(pBHarrayhead);

	dg_cleanup(pBHarrayhead);

	return(HSE_STATUS_SUCCESS);
}

