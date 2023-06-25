// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.12.
//
//    DiaperGlu v5.12 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.12 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.12; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// June 24, 2023              //
// version 5.12               //
// /////////////////////////////


#include "diapergluforth.h"

// Empty string
const unsigned char dg_emptystring[]       = "";

// General error and dg_success messages
// const char* dg_success                    = " - dg_success";

// const char dg_noerroryet[]                 = " - no error yet";
const char dg_incrementingerrorcount[]     = " - shouldn't see this on error stack";

const char dg_noerrors[]                   = " - no errors on error stack";
const char dg_errorbufnotinbharray[]       = " - there is no error stack buffer handle!";
const char dg_errorbufisfree[]             = " - the error stack buffer has been freed!";
const char dg_errorbufgrowbynesizenemaxsize[]  = " - error stack's growby != size != maxsize error.";
const char dg_errorbufnubcorrupt[]         = " - error stacks's next unused byte pointer corrupt";
const char dg_errorunderflow[]             = " - error stack underflow";
const char dg_erroroverflow[]              = " - error stack overflow";
const char dg_errornotthatmanyerrors[]     = " - not that many errors on the error stack";

const char dg_errorsbufidis0[]             = " - error's buffer id is 0";
const char dg_errorsbufidnotinbharray[]    = " - error's buffer id is for non existant buffer";
const char dg_errorsbufidisfree[]          = " - error's buffer id is for a freed buffer";
const char dg_errorsbufidnubcorrupt[]      = " - error's buffer id is for a buffer with used bytes > size";
const char dg_errorsbufidsizecorrupt[]     = " - error's buffer id is for a buffer with size > maxsize";
const char dg_errorsoffsetpastend[]        = " - error's offset is off end of it's buffer";

const char dg_errorinsubroutine[]          = " - error in subroutine";
// const char dg_osexception[]                = " - operating system exception";
// const char* dg_oserror                    = " - operating system error";
// const char* dg_badmemoryerror             = " - bad memory error, process did not have permission to access some memory";
const char dg_illegalopcodeerror[]         = " - illegal opcode error, cpu encounter bad instruction code";
// const char* dg_outofmemoryerror           = " - out of memory error";
// const char dg_badmagicerror[]              = " - file or structure's magic number not what was expected error";
// const char dg_missingexporttableerror[]    = " - library file's export table is missing error";
// const char dg_exporttablebounderror[]      = " - library file export table's declared size goes into something else's memory error";
// const char dg_nullpbharrayheaderror[]      = " - Pointer to buffer handle array head invalid, null or -1 pointer";
// const char dg_bharrayheadbadmemerror[]     = " - Buffer handle array head pointer points to memory process is not allowed to access";
// const char dg_notbharrayheaderror[]        = " - Pointer does not point to buffer handle array head, id is incorrect";
// const char dg_nullpbharrayerror[]          = " - Pointer to buffer handle array invalid, null or -1 pointer";
// const char dg_bharraybadmemerror[]         = " - Buffer handle array pointer points to memory process is not allowed to access";

/*
const char dg_buffernubcorrupt[]           = " - Buffer's next unused byte index corrupt";
const char dg_bufferidnotinbharray[]       = " - Buffer id is too high. There aren't that many buffer handles in the buffer handle array.";
const char dg_bufferidisfree[]             = " - Buffer id is for a free buffer.";
const char dg_bufferidisnotfree[]          = " - Buffer id is for a buffer that is not free.";
const char dg_bufferunderflow[]            = " - Trying to drop more bytes than are in the buffer error";
const char dg_buffergrowbycorrupt[]        = " - Buffer's growby was changed from a multiple of system page size";
const char dg_buffersizecorrupt[]          = " - Buffer's size was changed from a multiple of system page size";
const char dg_buffermaxsizecorrupt[]       = " - Buffer's maximum allowed size was changed from a multiple of system page size";
const char dg_buffermaxsizeltsize[]        = " - Buffer's size is greater than it's maximum allowed size error";
const char dg_maxsizeltgrowbyerror[]       = " - Buffer's maxsize < growby";
const char dg_bufferidisforerrorstack[]    = " - Buffer id is for error stack which is not allowed.";
const char dg_bufferidisfordglubuffer[]    = " - Buffer id is for a dglu script engine buffer which is not allowed.";
*/

// const char dg_nullpointererror[]           = " - null pointer error";
// const char dg_offsetpastenderror[]         = " - offset is past end of buffer error";
// const char dg_segmentgoespastenderror[]    = " - offset + length goes past end of buffer error";
const char dg_lstringoffsetpastenderror[]  = " - offset is past end of lstring error";
const char dg_lstringsegmentgoespastenderror[] = " - offset + length goes past end of lstring error";

const char dg_branchsourcepastenderror[]   = " - can't resolve branch because source offset is beyond end of buffer error";
const char dg_branchsourcetoolowerror[]    = " - can't resolve branch because source offset off beginning of buffer error";
const char dg_branchopcodemissingerror[]   = " - branch opcode missing error";
const char dg_branchtoobigerror[]          = " - branch offset too big, if you see this error, signed offset is > 4 bytes, OR you are using a LOOP instruction and offset is greater than one byte.";
const char dg_branchalreadyresolvederror[] = " - branch already resolved error, default offset was not 0";

const char dg_signedvaluetoobigerror[]     = " - signed value too big error, value probably must fit into an INT64 or INT32";

// const char dg_buffergrowby0error[]         = " - Buffer's grow by is 0. When a buffer is allocated or increased, units of growby are used.";
// const char dg_bufferfullerror[]            = " - growing buffer would exceed maximum allowed size error";

const char dg_indexnotinarrayerror[]       = " - index is off end of array";
const char dg_lstringidtoohigherror[]      = " - lstring's id is higher than number of strings on lstring stack";
const char dg_lstringsoffsetscorrupt[]     = " - lstring's start offset is higher than it's end offset";
const char dg_lstringtopoffsetwasbad[]     = " - top lstrings end offset was not length of string buffer";
const char dg_lstringstackdepthcorrupt[]   = " - lstring stack's offset array is not UINT64 aligned";
const char dg_toobigfordesterror[]         = " - source is too big to fit in destination error";

const char dg_wordidtoobigerror[]          = " - word's id too big to index word buffer, the calculation would overflow a UINT64";
const char dg_wordlistidtoobigerror[]      = " - word list's id too big to index word list buffer, the calculation would overflow a UINT64";
const char dg_wordalreadylinkederror[]     = " - word is already linked into a wordlist error";
const char dg_newwordoldererror[]          = " - trying to link a new word that is older than latest word in wordlist error which could create a circular wordlist";
const char dg_wordnotfoundinsearchordererror[] = " - word not found in search order error";

const char dg_colonsysmissingerror[]       = " - colon sys missing; data stack not balanced through : definition, possibly an unresolved branch";

// const char dg_BHarraygrowby0error[]        = " - BHarray's grow by is 0. Something is very wrong with script engine.";
// const char dg_BHarraymaxsizeltgrowby[]     = " - BHarray's maxsize < growby. Something is very wrong with script engine.";
// const char dg_BHarraymaxsizeltbhsize[]     = " - BHarray's maxsize < size of a buffer handle. Did you change the #defines and recompile?";
// const char dg_BHarraynubcorrupt[]          = " - BHarray's next unused byte index is corrupt. Something is very wrong.";
// const char dg_BHarraynubgtsize[]           = " - BHarray's next unused byte index > BHarray's size. Something is very wrong.";
// const char dg_BHarrayfull[]                = " - BHarray is full. Maximum allowed size reached. I can't believe you reached it!";

const char dg_initerrorsbuf0inuse[]        = " - could not initialize error stack because something is already using buffer 0!";

// const char dg_filenotfounderror[]          = " - file not found error";
// const char dg_pathnotfounderror[]          = " - path not found error";
// const char dg_accessdeniederror[]          = " - access denied error";
// const char dg_toomanyopenfileserror[]      = " - too many open files error";
// const char dg_drivenotfounderror[]          = " - drive not found error";
// const char dg_devicenotfounderror[]         = " - device not found error";
// const char dg_devicenotreadyerror[]         = " - device not ready error";
// const char dg_filesystemunknownerror[]      = " - file system not supported by operating system error";
// const char dg_devicebrokenerror[]           = " - device is broken error";
// const char dg_fileinuseerror[]              = " - file in use by something else error";
// const char dg_fileislockederror[]           = " - file is locked error";
// const char dg_filesystemcorrupterror[]      = " - file system corrupt error";
// const char dg_filetoobigerror[]             = " - file too big for this function.";
// const char dg_filetypeunknownerror[]        = " - file type unknown error";
// const char dg_osdidlessthanavailableerror[] = " - operating system processed less than it said it could";
// const char dg_invalidparametererror[]       = " - invalid parameter error";
// const char dg_notexecutablefileerror[]      = " - not an executable file error";
// const char dg_parametersovermaxsizeerror[]  = " - parameter list's size over system size limit error";
// const char dg_ioerror[]                     = " - input or output error";
// const char dg_toomanysymboliclinkserror[]   = " - path to file has too many symbolic links error.";
// const char dg_pathorfilenametoolongerror[]  = " - path or file name too long error";
// const char dg_partofpathnotdirectoryerror[] = " - part of the path does not point to a directory error";
// const char dg_fileopenforwriteerror[]       = " - file open for write error";
// const char dg_badprocessiderror[]           = " - process does not exist or is not a child of the calling process";
// const char dg_interruptedbysignalerror[]    = " - call was interrupted and not restarted error";
// const char dg_toomanyprocesseserror[]       = " - too many processes error";

const char dg_toomanyparameterserror[]         = " - too many parameters for this function";

// yes, this 0xFF value is hard coded... and very vary bad :-( J.N. Nov. 30, 2019 ... and I couldn't get it to work anyways
const char dg_couldnotrunfileerror[]        = " - could not run the file error... or the program exited with error code 0xFF";
const char dg_programexitedwitherrorerror[] = " - program exited with an error code or could not run the file";

// const char dg_writeprotectederror[]        = " - write protected error";
// const char dg_diskisfullerror[]            = " - disk is full error";
// const char dg_invaliduserbuffererror[]     = " - invalid user buffer error, probably means too many pending i/o requests - os couldn't keep up and ran out of buffers";
// const char dg_unknownwriteerror[]          = " - unknown write error";
// const char dg_couldnotgetpagelockerror[]   = " - os could not get page lock on the caller's memory buffer error";

const char dg_crcerror[]                   = " - crc error";
// const char dg_invalidhandleerror[]         = " - os invalid handle error";
const char dg_outsideofbuffererror[]       = " - trying to access outside buffer error";

const char dg_inputbufferlengthchangederror[]         = " - input buffer length changed error";
const char dg_evaluatebufferwordnotfounderror[]       = "dg_evaluatebuffer - word not found error";

const char dg_datastackmisalignederror[]   = " - data stack not UINT32 aligned error";
const char dg_datastackunderflowerror[]    = " - not enough parameters on data stack error";
const char dg_stringstackunderflowerror[]  = " - not enough parameters on string stack error";
const char dg_lstringstackunderflowerror[] = " - not enough parameters on lstring stack error";
const char dg_rstackunderflowerror[]       = " - not enough parameters on rstack error, can be caused by missing loop counter or index";
const char dg_underflowerror[]             = " - underflow error";
const char dg_lstringemptyerror[]          = " - lstring is empty error";
const char dg_stringunderflowerror[]       = " - trying to drop more bytes than are in string error";
const char dg_datastacknoraddrmissingerror[] = " - address and/or number of parameters missing from data stack error";
const char dg_procparamsmissingerror[]     = " - proc parameters missing error; format for this function is paramn ... param1 n addr -- returnvalue";
const char dg_dfpprocparamsmissingerror[]  = " - dfp proc parameters missing error; format for this function is paramn ... param1 n nfloats addr -- returnvalue";
const char dg_missingobjecthandleerror[]   = " - missing object handle parameter; this function must have at least one parameter";
const char dg_arraymisalignederror[]       = " - array's buffer length not aligned to size of element error";
const char dg_alreadyfreeerror[]           = " - element you are trying to free is already free error";
const char dg_wasnottrulyfreeerror[]       = " - element in free list was not truly free error";
const char dg_structuretoosmallerror[]     = " - length of storage in bytes is too small to hold the structure's data error";

const char dg_emptystringerror[]           = " - empty input string error";
const char dg_wordlength0error[]           = " - word name length can not be 0 error";
const char dg_maxwordlengthexceedederror[] = " - word name length exceeds 255 characters error";
const char dg_countlengthexceedederror[]   = " - counted string length exceeds 255 characters error";

const char dg_nowordfounderror[]           = " - no word found in current input buffer";
const char dg_signedlengthlessthan0error[] = " - signed length parameter less than 0 error";

const char dg_basetoolowerror[]            = " - BASE is < 2 error";
const char dg_basetoohigherror[]           = " - BASE is too high. Up to 201 is supported.";

const char dg_searchorderemptyerror[]      = " - no word lists on search order stack error";

const char dg_datastackunbalancederror[]   = " - operation did not consume the correct number of parameters on data stack error";

const char dg_hlistpreviousparentbad[]     = " - hlist corrupt - element's previous sibling's does not have same parent as element error";
const char dg_hlistnextparentbad[]         = " - hlist corrupt - element's next sibling does not have same parent as element error";
const char dg_hlistpreviousnextbad[]       = " - hlist corrupt - element's previous sibling's next sibling is not the element error";
const char dg_hlistnextpreviousbad[]       = " - hlist corrupt - element's next sibling's previous sibling is not the element error";
const char dg_hlistparentlastchildbad[]    = " - hlist corrupt - element can not have a next child and be the parent's last child too error";

const char dg_hlistelementwasfreed[]       = " - hlist element holding this error was freed";
const char dg_hlistgetsnameerror[]         = " - error getting pointer to and length of hlist name";
const char dg_elementisfreeerror[]         = " - element is free error";
// const char dg_wordnotfounderror[]          = " - word not found error";
const char dg_namenotfounderror[]          = " - name not found error";

const char dg_symbolnotfounderror[]        = " - symbol not found error";
const char dg_patchfunctionnotfounderror[] = " - patch function not found error";

const char dg_tryingtofreehlist0error[]    = " - hlist 0 is reserved for wordlists, user tried to free it error";

const char dg_glulisttypenotfounderror[]   = " - Glu/NGlu hlist root name not one of \"NGlu\" or \"Glu \"";

const char dg_queueswitchlengthtoobigerror[]   = " - queue switchlength too big error. If you make your switchlength too big, and you didn't limit the buffer sizes, the queue will eat up all your memory.";

void dg_initerrors (
    Bufferhandle* pBHarrayhead,
    UINT64 size,
    const char** pError)
{
    UINT64 bufferid = BHarraymaxindex;
    const char* myerror;

    myerror = dg_putuint64(
        (UINT64*)pError,
        (UINT64)dg_badmemoryerror);

    if (myerror != dg_success)
    {
        return;
    }

    *pError = dg_checkbharrayhead(pBHarrayhead);

    if (*pError != dg_success)
    {
        return;
    }

    if (size < errorstackminimumsize)
    {
        size = errorstackminimumsize;
    }

    size = size & 0xFFFFFFF8; // force size to be a multiple of 8

    bufferid = dg_newbuffer(
        pBHarrayhead,
        size,
        size,
        pError,
        FORTH_FALSE);

    if (*pError != dg_success)
    {
        return;
    }

    if (bufferid != DG_ERRORSTACK_BUFFERID)
    {
        dg_freebuffer(pBHarrayhead, bufferid);
        *pError = dg_initerrorsbuf0inuse;
    }

    pBHarrayhead->errorcount = 0;
}


const char* dg_pusherrorname = "dg_pusherror";

void dg_pusherror (
    Bufferhandle* pBHarrayhead,
    const char* error)
{
    Bufferhandle* pBH;
    UINT64 here;
    UINT64* paddr;
    const char* flag;

    // would like to incremenet error count even if there is no bharray
    flag = dg_checkbharrayhead(pBHarrayhead);

    if (flag != dg_success)
    {
        return;
    }

    if (pBHarrayhead->errorcount < (largestunsignedint - 1))
    {
        pBHarrayhead->errorcount++;
    }

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        return;
    }

    // is there an error buffer handle in bharray?
    if (pBHarrayhead->nextunusedbyte < sizeof (Bufferhandle))
    {
        return;
    }

    pBH = (Bufferhandle *)pBHarrayhead->pbuf;

    if (pBH->pbuf == badbufferhandle)
    {
        return;
    }

    // making sure no one messed with error stack
    if (pBH->growby != pBH->maxsize)
    {
        return;
    }

    if (pBH->growby != pBH->size)
    {
        return;
    }

    // making sure error will fit
    if (pBH->nextunusedbyte <= (pBH->size - 2*sizeof (const char*)) )
    {
        here = pBH->nextunusedbyte;
        pBH->nextunusedbyte += 2*sizeof (const char*);
        paddr = (UINT64*)((char*)pBH->pbuf + here);
        paddr[0] = (UINT64)error;
        paddr[1] = DG_CORE_BUFFERID;
    }
}


const char* dg_pushbuffererrorname = "dg_pushbuffererror";

void dg_pushbuffererror (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64 offset)
{
    Bufferhandle* pBH;
    UINT64 here;
    UINT64* paddr;
    const char* flag;

    // would like to incremenet error count even if there is no bharray
    flag = dg_checkbharrayhead(pBHarrayhead);

    if (flag != dg_success)
    {
        return;
    }

    if (pBHarrayhead->errorcount < (largestunsignedint - 1))
    {
        pBHarrayhead->errorcount++;
    }

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        return;
    }

    if (pBHarrayhead->nextunusedbyte < sizeof (Bufferhandle))
    {
        return;
    }

    pBH = (Bufferhandle *)pBHarrayhead->pbuf;

    if (pBH->pbuf == badbufferhandle)
    {
        return;
    }

    if (pBH->growby != pBH->maxsize)
    {
        return;
    }

    if (pBH->growby != pBH->size)
    {
        return;
    }
    
    // if bufferid is the fake bufferid for the wordlist name or value
    //  set the element's "I'm on the error stack" flag

    if (pBH->nextunusedbyte <= (pBH->size - 2*sizeof (const char*)) )
    {
        here = pBH->nextunusedbyte;
        pBH->nextunusedbyte += 2*sizeof (const char*);
        paddr = (UINT64*)((char*)pBH->pbuf + here);
        paddr[0] = offset;
        paddr[1] = bufferid;
    }
}


const char* dg_geterrorname = "dg_geterror";

const char* dg_geterror (
    Bufferhandle* pBHarrayhead,
    UINT64 errorindex)
{
    Bufferhandle* pBH = NULL;
    UINT64 errorcount = 0;
    const char* error = dg_noerroryet;
    const char* flag = NULL;

    UINT64* pints = NULL;

    flag = dg_checkbharrayhead(pBHarrayhead);

    if (flag != dg_success)
    {
        return(flag);
    }

    if (pBHarrayhead->errorcount == 0)
    {
        return(dg_noerrors);
    }

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        return(flag);
    }

    errorcount = pBHarrayhead->errorcount;

    // assuming error stack is buffer 0
    if (pBHarrayhead->nextunusedbyte < sizeof(Bufferhandle))
    {
        return(dg_errorbufnotinbharray);
    }

    pBH = (Bufferhandle*)(pBHarrayhead->pbuf);

    if (pBH->pbuf == badbufferhandle)
    {
        return(dg_errorbufisfree);
    }

    if (pBH->growby != pBH->size)
    {
        return(dg_errorbufgrowbynesizenemaxsize);
    }

    if (pBH->growby != pBH->maxsize)
    {
        return(dg_errorbufgrowbynesizenemaxsize);
    }

    if ((pBH->nextunusedbyte % (2*sizeof(const char *))) != 0)
    {
        return(dg_errorbufnubcorrupt);
    }

    if (pBH->nextunusedbyte == 0)
    {
        return(dg_errorunderflow); // it got past errorcount == 0 above so... something is wrong
    }

    if (errorindex >= pBH->nextunusedbyte / ( 2*sizeof(UINT64)))
    {
        return(dg_errornotthatmanyerrors);
    }

    pints = (UINT64*)pBH->pbuf + (errorindex * 2);

    if (pints[1] == DG_CORE_BUFFERID)
    {
        error = (const char*)(pints[0]);
        return (error);
    }
        
    if (pints[1] == DG_ERRORSTACK_BUFFERID) // buffer 0 is reserved for the error stack
    {
        error = dg_errorsbufidis0;
        return (error);
    }
    
    // put check for wordlist name here
    //if (DG_WORDNAME_FAKE_BUFFERID == pints[1])
    //{
    //  return a fake error message indicating you can't use this function
      // for wordlist name errors
    //}
    
    // using division instead of multiplication to prevent overflow
    if ((pints[1]) >= ((pBHarrayhead->nextunusedbyte) / sizeof(Bufferhandle)))
    {
        error = dg_errorsbufidnotinbharray;
        return (error);
    }

    pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[(pints[1])] );

    if (pBH->pbuf == badbufferhandle)
    {
        error = dg_errorsbufidisfree;
        return (error);
    }

    if (pBH->nextunusedbyte > pBH->size)
    {
        error = dg_errorsbufidnubcorrupt;
        return (error);
    }

    if (pBH->size > pBH->maxsize)
    {
        error = dg_errorsbufidsizecorrupt;
        return (error);
    }

    if (pints[0] >= pBH->nextunusedbyte)
    {
        error = dg_errorsoffsetpastend;
        return (error);
    }

    error = (const char*)pBH->pbuf + pints[0];

    // can't check to see if there is a 0 at the end of the string and the whole string is in the buffer:-(

    return (error);
}


const char* dg_getbuffererrorname = "dg_getbuffererror";

void dg_getbuffererror (
    Bufferhandle* pBHarrayhead, 
    UINT64 errorindex,
    UINT64* poffset,
    UINT64* pbufferid)
{
    Bufferhandle* pBH;
    UINT64 errorcount = 0;
//    const char* error = dg_noerroryet;
    const char* flag;

    UINT64* pints = NULL;

    // this checks memory at poffset
    flag = dg_putuint64(
        poffset,
        (UINT64)dg_badmemoryerror);

    if (flag != dg_success)
    {
        return;
    }

    // this checks memory at pbufferid
    flag = dg_putuint64(
        pbufferid,
        (UINT64)DG_CORE_BUFFERID);

    if (flag != dg_success)
    {
        return;
    }
    
    flag = dg_checkbharrayhead(pBHarrayhead);

    if (flag != dg_success)
    {
        *poffset = (UINT64)flag;
        return;
    }

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        *poffset = (UINT64)flag;
        return;
    }

    errorcount = pBHarrayhead->errorcount;

    // checking error buffer
    if (pBHarrayhead->nextunusedbyte < sizeof(Bufferhandle)) // I should do the calculation because I may change which buffer is the error buffer
    {
        *poffset = (UINT64)dg_errorbufnotinbharray;
        return;
    }

    pBH = (Bufferhandle*)(pBHarrayhead->pbuf);

    if (pBH->pbuf == badbufferhandle)
    {
        *poffset = (UINT64)dg_errorbufisfree;
        return;
    }

    if ((pBH->growby != pBH->size) || (pBH->growby != pBH->maxsize))
    {
        *poffset = (UINT64)dg_errorbufgrowbynesizenemaxsize;
        return;
    }

    if ((pBH->nextunusedbyte % (2*sizeof(const char *))) != 0)
    {
        *poffset = (UINT64)dg_errorbufnubcorrupt;
        return;
    }

    if (errorindex >= (pBH->nextunusedbyte / (2*sizeof(unsigned int))))
    {
        *poffset = (UINT64)dg_errornotthatmanyerrors;
        return;
    }

    pints = (UINT64*)pBH->pbuf + (errorindex * 2);

    // checking to see if error message is DG_CORE_BUFFERID so we won't have to check error message buffer id if it is
    if (pints[1] == DG_CORE_BUFFERID)
    {
        *poffset = pints[0];
        return;
    }

    // checking to see if error message bufferid is valid
    if (pints[1] == DG_ERRORSTACK_BUFFERID) // buffer 0 is reserved for the error stack
    {
        *poffset = (UINT64)dg_errorsbufidis0;
        return;
    }
    
    if ((pints[1] != DG_WORDNAME_FAKE_BUFFERID) &&
        (pints[1] != DG_WORDNAME_FAKE_BUFFERID) )
    {
        if ( (pints[1]) >= ((pBHarrayhead->nextunusedbyte) / sizeof(Bufferhandle)) )
        {
            *poffset = (UINT64)dg_errorsbufidnotinbharray;
            return;
        }

        // checking to see if error message buffer is still valid and error message start is in it
        pBH = &( ((Bufferhandle*)(pBHarrayhead->pbuf))[(pints[1])] );

        if (pBH->pbuf == badbufferhandle)
        {
            *poffset = (UINT64)dg_errorsbufidisfree;
            return;
        }

        if (pBH->nextunusedbyte > pBH->size)
        {
            *poffset = (UINT64)dg_errorsbufidnubcorrupt;
            return;
        }

        if (pBH->size > pBH->maxsize)
        {
            *poffset = (UINT64)dg_errorsbufidsizecorrupt;
            return;
        }

        if (pints[0] >= pBH->nextunusedbyte)
        {
            *poffset = (UINT64)dg_errorsoffsetpastend;
            return;
        }
    }

    *poffset = pints[0];
    *pbufferid = pints[1];
    
    return;
}

// don't need to change this one
const char* dg_poperrorname = "dg_poperror";

const char* dg_poperror (Bufferhandle* pBHarrayhead)
{
    Bufferhandle* pBH = NULL;
    UINT64 errorcount = 0;
    const char* error = dg_noerroryet;
    UINT64 i = 0;
    const char* flag = NULL;

    flag = dg_checkbharrayhead(pBHarrayhead);

    if (flag != dg_success)
    {
        return (flag);
    }

    errorcount = pBHarrayhead->errorcount;

    // may need to move this down so we can catch the case where there is stuff
    //  on the stack but the errorcount is 0... on the other hand, anyerrors wont 
    //  catch it... so.... gonna leave it for now
    if (errorcount == 0)
    {
        return(dg_noerrors);
    }

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        return (flag);
    }

    // buffer handle for error buffer is missing
    if (pBHarrayhead->nextunusedbyte < sizeof(Bufferhandle))
    {
        pBHarrayhead->errorcount--;
        return(dg_errorbufnotinbharray);
    }

    pBH = (Bufferhandle*)(pBHarrayhead->pbuf);

    // no memory allocated for error buffer
    if (pBH->pbuf == badbufferhandle)
    {
        pBHarrayhead->errorcount--;
        return(dg_errorbufisfree);
    }

    // error buffer not locked to not grow
    if (pBH->growby != pBH->size)
    {
        pBHarrayhead->errorcount--;
        return(dg_errorbufgrowbynesizenemaxsize);
    }

    if (pBH->growby != pBH->maxsize)
    {
        pBHarrayhead->errorcount--;
        return(dg_errorbufgrowbynesizenemaxsize);
    }

    // error stack misaligned
    if ((pBH->nextunusedbyte % ( 2*sizeof(const char *))) != 0)
    {
        pBHarrayhead->errorcount--;
        return(dg_errorbufnubcorrupt);
    }

    // no errors on stack, yet error count is not 0
    //  shouldn't be possible to get this error if all access is through error routines
    if (pBH->nextunusedbyte == 0)
    {
        pBHarrayhead->errorcount--;
        return(dg_errorunderflow);
    }

    // get index of top error on stack
    i = (pBH->nextunusedbyte / (2 * sizeof(const char*))) - 1;

    // errorcount > number of errors on stack case
    //  return overflow and set error count to number of errors
    //  could return one overflow error for each occurence but not gonna do it
    if (errorcount > (i + 1))
    {
        pBHarrayhead->errorcount = i + 1;
        return (dg_erroroverflow);
    }
    
    // success case
    error = dg_geterror(pBHarrayhead, i);
    pBH->nextunusedbyte = pBH->nextunusedbyte - 2*sizeof(const char*);

    // it shouldn't happen but in case error stack has more errors than error count...
    //  just setting errorcount to i instead of decrementing
    pBHarrayhead->errorcount = i;

    return (error);
}


const char* dg_popbuffererrorname = "dg_popbuffererror";

void dg_popbuffererror (
    Bufferhandle* pBHarrayhead, 
    UINT64* perrmsgoffset,
    UINT64* perrmsgbufid)
{
    
    Bufferhandle* pBH = NULL;

    UINT64 errorcount = 0;
//    const char* error = dg_noerroryet;
    UINT64 i = 0;
    const char* flag = NULL;

    flag = dg_putuint64(
        perrmsgoffset,
        (UINT64)dg_badmemoryerror);

    if (flag != dg_success)
    {
        return;
    }

    flag = dg_putuint64(
        perrmsgbufid,
        (UINT64)DG_CORE_BUFFERID);

    if (flag != dg_success)
    {
        return;
    }

    flag = dg_checkbharrayhead(pBHarrayhead);

    if (flag != dg_success)
    {
        // not a lot we can do if pBHarrayhead is messed up
        *perrmsgoffset = (UINT64)flag;
        return;
    }

    errorcount = pBHarrayhead->errorcount;

    // may need to move this down so we can catch the case where there is stuff
    //  on the stack but the errorcount is 0... on the other hand, anyerrors wont 
    //  catch it... so.... gonna leave it for now
    if (errorcount == 0)
    {
        *perrmsgoffset = (UINT64)dg_noerrors;
        return;
    }

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        *perrmsgoffset = (UINT64)flag;
        return;
    }

    // buffer handle for error buffer is missing
    if (pBHarrayhead->nextunusedbyte < sizeof(Bufferhandle))
    {
        pBHarrayhead->errorcount = 0;
        *perrmsgoffset = (UINT64)dg_errorbufnotinbharray;
        return;
    }

    pBH = (Bufferhandle*)(pBHarrayhead->pbuf);

    // no memory allocated for error buffer
    if (pBH->pbuf == badbufferhandle)
    {
        pBHarrayhead->errorcount = 0;
        *perrmsgoffset = (UINT64)dg_errorbufisfree;
        return;
    }

    // error buffer not locked to not grow
    if (pBH->growby != pBH->size)
    {
        pBHarrayhead->errorcount = 0;
        *perrmsgoffset = (UINT64)dg_errorbufgrowbynesizenemaxsize;
        return;
    }

    if (pBH->growby != pBH->maxsize)
    {
        pBHarrayhead->errorcount = 0;
        *perrmsgoffset = (UINT64)dg_errorbufgrowbynesizenemaxsize;
        return;
    }

    // error stack misaligned
    if ((pBH->nextunusedbyte % ( 2*sizeof(const char *))) != 0)
    {
        // clearing stack
        pBHarrayhead->errorcount = 0;
        pBH->nextunusedbyte = 0;
        *perrmsgoffset = (UINT64)dg_errorbufnubcorrupt;
        return;
    }

    // no errors on stack, yet error count is not 0
    //  shouldn't be possible to get this error if all access is through error routines
    if (pBH->nextunusedbyte == 0)
    {
        pBHarrayhead->errorcount = 0;
        *perrmsgoffset = (UINT64)dg_errorunderflow;
        return;
    }

    // get index of top error on stack
    i = (pBH->nextunusedbyte / (2 * sizeof(const char*))) - 1;

    // errorcount > number of errors on stack case
    //  return overflow and set error count to number of errors
    //  could return one overflow error for each occurence but not gonna do it
    if (errorcount > (i + 1))
    {
        pBHarrayhead->errorcount = i + 1;
        *perrmsgoffset = (UINT64)dg_erroroverflow;
        return;
    }
    
    // success case
    dg_getbuffererror(pBHarrayhead, i, perrmsgoffset, perrmsgbufid);
    pBH->nextunusedbyte = pBH->nextunusedbyte - 2*sizeof(const char*);

    // it shouldn't happen but in case error stack has more errors than error count...
    //  just setting errorcount to i instead of decrementing
    pBHarrayhead->errorcount = i;

    return;
}


const char* dg_geterrorcountname = "dg_geterrorcount";

UINT64 dg_geterrorcount (Bufferhandle* pBHarrayhead)
{
    // since many routines call this many times...
    //  this should be as fast as possible
    const char* flag = dg_checkbharrayhead(pBHarrayhead);

    if (flag != dg_success)
    {
        return (baderrorcount);
    }

    return (pBHarrayhead->errorcount);
}


UINT64 dg_checkerrorsonstack (Bufferhandle* pBHarrayhead)
{
    Bufferhandle* pBH = NULL;
    const char* flag = NULL;

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        return (0);
    }

    pBH = (Bufferhandle*)pBHarrayhead->pbuf; // this assumes error stack is array 0

    if (pBH->pbuf == badbufferhandle)
    {
        return (0);
    }

    return (pBH->nextunusedbyte / (2 * sizeof (const char*)));
}


void dg_clearerrors (Bufferhandle* pBHarrayhead)
{
    Bufferhandle* pBH = NULL;
    const char* flag = dg_checkbharrayhead(pBHarrayhead);

    if (flag != dg_success) 
    {
        return;
    }

    pBHarrayhead->errorcount = 0;

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        return;
    }

    // seeing if there is a buffer handle for the error stack
    if (pBHarrayhead->nextunusedbyte < sizeof (Bufferhandle))
    {
        return;
    }

    // assuming handle is correct
    pBH = (Bufferhandle*)(pBHarrayhead->pbuf);
    pBH->nextunusedbyte = 0;
    
    
    
    // clear all wordlist element flags
}


void dg_clearerrorsanderrorline(Bufferhandle* pBHarrayhead)
{
    Bufferhandle* pBH = NULL;
    const char* flag = dg_checkbharrayhead(pBHarrayhead);

    if (flag != dg_success) 
    {
        return;
    }
    
    // trying to clear the error line buffer
    dg_clearbuffer(
        pBHarrayhead,
        DG_ERRORLINE_BUFFERID);

    pBHarrayhead->errorcount = 0;

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        return;
    }

    // seeing if there is a buffer handle for the error stack
    if (pBHarrayhead->nextunusedbyte < sizeof (Bufferhandle))
    {
        return;
    }

    // assuming handle is correct
    pBH = (Bufferhandle*)(pBHarrayhead->pbuf);
    pBH->nextunusedbyte = 0;
}


void dg_droptoerrorcount (
    Bufferhandle* pBHarrayhead,
    UINT64 newerrorcount)
{
    Bufferhandle* pBH;

    const char* flag;

    flag = dg_checkbharrayhead(pBHarrayhead);

    // no bufferhandle array case
    if (flag != dg_success)
    {
        return;
    }

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        return;
    }

    // no errorstack case
    if (pBHarrayhead->nextunusedbyte < sizeof (Bufferhandle))
    {
        if (pBHarrayhead->errorcount <= newerrorcount)
        {
            return;
        }
        else
        {
            pBHarrayhead->errorcount = newerrorcount;
        }
    }

    pBH = (Bufferhandle*)(pBHarrayhead->pbuf);

    if (pBH->nextunusedbyte / (2 * sizeof(UINT64)) <= newerrorcount)
    {
        return;
    }
    
    // clear all wordlist element flags for items dropped if element isn't somewhere else on error stack

    pBH->nextunusedbyte = (newerrorcount * 2 * sizeof(UINT32));
    pBHarrayhead->errorcount = newerrorcount;
}


void dg_replaceerrors(
    Bufferhandle* pBHarrayhead, 
    UINT64 olderrorbufferid,
    UINT64 olderroroffset,
    UINT64 newerrorbufferid,
    UINT64 newerroroffset)
{
    Bufferhandle* pBH = NULL;

//    const char* error = dg_noerroryet;
    UINT64 i = 0;
    UINT64 n = 0;
    UINT64 k = 0;
    UINT64* pints;
    
    const char* flag = dg_success;

    flag = dg_checkbharray(pBHarrayhead);

    if (flag != dg_success)
    {
        return;
    }
    
    // if no errors, just quickly returning
    if (0 == pBHarrayhead->errorcount)
    {
        return;
    }

    // buffer handle for error buffer is missing
    if (pBHarrayhead->nextunusedbyte < sizeof(Bufferhandle))
    {
        pBHarrayhead->errorcount = 0;
        return;
    }

    pBH = (Bufferhandle*)(pBHarrayhead->pbuf);

    // no memory allocated for error buffer
    if (pBH->pbuf == badbufferhandle)
    {
        pBHarrayhead->errorcount = 0;
        return;
    }

    // error buffer not locked to not grow
    if (pBH->growby != pBH->size)
    {
        pBHarrayhead->errorcount = 0;
        return;
    }

    if (pBH->growby != pBH->maxsize)
    {
        pBHarrayhead->errorcount = 0;
        return;
    }

    // error stack misaligned
    if ((pBH->nextunusedbyte % ( 2 * sizeof(UINT64*))) != 0)
    {
        // clearing stack
        pBHarrayhead->errorcount = 0;
        pBH->nextunusedbyte = 0;
        return;
    }

    // no errors on stack, yet error count is not 0
    //  shouldn't be possible to get this error if all access is through error routines
    if (pBH->nextunusedbyte == 0)
    {
        pBHarrayhead->errorcount = 0;
        return;
    }

    // get true number of errors on error stack
    n = ((pBH->nextunusedbyte) / (2 * sizeof(UINT64)));
    
    if (0 == n)
    {
        return;
    }
    
    pints = (UINT64*)pBH->pbuf;
    
    for (i = 0; i < n; i++)
    {
        k = 2*i;
        
        if ((pints[k+1] == olderrorbufferid) && (pints[k] == olderroroffset))
        {
            pints[k+1] = newerrorbufferid;
            pints[k] = newerroroffset;
        }
    }
}


void dg_getserrormessage (
    Bufferhandle* pBHarrayhead,
    UINT64 errorbufferid,
    UINT64 erroroffset,
    unsigned char** pperror,
    UINT64* perrorlength)
{
    const char* flag = dg_success;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    flag = dg_putuint64((UINT64*)pperror, (UINT64)badbufferhandle);

    if (flag != dg_success)
    {
        return;
    }
    
    flag = dg_putuint64((UINT64*)perrorlength, 0);

    if (flag != dg_success)
    {
        return;
    }
    
    if (DG_CORE_BUFFERID == errorbufferid)
    {
    
        *pperror = (unsigned char*)erroroffset;
        
        // setting maxlength
        *perrorlength = largestunsignedint;
    
        flag = dg_scanforbyte ((void*)erroroffset, perrorlength, 0);
    
        if (flag != dg_success)
        {
            // could return a message indicating couldn't get length instead
            *perrorlength = 0;
        }
        
        return;
    }
    
    if (DG_WORDNAME_FAKE_BUFFERID == errorbufferid)
    {
        *pperror = dg_getshlistelementnom (
            pBHarrayhead,
            0, // hlistheaderid, // hlist 0 reserved for the wordlist
            erroroffset, // elementid,
            perrorlength);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_droptoerrorcount(pBHarrayhead, olderrorcount);
            
            // could set error to a message indicating couldn't get hlist element name
            *pperror = (unsigned char*)badbufferhandle;
            *perrorlength = 0;
        }
        
        return;
    }
    
    if (DG_WORDVALUE_FAKE_BUFFERID == errorbufferid)
    {
        *pperror = dg_getshlistelementvalue (
            pBHarrayhead,
            0, // hlistheaderid, // hlist 0 reserved for the wordlist
            erroroffset, // elementid,
            perrorlength);
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_droptoerrorcount(pBHarrayhead, olderrorcount);
            
            // could set error to a message indicating couldn't get hlist element name
            *pperror = (unsigned char*)badbufferhandle;
            *perrorlength = 0;
        }
        
        return;
    }
    
    *pperror = dg_getpbufferoffset  (
        pBHarrayhead,
        errorbufferid,
        erroroffset);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_droptoerrorcount(pBHarrayhead, olderrorcount);
            
        // could set error to a message indicating couldn't get hlist element name
        *pperror = (unsigned char*)badbufferhandle;
        *perrorlength = 0;
    }
    
    // setting maxlength
    *perrorlength = largestunsignedint;
    
    flag = dg_scanforbyte ((void*)(*pperror), perrorlength, 0);
    
    if (flag != dg_success)
    {
        // could return a message indicating couldn't get length instead
        *perrorlength = 0;
    }
}


void dg_forthdoterrors (Bufferhandle* pBHarrayhead)
{
    UINT64 errorcount;
    unsigned char* perror;
    UINT64 errorlength;
    UINT64 i;
    UINT64 errorbufferid;
    UINT64 erroroffset;

    unsigned char c = '\n';
    unsigned char* punknownword;
 
    unsigned char* pbuffer;
    UINT64* pbufferlength;   

    errorcount = dg_checkerrorsonstack(pBHarrayhead);

    if (errorcount == 0)
    {
        if (dg_geterrorcount(pBHarrayhead) == 0)
        {
            dg_printzerostring(pBHarrayhead, (unsigned char*)"no errors\n");
        }
        else
        {
            dg_printzerostring(pBHarrayhead, (unsigned char*)"error count corrupt - no errors on error stack but error count is not 0\n");
        }

        return;
    }

    for (i = errorcount; i > 0; i--)
    {
        //error = dg_geterror(pBHarrayhead, i-1);
        
        dg_getbuffererror (
            pBHarrayhead, 
            i-1, //errorindex, 
            &erroroffset, 
            &errorbufferid);

        if (
            ((dg_evaluatebufferwordnotfounderror == (const char*)erroroffset) ||
            (dg_symbolnotfounderror == (const char*)erroroffset))
             && (DG_CORE_BUFFERID == errorbufferid))
        {
            punknownword = ::dg_getpbufferoffset(pBHarrayhead, DG_DATASPACE_BUFFERID, lastnotfoundword);

            if (punknownword != NULL)
            {
                dg_printzerostring(pBHarrayhead, (unsigned char*)" - word/symbol not found error (showing last word/symbol not found) >>>");
                dg_printzerostring(pBHarrayhead, (unsigned char*)punknownword);
                dg_printzerostring(pBHarrayhead, (unsigned char*)"<<<\n");
            }
        }
        else
        {
            dg_getserrormessage (
                pBHarrayhead,
                errorbufferid,
                erroroffset,
                &perror,
                &errorlength);
    
           //dg_printzerostring(pBHarrayhead, (unsigned char*)error);
            dg_writestdout(pBHarrayhead, perror, errorlength);

            dg_writestdout(pBHarrayhead, &c, 1);
        }

        // just in case
        //if (error == dg_errornotthatmanyerrors)
        if ((dg_errornotthatmanyerrors == (const char*)erroroffset) && (DG_CORE_BUFFERID == errorbufferid))
        {
            break;
        }
    }

    if (dg_geterrorcount(pBHarrayhead) > errorcount)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nerror stack overflowed\n");
    }

    if (dg_geterrorcount(pBHarrayhead) < errorcount)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\nerror count was less than errors on stack, this shouldn't happen\n");
    }
        
}




