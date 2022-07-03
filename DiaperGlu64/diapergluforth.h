// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.5.
//
//    DiaperGlu v5.5 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.5 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.5; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// July 2, 2022               //
// version 5.5                //
// /////////////////////////////

#if !defined(_INC_diapergluforth)
#define _INC_diapergluforth

#ifdef  __cplusplus
extern "C" {
#endif

#define FLOAT32 float
#define FLOAT64 double

    // /////////////////////
    // MinGW Win32 stuff  //
    // /////////////////////


#ifdef DGLU_OS_WIN64
    
#include "windows.h" // for the types in basestd.h
// #include "httpext.h"

#ifdef DGLU_NO_DIAPER

#define DG_DIAPERGLU_LIB_NAME "libnodiaperglu.dll"
#define DG_DIAPERGLU_LIB_NAME_LENGTH (18)
#define DG_DIAPERGLUOSAPI_LIB_NAME "nodiapergluosapi.dll"
#define DG_DIAPERGLUOSAPI_LIB_NAME_LENGTH (20)

#endif

#ifndef DGLU_NO_DIAPER

#define DG_DIAPERGLU_LIB_NAME "libdiaperglu.dll"
#define DG_DIAPERGLU_LIB_NAME_LENGTH (16)
#define DG_DIAPERGLUOSAPI_LIB_NAME "diapergluosapi.dll"
#define DG_DIAPERGLUOSAPI_LIB_NAME_LENGTH (18)

#endif

#define DG_PATH_SLASH_SYMBOL ((unsigned char)'\\')

#define DG_WIN64_FILETIME_1970_JAN_1 (0x019DB1DED53E8000)

#define dg_param1reg dg_rcx
#define dg_param2reg dg_rdx
#define dg_param3reg dg_r8
#define dg_param4reg dg_r9
    
    typedef __int16 INT16;
    typedef unsigned __int16 UINT16;
    
    typedef __int32 INT32;
    typedef unsigned __int32 UINT32;
    
    typedef __int64 INT64;
    typedef unsigned __int64 UINT64;

    LONG dg_catchbadmemoryerror(LPEXCEPTION_POINTERS pexception);
    LONG dg_catchbadmemoryerrorwithfullframe(LPEXCEPTION_POINTERS pexception);

    void dg_trycatchbadmemoryerror();
    void dg_trycatchbadmemoryerrorwithfullframe();
    void dg_endtrycatchbadmemoryerror();
    
    const char* dg_catchbadmemoryexit();
    const char* dg_catchbadmemoryexitwithfullframe();

    extern const char dg_symboltypefunction[];
    extern const char dg_symboltypeconstant[];
    extern const char dg_symboltypeunknown[];
    extern const char dg_getlibrarysymbolname[];

    const char* dg_getlibrarysymbol(
        HINSTANCE hlibrary,
        UINT64 symbolnumber,     // not ordinal
        const char** psymbolname,
        UINT64* pnamelength,
        const char** psymboltype,
        UINT64* psymbolvalue,
        const char* forceerrorflag);

    extern const char dg_getnumberoflibrarysymbolsname[];

    const char* dg_getnumberoflibrarysymbols(
        HINSTANCE hlibrary,
        UINT64* pnumberofsymbols,
        const char* forceerrorflag);

#ifdef DGLU_EXPORTS

#define DGLU_API __declspec(dllexport)
//#define DGLU_API __attribute__ ((__dllexport__))

#endif

#ifdef DGLU_IMPORTS

#define DGLU_API __declspec(dllimport)
//#define DGLU_API __attribute__ ((__dllimport__))
    
#endif
    
    // declared in httpext.h
    // doing it here because we need to export these three functions
#define   HSE_LOG_BUFFER_LEN         80
#define   HSE_MAX_EXT_DLL_NAME_LEN  256
#define   HSE_IO_SYNC               0x00000001   // for WriteClient

#define   HSE_STATUS_SUCCESS                       1
#define   HSE_STATUS_SUCCESS_AND_KEEP_CONN         2
#define   HSE_STATUS_PENDING                       3
#define   HSE_STATUS_ERROR                         4

#define   HSE_REQ_BASE                             0
#define   HSE_REQ_SEND_URL_REDIRECT_RESP           ( HSE_REQ_BASE + 1 )
#define   HSE_REQ_SEND_URL                         ( HSE_REQ_BASE + 2 )
#define   HSE_REQ_SEND_RESPONSE_HEADER             ( HSE_REQ_BASE + 3 )
#define   HSE_REQ_DONE_WITH_SESSION                ( HSE_REQ_BASE + 4 )
#define   HSE_REQ_END_RESERVED                     1000

    typedef   LPVOID          HCONN;

    typedef struct   _HSE_VERSION_INFO {

        DWORD  dwExtensionVersion;
        CHAR   lpszExtensionDesc[HSE_MAX_EXT_DLL_NAME_LEN];

    } HSE_VERSION_INFO, * LPHSE_VERSION_INFO;

    typedef struct _HSE_SEND_HEADER_EX_INFO {

        //
        // HTTP status code and header
        //

        LPCSTR  pszStatus;  // HTTP status code  eg: "200 OK"
        LPCSTR  pszHeader;  // HTTP header

        DWORD   cchStatus;  // number of characters in status code
        DWORD   cchHeader;  // number of characters in header

        BOOL    fKeepConn;  // keep client connection alive?

    } HSE_SEND_HEADER_EX_INFO, * LPHSE_SEND_HEADER_EX_INFO;

    typedef struct _EXTENSION_CONTROL_BLOCK {

        DWORD     cbSize;                 // size of this struct.
        DWORD     dwVersion;              // version info of this spec
        HCONN     ConnID;                 // Context number not to be modified!
        DWORD     dwHttpStatusCode;       // HTTP Status code
        CHAR      lpszLogData[HSE_LOG_BUFFER_LEN];// null terminated log info specific to this Extension DLL

        LPSTR     lpszMethod;             // REQUEST_METHOD
        LPSTR     lpszQueryString;        // QUERY_STRING
        LPSTR     lpszPathInfo;           // PATH_INFO
        LPSTR     lpszPathTranslated;     // PATH_TRANSLATED

        DWORD     cbTotalBytes;           // Total bytes indicated from client
        DWORD     cbAvailable;            // Available number of bytes
        LPBYTE    lpbData;                // pointer to cbAvailable bytes

        LPSTR     lpszContentType;        // Content type of client data

        BOOL(WINAPI* GetServerVariable) (HCONN       hConn,
            LPSTR       lpszVariableName,
            LPVOID      lpvBuffer,
            LPDWORD     lpdwSize);

        BOOL(WINAPI* WriteClient)  (HCONN      ConnID,
            LPVOID     Buffer,
            LPDWORD    lpdwBytes,
            DWORD      dwReserved);

        BOOL(WINAPI* ReadClient)  (HCONN      ConnID,
            LPVOID     lpvBuffer,
            LPDWORD    lpdwSize);

        BOOL(WINAPI* ServerSupportFunction)(HCONN      hConn,
            DWORD      dwHSERequest,
            LPVOID     lpvBuffer,
            LPDWORD    lpdwSize,
            LPDWORD    lpdwDataType);

    } EXTENSION_CONTROL_BLOCK, * LPEXTENSION_CONTROL_BLOCK;

    DGLU_API DWORD WINAPI HttpExtensionProc(EXTENSION_CONTROL_BLOCK* lpECB);

    DGLU_API BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO* pVer);

    DGLU_API BOOL WINAPI TerminateExtension(DWORD dwFlags);

#define DG_IMPORT_LINK_SIZE (6)
#define DG_IMPORT_LINK_IMPORT_OFFSET (2)
#define DG_IMPORT_LINK_DATA_SIZE (4)

#define DG_MUTEX_MEM_SIZE (8)

#define dg_paramusingframeoffset        (0x6)   // in UINT64s   // savedrbp retaddress 4 shadow params
#define dg_defaultnoframerstackdepth    (0x5)   // in UINT64s  retaddress and 4 shadow params
    
#endif

    // ////////////////////////
    // End of Windows stuff  //
    // ////////////////////////


    // //////////////////////////////
    // FreeBSD Linux MacOsX stuff  //
    // //////////////////////////////
    
#ifdef DGLU_OS_FREEBSD

#define DG_DIAPERGLU_LIB_NAME "libdiaperglu.dylib"

#define DG_DIAPERGLU_LIB_NAME_LENGTH (18)

#define DG_PATH_SLASH_SYMBOL ((unsigned char)'/')
    
#define DGLU_API 

#define dg_param1reg dg_rdi
#define dg_param2reg dg_rsi
#define dg_param3reg dg_rdx
#define dg_param4reg dg_rcx
    
#if !defined(NULL)
#define NULL (0)
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
/*
    DGLU_API void dg_catchbadmemoryerror (
        int signum,
        siginfo_t* pinfo,
        void* pcontext);
*/
    DGLU_API void dg_trycatchbadmemoryerror ();
    
    DGLU_API void dg_endtrycatchbadmemoryerror ();
/*
    DGLU_API void dg_catchbadmemoryerror2 (
        int signum,
        siginfo_t* pinfo,
        void* pcontext);
*/
    DGLU_API void dg_trycatchbadmemoryerror2 ();

    DGLU_API const char* dg_catchbadmemoryexit2 ();
    DGLU_API const char* dg_catchbadmemoryexitputbyte ();
    DGLU_API const char* dg_catchbadmemoryexitmovebytes ();

    DGLU_API const char* dg_catchbadmemoryexit();
    
    DGLU_API UINT64 dg_syscall(
        UINT64 functionid, // rax
        UINT64 n1,         // rdi
        UINT64 n2,         // rsi
        UINT64 n3,         // rdx
        UINT64 n4,         // rcx
        UINT64 n5);        // r8
    
    DGLU_API UINT64 dg_fstat(
        UINT64 fileid,
        UINT64 pstat);

    DGLU_API UINT64 dg_write(
        UINT64 fileid,
        UINT64 pbuf,
        UINT64 length);
    
    extern char **environ;
    
    DGLU_API void dg_putbyteerroraddress();
    DGLU_API void dg_movebyteserroraddress();
 
#include <pthread.h>    

#define DG_IMPORT_LINK_SIZE (6)
#define DG_IMPORT_LINK_IMPORT_OFFSET (2)
#define DG_IMPORT_LINK_DATA_SIZE (4)

#define DG_MUTEX_MEM_SIZE (sizeof(pthread_mutex_t))

#define dg_paramusingframeoffset        (0x2)   // in UINT64s  savedrbp retaddress
#define dg_defaultnoframerstackdepth    (0x1)   // in UINT64s  retaddress
    
#endif
    
    // /////////////////////////////////////
    // End of FreeBSD Linux MacOsX stuff  //
    // /////////////////////////////////////

// #define dg_localusingframestartoffset        (0xFFFFFFFFFFFFFFC0)  // in bytes  offset of no locals

#define DG_MUTEX_HOLDER_MAGIC 0x6878746D

    struct DG_Mutex_Holder
    {
        UINT64 magic; // 'mtxh'
        UINT64 mutexhandle;
        UINT64 ismutexlockedflag;
        unsigned char mutexmem[DG_MUTEX_MEM_SIZE]; // not really used on windows... except for testing... 
        UINT64 aftermutexmem;  // for testing... to see if memory after mutexmem gets corrupted by os call
    };

    

    
#define badbufferhandle ((void*)0xFFFFFFFFFFFFFFFF)
#define badlibraryhandle ((UINT64)0xFFFFFFFFFFFFFFFF)
#define baderrorcount ((UINT64)0xFFFFFFFFFFFFFFFF)
    
#define badfilehandle ((UINT64)0xFFFFFFFFFFFFFFFF)
#define isapistdinfilehandle ((UINT32)-3)
#define isapistdoutfilehandle ((UINT32)-5)
#define isapistderrfilehandle ((UINT32)-7)
#define dg_stdinbadfilehandle ((UINT64)0xFFFFFFFFFFFFFFF7) // was -9

    // ////////////////////////////
    // presorted wordlist sizes  //
    // ////////////////////////////

#define dg_presortedcorewordlistsize (297)
#define dg_presortedenvwordlistsize (21)
// #define dg_presortedstringwordlistsize (0)
// #define dg_presortederrorwordlistsize (0)
#define dg_prestoredbufferwordlistsize (643)
// #define dg_presortedoswordlistsize (0)
#define dg_presortedx86wordlistsize (1250)

    // gcc inline assembly doesn't take 'FORTH_TRUE', so 0xFFFFFFFF was hardcoded in some places
    //  gcc inline assembly was buggy so stopped using it a long time ago JN 7/16/2013
    enum dg_constants
    {
        FORTH_FALSE      = 0,
        FORTH_TRUE       = 0xFFFFFFFFFFFFFFFF,
        DG_ENDOFWORDLIST = 0xFFFFFFFFFFFFFFFF,
        DG_ENDOFLIST     = 0xFFFFFFFFFFFFFFFF
    };

#define largestunsignedint (0xFFFFFFFFFFFFFFFF)
#define largestsignedint   (0x7FFFFFFFFFFFFFFF)


#define maxwordlength      (255)  // dg_forth standard specifies max counted string length is one character cell which is a byte
#define dg_maxholdbufferlength (200)
#define dg_maxpadbufferlength (4096) 
#define dg_addressunitbits    (64)
#define hascoreset         (FORTH_TRUE)
#define hascoreextset      (FORTH_FALSE)
#define flooreddefault     (FORTH_FALSE)
#define maxcharvalue       (255)

#define dg_maxprecision (64)     // probably should be a multiple of 8
#define dg_initialprecision (20)

#define dg_f64infinity          (0x7FF0000000000000)
#define dg_f64negativeinfinity  (0xFFF0000000000000)
#define dg_f64denormal          (0x0000000000000001)
#define dg_f64negativedenormal  (0x8000000000000001)
#define dg_f64NaN               (0x7FFFFFFFFFFFFFFF)
#define dg_f64negativeNaN       (0xFFFFFFFFFFFFFFFF)
#define dg_f64pi                (0x400921FB54442D18)
#define dg_f64e                 (0x4005BF0A8B145769)
#define dg_f64maxfloat          (0x7FEFFFFFFFFFFFFF)


#define largestnegativeint (0x8000000000000000)
    
#define largestsigneddinthi   (0x7FFFFFFFFFFFFFFF)
#define largestsigneddintlo   (0xFFFFFFFFFFFFFFFF)
#define largestunsigneddinthi (0xFFFFFFFFFFFFFFFF)
#define largestunsigneddintlo (0xFFFFFFFFFFFFFFFF)
    
#define maxrstackbufferlength       (10000)    // note the subroutine return stack is separate and handled by operating system
#define maxdatastackbufferlength    (10000)
#define maxf64stackbufferlength     (0x4000)
#define hassearchorderset           (FORTH_TRUE)
#define hassearchorderextset        (FORTH_FALSE)
#define maxsearchorderbufferlength  (1000)
    
#define maxwordbufferlength           (300) // max length of a word is 255
#define maxleavebufferlength          (1000) // gives you up to 250 LEAVEs at one time 


#define jumpbufferlength             (80)
    
#define colonnonamemarker  (0xFFFEFFFFFFFFFFF9)
#define colonsysmarker  (0xFFFEFFFFFFFFFFF8)
#define dg_codesysmarker (0xFFFEFFFFFFFFFFF7)
#define dg_subparamscommamarker (0xFFFEFFFFFFFFFFF6)


#define dg_writebuffersize (0x10000)
    
    
    enum dg_wordlistids
    {
        //DG_CORE_WORDLISTID        = 0,
        //DG_ENVIRONMENT_WORDLISTID = 1,
        //DG_BUFFER_WORDLISTID      = 2,
        //DG_STRING_WORDLISTID      = 3,
        //DG_OS_WORDLISTID          = 4,
        //DG_USER_WORDLISTID        = 5,
        //DG_ERROR_WORDLISTID       = 6,
//        DG_SYSTEM_WORDLISTID      = 0xFFFFFFF5
        DG_MAX_WORDLISTID         = 0xFFFFFFFFFFFFFFF4
    };
    
    enum dg_bufferids
    {
        DG_ERRORSTACK_BUFFERID           = 0,
        DG_DATASTACK_BUFFERID,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        DG_DATASPACE_BUFFERID,
        DG_RSTACK_BUFFERID,
        DG_SEARCHORDERSTACK_BUFFERID,
        DG_TERMINALINPUT_BUFFERID,
        DG_HOLD_BUFFERID,
        DG_WORD_BUFFERID,
        DG_LEAVESTACK_BUFFERID,
        DG_ARGS_BUFFERID,
        DG_CLEANUP_BUFFERID,
        DG_LIBHANDLE_BUFFERID,
        DG_POST_BUFFERID,
        DG_SCRIPTFILENAME_BUFFERID,
        DG_LOCALPATH_BUFFERID,
        DG_WORDNAME_BUFFERID,
        DG_EXTENDABLECODESPACE_BUFFERID,
        DG_EXTENDABLEDATASPACE_BUFFERID,
        DG_CATCHCODE_BUFFERID,
        DG_HLISTHEADERARRAY_BUFFERID,
        DG_LOCALS_DATASTACK_BUFFERID,
        DG_LOCALS_STRINGOFFSETSTACK_BUFFERID,
        DG_LOCALS_STRINGSTRINGSTACK_BUFFERID,
        DG_VARIABLEFLSTR_OFFSET_BUFFERID,
        DG_VARIABLEFLSTR_STRING_BUFFERID,
        DG_VARIABLEFLSTR_HEADER_BUFFERID,
        DG_LOCALS_STACKDEPTH_BUFFERID,
        DG_LOCALS_LSTRINGSTACKDEPTH_BUFFERID,
        DG_PAD_BUFFERID,
        DG_SCRIPTNAME_BUFFERID,
        DG_QUERYSTRING_BUFFERID,
        DG_SERVERNAME_BUFFERID,
        DG_SERVERSOFTWARE_BUFFERID,
        DG_LINKNEWBUFFERIDSTACK_BUFFERID,
        DG_EHSTACK_BUFFERID,
        DG_F64STACK_BUFFERID,
        DG_CURRENTNEWWORDWORDLISTSTACK_BUFFERID,
        DG_CURRENTCOMPILEBUFFERSTACK_BUFFERID,
        DG_CURRENTVARIABLEBUFFERSTACK_BUFFERID,
        DG_ERRORLINE_BUFFERID,
        DG_WORDVALUE_FAKE_BUFFERID = 0xFFFFFFFFFFFFFFFB,
        DG_WORDNAME_FAKE_BUFFERID  = 0xFFFFFFFFFFFFFFFD,
        DG_CORE_BUFFERID           = 0xFFFFFFFFFFFFFFFE
    };

// used in dg_forthfreebuffer, buffer ids less than this are protected from being freed
#define dg_lastdiaperglubufferid     (DG_CURRENTVARIABLEBUFFERSTACK_BUFFERID)  
    
    // use BHarraymaxindex for an invalid bufferid
    

    enum dg_hlistids
    {
        DG_WORDLISTS_HLISTID           = 0,
        DG_VARIABLESTRINGS_HLISTID,
        DG_NAMEDBUFFERS_HLISTID,
        DG_NAMEDSYMBOLLISTS_HLISTID,
        DG_NAMEDSHAREDLIBS_HLISTID,
        DG_NAMEDHLISTS_HLISTID
    };
    
#define DG_ROOT_ELEMENTID       (0)
#define DG_IMPORTS_ELEMENTID    (1)

    DGLU_API extern const char* dg_rootelementname;
#define DG_ROOTELEMENTNAMELENGTH        (4)

    DGLU_API extern const char* dg_symbollistelementname;
#define DG_SYMBOLLISTELEMENTNAMELENGTH  (10)

    DGLU_API extern const char* dg_importselementname;
#define DG_IMPORTSELEMENTNAMELENGTH     (7)


    enum dg_parametertypes
    {
        DG_PARAMP = 0, // this is also N U8 U16 U32 U64 BOOL
        DG_PARAMF,     // this is also F F32 F64
        DG_PARAMO,
        DG_PARAMRETURN,   // return value
        DG_PARAMFRETURN,  
        DG_PARAMBRACKETO,
        DG_PARAMBRACKETP,
        DG_PARAMBRACKETL,
        DG_PARAMBRACKETU8,
        DG_PARAMBRACKETU16,
        DG_PARAMBRACKETU32,
        DG_PARAMBRACKETU64, // this is also [N] and [P]
        DG_PARAMBRACKETU128,
        DG_PARAMBRACKETS8,
        DG_PARAMBRACKETS16,
        DG_PARAMBRACKETS32,
        DG_PARAMBRACKETS64,
        DG_PARAMBRACKETS128,
        DG_PARAMBRACKETF32,
        DG_PARAMBRACKETF64,
        DG_PARAMBRACKETF128,
        DG_PARAMCALLADDRESS
    };
    

    // General error and success messages
    DGLU_API extern const char dg_success[];
    DGLU_API extern const char dg_badmemoryerror[];
    DGLU_API extern const char dg_badmemoryerrorputbyte[];
    DGLU_API extern const char dg_badmemoryerrorputuint16[];
    DGLU_API extern const char dg_badmemoryerrorputuint32[];
    DGLU_API extern const char dg_badmemoryerrorputuint64[];
    DGLU_API extern const char dg_badmemoryerrorgetbyte[];
    DGLU_API extern const char dg_badmemoryerror2getbyte[];
    DGLU_API extern const char dg_badmemoryerrorgetuint16[];
    DGLU_API extern const char dg_badmemoryerror2getuint16[];
    DGLU_API extern const char dg_badmemoryerrorgetuint32[];
    DGLU_API extern const char dg_badmemoryerror2getuint32[];
    DGLU_API extern const char dg_badmemoryerrorgetuint64[];
    DGLU_API extern const char dg_badmemoryerror2getuint64[];
    DGLU_API extern const char dg_badmemoryerrormovebytes[];
    DGLU_API extern const char dg_badmemoryerrormovebytesforward[];
    DGLU_API extern const char dg_badmemoryerrormovebytesreverse[];
    DGLU_API extern const char dg_badmemoryerrorscanforbyte[];
    DGLU_API extern const char dg_badmemoryerror2scanforbyte[];
    DGLU_API extern const char dg_badmemoryerrorscanfornotbytereverse[];
    DGLU_API extern const char dg_badmemoryerror2scanfornotbytereverse[];
    DGLU_API extern const char dg_badmemoryerrorscanforuint32[];
    DGLU_API extern const char dg_badmemoryerror2scanforuint32[];
    DGLU_API extern const char dg_badmemoryerrorscanforuint64[];
    DGLU_API extern const char dg_badmemoryerror2scanforuint64[];
    DGLU_API extern const char dg_badmemoryerrorcomparebytes[];
    DGLU_API extern const char dg_badmemoryerror1search[];
    DGLU_API extern const char dg_badmemoryerror2search[];
    DGLU_API extern const char dg_badmemoryerror3search[];
    DGLU_API extern const char dg_badmemoryerror4search[];
    DGLU_API extern const char dg_badmemoryerrorcomparebytes[];
    DGLU_API extern const char dg_badmemoryerror2comparebytes[];
    DGLU_API extern const char dg_badmemoryerrorfillwithbyte[];
    DGLU_API extern const char dg_badmemoryerrorreadallbytes[];
    DGLU_API extern const char dg_oserror[];
    DGLU_API extern const char dg_sizenotxpagesizeerror[];
    DGLU_API extern const char dg_outofmemoryerror[];
    DGLU_API extern const char dg_invalidhandleerror[];
    DGLU_API extern const char dg_invalidfunctionerror[];
    
    DGLU_API extern const char dg_accessdeniederror[];
    DGLU_API extern const char dg_filenotfounderror[];
    DGLU_API extern const char dg_pathnotfounderror[];
    DGLU_API extern const char dg_toomanyopenfileserror[];
    DGLU_API extern const char dg_writeprotectederror[];
    
    DGLU_API extern const char dg_invalidparametererror[];
    DGLU_API extern const char dg_toomanyparameterserror[];
    

    DGLU_API extern const char dg_noerrors[];
    DGLU_API extern const char dg_errorbufnotinbharray[];
    DGLU_API extern const char dg_errorbufisfree[];
    DGLU_API extern const char dg_errorbufgrowbynesizenemaxsize[];
    DGLU_API extern const char dg_errorbufnubcorrupt[];
    DGLU_API extern const char dg_errorunderflow[];
    DGLU_API extern const char dg_erroroverflow[];
    DGLU_API extern const char dg_errornotthatmanyerrors[];
    
    DGLU_API extern const char dg_errorsbufidis0[];
    DGLU_API extern const char dg_errorsbufidnotinbharray[];
    DGLU_API extern const char dg_errorsbufidisfree[];
    DGLU_API extern const char dg_errorsbufidnubcorrupt[];
    DGLU_API extern const char dg_errorsbufidsizecorrupt[];
    DGLU_API extern const char dg_errorsoffsetpastend[];
    
    DGLU_API extern const char dg_incrementingerrorcount[];
    DGLU_API extern const char dg_errorinsubroutine[];
    DGLU_API extern const char dg_osexception[];
    

//    DGLU_API extern const char* dg_illegalopcodeerror;
    
    DGLU_API extern const char dg_noerroryet[];
    
    DGLU_API extern const char dg_badmagicerror[];
    DGLU_API extern const char dg_nullpbharrayheaderror[];
    DGLU_API extern const char dg_bharrayheadbadmemerror[];
    DGLU_API extern const char dg_notbharrayheaderror[];
    DGLU_API extern const char dg_nullpbharrayerror[];
    DGLU_API extern const char dg_bharraybadmemerror[];
    
    DGLU_API extern const char dg_BHarraygrowby0error[];
    DGLU_API extern const char dg_BHarraymaxsizeltgrowby[];
    DGLU_API extern const char dg_BHarraymaxsizeltbhsize[];
    DGLU_API extern const char dg_BHarraynubcorrupt[];
    DGLU_API extern const char dg_BHarraynubgtsize[];
    DGLU_API extern const char dg_BHarrayfull[];
    
    DGLU_API extern const char dg_buffernubcorrupt[];
    DGLU_API extern const char dg_bufferidnotinbharray[];
    DGLU_API extern const char dg_bufferidisfree[];
    DGLU_API extern const char dg_bufferidisnotfree[];
    DGLU_API extern const char dg_bufferunderflow[];
    DGLU_API extern const char dg_buffergrowbycorrupt[];
    DGLU_API extern const char dg_buffersizecorrupt[];
    DGLU_API extern const char dg_buffermaxsizecorrupt[];
    DGLU_API extern const char dg_buffermaxsizeltsize[];
    DGLU_API extern const char dg_maxsizeltgrowbyerror[];
    DGLU_API extern const char dg_bufferidisforerrorstack[];
    DGLU_API extern const char dg_bufferidisfordglubuffer[];
    
    DGLU_API extern const char dg_buffergrowby0error[];
    DGLU_API extern const char dg_bufferfullerror[];
    
    DGLU_API extern const char dg_nullpointererror[];
    DGLU_API extern const char dg_offsetpastenderror[];
    DGLU_API extern const char dg_segmentgoespastenderror[];
    

    DGLU_API extern const char dg_missingexporttableerror[];
    DGLU_API extern const char dg_exporttablebounderror[];
 
    DGLU_API extern const char dg_indexnotinarrayerror[];
    DGLU_API extern const char dg_lstringidtoohigherror[];
    DGLU_API extern const char dg_lstringsoffsetscorrupt[];
    DGLU_API extern const char dg_lstringtopoffsetwasbad[];
    DGLU_API extern const char dg_lstringstackdepthcorrupt[];
    DGLU_API extern const char dg_toobigfordesterror[];
    
    DGLU_API extern const char dg_wordidtoobigerror[];
    DGLU_API extern const char dg_wordlistidtoobigerror[];
    DGLU_API extern const char dg_wordalreadylinkederror[];
    DGLU_API extern const char dg_newwordoldererror[];
    DGLU_API extern const char dg_wordnotfoundinsearchordererror[];
    
    DGLU_API extern const char dg_colonsysmissingerror[];
    
    DGLU_API extern const char dg_lstringoffsetpastenderror[];
    DGLU_API extern const char dg_lstringsegmentgoespastenderror[];
    
    DGLU_API extern const char dg_drivenotfounderror[];
    DGLU_API extern const char dg_devicenotfounderror[];
    DGLU_API extern const char dg_devicenotreadyerror[];
    DGLU_API extern const char dg_filesystemunknownerror[];
    DGLU_API extern const char dg_devicebrokenerror[];
    DGLU_API extern const char dg_fileinuseerror[];
    DGLU_API extern const char dg_fileislockederror[];
    DGLU_API extern const char dg_filesystemcorrupterror[];
    DGLU_API extern const char dg_filetoobigerror[];
    DGLU_API extern const char dg_filetypeunknownerror[];
    DGLU_API extern const char dg_osdidlessthanavailableerror[];
    DGLU_API extern const char dg_notexecutablefileerror[];
    DGLU_API extern const char dg_parametersovermaxsizeerror[];
    DGLU_API extern const char dg_ioerror[];
    DGLU_API extern const char dg_toomanysymboliclinkserror[];
    DGLU_API extern const char dg_pathorfilenametoolongerror[];
    DGLU_API extern const char dg_partofpathnotdirectoryerror[];
    DGLU_API extern const char dg_fileopenforwriteerror[];
    DGLU_API extern const char dg_badprocessiderror[];
    DGLU_API extern const char dg_interruptedbysignalerror[];
    DGLU_API extern const char dg_toomanyprocesseserror[];
    DGLU_API extern const char dg_couldnotrunfileerror[];
    DGLU_API extern const char dg_programexitedwitherrorerror[];

    DGLU_API extern const char dg_freemutexwhilelockederror[];
    DGLU_API extern const char dg_woulddeadlockerror[];
    DGLU_API extern const char dg_mutexisnotlockederror[];
    
    DGLU_API extern const char dg_diskisfullerror[];
    DGLU_API extern const char dg_invaliduserbuffererror[];
    DGLU_API extern const char dg_unknownwriteerror[];
    DGLU_API extern const char dg_couldnotgetpagelockerror[];
    
    DGLU_API extern const char dg_crcerror[];
    DGLU_API extern const char dg_invalidhandleerror[];
    
    DGLU_API extern const char dg_outsideofbuffererror[];
    
    DGLU_API extern const char dg_inputbufferlengthchangederror[];
    DGLU_API extern const char dg_evaluatebufferwordnotfounderror[];
    
    DGLU_API extern const char dg_datastackmisalignederror[];
    DGLU_API extern const char dg_datastackunderflowerror[];
    DGLU_API extern const char dg_stringstackunderflowerror[];
    DGLU_API extern const char dg_lstringstackunderflowerror[];
    DGLU_API extern const char dg_rstackunderflowerror[];
    DGLU_API extern const char dg_underflowerror[];
    DGLU_API extern const char dg_lstringemptyerror[];
    DGLU_API extern const char dg_stringunderflowerror[];
    DGLU_API extern const char dg_datastacknoraddrmissingerror[];
    DGLU_API extern const char dg_procparamsmissingerror[];
    DGLU_API extern const char dg_dfpprocparamsmissingerror[];
    DGLU_API extern const char dg_missingobjecthandleerror[];
    DGLU_API extern const char dg_arraymisalignederror[];
    DGLU_API extern const char dg_alreadyfreeerror[];
    DGLU_API extern const char dg_wasnottrulyfreeerror[];
    DGLU_API extern const char dg_structuretoosmallerror[];
    
    DGLU_API extern const char dg_emptystringerror[];
    DGLU_API extern const char dg_wordlength0error[];
    DGLU_API extern const char dg_maxwordlengthexceedederror[];
    
    DGLU_API extern const char dg_nowordfounderror[];
    DGLU_API extern const char dg_signedlengthlessthan0error[];
    
    DGLU_API extern const char dg_basetoolowerror[];
    DGLU_API extern const char dg_basetoohigherror[];
    
    DGLU_API extern const char dg_datastackunbalancederror[];
    
    DGLU_API extern const char dg_hlistpreviousparentbad[];
    DGLU_API extern const char dg_hlistnextparentbad[];
    DGLU_API extern const char dg_hlistpreviousnextbad[];
    DGLU_API extern const char dg_hlistnextpreviousbad[];
    DGLU_API extern const char dg_hlistparentlastchildbad[];
    DGLU_API extern const char dg_hlistelementwasfreed[];
    DGLU_API extern const char dg_elementisfreeerror[];
    // DGLU_API extern const char dg_wordnotfounderror[];
    DGLU_API extern const char dg_namenotfounderror[];
    DGLU_API extern const char dg_symbolnotfounderror[];
    DGLU_API extern const char dg_patchfunctionnotfounderror[];
    
    DGLU_API extern const char dg_tryingtofreehlist0error[];
    
    DGLU_API extern const char dg_glulisttypenotfounderror[];
    
    DGLU_API extern const char dg_queueswitchlengthtoobigerror[];



    // predefined variables in the dataspace buffer
    //                                  (0)  // not used at this time
#define statevariable                (0x08)  // current state, compiling or executing usually
#define exitmainflag                 (0x10)  // set this to true to get out of program
#define currentinterpretbuffer       (0x18)
#define jumpbuffervariable           (0x20)
#define basevariable                 (0x28)
#define currentcompilebuffer         (0x30)
#define currentcompilewordlist       (0x38)
#define currentvariablebuffer        (0x40)
#define quitwasinitializedflag       (0x48)
#define dg_variablestringshlistid    (0x50)
#define dg_hlistheaderbuffer         (0x58)
#define promptsoffflag               (0x60)
#define currentcompileerrorbufferid  (0x68)
#define currentcompileerroroffset    (0x70)
#define showerrorsonexitflag         (0x78)
#define coloncallssafeflag           (0x80)
#define dg_wordlistshlistid          (0x88)
#define dg_latestnewword             (0x90)
#define dg_corewordlistid            (0x98)
#define dg_environmentwordlistid     (0xa0)
#define dg_bufferwordlistid          (0xa8)
#define dg_stringwordlistid          (0xb0)
#define dg_oswordlistid              (0xb8)
#define dg_userwordlistid            (0xc0)
#define dg_errorwordlistid           (0xc8)
#define dg_localswordlistid          (0xd0)
#define dg_colonhaslocalsflag        (0xd8)
#define dg_colonhaslocalstringsflag  (0xe0)
#define dg_numberoflocals            (0xe8)
#define dg_numberoflocalstrings      (0xf0)
#define dg_cpux86vocabid             (0xf8)
#define dg_patchdestnamedbuf         (0x100) // in list of named buffers
#define dg_patchsrcnamedbuf          (0x108) // in list of named buffers
#define dg_patchsrcnamedlib          (0x110) // in list of named libraries
#define dg_patchsrcnamedsymbollist   (0x118) // in list of named symbol lists
#define dg_patchdestnamedsymbollist  (0x120) // in list of named symbol lists
#define dg_callhlisterrorelementid   (0x128)
#define dg_x86asmaddresssize         (0x130) // 4 = 32 bits, 8 = 64 bits
#define dg_precision                 (0x138)
#define dg_numberofcparameters       (0x140)
#define dg_numberofcfparameters      (0x148)
#define dg_whichintparameter         (0x150)
#define dg_whichfloatparameter       (0x158)
#define dg_extraparametersfloatsflag (0x160)
#define dg_noframereturnstackdepth   (0x168) // in UINT64s
#define dg_cparameterregisters       (0x170) // room for 4 parameters...

#define dg_callsubnumberofints       (0x190)
#define dg_callsubnumberoffloats     (0x198)
#define dg_callsubreturnstackdepth   (0x1A0)
#define dg_colonreturnstackdepth     (0x1A8)
#define dg_errorlinenumber           (0x1B0)
#define lastnotfoundword             (0x1B8) // this is 256 characters (bytes) long.. needs to be maxwordlength long which is 255.. I added 1

#define dg_quitsavedstate            (0x2B8) // this is 9*4 = 36 bytes long, rounding up to 0x30  ... looks like it is only 0x18...
 
// put more variables here and increase initialsizeofvariablebuffer
#define initialsizeofvariablebuffer  (0x2E8)

#define dg_cparameterregisterslength    (0x4)   // in number of parameters, Windows needs 4
#define dg_cparameteronstackflag        (0x0100000000000000)
#define dg_cparameteronstacknoframeflag (0x0200000000000000)
#define dg_cparameterpassinbothflag     (0x0300000000000000)
#define dg_cparameteronstackmask        (0xFF00000000000000)


#define dg_dgluframelocaloffset         (0x5)   // in UINT64s - offset from rbp to address of local 0
                                                //   need to add one here because you have to include saved RBP
                                                //   so it's the 4 dglu frame items + saved RBP
// #define dg_laststuffbeforeerrorsize     (0xA0) // has to be less than true size of dg_laststuffbeforeerror

#define dg_quitsavedstatelength     (0x30) // 11/22/2017 - will figure out actual size later  


        //DG_CORE_WORDLISTID        = 0,
        //DG_ENVIRONMENT_WORDLISTID = 1,
        //DG_BUFFER_WORDLISTID      = 2,
        //DG_STRING_WORDLISTID      = 3,
        //DG_OS_WORDLISTID          = 4,
        //DG_USER_WORDLISTID        = 5,
        //DG_ERROR_WORDLISTID       = 6,

    
    
    // force condition flags
    // if the corresponding bit is set in pBHarrayhead->currentoffset,
    //  the effect should happen
    // #define fforceoutofmemory (0x01)
    // #define fforcerelocation  (0x01)
    
    
    // FreeBSD operatingsystem.cpp dg_checkbharray and dg_checkbharrayhead 
    //  uses hard coded constants for Bufferhandle offsets. If this changes, you need
    //  you need to update those functions.
    struct Bufferhandle {
        UINT64 errorcount;       // 0 if this is the handle for the BHarray, then this
                                 //  is the number of errors on the error stack if this
                                 //  error stack isn't corrupt or over overflowed
                                 // ?ERRORIF and save of errorcount at start of definition
                                 //  expect errorcount to be at position 0
        void*  pbuf;             // 8 pointer to memalloc buffer or -1 if free
        UINT64 size;             // 16 in bytes of memalloced buffer
        UINT64 growby;           // 24 in bytes
        UINT64 maxsize;          // 32 in bytes  (do I really need a maxsize?)
        UINT64 nextunusedbyte;   // 40 in bytes of offset of next unused byte in the buffer
        UINT64 nextfreeindex;    // 48 pointer to the next free buffer handle
        UINT64 currentoffset;    // 56 for interpreting and other uses (like the seek pointer for streams)
        void*  pisapiecb;        // 64 to hold windows isapi function pointer
        UINT64 id;               // 72 Bufferhandle Array Head has id of "dglu".
        UINT64 argc;             // 80 argc passed in to main
        char** argv;             // 88 argv passed in to main
        UINT64* pfunctbl;        // 96 pointer to diaperglu function table
        // UINT64 diaperflags;      // 104 if 0 the diaper is on (may add more flags later)
        //    Generic bufferhandle has id of "bufr"
    };

    // these #defines must match the offsets in the bufferhandle structure
    //  for the check bufferhandle subroutines
#define bufferhandleidoffset   (72)
#define bufferhandlepbufoffset (8)
#define bufferhandleppfunctbloffset (96)

// #define errorcountoffset (24)
    
#define BHarraygrowby   (1024   * sizeof(Bufferhandle))
#define BHarraymaxsize  (1048576 * sizeof(Bufferhandle))
#define BHarraymaxindex ((BHarraymaxsize - 1) / sizeof(Bufferhandle))
    
#define BHarrayheadid (0x64676c75)
    
#define errorstackminimumsize (2 * sizeof(const char*))


    struct Definitionheader {
        UINT64 compileroutinebuf;
        UINT64 compileroutineoffset;
        UINT64 databuf;
        UINT64 dataoffset;
    };
    
    struct Premadeword {
        const char *pname;
        UINT64 namelength;
        UINT64 compileroutinebuf;
        UINT64 compileroutineoffset;
        UINT64 databuf;
        UINT64 dataoffset;
    };
    
    struct Freeablelstringarrayheader
    {
        UINT64 magic;                  // 'flst'
        UINT64 lstringoffsetbufferid;
        UINT64 lstringstringbufferid;
        UINT64 firstfreeid;
    };

#define dg_freeablelstringheadermagic (0x74736c66)
#define dg_freeablelstringlastfreeid  (0xFFFFFFFFFFFFFFFF)
#define dg_freeablelstringisnotfreeid (0xFFFFFFFFFFFFFFFD)


    struct Lstringqueueheader
    {
        UINT64 magic;                  // 'lstq'
        UINT64 lstringoffsetbufferida;
        UINT64 lstringstringbufferida;
        UINT64 lstringoffsetbufferidb;
        UINT64 lstringstringbufferidb;      
        UINT64 pusharray;              // current push L$array (0 or 1)
        UINT64 switchlength;
        UINT64 poparray;               // current pop L$array (0 or 1)
        UINT64 popindex;
    };
 
 #define dg_lstringqueuemagic (0x7074736c) 
 #define dg_maxlstringqueueswitchlength (0x7FFFFFFF) 
 // #define dg_lstringqueuemutexhandlemaxsize (0x80) 
 
    struct SharedQueueHandleBufferStructs {
        UINT64 magic; // 'sqhb'
        struct Bufferhandle sharedQueueBHarrayhead;
        struct Lstringqueueheader lsQueueHeader;
        struct DG_Mutex_Holder mutexHolder;
        // UINT64 mutexhandle;
        // unsigned char mutexmem[DG_MUTEX_MEM_SIZE]; // mac os x needs this
    };
     
#define dg_sharedqueuemagic (0x62687473)

    struct DG_AsyncFunctionCallerHeader
    {
        UINT64 magic; // 'afch'
        // UINT64 childgomutexhandle;
        // unsigned char childgomutexmem[DG_MUTEX_MEM_SIZE];
        struct DG_Mutex_Holder childgomutexHolder;
        // UINT64 childstopmutexhandle;
        //unsigned char childstopmutexmem[DG_MUTEX_MEM_SIZE];
        struct DG_Mutex_Holder childstopmutexHolder;
        // UINT64 childgotgomutexhandle;
        // unsigned char childgotgomutexmem[DG_MUTEX_MEM_SIZE];
        struct DG_Mutex_Holder childgotgomutexHolder;
        // UINT64 childgotstopmutexhandle;
        // unsigned char childgotstopmutexmem[DG_MUTEX_MEM_SIZE];
        struct DG_Mutex_Holder childgotstopmutexHolder;
        UINT64 threadhandle;
        void (*pfunction)(Bufferhandle* pBHarrayhead); // function pointer
        Bufferhandle childBHarrayhead; 
    };

#define dg_afchmagic (0x68636661)

// used in testing, represents the number of elements added to the wordlist hlist
//  dg_inithlists in dglumain.cpp
#define dg_defaulthlistelements      (1)

    struct Hlistelementheader
    {
        UINT64 magic;                        // 'hlel'
        UINT64 parentelementid;
        UINT64 lastchildelementid;
        UINT64 nextsiblingelementid;
        UINT64 previoussiblingelementid;
        UINT64 firstchildelementid;
    };
    
    struct Hlistheader
    {
        UINT64 magic;                         // 'hlst'
        UINT64 elementheaderflstrbufid;
        UINT64 namelstroffsetbufid;
        UINT64 namelstrstringbufid;
        UINT64 valuelstroffsetbufid;
        UINT64 valuelstrstringbufid;
        UINT64 sortedchildidslstroffsetbufid;
        UINT64 sortedchildidslstrstringbufid;
    };
    
#define dg_hlistheadermagic  (0x76736c67)
#define dg_hlistelementmagic (0x6c656c67)

    
#define dg_badbufferid                (0xFFFFFFFFFFFFFFFF)

#define dg_defaultbuffergrowby        (0x10000)
#define dg_defaultbuffermaxsize       (largestunsignedint)
#define dg_badlstringid               (0xFFFFFFFFFFFFFFFF)


#define dg_namedbuffertypebuffer      (0)
#define dg_namedbuffertypesharedlib   (1)
#define dg_namedbuffertypefile        (2)
    
    struct HListidElementid
    {
        UINT64 hlistid;
        UINT64 elementid;
    };
/*
#define dg_linkoffset (1)


     struct Linkheader
     {
         // UINT32 magic;                        // 'hlnk'
         UINT64 pLinkbuffer;                     // not using bufferid for speed... which means you have to be careful
         UINT64 descriptionHlistid;
     }
    
     struct Linkarrayelement
     {
        // UINT32 magic;
        UINT64 offset;
        UINT64 bufferid; // could use pbuffer for speed, but then user has to be really careful
        UINT64 type1;
        UINT64 type2;
     }
*/

#define dg_numberofglufunctions (24)

    enum dg_glulistfunctions
    {
        DG_GLUFUNCBUFS              = 0,
        DG_GLUFUNCCALLBUF,
        DG_GLUFUNCCALLBUFTODS,
        DG_GLUFUNCCALLDESTOFFSET,
        DG_GLUFUNCCALLDESTOFFSETTODS,
        DG_GLUFUNCCALLLIB,
        DG_GLUFUNCCALLLIBTODS,
        DG_GLUFUNCDESTBUF,
        DG_GLUFUNCDESTSYMBOLS,
        DG_GLUFUNCFILES,
        DG_GLUFUNCHFILES,
        DG_GLUFUNCHLISTHERE,
        DG_GLUFUNCLIBS,
        DG_GLUFUNCLINKBUF,
        DG_GLUFUNCLINKLIB,
        DG_GLUFUNCLINKNEWBUF,
        DG_GLUFUNCLINKOFFSET,
        DG_GLUFUNCNGLU,
        DG_GLUFUNCSRCBUF,
        DG_GLUFUNCSRCLIB,
        DG_GLUFUNCSRCSYMBOLS,
        DG_GLUFUNCSYMBOLS,
        DG_GLUFUNCUINT64VALUETODS,
        DG_GLUFUNCVALUETOSTRS,
    };
    
    #define DG_NUMBEROFFUNCTIONTABLEIDS (2)

    DGLU_API extern UINT64 dg_functiontable[];
 
    DGLU_API extern unsigned char dg_glufunctionnames[];
    DGLU_API extern UINT64 dg_glufunctionnameoffsets[dg_numberofglufunctions];
    DGLU_API extern UINT64 dg_glufunctiontable[dg_numberofglufunctions];
    DGLU_API extern UINT64 dg_glufunctionsortedkeys[dg_numberofglufunctions];

    DGLU_API extern const char dg_glulistelementname[];
    DGLU_API extern UINT64 dg_glulistelementnamelength;

    DGLU_API extern const char dg_nglulistelementname[];
    DGLU_API extern UINT64 dg_nglulistelementnamelength;
    
    DGLU_API extern const char dg_diaperglulibsymbolname[];
    
    DGLU_API extern const char dg_diaperglulibname[];
    
    DGLU_API extern const char dg_compilesegmentname[];
    DGLU_API extern const char dg_compile0stringname[];

    // Forth Core Extension Names
    DGLU_API extern const char dg_forthfalsename[];
    
    
    // forth show wordlist names
    DGLU_API extern const char dg_forthforthwordsname[];
    DGLU_API extern const char dg_fortherrorwordsname[];
    DGLU_API extern const char dg_forthenvironmentwordsname[];
    DGLU_API extern const char dg_forthbufferwordsname[];
    DGLU_API extern const char dg_forthstringwordsname[];
    DGLU_API extern const char dg_forthlibrarywordsname[];
    DGLU_API extern const char dg_forthuserwordsname[];
    
    // forth operating system words
    DGLU_API extern const char dg_forthgethstdinname[];
    DGLU_API extern const char dg_forthgethstdoutname[];
    DGLU_API extern const char dg_forthgethstderrorname[];
    DGLU_API extern const char dg_forthgetfilelengthname[];
    DGLU_API extern const char dg_forthreadavailabletobuffername[];
    DGLU_API extern const char dg_forthreadwaitforntobuffername[];
    
    // forth search order word names
    DGLU_API extern const char dg_forthdefinitionsname[];
    DGLU_API extern const char dg_forthforthwordlistname[];
    DGLU_API extern const char dg_forthgetcurrentname[];
    DGLU_API extern const char dg_forthgetordername[];
    DGLU_API extern const char dg_forthsearchwordlistname[];
    DGLU_API extern const char dg_forthsetcurrentname[];
    DGLU_API extern const char dg_forthsetordername[];
    DGLU_API extern const char dg_forthwordlistname[];
    
    
    // forth double number word names
    DGLU_API extern const char dg_forthtwoconstantname[];
    DGLU_API extern const char dg_forthtwoliteralname[];
    DGLU_API extern const char dg_forthtworotname[];
    DGLU_API extern const char dg_forthtwovariablename[];
    DGLU_API extern const char dg_forthdlessthanname[];
    DGLU_API extern const char dg_forthdequalsname[];
    DGLU_API extern const char dg_forthdtosname[];   
    DGLU_API extern const char dg_forthdplusname[];
    DGLU_API extern const char dg_forthdminusname[];
    DGLU_API extern const char dg_forthddotname[];
    DGLU_API extern const char dg_forthddotrname[];
    DGLU_API extern const char dg_forthdzerolessname[];
    DGLU_API extern const char dg_forthdzeroequalsname[];
    DGLU_API extern const char dg_forthdtwostarname[];
    DGLU_API extern const char dg_forthdtwoslashname[];
    DGLU_API extern const char dg_forthdabsname[];
    DGLU_API extern const char dg_forthdmaxname[];
    DGLU_API extern const char dg_forthdminname[];
    DGLU_API extern const char dg_forthdnegatename[];
    DGLU_API extern const char dg_forthdulessthanname[];
    DGLU_API extern const char dg_forthmplusname[];
    DGLU_API extern const char dg_forthmstarslashname[];
    
    // forth floating point word names
    DGLU_API extern const char dg_forthtofloatname[]; 
    DGLU_API extern const char dg_forthdtofname[];
    DGLU_API extern const char dg_forthfliteralname[]; 
    DGLU_API extern const char dg_forthfstorename[]; 
    DGLU_API extern const char dg_forthfstarname[];
    DGLU_API extern const char dg_forthfstarstarname[];
    DGLU_API extern const char dg_forthfplusname[];
    DGLU_API extern const char dg_forthfminusname[];
    DGLU_API extern const char dg_forthfdotname[];
    DGLU_API extern const char dg_forthfslashname[];
    DGLU_API extern const char dg_forthfzerolessthanname[];
    DGLU_API extern const char dg_forthfzeroequalsname[];
    DGLU_API extern const char dg_forthflessthanname[];
    DGLU_API extern const char dg_forthffetchname[];
    DGLU_API extern const char dg_forthftosname[];
    DGLU_API extern const char dg_forthfabsname[];
    DGLU_API extern const char dg_forthfalignname[];
    DGLU_API extern const char dg_forthfalignedname[];
    DGLU_API extern const char dg_forthfalogname[];
    DGLU_API extern const char dg_forthfacosname[];
    DGLU_API extern const char dg_forthfacoshname[];
    DGLU_API extern const char dg_forthfasinname[];
    DGLU_API extern const char dg_forthfasinhname[];
    DGLU_API extern const char dg_forthfatanname[];
    DGLU_API extern const char dg_forthfatan2name[];
    DGLU_API extern const char dg_forthfatanhname[];
    DGLU_API extern const char dg_forthfconstantname[];
    DGLU_API extern const char dg_forthfcosname[];
    DGLU_API extern const char dg_forthfcoshname[];
    DGLU_API extern const char dg_forthfdepthname[];
    DGLU_API extern const char dg_forthfdropname[];
    DGLU_API extern const char dg_forthfdupname[];
    DGLU_API extern const char dg_forthfedotname[];
    DGLU_API extern const char dg_forthfexpname[];
    DGLU_API extern const char dg_forthfexpm1name[];
    DGLU_API extern const char dg_forthflnname[];
    DGLU_API extern const char dg_forthflnp1name[];
    DGLU_API extern const char dg_forthflogname[];
    DGLU_API extern const char dg_forthfloatsname[];
    DGLU_API extern const char dg_forthfloatplusname[];
    DGLU_API extern const char dg_forthfloorname[];
    DGLU_API extern const char dg_forthfmaxname[];
    DGLU_API extern const char dg_forthfminname[];
    DGLU_API extern const char dg_forthfnegatename[];
    DGLU_API extern const char dg_forthfovername[];
    DGLU_API extern const char dg_forthfproximatename[];
    DGLU_API extern const char dg_forthfrotname[];
    DGLU_API extern const char dg_forthfroundname[];
    DGLU_API extern const char dg_forthfsdotname[];
    DGLU_API extern const char dg_forthfsincosname[];
    DGLU_API extern const char dg_forthfsinname[];
    DGLU_API extern const char dg_forthfsinhname[];
    DGLU_API extern const char dg_forthfsqrtname[];
    DGLU_API extern const char dg_forthfswapname[];
    DGLU_API extern const char dg_forthftanname[];
    DGLU_API extern const char dg_forthftanhname[];
    DGLU_API extern const char dg_forthfvariablename[];
    DGLU_API extern const char dg_forthfvariablesname[];
    DGLU_API extern const char dg_forthprecisionname[];
    DGLU_API extern const char dg_forthrepresentname[];
    DGLU_API extern const char dg_forthstofname[];
    DGLU_API extern const char dg_forthsetprecisionname[];
    DGLU_API extern const char dg_forthsfstorename[];
    DGLU_API extern const char dg_forthsffetchname[];
    DGLU_API extern const char dg_forthsfalignname[];
    DGLU_API extern const char dg_forthsfalignedname[];
    DGLU_API extern const char dg_forthsfloatplusname[];
    DGLU_API extern const char dg_forthsfloatsname[];
    
    // Forth String word names
    DGLU_API extern const char dg_forthdashtrailingname[];
    DGLU_API extern const char dg_forthblankname[];
    
    // Forth Programming Tools names
    DGLU_API extern const char dg_forthquestionname[];
    DGLU_API extern const char dg_forthdotsname[];
    DGLU_API extern const char dg_forthdumpname[];
    DGLU_API extern const char dg_forthwordsname[];
    
    DGLU_API extern const char dg_forthbyename[];
    DGLU_API extern const char dg_forthsynonymname[];
    DGLU_API extern const char* dg_forthcodename;

    
    
    // forth error word names
    DGLU_API extern const char dg_forthpushoerrorname[];
    DGLU_API extern const char dg_forthtoerrorname[];
    DGLU_API extern const char dg_forthtoerrorshortname[];
    DGLU_API extern const char dg_forthpopoerrorname[];
    DGLU_API extern const char dg_fortherrorfromname[];
    DGLU_API extern const char dg_fortherrorfromshortname[];
    DGLU_API extern const char dg_forthgetoerrorname[];
    DGLU_API extern const char dg_forthgeterrorcountname[];
    DGLU_API extern const char dg_forthcheckerrordepthname[];
    DGLU_API extern const char dg_forthdroptoerrorcountname[];
    DGLU_API extern const char dg_forthdoterrorsname[];
    DGLU_API extern const char dg_clearerrorsname[];
    DGLU_API extern const char dg_forthdoterrorsshortname[];
    DGLU_API extern const char dg_forthshowerrorsname[];
    DGLU_API extern const char dg_clearerrorsshortname[];
    DGLU_API extern const char dg_forthcplgetolderrorcountname[];
    
    
    // forth get compile type routine offset bufferid word names
    DGLU_API extern const char dg_forthodoctalwaysexecutename[];
    DGLU_API extern const char dg_forthodoctsubroutinename[];
    DGLU_API extern const char dg_forthodoctpreserveregsname[];
    DGLU_API extern const char dg_forthodoctsafesubroutinename[];
    DGLU_API extern const char dg_forthodocompiletypedpushnname[];
    DGLU_API extern const char dg_forthodocompiletypedpushfname[];   
    DGLU_API extern const char dg_forthodoctdpushdnname[];
    DGLU_API extern const char dg_forthodocompiletypedpushpname[];
    DGLU_API extern const char dg_forthodocompiletypedpushsname[];
    DGLU_API extern const char dg_forthodocompiletypewordsstringquotesname[];
    DGLU_API extern const char dg_forthodocompiletypewords0stringquotesname[];
    DGLU_API extern const char dg_forthodocompiletyperunfileandwaitnoenvquotesname[];
    DGLU_API extern const char dg_forthodocompiletypecdeclname[];
    DGLU_API extern const char dg_forthodocpltypedfpcdeclname[];
    DGLU_API extern const char dg_forthodoctcdeclretuint128name[];
    DGLU_API extern const char dg_forthodoctcppmembername[];
    DGLU_API extern const char dg_forthodocompiletypecallname[];
    DGLU_API extern const char dg_forthdocompiletypeftcolonname[];
    DGLU_API extern const char dg_forthdocompiletypedpushbracketrbpplusnname[];
    DGLU_API extern const char dg_forthdocompiletypebrackettoordername[];
    DGLU_API extern const char dg_forthdocompiletypebracketwordlistdotname[];
    DGLU_API extern const char dg_forthdocompiletypebracketlibdotname[];
    DGLU_API extern const char dg_forthdocompiletypecompilepushlocalname[];
    DGLU_API extern const char dg_forthodocompiletypevaluename[];
    DGLU_API extern const char dg_forthodocompiletypetwovaluename[];
    DGLU_API extern const char dg_forthodocompiletypefvaluename[];
    DGLU_API extern const char dg_forthodocompiletypeostorename[];
    DGLU_API extern const char dg_forthodocompiletypeof64storename[];
    DGLU_API extern const char dg_forthodocompiletypeotwostorename[];
    
    
    // forth compiling word names
    DGLU_API extern const char dg_forthcompileentercolonname[];
    DGLU_API extern const char dg_forthcompileentername[];
    DGLU_API extern const char dg_forthcompileentersubname[];
    DGLU_API extern const char dg_forthcompileexitname[];
    DGLU_API extern const char dg_forthcompilesname[];
    DGLU_API extern const char dg_forthcompilebranchname[];
    DGLU_API extern const char dg_forthresolvecompiledbranchname[];
    DGLU_API extern const char dg_forthdopromptname[];
    DGLU_API extern const char dg_forthqueryerrorifname[];
    DGLU_API extern const char dg_forthsliteralname[];
    DGLU_API extern const char dg_forthcompilecallcorename[];
    DGLU_API extern const char dg_forthcompilecallsamebuffername[];
    DGLU_API extern const char dg_forthcompilecallbuffername[];
    DGLU_API extern const char dg_forthcompilesafecallbuffername[];
    
    
    // forth definition word names
    DGLU_API extern const char dg_forthsafename[];
    DGLU_API extern const char dg_forthiscolonname[];
    DGLU_API extern const char dg_forthisotoname[];
    DGLU_API extern const char dg_forthisobtoname[];
    DGLU_API extern const char dg_forthisptoname[];
    DGLU_API extern const char dg_forthiscompilecallname[] ;
    DGLU_API extern const char dg_forthiscallprocname[];
    DGLU_API extern const char dg_forthiscallprocretuint64name[];
    DGLU_API extern const char dg_forthstringtonewprocwordname[];
    DGLU_API extern const char dg_forthstringtonewobwordname[];

    DGLU_API extern const char dg_forthcreateocname[];
    DGLU_API extern const char dg_forthcreateovname[];
    
    DGLU_API extern const char dg_forthtoonamename[];
    DGLU_API extern const char dg_forthlatestname[];
    DGLU_API extern const char dg_forthbracketlatestname[];
    DGLU_API extern const char dg_forthbracketcolononamename[];
    DGLU_API extern const char dg_forthbracketolatestnamename[];
    DGLU_API extern const char dg_forthbracketwordnametoerrorname[];
    DGLU_API extern const char dg_forthnametoename[];
    DGLU_API extern const char dg_forthnametoerrorname[];
    
    DGLU_API extern const char dg_forthgetcompileroutinename[];
    DGLU_API extern const char dg_forthsetcompileroutinename[];
    DGLU_API extern const char dg_forthgetodfname[];
    DGLU_API extern const char dg_forthsetodfname[];
    DGLU_API extern const char dg_forthtocurrentname[];
    DGLU_API extern const char dg_forthcurrentfromname[];
    DGLU_API extern const char dg_forthsearchorderdropname[];
    DGLU_API extern const char dg_forthbracketsearchorderdropname[];
    DGLU_API extern const char dg_forthbrackettoorderconstantname[];
    DGLU_API extern const char dg_forthwordlistdotname[];  
    DGLU_API extern const char dg_forthlibdotname[];
    DGLU_API extern const char dg_forthcreatebracketwordlistdotname[];
    DGLU_API extern const char dg_forthcreatebracketlibdotname[]; 
    
    
    // forth miscellaneous word names
    DGLU_API extern const char dg_forthevaluatebuffername[];
    DGLU_API extern const char dg_forthocallname[];
    DGLU_API extern const char dg_forthqueryendevaluatename[];
    DGLU_API extern const char dg_forthosquotesname[];
    DGLU_API extern const char dg_fortho0quotesname[];
    DGLU_API extern const char dg_fortherrorquotesshortname[];
    DGLU_API extern const char dg_fortherrorquotesname[];
    DGLU_API extern const char dg_forthtype0stringname[];
    DGLU_API extern const char dg_forthdotwordnamename[];
    DGLU_API extern const char dg_forthshowwordlistname[];
    DGLU_API extern const char dg_forthshowsortedwordlistname[];
    DGLU_API extern const char dg_forthshowallwordsname[];
    DGLU_API extern const char dg_forthshowlicensename[];
    DGLU_API extern const char dg_forthcrlfname[];
    DGLU_API extern const char dg_forthtoordername[];
    DGLU_API extern const char dg_forthorderfromname[];
    DGLU_API extern const char dg_forthbswapname[];
    DGLU_API extern const char dg_forthodoesname[];
    DGLU_API extern const char dg_forthpagesizename[];
    DGLU_API extern const char dg_forthroundupname[];
    DGLU_API extern const char dg_forthpackdfname[];
    DGLU_API extern const char dg_forthunpackdfname[];
    DGLU_API extern const char dg_forthdfplusname[];
    DGLU_API extern const char dg_forthdfminusname[];
    DGLU_API extern const char dg_forthdfstarname[];
    DGLU_API extern const char dg_forthdfslashname[];
    DGLU_API extern const char dg_showframename[];
    
    DGLU_API extern const char dg_forthhexname[];
    DGLU_API extern const char dg_forthnipname[];
    DGLU_API extern const char dg_forthpadname[];
    DGLU_API extern const char dg_forthrollname[];
    DGLU_API extern const char dg_forthtibname[];
    DGLU_API extern const char dg_forthtuckname[];
    DGLU_API extern const char dg_forthtruename[];
    DGLU_API extern const char dg_forthugreaterthanname[];
    DGLU_API extern const char dg_forthbackslashname[];
    DGLU_API extern const char dg_forthudmslashmodname[];
    DGLU_API extern const char dg_forthendoflistname[];
    DGLU_API extern const char dg_forthendofwordlistname[];
    DGLU_API extern const char dg_forthpickname[];
    DGLU_API extern const char dg_forthminusrotname[];   

    DGLU_API extern const char dg_forthparsename[];
    DGLU_API extern const char dg_forthlinesparsename[];    
    DGLU_API extern const char dg_forthparsebuffername[]; 
    DGLU_API extern const char dg_forthparsenamenom[];
    DGLU_API extern const char dg_forthparsenamesname[];
    DGLU_API extern const char dg_forthparsewordname[];
    DGLU_API extern const char dg_forthparsewordsname[]; 
    DGLU_API extern const char dg_forthlinesparsenamesname[]; 
    DGLU_API extern const char dg_forthparselinename[]; 
    DGLU_API extern const char dg_forthcscanname[];
    DGLU_API extern const char dg_forthcscanbufname[];
    DGLU_API extern const char dg_forthscanname[];
    DGLU_API extern const char dg_forthscanbufname[];
    DGLU_API extern const char dg_forthslashstringname[];   
    DGLU_API extern const char dg_forthsearchname[];
    DGLU_API extern const char dg_forthcomparename[];   
    
    DGLU_API extern const char dg_forthnewdefinitionname[];
    DGLU_API extern const char dg_forthnewwordname[];
    DGLU_API extern const char dg_forthgetpdefinitionname[];
    DGLU_API extern const char dg_forthgetswordheadname[];
    DGLU_API extern const char dg_forthtoheadname[];
    DGLU_API extern const char dg_forthlinkdefinitionname[];
    DGLU_API extern const char dg_forthlinkwordname[];
    DGLU_API extern const char dg_forthnewsubroutinedefinitionname[];
    DGLU_API extern const char dg_forthnewvariabledefinitionname[];
    DGLU_API extern const char dg_forthnewconstantdefinitionname[];
    DGLU_API extern const char dg_forthgetnewestdefinitioninwordlistname[];
    DGLU_API extern const char dg_forthgetnextdefinitionname[];
    DGLU_API extern const char dg_forthfinddefinitioninwordlistname[];
    DGLU_API extern const char dg_forthfinddefinitioninsearchordername[];
    DGLU_API extern const char dg_forthputnewestdefinitioncompiletypename[];
    
    DGLU_API extern const char dg_forthcodescommaname[];
    DGLU_API extern const char dg_forthcodeu8commaname[];
    DGLU_API extern const char dg_forthcodeu16commaname[];
    DGLU_API extern const char dg_forthcodeu32commaname[];
    DGLU_API extern const char dg_forthcodeu64commaname[];
    DGLU_API extern const char dg_forthcodeallotname[];
    
    DGLU_API extern const char dg_forthdoterrorlinename[];
    DGLU_API extern const char dg_forthoherename[];
    
    DGLU_API extern const char dg_forthdglibstringname[];
    
    DGLU_API extern const char dg_forthlobitname[];
    DGLU_API extern const char dg_forthhibitname[];
    DGLU_API extern const char dg_forthcountbitsname[];
    
    DGLU_API extern const char dg_forthmicrosecondssince1970jan01name[];
    
    DGLU_API extern const char dg_forthtouleb128name[];
    DGLU_API extern const char dg_forthhctwostorename[];
    DGLU_API extern const char dg_forthdrshiftname[];
    DGLU_API extern const char dg_forthdlshiftname[];
    DGLU_API extern const char dg_forthdarshiftname[];

    DGLU_API extern const char dg_forthbuftodotobufname[];
    DGLU_API extern const char dg_forthbuftodotofilestringname[];
    
    DGLU_API extern const char dg_forthbuftomachodotobufname[];
    DGLU_API extern const char dg_forthosymbolbuftonewdotobufname[];
    DGLU_API extern const char dg_forthosymbolbuftonewdotofilestringname[];
    
    DGLU_API extern const char dg_forthtestfindnumbername[];
    
    DGLU_API extern const char dg_forthfunctblofnname[];
    
    DGLU_API extern const char dg_forthdiaperoffname[];
    DGLU_API extern const char dg_forthdiaperonname[];
    DGLU_API extern const char dg_forthemptywordlistname[];
    DGLU_API extern const char dg_forthrandomname[];
    DGLU_API extern const char dg_forthcompileu8sname[];
    DGLU_API extern const char dg_forthcompileu8scurlyname[];
    DGLU_API extern const char dg_forthconstantscurlyname[];
    DGLU_API extern const char dg_forthfconstantscurlyname[];
    DGLU_API extern const char dg_forthlocalconstantsname[];
    DGLU_API extern const char dg_forthbracketlocalconstantsname[];
    DGLU_API extern const char dg_forthlocalconstantscurlyname[];
    DGLU_API extern const char dg_forthbracketlocalconstantscurlyname[];
    DGLU_API extern const char dg_forthvariablescurlyname[];
    DGLU_API extern const char dg_forthvariablesname[];
    DGLU_API extern const char dg_forthconstantsname[];
    DGLU_API extern const char dg_forthfconstantsname[];
    DGLU_API extern const char dg_forthsizedconstantscurlyname[];
    DGLU_API extern const char dg_forthenumcurlyname[];
    DGLU_API extern const char dg_forthlocalenumcurlyname[];
    DGLU_API extern const char dg_forthbracketlocalenumcurlyname[];
    DGLU_API extern const char dg_forthtypedenumcurlyname[];
    DGLU_API extern const char dg_forthtypedlocalenumcurlyname[];
    DGLU_API extern const char dg_forthbenchmarkname[];

    
    // floating point words
    DGLU_API extern const char dg_forthsftodfname[];
    DGLU_API extern const char dg_forthdftosfname[];
    
    DGLU_API extern const char dg_forthftodname[];
    DGLU_API extern const char dg_forthdftodname[];
    DGLU_API extern const char dg_forthdtodfname[];

    DGLU_API extern const char dg_forthf64commaname[];
    
    
    // forth buffer word names
    DGLU_API extern const char dg_forthbufferwordlistname[];
    
    DGLU_API extern const char dg_forthocfetchname[];
    DGLU_API extern const char dg_forthgetbufferbytename[];
    DGLU_API extern const char dg_forthofetchname[];
    DGLU_API extern const char dg_forthgetbufferuint64name[];
    DGLU_API extern const char dg_forthostonewstringname[];
    DGLU_API extern const char dg_forthocstorename[];
    DGLU_API extern const char dg_forthputbufferbytename[];
    DGLU_API extern const char dg_forthostorename[];
    DGLU_API extern const char dg_forthotwostorename[];
    DGLU_API extern const char dg_forthputbufferuint64name[];
    DGLU_API extern const char dg_forthctobufname[];
    DGLU_API extern const char dg_forthtobufname[];
    DGLU_API extern const char dg_forthstringtobufname[];
    DGLU_API extern const char dg_forthbuftocname[];
    DGLU_API extern const char dg_forthbuftoname[];
    DGLU_API extern const char dg_forthbuftostringname[];
    DGLU_API extern const char dg_forthosstorename[];
    DGLU_API extern const char dg_forthosfetchname[];
    DGLU_API extern const char dg_forthstobufname[];
    DGLU_API extern const char dg_forthbuftosname[];
    DGLU_API extern const char dg_forthlengthbufname[];
    DGLU_API extern const char dg_forthgetpbufferhandlearrayheadname[];
    DGLU_API extern const char dg_forthgetsbufferhandlearrayheadname[];
    DGLU_API extern const char dg_forthgetpbufferhandlename[];
    DGLU_API extern const char dg_forthgetsbufferhandlename[];
    
    DGLU_API extern const char dg_forthgetbuffersizename[];
    DGLU_API extern const char dg_forthgetbufferlengthname[];
    DGLU_API extern const char dg_forthgetbuffermaxsizename[];
    DGLU_API extern const char dg_forthgetbuffergrowbyname[];
    DGLU_API extern const char dg_forthgetbuffercurrentoffsetname[];
    DGLU_API extern const char dg_forthputbuffercurrentoffsetname[];
    DGLU_API extern const char dg_forthgetpbufferlengthname[];
    DGLU_API extern const char dg_forthgetpbuffercurrentoffsetname[];

    DGLU_API extern const char dg_forthgetoarrayelementname[];
    DGLU_API extern const char dg_forthgetparrayelementname[];
    DGLU_API extern const char dg_forthinsertinbuffername[];
    DGLU_API extern const char dg_forthdeleteinbuffername[];
    DGLU_API extern const char dg_forthreplaceinbuffername[];  
    DGLU_API extern const char dg_forthinsertsintobuffername[];
    DGLU_API extern const char dg_forthgrowbuffername[];
    DGLU_API extern const char dg_forthshrinkbuffername[];
    DGLU_API extern const char dg_forthemptybuffername[];
    
    DGLU_API extern const char dg_forthnewbuffername[];
    DGLU_API extern const char dg_forthfreebuffername[];
    DGLU_API extern const char dg_forthgetpbufferoffsetname[];
    DGLU_API extern const char dg_forthotopname[];
    DGLU_API extern const char dg_forthgetpbuffername[];
    DGLU_API extern const char dg_forthgetpbufferpbufferlengthname[];
    DGLU_API extern const char dg_forthgetsbuffername[];
    DGLU_API extern const char dg_forthgetpbuffersegmentname[];
    
    DGLU_API extern const char dg_forthmaxusedbuffersname[];
    DGLU_API extern const char dg_forthinusebuffersname[];
    DGLU_API extern const char dg_forthinusebytesname[];
    DGLU_API extern const char dg_forthallocatedbytesname[];
    DGLU_API extern const char dg_forthgetpnewbuffername[];
    
    DGLU_API extern const char dg_forthlinecommentname[];
    DGLU_API extern const char dg_forthslashslashname[];

    DGLU_API extern const char dg_forthu16storename[];
    DGLU_API extern const char dg_forthu32storename[];
    DGLU_API extern const char dg_forthu16fetchname[];
    DGLU_API extern const char dg_forthu32fetchname[];
    DGLU_API extern const char dg_forthu32commaname[];

    DGLU_API extern const char dg_forthof64storename[];

    // buffer id names
    DGLU_API extern const char dg_fortherrorstackbufferidname[];
    DGLU_API extern const char dg_forthdatastackbufferidname[];
    DGLU_API extern const char dg_forthstringstackoffsetbufferidname[];
    DGLU_API extern const char dg_forthstringstackstringbufferidname[];
    DGLU_API extern const char dg_forthdataspacebufferidname[];
    DGLU_API extern const char dg_forthrstackbufferidname[];
    DGLU_API extern const char dg_forthsearchorderstackbufferidname[];
    DGLU_API extern const char dg_forthterminalinputbufferidname[];
    DGLU_API extern const char dg_forthholdbufferidname[];
    DGLU_API extern const char dg_forthpadbufferidname[];
    DGLU_API extern const char dg_forthwordlistbufferidname[];
    DGLU_API extern const char dg_forthdefinitionbufferidname[];
    DGLU_API extern const char dg_forthnameoffsetbufferidname[];
    DGLU_API extern const char dg_forthnamestringbufferidname[];
    DGLU_API extern const char dg_forthwordbufferidname[];
    DGLU_API extern const char dg_forthleavebufferidname[];
    DGLU_API extern const char dg_forthargsbufferidname[];
    DGLU_API extern const char dg_forthcleanupbufferidname[];
    DGLU_API extern const char dg_forthlibhandlebufferidname[];
    DGLU_API extern const char dg_forthpostbufferidname[];
    DGLU_API extern const char dg_forthscriptfilenamebufferidname[];
    DGLU_API extern const char dg_forthlocalpathbufferidname[];
    DGLU_API extern const char dg_forthwordnamebufferidname[];
    DGLU_API extern const char dg_forthextendablecodespacebufferidname[];
    DGLU_API extern const char dg_forthextendabledataspacebufferidname[];
    DGLU_API extern const char dg_forthcorebufferidname[];
    DGLU_API extern const char dg_forthhlistheaderarraybufferidname[];
    DGLU_API extern const char dg_linknewbufstackbufferidname[];
    DGLU_API extern const char dg_forthhstackbufferidname[];
    DGLU_API extern const char dg_forthf64stackbufferidname[];
    

    // forth lstring names
    DGLU_API extern const char dg_forthdepthlstringname[];
    DGLU_API extern const char dg_forthstartoffsetlstringname[];
    DGLU_API extern const char dg_forthgetstartoffsetlstringnname[];
    DGLU_API extern const char dg_forthlengthlstringname[];
    DGLU_API extern const char dg_forthlengthlstringnname[];
    DGLU_API extern const char dg_forthgetplstringname[];
    DGLU_API extern const char dg_forthgetslstringnname[];
    DGLU_API extern const char dg_forthgetlstringname[];
    DGLU_API extern const char dg_forthcopylstringntosname[];
    DGLU_API extern const char dg_forthlstringsfetchname[];
    DGLU_API extern const char dg_forthlstringtosname[];
    DGLU_API extern const char dg_forthstolstringname[];
    DGLU_API extern const char dg_forthgrowlstringname[];
    DGLU_API extern const char dg_forthshortenlstringname[];
    DGLU_API extern const char dg_forthpicklstringname[];
    DGLU_API extern const char dg_forthdroplstringname[];
    DGLU_API extern const char dg_forthdeletelstringname[];
    DGLU_API extern const char dg_forthdeletelstringnname[];
    DGLU_API extern const char dg_forthnewlstringname[];
    DGLU_API extern const char dg_forthinsertlstringname[];
    DGLU_API extern const char dg_forthinsertlstringnname[];
    DGLU_API extern const char dg_forthrolllstringname[];
    DGLU_API extern const char dg_forthminusrolllstringname[];
    DGLU_API extern const char dg_forthdeleteinlstringname[];
    DGLU_API extern const char dg_forthdeleteinlstringnname[];
    DGLU_API extern const char dg_forthinsertinlstringname[];
    DGLU_API extern const char dg_forthinsertinlstringnname[];
    DGLU_API extern const char dg_forthcscanlstringname[];
    DGLU_API extern const char dg_forthcscanlstringnname[];
    DGLU_API extern const char dg_forthscanlstringname[];
    DGLU_API extern const char dg_forthscanlstringnname[];
    DGLU_API extern const char dg_forthcatlstringnname[];
    DGLU_API extern const char dg_forthcopystolstringnname[];
    DGLU_API extern const char dg_forthcopysfromlstringnname[];
    DGLU_API extern const char dg_forthsetlengthlstringnname[];
    DGLU_API extern const char dg_forthcopystoreplacelstringnname[];
    DGLU_API extern const char dg_forthcopylstringntoreplacelstringnname[];
    DGLU_API extern const char dg_forthnewfreeablelstringarrayname[];
    DGLU_API extern const char dg_forthfreefreeablelstringarrayname[];
    DGLU_API extern const char dg_forthpacklstringname[];
    DGLU_API extern const char dg_forthunpacklstringname[];
    DGLU_API extern const char dg_forthnotlstringnname[];
    DGLU_API extern const char dg_forthu8reverselstringnname[];
    DGLU_API extern const char dg_forthuleextendlstringntolname[];
    DGLU_API extern const char dg_forthuleandlstringntolstringnname[];
    DGLU_API extern const char dg_forthuleorlstringntolstringnname[];
    DGLU_API extern const char dg_forthulexorlstringntolstringnname[];
    DGLU_API extern const char dg_forthulenandlstringntolstringnname[];
    DGLU_API extern const char dg_forthulenorlstringntolstringnname[];
    DGLU_API extern const char dg_forthulexnorlstringntolstringnname[];
    DGLU_API extern const char dg_forthuleaddlstringntolstringnname[];
    DGLU_API extern const char dg_forthuleadclstringntolstringnname[];
    DGLU_API extern const char dg_forthulesbblstringntolstringnname[];
    DGLU_API extern const char dg_forthlelshiftlstringnname[];
    DGLU_API extern const char dg_forthulershiftlstringnname[];
    DGLU_API extern const char dg_forthslershiftlstringnname[];
    DGLU_API extern const char dg_forthlelshiftclstringnname[];
    DGLU_API extern const char dg_forthlershiftclstringnname[];
    DGLU_API extern const char dg_forthu64starlstringnplustolstringnname[];
    DGLU_API extern const char dg_forthtoslashulelstringnname[];
    DGLU_API extern const char dg_forthtofactorialulestringname[];
    
    
    // forth string 
    DGLU_API extern const char dg_forthstringwordlistname[];
    
    DGLU_API extern const char dg_forthcomparestringname[];
    DGLU_API extern const char dg_forthequalstringname[];
    DGLU_API extern const char dg_forthgetmidstringname[];
    DGLU_API extern const char dg_forthcatstringname[];
    DGLU_API extern const char dg_forthstringtostringname[];
    DGLU_API extern const char dg_forthlengthstringname[];
    DGLU_API extern const char dg_forthshortenstringname[];
    DGLU_API extern const char dg_forthpickstringname[];
    DGLU_API extern const char dg_forthdupstringname[];
    DGLU_API extern const char dg_forthoverstringname[];
    DGLU_API extern const char dg_forthdropstringname[];
    DGLU_API extern const char dg_forthdeletestringname[];
    DGLU_API extern const char dg_forthswapstringname[];
    DGLU_API extern const char dg_forthnipstringname[];
    DGLU_API extern const char dg_forthrotstringname[];
    DGLU_API extern const char dg_forthdepthstringname[];
    DGLU_API extern const char dg_forthnewstringname[];
    DGLU_API extern const char dg_forthlessthannumbersignstringname[];
    DGLU_API extern const char dg_forthctonewstringname[];
    DGLU_API extern const char dg_forthtonewstringname[];
    DGLU_API extern const char dg_forthturnstringinto0stringname[];
    DGLU_API extern const char dg_forthinsertinstringname[];
    DGLU_API extern const char dg_forthdeleteinstringname[];
    DGLU_API extern const char dg_forthholdstringname[];
    DGLU_API extern const char dg_forthnumbersignstringname[];
    DGLU_API extern const char dg_forthnumbersignsstringname[];
    DGLU_API extern const char dg_forthsignstringname[];
    DGLU_API extern const char dg_forthnumbersigngreaterthanstringname[];
    DGLU_API extern const char dg_forthstringcfetchname[];
    DGLU_API extern const char dg_forthstringcstorename[];
    DGLU_API extern const char dg_forthstringtocname[];
    DGLU_API extern const char dg_forthstringtoname[];
    DGLU_API extern const char dg_forthctostringname[];
    DGLU_API extern const char dg_forthtostringname[];
    DGLU_API extern const char dg_forthsplitstringname[];
    DGLU_API extern const char dg_forthputmidstringname[];
    DGLU_API extern const char dg_forthstostringname[];
    DGLU_API extern const char dg_forthloadfilestringname[];
    DGLU_API extern const char dg_forthsavefilestringname[];
    DGLU_API extern const char dg_forthincludefilestringname[];
    DGLU_API extern const char dg_forthqueryincludefilestringname[];
    DGLU_API extern const char dg_forthgetenvstringname[];
    DGLU_API extern const char dg_forthprintstringname[];
    DGLU_API extern const char dg_forthstringquotesname[];
    DGLU_API extern const char dg_forthgetpstringname[];
    DGLU_API extern const char dg_forthgetsstringndname[];
    DGLU_API extern const char dg_forthasciitounicodestringname[];
    DGLU_API extern const char dg_forthunicodetoasciistringname[];
    DGLU_API extern const char dg_forthgrowstringname[];
    DGLU_API extern const char dg_forthrollstringname[];
    DGLU_API extern const char dg_forthminusrollstringname[];
    DGLU_API extern const char dg_forthdeleteinstringndname[];
    DGLU_API extern const char dg_forthinsertinstringndname[];
    DGLU_API extern const char dg_forthcatstringndname[];
    DGLU_API extern const char dg_forthurldecodestringname[];
    DGLU_API extern const char dg_forthurlencodestringname[];
    DGLU_API extern const char dg_forthstripstringname[];
    DGLU_API extern const char dg_forthstrippathfromfilenamestringname[];
    DGLU_API extern const char dg_forthvariableflstringname[];
    DGLU_API extern const char dg_forthcscanstringname[];
    DGLU_API extern const char dg_forthminuscscanstringname[];
    DGLU_API extern const char dg_forthdotstringsname[];
    DGLU_API extern const char dg_forthwordsstringquotesname[];
    DGLU_API extern const char dg_forthwords0stringquotesname[];
    
    DGLU_API extern const char dg_forthgetquerystringname[];
    DGLU_API extern const char dg_forthgetmethodstringname[];
    DGLU_API extern const char dg_forthfixpathstringname[];
    
    DGLU_API extern const char dg_forthopenlibstringname[];
    DGLU_API extern const char dg_forthopenlibrarystringname[];
    DGLU_API extern const char* dg_forthloadlibrarystringsubname;
    DGLU_API extern const char dg_forthloadlibrarystringname[];
    DGLU_API extern const char dg_forthshowopenlibraryname[];
    DGLU_API extern const char dg_forthshowlibrarystringname[];
    DGLU_API extern const char dg_forthfindlibrarysymbolname[];
    
    DGLU_API extern const char dg_forthfillnewstringname[];
    DGLU_API extern const char dg_forthpzerostrtonewstrname[];
    DGLU_API extern const char dg_forthnglufilestringname[];
    DGLU_API extern const char dg_forthglufilestringname[];
    
    DGLU_API extern const char dg_forthgetargsfromnstringsname[];
    DGLU_API extern const char dg_forthumulleutostringname[];
    DGLU_API extern const char dg_forthtostarulestringname[];
    DGLU_API extern const char dg_forthtoslashulestringname[];
    DGLU_API extern const char dg_forthreversestringname[];
    DGLU_API extern const char dg_forthnotstringname[];
    DGLU_API extern const char dg_forthuleandstringname[];
    DGLU_API extern const char dg_forthuleorstringname[];
    DGLU_API extern const char dg_forthulexorstringname[];
    DGLU_API extern const char dg_forthulenandstringname[];
    DGLU_API extern const char dg_forthulenorstringname[];
    DGLU_API extern const char dg_forthulexnorstringname[];
    DGLU_API extern const char dg_forthlelshiftstringname[];
    DGLU_API extern const char dg_forthulershiftstringname[];
    DGLU_API extern const char dg_forthslershiftstringname[];
    DGLU_API extern const char dg_forthlelshiftcstringname[];
    DGLU_API extern const char dg_forthlershiftcstringname[];
    DGLU_API extern const char dg_forthulestringtonumberstringname[];
    DGLU_API extern const char dg_forthrunfileandwaitnoenvquotesname[];
    DGLU_API extern const char dg_forthrunfileandwaitnoenvstringname[];
    
    
    // forth operating system word names
    DGLU_API extern const char dg_forthwindowswordlistname[];
    DGLU_API extern const char dg_forthfreelibraryname[];
    DGLU_API extern const char dg_forthcallprocaddressname[];
    DGLU_API extern const char dg_forthcalldfpprocname[];
    DGLU_API extern const char dg_forthcallcdeclname[];
    DGLU_API extern const char dg_forthcallstdcallname[];
    DGLU_API extern const char dg_forthcallcppmembername[];
    DGLU_API extern const char dg_forthcallprocaddressretuint128name[];
    DGLU_API extern const char dg_forthcallcdeclretuint128name[];
    DGLU_API extern const char dg_forthcallstdcallretuint128name[];
    DGLU_API extern const char dg_forthcallcppmemberretuint128name[];
    DGLU_API extern const char dg_forthcallcppmemberfunctionname[];
    DGLU_API extern const char dg_forthregsfromname[];
    DGLU_API extern const char dg_forthtoregsname[];
    DGLU_API extern const char dg_forthshowcapturedregsname[];
    DGLU_API extern const char dg_forthtofp0name[];
    DGLU_API extern const char dg_forthfp0fromname[];
    DGLU_API extern const char dg_forthfsfromname[];
    DGLU_API extern const char dg_forthf32fromname[];
    DGLU_API extern const char dg_forthf64fromname[];
    DGLU_API extern const char dg_forthrunfileandwaitname[];
    
    
    // forth user wordlist word names
    DGLU_API extern const char dg_forthuserwordlistname[];
    
    
    // forth variable names
    DGLU_API extern const char dg_forthpbyeflagname[];
    DGLU_API extern const char dg_forthpnopromptsflagname[];
    DGLU_API extern const char dg_forthpcurrentinputbuffername[];
    DGLU_API extern const char dg_forthpjumpbuffervariablename[];
    DGLU_API extern const char dg_forthpcurrentcompilebuffername[];
    DGLU_API extern const char dg_forthpcurrentcreatewordlistname[];
    DGLU_API extern const char dg_forthpcurrentnewvariablebuffername[];
    DGLU_API extern const char dg_forthpquitwasinitflagname[];
    DGLU_API extern const char dg_forthpshowerrorsonexitflagname[];
    DGLU_API extern const char dg_forthpcoloncallssafeflagname[];
    
    DGLU_API extern const char dg_patchdestnamedbufname[];
    DGLU_API extern const char dg_patchsrcnamedbufname[];
    DGLU_API extern const char dg_patchsrcnamedlibname[];
    DGLU_API extern const char dg_patchsrcnamedsymbollistname[];
    DGLU_API extern const char dg_patchdestnamedsymbollistname[];
    DGLU_API extern const char dg_currentnewsymbolhlistidname[];
    DGLU_API extern const char dg_currentnewsymbolelementidname[];
    DGLU_API extern const char dg_currentglulisthlistidname[];
    DGLU_API extern const char dg_currentnewlinkelementidname[];


    
    
    // forth environment word names
    DGLU_API extern const char dg_forthenvironmentwordlistname[];
    DGLU_API extern const char dg_forthslashcountedstringname[];
    DGLU_API extern const char dg_forthslashholdname[];
    DGLU_API extern const char dg_forthslashpadname[];
    DGLU_API extern const char dg_forthaddressunitbitsname[];
    DGLU_API extern const char dg_forthcorename[];
    DGLU_API extern const char dg_forthcoreextname[];
    DGLU_API extern const char dg_forthflooredname[];
    DGLU_API extern const char dg_forthmaxcharname[];
    DGLU_API extern const char dg_forthmaxdname[];
    DGLU_API extern const char dg_forthmaxnname[];
    DGLU_API extern const char dg_forthmaxuname[];
    DGLU_API extern const char dg_forthmaxudname[];
    DGLU_API extern const char dg_forthreturnstackcellsname[];
    DGLU_API extern const char dg_forthstackcellsname[];
    DGLU_API extern const char dg_forthsearchordername[];
    DGLU_API extern const char dg_forthsearchorderextname[];
    DGLU_API extern const char dg_forthwordlistsname[];
    
    
    // forth error word names
    DGLU_API extern const char dg_fortherrorwordlistname[];
    
    DGLU_API extern const char dg_successname[];
    
    DGLU_API extern const char dg_noerroryetname[];
    DGLU_API extern const char dg_incrementingerrorcountname[];
    
    DGLU_API extern const char dg_noerrorsname[];
    DGLU_API extern const char dg_errorbufnotinbharrayname[];
    DGLU_API extern const char dg_errorbufisfreename[];
    DGLU_API extern const char dg_errorbufgrowbynesizenemaxsizename[];
    DGLU_API extern const char dg_errorbufnubcorruptname[];
    DGLU_API extern const char dg_errorunderflowname[];
    DGLU_API extern const char dg_erroroverflowname[];
    DGLU_API extern const char dg_errornotthatmanyerrorsname[];
    
    DGLU_API extern const char dg_errorsbufidis0name[];
    DGLU_API extern const char dg_errorsbufidnotinbharrayname[];
    DGLU_API extern const char dg_errorsbufidisfreename[];
    DGLU_API extern const char dg_errorsbufidnubcorruptname[];
    DGLU_API extern const char dg_errorsbufidsizecorruptname[];
    DGLU_API extern const char dg_errorsoffsetpastendname[];
    
    DGLU_API extern const char dg_errorinsubroutinename[];
    DGLU_API extern const char dg_osexceptionname[];
    DGLU_API extern const char dg_oserrorname[];
    DGLU_API extern const char dg_badmemoryerrorname[];
    DGLU_API extern const char dg_outofmemoryerrorname[];
    DGLU_API extern const char dg_nullpbharrayheaderrorname[];
    DGLU_API extern const char dg_bharrayheadbadmemerrorname[];
    DGLU_API extern const char dg_notbharrayheaderrorname[];
    DGLU_API extern const char dg_nullpbharrayerrorname[];
    DGLU_API extern const char dg_bharraybadmemerrorname[];
    
    DGLU_API extern const char dg_buffernubcorruptname[];
    DGLU_API extern const char dg_bufferidnotinbharrayname[];
    DGLU_API extern const char dg_bufferidisfreename[];
    DGLU_API extern const char dg_bufferidisnotfreename[];
    DGLU_API extern const char dg_bufferunderflowname[];
    DGLU_API extern const char dg_buffergrowbycorruptname[];
    DGLU_API extern const char dg_buffersizecorruptname[];
    DGLU_API extern const char dg_buffermaxsizecorruptname[];
    DGLU_API extern const char dg_buffermaxsizeltsizename[];
    DGLU_API extern const char dg_maxsizeltgrowbyerrorname[];
    DGLU_API extern const char dg_bufferidisforerrorstackname[];
    
    DGLU_API extern const char dg_nullpointererrorname[];
    DGLU_API extern const char dg_offsetpastenderrorname[];
    DGLU_API extern const char dg_segmentgoespastenderrorname[];
    DGLU_API extern const char dg_lstringoffsetpastenderrorname[];
    DGLU_API extern const char dg_lstringsegmentgoespastenderrorname[];
    
    DGLU_API extern const char dg_branchsourcepastenderror[];
    DGLU_API extern const char dg_branchsourcetoolowerror[];
    DGLU_API extern const char dg_branchopcodemissingerror[];
    DGLU_API extern const char dg_branchtoobigerror[];
    DGLU_API extern const char dg_branchalreadyresolvederror[];
    
    DGLU_API extern const char dg_signedvaluetoobigerror[];
    
    DGLU_API extern const char dg_buffergrowby0errorname[];
    DGLU_API extern const char dg_bufferfullerrorname[];
    
    DGLU_API extern const char dg_indexnotinarrayerrorname[];
    DGLU_API extern const char dg_lstringidtoohigherrorname[];
    DGLU_API extern const char dg_lstringsoffsetscorruptname[];
    DGLU_API extern const char dg_lstringtopoffsetwasbadname[];
    DGLU_API extern const char dg_lstringstackdepthcorruptname[];
    DGLU_API extern const char dg_toobigfordesterrorname[];
    
    DGLU_API extern const char dg_wordidtoobigerrorname[];
    DGLU_API extern const char dg_wordlistidtoobigerrorname[];
    DGLU_API extern const char dg_wordalreadylinkederrorname[];
    DGLU_API extern const char dg_newwordoldererrorname[];
    DGLU_API extern const char dg_wordnotfoundinsearchordererrorname[];
    
    DGLU_API extern const char dg_BHarraygrowby0errorname[];
    DGLU_API extern const char dg_BHarraymaxsizeltgrowbyname[];
    DGLU_API extern const char dg_BHarraymaxsizeltbhsizename[];
    DGLU_API extern const char dg_BHarraynubcorruptname[];
    DGLU_API extern const char dg_BHarraynubgtsizename[];
    DGLU_API extern const char dg_BHarrayfullname[];
    
    DGLU_API extern const char dg_initerrorsbuf0inusename[];
    
    DGLU_API extern const char dg_filenotfounderrorname[];
    DGLU_API extern const char dg_pathnotfounderrorname[];
    DGLU_API extern const char dg_accessdeniederrorname[];
    DGLU_API extern const char dg_toomanyopenfileserrorname[];
    DGLU_API extern const char dg_drivenotfounderrorname[];
    DGLU_API extern const char dg_devicenotfounderrorname[];
    DGLU_API extern const char dg_devicenotreadyerrorname[];
    DGLU_API extern const char dg_filesystemunknownerrorname[];
    DGLU_API extern const char dg_devicebrokenerrorname[];
    DGLU_API extern const char dg_fileinuseerrorname[];
    DGLU_API extern const char dg_fileislockederrorname[];
    DGLU_API extern const char dg_filesystemcorrupterrorname[];
    DGLU_API extern const char dg_filetoobigerrorname[];
    DGLU_API extern const char dg_filetypeunknownerrorname[];
    DGLU_API extern const char dg_osdidlessthanavailableerrorname[];
    
    DGLU_API extern const char dg_invalidparametererrorname[];
    
    DGLU_API extern const char dg_writeprotectederrorname[];
    DGLU_API extern const char dg_diskisfullerrorname[];
    
    DGLU_API extern const char dg_crcerrorname[];
    DGLU_API extern const char dg_invalidhandleerrorname[];
    DGLU_API extern const char dg_outsideofbuffererrorname[];
    
    DGLU_API extern const char dg_datastackmisalignederrorname[];
    DGLU_API extern const char dg_datastackunderflowerrorname[];
    DGLU_API extern const char dg_datastacknoraddrmissingerrorname[];
    DGLU_API extern const char dg_rstackunderflowerrorname[];
    DGLU_API extern const char dg_stringstackunderflowerrorname[];
    DGLU_API extern const char dg_lstringstackunderflowerrorname[];
    DGLU_API extern const char dg_underflowerrorname[];
    DGLU_API extern const char dg_arraymisalignederrorname[];
    DGLU_API extern const char dg_alreadyfreeerrorname[];
    DGLU_API extern const char dg_wasnottrulyfreeerrorname[];
    
    DGLU_API extern const char dg_emptystringerrorname[];
    DGLU_API extern const char dg_stringunderflowerrorname[];
    
    DGLU_API extern const char dg_wordlength0errorname[];
    DGLU_API extern const char dg_maxwordlengthexceedederrorname[];
 
    DGLU_API extern const char dg_countlengthexceedederror[];   
    
    DGLU_API extern const char dg_basetoolowerrorname[];
    DGLU_API extern const char dg_basetoohigherrorname[];
    DGLU_API extern const char dg_dglubufferinvaliderrorname[];
    
    DGLU_API extern const char dg_searchorderemptyerror[];
    
    // Forth Hierarchical List Names
    DGLU_API extern const char dg_forthnewhlistname[];
    DGLU_API extern const char dg_forthfreehlistname[];
    DGLU_API extern const char dg_forthprunehlistelementname[];
    DGLU_API extern const char dg_forthfreehlistelementname[];
    DGLU_API extern const char dg_forthnewhlistelementname[];
    DGLU_API extern const char dg_forthgethlistelementnomname[];
    DGLU_API extern const char dg_forthgethlistelementvaluename[];
    DGLU_API extern const char dg_forthgethlistnewestchildname[];
    DGLU_API extern const char dg_forthgethlistoldestchildname[];
    DGLU_API extern const char dg_forthgethlistoldersiblingname[];
    DGLU_API extern const char dg_forthgethlistnewersiblingname[];
    DGLU_API extern const char dg_forthchangehlistparentname[];
    DGLU_API extern const char dg_forthfindclosesthlistchildname[];
    DGLU_API extern const char dg_forthhlisttoxmlstringname[];
    DGLU_API extern const char dg_forthgethowmanyhlistkidsname[];
    DGLU_API extern const char dg_forthgethlistsortedchildnname[];
    DGLU_API extern const char dg_forthfindhlistchildname[];
    DGLU_API extern const char dg_forthhfindstringname[];
    DGLU_API extern const char dg_forthgethlistparentname[];
    DGLU_API extern const char dg_forthsethlistelementvaluename[];
    DGLU_API extern const char dg_forthpackhlistname[];
    DGLU_API extern const char dg_forthunpackhlistname[];
    DGLU_API extern const char dg_forthtoehname[];
    DGLU_API extern const char dg_forthehfromname[];
    DGLU_API extern const char dg_forthdropehname[];
    DGLU_API extern const char dg_forthehtopname[];
    DGLU_API extern const char dg_forthehndname[];
    DGLU_API extern const char dg_forthehname[];
    DGLU_API extern const char dg_forthdupehname[];
    DGLU_API extern const char dg_forthetoehtopname[];
    DGLU_API extern const char dg_forthehnewelementname[];
    DGLU_API extern const char dg_forthehnewelementtoehname[];
    DGLU_API extern const char dg_forthnamestrtovaluestrname[];
    DGLU_API extern const char dg_forthnamestrtovaluename[];
    DGLU_API extern const char dg_forthehnamestrtovaluestrname[];
    DGLU_API extern const char dg_forthehnamestrtovaluename[];
    DGLU_API extern const char dg_forthnamewtovaluestrname[];
    DGLU_API extern const char dg_forthnamewtovaluename[];
    DGLU_API extern const char dg_forthehnamewtovaluestrname[];
    DGLU_API extern const char dg_forthehnamewtovaluename[];
    DGLU_API extern const char dg_forthehoherewtonewelementname[];
    DGLU_API extern const char dg_forthehdotname[];
    DGLU_API extern const char dg_forthehbracketnddotname[];
    DGLU_API extern const char dg_forthehbracket1ddotname[];
    DGLU_API extern const char dg_forthsymbolenumcurlyname[];
    DGLU_API extern const char dg_forthosymbolcodeimportscommacurlyname[];
    DGLU_API extern const char dg_forthnewflatosymbolbufname[];
    DGLU_API extern const char dg_forthfreeflatosymbolbufname[];
    DGLU_API extern const char dg_forthosymbolimportname[];
    
    DGLU_API extern const char dg_wordlisthlistidname[];
    DGLU_API extern const char dg_stringhlistidname[];
    DGLU_API extern const char dg_bufferhlistidname[];
    DGLU_API extern const char dg_symbollistshlistidname[];
    DGLU_API extern const char dg_libraryhlistidname[];
    
    // Forth Glu List Names
    DGLU_API extern const char dg_forthpnewsymbolhlistidname[];
    DGLU_API extern const char dg_forthpnewsymbolelementidname[];
    
    DGLU_API extern const char dg_forthsymbolsstringtoehname[];
    DGLU_API extern const char dg_forthnamedbufstringtoename[];
    DGLU_API extern const char dg_forthnamedbufstrtobufidname[];
    DGLU_API extern const char dg_forthnamedbufstrtopname[];
    DGLU_API extern const char dg_forthhsymbolstrtoname[];
    DGLU_API extern const char dg_forthdashtoname[];
    
    
    // DGLU_API extern const char dg_forthlibdashtoname[];
    
  

    //////////////////////////////////////
    // Operating system access routines //
    //////////////////////////////////////
    
    DGLU_API UINT64 dg_getbharrayheadsize();
    
    DGLU_API UINT64 dg_getpagesize ();
 
    //  DGLU_API UINT128 dg_getsystemtime();
    
    DGLU_API UINT64 dg_getnearesthighestmultiple (
        UINT64 n,
        UINT64 pagesize);

    DGLU_API UINT64 dg_calcnearestpagesize (UINT64 n);
    
    DGLU_API UINT64 dg_gettruesize();

    DGLU_API UINT64 dg_getmicrosecondssince1970Jan01();
    
    DGLU_API extern const char* dg_mallocname;
    DGLU_API const char* dg_malloc(
        void** phandle,
        UINT64 size,
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_reallocname;
    DGLU_API const char* dg_realloc(
        void** phandle,
        UINT64 oldsize, // needed for Linux compatibility
        UINT64 newsize,
    const char* forceerrorflag);
    
    DGLU_API extern const char* dg_freename;
    DGLU_API const char* dg_free(
        void* pbuf,
        UINT64 size, // needed for Linux compatibility
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_readfilename;
    DGLU_API const char* dg_readfile(
        Bufferhandle* pBHarrayhead,
        UINT64 fileid,
        unsigned char* pbuf,
        UINT64 length,
        UINT64 timeout,
        UINT64* pnumread,
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_writefilename;
    DGLU_API const char* dg_writefile(
        Bufferhandle* pBHarrayhead,
        UINT64 fileid,
        unsigned char* pbuf,
        UINT64 length,
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_writestdoutrawname;
    DGLU_API const char* dg_writestdoutraw(
        Bufferhandle* pBHarrayhead,
        unsigned char* pbuf,
        UINT64 length);
    
    DGLU_API extern const char* dg_closefilename;
    DGLU_API const char* dg_closefile(
        UINT64 fileid,
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_filetypeconsole;
    DGLU_API extern const char* dg_filetypepipe;   
    DGLU_API extern const char* dg_filetypedisk;
    DGLU_API extern const char* dg_filetypeunknown;
    
    DGLU_API extern const char* dg_getfiletypename;
    DGLU_API const char* dg_getfiletype(
        Bufferhandle* pBHarrayhead,
        UINT64 fileid,
        const char** pfiletype,
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_gethstdinname;
    DGLU_API const char* dg_gethstdin(
        Bufferhandle* pBHarrayhead,
        UINT64* pfileid,
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_gethstdoutname;
    DGLU_API const char* dg_gethstdout(
        Bufferhandle* pBHarrayhead,
        UINT64* pfileid,
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_gethstderrorname;
    DGLU_API const char* dg_gethstderror(
        Bufferhandle* pBHarrayhead,
        UINT64* pfileid,
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_getfilelengthname;
    DGLU_API const char* dg_getfilelength(
        Bufferhandle* pBHarrayhead,
        UINT64 fileid,
        UINT64* pfilelength,
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_freelibraryname;
    DGLU_API const char* dg_freelibrary(
        UINT64 hlibrary,
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_loadlibraryname;
    DGLU_API const char* dg_loadlibrary(
        const char* libraryname,
        UINT64* phlibrary,
        const char* forceerrorflag);

    DGLU_API extern const char* dg_dlsymname;
    DGLU_API const char* dg_dlsym(
        void* libraryhandle,
        const char* pnamelstring,
        void** psymboladdress,
        const char* pforcerror);
    
    // need dg_openfile
    DGLU_API extern const char* dg_openfileforreadname;
    DGLU_API const char* dg_openfileforread(
        const char* filename, 
        UINT64* pfileid,
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_openfileforwritenewname;
    DGLU_API const char* dg_openfileforwritenew(
        const char* filename, 
        UINT64* pfileid,
        const char* forceerrorflag);
    
    DGLU_API extern const char* dg_getenvironmentvariablename;
    DGLU_API const char* dg_getenvironmentvariable(
        Bufferhandle* pBHarrayhead,
        const char* pvarname,
        unsigned char* pbuf,
        UINT64 length,
        UINT64* pvaluelength,
        const char* forceerrorflag);

    // DGLU_API pid_t dg_getcurrentprocessid();

    DGLU_API extern const char* dg_forkname;
    // DGLU_API const char* dg_fork(
    //    pid_t* ppid,
    //    const char* forceerrorflag);

    DGLU_API extern const char* dg_execvename;
    DGLU_API const char* dg_execve(
        // Bufferhandle* pBHarrayhead,
        const char* pfilename,
        char *const argv[],
        char *const envp[],
        const char* forceerrorflag);

    DGLU_API extern const char* dg_waitpidname;
    // DGLU_API const char* dg_waitpid(
    //     Bufferhandle* pBHarrayhead,
    //     pid_t pid,
    //     int *stat_loc,
    //     int options,
    //     pid_t* pchildprocessid,
    //     const char* forceerrorflag);
   
    DGLU_API UINT64 dg_getmutexhandlesize();
    
    DGLU_API extern const char* dg_newmutexname;
    DGLU_API const char* dg_newmutex(
        struct DG_Mutex_Holder* pmutexholder,
        const char* forceerrorflag);
   
    DGLU_API extern const char* dg_freemutexname;
    DGLU_API const char* dg_freemutex(
        struct DG_Mutex_Holder* pmutexholder,
        const char* forceerrorflag);
   
    DGLU_API extern const char* dg_lockmutexname;
    DGLU_API const char* dg_lockmutex(
        struct DG_Mutex_Holder* pmutexholder,
        const char* forceerrorflag);
   
    DGLU_API extern const char* dg_unlockmutexname;
    DGLU_API const char* dg_unlockmutex(
        struct DG_Mutex_Holder* pmutexholder,
        const char* forceerrorflag);

    DGLU_API extern const char* dg_runfileandwaitname;
    DGLU_API const char* dg_runfileandwait(
        Bufferhandle* pBHarrayhead,
        unsigned char* pfilename,
        char *const argv[],
        char *const envp[],
        const char* forceerrorflag);
        
    DGLU_API extern const char* dg_callfunctionasyncname;
    DGLU_API const char* dg_callfunctionasync(
        UINT64* pthreadhandle,
        void *(*pfunction)(void *), 
        void *parguments);
    
    // DGLU_API extern const char* dg_setenvironmentvariablename;
    // DGLU_API const char* dg_setenvironmentvariable (
    //    Bufferhandle* pBHarrayhead,
    //    const char* pvarname,
    //    const char* pvarvalue,
    //    const char* forceerrorflag);
    
    DGLU_API INT64 dg_getch();
    
    DGLU_API extern const char* dg_readstdinavailabletobuffername;
    DGLU_API void dg_readstdinavailabletobuffer(
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid);
    
    DGLU_API extern const char* dg_writestdoutname;
    DGLU_API const char* dg_writestdout(
        Bufferhandle* pBHarrayhead,
        unsigned char* pbuf,
        UINT64 length);

    DGLU_API void dg_writefileuint64todec(
         Bufferhandle* pBHarrayhead,
         UINT64 fileid,
         UINT64 i);
    
    DGLU_API void dg_writestdoutuinttodec(
        Bufferhandle* pBHarrayhead,
        UINT64 i);
    
    DGLU_API void dg_writestdoutuint64tohex(
        Bufferhandle* pBHarrayhead,
        UINT64 i);
    
    DGLU_API void dg_hexdumpsegment (
        Bufferhandle* pBHarrayhead,
        unsigned char* pstring,
        UINT64 length);

    DGLU_API void dg_forthgothere(Bufferhandle* pBHarrayhead);
    
    DGLU_API const char* dg_checkbharrayhead (Bufferhandle* pBHarrayhead);
    
    DGLU_API const char* dg_checkbharray (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthgetquerystring (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgetmethodstring (Bufferhandle* pBHarrayhead);

    
    
    DGLU_API extern const char* dg_movebytesskipdestinationname;
    DGLU_API const char* dg_movebytesskipdestination (
        unsigned char* psrc, 
        unsigned char* pdest, 
        UINT64 stringlength);

    DGLU_API FLOAT64 dg_f32tof64 (FLOAT32 f32);

    DGLU_API FLOAT32 dg_f64tof32 (FLOAT64 f64);

    DGLU_API INT64 dg_ftod (FLOAT32 f32);
    
    DGLU_API INT64 dg_f64toi64 (FLOAT64 f64);
    
    DGLU_API FLOAT64 dg_dtodf(INT64 i64);


    DGLU_API UINT64 dg_isdelimiter (char c);
    
    DGLU_API UINT64 dg_islineterminator (char c);
    
/*
    DGLU_API extern const char* dg_getlinename;
    DGLU_API void dg_getline(
        Bufferhandle* pBHarrayhead, 
        UINT64 bufferid,
        UINT64 forceerror);
*/

    DGLU_API UINT64 dg_returntestuint128(); // really returns a UINT128 in RDX:RAX

    DGLU_API UINT64 dg_nop();

    DGLU_API UINT64 dg_testasm(UINT64 i);
    
    // test function... for Diaperglu CALLPROCRETUINT128 function
    DGLU_API UINT64 dg_testasmretuint128(UINT64 u); // windows doesn't support this from c
    
    DGLU_API const char* dg_testasmimport ();
    
    DGLU_API UINT64 dg_testalignment ();
    
    DGLU_API FLOAT64 dg_testalignmentdf ();
    
    DGLU_API FLOAT64 dg_testreturndfp ();

    DGLU_API extern const char dg_hexdectonumbername[];
    DGLU_API UINT64 dg_hexdectonumber (
        unsigned char* pnumber,
        UINT64 length,
        UINT64* pflag);
    
    const char* dg_scanforbytesub (
        void* pbuf,
        UINT64* plength,
        UINT64 value);

    DGLU_API extern const char dg_scanforbytename[];
    DGLU_API const char* dg_scanforbyte (
        void* pbuf,
        UINT64* plength,
        UINT64 value);

    const char* dg_scanfornotbytereversesub(
        void* pbuf,
        UINT64* plength,
        UINT64 value);
        
    DGLU_API extern const char dg_scanfornotbytereversename[];
    DGLU_API const char* dg_scanfornotbytereverse (
        void* pbuf,
        UINT64* plength,
        UINT64 value);
    
    const char* dg_scanforuint64sub (
        void* pbuf,
        UINT64* plength,
        UINT64 value);
    DGLU_API extern const char dg_scanforuint64name[];
    DGLU_API const char* dg_scanforuint64 (
        void* pbuf,
        UINT64* plength,
        UINT64 value);
    
    const char* dg_movebytessub (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength);
                                      
    DGLU_API extern const char dg_movebytesname[];
    DGLU_API const char* dg_movebytes (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength);

    const char* dg_movebytesforwardsub(
        unsigned char* psrc,
        unsigned char* pdest,
        UINT64 stringlength);
        
    DGLU_API extern const char dg_movebytesforwardname[];
    DGLU_API const char* dg_movebytesforward (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength);

    const char* dg_movebytesreversesub(
        unsigned char* psrc,
        unsigned char* pdest,
        UINT64 stringlength);
        
    DGLU_API extern const char dg_movebytesreversename[];
    DGLU_API const char* dg_movebytesreverse (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength);
        
        
    DGLU_API extern const char dg_moveuint64sname[];
    DGLU_API const char* dg_moveuint64s (
        UINT64* psrc, 
        UINT64* pdest,
        UINT64 stringlength);
    
    const char* dg_comparebytessub (
        unsigned char* pstring1, 
        UINT64 string1length,
        unsigned char* pstring2,
        UINT64 string2length,
        INT64* pflag);
                                          
    DGLU_API extern const char dg_comparebytesname[];
    DGLU_API const char* dg_comparebytes (
        unsigned char* pstring1, 
        UINT64 string1length,
        unsigned char* pstring2,
        UINT64 string2length,
        INT64* pflag);
    
    DGLU_API void* dg_getretstackpointer ();
    
    DGLU_API void* dg_getframepointer ();
    
    DGLU_API void* dg_getplocalvariablestackspacestart ();
    
    DGLU_API void* dg_getplocalvariablestackspaceend ();
    
    DGLU_API UINT64 dg_getlocalvariablestackspacelength ();
    
    DGLU_API extern const char dg_putbytename[];
    DGLU_API const char* dg_putbyte (
        unsigned char* paddr,
        unsigned char c);
    
    DGLU_API extern const char dg_putuint16name[];
    DGLU_API const char* dg_putuint16 (
        UINT16* paddr,
        UINT16 u);
    
    DGLU_API extern const char dg_putuint32name[];
    DGLU_API const char* dg_putuint32 (
        UINT32* paddr,
        UINT32 u);
    
    DGLU_API extern const char dg_putuint64name[];
    DGLU_API const char* dg_putuint64 (
        UINT64* paddr,
        UINT64 u);
    
    DGLU_API extern const char dg_getbytename[];
    DGLU_API const char* dg_getbyte (
        unsigned char* paddr,
        unsigned char* pc);
    
    DGLU_API extern const char dg_getuint16name[];
    DGLU_API const char* dg_getuint16 (
        UINT16* paddr,
        UINT16* pn);
    
    DGLU_API extern const char dg_getuint32name[];
    DGLU_API const char* dg_getuint32 (
        UINT32* paddr,
        UINT32* pn);
    
    DGLU_API extern const char dg_getuint64name[];
    DGLU_API const char* dg_getuint64 (
        UINT64* paddr,
        UINT64* pn);
    
    DGLU_API extern const char dg_hibitname[];
    DGLU_API UINT64 dg_hibit (UINT64 u);
    
    DGLU_API extern const char dg_countbitsname[];
    DGLU_API UINT64 dg_countbits (UINT64 u);
    
    
    DGLU_API extern const char dg_lobitname[];
    DGLU_API UINT64 dg_lobit (UINT64 u);


    DGLU_API extern const char dg_touleb128name[]; // sub can't give error
    DGLU_API UINT64 dg_touleb128(UINT64 u, UINT64* presult);


    DGLU_API UINT64 dg_gethctwolength(UINT64* pud);


    DGLU_API extern const char dg_hctwostorename[];
    DGLU_API const char* dg_hctwostore(
        unsigned char* pdest, // string length can be up to size of UINT128
        UINT64* pud); // really UINT128*
    
    const char* dg_hctwostoresub(
        unsigned char* pdest, // string length can be up to size of UINT128
        UINT64* pud); // really UINT128*
    
    const char* dg_addbytessub(
        unsigned char* psrc,
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryout);

    DGLU_API extern const char dg_addbytesname[];
    DGLU_API const char* dg_addbytes (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryout);
    
    const char* dg_adcbytessub(
        unsigned char* psrc,
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryinout);

    DGLU_API extern const char dg_adcbytesname[];
    DGLU_API const char* dg_adcbytes (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryinout);
    
    const char* dg_sbbbytessub(
        unsigned char* psrc,
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryinout);

    DGLU_API extern const char dg_sbbbytesname[];
    DGLU_API const char* dg_sbbbytes (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryinout);
    
    const char* dg_shlbytessub(
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryout);

    DGLU_API extern const char dg_shlbytesname[];
    DGLU_API const char* dg_shlbytes ( 
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryout);
    
    const char* dg_rclbytessub(
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryinout);

    DGLU_API extern const char dg_rclbytesname[];
    DGLU_API const char* dg_rclbytes ( 
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryinout);
    
    const char* dg_shrbytessub(
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryout);

    DGLU_API extern const char dg_shrbytesname[];
    DGLU_API const char* dg_shrbytes ( 
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryout);
    
    const char* dg_sarbytessub(
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryout);

    DGLU_API extern const char dg_sarbytesname[];
    DGLU_API const char* dg_sarbytes ( 
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryout);
    
    const char* dg_rcrbytessub(
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryinout);

    DGLU_API extern const char dg_rcrbytesname[];
    DGLU_API const char* dg_rcrbytes ( 
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryinout);
    
    const char* dg_notbytessub(
        unsigned char* pdest,
        UINT64 stringlength);

    DGLU_API extern const char dg_notbytesname[];
    DGLU_API const char* dg_notbytes ( 
        unsigned char* pdest,
        UINT64 stringlength);
    
    const char* dg_andbytessub(
        unsigned char* psrc,
        unsigned char* pdest,
        UINT64 stringlength);

    DGLU_API extern const char dg_andbytesname[];
    DGLU_API const char* dg_andbytes (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength);
    
    const char* dg_orbytessub(
        unsigned char* psrc,
        unsigned char* pdest,
        UINT64 stringlength);

    DGLU_API extern const char dg_orbytesname[];
    DGLU_API const char* dg_orbytes (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength);
    
    const char* dg_xorbytessub(
        unsigned char* psrc,
        unsigned char* pdest,
        UINT64 stringlength);

    DGLU_API extern const char dg_xorbytesname[];
    DGLU_API const char* dg_xorbytes (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength);
    
    const char* dg_nandbytessub(
        unsigned char* psrc,
        unsigned char* pdest,
        UINT64 stringlength);

    DGLU_API extern const char dg_nandbytesname[];
    DGLU_API const char* dg_nandbytes (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength);
    
    const char* dg_norbytessub(
        unsigned char* psrc,
        unsigned char* pdest,
        UINT64 stringlength);

    DGLU_API extern const char dg_norbytesname[];
    DGLU_API const char* dg_norbytes (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength);
    
    const char* dg_xnorbytessub(
        unsigned char* psrc,
        unsigned char* pdest,
        UINT64 stringlength);

    DGLU_API extern const char dg_xnorbytesname[];
    DGLU_API const char* dg_xnorbytes (
        unsigned char* psrc, 
        unsigned char* pdest,
        UINT64 stringlength);
    
    const char* dg_reversebytessub(
        unsigned char* pdest,
        UINT64 stringlength);

    DGLU_API extern const char dg_reversebytesname[];
    DGLU_API const char* dg_reversebytes ( 
        unsigned char* pdest,
        UINT64 stringlength);
    
    const char* dg_incbytessub(
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryout);

    DGLU_API extern const char dg_incbytesname[];
    DGLU_API const char* dg_incbytes ( 
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryout);
    
    const char* dg_decbytessub(
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryout);

    DGLU_API extern const char dg_decbytesname[];
    DGLU_API const char* dg_decbytes ( 
        unsigned char* pdest,
        UINT64 stringlength,
        UINT64* pcarryout);
    
    const char* dg_mulu64tou64ssub(
        UINT64* pdest,           // rdi 
        UINT64* psrc,            // rsi 
        UINT64 u,                // rdx 
        UINT64 srclengthinu64s,  // rcx
        UINT64* pcarryout);      // r8

    DGLU_API extern const char dg_mulu64tou64sname[];   
    DGLU_API const char* dg_mulu64tou64s (
        UINT64* pdest,           // rdi 
        UINT64* psrc,            // rsi 
        UINT64 u,                // rdx 
        UINT64 srclengthinu64s,  // rcx
        UINT64* pcarryout);      // r8
    
    const char* dg_divu64sbyu64sub(
        UINT64* pdest,            // rdi 
        UINT64* premainder,       // rsi 
        UINT64 u,                 // rdx 
        UINT64 destlengthinu64s); // rcx

    DGLU_API extern const char dg_divu64sbyu64name[];   
    DGLU_API const char* dg_divu64sbyu64 (
        UINT64* pdest,            // rdi 
        UINT64* premainder,       // rsi 
        UINT64 u,                 // rdx 
        UINT64 destlengthinu64s); // rcx

    DGLU_API UINT64 dg_dplus(UINT64* pints);  // really a pointer to two UINT128s

    DGLU_API UINT64 dg_dminus(UINT64* pints); // really a pointer to two UINT128s

    DGLU_API UINT64 dg_dulessthan(UINT64* pints); // really a pointer to two UINT128s

    DGLU_API UINT64 dg_dugreaterequalthan(UINT64* pints); // really a pointer to two UINT128s

    DGLU_API UINT64 dg_dlessthan(INT64* pints); // really a pointer to two INT128s

    DGLU_API UINT64 dg_dgreaterequalthan(INT64* pints); // really a pointer to two INT128s

    DGLU_API UINT64 dg_dumin(UINT64* pints); // really a pointer to two UINT128s

    DGLU_API UINT64 dg_dumax(UINT64* pints); // really a pointer to two UINT128s

    DGLU_API UINT64 dg_dmin(INT64* pints); // really a pointer to two INT128s

    DGLU_API UINT64 dg_dmax(INT64* pints); // really a pointer to two INT128s

    DGLU_API UINT64 dg_dnegate(INT64* pints); // really a pointer to two UINT128s

    DGLU_API UINT64 dg_dabs(INT64* pints); // really a pointer to two UINT128s

    
    DGLU_API extern const char dg_tentothexname[];
    DGLU_API FLOAT64 dg_tentothex (UINT64 x);
    
    // DGLU_API extern const char dg_int64tofloat64name[];
    DGLU_API FLOAT64 dg_i64tof64 (INT64 x);
    
    DGLU_API UINT64 dg_timeslog2 (UINT64 x);
    
    DGLU_API FLOAT64 dg_roundf64tonearesteven (FLOAT64 x);
    
    DGLU_API FLOAT64 dg_roundf64tonegativeinfinity (FLOAT64 x);
    
    DGLU_API FLOAT64 dg_f64sqrt (FLOAT64 x);
    
    DGLU_API FLOAT64 dg_f64cos (FLOAT64 x);
    
    DGLU_API FLOAT64 dg_f64sin (FLOAT64 x);
    
    DGLU_API FLOAT64 dg_f64sincos(FLOAT64 x, FLOAT64* psinresult);
    
    DGLU_API FLOAT64 dg_f64tan (FLOAT64 x);
    
    DGLU_API FLOAT64 dg_f64fyl2x (FLOAT64 x, FLOAT64 y);
    
    DGLU_API FLOAT64 dg_f64fyl2xp1 (FLOAT64 x, FLOAT64 y);
    
    DGLU_API FLOAT64 dg_f64f2xm1 (FLOAT64 x);
    
    DGLU_API FLOAT64 dg_truncatef64 (FLOAT64 x);
    
    DGLU_API FLOAT64 dg_f64getfractional (FLOAT64 x);
    
    // DGLU_API FLOAT64 dg_f64pi();
    
    DGLU_API FLOAT64 dg_f64logbase2of10();
    
    DGLU_API FLOAT64 dg_f64logbase2ofe();
    
    DGLU_API FLOAT64 dg_f64fpatan (FLOAT64 x, FLOAT64 y);
    
    DGLU_API FLOAT32 dg_f64tof32 (FLOAT64 x);
    
    DGLU_API FLOAT64 dg_f32tof64 (FLOAT32 x);


    // ///////////////////////////////////////
    // End of Operating System API routines //
    // ///////////////////////////////////////

    DGLU_API void dg_stonewstring(
        Bufferhandle* pBHarrayhead,
        unsigned char* pstring,
        UINT64 stringlength);

    DGLU_API extern const char* dg_stonew0stringname;
    DGLU_API void dg_stonew0string(
        Bufferhandle* pBHarrayhead,
        unsigned char* pstring,
        UINT64 stringlength);

    DGLU_API extern const char dg_pzerostringtonewstringname[];

    DGLU_API void dg_pzerostringtonewstring(
        Bufferhandle* pBHarrayhead,
        unsigned char* pzerostring);
    

    DGLU_API extern const char dg_pushhctwotobuffername[];
    DGLU_API void dg_pushhctwotobuffer(
           Bufferhandle* pBHarrayhead,
           UINT64 bufferid,
           UINT64* pud);  // really UINT128*

    DGLU_API extern const char dg_hlisttomachotriexportlistname[];

    DGLU_API void dg_hlisttomachotriexportlist(
        Bufferhandle* pBHarrayhead,
        UINT64 destbufferid,
        UINT64 srchlistheaderid,      // source symbol list hlist
        UINT64 srcparentelementid,
        UINT64 baseoffset,
        UINT64 childrenpernode);

    DGLU_API extern const char dg_makemachotrieforlt256name[];

    DGLU_API void dg_makemachotrieforlt256 (
        Bufferhandle* pBHarrayhead,
        UINT64 srchlistid,
        UINT64 srcparentelementid,
        unsigned char* pprefix, // this will likely be a pointer to a '-'
        UINT64 prefixlength,    // this will likely be 1
        UINT64 valuelstringoffsetbufferid,
        UINT64 valuelstringstringbufferid,
        UINT64 destbufid);

    DGLU_API extern const char dg_makesharedlibtobufname[];

    DGLU_API void dg_makesharedlibtobuf (
        Bufferhandle* pBHarrayhead,
        unsigned char* pcode,
        UINT64 codelength,
        unsigned char* pexportrie,
        UINT64 exporttrielength,
        UINT64 destbuf);

    DGLU_API extern const char dg_makedototobufname[];

    DGLU_API void dg_makedototobuf (
        Bufferhandle* pBHarrayhead,
        unsigned char* pcode,
        UINT64 codelength,
        UINT64 exportsymbollisthlistid,
        UINT64 exportsymbollistparentelementid,
        UINT64 importsymbollisthlistid,
        UINT64 importsymbollistparentelementid,
        UINT64 destbuf);

    DGLU_API extern const char dg_dotofiletodylibfilename[];

    DGLU_API const char* dg_dotofiletodylibfile (
        // Bufferhandle* pBHarrayhead,
        char* pdotofilename,
        char* pdotdylibfilename);
    
    DGLU_API UINT64 dg_shrd(UINT64* pu, UINT64 shiftcount);
    DGLU_API UINT64 dg_shld(UINT64* pu, UINT64 shiftcount);
    DGLU_API UINT64 dg_ashrd(INT64* pu, UINT64 shiftcount);

    DGLU_API void dg_forthrunfileandwait(Bufferhandle* pBHarrayhead);

//    double dg_forthfsfromsub (Bufferhandle* pBHarrayhead);

//    float dg_forthf32fromsub (Bufferhandle* pBHarrayhead);

    DGLU_API UINT64 dg_getnumberofboxesatleastone (
        UINT64 total, 
        UINT64 boxsize);

    DGLU_API UINT64 dg_getuleb128size (UINT64 u);

    DGLU_API UINT64 dg_getlengthwithuleb128length (UINT64 currentlength);
    
    DGLU_API extern const char dg_randomname[];

    DGLU_API UINT64 dg_random ();
    
    //////////////////////////
    // ASM utility routines //
    //////////////////////////
    
    DGLU_API UINT64 dg_bswap (UINT64 u);
    
    DGLU_API UINT64 dg_callcoreforthroutine(
        Bufferhandle* pBHarrayhead,
        UINT64 forthcoreroutineaddress);
    
    DGLU_API INT64 dg_twoslash (INT64 n1);
    
    DGLU_API UINT64 dg_lshift (UINT64 x1, UINT64 u);
    
    DGLU_API INT64 dg_mstar (
        INT64 n1, 
        INT64 n2, 
        INT64* presult); // really an INT128*
    
    DGLU_API UINT64 dg_rshift (UINT64 x1, UINT64 u);
    
    DGLU_API const char* dg_searchsub (
        unsigned char* caddr1, 
        UINT64 u1,
        unsigned char* caddr2, 
        UINT64 u2,
        unsigned char** pcaddrout);
        
    DGLU_API extern const char dg_searchname[];
    DGLU_API const char* dg_search (
        unsigned char* caddr1, 
        UINT64 u1,
        unsigned char* caddr2, 
        UINT64 u2,
        unsigned char** pcaddrout);
        
    DGLU_API const char* dg_fillwithbytesub (
        unsigned char* pbuf,
        UINT64 length,
        UINT64 value);
        
    DGLU_API extern const char dg_fillwithbytename[];
    DGLU_API const char* dg_fillwithbyte (
        unsigned char* pbuf,
        UINT64 length,
        unsigned char value);

    DGLU_API const char* dg_readallbytessub(
        unsigned char* pbuf,
        UINT64 length);
        
    DGLU_API extern const char dg_readallbytesname[];
    DGLU_API const char* dg_readallbytes (
        unsigned char* pbuf,
        UINT64 length);
    
    DGLU_API void dg_fmslashmod (UINT64* pints); // validity of memory at pints not checked
    
    DGLU_API void dg_smslashrem (UINT64* pints); // validity of memory at pints not checked
    
    DGLU_API void dg_udmslashmod(UINT64* pints); // validity of memory at pints not checked
    
    UINT64 dg_umstar(
        UINT64 n1,
        UINT64 n2,
        UINT64* presult); // really UINT128*
    
    DGLU_API void dg_umslashmod (UINT64* pints); // validity of memory at pints not checked
    
    DGLU_API UINT64 dg_uaddclipped (
        UINT64 u1,  // rdi 
        UINT64 u2); // rsi
    
    DGLU_API UINT64 dg_mstarslash (
        INT64* pnd1,
        INT64 n1,
        INT64 n2); 

    DGLU_API void dg_mplus(UINT64* pints);
    
    DGLU_API void dg_restorequitstate (void* pquitstate);
    
    DGLU_API void dg_savequitstate (void* pquitstate);
    
    // this routine returns no errors
    DGLU_API void dg_printzerostring(
        Bufferhandle* pBHarrayhead,
        unsigned char* addr);
    
    DGLU_API void dg_initpbharrayhead(Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_getsvaluename;

    DGLU_API const char* dg_getsvalue(
        unsigned char* pbuf,
        UINT64 buflength,
        UINT64* pfirstvaluestartoffset,
        UINT64* pfirstvaluelength);
    
    DGLU_API UINT64 dg_checkformatchafterslash(
        unsigned char* pbufa,
        UINT64 bufalength,
        unsigned char* pbufb,
        UINT64 bufblength);
        
    DGLU_API UINT64 dg_hibitd(
        UINT64 ulo,
        UINT64 uhi);
    
    DGLU_API void dg_forthprintstring(Bufferhandle* pBHarrayhead);
    //              ( $1 -$- )
    
    // ////////////////////////
    //  C Compiling Routines //
    // ////////////////////////
    
    DGLU_API void dg_bumpdisplacementsizeifneeded (struct dg_Sibformatter* psf);
    
    DGLU_API extern const char* dg_forthraxjumpcommaname;
    DGLU_API void dg_compilejumptorax (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_compilemovntorax (
        Bufferhandle* pBHarrayhead,
        UINT64 n);
    
    DGLU_API void dg_compileaddn32torax (
        Bufferhandle* pBHarrayhead,
        UINT64 n);

    DGLU_API void dg_compilenegatereg(
        Bufferhandle* pBHarrayhead,
        UINT64 reg);
    
    DGLU_API void dg_compilemovntoreg(
        Bufferhandle* pBHarrayhead,
        UINT64 n,
        UINT64 reg);
    
    DGLU_API void dg_compilemovregtoreg (
        Bufferhandle* pBHarrayhead,
        UINT64 srcreg,
        UINT64 destreg);
    
    DGLU_API void dg_compileaddregtoreg (
        Bufferhandle* pBHarrayhead,
        UINT64 srcreg,
        UINT64 destreg);

    DGLU_API void dg_compilesubn8fromrsp(
        Bufferhandle* pBHarrayhead,
        UINT64 n);

    DGLU_API void dg_compileaddn8torsp(
        Bufferhandle* pBHarrayhead,
        UINT64 n);
    
    DGLU_API void dg_compilemovbracketrbpd8toreg (
        Bufferhandle* pBHarrayhead,
        UINT64 reg,
        UINT64 displacement8);

    DGLU_API void dg_compilemovbracketrbpd32toreg (
        Bufferhandle* pBHarrayhead,
        UINT64 reg,
        UINT64 displacement32);

    DGLU_API void dg_compilemovbracketrbpdtoreg (
        Bufferhandle* pBHarrayhead,
        UINT64 reg,
        INT64 displacement);
    
    DGLU_API void dg_compilepushbracketrbpd8 (
        Bufferhandle* pBHarrayhead,
        UINT64 displacement8);
    
    DGLU_API void dg_compilemovbracketripd32torax (
        Bufferhandle* pBHarrayhead,
        UINT64 displacement32);
    
    DGLU_API void dg_compilecallbracketripd32 (
        Bufferhandle* pBHarrayhead,
        UINT64 displacement32);

    DGLU_API void dg_compilemovregtobracketrbpd8 (
        Bufferhandle* pBHarrayhead,
        UINT64 reg,
        UINT64 displacement8);

    DGLU_API void dg_compilemovregtobracketrbpd32 (
        Bufferhandle* pBHarrayhead,
        UINT64 reg,
        UINT64 displacement32);

    DGLU_API void dg_compilemovregtobracketrbpd (
        Bufferhandle* pBHarrayhead,
        UINT64 reg,
        INT64 displacement);

    DGLU_API void dg_compilebracketrbpdtodatastack (
        Bufferhandle* pBHarrayhead,
        INT64 displacement);

    DGLU_API void dg_compiledatastacktobracketrbpd (
        Bufferhandle* pBHarrayhead,
        INT64 displacement);
    
    DGLU_API void dg_compiledatalink (
        Bufferhandle* pBHarrayhead,
        UINT64 n);
    
    DGLU_API void dg_compilejumptoaddress (
        Bufferhandle* pBHarrayhead,
        UINT64 addr);
    
    DGLU_API void dg_compilereturn (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_compileclc (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_compilestc (Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_compilecopystonewstring (
        Bufferhandle* pBHarrayhead,
        const char* pstring,
        UINT64 stringlength);
        
    DGLU_API void dg_compilecopystonew0string (
    Bufferhandle* pBHarrayhead,
    const char* pstring,
    UINT64 stringlength);
    
    DGLU_API void dg_compilecalloffset (
        Bufferhandle* pBHarrayhead,
        INT64 offset);

    DGLU_API void dg_compilejmpoffset(
        Bufferhandle* pBHarrayhead,
        INT64 offset);

    DGLU_API void dg_compilejmpbracketoffset (
        Bufferhandle* pBHarrayhead,
        INT64 offset);
    
    DGLU_API void dg_compilecalloffsetinsamebuffer (
        Bufferhandle* pBHarrayhead,
        INT64 targetoffset);
    
    DGLU_API void dg_compilecalladdress (
        Bufferhandle* pBHarrayhead,
        UINT64 addr);
    
    DGLU_API void dg_compilecalladdresspreserveregs (
        Bufferhandle* pBHarrayhead,
        UINT64 addr);
    
    DGLU_API void dg_compilecallfunctblfunction (
        Bufferhandle* pBHarrayhead,
        UINT64 functionindex);
    
    DGLU_API void dg_compilepushparametertoret (
        Bufferhandle* pBHarrayhead,
        UINT64 parameterindex);
    
    DGLU_API void dg_compilepushregtoret (
        Bufferhandle* pBHarrayhead,
        UINT64 reg);
    
    DGLU_API void dg_compilepopregfromret (
        Bufferhandle* pBHarrayhead,
        UINT64 reg);
        
    DGLU_API void dg_compileaddnlocalstocallsubsframe (
        Bufferhandle* pBHarrayhead,
        UINT64 n);
        
    DGLU_API void dg_forthentercallsubsframecomma (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthexitframecomma (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthenterrbpframecomma (Bufferhandle* pBHarrayhead);

/*
    DGLU_API unsigned char dg_packmodrslashm (
        UINT64 mode,
        UINT64 reg1orn,
        UINT64 reg2);
    
    DGLU_API unsigned char dg_packsib (
        UINT64 basereg,
        UINT64 indexscalecode,
        UINT64 indexreg);
    
    DGLU_API void dg_compilerfromr (
        Bufferhandle* pBHarrayhead,
        UINT32 opcode,
        UINT32 destreg,
        UINT32 srcreg);
    
    DGLU_API void dg_compilerfrommatrplusscaletimesrplusn (
        Bufferhandle* pBHarrayhead,
        UINT32 opcode,
        UINT32 destreg,
        UINT32 srcbasereg,
        UINT32 srcindexscalecode,
        UINT32 srcindexreg,
        INT32 srcoffset);
    
    DGLU_API void dg_compilerfrommatrplusn (
        Bufferhandle* pBHarrayhead,
        UINT32 opcode,
        UINT32 destreg,
        UINT32 srcreg,
        INT32 srcoffset);
*/
        
    DGLU_API void dg_compilepusholderrorcounttoret (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_compilealignretstack(
        Bufferhandle* pBHarrayhead,
        UINT64 numberofparameters);
/*
    DGLU_API void dg_compilealignretstackpreserveregs(
        Bufferhandle* pBHarrayhead,
        UINT32 numberofparameters);
        
    DGLU_API void dg_compileundoalignretstack (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_compiledropparametersfromret (
        Bufferhandle* pBHarrayhead,
        UINT32 n);
*/
    DGLU_API void dg_compilepushpBHarrayheadtoret (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_compilecallcorename;
    DGLU_API void dg_compilecallcore (
        Bufferhandle* pBHarrayhead,
        UINT64 addr);

    DGLU_API extern const char* dg_compilecallcoreoneuparamname;
    DGLU_API void dg_compilecallcoreoneuparam (
        Bufferhandle* pBHarrayhead, 
        UINT64 addr,
        UINT64 uparam1);

    DGLU_API extern const char* dg_compilecallcoretwouparamsname;
    DGLU_API void dg_compilecallcoretwouparams (
        Bufferhandle* pBHarrayhead, 
        UINT64 addr,
        UINT64 uparam1,
        UINT64 uparam2);

/*
    DGLU_API void dg_compilecallcorepreserveregs (
        Bufferhandle* pBHarrayhead,
        UINT32 addr);
    
    DGLU_API void dg_compilesavelocalframestackpointer (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_compilepushparametertoret (
        Bufferhandle* pBHarrayhead,
        UINT32 parameterindex);
*/
    DGLU_API UINT64 dg_compilepushntoret (
        Bufferhandle* pBHarrayhead,
        UINT64 n);
    
    DGLU_API void dg_compilentoparameter (
        Bufferhandle* pBHarrayhead,
        UINT64 n,
        UINT64 parameter);


    DGLU_API extern const char* dg_compilecallftcolonname;
    DGLU_API void dg_compilecallftcolon (
        Bufferhandle* pBHarrayhead,
        UINT64 n);

    DGLU_API extern const char* dg_compilebranchname;
    DGLU_API UINT64 dg_compilebranch (
        Bufferhandle* pBHarrayhead,
        UINT64 branchtype);
    
    DGLU_API extern const char* dg_resolvecompiledbranchname;
    DGLU_API void dg_resolvecompiledbranch (
        Bufferhandle* pBHarrayhead,
        UINT64 afterbranchoffset,
        UINT64 targetoffset);
    
    DGLU_API extern const char* dg_compilecomparename;
    DGLU_API void dg_compilecompare(
        Bufferhandle* pBHarrayhead,
        UINT64 n);

    DGLU_API extern const char dg_compileacopyofsscopytoname[];

    DGLU_API void dg_compileacopyofsscopyto(
        Bufferhandle* pBHarrayhead,
        unsigned char* psqstr,
        UINT64 sqstrlen);

//    DGLU_API void dg_showframe (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_compileinitlocals (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_compileentersubroutineframe (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_compileexitlocalsname;
    
    DGLU_API void dg_compileexitlocals (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_compilequeryerror (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const UINT64 dg_regnottrashedduringaligment;
    
    DGLU_API void dg_compilepushdatastack (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_compilepushntodatastack (
        Bufferhandle* pBHarrayhead,
        UINT64 n);
        
    DGLU_API void dg_compilepushntof64stack (
        Bufferhandle* pBHarrayhead,
        UINT64 n);

    DGLU_API extern const char* dg_compileobtoptodatastackname;
    DGLU_API void dg_compileobtoptodatastack(
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);

    DGLU_API extern const char* dg_compilebracketobtodatastackname;
    DGLU_API void dg_compilebracketobtodatastack (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);

    DGLU_API extern const char* dg_compiledatastacktobracketobname;
    DGLU_API void dg_compiledatastacktobracketob (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);

    DGLU_API extern const char* dg_compilef64stacktobracketobname;
    DGLU_API void dg_compilef64stacktobracketob (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);

    DGLU_API extern const char* dg_compileu128bracketobtodatastackname;
    DGLU_API void dg_compileu128bracketobtodatastack (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);

    DGLU_API extern const char* dg_compiledatastacktou128bracketobname;
    DGLU_API void dg_compiledatastacktou128bracketob (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);

    DGLU_API extern const char* dg_compilebracketobtof64stackname;
    DGLU_API void dg_compilebracketobtof64stack (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);
    
    DGLU_API void dg_pushf64tof64stack(
        Bufferhandle* pBHarrayhead,
        FLOAT64 r);
    
    DGLU_API FLOAT64 dg_popf64fromf64stack(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthregsfrom (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthtoregs (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthshowsavedregs (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthshowcapturedregs (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthtofp0(Bufferhandle* pBHarrayhead, FLOAT64 df);
    
    DGLU_API FLOAT64 dg_forthfp0from (Bufferhandle* pBHarrayhead);
    
    DGLU_API FLOAT64 dg_forthfsfrom (Bufferhandle* pBHarrayhead);
    
    DGLU_API FLOAT32 dg_forthf32from (Bufferhandle* pBHarrayhead);
    
    
    //////////////////////
    // C Error Routines //
    //////////////////////
    
    DGLU_API extern const char dg_initerrorsbuf0inuse[];
    
    DGLU_API void dg_initerrors (
        Bufferhandle* pBHarrayhead,
        UINT64 size,
        const char** pError);
    
    DGLU_API extern const char* dg_pusherrorname;
    DGLU_API void dg_pusherror (
        Bufferhandle* pBHarrayhead,
        const char* error);
    
    DGLU_API extern const char* dg_pushbuffererrorname;
    DGLU_API void dg_pushbuffererror (Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);
        
    DGLU_API extern const char* dg_geterrorname;
    DGLU_API const char* dg_geterror (
        Bufferhandle* pBHarrayhead,
        UINT64 errorindex);
    
    DGLU_API extern const char* dg_getbuffererrorname;
    DGLU_API void dg_getbuffererror (
        Bufferhandle* pBHarrayhead, 
        UINT64 errorindex,
        UINT64* poffset,
        UINT64* pbufferid);
    
    DGLU_API extern const char* dg_poperrorname;
    DGLU_API const char* dg_poperror (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_popbuffererrorname;
    DGLU_API void dg_popbuffererror (
        Bufferhandle* pBHarrayhead, 
        UINT64* perrmsgoffset,
        UINT64* perrmsgbufid);
    
    DGLU_API extern const char* dg_geterrorcountname;
    DGLU_API UINT64 dg_geterrorcount (Bufferhandle* pBHarrayhead);
    
    DGLU_API UINT64 dg_checkerrorsonstack (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_clearerrors (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_clearerrorsanderrorline (Bufferhandle* pBHarrayhead);   
    
    DGLU_API void dg_droptoerrorcount (
        Bufferhandle* pBHarrayhead,
        UINT64 newerrorcount);
    
    DGLU_API void dg_replaceerrors (
        Bufferhandle* pBHarrayhead, 
        UINT64 olderrorbufferid,
        UINT64 olderroroffset,
        UINT64 newerrorbufferid,
        UINT64 newerroroffset);
    
    DGLU_API void dg_forthdoterrors (Bufferhandle* pBHarrayhead);
    
    // ///////////////////////////
    // End of C Error Routines  //
    // ///////////////////////////
    
    
    // /////////////////////
    // C buffer routines  //
    // /////////////////////
    
    DGLU_API extern const char* dg_newbuffername;
    DGLU_API UINT64 dg_newbuffer (
        Bufferhandle* pBHarrayhead,
        UINT64 growby,
        UINT64 maxsize,
        const char** pError,
        UINT64 forceoutofmemory);
    
    DGLU_API void dg_freebuffer (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid);
    
    DGLU_API UINT64 dg_freeallbuffers (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_checkbuffername;
    DGLU_API const char* dg_checkbuffer (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid);
    
    DGLU_API extern const char* dg_growbuffername;
    DGLU_API UINT64 dg_growbuffer (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 length,  // in bytes
        const char** pError,
        UINT64 forceoutofmemory);
    
    DGLU_API extern const char* dg_shrinkbuffername;
    DGLU_API void dg_shrinkbuffer (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 length,  // in bytes
        const char** pError);
    
    DGLU_API extern const char* dg_getpbuffername;
    DGLU_API unsigned char* dg_getpbuffer (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64** pplength);
    
    DGLU_API extern const char* dg_clearbuffername;
    DGLU_API void dg_clearbuffer (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid);
    
    DGLU_API extern const char* dg_getpbuffersegmentname;
    DGLU_API unsigned char* dg_getpbuffersegment (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset,
        UINT64 length);
    
    DGLU_API extern const char* dg_getpbufferoffsetname;
    DGLU_API unsigned char* dg_getpbufferoffset  (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);
    
    DGLU_API extern const char* dg_getbuffersegmentname;
    DGLU_API void dg_getbuffersegment (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset,
        UINT64 length,
        unsigned char* pdest);
    
    DGLU_API extern const char* dg_putbuffersegmentname;
    DGLU_API void dg_putbuffersegment (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset,
        UINT64 length,
        unsigned char* psrc);
    
    DGLU_API extern const char* dg_getbufferuint32name;
    DGLU_API UINT32 dg_getbufferuint32 (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);  // in bytes, that way this can be used in mixed buffers
    
    DGLU_API extern const char* dg_putbufferuint32name;
    DGLU_API void dg_putbufferuint32 (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset,
        UINT64 data);
    
    DGLU_API extern const char* dg_pushbufferuint32name;
    DGLU_API void dg_pushbufferuint32 (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 data);
    
    DGLU_API extern const char* dg_popbufferuint32name;
    DGLU_API UINT32 dg_popbufferuint32 (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid);
    
    DGLU_API extern const char* dg_getbufferuint64name;
    DGLU_API UINT64 dg_getbufferuint64 (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);  // in bytes, that way this can be used in mixed buffers
    
    DGLU_API extern const char* dg_putbufferuint64name;
    DGLU_API void dg_putbufferuint64 (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset,
        UINT64 data);
    
    DGLU_API extern const char* dg_pushbufferuint64name;
    DGLU_API void dg_pushbufferuint64 (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 data);
    
    DGLU_API extern const char* dg_pushbuffersegmentname;
    DGLU_API void dg_pushbuffersegment (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 length,
        unsigned char* psrc);
    
    DGLU_API extern const char* dg_pickbuffersegmentname;
    DGLU_API void dg_pickbuffersegment (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset,
        UINT64 length);
    
    DGLU_API extern const char* dg_popbuffersegmentname;
    DGLU_API void dg_popbuffersegment (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 length,
        unsigned char* pdest);
    
    DGLU_API extern const char* dg_getbufferbytename;
    DGLU_API unsigned char dg_getbufferbyte (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);
    
    DGLU_API extern const char* dg_putbufferbytename;
    DGLU_API void dg_putbufferbyte (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset,
        unsigned char data);
    
    DGLU_API extern const char* dg_popbufferbytename;
    DGLU_API unsigned char dg_popbufferbyte (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid);
    
    DGLU_API extern const char* dg_pushbufferbytename;
    DGLU_API void dg_pushbufferbyte (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        unsigned char data);
    
    DGLU_API extern const char* dg_popbufferuint64name;
    DGLU_API UINT64 dg_popbufferuint64 (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid);
    
    DGLU_API extern const char* dg_insertinbuffername;
    DGLU_API void dg_insertinbuffer (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset, // in bytes
        UINT64 length); // in bytes
  
    DGLU_API extern const char dg_replacebuffersegmentname[];
    DGLU_API void dg_replacebuffersegment (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 destoffset,
        UINT64 destlength,
        unsigned char* psrc,
        UINT64 srclength);     
    
    DGLU_API extern const char* dg_deleteinbuffername;
    DGLU_API void dg_deleteinbuffer (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset, // in bytes
        UINT64 length); // in bytes
    
    DGLU_API extern const char* dg_getbufferlengthname;
    DGLU_API UINT64 dg_getbufferlength (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid);
    
    DGLU_API extern const char* dg_getpbufferhandlename;
    DGLU_API Bufferhandle* dg_getpbufferhandle (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid);
    
    DGLU_API extern const char* dg_push0stringtobuffersegmentname;
    DGLU_API void dg_push0stringtobuffersegment (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        unsigned char* psrc);
                                                 
    DGLU_API extern const char* dg_freebuffersetname;
    DGLU_API void dg_freebufferset (
       Bufferhandle* pBHarrayhead,
       UINT64 buffersetheaderbufferid);
       
    DGLU_API extern const char* dg_newbuffersetname;
    DGLU_API UINT64 dg_newbufferset (
         Bufferhandle* pBHarrayhead,
         UINT64 growby,
         UINT64 maxsize,
         UINT64 numberofbuffers);
         
    DGLU_API extern const char* dg_getuint64arrayelementname;
    DGLU_API UINT64 dg_getuint64arrayelement (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 index);
    
    DGLU_API extern const char* dg_getuint64stackelementname;
    DGLU_API UINT64 dg_getuint64stackelement (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 index); // 0 = top
        
    DGLU_API extern const char* dg_putuint64arrayelementname;
    DGLU_API void dg_putuint64arrayelement (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 index,
        UINT64 x);
    
    DGLU_API extern const char* dg_putuint64stackelementname;
    DGLU_API void dg_putuint64stackelement (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 index,
        UINT64 x);
    
    DGLU_API extern const char* dg_stonewbuffername;
    DGLU_API UINT64 dg_stonewbuffer (
        Bufferhandle* pBHarrayhead,
        UINT64 growby,
        UINT64 maxsize,
        unsigned char* psrc,
        UINT64 srclength);
    
    DGLU_API extern const char* dg_stonewbuffername;
    DGLU_API Bufferhandle* dg_getpbufferhandlefast(
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid);
    
    DGLU_API extern const char* dg_makebuffersizeatleastxname;
    DGLU_API void dg_makebuffersizeatleastx (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 x);
    
    DGLU_API extern const char* dg_getpnewbuffername;
    DGLU_API unsigned char* dg_getpnewbuffer (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferlength);
    
    DGLU_API void dg_pushdatastack (
        Bufferhandle* pBHarrayhead,
        UINT64 data);

    DGLU_API extern const char* dg_pushbracketobtodatastackname;
    DGLU_API void dg_pushbracketobtodatastack (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);

    DGLU_API extern const char* dg_pushu128bracketobtodatastackname;
    DGLU_API void dg_pushu128bracketobtodatastack (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);
        
    DGLU_API void dg_pushf64stack (
        Bufferhandle* pBHarrayhead,
        UINT64 data);

    DGLU_API extern const char* dg_pushbracketobtof64stackname;
    DGLU_API void dg_pushbracketobtof64stack (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);
        
    DGLU_API void dg_pushsearchorderstack (
       Bufferhandle* pBHarrayhead,
       UINT64 wid);
    
    
    DGLU_API UINT64 dg_popdatastack (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_popdatastacktobracketobname;
    DGLU_API void dg_popdatastacktobracketob (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);

    DGLU_API extern const char* dg_popdatastacktou128bracketobname;
    DGLU_API void dg_popdatastacktou128bracketob (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);

    DGLU_API UINT64 dg_popf64stack (Bufferhandle* pBHarrayhead);

    DGLU_API extern const char* dg_popf64stacktobracketobname;
    DGLU_API void dg_popf64stacktobracketob (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);
    
    DGLU_API void dg_compilesegment (
        Bufferhandle* pBHarrayhead,
        const char* psrc,
        UINT64 length);
    
    DGLU_API extern const char* dg_savelocalstackdepthname;
    DGLU_API void dg_savelocalstackdepth (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_restorelocalstackdepthname;
    DGLU_API void dg_restorelocalstackdepth (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_savelocallsstackdepthname;
    DGLU_API void dg_savelocallsstackdepth (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_restorelocallsstackdepthname;
    DGLU_API void dg_restorelocallsstackdepth (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_tocurrentname;
    DGLU_API void dg_tocurrent (
        Bufferhandle* pBHarrayhead,
        UINT64 newcurrentwordlist);
    
    DGLU_API extern const char* dg_currentfromname;
    DGLU_API UINT64 dg_currentfrom (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_tocurrentcompilebufferstackname;
    DGLU_API void dg_tocurrentcompilebufferstack (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_fromcurrentcompilebufferstackname;
    DGLU_API void dg_fromcurrentcompilebufferstack (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_tocurrentvariablebufferstackname;
    DGLU_API void dg_tocurrentvariablebufferstack (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_fromcurrentvariablebufferstackname;
    DGLU_API void dg_fromcurrentvariablebufferstack (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_pushenvtobufname;
    DGLU_API void dg_pushenvtobuf (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        const char* penvname);
    
    DGLU_API extern const char* dg_getevalstdinfileidname;
    DGLU_API UINT64 dg_getevalstdinfileid (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_getevalfilenamefileidname;
    DGLU_API UINT64 dg_getevalfilenamefileid (
        Bufferhandle* pBHarrayhead,
        unsigned char* pbuf,
        UINT64* pbuflength);
    
    DGLU_API extern const char* dg_getevalargsfileidname;
    DGLU_API UINT64 dg_getevalargsfileid (Bufferhandle* pBHarrayhead);
    
    DGLU_API UINT64 dg_getnoscriptfileid (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_getiisquerystringfileidname;
    DGLU_API UINT64 dg_getiisquerystringfileid (
        Bufferhandle* pBHarrayhead,
        unsigned char* pname,
        UINT64 namelength);
    
    DGLU_API extern const char* dg_getapachequerystrfileidname;
    DGLU_API UINT64 dg_getapachequerystrfileid (
        Bufferhandle* pBHarrayhead,
        unsigned char* pname,
        UINT64 namelength);
    
    DGLU_API extern const char* dg_getquerystringfileidname;
    DGLU_API UINT64 dg_getquerystringfileid(Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_getevaluatefileidname;
    DGLU_API UINT64 dg_getevaluatefileid (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_readstdinavailabletobuffername;
    DGLU_API void dg_readstdinavailabletobuffer(
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid);
    
    DGLU_API extern const char* dg_querygetpostname;
    DGLU_API void dg_querygetpost (
        Bufferhandle* pBHarrayhead,
        UINT64 firsttimethrough);
    
    DGLU_API extern const char* dg_closeevalfileidname;
    DGLU_API void dg_closeevalfileid (
        Bufferhandle* pBHarrayhead,
        UINT64 fileid);
    
    DGLU_API extern const char* dg_getlinename;
    DGLU_API UINT64 dg_getline(
       Bufferhandle* pBHarrayhead,
       UINT64 fileid,
       UINT64 bufferid, 
       const char* pforceerror);
    
    DGLU_API extern const char* dg_argstoargsbuffername;
    DGLU_API void dg_argstoargsbuffer (Bufferhandle* pBHarrayhead, int argc, char* argv[]);
    
    //////////////////////////////
    // End of C Buffer Routines //
    //////////////////////////////
    
    
        
    ////////////////////////
    // C lstring routines //
    ////////////////////////
    
    DGLU_API extern const char* dg_getnumberoflstringsonstackname;
    DGLU_API UINT64 dg_getnumberoflstringsonstack(
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid);
    
    DGLU_API extern const char* dg_getlstringstartoffsetname;
    DGLU_API UINT64 dg_getlstringstartoffset (
        Bufferhandle *pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringid);
    
    DGLU_API extern const char* dg_getlstringlengthname;
    DGLU_API UINT64 dg_getlstringlength (
        Bufferhandle *pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringid);
    
    DGLU_API extern const char* dg_getplstringname;
    DGLU_API unsigned char* dg_getplstring(
        Bufferhandle* pBHarrayhead,
        UINT64  offsetbufferid,
        UINT64  stringbufferid,
        UINT64  stringid,
        UINT64* pstringlength);
    
    DGLU_API extern const char* dg_getlstringname;
    DGLU_API void dg_getlstring (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64 maxlength,
        unsigned char* pdest);
    
    DGLU_API extern const char* dg_poplstringname;
    DGLU_API void dg_poplstring (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 maxlength,
        unsigned char* pdest);
    
    DGLU_API extern const char* dg_pushlstringname;
    DGLU_API void dg_pushlstring (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 length,
        unsigned char* psrc);
    
    DGLU_API extern const char* dg_growlstringname;
    DGLU_API void dg_growlstring (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 length);
    
    DGLU_API extern const char dg_catlstringname[];
    DGLU_API void dg_catlstring (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid);

    DGLU_API extern const char dg_catulstringsname[];
    DGLU_API void dg_catulstrings(
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 u);
        
    DGLU_API extern const char* dg_picklstringname;
    DGLU_API void dg_picklstring (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 n);
    
    DGLU_API extern const char* dg_droplstringname;
    DGLU_API void dg_droplstring (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid);
  
    DGLU_API extern const char* dg_dropnlstringsname;
    DGLU_API void dg_dropnlstrings (Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 n);
    
    DGLU_API extern const char* dg_deletelstringname;
    DGLU_API void dg_deletelstring (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid);
    
    DGLU_API extern const char* dg_insertlstringname;
    DGLU_API void dg_insertlstring (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64 length);
    
    DGLU_API extern const char* dg_deleteinlstringname;
    DGLU_API void dg_deleteinlstring (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64 offset,
        UINT64 length);
    
    DGLU_API extern const char* dg_insertinlstringname;
    DGLU_API void dg_insertinlstring (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64 offset,
        UINT64 length);
    
    DGLU_API extern const char* dg_catlstringnname;
    DGLU_API void dg_catlstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid);
                                  
    DGLU_API extern const char* dg_stotoplstringname;
    DGLU_API void dg_stotoplstring (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 length,
        unsigned char* psrc);
    
    DGLU_API extern const char* dg_copystolstringnname;
    DGLU_API void dg_copystolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64 offset,
        unsigned char* psrc,
        UINT64 length);
  
    DGLU_API extern const char* dg_pushstolstringnname;
    DGLU_API void dg_pushstolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        unsigned char* psrc,
        UINT64 length);
    
    DGLU_API extern const char* dg_copysfromlstringnname;
    DGLU_API void dg_copysfromlstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64 offset,
        UINT64 length,
        unsigned char* pdest);
    
    DGLU_API extern const char* dg_setlengthlstringnname;
    DGLU_API void dg_setlengthlstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64 newlength);
    
    DGLU_API extern const char* dg_replacelstringnname;
    DGLU_API void dg_replacelstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        unsigned char* psrc,
        UINT64 length);
    
    DGLU_API extern const char* dg_copylstringntoreplacelstringnname;
    DGLU_API void dg_copylstringntoreplacelstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 srcoffsetbufferid,
        UINT64 srcstringbufferid,
        UINT64 srcstringid,
        UINT64 destoffsetbufferid,
        UINT64 deststringbufferid,
        UINT64 deststringid);

    DGLU_API extern const char* dg_copytoinsertlstrntomname;
    DGLU_API void dg_copytoinsertlstrntom (
        Bufferhandle* pBHarrayhead,
        UINT64 srcoffsetbufferidn,
        UINT64 srcstringbufferidn,
        UINT64 srcstringidn,
        UINT64 srcoffsetn,
        UINT64 destoffsetbufferidm,
        UINT64 deststringbufferidm,
        UINT64 deststringidm,
        UINT64 destoffsetm,
        UINT64 length);
    
    DGLU_API extern const char* dg_makesurelstringnexistsname;
    DGLU_API void dg_makesurelstringnexists (
        Bufferhandle* pBHarrayhead,
        UINT64 lstringoffsetbufferid,
        UINT64 lstringstringbufferid,
        UINT64 n);

    DGLU_API extern const char* dg_freefreeablelstringarrayname;
    DGLU_API void dg_freefreeablelstringarray(
        Bufferhandle* pBHarrayhead,
        UINT64 freeindexbuffer);

    DGLU_API extern const char* dg_newfreeablelstringarrayname;
    DGLU_API UINT64 dg_newfreeablelstringarray(Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char* dg_freefreeablelstringname;
    DGLU_API void dg_freefreeablelstring(
        Bufferhandle* pBHarrayhead,
        UINT64 freeindexbuffer,
        UINT64 lstringindex);
    
    DGLU_API extern const char* dg_newfreeablelstringname;
    DGLU_API UINT64 dg_newfreeablelstring (
        Bufferhandle* pBHarrayhead,
        UINT64 freeindexbuffer);
 
    DGLU_API extern const char* dg_isfreeablelstringfreename;
    DGLU_API UINT64 dg_isfreeablelstringfree (
        Bufferhandle* pBHarrayhead,
        UINT64 freeindexbuffer,
        UINT64 flstringid);
    
    DGLU_API extern const char* dg_getsflstrheadername;
    DGLU_API Freeablelstringarrayheader* dg_getsflstrheader(
        Bufferhandle* pBHarrayhead,
        UINT64 freeindexbuffer,
        UINT64* pflstrheaderlength);

    DGLU_API extern const char* dg_copyflstrheadertosname;
    DGLU_API void dg_copyflstrheadertos(
        Bufferhandle* pBHarrayhead,
        UINT64 freeindexbuffer,
        Freeablelstringarrayheader* pflstrheader,
        UINT64 flstrheaderlength);
    
    DGLU_API extern const char* dg_insertsintoflstrnname;
    DGLU_API void dg_insertsintoflstrn(
        Bufferhandle* pBHarrayhead,
        UINT64 freeindexbuffer,
        UINT64 flstringid,
        UINT64 offset,
        unsigned char* psrc,
        UINT64 length);

    DGLU_API extern const char* dg_copysfromflstrnname;
    DGLU_API void dg_copysfromflstrn(
        Bufferhandle* pBHarrayhead,
        UINT64 freeindexbuffer,
        UINT64 flstringid,
        UINT64 offset,
        UINT64 length,
        unsigned char* pdest);

    DGLU_API extern const char* dg_copytoinsertflstrntomname;
    DGLU_API void dg_copytoinsertflstrntom(
        Bufferhandle* pBHarrayhead,
        UINT64 freeindexbuffern,
        UINT64 flstringnid,
        UINT64 offsetn,
        UINT64 freeindexbufferm,
        UINT64 flstringmid,
        UINT64 offsetm,
        UINT64 length);

    DGLU_API extern const char* dg_deleteinflstringnname;
    DGLU_API void dg_deleteinflstringn(
        Bufferhandle* pBHarrayhead,
        UINT64 freeindexbuffer,
        UINT64 flstringid,
        UINT64 offset,
        UINT64 length);

    DGLU_API extern const char* dg_getlengthflstringnname;
    DGLU_API UINT64 dg_getlengthflstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 freeindexbuffer,
        UINT64 flstringid);

    DGLU_API extern const char* dg_newfreeablelstringonendname;
    DGLU_API UINT64 dg_newfreeablelstringonend (
        Bufferhandle* pBHarrayhead,
        UINT64 freeindexbuffer,
        unsigned char* plstring,
        UINT64 lstringlength);
    
    DGLU_API extern const char* dg_comparestolstringnname;
    DGLU_API INT64 dg_comparestolstringn (
        Bufferhandle* pBHarrayhead,
        unsigned char* ps,
        UINT64 slength,
        UINT64 lstringoffsetbufferid,
        UINT64 lstringstringbufferid,
        UINT64 n);

    DGLU_API extern const char* dg_deleteuint64inlstringnname;
    DGLU_API void dg_deleteuint64inlstringn (
        Bufferhandle* pBHarrayhead, 
        UINT64 sortedkeyslstringoffsetbufferid, // lstring holding sort key array
        UINT64 sortedkeyslstringstringbufferid,
        UINT64 sortedkeyslstringindex,
        UINT64 keyofvaluetoremove);

    DGLU_API extern const char* dg_insertwithcfillinlstringnname;
    DGLU_API void dg_insertwithcfillinlstringn (
        Bufferhandle* pBHarrayhead, 
        UINT64 lstringoffsetbufferid,
        UINT64 lstringstringbufferid,
        UINT64 lstringindex,
        UINT64 offset,
        UINT64 length,
        unsigned char cvalue);
    
    DGLU_API extern const char* dg_packedlstringmagicstring;
    DGLU_API extern const UINT64 dg_packedlstringmagicstringlength;
    
    DGLU_API extern const char* dg_packlstringname;
    DGLU_API void dg_packlstring (
        Bufferhandle* pBHarrayhead,
        UINT64 lstringoffsetbufferid,
        UINT64 lstringstringbufferid);
    
    DGLU_API extern const char* dg_isbufferapackedlstringname;
    DGLU_API UINT64 dg_isbufferapackedlstring (
        Bufferhandle* pBHarrayhead,
        UINT64 lstringstringbufferid);

    DGLU_API extern const char* dg_unpacklstringname;
    DGLU_API UINT64 dg_unpacklstring (
        Bufferhandle* pBHarrayhead,
        UINT64 lstringstringbufferid);
    
    DGLU_API extern const char dg_urlencodelstringname[];
    DGLU_API void dg_urlencodelstring (
        Bufferhandle* pBHarrayhead,
        UINT64 lstringoffsetbufferid,
        UINT64 lstringstringbufferid);
    
    DGLU_API extern const char dg_urldecodelstringname[];
    DGLU_API void dg_urldecodelstring (
        Bufferhandle* pBHarrayhead,
        UINT64 lstringoffsetbufferid,
        UINT64 lstringstringbufferid);
        
    DGLU_API extern const char dg_uleextendlstringntolname[];
    DGLU_API void dg_uleextendlstringntol (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64 newlength);
        
    DGLU_API extern const char dg_uleaddlstringntolstringnname[];
    DGLU_API void dg_uleaddlstringntolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 offsetbufferidb,
        UINT64 stringbufferidb,
        UINT64 stringidb,
        UINT64* pcarryout);
        
    DGLU_API extern const char dg_uleadclstringntolstringnname[];
    DGLU_API void dg_uleadclstringntolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 offsetbufferidb,
        UINT64 stringbufferidb,
        UINT64 stringidb,
        UINT64* pcarryinout);
        
    DGLU_API extern const char dg_ulesbblstringntolstringnname[];
    DGLU_API void dg_ulesbblstringntolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 offsetbufferidb,
        UINT64 stringbufferidb,
        UINT64 stringidb,
        UINT64* pcarryinout);
        
    DGLU_API extern const char dg_lelshiftlstringnname[];
    DGLU_API void dg_lelshiftlstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64* pcarryout);
        
    DGLU_API extern const char dg_ulershiftlstringnname[];
    DGLU_API void dg_ulershiftlstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64* pcarryout);
        
    DGLU_API extern const char dg_slershiftlstringnname[];
    DGLU_API void dg_slershiftlstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64* pcarryout);
        
    DGLU_API extern const char dg_lelshiftclstringnname[];
    DGLU_API void dg_lelshiftclstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64* pcarryinout);
        
    DGLU_API extern const char dg_lershiftclstringnname[];
    DGLU_API void dg_lershiftclstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid,
        UINT64* pcarryinout);
        
    DGLU_API extern const char dg_partialulemulu64tolstringnname[];
    DGLU_API void dg_partialulemulu64tolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 offsetbufferidb,
        UINT64 stringbufferidb,
        UINT64 stringidb,
        UINT64* px);
        
    DGLU_API extern const char dg_ulemulu64tolstringnname[];
    DGLU_API void dg_ulemulu64tolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 offsetbufferidb,
        UINT64 stringbufferidb,
        UINT64 stringidb,
        UINT64 x);
        
    DGLU_API extern const char dg_notlstringnname[];
    DGLU_API void dg_notlstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid);
        
    DGLU_API extern const char dg_reverselstringnname[];
    DGLU_API void dg_reverselstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferid,
        UINT64 stringbufferid,
        UINT64 stringid);
        
    DGLU_API extern const char dg_uleandlstringntolstringnname[];
    DGLU_API void dg_uleandlstringntolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 offsetbufferidb,
        UINT64 stringbufferidb,
        UINT64 stringidb);
        
    DGLU_API extern const char dg_uleorlstringntolstringnname[];
    DGLU_API void dg_uleorlstringntolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 offsetbufferidb,
        UINT64 stringbufferidb,
        UINT64 stringidb);
        
    DGLU_API extern const char dg_ulexorlstringntolstringnname[];
    DGLU_API void dg_ulexorlstringntolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 offsetbufferidb,
        UINT64 stringbufferidb,
        UINT64 stringidb);
        
    DGLU_API extern const char dg_ulenandlstringntolstringnname[];
    DGLU_API void dg_ulenandlstringntolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 offsetbufferidb,
        UINT64 stringbufferidb,
        UINT64 stringidb);
        
    DGLU_API extern const char dg_ulenorlstringntolstringnname[];
    DGLU_API void dg_ulenorlstringntolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 offsetbufferidb,
        UINT64 stringbufferidb,
        UINT64 stringidb);
        
    DGLU_API extern const char dg_ulexnorlstringntolstringnname[];
    DGLU_API void dg_ulexnorlstringntolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 offsetbufferidb,
        UINT64 stringbufferidb,
        UINT64 stringidb);
        
    DGLU_API extern const char dg_mulu64bylstringnaddtolstringnname[];
    DGLU_API void dg_mulu64bylstringnaddtolstringn (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 offsetbufferidb,
        UINT64 stringbufferidb,
        UINT64 stringidb,
        UINT64 u);
        
    DGLU_API extern const char dg_divlstringnbyu64name[];
    DGLU_API void dg_divlstringnbyu64 (
        Bufferhandle* pBHarrayhead,
        UINT64 offsetbufferida,
        UINT64 stringbufferida,
        UINT64 stringida,
        UINT64 u,
        UINT64* premainder);
    
    // #define dg_packedlstringmagic (0x6b636170)
    
    
    // ///////////////////////////
    // C Lstring Queue Routines //
    // ///////////////////////////
    
    DGLU_API extern const char* dg_initlstringqueuename;

    DGLU_API void dg_initlstringqueue (
        Bufferhandle *pBHarrayhead,
        UINT64 growby,
        UINT64 maxsize,
        UINT64 switchlength,
        Lstringqueueheader* pLstringqueueheader);
      
        
    DGLU_API extern const char* dg_pushlstringqueueheadname;

    DGLU_API void dg_pushlstringqueuehead (
        Bufferhandle* pBHarrayhead,
        Lstringqueueheader* pLstringqueueheader,
        unsigned char* pstring,
        UINT64 stringlength);
        
        
    DGLU_API extern const char* dg_poplstringqueuetailname;

    DGLU_API unsigned char* dg_poplstringqueuetail (
        Bufferhandle* pBHarrayhead,
        Lstringqueueheader* pLstringqueueheader,
        UINT64* pstringlength);
    
    DGLU_API extern const char* dg_getslstringqueuetailname;

    DGLU_API unsigned char* dg_getslstringqueuetail (
        Bufferhandle* pBHarrayhead,
        Lstringqueueheader* pLstringqueueheader,
        UINT64 lstringqueheaderlength,
        UINT64* pstringlength);
        
    DGLU_API extern const char* dg_newsharedlstringqueuename;

    DGLU_API UINT64 dg_newsharedlstringqueue(
        Bufferhandle* pBHarrayhead,
        UINT64 growby,       
        UINT64 maxsize,      
        UINT64 switchlength); 
        
    DGLU_API extern const char* dg_freesharedlstringqueuename;

    DGLU_API void dg_freesharedlstringqueue(
        Bufferhandle* pBHarrayhead,
        UINT64 SharedQueueHandleBufferID);
        
    DGLU_API extern const char* dg_droplstringqueuetailname;

    DGLU_API void dg_droplstringqueuetail (
        Bufferhandle* pBHarrayhead,
        Lstringqueueheader* pLstringqueueheader,
        UINT64 lstringqueheaderlength);
        
    DGLU_API extern const char* dg_pushsharedlstringqueuename;

    DGLU_API void dg_pushsharedlstringqueue(
        Bufferhandle* pBHarrayhead,
        SharedQueueHandleBufferStructs* psharedqueuebuffer, // has to be the pointer
        UINT64 sharedquebufferlength,                       // making them pass the length too
        unsigned char* pstring,
        UINT64 stringlength);
        
    DGLU_API extern const char* dg_lockpopsharedlstringqueuetailname;

    DGLU_API unsigned char* dg_lockpopsharedlstringqueuetail (
        Bufferhandle* pBHarrayhead,
        SharedQueueHandleBufferStructs* psharedqueuebuffer, 
        UINT64 sharedquebufferlength,
        UINT64* pstringlength);
        
    DGLU_API extern const char* dg_locksharedlstringqueuename;

    DGLU_API void dg_locksharedlstringqueue(
        Bufferhandle* pBHarrayhead,
        SharedQueueHandleBufferStructs* psharedqueuebuffer, 
        UINT64 sharedquebufferlength);
        
    DGLU_API extern const char* dg_unlocksharedlstringqueuename;

    DGLU_API void dg_unlocksharedlstringqueue(
        Bufferhandle* pBHarrayhead,
        SharedQueueHandleBufferStructs* psharedqueuebuffer, 
        UINT64 sharedquebufferlength);
    
    // ///////////////////////
    // C Wordlist Routines  //
    // ///////////////////////
    
    DGLU_API extern const char* dg_newwordlistname;
    
    DGLU_API UINT64 dg_newwordlist (
        Bufferhandle* pBHarrayhead, 
        UINT64 parentelementid);
    
    
    DGLU_API extern const char* dg_newwordname;
    
    DGLU_API UINT64 dg_newword (
        Bufferhandle* pBHarrayhead,
        UINT64 compilebufid,
        UINT64 compilebufoffset,
        UINT64 databufid,
        UINT64 databufoffset,
        UINT64 namebufid,
        UINT64 nameoffset,
        UINT64 namelength);


    DGLU_API extern const char* dg_newwordcopynamename;
    
    DGLU_API UINT64 dg_newwordcopyname (
        Bufferhandle* pBHarrayhead,
        UINT64 compilebufid,
        UINT64 compilebufoffset,
        UINT64 databufid,
        UINT64 databufoffset,
        UINT64 namebufid,
        UINT64 nameoffset,
        UINT64 namelength);
    
    
    DGLU_API UINT64 dg_new0stringnamecoreword (
        Bufferhandle* pBHarrayhead, 
        UINT64 compilebufoffset,
        UINT64 databufoffset,
        unsigned char* pname);
    
    
    DGLU_API UINT64 dg_new0stringcorenameword (
        Bufferhandle* pBHarrayhead, 
        UINT64 compilebufid,
        UINT64 compilebufoffset,
        UINT64 databufid,
        UINT64 databufoffset,
        unsigned char* pname);
    
    
    DGLU_API extern const char* dg_getpdefinitionname;   
    
    DGLU_API Definitionheader* dg_getpdefinition (
        Bufferhandle* pBHarrayhead,
        UINT64 definitionid);
    
    
    DGLU_API extern const char* dg_linkdefinitionname;        
    
    DGLU_API void dg_linkdefinition (
        Bufferhandle* pBHarrayhead,
        UINT64 wordlistid,
        UINT64 newwordid);
    
    
    DGLU_API extern const char* dg_createovariablebufdefname;         
    
    DGLU_API UINT64 dg_createovariablebufdef (
        Bufferhandle* pBHarrayhead,
        unsigned char* pname,
        UINT64 namelength);
    
    
    DGLU_API extern const char* dg_createocompilebufdefname;         
    
    DGLU_API UINT64 dg_createocompilebufdef (
        Bufferhandle* pBHarrayhead,
        unsigned char* pname,
        UINT64 namelength);
    
    
    DGLU_API extern const char* dg_createsubthreaddefname;    
    
    DGLU_API UINT64 dg_createsubthreaddef (
        Bufferhandle* pBHarrayhead,
        unsigned char* pname,
        UINT64 namelength);
    
    
    DGLU_API extern const char* dg_createvariabledefname;         
    
    DGLU_API UINT64 dg_createvariabledef (
        Bufferhandle* pBHarrayhead,
        unsigned char* pname,
        UINT64 namelength);
    
    
    DGLU_API extern const char* dg_createdconstantdefname;

    DGLU_API UINT64 dg_createdconstantdef (
        Bufferhandle* pBHarrayhead,
        UINT64 databufoffset,
        UINT64 databufid,
        unsigned char* pname,
        UINT64 namelength);
    
    
    DGLU_API extern const char* dg_createconstantdefname;        
    
    DGLU_API UINT64 dg_createconstantdef (
        Bufferhandle* pBHarrayhead,
        UINT64 dataid,
        unsigned char* pname,
        UINT64 namelength);
  
  
    DGLU_API extern const char* dg_createbrackettoorderconstantdefname;

    DGLU_API UINT64 dg_createbrackettoorderconstantdef (
        Bufferhandle* pBHarrayhead,
        UINT64 dataid,
        unsigned char* pname,
        UINT64 namelength);     
  
  
    DGLU_API extern const char* dg_createfconstantdefname;

    DGLU_API UINT64 dg_createfconstantdef (
        Bufferhandle* pBHarrayhead,
        UINT64 dataid,
        unsigned char* pname,
        UINT64 namelength);
        
        
    DGLU_API extern const char* dg_getlatestdefinitionname; 
      
    DGLU_API UINT64 dg_getlatestdefinition (
        Bufferhandle* pBHarrayhead,
        UINT64 vocabularyid);
      
      
    DGLU_API extern const char* dg_getnextdefinitionname;
      
    DGLU_API UINT64 dg_getnextdefinition (
        Bufferhandle* pBHarrayhead,
        UINT64 currentdefinition);
      
      
    DGLU_API extern const char* dg_executedefinitionname;       
      
    DGLU_API void dg_executedefinition (
        Bufferhandle* pBHarrayhead,
        UINT64 definitionid);
      
      
    DGLU_API extern const char* dg_finddefinwordlistname; 
      
    DGLU_API UINT64 dg_finddefinwordlist (
        Bufferhandle* pBHarrayhead,
        UINT64 vocabularyid,
        unsigned char* pname,
        UINT64 namelength);
      
      
    DGLU_API extern const char* dg_finddefinsearchordername; 
      
    DGLU_API UINT64 dg_finddefinsearchorder (
        Bufferhandle* pBHarrayhead,
        unsigned char* pname,
        UINT64 namelength);
    
      
    DGLU_API UINT64 dg_getfinddefinsearchordermetrics(
        Bufferhandle* pBHarrayhead,
        unsigned char* pname,
        UINT64 namelength,
        UINT64 numberofseconds);
          
      
    DGLU_API extern const char* dg_changelatestcompileroutinename; 
      
    DGLU_API void dg_changelatestcompileroutine (
        Bufferhandle* pBHarrayhead,
        UINT64 compilebufid,
        UINT64 compilebufoffset);
      
      
    DGLU_API extern const char* dg_newpresortedwordlistname ;

    DGLU_API UINT64 dg_newpresortedwordlist (
        Bufferhandle* pBHarrayhead,
        struct Premadeword *pmypresortedwordlist,
        UINT64 mypresortedwordlistlength);
      
      
    DGLU_API extern const char dg_copyandrenamewordidname[];

    DGLU_API UINT64 dg_copyandrenamewordid (
        Bufferhandle* pBHarrayhead,
        UINT64 definitionid,
        unsigned char* pname,
        UINT64 namelength);
          
          
    DGLU_API extern const char dg_findcopyandrenamewordname[];

    DGLU_API UINT64 dg_findcopyandrenameword (
        Bufferhandle* pBHarrayhead,
        unsigned char* poldname,
        UINT64 oldnamelength,
        unsigned char* pnewname,
        UINT64 newnamelength);
 
 
    DGLU_API extern const char dg_emptywordlistname[];

    DGLU_API void dg_emptywordlist (
        Bufferhandle* pBHarrayhead,
        UINT64 parentelementid);
          
        
    DGLU_API FLOAT64 dg_f64tobase10 (
        FLOAT64 r,
        INT64* pbase10exponent,
        INT64* psign);
        
    DGLU_API void dg_unpackdf(
        FLOAT64 df,
        UINT64* pmantissa,
        INT64* pexponent,
        INT64* psign);
        
    DGLU_API FLOAT64 dg_packdf(
        UINT64 mantissa,
        INT64 exponent,
        INT64 sign);
        
    DGLU_API void dg_f64tof64rootf642expf6410exp(   
        FLOAT64 f64,
        FLOAT64* pf64root,
        FLOAT64* pf642exp,
        FLOAT64* pf6410exp,
        INT64* base10exponent,
        INT64* psign);
        
    DGLU_API UINT64 dg_fixedpointu128todecimalstring(
        unsigned char* pstring,
        UINT64 stringlength,
        UINT64 whole, 
        UINT64 fractional,
        INT64 sign);
        
    DGLU_API INT64 dg_represent(
        FLOAT64 r,
        unsigned char* pstring,
        UINT64 stringlength,
        INT64* psign,
        UINT64* pfractionalremainder);
        
    DGLU_API FLOAT64 dg_f64twotothex(FLOAT64 x);
    
    DGLU_API void dg_forthfdot(Bufferhandle* pBHarrayhead);
        
    DGLU_API void dg_forthfsdot(Bufferhandle* pBHarrayhead);
        
    DGLU_API void dg_forthfedot(Bufferhandle* pBHarrayhead);
    
    
    
        
        
    /*
    //////////////////////////////////
    // Some Buffer Parsing Routines //
    //////////////////////////////////
    
    DGLU_API extern const char dg_captureerrorlinename[];

    DGLU_API void dg_captureerrorline(
        Bufferhandle* pBHarrayhead,
        UINT32 bufferid);
    
    */
    DGLU_API extern const char* dg_evaluatebuffername;       
    
    DGLU_API void dg_evaluatebuffer (
        Bufferhandle* pBHarrayhead, 
        UINT64 bufferid);
    
    
    DGLU_API void dg_forthevaluatebuffer (Bufferhandle* pBHarrayhead);
    //                   ( bufferid -- )
    
/*
    DGLU_API extern const char* dg_argstoargsbuffername;  
    
    DGLU_API void dg_argstoargsbuffer (
        Bufferhandle* pBHarrayhead, 
        INT64 argc,
        char* argv[]);
*/    
    
    DGLU_API extern const char* dg_forthdopromptgetstateerror;
    
    DGLU_API void dg_forthdoprompt (Bufferhandle* pBHarrayhead);
    
    /////////////////////////////////////////
    // End of Some Buffer Parsing Routines //
    /////////////////////////////////////////
    
    
    
    //////////////////////////////////
    // C Hierarchical List Routines //
    //////////////////////////////////
    
    DGLU_API extern const char* dg_sortedkeyslstringname;
    
    DGLU_API extern const char* dg_gethlistheaderarrayheadername;

    DGLU_API void dg_gethlistheaderarrayheader(
        Bufferhandle* pBHarrayhead,
        Freeablelstringarrayheader* phlistheaderarrayheader,
        UINT64 hlistheaderarrayheaderlength);
        
        
    DGLU_API extern const char* dg_querycreatehlistheaderarrayname;

    DGLU_API UINT64 dg_querycreatehlistheaderarray(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_gethlistheadername;

    DGLU_API void dg_gethlistheader(
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        Hlistheader* phlistheader,
        UINT64 hlistheaderlength);
        
        
    DGLU_API extern const char* dg_newhlistname;

    DGLU_API UINT64 dg_newhlist (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_freehlistname;

    DGLU_API void dg_freehlist (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid);
        
        
    DGLU_API extern const char* dg_linklasthlistchildelementname;

    DGLU_API void dg_linklasthlistchildelement (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 elementheaderid,
        UINT64 parentelementheaderid);
        
    
    DGLU_API extern const char* dg_prunehlistelementname;

    DGLU_API void dg_prunehlistelement (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 elementheaderid);
        
        
    DGLU_API extern const char* dg_unlinkhlistchildelementname;

    DGLU_API void dg_unlinkhlistchildelement (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 elementheaderid);
    
    
    DGLU_API extern const char* dg_newhlistelementname;
        
    DGLU_API UINT64 dg_newhlistelement (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistid,
        UINT64 parentelementid,
        unsigned char* pname,
        UINT64 namelength,
        unsigned char* pvalue,
        UINT64 valuelength);
        
        
    DGLU_API extern const char* dg_newpresortedhlistelementname;
        
    DGLU_API UINT64 dg_newpresortedhlistelement (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistid,
        UINT64 parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        UINT64 key,
        unsigned char* pname,
        UINT64 namelength,
        unsigned char* ptag,
        UINT64 taglength,
        unsigned char* pvalue,
        UINT64 valuelength);
        
        
    DGLU_API extern const char* dg_gethlistlastchildofparentname;

    DGLU_API UINT64 dg_gethlistlastchildofparent (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 parentelementid);
    
    
    DGLU_API extern const char* dg_gethlistfirstchildname;

    DGLU_API UINT64 dg_gethlistfirstchild (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 parentelementid);
        
        
    DGLU_API extern const char* dg_gethlistnextsiblingname;

    DGLU_API UINT64 dg_gethlistnextsibling (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 childelementid);
        
        
    DGLU_API extern const char* dg_gethlistprevioussiblingname;

    DGLU_API UINT64 dg_gethlistprevioussibling (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 childelementid);
    
    
    DGLU_API extern const char* dg_freehlistelementname;

    DGLU_API void dg_freehlistelement (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 elementheaderid);
        
        
    DGLU_API extern const char* dg_gethlistelementparentname;

    DGLU_API UINT64 dg_gethlistelementparent (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 elementid);
        
        
    DGLU_API extern const char* dg_getshlistelementnomname;

    DGLU_API unsigned char* dg_getshlistelementnom (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 elementid,
        UINT64* pnamelength);
        
        
    DGLU_API extern const char* dg_getshlistelementvaluename;

    DGLU_API unsigned char* dg_getshlistelementvalue (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 elementid,
        UINT64* pvaluelength);
        
        
    DGLU_API extern const char* dg_sethlistelementvaluename;

    DGLU_API void dg_sethlistelementvalue (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 elementid,
        unsigned char* pvalue,
        UINT64 valuelength);
        
        
    DGLU_API extern const char* dg_getshlistelementname;

    DGLU_API void dg_getshlistelement (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 elementid,
        unsigned char** ppname,
        UINT64* pnamelength,
        unsigned char** ppvalue,
        UINT64* pvaluelength);
        
        
    DGLU_API extern const char* dg_findhlistchildwithnamesname;

    DGLU_API UINT64 dg_findhlistchildwithnames (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 parentelementid,
        unsigned char* pnametomatch,
        UINT64 nametomatchlength);
    
    
    DGLU_API extern const char* dg_forthsortcomparevaluekeyname;

    DGLU_API void dg_forthsortcomparevaluekey (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_forthsortcomparevaluename;

    DGLU_API void dg_forthsortcomparevalue (Bufferhandle* pBHarrayhead);
        
        
    DGLU_API extern const char* dg_dobinaryinsertsortstepname;

    DGLU_API UINT64 dg_dobinaryinsertsortstep (
        Bufferhandle* pBHarrayhead,
        unsigned char* psortedkeyslstring,
        UINT64 sortedkeyslength,
        INT64 (*pcompareroutine)(Bufferhandle*, void*, UINT64, UINT64),
        void* pcomparedata,
        UINT64 comparedatalength,
        UINT64* pstartindex,
        UINT64* pendindex,
        UINT64* ptofindbeforerangeflag,
        UINT64* ploopdoneflag);
    
    
    DGLU_API extern const char* dg_findsortedhlistchildsubname;

    DGLU_API UINT64 dg_findsortedhlistchildsub (
        Bufferhandle* pBHarrayhead,
        unsigned char* pname,
        UINT64 namelength,
        UINT64 sortedkeyslstringlength,
        unsigned char* psortedkeyslstring,
        UINT64* pnamelstringoffsetbufferlength,
        UINT64* pnamelstringoffsetbuffer,
        UINT64* pnamelstringstringbufferlength,
        unsigned char* pnamelstringstringbuffer,
        UINT64* pindexofkeyaftermatch, // index in sort key lstring after match
        UINT64* pkey);
        
        
    DGLU_API extern const char* dg_findsortedhlistchildname;
    //const char* dg_sortedkeyslstringname = "sorted keys lstring";

    DGLU_API UINT64 dg_findsortedhlistchild (
        Bufferhandle* pBHarrayhead,
        unsigned char* pname,
        UINT64 namelength,
        UINT64 hlistheaderid,
        UINT64 parentelementid,
        UINT64* pindexofkeyaftermatch, // index in sort key lstring after match
        UINT64* pkey); // key = f[indexaftermatch - 1]
        
        
    DGLU_API extern const char* dg_changehlistelementparentname;

    DGLU_API void dg_changehlistelementparent (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistid,
        UINT64 elementid,
        UINT64 newparentelementid);
        
        
    DGLU_API extern const char* dg_getnumberofsortedchildrenname;

    DGLU_API UINT64 dg_getnumberofsortedchildren(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid,
    UINT64 parentelementid);
    
    
    DGLU_API extern const char* dg_getidofsortedhlistchildnname;

    DGLU_API UINT64 dg_getidofsortedhlistchildn(
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 parentelementid,
        UINT64 sortkeyindex);
        
        
    DGLU_API extern const char* dg_addnsamechartostringname;
    
    DGLU_API void dg_addnsamechartostring (
        Bufferhandle* pBHarrayhead,
        UINT64 n,
        unsigned char c);
        
        
    DGLU_API extern const char* dg_hlisttodglumlstringname;

    DGLU_API void dg_hlisttodglumlstring (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistid,
        UINT64 rootelementid,
        UINT64 indentationstepsize,
        UINT64 currentindentationlevel);
        
        
    DGLU_API extern const char* dg_newunsortedhlistelementname;
        
    DGLU_API UINT64 dg_newunsortedhlistelement (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistid,
        Hlistheader myhlistheader,
        UINT64 parentelementid, // if parentelementid == DG_ENDOFLIST it means you are adding a root element
        unsigned char* pname,
        UINT64 namelength,
        unsigned char* pvalue,
        UINT64 valuelength,
        UINT64 previouselementid,
        UINT64 nextelementid);
        
        
    DGLU_API extern const char* dg_getshlistelementnamenename;

    DGLU_API const char* dg_getshlistelementnamene (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistheaderid,
        UINT64 elementid,
        unsigned char** ppname,
        UINT64* pnamelength);
    
    
    DGLU_API extern const char* dg_callhlistchildrenname;

    DGLU_API void dg_callhlistchildren(
        Bufferhandle* pBHarrayhead,
        UINT64 hlistid,         // hlist containing function names to do
        UINT64 parentelementid, // parent element id in hlist containing function names to do
        UINT64         fsortedkeyslstringlength,       // function symbol list - actually. the list doesn't
        unsigned char* pfsortedkeyslstring,            //   change at run time so a key array is not necessary
        UINT64*        pfnamelstringoffsetbuffer,
        unsigned char* pfnamelstringstringbuffer,
        void           (**pfunctions)(Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*));

    
    DGLU_API extern const char* dg_callhlistchildrenbynname;

    DGLU_API void dg_callhlistchildrenbyn(
        Bufferhandle* pBHarrayhead,
        UINT64 hlistid,         // hlist containing function names to do
        UINT64 parentelementid, // parent element id in hlist containing function names to do
        UINT64 maxnumberoffunctions,
        void           (**pfunctions)(Bufferhandle*, UINT64, UINT64, unsigned char*, UINT64, Hlistheader*));


    DGLU_API extern const char* dg_packhlistname;

    DGLU_API UINT64 dg_packhlist (
        Bufferhandle* pBHarrayhead,
        UINT64 hlistid);
    
    
    DGLU_API extern const char* dg_unpackhlistname;

    DGLU_API UINT64 dg_unpackhlist (
        Bufferhandle* pBHarrayhead,
        UINT64 lstringstringbufferid);
    
    
    DGLU_API extern const char dg_namestringtovaluestringname[];

    DGLU_API unsigned char* dg_namestringtovaluestring(
        Bufferhandle* pBHarrayhead,
        UINT64 hlistid,
        UINT64 elementid,
        unsigned char* pname,
        UINT64 namelength,
        UINT64* pvaluelength);
    
    // ///////////////////////////////////////
    // End of C Hierarchical List Routines  //
    // ///////////////////////////////////////
    
    
    // ////////////////////
    // FORTH Core Words  //
    // ////////////////////
    
    
    DGLU_API extern const char dg_forthstorename[];  
    
    DGLU_API void dg_forthstore (Bufferhandle* pBHarrayhead);
    //         ( data address -- )
    
    
    DGLU_API extern const char dg_forthnumbersignname[];    
    
    DGLU_API void dg_forthnumbersign (Bufferhandle* pBHarrayhead);
    //              ( u1 -- u1/base )
    //              ( number$ -pad- number$2 )
    
    
    DGLU_API extern const char dg_forthnumbersigngreatername[];        
    
    DGLU_API void dg_forthnumbersigngreater (Bufferhandle* pBHarrayhead);
    //                     ( u1 -- addressofnumber$ lengthofnumber$ )
    //                     ( number$ -pad- number$ )
    
    
    DGLU_API extern const char dg_forthnumbersignsname[];
    
    DGLU_API void dg_forthnumbersigns (Bufferhandle* pBHarrayhead);
    //               ( u1 -- 0 )
    //               ( number$ -pad- number$2 )
    
    
    DGLU_API extern const char dg_forthtickname[]; 
    
    DGLU_API void dg_forthtick (Bufferhandle* pBHarrayhead);
    //             ( "<spaces>name<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff")
    //             ( -- executiontoken )
    
    
    DGLU_API extern const char dg_forthparenname[];
    
    DGLU_API void dg_forthparen (Bufferhandle* pBHarrayhead); // ( ( ) comment
    //         ( "somestuff<rightdg_forthparen>morestuff" -currentinputbuffer- "morestuff" )
    
    
    DGLU_API extern const char dg_forthstarname[];       
    
    DGLU_API void dg_forthstar (Bufferhandle* pBHarrayhead);          
    //        ( n1 n2 -- n1*n2 )
    
    
    DGLU_API extern const char dg_forthstarslashname[];
    
    DGLU_API void dg_forthstarslash (Bufferhandle* pBHarrayhead);     
    //             ( n1 n2 n3 -- n1*n2/n3 )
    
    
    DGLU_API extern const char dg_forthstarslashmodname[];
    
    DGLU_API void dg_forthstarslashmod (Bufferhandle* pBHarrayhead);  
    //                ( n1 n2 n3 -- remainder n1*n2/n3 )
    
    
    DGLU_API extern const char dg_forthplusname[];            
    
    DGLU_API void dg_forthplus (Bufferhandle* pBHarrayhead);          
    //        ( n1 n2 -- n1+n2 )
    
    
    DGLU_API extern const char dg_forthplusstorename[];
    
    DGLU_API void dg_forthplusstore (Bufferhandle* pBHarrayhead);
    //             ( n1 addr -- )
    
    
    DGLU_API extern const char dg_checkplusloopdonename[];   
    
    DGLU_API UINT64 dg_checkplusloopdone (Bufferhandle* pBHarrayhead);
    //                             ( index limit -r- | index limit )
    //                             ( loopstep -- )
    
    
    DGLU_API extern const char dg_forthplusloopname[];
    
    DGLU_API void dg_forthplusloop (Bufferhandle* pBHarrayhead);
    //            ( do-sys -- )
    //            ( compiles code that does: ) ( loopstep -- ) 
    //            ( loop-sys1 -controlflowstack- ) if loop ends
    //            ( loop-sys1 -controlflowstack- loop-sys1' ) if loop does not end
    
    
    DGLU_API extern const char dg_forthcommaname[]; 
    
    DGLU_API void dg_forthcomma (Bufferhandle* pBHarrayhead);
    //         ( n1 -- )
    //         ( -currentcompilebuffer- n1 )
    
    
    DGLU_API extern const char dg_forthminusname[];
    
    DGLU_API void dg_forthminus (Bufferhandle* pBHarrayhead);         
    //         ( n1 n2 -- n1-n2 )
    
    
    DGLU_API extern const char dg_forthdotname[];
    
    DGLU_API void dg_forthdot (Bufferhandle* pBHarrayhead);
    //            ( n1 -- )
    
    
    DGLU_API extern const char dg_forthdotquotesname[];
    
    DGLU_API void dg_forthdotquotes (Bufferhandle* pBHarrayhead); // compiling routine
    //                  ( "stuff<quotes>morestuff" -currentinputbuffer- "morestuff" )
    
    
    DGLU_API extern const char dg_forthdotrname[];
    
    DGLU_API void dg_forthdotr (Bufferhandle* pBHarrayhead);
    //            ( n1 n2 -- )
    
       
    DGLU_API extern const char dg_forthslashname[];
    
    DGLU_API void dg_forthslash (Bufferhandle* pBHarrayhead);         
    //         ( n1 n2 -- n1/n2 )
    
    
    DGLU_API extern const char dg_forthslashmodname[];
    
    DGLU_API void dg_forthslashmod (Bufferhandle* pBHarrayhead);      
    //            ( n1 n2 -- remainder quotient )
    
    
    DGLU_API extern const char dg_forthzerolessname[];
    
    DGLU_API void dg_forthzeroless (Bufferhandle* pBHarrayhead);      
    //            ( n1 -- flag )
    
    
    DGLU_API extern const char dg_forthzeroequalsname[];
    
    DGLU_API void dg_forthzeroequals (Bufferhandle* pBHarrayhead);    
    //              ( n1 -- flag )
    
    
    DGLU_API extern const char dg_forthoneplusname[];
    
    DGLU_API void dg_forthoneplus (Bufferhandle* pBHarrayhead);       
    //           ( n1 -- n1++ )
    
    
    DGLU_API extern const char dg_forthoneminusname[];
    
    DGLU_API void dg_forthoneminus (Bufferhandle* pBHarrayhead);      
    //            ( n1 -- n1-1 )
    
    
    DGLU_API extern const char dg_forthtwostorename[];
    
    DGLU_API void dg_forthtwostore (Bufferhandle* pBHarrayhead);
    //            ( n1 n2 addr -- )
    
    
    DGLU_API extern const char dg_forthtwostarname[];
    
    DGLU_API void dg_forthtwostar (Bufferhandle* pBHarrayhead);      
    //           ( n1 -- n1*2 )
    
    
    DGLU_API extern const char dg_forthtwoslashname[];
    
    DGLU_API void dg_forthtwoslash (Bufferhandle* pBHarrayhead);     
    //            ( n1 -- n1/2 )
    
    
    DGLU_API extern const char dg_forthtwofetchname[];
    
    DGLU_API void dg_forthtwofetch (Bufferhandle* pBHarrayhead);
    //            ( addr -- n1 n2 )
    
    
    DGLU_API extern const char dg_forthtwodropname[];
    
    DGLU_API void dg_forthtwodrop (Bufferhandle* pBHarrayhead);       
    //           ( n1 n2 -- )
    
    
    DGLU_API extern const char dg_forthtwodupname[];
    
    DGLU_API void dg_forthtwodup (Bufferhandle* pBHarrayhead);        
    //          ( n1 n2 -- n1 n2 n1 n2 )
    
    
    DGLU_API extern const char dg_forthtwoovername[];
    
    DGLU_API void dg_forthtwoover (Bufferhandle* pBHarrayhead);       
    //           ( n1 n2 n3 n4 -- n1 n2 n3 n4 n1 n2 )
    
    
    DGLU_API extern const char dg_forthtwoswapname[];
    
    DGLU_API void dg_forthtwoswap (Bufferhandle* pBHarrayhead);       
    //           ( n1 n2 n3 n4 -- n3 n4 n1 n2 )
    
    
    DGLU_API extern const char dg_forthcolonname[];
    
    DGLU_API void dg_forthcolon (Bufferhandle* pBHarrayhead);
    //              ( "<delimiters>name<delimiters>morestuff" -currentinputbuffer- "spaces<morestuff>" )
    //              ( -- colonsys )
    
    
 #define dg_forthsemicolonnamelength (1)   
    DGLU_API extern const char dg_forthsemicolonname[];
    
    DGLU_API void dg_forthsemicolon (Bufferhandle* pBHarrayhead);
    //                  ( colonsys -- )
    
    
    DGLU_API extern const char dg_forthlessthanname[];
    
    DGLU_API void dg_forthlessthan (Bufferhandle* pBHarrayhead);      
    //            ( n1 n2 -- flag )
    
    
    
    DGLU_API extern const char dg_forthlessthannumbersignname[];
    
    DGLU_API void dg_forthlessthannumbersign (Bufferhandle* pBHarrayhead);
    //                      ( -- )
    //                      ( "number$" -pad- )
    
    
    DGLU_API extern const char dg_forthequalsname[];
    
    DGLU_API void dg_forthequals (Bufferhandle* pBHarrayhead);
    //          ( n1 n2 -- flag )
    
    
    DGLU_API extern const char dg_forthgreaterthanname[];
    
    DGLU_API void dg_forthgreaterthan (Bufferhandle* pBHarrayhead);   
    //               ( n1 n2 -- flag )
    
    
    DGLU_API extern const char dg_forthtobodyname[];
    
    DGLU_API void dg_forthtobody (Bufferhandle* pBHarrayhead); 
    //          ( executiontoken -- address )
    
    
    DGLU_API extern const char dg_forthtoinname[];
    
    DGLU_API void dg_forthtoin (Bufferhandle* pBHarrayhead);
    //        (  -- addressofcurrentoffset )
    
    
    DGLU_API extern const char dg_forthtonumbername[];
    
    DGLU_API void dg_forthtonumber (Bufferhandle* pBHarrayhead);
    //            ( ud1 c-addr1 u1 -- ud2 c-addr2 u2)
    
    
    DGLU_API extern const char dg_forthtorname[];
    
    DGLU_API void dg_forthtor (Bufferhandle* pBHarrayhead);
    //       ( x1 -- )
    //       ( -r- x1 )
    
    
    DGLU_API extern const char dg_forthquestiondupname[];
    
    DGLU_API void dg_forthquestiondup (Bufferhandle* pBHarrayhead);   
    // ( n1 -- n1 ) if n1 = 0 or 
    // ( n1 -- n1 n1 ) if n1 != 0
    
    
    DGLU_API extern const char dg_forthfetchname[];
    
    DGLU_API void dg_forthfetch (Bufferhandle* pBHarrayhead);
    //         ( address -- data )
    
    
    DGLU_API extern const char dg_forthabortname[];
    
    DGLU_API void dg_forthabort (Bufferhandle* pBHarrayhead);
    //              ( xintegers -- )
    //              ( xintegers -r- )
    
    
    DGLU_API extern const char dg_forthabortquotesname[];
    
    DGLU_API void dg_forthabortquotes (Bufferhandle* pBHarrayhead);
    //                    ( flag -- )
    
    
    DGLU_API extern const char dg_forthabsname[];
    
    DGLU_API void dg_forthabs (Bufferhandle* pBHarrayhead);   
    //               ( n1 -- u1 )
    
    
    DGLU_API extern const char dg_forthacceptname[];
    
    DGLU_API void dg_forthaccept (Bufferhandle* pBHarrayhead);
    //               ( caddr +n1 -- +n2 )
    
    
    DGLU_API extern const char dg_forthalignname[];
    
    DGLU_API void dg_forthalign (Bufferhandle* pBHarrayhead);
    //              ( -- )
    
    
    DGLU_API extern const char dg_forthalignedname[];
    
    DGLU_API void dg_forthaligned (Bufferhandle* pBHarrayhead);
    //                ( addr -- a-addr )
    
    
    DGLU_API extern const char dg_forthallotname[];
    
    DGLU_API void dg_forthallot (Bufferhandle* pBHarrayhead);
    //         ( n1 -- )
    //         ( -currentnewvariablebuffer- +n1bytes )
    
    
    DGLU_API extern const char dg_forthandname[];
    
    DGLU_API void dg_forthand (Bufferhandle* pBHarrayhead);    
    //              ( u1 u2 -- u1&u2 ) funky name to aDGLU_API void using reserved word
    
    
    DGLU_API extern const char dg_forthbasename[];
    
    DGLU_API void dg_forthbase (Bufferhandle* pBHarrayhead);
    //             ( -- a-addr )
    
    
    DGLU_API extern const char dg_forthbeginname[];
    
    DGLU_API void dg_forthbegin (Bufferhandle* pBHarrayhead);
    //              ( -- codespaceoffset )
    
    
    DGLU_API extern const char dg_forthblname[];
    
    DGLU_API void dg_forthbl  (Bufferhandle* pBHarrayhead);    
    //              ( -- space ) a.k.a. bl
    
    
    DGLU_API extern const char dg_forthcstorename[];
    
    DGLU_API void dg_forthcstore (Bufferhandle* pBHarrayhead);
    //          ( char c-addr -- )
    
    
    DGLU_API extern const char dg_forthccommaname[];
    
    DGLU_API void dg_forthccomma (Bufferhandle* pBHarrayhead);
    //          ( char -- )
    
    
    DGLU_API extern const char dg_forthcfetchname[];
    
    DGLU_API void dg_forthcfetch (Bufferhandle* pBHarrayhead);
    //         ( address -- char )
    
    
    DGLU_API extern const char dg_forthcellplusname[];
    
    DGLU_API void dg_forthcellplus (Bufferhandle* pBHarrayhead);
    //            ( a-addr1 -- a-addr2 )
    
    
    DGLU_API extern const char dg_forthcellsname[];
    
    DGLU_API void dg_forthcells (Bufferhandle* pBHarrayhead);
    //         ( n1 -- n1*dg_forthcellsize )
    
    
    DGLU_API extern const char dg_forthcharname[];
    
    DGLU_API void dg_forthchar (Bufferhandle* pBHarrayhead);
    //             ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
    //             ( -- firstcharofword )
    
    
    DGLU_API extern const char dg_forthcharplusname[];
    
    DGLU_API void dg_forthcharplus (Bufferhandle* pBHarrayhead);
    //            ( c-addr1 -- c-addr2 )
    
    
    DGLU_API extern const char dg_forthcharsname[];
    
    DGLU_API void dg_forthchars (Bufferhandle* pBHarrayhead);
    //         ( n1 -- n1*charsize )
    
 
    DGLU_API extern const char dg_forthcmovename[];
    
    DGLU_API void dg_forthcmove (Bufferhandle* pBHarrayhead);
    //             ( addr1 addr2 u -- )
    
    
    DGLU_API extern const char dg_forthcmovetoname[];
    
    DGLU_API void dg_forthcmoveto (Bufferhandle* pBHarrayhead);
    //             ( addr1 addr2 u -- )
    
       
    DGLU_API extern const char dg_forthconstantname[];
    
    DGLU_API void dg_forthconstant (Bufferhandle* pBHarrayhead);
    //                 ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
    //                 ( n1 -- )
    
    
    DGLU_API extern const char dg_forthcountname[];
    
    DGLU_API void dg_forthcount (Bufferhandle* pBHarrayhead);
    //              ( c-addr1 -- c-addr2 u )
    
    
    DGLU_API extern const char dg_forthcrname[];
    
    DGLU_API void dg_forthcr (Bufferhandle* pBHarrayhead);
    //           ( -- )
    
    
    DGLU_API extern const char dg_forthcreatename[];
    
    DGLU_API void dg_forthcreate (Bufferhandle* pBHarrayhead);
    //               ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
    
    
    DGLU_API extern const char dg_forthdecimalname[];
    
    DGLU_API void dg_forthdecimal (Bufferhandle* pBHarrayhead);
    //                    ( -- )
    
    
    DGLU_API extern const char dg_forthdepthname[];
    
    DGLU_API void dg_forthdepth (Bufferhandle* pBHarrayhead);
    //              ( nx ... n2 n1 -- nx ... n2 n1 x )
    
    
    DGLU_API extern const char dg_forthdoname[];
    
    DGLU_API void dg_forthdo (Bufferhandle* pBHarrayhead);
    //           ( -- do-sys )
    
    
    DGLU_API extern const char dg_forthdoesname[];
    
    DGLU_API void dg_forthdoes (Bufferhandle* pBHarrayhead);
    //             ( -- )
    
    
    DGLU_API extern const char dg_forthdropname[];
    
    DGLU_API void dg_forthdrop (Bufferhandle* pBHarrayhead);          
    //        ( n1 -- )
    
    
    DGLU_API extern const char dg_forthdupname[];
    
    DGLU_API void dg_forthdup (Bufferhandle* pBHarrayhead);
    //            ( n1 -- n1 n1)
    
    
    DGLU_API extern const char dg_forthelsename[];
    
    DGLU_API void dg_forthelse (Bufferhandle* pBHarrayhead);
    //             ( ifoffset -- elseoffset )
    
    
    DGLU_API extern const char dg_forthemitname[];
    
    DGLU_API void dg_forthemit (Bufferhandle* pBHarrayhead);          
    //        ( n1 -- )
    
    
    DGLU_API extern const char dg_forthenvironmentqueryname[];
    
    DGLU_API void dg_forthenvironmentquery (Bufferhandle* pBHarrayhead);
    //                    ( c-addr u -- false | i*x true )
    
    
    DGLU_API extern const char dg_forthevaluatename[];
    
    DGLU_API void dg_forthevaluate (Bufferhandle* pBHarrayhead);
    //                 ( c-addr u -- )
    
    
    DGLU_API extern const char dg_forthexecutename[];
    
    DGLU_API void dg_forthexecute (Bufferhandle* pBHarrayhead);
    //                ( executiontoken -- )
    
    
    DGLU_API extern const char dg_forthexitname[];
    
    DGLU_API void dg_forthexit (Bufferhandle* pBHarrayhead);
    //             ( -- )
    
    
    DGLU_API extern const char dg_forthfillname[];
    
    DGLU_API void dg_forthfill (Bufferhandle* pBHarrayhead);
    //             ( c-addr n char -- )
    
    
    DGLU_API extern const char dg_forthfindname[];
    
    DGLU_API void dg_forthfind (Bufferhandle* pBHarrayhead);
    //             ( c-addr -- c-addr 0 ) if word not found
    //             ( c-addr -- xt 1 ) if word found and it is dg_forthimmediate
    //             ( c-addr -- xt -1 ) if word found and it is not dg_forthimmediate
    
    
    DGLU_API extern const char dg_forthfmslashmodname[];
    
    DGLU_API void dg_forthfmslashmod (Bufferhandle* pBHarrayhead);
    //              ( d1 n1 -- n2 n3 )
    
    
    DGLU_API extern const char dg_forthherename[];
    
    DGLU_API void dg_forthhere (Bufferhandle* pBHarrayhead);
    //             ( -- addr )
    
    
    DGLU_API extern const char dg_forthholdname[];
    
    DGLU_API void dg_forthhold (Bufferhandle* pBHarrayhead);
    //        ( char -- )
    
    
    DGLU_API extern const char dg_forthiname[];
    
    DGLU_API void dg_forthi (Bufferhandle* pBHarrayhead);
    //          ( limit index -rstack- limit index )
    //          ( -- index )
    
    
    DGLU_API extern const char dg_forthifname[];
    
    DGLU_API void dg_forthif (Bufferhandle* pBHarrayhead);
    //           ( -- ifoffset )
    
    
    DGLU_API extern const char dg_forthimmediatename[];
    
    DGLU_API void dg_forthimmediate (Bufferhandle* pBHarrayhead);
    //             ( -- )
    
    
    DGLU_API extern const char dg_forthinvertname[];
    
    DGLU_API void dg_forthinvert (Bufferhandle* pBHarrayhead);
    //               ( x1 -- x2 )
    
    
    DGLU_API extern const char dg_forthjname[];
    
    DGLU_API void dg_forthj (Bufferhandle* pBHarrayhead);
    //          ( limit2 index2 limit1 index1 -rstack- limit2 index2 limit1 index1 )
    //          ( -- index2 )
    
    
    DGLU_API extern const char dg_forthkeyname[];
    
    DGLU_API void dg_forthkey (Bufferhandle* pBHarrayhead);
    //            ( -- char )
    
    
    DGLU_API extern const char dg_forthleavename[];
    
    DGLU_API void  dg_forthleave (Bufferhandle* pBHarrayhead);
    //               ( compile: ) ( -- ) ( -leavestack- leaveoffset )
    //               ( compiled code does: ) ( loopsys -rstack- )
    
    
    DGLU_API extern const char dg_forthliteralname[];
    
    DGLU_API void dg_forthliteral (Bufferhandle* pBHarrayhead);
    //                ( n1 -- )
    
    
    DGLU_API extern const char dg_checkloopdonename[];                     
    
    DGLU_API UINT64 dg_checkloopdone (Bufferhandle* pBHarrayhead);
    //                         ( index limit -r- | index limit )
    
    
    DGLU_API extern const char dg_forthloopname[];
    
    DGLU_API void dg_forthloop (Bufferhandle* pBHarrayhead);
    //               ( do-sys -- )
    //               ( compiled code does: ) ( -- )
    //               ( loop-sys1 -controlflowstack- ) if loop ends
    //               ( loop-sys1 -controlflowstack- loop-sys1' ) if loop does not end
    
    
    DGLU_API extern const char dg_forthlshiftname[];
    
    DGLU_API void dg_forthlshift (Bufferhandle* pBHarrayhead);
    //          ( x1 u -- x2 )
    
    
    DGLU_API extern const char dg_forthmstarname[];
    
    DGLU_API void dg_forthmstar (Bufferhandle* pBHarrayhead);
    //         ( n1 n2 -- d ) 
    
    
    DGLU_API extern const char dg_forthmaxname[];
    
    DGLU_API void dg_forthmax (Bufferhandle* pBHarrayhead);    
    //             ( n1 n2 -- n3 )
    
    
    DGLU_API extern const char dg_forthminname[];
    
    DGLU_API void dg_forthmin (Bufferhandle* pBHarrayhead);    
    //             ( n1 n2 -- n3 )
    
    
    DGLU_API extern const char dg_forthmodname[];
    
    DGLU_API void dg_forthmod (Bufferhandle* pBHarrayhead);           
    //            ( n1 n2 -- n1modn2 )
    
    
    DGLU_API extern const char dg_forthmovename[];
    
    DGLU_API void dg_forthmove (Bufferhandle* pBHarrayhead);
    //             ( addr1 addr2 u -- )
    
    
    DGLU_API extern const char dg_forthnegatename[];
    
    DGLU_API void dg_forthnegate (Bufferhandle* pBHarrayhead); 
    //               ( n1 -- 0-n1 ) 
    
    
    DGLU_API extern const char dg_forthorname[];
    
    DGLU_API void dg_forthor (Bufferhandle* pBHarrayhead);  
    //           ( x1 x2 -- x3 )
    
    
    DGLU_API extern const char dg_forthovername[];
    
    DGLU_API void dg_forthover (Bufferhandle* pBHarrayhead);          
    //        ( n1 n0 -- n1 n0 n1 )
    
    
    DGLU_API extern const char dg_forthpostponename[];
    
    DGLU_API void dg_forthpostpone (Bufferhandle* pBHarrayhead);
    //            (compile mode)
    //            ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
    
    
    DGLU_API extern const char dg_forthquitname[];
    
    DGLU_API void dg_forthquit (Bufferhandle* pBHarrayhead);
    //             ( rx ... r1 r0 -r- )
    
    
    DGLU_API extern const char dg_forthrfromname[];
    
    DGLU_API void dg_forthrfrom (Bufferhandle* pBHarrayhead);
    //         ( x1 -r- )
    //         ( -- x1 )
    
    
    DGLU_API extern const char dg_forthrfetchname[];
    
    DGLU_API void dg_forthrfetch (Bufferhandle* pBHarrayhead);
    //          ( x1 -r- x1 )
    //          ( -- x1 )
    
    
    DGLU_API extern const char dg_forthrecursename[];
    
    DGLU_API void dg_forthrecurse (Bufferhandle* pBHarrayhead);
    //           ( -- )
    
    
    DGLU_API extern const char dg_forthrepeatname[];
    
    DGLU_API void dg_forthrepeat (Bufferhandle* pBHarrayhead);
    //               ( whileoffset beginoffset -- )
    
    
    DGLU_API extern const char dg_forthrotname[];
    
    DGLU_API void dg_forthrot (Bufferhandle* pBHarrayhead);           
    //       ( n1 n2 n3 -- n2 n3 n1 )
    
    
    DGLU_API extern const char dg_forthrshiftname[];
    
    DGLU_API void dg_forthrshift (Bufferhandle* pBHarrayhead);        
    //          ( n1 u -- n2 )
    
    
    DGLU_API extern const char dg_forthsquotesname[];
    
    DGLU_API void dg_forthsquotes (Bufferhandle* pBHarrayhead); // ( S" )
    //           ( "somestuff<rightdg_forthparen>morestuff" -currentinputbuffer- "morestuff" )
    //           ( -- caddr u  )
    
    
    DGLU_API extern const char dg_forthstodname[];
    
    DGLU_API void dg_forthstod (Bufferhandle* pBHarrayhead);
    //        ( n -- d )
 
 
    DGLU_API extern const char dg_forthscreatename[];
       
    DGLU_API void dg_forthscreate (Bufferhandle* pBHarrayhead);
    //               ( c-addr u -- )
    
    
    DGLU_API extern const char dg_forthsignname[];
    
    DGLU_API void dg_forthsign (Bufferhandle* pBHarrayhead);
    //             ( n -- )
    
    
    DGLU_API extern const char dg_forthsmslashremname[];
    
    DGLU_API void dg_forthsmslashrem (Bufferhandle* pBHarrayhead);
    //              ( d1 n1 -- n2 n3 )
    
    
    DGLU_API extern const char dg_forthsourcename[];
    
    DGLU_API void dg_forthsource (Bufferhandle* pBHarrayhead);
    //               ( -- caddr u )
    
    
    DGLU_API extern const char* dg_forthspaceputcerror;
    
    DGLU_API extern const char dg_forthspacename[];
    
    DGLU_API void dg_forthspace (Bufferhandle* pBHarrayhead);         
    //              ( -- )
    
    
    DGLU_API extern const char dg_forthspacesname[];
    
    DGLU_API void dg_forthspaces (Bufferhandle* pBHarrayhead);        
    //               ( n -- )
    
    
    DGLU_API extern const char dg_forthstatename[];
    
    DGLU_API void dg_forthstate (Bufferhandle* pBHarrayhead);
    //              ( -- a-addr )
    
    
    DGLU_API extern const char dg_forthswapname[];
    
    DGLU_API void dg_forthswap (Bufferhandle* pBHarrayhead);          
    //        ( n1 n2 -- n2 n1 )
    
    
    DGLU_API extern const char dg_forththenname[];
    
    DGLU_API void dg_forththen (Bufferhandle* pBHarrayhead);
    //             ( ifoffset -- )
    
    
    DGLU_API extern const char dg_forthtypename[];
    
    DGLU_API void dg_forthtype (Bufferhandle* pBHarrayhead);
    //             ( c-addr u -- )
    
    
    DGLU_API extern const char dg_forthudotname[];
    
    DGLU_API void dg_forthudot (Bufferhandle* pBHarrayhead);
    //        ( u -- )
    
    
    DGLU_API extern const char dg_forthulessthanname[];
    
    DGLU_API void dg_forthulessthan (Bufferhandle* pBHarrayhead);     
    //             ( u1 u2 -- flag )
    
    
    DGLU_API extern const char dg_forthumstarname[];
    
    DGLU_API void dg_forthumstar (Bufferhandle* pBHarrayhead);        
    //          ( u1 u2 -- ud )
    
    
    DGLU_API extern const char dg_forthumslashmodname[];
    
    DGLU_API void dg_forthumslashmod (Bufferhandle* pBHarrayhead);    
    //              ( ud u1 -- u2 u3 )
    
    
    DGLU_API extern const char dg_forthunloopname[];
    
    DGLU_API void dg_forthunloop (Bufferhandle* pBHarrayhead);
    //               ( limit index -rstack- )
    
    
    DGLU_API extern const char dg_forthuntilname[];
    
    DGLU_API void dg_forthuntil (Bufferhandle* pBHarrayhead);
    //              ( beginoffset -- )
    
    
    DGLU_API extern const char dg_forthvariablename[];
    
    DGLU_API void dg_forthvariable (Bufferhandle* pBHarrayhead);
    //                 ( "<spaces>word<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
    //                 ( -currentnewvariablebuffer- +sizeofunsignedint )
    
    
    DGLU_API extern const char dg_forthwhilename[];
    
    DGLU_API void dg_forthwhile (Bufferhandle* pBHarrayhead);
    //              ( beginoffset -- whileoffset beginoffset )
    
    
    DGLU_API extern const char dg_forthwordname[];
    
    DGLU_API void dg_forthword (Bufferhandle* pBHarrayhead);
    //        ( "<chars>word<char>morestuff" -currentinputbuffer- "<char>morestuff")
    //        ( char -- c-addr )
    //        ( -wordbuffer- "word" )
    
    
    DGLU_API extern const char dg_forthxorname[];
    
    DGLU_API void dg_forthxor (Bufferhandle* pBHarrayhead);  
    //            ( x1 x2 -- x3 )      
    
    
    DGLU_API extern const char dg_forthleftbracketname[];
    
    DGLU_API void dg_forthleftbracket (Bufferhandle* pBHarrayhead);
    //                   ( -- )
    
    
    DGLU_API extern const char dg_forthbrackettickname[];
    
    DGLU_API void dg_forthbrackettick (Bufferhandle* pBHarrayhead);
    // ( "<spaces>name<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
    // ( -- )
    // ( compiled code does: ) ( -- executiontokenofname )
    
    
    DGLU_API extern const char dg_forthbracketcharname[];
    
    DGLU_API void dg_forthbracketchar (Bufferhandle* pBHarrayhead);
    // ( "<spaces>name<spaces>morestuff" -currentinputbuffer- "<spaces>morestuff" )
    // ( -- )
    // ( compiled code does: ) ( -- firstcharofname )
    
    
    DGLU_API extern const char dg_forthrightbracketname[];
    
    DGLU_API void dg_forthrightbracket (Bufferhandle* pBHarrayhead);
    //                   ( -- )
    
    
    // ///////////////////////////
    // end of core FORTH words  // 
    // ///////////////////////////
    
    
    // //////////////////////////////
    // Forth Core Extension words  //
    // //////////////////////////////
    
    DGLU_API extern const char dg_forthnumbertibname[];

    DGLU_API void dg_forthnumbertib (Bufferhandle* pBHarrayhead);
    //             ( -- a-addr )
    
    
    DGLU_API extern const char dg_forthzeronotequalsname[];
    
    DGLU_API void dg_forthzeronotequals (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char dg_forthzerogreatername[];
    
    DGLU_API void dg_forthzerogreater (Bufferhandle* pBHarrayhead);      
    //             ( n1 -- flag )
    
    
    DGLU_API extern const char dg_forthdotparenname[];
    
    DGLU_API void dg_forthdotparen (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char dg_forthtwotorname[];
    
    DGLU_API void dg_forthtwotor (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char dg_forthtworfetchname[];
    
    DGLU_API void dg_forthtworfetch (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char dg_forthtworfromname[];
    
    DGLU_API void dg_forthtworfrom (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char dg_forthcolonnonamename[];
    
    DGLU_API void dg_forthcolonnoname (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char dg_forthcquotename[];
    
    DGLU_API void dg_forthcquote (Bufferhandle* pBHarrayhead);


    DGLU_API extern const char dg_forthquerydoname[];

    DGLU_API void dg_forthquerydo (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char dg_forthagainname[];

    DGLU_API void dg_forthagain (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char dg_forthnotequalsname[];
    
    DGLU_API void dg_forthnotequals (Bufferhandle* pBHarrayhead);
    //             ( n1 n2 -- flag )
    
    
    DGLU_API extern const char dg_fortherasename[];
    
    DGLU_API void dg_fortherase (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthhex (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthnip (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthpad (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthroll (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthugreaterthan (Bufferhandle* pBHarrayhead);     
    //             ( u1 u2 -- flag )
    

    DGLU_API void dg_forthtib (Bufferhandle* pBHarrayhead);
    //             ( -- a-addr )
    
    
    DGLU_API void dg_forthtuck (Bufferhandle* pBHarrayhead);
    //             ( u1 u2 -- u2 u1 u2 )
    
    
    // //////////////////////
    // Forth String Words  //
    // //////////////////////
    
    DGLU_API void dg_forthdashtrailing (Bufferhandle* pBHarrayhead);
    //            ( c-addr1 u1 -- c-addr2 u2 )   
    
    DGLU_API void dg_forthcompiles (Bufferhandle* pBHarrayhead);
    //            ( addr u -- )
    //            ( dcompiles copy of string at addr u and code that does: ( -- addr' u )
 
 
    DGLU_API void dg_forthblank (Bufferhandle* pBHarrayhead);
    //            ( addr u -- )   

    // ////////////////////////////////
    // Forth string extension words  //
    // ////////////////////////////////
       
    DGLU_API void dg_forthslashstring (Bufferhandle* pBHarrayhead);
    //               ( caddr1 u1 n1 -- caddr2 u2 )   
       
    DGLU_API void dg_forthsearch (Bufferhandle* pBHarrayhead);
    //               ( caddr1 u1 caddr2 u2 -- caddr3 u3 flag )
    
    DGLU_API void dg_forthcompare (Bufferhandle* pBHarrayhead);
    //               ( caddr1 u1 caddr2 u2 -- flag )
       
    
    // //////////////////////
    // Search-Order words  // 
    // //////////////////////
    
    
    DGLU_API void dg_forthdefinitions (Bufferhandle* pBHarrayhead);
    //               ( -- )
    
    
    // see dg_forthfind
    
    DGLU_API void dg_forthgetcurrent (Bufferhandle* pBHarrayhead);
    //              ( -- currentcompilewordlistid )
    
    
    DGLU_API void dg_forthgetorder (Bufferhandle* pBHarrayhead);
    //            ( -- wordlistidn ... wordlistid1 n )
    
    
    DGLU_API void dg_forthsearchwordlist (Bufferhandle* pBHarrayhead); 
    //             ( c-addr u wid -- 0 ) if word not found
    //             ( c-addr u wid -- xt 1 ) if word found and it is dg_forthimmediate
    //             ( c-addr u wid -- xt -1 ) if word found and it is not dg_forthimmediate
    
    
    DGLU_API void dg_forthsetcurrent (Bufferhandle* pBHarrayhead);
    //              ( wordlistid -- )
    
    
    DGLU_API void dg_forthsetorder (Bufferhandle* pBHarrayhead);
    //            ( wordlistidn ... wordlistid1 n -- )
    
    
    DGLU_API void dg_forthwordlist (Bufferhandle* pBHarrayhead);
    //               ( -- wordlistid )
    
    
    ///////////////////////////////
    // End of search-order words // 
    ///////////////////////////////
    
    
    
    // /////////////////////////////
    // Forth Double Number Words  //
    // /////////////////////////////
    

    DGLU_API void dg_forthtwoconstant (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthtwoliteral (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthtworot (Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_forthtwovariable (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdabs (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdlessthan (Bufferhandle* pBHarrayhead); 
    
    
    DGLU_API void dg_forthdequals (Bufferhandle* pBHarrayhead); 
 
 
    DGLU_API void dg_forthdtos (Bufferhandle* pBHarrayhead);   
 
 
    DGLU_API void dg_forthdplus (Bufferhandle* pBHarrayhead);
    
    
    // DGLU_API void dg_forthdstar (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdminus (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthddot (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthddotr (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdzeroless (Bufferhandle* pBHarrayhead); 
    
    
    DGLU_API void dg_forthdzeroequals (Bufferhandle* pBHarrayhead);  
    
    
    DGLU_API void dg_forthdtwostar (Bufferhandle* pBHarrayhead); 
    
    
    DGLU_API void dg_forthdtwoslash (Bufferhandle* pBHarrayhead); 
    
    
    DGLU_API void dg_forthdmax (Bufferhandle* pBHarrayhead);  
    
    
    DGLU_API void dg_forthdmin (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdnegate (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdulessthan (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthmplus (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthmstarslash (Bufferhandle* pBHarrayhead);
    
    
    // ////////////////////////////////////
    // End of Forth Double Number Words  //
    // ////////////////////////////////////
    
 
    // //////////////////////////////
    // Forth Floating Point Words  //
    // //////////////////////////////
 
     
    DGLU_API void dg_forthtofloat (Bufferhandle* pBHarrayhead); 
    
    DGLU_API void dg_forthdtof (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthfliteral (Bufferhandle* pBHarrayhead); 
    
    DGLU_API void dg_forthfstore (Bufferhandle* pBHarrayhead); 
    
    DGLU_API void dg_forthfstar (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthfstarstar (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthfplus (Bufferhandle* pBHarrayhead);
    
     DGLU_API void dg_forthfminus (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfslash (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfzerolessthan (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfzeroequals (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthflessthan (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthffetch (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthftos (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfabs (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfalign (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfaligned (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfalog (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfacos (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfacosh (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfasin (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfasinh (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfatan (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfatan2 (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfatanh (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfconstant (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfcos (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfcosh (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfdepth (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfdrop (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfdup (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfexp (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfexpm1 (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfln (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthflnp1 (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfloatplus (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfloats (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthflog (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfloor (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfmax (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfmin (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfnegate (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfover (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfproximate (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfrot (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfround (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfsin (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfsinh (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfsincos (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfsqrt (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthfswap (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthftan (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthftanh (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthprecision (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthrepresent (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthstof (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthsetprecision (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthsfstore (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthsffetch (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthsfalign (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthsfaligned (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthsfloatplus (Bufferhandle* pBHarrayhead);
     
     DGLU_API void dg_forthsfloats (Bufferhandle* pBHarrayhead);

     DGLU_API void dg_forthf64comma (Bufferhandle* pBHarrayhead);
     
    
    // /////////////////////////////////////
    // End of Forth Floating Point Words  //
    // /////////////////////////////////////
    
    
    // //////////////////////////
    // FORTH Definition Words  //
    // //////////////////////////
    
    
    DGLU_API void dg_forthnewdefinition (Bufferhandle* pBHarrayhead);
    //                ( compilebufid compilebufoffset databufid databufoffset pname namelength -- executiontoken )
    
    
    DGLU_API void dg_forthgetswordhead (Bufferhandle* pBHarrayhead);
    //                ( executiontoken -- pwordhead wordheadlength )
    
    
    DGLU_API void dg_forthtohead (Bufferhandle* pBHarrayhead);
    //                ( executiontoken -- pwordhead )
    
    
    DGLU_API void dg_forthlinkdefinition (Bufferhandle* pBHarrayhead);
    //                ( executiontoken wordlistid -- )
    
    
    DGLU_API void dg_forthnewsubroutinedefinition (Bufferhandle* pBHarrayhead);
    //               ( pname namelength -- executiontoken )
    
    
    DGLU_API void dg_forthnewvariabledefinition (Bufferhandle* pBHarrayhead);
    //               ( pname namelength -- executiontoken );
    
    
    DGLU_API void dg_forthnewconstantdefinition (Bufferhandle* pBHarrayhead);
    //              ( constant pname namelength -- executiontoken )
    
    
    DGLU_API void dg_forthgetnewestdefinitioninwordlist (Bufferhandle* pBHarrayhead);
    //              ( wordlistid -- executiontoken )
    
    
    DGLU_API void dg_forthgetnextdefinition (Bufferhandle* pBHarrayhead);
    //              ( executiontoken -- nextexecutiontoken )
    
    
    DGLU_API void dg_forthfinddefinitioninwordlist (Bufferhandle* pBHarrayhead);
    //              ( wordlistid pname namelength -- executiontoken )
    
    
    DGLU_API void dg_forthfinddefinitioninsearchorder (Bufferhandle* pBHarrayhead);
    //              ( pname namelength -- executiontoken )
    
    
    DGLU_API void dg_forthputnewestdefinitioncompiletype (Bufferhandle* pBHarrayhead);
    //              ( compilebuffoffset compilebufid -- )
    
    
    DGLU_API void dg_forthgetcompileroutine (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthsetcompileroutine (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthgetodf (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthsetodf (Bufferhandle* pBHarrayhead);
 
 
    DGLU_API void dg_forthtocurrent (Bufferhandle* pBHarrayhead);   


    DGLU_API void dg_forthcurrentfrom (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthsearchorderdrop (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthbrackettoorderconstant (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthwordlistdot(Bufferhandle* pBHarrayhead);


    DGLU_API void dg_forthlibdot(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcreatebracketwordlistdot(Bufferhandle* pBHarrayhead);

    
    DGLU_API void dg_forthcreatebracketlibdot(Bufferhandle* pBHarrayhead);
    
         
    // /////////////////////////////////
    // End of FORTH Definition Words  //
    // /////////////////////////////////
    
    
    DGLU_API void dg_initwordlists (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthbye (Bufferhandle* pBHarrayhead);
 
 
    DGLU_API void dg_forthsynonym (Bufferhandle* pBHarrayhead);   
    
 
    DGLU_API void dg_forthcode (Bufferhandle* pBHarrayhead); 
    
    
    DGLU_API void dg_forthemptywordlist (Bufferhandle* pBHarrayhead); 
    
    
    DGLU_API void dg_forthrandom (Bufferhandle* pBHarrayhead); 
    
    
    DGLU_API void dg_forthcompileu8s (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcompileu8scurly (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthconstantscurly (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthfconstantscurly (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthlocalconstants (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthlocalconstantscurly (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthvariablescurly (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthvariables (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthconstants (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthfconstants (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthsizedconstantscurly (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthenumcurly (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthlocalenumcurly (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthbracketlocalenumcurly (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthtypedenumcurly (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthtypedlocalenumcurly (Bufferhandle* pBHarrayhead);


    DGLU_API void dg_forthbenchmark(Bufferhandle* pBHarrayhead);
    
    
    // //////////////////////
    // FORTH Buffer Words  //
    // //////////////////////
    
    
    DGLU_API void dg_forthocfetch (Bufferhandle* pBHarrayhead);
   
    DGLU_API void dg_forthofetch (Bufferhandle* pBHarrayhead);
  
    DGLU_API void dg_forthostonewstring (Bufferhandle* pBHarrayhead);
  
    DGLU_API void dg_forthocstore (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthostore (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthotwostore (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthctobuf (Bufferhandle* pBHarrayhead);
   
    DGLU_API void dg_forthtobuf (Bufferhandle* pBHarrayhead);   
    
    DGLU_API void dg_forthstringtobuf (Bufferhandle* pBHarrayhead);
  
    DGLU_API void dg_forthbuftoc (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthbufto (Bufferhandle* pBHarrayhead); 
    
    DGLU_API void dg_forthbuftostring (Bufferhandle* pBHarrayhead);  
    
    DGLU_API void dg_forthosstore (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthosfetch (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthstobuf (Bufferhandle* pBHarrayhead);    
    
    DGLU_API void dg_forthbuftos (Bufferhandle* pBHarrayhead);    
    
    DGLU_API void dg_forthlengthbuf (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgetsbufferhandlearrayhead (Bufferhandle* pBHarrayhead);    
    
    DGLU_API void dg_forthgetsbufferhandle (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgetoarrayelement (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgetparrayelement (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgetbuffersize (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgetbuffermaxsize (Bufferhandle* pBHarrayhead);    
    
    DGLU_API void dg_forthgetbuffergrowby (Bufferhandle* pBHarrayhead);    
    
    DGLU_API void dg_forthgetbuffercurrentoffset (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthputbuffercurrentoffset (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgetpbufferlength (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgetpbuffercurrentoffset (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthinsertinbuffer (Bufferhandle* pBHarrayhead);    
    
    DGLU_API void dg_forthdeleteinbuffer (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthreplaceinbuffer (Bufferhandle* pBHarrayhead);  
    
    DGLU_API void dg_forthinsertsintobuffer (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgrowbuffer (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthshrinkbuffer (Bufferhandle* pBHarrayhead);
  
    DGLU_API void dg_forthemptybuffer (Bufferhandle* pBHarrayhead);
 
    DGLU_API void dg_forthnewbuffer (Bufferhandle* pBHarrayhead);
  
    DGLU_API void dg_forthfreebuffer (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthgetpbufferoffset (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthgetpbuffer (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthgetsbuffer (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthgetpbuffersegment (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthlinecomment (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthparse (Bufferhandle* pBHarrayhead);
 
    DGLU_API void dg_forthlinesparse (Bufferhandle* pBHarrayhead);   
 
    DGLU_API void dg_forthparsebuffer (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthparseword (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthparsewords (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthlinesparsenames (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthparseline (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthcscanbuf (Bufferhandle* pBHarrayhead);
  
    DGLU_API void dg_forthscanbuf (Bufferhandle* pBHarrayhead);
 
    DGLU_API void dg_forthmaxusedbuffers (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthinusebuffers (Bufferhandle* pBHarrayhead);
  
    DGLU_API void dg_forthinusebytes (Bufferhandle* pBHarrayhead);
  
    DGLU_API void dg_forthallocatedbytes (Bufferhandle* pBHarrayhead);
   
    DGLU_API void dg_forthgetpnewbuffer(Bufferhandle* pBHarrayhead);
       
    DGLU_API void dg_forthu16store (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthu32store (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthu16fetch (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthu32fetch (Bufferhandle* pBHarrayhead);
        
    DGLU_API void dg_forthu32comma (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthof64store (Bufferhandle* pBHarrayhead);
    
    
    // /////////////////////////////
    // End of FORTH Buffer Words  //
    // /////////////////////////////
    
    
    // ///////////////////////
    // FORTH Lstring Words  //
    // ///////////////////////
    
    
    DGLU_API void dg_forthdepthlstring(Bufferhandle* pBHarrayhead);  // LSTRINGSTACKDEPTH ?
    //                              ( stringoffsetbufferid -- n );
    //                              ( endoffset$1 endoffset$2 ... endoffset$n -offsetbuffer- 
    //                                  endoffset$1 endoffset$2 ... endoffset$n ) 
    
    
    DGLU_API void dg_forthstartoffsetlstring (Bufferhandle *pBHarrayhead);
    //                          ( stringid stringoffsetbufferid -- lstringstartoffset )
    //                          ( endoffset$1 endoffset$2 ... endoffset$stringid ... endoffset$n -offsetbuffer- 
    //                              endoffset$1 endoffset$2 ... endoffset$stringid ... endoffset$n )
    
    
    DGLU_API void dg_forthlengthlstring (Bufferhandle *pBHarrayhead);
    //                     ( stringid stringoffsetbufferid -- lstringlength )
    //                          ( endoffset$1 endoffset$2 ... endoffset$stringid ... endoffset$n -offsetbuffer- 
    //                              endoffset$1 endoffset$2 ... endoffset$stringid ... endoffset$n )                     
    
    
    DGLU_API void dg_forthgetslstringn(Bufferhandle* pBHarrayhead);
    //               ( stringid offsetbufferid stringbufferid -- plstring lstringlength )
    //               ( $0 $1 ... $stringid ... $n -offsetbuffer&stringbuffer- $0 $1 ... $stringid ... $n )
    
    
    DGLU_API void dg_forthgetlstring (Bufferhandle* pBHarrayhead);
    //               ( stringid offsetbufferid stringbufferid pdest maxlength -- )
    //               ( $0 $1 ... $stringid ... $n -offsetbuffer&stringbuffer- $0 $1 ... $stringid ... $n )
    
    
    DGLU_API void dg_forthlstringtos (Bufferhandle* pBHarrayhead);
    //               ( offsetbufferid stringbufferid pdest maxlength -- )
    //               ( l$ -offsetbuffer&stringbuffer- )
    
    
    DGLU_API void dg_forthstolstring (Bufferhandle* pBHarrayhead);
    //                ( psrc length offsetbufferid stringbufferid -- )
    //                ( -offsetbuffer&stringbuffer- l$ )
    
    
    DGLU_API void dg_forthgrowlstring (Bufferhandle* pBHarrayhead);
    //                ( n offsetbufferid stringbufferid -- )
    //                ( $1 -offsetbuffer&stringbuffer- l$' )
    
    
    DGLU_API void dg_forthshortenlstring ( Bufferhandle* pBHarrayhead );
    
    
    DGLU_API void dg_forthpicklstring (Bufferhandle* pBHarrayhead);
    //                ( n offsetbufferid stringbufferid -- )
    //                ( $n $n-1 ... $1 $0 -offsetbuffer&stringbuffer- $n $n-1 ... $1 $0 $n )
    
    
    DGLU_API void dg_forthdroplstring (Bufferhandle* pBHarrayhead);
    //                ( offsetbufferid stringbufferid -- )
    //                ( l$ -offsetbuffer&stringbuffer- )
    
    
    DGLU_API void dg_forthdeletelstring (Bufferhandle* pBHarrayhead);
    //                  ( stringid offsetbufferid stringbufferid -- )
    //                  ( $0 $1 ... $stringid ... $n -offsetbuffer&stringbuffer- $0 $1 ... $n )
    
    
    DGLU_API void dg_forthinsertlstring (Bufferhandle* pBHarrayhead);
    //                ( psrc length n offsetbufferid stringbufferid -- )
    //                ( L$0 L$1 L$2 ... L$N ... L$TOP -offsetbuffer&stringbuffer- 
    //                    L$0 L$1 L$2 ... copyL$psrc L$N ... L$TOP )
    
    
    DGLU_API void dg_forthnewlstring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthrolllstring (Bufferhandle* pBHarrayhead);
    //             ( nd offsetbufferid stringbufferid -- )
    //             ( l$depth-1{bottom} ... l$nd+1 l$nd l$nd-1 ... l$1 l$0{top} -l$- 
    //                 l$depth-1{bottom} ... l$nd+1 l$nd-1 ... l$1 l$0 l$nd )
    
    
    DGLU_API void dg_forthminusrolllstring (Bufferhandle* pBHarrayhead);
    //             ( nd offsetbufferid stringbufferid -- )
    //             ( l$depth-1{bottom} ... l$nd+1 l$nd l$nd-1 ... l$1 l$0{top} -l$- 
    //                 l$depth-1{bottom} ... l$nd+1 l$0{top} l$nd l$nd-1 ... l$1 )
    
    
    DGLU_API void dg_forthdeleteinlstring (Bufferhandle* pBHarrayhead);
    //             ( offset length n offsetbufferid stringbufferid -- )
    //             ( l$depth-1{bottom} ... l$nd+1 l$nd l$nd-1 ... l$1 l$0{top} -l$- 
    //                 l$depth-1{bottom} ... l$nd+1 l$nd' l$nd-1 ... l$1 l$0{top} )
    
    
    DGLU_API void dg_forthinsertinlstring (Bufferhandle* pBHarrayhead);
    //             ( offset length n offsetbufferid stringbufferid -- )
    //             ( l$depth-1{bottom} ... l$nd+1 l$nd l$nd-1 ... l$1 l$0{top} -l$- 
    //                 l$depth-1{bottom} ... l$nd+1 l$nd' l$nd-1 ... l$1 l$0{top} )
    
    
    DGLU_API void dg_forthcatlstringn (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcopystolstringn (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcopysfromlstringn (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthsetlengthlstringn (Bufferhandle* pBHarrayhead);
    //             ( newlength n offsetbufferid stringbufferid -- )
    
    
    DGLU_API void dg_forthcopystoreplacelstringn (Bufferhandle* pBHarrayhead);
    //             ( psrc length index offsetbufferid stringbufferid -- )
    
    
    DGLU_API void dg_forthcopylstringntoreplacelstringn (Bufferhandle* pBHarrayhead);
    //             ( srcn srcoffsetbufferid srcstringbufferid destn destoffsetbufferid 
    //               deststringbufferid -- )
    
    
    DGLU_API void dg_forthnewfreeablelstringarray (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthfreefreeablelstringarray (Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_forthpacklstring(Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_forthunpacklstring(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthnotlstringn(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthu8reverselstringn(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthuleextendlstringntol(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthuleandlstringntolstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthuleorlstringntolstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthulexorlstringntolstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthulenandlstringntolstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthulenorlstringntolstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthulexnorlstringntolstringn (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthuleaddlstringntolstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthuleadclstringntolstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthulesbblstringntolstringn (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthlelshiftlstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthulershiftlstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthslershiftlstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthlelshiftclstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthlershiftclstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthu64starlstringnplustolstringn (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthtoslashulelstringn (Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_forthgetargsfromnstrings(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthrunfileandwaitnoenvquotessub(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthrunfileandwaitnoenvquotes(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthrunfileandwaitnoenvstring(Bufferhandle* pBHarrayhead);
    
    
    // //////////////////////////////
    // End of Forth Lstring Words  //
    // //////////////////////////////
    
    
    // /////////////////////
    // Forth Error Words  //
    // /////////////////////
    
    // call this O0$>ERROR ?
    DGLU_API void dg_forthpushoerror (Bufferhandle* pBHarrayhead); 
    //                    ( offset bufferid -- )
    //                    ( -error- offset bufferid )
    
    DGLU_API void dg_forthgetoerror (Bufferhandle* pBHarrayhead);
    //             ( offset bufferid -error- )
    //             ( index -- offset bufferid )
    
    // call this ERROR>p0$ ?
    //DGLU_API void dg_forthpoperror (Bufferhandle* pBHarrayhead);
    //             ( offset bufferid -error- )
    //             ( -- pError0$ )
    
    DGLU_API void dg_forthpopoerror (Bufferhandle* pBHarrayhead);
    //             ( offset bufferid -error- )
    //             ( -- offset bufferid )
    
    // also need ERROR>O0$ so comparisons can be done and 2=
    
    // call this GETERRORN ?
    //DGLU_API void dg_forthgeterror (Bufferhandle* pBHarrayhead);
    //             ( errorstackindex - pError0$ )
    
    DGLU_API void dg_forthgeterrorcount (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcheckerrordepth (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdroptoerrorcount (Bufferhandle* pBHarrayhead);
    

    // ////////////////////////////
    // End of Forth Error Words  //
    // //////////////////////////// 
    
    DGLU_API void dg_forthudmslashmod (Bufferhandle* pBHarrayhead);
    //               ( ud u1 -- ud2 rem )
    
    
    DGLU_API void dg_forthpick(Bufferhandle* pBHarrayhead);
    //            ( nidx ... n2 n1 n0 idx -- n2 n1 n0 nidx )
    
    DGLU_API void dg_forthminusrot(Bufferhandle* pBHarrayhead);
    //            ( n1 n2 n3 -- n3 n1 n2 )
    
    DGLU_API void dg_forthodoes (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_callbuffername;
    
    DGLU_API UINT64 dg_callbuffer (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);
    
    
    // DGLU_API void jmpbuffer (DGLU_API void);
    //             ( offset bufferid pBHarrayhead -ret- ) 
    //             ( note: no return address on top of pBHarrayhead! )
    
    
    DGLU_API void dg_initjumpbuffer (Bufferhandle* pBHarrayhead);
    
    
    
    DGLU_API extern const char* dg_stateexecute;  // setting the state variable to this puts script interpreter into execute mode
    
    DGLU_API extern const char dg_statecompile[];  // setting the state variable to this puts script interpreter into compile mode
    
    
    DGLU_API const char* dg_initbuffers(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_initvariables (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API UINT64 dg_isnegative (UINT64 x);
    
    
    
    // ////////////////////////////
    // Forth Compiling Routines  //
    // ////////////////////////////
    
    
    DGLU_API void dg_forthsafe (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthiscolon (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthisoto (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthisobto (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthispto (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthiscompilecall (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthiscallproc (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthiscallprocretuint64 (Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_forthiscolon (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthstringtonewprocword(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API  void dg_forthstringtonewobword(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcompilebranch (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthresolvecompiledbranch (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcompilecallcore (Bufferhandle* pBHarrayhead); 
    //                   ( addr -- )
    
    
    DGLU_API void dg_forthcompilecallsamebuffer (Bufferhandle* pBHarrayhead);
    //                         ( offsetinsamebuffer -- )
    
    
    DGLU_API void dg_forthcompilecallbuffer (Bufferhandle* pBHarrayhead);
    //                     ( bufferoffset bufferid -- )
    
    
    DGLU_API void dg_forthcompilesafecallbuffer (Bufferhandle* pBHarrayhead);
    //                     ( bufferoffset bufferid -- )
    
    
    // /////////////////////////
    // Compile Type Routines  //
    // /////////////////////////
    
    DGLU_API void dg_forthdocompiletypealwaysexecute(Bufferhandle* pBHarrayhead);
        
    DGLU_API void dg_forthdocompiletypesubroutine(Bufferhandle* pBHarrayhead);
        
    DGLU_API void dg_forthdocompiletypepreserveregs(Bufferhandle* pBHarrayhead);
        
    DGLU_API void dg_forthdocompiletypesafesubroutine(Bufferhandle* pBHarrayhead);    
    
    DGLU_API void dg_forthdocompiletypedpushn(Bufferhandle* pBHarrayhead);
 
    DGLU_API void dg_forthdocompiletypedpushf(Bufferhandle* pBHarrayhead);   
    
    DGLU_API void dg_forthdocompiletypedpushdn(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletypedpushp(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletypedpushs(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthdocompiletypewordsstringquotes (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthdocompiletypewords0stringquotes (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletyperunfileandwaitnoenvquotes (Bufferhandle* pBHarrayhead);
        
    DGLU_API void dg_forthdocompiletypecdecl(Bufferhandle* pBHarrayhead);
        
    DGLU_API void dg_forthdocompiletypecdeclretuint128(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthdocompiletypedfpcdecl(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletypecppmemberfunction(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthdocompiletypecall(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletypeftcolon(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthdocompiletypedpushbracketrbpplusn(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthdocompiletypebrackettoorder(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletypebracketwordlistdot(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthdocompiletypebracketlibdot(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletypecompilepushlocal(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletypevalue(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletypetwovalue(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletypefvalue(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletypeostore(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletypeof64store(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdocompiletypeotwostore (Bufferhandle* pBHarrayhead);

    DGLU_API extern const char* dg_docompiletypeostorename;
    DGLU_API void dg_docompiletypeostore (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);

    DGLU_API extern const char* dg_docompiletypeof64storename;
    DGLU_API void dg_docompiletypeof64store (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);

    DGLU_API extern const char* dg_docompiletypeotwostorename;
    DGLU_API void dg_docompiletypeotwostore (
        Bufferhandle* pBHarrayhead,
        UINT64 bufferid,
        UINT64 offset);
    
    
    // ////////////////////////////
    // Forth string stack words  //
    // ////////////////////////////          

    
    DGLU_API void dg_forthcomparestring ( Bufferhandle* pBHarrayhead );
    //                 ( $1 $2 -$- $1 $2 )
    //                 ( -- flag )
    
    
    DGLU_API void dg_forthgetmidstring ( Bufferhandle* pBHarrayhead );
    //             ( $1 -$- $1 $2 )
    //             ( offset length -- )
    
    
    DGLU_API void dg_forthcatstring ( Bufferhandle* pBHarrayhead );
    //                  ( $1 $2 -$- $1+$2 )
    
    
    DGLU_API void dg_forthlengthstring ( Bufferhandle* pBHarrayhead );
    //                ( $1 -$- $1 )
    //                ( -- length )
    
    
    DGLU_API void dg_forthshortenstring ( Bufferhandle* pBHarrayhead );
    //                 ( $1 -$- $1' )
    
    
    DGLU_API void dg_forthpickstring (Bufferhandle* pBHarrayhead);
    //              ( $x .. $3 $2 $1 $0 -$- $x ... $3 $2 $1 $0 $x )
    //              ( x -- )
    
    
    DGLU_API void dg_forthdupstring ( Bufferhandle* pBHarrayhead );
    //             ( $1 -$- $1 $1 )
    
    
    DGLU_API void dg_forthoverstring (Bufferhandle* pBHarrayhead);
    //              ( $1 $0 -$- $1 $0 $1 )
    
    
    DGLU_API void dg_forthdropstring (Bufferhandle* pBHarrayhead);
    //              ( $0 -$- )
    
    
    DGLU_API void dg_forthdeletestring (Bufferhandle* pBHarrayhead);
    //                ( ... $n+1 $n $n-1... $1 $0 -$- $n+1 $n-1 ... $1 $0 )
    //                ( n -- )
    
    
    DGLU_API void dg_forthswapstring (Bufferhandle* pBHarrayhead);
    //              ( $1 $0 -$- $0 $1 )
    
    
    DGLU_API void dg_forthnipstring (Bufferhandle* pBHarrayhead);
    //              ( $1 $0 -$- $0 )
    
    
    DGLU_API void dg_forthrotstring (Bufferhandle* pBHarrayhead);
    //             ( $2 $1 $0 -$- $0 $1 $2 )
    
    
    DGLU_API void dg_forthdepthstring (Bufferhandle* pBHarrayhead);
    //               ( -- n )
    //               ( $1 $2 $3 ... $n -$- $1 $2 $3 ... $n )
    
    
    DGLU_API void dg_forthnewstring (Bufferhandle* pBHarrayhead);
    //             ( -$- empty$ )
    
    
    DGLU_API void dg_forthctonewstring (Bufferhandle* pBHarrayhead);      
    //                ( -$- char$ )
    //                ( char -- )
    
    
    DGLU_API void dg_forthtonewstring (Bufferhandle* pBHarrayhead);      
    //                ( -$- $u )
    //                ( u -- )
    
    
    DGLU_API void dg_forthturnstringinto0string (Bufferhandle* pBHarrayhead); 
    //                         ( $1 -$- 0$1 )
    
    
    DGLU_API void dg_forthinsertinstring (Bufferhandle* pBHarrayhead);
    //                  ( offset -- )
    //                  ( $1 $2 -$- $2in$1atoffset )
    
    
    DGLU_API void dg_forthdeleteinstring (Bufferhandle* pBHarrayhead);
    //                  ( offset length -- )
    //                  ( $1 -$- $1' )
    
    
    DGLU_API void dg_forthholdstring (Bufferhandle* pBHarrayhead); 
    //                             ( $1 -$- $1' )
    //                             ( char -- )
    
    
    DGLU_API void dg_forthnumbersignstring (Bufferhandle* pBHarrayhead);   
    //                           ( $1 -$- $1' ) 
    //                           ( ud -- ud' )
    
    
    DGLU_API void dg_forthnumbersignsstring (Bufferhandle* pBHarrayhead);  
    //                            ( $1 -$- $1' ) 
    //                            ( ud -- 0 0)
    
    
    DGLU_API void dg_forthsignstring (Bufferhandle* pBHarrayhead);    
    //                          ( $1 -$- $1' ) 
    //                          ( n -- )
    
    
    DGLU_API void dg_forthstringcfetch (Bufferhandle* pBHarrayhead); 
    //                     ( $1 -$- $1 )   
    //                     ( position -- char )
    
    
    DGLU_API void dg_forthstringcstore (Bufferhandle* pBHarrayhead);   
    //                   ( $1 -$- $1' )  
    //                   ( char position -- )
    
    
    DGLU_API void dg_forthstringtoc (Bufferhandle* pBHarrayhead);
    //                     ( $1 -$- $1' )
    //                     ( -- char )
    
    
    DGLU_API void dg_forthstringto (Bufferhandle* pBHarrayhead);
    //                     ( $1 -$- $1' )
    //                     ( -- u )
    
    
    DGLU_API void dg_forthctostring (Bufferhandle* pBHarrayhead);
    //                    ( $1 -$- $1' )
    //                    ( char -- )
    
    
    DGLU_API void dg_forthtostring (Bufferhandle* pBHarrayhead);
    //                    ( $1 -$- $1' )
    //                    ( u -- )
    
    
    DGLU_API void dg_forthsplitstring (Bufferhandle* pBHarrayhead);
    //               ( $1 -$- $2 $3 )
    //               ( n -- )
    
    
    DGLU_API void dg_forthputmidstring (Bufferhandle* pBHarrayhead);
    //                ( n -- )
    //                ( destination$ source$ -$- destination$' )
    
    
    DGLU_API void dg_forthstringquotes (Bufferhandle* pBHarrayhead ); 
    // everything up to word ending in " is put onto string stack as a string
    
    
    DGLU_API void dg_forthstostring (Bufferhandle* pBHarrayhead);
    //               ( addr length -- )
    //               ( -- $1 )
    
    
    DGLU_API void dg_forthgetsstringnd (Bufferhandle* pBHarrayhead);
    //               ( $n $n-1 ... $1 $0 -$- $n $n-1 ... $1 $0 )
    //               ( n -- pstringn dg_forthlengthstringn )
    
    
    DGLU_API void dg_forthgetenvstring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthasciitounicodestring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthunicodetoasciistring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthgrowstring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthrollstring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthminusrollstring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthstripstring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdeleteinstringnd (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthinsertinstringnd (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcatstringnd (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthstrippathfromfilenamestring (Bufferhandle* pBHarrayhead);
    //        ( path\filename$ -$- filename$ )
    
    
    DGLU_API void dg_forthfillnewstring (Bufferhandle* pBHarrayhead);
    //        ( char n -- )
    //        ( -$- a$ )
    
    DGLU_API void dg_forthpzerostrtonewstr (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthnglufilestring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthglufilestring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthwordsstringquotes (Bufferhandle* pBHarrayhead );
    
    DGLU_API void dg_forthwords0stringquotes (Bufferhandle* pBHarrayhead );
    
    DGLU_API void dg_forthumulleutostring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthtostarulestring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthtoslashulestring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthreversestring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthnotstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthuleandstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthuleorstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthulexorstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthulenandstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthulenorstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthulexnorstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthlelshiftstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthulershiftstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthslershiftstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthlelshiftcstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthlershiftcstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthulestringtonumberstring(Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthtofactorialulestring(Bufferhandle* pBHarrayhead);
    
    
    // /////////////////////////////
    //  End of string stack words //
    // /////////////////////////////
    
    
    DGLU_API UINT64 dg_chartodigit (unsigned char c);
    
    
    DGLU_API UINT64 dg_chartodigitlowertoo (unsigned char c);
    
    
    DGLU_API UINT64 dg_pchartonumber (
        unsigned char* pnumber,
        UINT64 length,
        UINT64 base,
        UINT64* flag);
  
    DGLU_API INT64 dg_pchartonumberskipperiod (
        UINT8* pnumber,
        UINT64 length,
        UINT64 base,
        UINT64* pindex,
        UINT64* pdigitsafterperiod); 
        
    DGLU_API INT64 dg_pchartobase10numberandexponent (
        UINT8* pnumber,
        UINT64 length,
        INT64* pexponent,
        UINT64* pflag);
        
    DGLU_API FLOAT64 dg_u64times10totheu64tof64(
        INT64 number,
        INT64 exponent);
        
    DGLU_API FLOAT64 dg_pchartof64 (
        UINT8* pnumber,
        UINT64 length,
        UINT64* pflag);
    
    DGLU_API UINT64 dg_hexdectonumber (
        unsigned char* pnumber,
        UINT64 length,
        UINT64* pflag);
        
    DGLU_API unsigned char dg_digittochar (UINT64 d);
    
    
    
    DGLU_API void dg_forthocall ( Bufferhandle* pBHarrayhead );
    //           ( compileoffset compilebufid -- )
    
    
    DGLU_API void dg_forthqueryendevaluate (Bufferhandle* pBHarrayhead);
    //                     ( flag -- )
    
    
    DGLU_API void dg_forthtype0string (Bufferhandle* pBHarrayhead);
    //                     ( caddr -- )
    
    
    DGLU_API void dg_forthquestion (Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_forthdots (Bufferhandle* pBHarrayhead);
 
    
    DGLU_API void dg_forthdumphex (Bufferhandle* pBHarrayhead);
    //             ( addr length -- )
    
    DGLU_API void dg_forthwords (Bufferhandle* pBHarrayhead);
    //              ( -- )
    
    
    DGLU_API void dg_forthdotstrings (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdotwordname (Bufferhandle* pBHarrayhead);
    //              ( executiontoken -- )
    
    
    DGLU_API void dg_forthshowwordlist (Bufferhandle* pBHarrayhead);
    //              ( wordlistid -- )
    
    
    DGLU_API void dg_forthshowsortedwordlist (Bufferhandle* pBHarrayhead);
    //              ( wordlistid -- )
    
    
    DGLU_API void dg_forthshowallwords (Bufferhandle* pBHarrayhead);
    //              ( -- )
    
    
    DGLU_API void dg_forthcscan (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcscanlstring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcscanstring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthminuscscanstring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthscan (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthscanlstring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcodeallot (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthsftodf (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdftosf (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthftod (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdftod (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdtodf (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdoterrorline(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthohere(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthdglibstring(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcodescomma (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcodeu8comma (Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_forthcodeu16comma (Bufferhandle* pBHarrayhead);


    DGLU_API void dg_forthcodeu32comma (Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_forthcodeu64comma (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthlobit (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthhibit (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthcountbits (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthmicrosecondssince1970jan01(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthtouleb128 (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthhctwostore(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthdrshift (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthdlshift (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthdarshift (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthbuftodotobuf (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthbuftodotofilestring (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthbuftomachodotobuf (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthosymbolbuftonewdotobuf (Bufferhandle* pBHarrayhead);
    DGLU_API void dg_forthosymbolbuftonewdotofilestring (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthtestfindnumber (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthfunctblofn (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthdiaperoff (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthdiaperon (Bufferhandle* pBHarrayhead);
    
    
    
    
    
    
    // ///////////////////////////////////////
    // End of Forth string extension words  //
    // ///////////////////////////////////////
    
    
    
    DGLU_API void dg_forthurlencodestring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthurldecodestring (Bufferhandle* pBHarrayhead);
    
    
    // fileio stuff
    
    DGLU_API void dg_forthloadfilestring (Bufferhandle* pBHarrayhead);
    //              ( filename$ -$- )
    //              ( -- bufferid )
    
    
    DGLU_API void dg_forthsavefilestring (Bufferhandle* pBHarrayhead);
    //              ( filename$ -$- )
    //              ( bufferid -- )
    
    
    DGLU_API void dg_forthfixpathstring (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthincludefilestring (Bufferhandle* pBHarrayhead);
    //                 ( filename$ -$- )  
    
    
    DGLU_API void dg_forthqueryincludefilestring (Bufferhandle* pBHarrayhead);
    //                      ( filename$ -$- )
    //                      ( flag -- )
    
    // library stuff
    DGLU_API void dg_forthopenlibstring (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthopenlibrarystring (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthloadlibrarystringsub (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthloadlibrarystring (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthshowopenlibrary (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthshowlibrarystring (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthfindlibrarysymbol (Bufferhandle* pBHarrayhead);

    // Windows specific
    /*
    DGLU_API extern const char* dg_forthloadstdcalllibrarystringname;
    
    DGLU_API void dg_forthloadstdcalllibrarystring (Bufferhandle* pBHarrayhead);
    //                 ( libraryname$ -$- )
    //                 ( -openlibraryhandlestack- libraryhandle )
    //                 ( -- wordlistid )
    */

    DGLU_API void dg_forthfreelibrary (Bufferhandle* pBHarrayhead);
    

    DGLU_API UINT64 dg_callprocaddress (
        UINT64* pints,
        UINT64 n,
        UINT64* plength,
        UINT64* address);

    DGLU_API UINT64 dg_callprocaddressretuint128(
        UINT64* pints,
        UINT64 n,
        UINT64* plength,
        UINT64* address,
        UINT64* phireturn);
    
    
    // DGLU_API UINT128 dg_callprocaddressretuint128(
        //     UINT64* pints,
        //    UINT64 n,
        //    UINT64* plength,
        //    UINT64* address);
    
    DGLU_API FLOAT64 dg_calldfpprocaddress (
        UINT64* pints,
        UINT64 n,
        UINT64* plength,
        UINT64* address,
        UINT64 nfloat);
                                            
/*
    DGLU_API UINT32 dg_callprocaddressalign16 (
        UINT32* address,
        UINT32 n, // number of UINT32 units in parameters
        ...);     //   most things are 1 unit, a UINT64 is 2 units


    //DGLU_API UINT64 dg_callprocaddressretuint64  (UINT32* pints, UINT32 n, UINT32* plength, UINT32* address);
    
    
    
    //DGLU_API UINT32 dg_callprocaddressnodrop (UINT32* pints, 
    //                                             UINT32 n, 
    //                                             UINT32* plength, 
    //                                             UINT32* address);
    
                                            
    DGLU_API UINT32 dg_callcppmemberwin32 (UINT32* pints, 
                                           UINT32 n, 
                                           UINT32* plength, 
                                           UINT32* address);
    
*/
    DGLU_API void dg_forthcallprocaddress (Bufferhandle* pBHarrayhead);
    //  ( paramn paramn-1 paramn-2 ... param1 n procaddress -- returnvalue )

    
    DGLU_API void dg_forthcallprocaddressretuint128 (Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_forthcalldfpprocaddress (Bufferhandle* pBHarrayhead);
    
/*
    DGLU_API void dg_forthcallcppmemberfunction (Bufferhandle* pBHarrayhead);
    //                     ( paramn paramn-1 paramn-2 ... param1 n procaddress -- returnvalue )
    
    
    
    //DGLU_API void dg_forthcallprocaddressnodrop (Bufferhandle* pBHarrayhead);
    //                           ( paramn paramn-1 paramn-2 ... param1 n procaddress -- returnvalue )

    
    DGLU_API void dg_forthloadstdcallllibwordlist (Bufferhandle* pBHarrayhead);
    //                                 ( libraryhandle -- )
    
    
    DGLU_API const char* dg_determinecalltypefromname (const char* pname, UINT32 namelength, UINT32* pcalltype);
    
    
    DGLU_API void dg_forthloadcdecllibwordlist (Bufferhandle* pBHarrayhead);
    //                                 ( libraryhandle -- )
*/
    DGLU_API void dg_forthcreateov (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcreateov (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthcreateoc (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthosquotes (Bufferhandle* pBHarrayhead); // ( OS" )
    

    DGLU_API void dg_fortho0quotes (Bufferhandle* pBHarrayhead); // ( O0" )
 
 
    DGLU_API UINT64 dg_packtwobytevex (
        UINT64 simdprefixcode, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2
        UINT64 vectorlength, // 0 = 128, 1 = 256
        UINT64 secondsourcereg, // 0-15
        UINT64 rexdotr); // 0 or 1
        
    DGLU_API UINT64 dg_packthreebytevex (
        UINT64 leadingopcodebytescode, // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A
        UINT64 rexdotb, // 0 or 1
        UINT64 rexdotx, // 0 or 1
        UINT64 rexdotr, // 0 or 1
        UINT64 simdprefixcode, // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2
        UINT64 vectorlength, // 0 = 128, 1 = 256
        UINT64 secondsourcereg, // 0-15
        UINT64 rexdotw);         // 0 or 1 comes from opcode sequence apparently
        
    DGLU_API void dg_compilevex ( // need to add way to force promotion to 3 byte vex...
        Bufferhandle* pBHarrayhead,
        struct dg_Sibformatter* psf, // moo
        UINT64 addresssize,
        UINT64 simdprefixcode,  // 0 = none, 1 = 0x66, 2 = 0xF3, 3 = 0xF2
        UINT64 leadingopcodebytescode,  // 1 = 0x0F, 2 = 0x0F 0x38, 3 = 0x0F 0x3A
        UINT64 rexdotw, // 0x48 comes from opcode I think
        UINT64 usethreebytevex); // not zero means use three byte vex

    DGLU_API void dg_fortherrorquotes( Bufferhandle* pBHarrayhead); // ( ERROR" )
    
    
    DGLU_API void dg_forthtooname (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthlatest (Bufferhandle* pBHarrayhead);

    
    DGLU_API void dg_forthbracketlatest (Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_forthbracketcolononame (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthbracketwordnametoerror (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthnametoe (Bufferhandle* pBHarrayhead);
   
    
    /*
     DGLU_API extern const char* dg_compilepushdatastackname;
     
     DGLU_API void dg_compilepushdatastack (Bufferhandle* pBHarrayhead);
     */
    

    DGLU_API void dg_forthcompilegetolderrorcount (Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_compile0string (Bufferhandle* pBHarrayhead, unsigned char* psrc);
    
    
    DGLU_API void dg_forthqueryerrorif (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthtoorder (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthorderfrom (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthforthwords (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_fortherrorwords (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthenvironmentwords (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthbufferwords (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthstringwords (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthlibrarywords (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthuserwords (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthshowlicense (Bufferhandle* pBHarrayhead);
    //               ( -- )
    
    DGLU_API void dg_forthcrlf (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthgethstdin (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthgethstdout (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthgethstderror (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthgetfilelength (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthreadavailabletobuffer (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthreadwaitforntobuffer(Bufferhandle* pBHarrayhead);
    

    DGLU_API extern const char* dg_inithlistsname;


    DGLU_API void dg_inithlists (Bufferhandle* pBHarrayhead);
    

    DGLU_API Bufferhandle* dg_initwithoutwordlists(int argc, char* argv[]);
    
    
    DGLU_API Bufferhandle* dg_init(int argc, char* argv[]);
    
    
    DGLU_API void dg_cleanup (Bufferhandle* pBHarrayhead);
    

    DGLU_API void dg_main (int argc, char* argv[]);
    

    int main(int argc, char* argv[]);
    

    DGLU_API void dg_forthbswap (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API void dg_forthpagesize(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthroundup (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthpackdf (Bufferhandle* pBHarrayhead);
    //      ( mantissalo mantissahi exponent-n sign-f -- dfhi dflo )
    
    DGLU_API void dg_forthunpackdf (Bufferhandle* pBHarrayhead);
    //      ( dfhi dflo -- mantissalo mantissahi exponent-n sign-f )
    
    DGLU_API void dg_forthdfplus (Bufferhandle* pBHarrayhead);
    //      ( df1 df2 -- df1+df2 )
    
    DGLU_API void dg_forthdfminus (Bufferhandle* pBHarrayhead);
    //      ( df1 df2 -- df1-df2 )
    
    void dg_forthdfstar (Bufferhandle* pBHarrayhead);
    //      ( df1 df2 -- df1*df2 )
    
    void dg_forthdfslash (Bufferhandle* pBHarrayhead);
    //      ( df1 df2 -- df1/df2 )
    
    
    // ////////////////////////////////////
    // Forth Hierarchical List Routines  //
    // ////////////////////////////////////
    
    DGLU_API void dg_forthnewhlist (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthfreehlist (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthprunehlistelement(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthfreehlistelement(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthnewhlistelement(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgethlistelementnom (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgethlistelementvalue (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgethlistnewestchild (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgethlistoldestchild (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgethlistoldersibling (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgethlistnewersibling (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthchangehlistparent (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthfindclosesthlistchild (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthfindhlistchild (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthhlisttoxmlstring (Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgethowmanyhlistkids(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthgethlistsortedchildn(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthgethlistparent (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthsethlistelementvalue (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthpackhlist(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthunpackhlist(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthnamestrtovaluestr(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthnamestrtovalue(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthehnamestrtovaluestr(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthehnamestrtovalue(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthnamewtovaluestr(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthnamewtovalue(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthehnamewtovaluestr(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthehnamewtovalue(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthtoeh(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthehfrom(Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthdropeh(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthehtop(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthehnd(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthdupeh(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthetoehtop(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthehnewelement(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthehnewelementtoeh(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthehoherewtonewelement(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthehdot(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthehbracketnddot(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthehbracket1ddot(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthsymbolenumcurly (Bufferhandle* pBHarrayhead);

    DGLU_API void dg_forthosymbolcodeimportscommacurly(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthnewflatosymbolbuf(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthfreeflatosymbolbuf(Bufferhandle* pBHarrayhead);
    
    DGLU_API void dg_forthosymbolimport(Bufferhandle* pBHarrayhead);
 
    
    struct CompareNameData {
        unsigned char* pname;
        UINT64 namelength;
        UINT64 namelstroffsetbufid;
        UINT64 namelstrstringbufid;
        UINT64 elementheaderlstroffsetbufid;
        UINT64 elementheaderlstrstringbufid;
    };
    
    DGLU_API extern const char* dg_sortcomparehlistnomname;
    DGLU_API INT64 dg_sortcomparehlistnom(
        Bufferhandle* pBHarrayhead,
        void* pcomparedata,
        UINT64 comparedatalength,
        UINT64 keyofmidrangevalue);

    
    /////////////////////////////////////////////
    // End of Forth Hierarchical List Routines //
    ///////////////////////////////////////////// 
    
 
    ///////////////////////////
    // Forth Locals Routines //
    ///////////////////////////
    
    DGLU_API extern const char* dg_savelocalstackdepthname;
    DGLU_API void dg_savelocalstackdepth (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_restorelocalstackdepthname;
    DGLU_API void dg_restorelocalstackdepth (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_forthlocalsfetchname;
    DGLU_API void dg_forthlocalsfetch (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_forthlocalsstorename;
    DGLU_API void dg_forthlocalsstore(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_forthtolocalsname;
    DGLU_API void dg_forthtolocals(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_forthdocompiletypelocalname;
    DGLU_API void dg_forthdocompiletypelocal (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char dg_forthlocalsbarname[];
    DGLU_API extern const char* dg_forthbarname;
    DGLU_API extern const char* dg_localsbarmissingerror;

    DGLU_API void dg_forthlocalsbar(Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char dg_forthclearlocalwordlistname[];
    DGLU_API void dg_forthclearlocalwordlist (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char dg_forthquerycompileunnestlocalsname[];
    DGLU_API void dg_forthquerycompileunnestlocals (Bufferhandle* pBHarrayhead);
    
    DGLU_API extern const char dg_forthqueryclearlocalsname[];
    DGLU_API void dg_forthqueryclearlocals(Bufferhandle* pBHarrayhead);

    DGLU_API extern const char dg_forthcurlybracename[];
    DGLU_API void dg_forthcurlybrace (Bufferhandle* pBHarrayhead);

    DGLU_API extern const char dg_forthtoname[];
    DGLU_API void dg_forthto(Bufferhandle* pBHarrayhead);

    DGLU_API extern const char dg_forthvaluename[];
    DGLU_API void dg_forthvalue(Bufferhandle* pBHarrayhead);

    DGLU_API extern const char dg_forthtwovaluename[];
    DGLU_API void dg_forthtwovalue(Bufferhandle* pBHarrayhead);

    DGLU_API extern const char dg_forthfvaluename[];
    DGLU_API void dg_forthfvalue(Bufferhandle* pBHarrayhead);
    
    // ////////////////////////////////
    // End of Forth Locals Routines  //
    // ////////////////////////////////
    
 
    // ////////////////////////////////
    // Forth String Locals Routines  //
    // ////////////////////////////////
    
    DGLU_API extern const char* dg_savelocallsstackdepthname;
    DGLU_API void dg_savelocallsstackdepth (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_restorelocallsstackdepthname;
    DGLU_API void dg_restorelocallsstackdepth (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_forthlocalslstringfetchname;
    DGLU_API void dg_forthlocalslstringfetch (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_forthtolocalslstringname;
    DGLU_API void dg_forthtolocalslstring(Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_forthdocompiletypelocallsname;
    DGLU_API void dg_forthdocompiletypelocalls (Bufferhandle* pBHarrayhead);
    
    
    DGLU_API extern const char* dg_forthlocalslstringbarname;
    DGLU_API void dg_forthlocalslstringbar(Bufferhandle* pBHarrayhead);
    
    
    // ///////////////////////////////////////
    // End of Forth String Locals Routines  //
    // ///////////////////////////////////////
 

    DGLU_API Premadeword* dg_getppresortedcorewords (Bufferhandle* pBHarrayhead);

    DGLU_API Premadeword* dg_getppresortedenvironmentwords ();

    DGLU_API Premadeword* dg_getppresortedstringwords ();

    DGLU_API Premadeword* dg_getppresortederrorwords ();

    DGLU_API Premadeword* dg_getppresortedbufferwords (Bufferhandle* pBHarrayhead);

    DGLU_API Premadeword* dg_getppresortedoswords ();
    
    DGLU_API Premadeword* dg_getppresortedx86words ();
    

    
    
    
    DGLU_API extern const char* dg_forthocodename;

    DGLU_API void dg_forthocode (Bufferhandle* pBHarrayhead);
        
        
    DGLU_API extern const char* dg_forthendcodename;

    DGLU_API void dg_forthendcode (
        Bufferhandle* pBHarrayhead);
        
        
    DGLU_API void dg_initcpux86wordlist (
        Bufferhandle* pBHarrayhead);


#define dg_isdatasize   ((UINT64)0xFFFFFFFFFFFFFFFF)
#define dg_isforward    ((UINT64)0xFFFFFFFFFFFFFFFE)
#define dg_isreverse    ((UINT64)0xFFFFFFFFFFFFFFFD)
#define dg_isimmediate  ((UINT64)0xFFFFFFFFFFFFFFFC)
#define dg_isreg        ((UINT64)0xFFFFFFFFFFFFFFFB)
#define dg_isbasedisplacement            ((UINT64)0xFFFFFFFFFFFFFFFA) // technically [R+N]
#define dg_isbasescaleindexdisplacement  ((UINT64)0xFFFFFFFFFFFFFFF9) // technically [R+R*I+N]
#define dg_iscurrentcompilebufferoffset  ((UINT64)0xFFFFFFFFFFFFFFF8) // technically [O]
#define dg_ishereplusdisplacement        ((UINT64)0xFFFFFFFFFFFFFFF7) // technically [RIP+N]
#define dg_isbufferoffset                ((UINT64)0xFFFFFFFFFFFFFFF6) // technically [bufferoffset]
#define dg_isccbufferoffsetnobracket     ((UINT64)0xFFFFFFFFFFFFFFF5) // for call rip+n
#define dg_iscontrolreg                  ((UINT64)0xFFFFFFFFFFFFFFF4)
#define dg_isfloatingpointstackreg       ((UINT64)0xFFFFFFFFFFFFFFF3)
#define dg_isxmmreg                      ((UINT64)0xFFFFFFFFFFFFFFF2)
#define dg_isdebugreg                    ((UINT64)0xFFFFFFFFFFFFFFF1)
#define dg_issegmentreg                  ((UINT64)0xFFFFFFFFFFFFFFF0)
#define dg_isymmreg                      ((UINT64)0xFFFFFFFFFFFFFFEF)
#define dg_isthreebytevex                ((UINT64)0xFFFFFFFFFFFFFFEE)
#define dg_isbasescalevindexdisplacement ((UINT64)0xFFFFFFFFFFFFFFED) // technically [R+YMMR*I+N]
#define dg_isparamusingframe             ((UINT64)0xFFFFFFFFFFFFFFEC)
#define dg_isparamusingnoframe           ((UINT64)0xFFFFFFFFFFFFFFEB)
#define dg_isdgluforthframelocal         ((UINT64)0xFFFFFFFFFFFFFFEA) // technically [RBP+8*(N+2)]
#define dg_istointsubparam               ((UINT64)0xFFFFFFFFFFFFFFE9) // for setting up params for subroutine call
#define dg_istofloatsubparam             ((UINT64)0xFFFFFFFFFFFFFFE8) // for setting up params for subroutine call
#define dg_istointfloatsubparam          ((UINT64)0xFFFFFFFFFFFFFFE7) // for setting up params for subroutine call
#define dg_isfromintsubparam             ((UINT64)0xFFFFFFFFFFFFFFE6) // for unloading return params after subroutine call
#define dg_isfromfloatsubparam           ((UINT64)0xFFFFFFFFFFFFFFE5) // for unloading return params after subroutine call
#define dg_isptointsubparam              ((UINT64)0xFFFFFFFFFFFFFFE4) // for setting up params for subroutine call


#define dg_memmodeimmediate    (0)
#define dg_memmodedefaultreg   (1)
#define dg_memmodereg          (2)
#define dg_memmodemodrslashm   (3)
#define dg_memmodesib          (4)
#define dg_memmodeeipplusn     (5)
#define dg_memmodebufferoffset (6)
#define dg_memmodebufferoffsetnobracket (7)
#define dg_memmodefpsreg       (8)
#define dg_memmodexmmreg       (9)
#define dg_memmodecontrolreg   (10)
#define dg_memmodedebugreg     (11)
#define dg_memmodesegmentreg   (12)
#define dg_memmodevsib         (13)
#define dg_memmodeunknown      (0xFFFFFFFFFFFFFFFF)

#define dg_targettypeimmediate     (0)
#define dg_targettyperega          (1)
#define dg_targettypereg           (2)
#define dg_targettypemem           (3)
#define dg_targettypecontrolreg    (4)
#define dg_targettypefpsreg        (5)
#define dg_targettypexmmreg        (6)
#define dg_targettypedebugreg      (7)
#define dg_targettypesegmentreg    (8)
#define dg_targettypenumberoftypes (9)
#define dg_targettypeunknown       (0xFFFFFFFFFFFFFFFF)


// #define and enum are redundant... one must go
enum dg_branchtypes {
    DG_BRANCHTYPE_OVERFLOW = 0,
    DG_BRANCHTYPE_NOOVERFLOW,
    DG_BRANCHTYPE_ULESSTHAN,
    DG_BRANCHTYPE_UGREATERTHANOREQUAL,
    DG_BRANCHTYPE_EQUAL,
    DG_BRANCHTYPE_NOTEQUAL,
    DG_BRANCHTYPE_ULESSTHANOREQUAL,
    DG_BRANCHTYPE_UGREATERTHAN,
    DG_BRANCHTYPE_MINUS,
    DG_BRANCHTYPE_PLUS,
    DG_BRANCHTYPE_PARITYEVEN,
    DG_BRANCHTYPE_PARITYODD,
    DG_BRANCHTYPE_LESSTHAN,
    DG_BRANCHTYPE_GREATERTHANOREQUAL,
    DG_BRANCHTYPE_LESSTHANOREQUAL,
    DG_BRANCHTYPE_GREATERTHAN,
    DG_BRANCHTYPE_ALWAYS,
    DG_BRANCHTYPE_NEVER,
    DG_BRANCHTYPE_CARRYSET = 2,
    DG_BRANCHTYPE_CARRYCLEAR = 3,
    DG_BRANCHTYPE_ZERO = 4,
    DG_BRANCHTYPE_NOTZERO = 5
};
    
    
#define dg_ccvs (0)
#define dg_ccnv (1)
#define dg_cccs (2)
#define dg_ccnc (3)
#define dg_ccult (2)
#define dg_ccuge (3)
#define dg_cczs  (4)
#define dg_ccnz  (5)
#define dg_cceq  (4)
#define dg_ccne  (5)
#define dg_ccule (6)
#define dg_ccugt (7)
#define dg_ccss  (8)
#define dg_ccns  (9)
#define dg_ccmi  (8)
#define dg_ccpl  (9)
#define dg_ccps  (0x0A)
#define dg_ccnp  (0x0B)
#define dg_cclt  (0x0C)
#define dg_ccge  (0x0D)
#define dg_ccle  (0x0E)
#define dg_ccgt  (0x0F)
#define dg_ccalways (0x10)
#define dg_ccnever  (0x11)


enum dg_cpux86regs {
    dg_al = 0,
    dg_cl,
    dg_dl,
    dg_bl,
    dg_ah,
    dg_ch,
    dg_dh,
    dg_bh,
    dg_ax,
    dg_cx,
    dg_dx,
    dg_bx,
    dg_sp,
    dg_bp,
    dg_si,
    dg_di,
    dg_eax, // 0x10
    dg_ecx,
    dg_edx,
    dg_ebx,
    dg_esp,
    dg_ebp,
    dg_esi,
    dg_edi,
    // first rex reg is r8l
    dg_r8l,
    dg_r9l,
    dg_r10l,
    dg_r11l,
    dg_r12l,
    dg_r13l,
    dg_r14l,
    dg_r15l,
    dg_r8w, // 0x20
    dg_r9w,
    dg_r10w,
    dg_r11w,
    dg_r12w,
    dg_r13w,
    dg_r14w,
    dg_r15w,
    dg_r8d,
    dg_r9d,
    dg_r10d,
    dg_r11d,
    dg_r12d,
    dg_r13d,
    dg_r14d,
    dg_r15d,
    dg_r8, // 0x30
    dg_r9,
    dg_r10,
    dg_r11,
    dg_r12,
    dg_r13,
    dg_r14,
    dg_r15,
    dg_rax,
    dg_rcx,
    dg_rdx,
    dg_rbx,
    dg_rsp,
    dg_rbp,
    dg_rsi,
    dg_rdi,
    // need to add 4 to dg_spl, dg_bpl, dg_sil, dg_dil so gonna add some dummy regs
    dg_fakereg0, // 0x40
    dg_fakereg1,
    dg_fakereg2,
    dg_fakereg3,
    dg_spl,
    dg_bpl,
    dg_sil,
    dg_dil,
    dg_st0,
    dg_st1,
    dg_st2,
    dg_st3,
    dg_st4,
    dg_st5,
    dg_st6,
    dg_st7,
    dg_xmm0, // 0x50
    dg_xmm1,
    dg_xmm2,
    dg_xmm3,
    dg_xmm4,
    dg_xmm5,
    dg_xmm6,
    dg_xmm7,
    dg_xmm8,
    dg_xmm9,
    dg_xmm10,
    dg_xmm11,
    dg_xmm12,
    dg_xmm13,
    dg_xmm14,
    dg_xmm15,
    dg_ymm0, // 0x60
    dg_ymm1,
    dg_ymm2,
    dg_ymm3,
    dg_ymm4,
    dg_ymm5,
    dg_ymm6,
    dg_ymm7,
    dg_ymm8,
    dg_ymm9,
    dg_ymm10,
    dg_ymm11,
    dg_ymm12,
    dg_ymm13,
    dg_ymm14,
    dg_ymm15,
    dg_cr0, // 0x70
    dg_cr1,
    dg_cr2,
    dg_cr3,
    dg_cr4,
    dg_cr5,
    dg_cr6,
    dg_cr7,
    dg_cr8,
    dg_cr9,
    dg_cr10,
    dg_cr11,
    dg_cr12,
    dg_cr13,
    dg_cr14,
    dg_cr15,
    dg_dr0, // 0x80
    dg_dr1,
    dg_dr2,
    dg_dr3,
    dg_dr4,
    dg_dr5,
    dg_dr6,
    dg_dr7,
    dg_segregcs,
    dg_segregds,
    dg_segregss,
    dg_segreges,
    dg_segregfs,
    dg_segreggs,
    dg_segregfake1,
    dg_segregfake2,
    dg_gdtr, // 0x90
    dg_ldtr,
    dg_idtr,
    dg_crx,
    dg_fakereg4,
    dg_fakereg5,
    dg_fakereg6,
    dg_fakereg7,
    // last rex reg is dil
    dg_eip = 0xFFFF0000,
    dg_rip = 0xFFFF0001,
    dg_noreg = 0xFFFFFFFF
};


const UINT64 dg_sizenone = 0;
const UINT64 dg_sizebyte = 1;
const UINT64 dg_sizeword = 2;
const UINT64 dg_sizedword = 4;
const UINT64 dg_sizeqword = 8;

const UINT64 dg_optypeimmediate = 0;
const UINT64 dg_optypereg = 1;
const UINT64 dg_optypemem = 2;
const UINT64 dg_optypeunknown = 0xffffffffffffffff;


enum dg_twotargetmodes {
    dg_nton, // illegal
    dg_ntoa, // size matters
      // copy n to a's pfa, use a's size to determine start
      // if n's size is larger than a's size, could toss error
    dg_ntor, // size matters - could also handle signed/unsigned extension
      // copy n to a's pfa, use a's size to determine start
      // if n's size is larger than a's size, could toss error
    dg_ntom, // size matters - could also handle signed/unsigned extension
      // copy n to a's pfa, use a's size to determine start
      // if n's size is larger than a's size, could toss error
    dg_ntocr,
    dg_ntofpsr,
    dg_ntoxmmr,
    dg_ntodr,
    dg_ntosr,
    
    dg_aton, // illegal
      // swap pfas and use dg_ntoa
    dg_atoa,
    dg_ator, 
    dg_atom,
      // copy reg a to destination pfa
      // use r to m (unless reverse, then use m to r)
    dg_atocr,
    dg_atofpsr,
    dg_atoxmmr,
    dg_atodr,
    dg_atosr,
    
    dg_rton, // illegal
      // swap pfas and use dg_ntor
    dg_rtoa,
    dg_rtor, // (could handle size?) - could also handle signed/unsigned extension?
    dg_rtom, // size matters? - could also handle signed/unsigned extension
      // copy reg r to destination pfa
      // use r to m (unless reverse, then use m to r)
    dg_rtocr,
    dg_rtofpsr,
    dg_rtoxmmr,
    dg_rtodr,
    dg_rtosr,
    
    dg_mton, // illegal
      // swap pfas and use dg_ntom
    dg_mtoa,
    dg_mtor, // size matters? - could also handle signed/unsigned extension
      // swap pfas
      // copy reg a or r to destination pfa
      // use m to r (unless reverse, then use r to m)
    dg_mtom, // could handle this case with multiple opcodes
      // illegal for now
    dg_mtocr,
    dg_mtofpsr,
    dg_mtoxmmr,
    dg_mtodr,
    dg_mtosr,
    
    dg_crton,
    dg_crtoa,
    dg_crtor,
    dg_crtom,
    dg_crtocr,
    dg_crtofpsr,
    dg_crtoxmmr,
    dg_crtodr,
    dg_crtosr,
    
    dg_fpsrton,
    dg_fpsrtoa,
    dg_fpsrtor,
    dg_fpsrtom,
    dg_fpsrtocr,
    dg_fpsrtofpsr,
    dg_fpsrtoxmmr,
    dg_fpsrtodr,
    dg_fpsrtosr,
    
    dg_xmmrton,
    dg_xmmrtoa,
    dg_xmmrtor,
    dg_xmmrtom,
    dg_xmmrtocr,
    dg_xmmrtofpsr,
    dg_xmmrtoxmmr,
    dg_xmmrtodr,
    dg_xmmrtosr,
    
    dg_drton,
    dg_drtoa,
    dg_drtor,
    dg_drtom,
    dg_drtocr,
    dg_drtofpsr,
    dg_drtoxmmr,
    dg_drtodr,
    dg_drtosr,
    
    dg_srton,
    dg_srtoa,
    dg_srtor,
    dg_srtom,
    dg_srtocr,
    dg_srtofpsr,
    dg_srtoxmmr,
    dg_srtodr,
    dg_srtosr,
    
    //nfromn, // illegal
    //nfromr, // illegal
    //nfromm, // illegal
    //rfromn, // swap and use ntor
    //rfromr, // (could handle size? - don't swap so all opcode combos are covered)
    //rfromm, // swap and use mtor
    //mfromn, // swap and use ntom
    //mfromr, // swap and use rtom
    //mfromm // swap and use mtom
};

struct dg_opcodeholder {
    UINT64 opcodestringlength;
    UINT64 opcodeextension;
    char popcodestring[8]; // putting storage for the opcode strings in the structure...
    UINT64 prefixstringlength;
    char pprefixstring[8];
};

// All x86 2 target opcode types
struct Twotargetopcodestrings {
    // immediate types
    struct dg_opcodeholder n8toa8;  // promotes to n8tor8 if no opcode for this type
    struct dg_opcodeholder n8tor8;  // promotes to n8tom8 if no opcode for this type
    struct dg_opcodeholder n8tom8;  // error if this opcode is needed and is not available
    struct dg_opcodeholder n32toa32;  // promotes to n32tor32 if no opcode for this type
    struct dg_opcodeholder n32tor32;  // promotes to n8tom32signextended if no opcode for this type
    struct dg_opcodeholder n8tom32signextended;  // promotes to n32tom32 if no opcode for this type OR
                                                 // promotes to n32tom32 if immediate value does not fit into a signed 8 bit value
    struct dg_opcodeholder n32tom32; // error if this opcode is needed and is not available
    struct dg_opcodeholder n8tofpr;  // does not promote.. only PSSLW family uses this I think
    struct dg_opcodeholder n8toxmm;  // does not promote.. only PSSLW family uses this I think
    
    // m to r types (r to r forward)
    struct dg_opcodeholder m8tor8;   
    struct dg_opcodeholder m32tor32;
    struct dg_opcodeholder m64tofpr;
    struct dg_opcodeholder m64toxmm;
    
    // r to m types (r to r reverse)
    struct dg_opcodeholder r8tom8;
    struct dg_opcodeholder r32tom32;
    struct dg_opcodeholder fprtom64;
    struct dg_opcodeholder xmmtom64;
    
    UINT64 usesxmmandmemtargetsize;
};


// All x86 1 target opcode types
struct Onetargetopcodestrings {
    struct dg_opcodeholder n8;
    struct dg_opcodeholder a8;  // promotes to r8 if no opcode for this type
    struct dg_opcodeholder r8;  // promotes to m8 if no opcode for this type
    struct dg_opcodeholder m8;  // error if this opcode is needed and is not available
    struct dg_opcodeholder n32signextended; 
    struct dg_opcodeholder n32;
    struct dg_opcodeholder a32; // promotes to r32 if no opcode for this type
    struct dg_opcodeholder r32; // promotes to m32 if no opcode for this type
    struct dg_opcodeholder m32; // error if this opcode is needed and is not available
    struct dg_opcodeholder m32fp;
    struct dg_opcodeholder m64fp;
    struct dg_opcodeholder m80fp;
};

/*
enum dg_twotargetopcodetypes {
    dg_n8toa8 = 0, 
    dg_n8tor8,
    dg_n8tom8,
    dg_n32toa32,
    dg_n32tor32,
    dg_n8tom32signextended,
    dg_n32tom32,
    dg_m8tor8,
    dg_m32tor32,
    dg_r8tom8,
    dg_r32tom32,
};
*/
    
struct dg_Sibformatter {
    UINT64 basereg;           // 0-7 or -1 for no basereg
    UINT64 indexreg;          // 0-7 with esp not allowed and -1 for no scale reg
    // (no scale reg gets converted to esp's code)
    UINT64 scale;             // 0-3 representing 1 2 4 or 8
    UINT64 displacementsize;  // 0=byte or 1=dword or -1 for none
    INT64 displacement;       // this is signed I believe
    UINT64 targetreg;         // 0-7 or -1 for immediate value or -2 for slow eax
    UINT64 direction;         // 0 = to target reg, 1 = from target reg
    UINT64 size;              // data size in bytes
    UINT64 immediatevalue;
    UINT64 immediatevaluehi;
    UINT64 immediatesize;     // can be different than size in some cases
    UINT64 offset;
    UINT64 bufferid;
    UINT64 mod;
    UINT64 rslashm;
    UINT64 memmode;
    UINT64 usesxmmandmemtargetsize;
    UINT64 secondsourcereg;   // for vex
    UINT64 usesthreebytevex;  // not zero means force 3 byte vex
};


DGLU_API void dg_initSibformatter (struct dg_Sibformatter* psf);


DGLU_API extern const char* dg_pulloneaddressingmodename;
DGLU_API void dg_pulloneaddressingmode(
    Bufferhandle* pBHarrayhead,
    dg_Sibformatter* psf);


DGLU_API extern const char* dg_formatsibname;
DGLU_API void dg_formatsib (
    Bufferhandle* pBHarrayhead,
    struct dg_Sibformatter* psf);


DGLU_API extern const char* dg_formatmodrslashmname;
DGLU_API void dg_formatmodrslashm (
    Bufferhandle* pBHarrayhead,
    struct dg_Sibformatter* psf);


DGLU_API extern const char* dg_formatpsfname;
DGLU_API void dg_formatpsf(
    Bufferhandle* pBHarrayhead,
    struct dg_Sibformatter* psf);
    

DGLU_API extern const char* dg_compilepsfname;
DGLU_API void dg_compilepsf(
    Bufferhandle* pBHarrayhead,
    struct dg_Sibformatter* psf);


DGLU_API extern const char* dg_gettargettypename;
DGLU_API UINT64 dg_gettargettype (
    Bufferhandle* pBHarrayhead,
    struct dg_Sibformatter* psf);


DGLU_API extern const char* dg_fill2targetmathoptblname;
DGLU_API void dg_fill2targetmathoptbl (
    Bufferhandle* pBHarrayhead,
    struct Twotargetopcodestrings* popcodes,
    UINT64 mathopindex); // 0-7


DGLU_API extern const char* dg_compilentoaname;
DGLU_API void dg_compilentoa (
    Bufferhandle* pBHarrayhead,
    struct Twotargetopcodestrings* popcodes,
    struct dg_Sibformatter* pimmediatepsf,
    struct dg_Sibformatter* pregpsf);
    
    
DGLU_API extern const char* dg_compilentomname;
DGLU_API void dg_compilentom (
    Bufferhandle* pBHarrayhead,
    struct Twotargetopcodestrings* popcodes,
    struct dg_Sibformatter* pimmediatepsf, 
    struct dg_Sibformatter* pmempsf);


DGLU_API extern const char* dg_compilentorname;
DGLU_API void dg_compilentor (
    Bufferhandle* pBHarrayhead,
    struct Twotargetopcodestrings* popcodes,
    struct dg_Sibformatter* pimmediatepsf, 
    struct dg_Sibformatter* pregpsf);
    
    
DGLU_API extern const char* dg_compilertomname;
DGLU_API void dg_compilertom (
    Bufferhandle* pBHarrayhead,
    struct Twotargetopcodestrings* popcodes,
    struct dg_Sibformatter* pregpsf,
    struct dg_Sibformatter* pmempsf);


DGLU_API extern const char* dg_compiletwotargetsname;
DGLU_API void dg_compiletwotargets (
    Bufferhandle* pBHarrayhead,
    struct Twotargetopcodestrings* popcodes,
    struct dg_Sibformatter* pfirsttarget, 
    struct dg_Sibformatter* psecondtarget);
    
DGLU_API extern const char* dg_determineparameterregistername;
DGLU_API UINT64 dg_determineparameterregister (
    Bufferhandle* pBHarrayhead,
    UINT64 parameterindex);
    
DGLU_API extern const char* dg_determineparameterregisternoframename;
DGLU_API UINT64 dg_determineparameterregisternoframe (
    Bufferhandle* pBHarrayhead,
    UINT64 parameterindex);
    
    
// DGLU_API void dg_initcpux86wordlist (
//    Bufferhandle* pBHarrayhead);

DGLU_API const char* dg_getsenvnamevalue (
    INT64 argc,
    char* argv[], 
    const char* pnametofind,
    UINT64 nametofindlength,
    char** ppfoundname,
    UINT64* pfoundnamelength,
    char** ppfoundvalue,
    UINT64* pfoundvaluelength);

/*
DGLU_API const char* dg_checkargs (
    int argc, 
    char* argv[]);
*/

DGLU_API extern const char dg_parseoffdelimitername[];
DGLU_API unsigned char* dg_parseoffdelimiter(
    Bufferhandle* pBHarrayhead,
    UINT64* pwordlength,
    unsigned char endchar);
    
DGLU_API extern const char dg_parsename[];
DGLU_API unsigned char* dg_parse(
    Bufferhandle* pBHarrayhead,
    UINT64* pwordlength,
    unsigned char endchar);
    
DGLU_API extern const char dg_parsemultilinename[];
DGLU_API unsigned char* dg_parsemultiline(
    Bufferhandle* pBHarrayhead,
    UINT64* pwordlength,
    unsigned char endchar);

DGLU_API extern const char dg_parsewordname[];
DGLU_API unsigned char* dg_parseword(
    Bufferhandle* pBHarrayhead,
    UINT64* pwordlength);
    
DGLU_API extern const char dg_parsewordsname[];
DGLU_API unsigned char* dg_parsewords(
    Bufferhandle* pBHarrayhead,
    UINT64* pwordlength,
    unsigned char enddelimiter,
    UINT64* pfoundendflag,
    UINT64 lineterminatorsareendflag);
    
DGLU_API extern const char dg_noparseentercurrentlinename[];
DGLU_API unsigned char* dg_noparseentirecurrentline(
    Bufferhandle* pBHarrayhead,
    UINT64* plinelength,
    UINT64 bufferid);
    
DGLU_API extern const char dg_parselinename[];
DGLU_API unsigned char* dg_parseline(
    Bufferhandle* pBHarrayhead,
    UINT64* plinelength);
    
DGLU_API extern const char dg_noparselineatoffsetname[];
DGLU_API UINT64 dg_noparselineatoffset(
    Bufferhandle* pBHarrayhead,
    UINT64 cibid,
    UINT64 offset);

DGLU_API extern const char* dg_addnamedbuffername;
DGLU_API extern const char* dg_namedbuffervaluename;
DGLU_API void dg_addnamedbuffer(
    Bufferhandle* pBHarrayhead,
    unsigned char* pbuffername,
    UINT64 buffernamelength,
    UINT64 type,
    UINT64 bufferid,
    UINT64 descriptionhlistid);
    
DGLU_API extern const char* dg_checkfornamedbuffername;
DGLU_API UINT64 dg_checkfornamedbuffer (
    Bufferhandle* pBHarrayhead,
    unsigned char* pbuffername,
    UINT64 buffernamelength,
    UINT64 type,
    UINT64 bufferid,
    UINT64 descriptionhlistid);
    
DGLU_API extern const char* dg_getnamedbufferelementidname;
DGLU_API UINT64 dg_getnamedbufferelementid(
    Bufferhandle* pBHarrayhead,
    unsigned char* pbuffername,
    UINT64 buffernamelength);
    
DGLU_API extern const char dg_patchpnewbuffername[];
DGLU_API  void dg_patchpnewbuffer(
    Bufferhandle* pBHarrayhead,
    UINT64 desthlistheaderid,     // id of hlist containing patch new buffer list
    UINT64 destparentelementid,   // parent element id of the patch new buffer list
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmydesthlistheader);
    
DGLU_API extern const char dg_patchaddressusingdlsymname[];
DGLU_API void dg_patchaddressusingdlsym(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid, // id of hlist containing import list
    UINT64 parentelementid, // element id of source library name which is parent element id of symbol list
    UINT64 dylibhandle, // handle of source shared library
    unsigned char* pbuffer, // address of destination buffer to patch
    UINT64 bufferlength); // length of destination buffer

DGLU_API extern const char dg_patchaddressusinghlistname[];
DGLU_API void dg_patchaddressusinghlist(
    Bufferhandle* pBHarrayhead,
    UINT64 desthlistheaderid,     // id of hlist containing import symbol list
    UINT64 destparentelementid,   // parent element id of the import symbol list
    unsigned char* pdestbuffer,   // address of destination buffer to patch
    UINT64 destbufferlength,      // length of destination buffer
    UINT64 srchlistheaderid,      // source hlist
    UINT64 srcparentelementid,    // should be root... but just in case it's not
    unsigned char* psrcbuffer);   // pointer to source buffer (base address)

DGLU_API extern const char dg_patchaddressusingoffsetname[];
DGLU_API void dg_patchaddressusingoffset(
    Bufferhandle* pBHarrayhead,
    UINT64 desthlistheaderid,     // id of hlist containing destination patch list
    UINT64 destparentelementid,   // parent element id of the destination patch list
    unsigned char* pdestbuffer,   // address of destination buffer to patch
    UINT64 destbufferlength,      // length of destination buffer
    unsigned char* psrcbuffer);   // pointer to source buffer (base address)
    
DGLU_API extern const char dg_patchname[];
DGLU_API void dg_patch(
    Bufferhandle* pBHarrayhead,
    UINT64 destbufferid,
    UINT64 destbufferdescriptionhlistid,
    UINT64 importselementid);
    
DGLU_API extern const char dg_loadsharedliblistname[];

DGLU_API void dg_loadsharedliblist(
    Bufferhandle* pBHarrayhead,
    UINT64 srchlistid,
    UINT64 parentelementid,
    unsigned char* pparentvalue,
    UINT64 parentvaluelength,
    Hlistheader* pmysrchlistheader);
    
    
DGLU_API extern const char dg_nglufuncbufsname[];
DGLU_API extern const char dg_nglufunccallbufname[];
DGLU_API extern const char dg_nglufunccallbuftodsname[];
DGLU_API extern const char dg_nglufunccalloffsetname[];
DGLU_API extern const char dg_nglufunccalloffsetodsname[];
DGLU_API extern const char dg_nglufunccalllibname[];
DGLU_API extern const char dg_nglufunccalllibtodsname[];
DGLU_API extern const char dg_nglufuncdestbufname[];
DGLU_API extern const char dg_nglufuncdestsymbolsname[];
DGLU_API extern const char dg_nglufuncfilesname[];
DGLU_API extern const char dg_nglufunchfilesname[];
DGLU_API extern const char dg_nglufunchlistherename[];
DGLU_API extern const char dg_nglufunclibsname[];
DGLU_API extern const char dg_nglufunclinkbufname[];
DGLU_API extern const char dg_nglufunclinklibname[];
DGLU_API extern const char dg_nglufunclinknewbufname[];
DGLU_API extern const char dg_nglufunclinkoffsetname[];
DGLU_API extern const char dg_nglufuncngluname[];
DGLU_API extern const char dg_nglufuncsrcbufname[];
DGLU_API extern const char dg_nglufuncsrclibname[];
DGLU_API extern const char dg_nglufuncsrcsymbolsname[];
DGLU_API extern const char dg_nglufuncsymbolsname[];
DGLU_API extern const char dg_nglufuncuint64valuetodsname[];
DGLU_API extern const char dg_nglufuncvaluetossname[];


DGLU_API extern const char dg_bufferseleementname[];
DGLU_API extern UINT64 dg_bufferselementnamelength;
    
// DGLU_API extern const char dg_gluelementname[];
// DGLU_API extern UINT32 dg_gluelementnamelength;

DGLU_API extern const char dg_calldestbufname[];
DGLU_API extern UINT64 dg_calldestbufnamelength;

DGLU_API extern const char dg_calldestbuftodsname[];
DGLU_API extern UINT64 dg_calldestbuftodsnamelength;

DGLU_API extern const char dg_calldestoffsetname[];
DGLU_API extern UINT64 dg_calldestoffsetnamelength;

DGLU_API extern const char dg_calldestoffsettodsname[];
DGLU_API extern UINT64 dg_calldestoffsetnametodslength;

DGLU_API extern const char dg_calllibname[];
DGLU_API extern UINT64 dg_calllibnamelength;

DGLU_API extern const char dg_calllibtodsname[];
DGLU_API extern UINT64 dg_calllibtodsnamelength;

DGLU_API extern const char dg_setdestbufname[];
DGLU_API extern UINT64 dg_setdestbufnamelength;

DGLU_API extern const char dg_setdestsymbollistname[];
DGLU_API extern UINT64 dg_setdestsymbollistnamelength;

DGLU_API extern const char dg_fileselementname[];
DGLU_API extern UINT64 dg_fileselementnamelength;

DGLU_API extern const char dg_hlistfileselementname[];
DGLU_API extern UINT64 dg_hlistfileselementnamelength;

DGLU_API extern const char dg_hlistherename[];
DGLU_API extern UINT64 dg_hlistherenamelength;

DGLU_API extern const char dg_libsname[];
DGLU_API extern UINT64 dg_libsnamelength;

DGLU_API extern const char dg_linkbufname[];
DGLU_API extern UINT64 dg_linkbufnamelength;

DGLU_API extern const char dg_linklibname[];
DGLU_API extern UINT64 dg_linklibnamelength;

DGLU_API extern const char dg_linknewbufname[];
DGLU_API extern UINT64 dg_linknewbufnamelength;

DGLU_API extern const char dg_linkoffsetname[];
DGLU_API extern UINT64 dg_linkoffsetnamelength;

DGLU_API extern const char dg_ngluname[];
DGLU_API extern UINT64 dg_nglunamelength;

DGLU_API extern const char dg_setsrcbufname[];
DGLU_API extern UINT64 dg_setsrcbufnamelength;

DGLU_API extern const char dg_setsrclibname[];
DGLU_API extern UINT64 dg_setsrclibnamelength;

DGLU_API extern const char dg_setsrcsymbollistname[];
DGLU_API extern UINT64 dg_setsrcsymbollistnamelength;

DGLU_API extern const char dg_symbolsname[];
DGLU_API extern UINT64 dg_symbolsnamelength;

DGLU_API extern const char dg_uint64valuetodsname[];
DGLU_API  extern UINT64 dg_uint64valuetodsnamelength;

DGLU_API extern const char dg_valuetostrsname[];
DGLU_API  extern UINT64 dg_valuetostrsnamelength;


DGLU_API extern const char dg_dgluname[];
DGLU_API void dg_glu(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistheaderid);

DGLU_API void dg_nglu(
    Bufferhandle* pBHarrayhead,
    UINT64 hlistid);
    
DGLU_API extern const char dg_getnamedsymbollisthideidname[];

DGLU_API UINT64 dg_getnamedsymbollisthideid (
    Bufferhandle* pBHarrayhead,
    unsigned char* psymbollistname,
    UINT64 symbollistnamelength,
    UINT64* phlistid);
    
DGLU_API extern const char dg_namedbufnametoeidname[];

DGLU_API UINT64 dg_namedbufnametoeid (
    Bufferhandle* pBHarrayhead,
    unsigned char* pbuffername,
    UINT64 buffernamelength);

DGLU_API extern const char* dg_namedbufnametobufidname;

DGLU_API UINT64 dg_namedbufnametobufid (
    Bufferhandle* pBHarrayhead,
    unsigned char* pbuffername,
    UINT64 buffernamelength);
    
DGLU_API extern const char* dg_namedbufnametoaddrname;

DGLU_API unsigned char* dg_namedbufnametoaddr (
    Bufferhandle* pBHarrayhead,
    unsigned char* pbuffername,
    UINT64 buffernamelength);
    

DGLU_API extern const char* dg_hsymbolnametovaluename;
    
DGLU_API UINT64 dg_hsymbolnametovalue (
    Bufferhandle* pBHarrayhead,
    unsigned char* psymbolname,
    UINT64 symbolnamelength,
    UINT64 namedsymbollisthlistid,
    UINT64 namedsymbollistelementid);


DGLU_API extern const char dg_forthgluelementname[];
DGLU_API void dg_forthgluelement(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthngluelementname[];
DGLU_API void dg_forthngluelement(Bufferhandle* pBHarrayhead);

    
DGLU_API extern const char dg_forthgluname[];
DGLU_API void dg_forthglu(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthngluname[];
DGLU_API void dg_forthnglu(Bufferhandle* pBHarrayhead);

    
DGLU_API extern const char dg_forthnewnglulistname[];
DGLU_API void dg_forthnewnglulist(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthnewcurrentnglulistname[];
DGLU_API void dg_forthnewcurrentnglulist(Bufferhandle* pBHarrayhead);

    
DGLU_API extern const char dg_forthcreateimportcommaname[];
DGLU_API void dg_forthcreateimportcomma(Bufferhandle* pBHarrayhead);

DGLU_API extern const char dg_forthcreatecodelinkcommaname[];
DGLU_API void dg_forthcreatecodelinkcomma(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthcreateocodelinkcommaname[];
DGLU_API void dg_forthcreateocodelinkcomma(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthcreateobcodelinkcommaname[];
DGLU_API void dg_forthcreateobcodelinkcomma(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthcreatecdecllinkcommaname[];
DGLU_API void dg_forthcreatecdecllinkcomma(Bufferhandle* pBHarrayhead);

DGLU_API extern const char dg_forthcreatecolonlinkcommaname[];
DGLU_API void dg_forthcreatecolonlinkcomma(Bufferhandle* pBHarrayhead);

DGLU_API extern const char dg_forthcreateodatalinkcommaname[];
DGLU_API void dg_forthcreateodatalinkcomma(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthcreateobdatalinkcommaname[];
DGLU_API void dg_forthcreateobdatalinkcomma(Bufferhandle* pBHarrayhead);
    
    
DGLU_API extern const char dg_forthwtoimportcommaname[];
DGLU_API void dg_forthwtoimportcomma(Bufferhandle* pBHarrayhead);
    

DGLU_API extern const char dg_forthwtolinkcommaname[];
DGLU_API void dg_forthwtolinkcomma(Bufferhandle* pBHarrayhead);

DGLU_API extern const char dg_forthwtocodelinkcommaname[];
DGLU_API void dg_forthwtocodelinkcomma(Bufferhandle* pBHarrayhead);

DGLU_API extern const char dg_forthwtodatalinkcommaname[];
DGLU_API void dg_forthwtodatalinkcomma(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthsymbolname[];
DGLU_API void dg_forthsymbol(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthosymbolname[];
DGLU_API void dg_forthosymbol(Bufferhandle* pBHarrayhead);

DGLU_API extern const char dg_forthosymbolentryname[];
DGLU_API void dg_forthosymbolentry(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthnewsymbollistdashtoname[];
DGLU_API void dg_forthnewsymbollistdashto(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthstrtoimportcommaname[];
DGLU_API void dg_forthstrtoimportcomma(Bufferhandle* pBHarrayhead);
    
    
DGLU_API extern const char dg_forthstrtolinkcommaname[];
DGLU_API void dg_forthstrtolinkcomma(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthstrtocodelinkcommaname[];
DGLU_API void dg_forthstrtocodelinkcomma(Bufferhandle* pBHarrayhead);


DGLU_API extern const char dg_forthstrtodatalinkcommaname[];
DGLU_API void dg_forthstrtodatalinkcomma(Bufferhandle* pBHarrayhead);

DGLU_API void dg_forthsymbolsstringtoeh (Bufferhandle* pBHarrayhead);

DGLU_API void dg_forthnamedbufstringtoe (Bufferhandle* pBHarrayhead);

DGLU_API void dg_forthnamedbufstrtobufid (Bufferhandle* pBHarrayhead);

DGLU_API void dg_forthnamedbufstrtop (Bufferhandle* pBHarrayhead);

DGLU_API void dg_forthhsymbolstrto (Bufferhandle* pBHarrayhead);

DGLU_API void dg_forthdashto (Bufferhandle* pBHarrayhead);

// DGLU_API void dg_forthlibdashto (Bufferhandle* pBHarrayhead);

DGLU_API extern const char dg_forthshowbuffersname[];
DGLU_API void dg_forthshowbuffers(Bufferhandle* pBHarrayhead);


DGLU_API const char* dg_initenvironment (int argc, char* argv[]);
DGLU_API void dg_showinputmode (
    Bufferhandle* pBHarrayhead,
    UINT64 fileid);
    
DGLU_API extern const char* dg_doinputstuffname;
DGLU_API void dg_doinputstuff (
    Bufferhandle* pBHarrayhead,
    UINT64* pfirsttimethrough);
    
DGLU_API extern const char dg_loadfilename[];
DGLU_API UINT64 dg_loadfile (
    Bufferhandle* pBHarrayhead,
    unsigned char* pfilename,
    UINT64 filenamelength);
    
DGLU_API extern const char dg_nglufilename[];
DGLU_API  void dg_nglufile (
    Bufferhandle* pBHarrayhead,
    unsigned char* pfilename,
    UINT64 filenamelength);

DGLU_API extern const char* dg_compileosymbolimportstuffname;
UINT64 dg_compileosymbolimportstuff(Bufferhandle* pBHarrayhead);

DGLU_API extern const char* dg_compilecodelinkname;
UINT64 dg_compilecodelink(Bufferhandle* pBHarrayhead);

// winspecific stuff
#ifdef DGLU_OS_WIN64
DGLU_API extern const char dg_pushsymboltowin64coffsymboltablename[];

DGLU_API void  dg_pushsymboltowin64coffsymboltable(
    Bufferhandle* pBHarrayhead,
    UINT64 symboltablebufferid,
    UINT64 oversizesymbolnamebufferid,
    unsigned char* psymbolname,
    UINT64 symbolnamelength,
    DWORD value,
    SHORT sectionnumber,
    WORD type,
    BYTE storageclass,
    BYTE numberofauxsymbols);


DGLU_API extern const char dg_pushexportsymbolstowin64coffbuffersname[];

DGLU_API void dg_pushexportsymbolstowin64coffbuffers(
    Bufferhandle* pBHarrayhead,
    UINT64 exportsymbollisthlistid,
    UINT64 exportsymbollistparentelementid,
    UINT64 symboltablebufferid,
    UINT64 oversizesymbolnamebufferid,
    UINT64 dotdrectvebufferid,
    UINT64 dottextsectionnumber);

DGLU_API extern const char dg_pushsectionlengthtowin64coffsymboltablename[];

DGLU_API void dg_pushsectionlengthtowin64coffsymboltable(
    Bufferhandle* pBHarrayhead,
    UINT64 symboltablebufferid,
    UINT64 sectionlength);

DGLU_API extern const char dg_pushimportymbolstowin64coffbuffersname[];

DGLU_API UINT64 dg_pushimportsymbolstowin64coffbuffers(
    Bufferhandle* pBHarrayhead,
    UINT64 importsymbollisthlistid,
    UINT64 importsymbollistparentelementid,
    UINT64 symboltablebufferid,
    UINT64 oversizesymbolnamebufferid,
    UINT64 relocationtablebufferid);
#endif

#ifdef  __cplusplus
}
#endif


#endif  /* _INC_diapergluforth */
