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

// #include "../stdafx.h"
  
#include "../diapergluforth.h"
// #include <Windows.h>
// #include <httpext.h>
// #include <stdio.h>

// const char dg_success[] = "success";
// const char dg_badmemoryerror[] = "bad memory error";

const char dg_oserror[] = "operating system error";
const char dg_osexception[] = "operating system exception";
const char dg_outofmemoryerror[] = "out of memory error";
const char dg_invalidhandleerror[] = " - os invalid handle error";
const char dg_invalidfunctionerror[] = "invalid function error";

const char dg_sizenotxpagesizeerror[] = "size not a multiple of system page size error";

const char dg_filenotfounderror[]          = " - file not found error";
const char dg_pathnotfounderror[]          = " - path not found error";
const char dg_accessdeniederror[]          = " - access denied error";
const char dg_toomanyopenfileserror[]      = " - too many open files error";

const char dg_drivenotfounderror[] = " - drive not found error";
const char dg_devicenotfounderror[] = " - device not found error";
const char dg_devicenotreadyerror[] = " - device not ready error";
const char dg_filesystemunknownerror[] = " - file system not supported by operating system error";
const char dg_devicebrokenerror[] = " - device is broken error";
const char dg_fileinuseerror[] = " - file in use by something else error";
const char dg_fileislockederror[] = " - file is locked error";
const char dg_filesystemcorrupterror[] = " - file system corrupt error";
const char dg_filetoobigerror[] = " - file too big for this function.";
const char dg_filetypeunknownerror[] = " - file type unknown error";
const char dg_osdidlessthanavailableerror[] = " - operating system processed less than it said it could";
const char dg_invalidparametererror[] = " - invalid parameter error";
const char dg_notexecutablefileerror[] = " - not an executable file error";
const char dg_parametersovermaxsizeerror[] = " - parameter list's size over system size limit error";
const char dg_ioerror[] = " - input or output error";
const char dg_toomanysymboliclinkserror[] = " - path to file has too many symbolic links error.";
const char dg_pathorfilenametoolongerror[] = " - path or file name too long error";
const char dg_partofpathnotdirectoryerror[] = " - part of the path does not point to a directory error";
const char dg_fileopenforwriteerror[] = " - file open for write error";
const char dg_filelengthtoobigerror[] = " - file length is over size because it must fit into 32 bits";
const char dg_badprocessiderror[] = " - process does not exist or is not a child of the calling process";
const char dg_interruptedbysignalerror[] = " - call was interrupted and not restarted error";
const char dg_toomanyprocesseserror[] = " - too many processes error";
const char dg_freemutexwhilelockederror[] = " - can't free a mutex while it is locked error";
const char dg_woulddeadlockerror[] = " - waiting for mutex will cause a deadlock error";
const char dg_mutexisnotlockederror[] = " - mutex is not locked error";

const char dg_writeprotectederror[]        = " - write protected error";
const char dg_diskisfullerror[] = " - disk is full error";
const char dg_invaliduserbuffererror[] = " - invalid user buffer error, probably means too many pending i/o requests - os couldn't keep up and ran out of buffers";
const char dg_unknownwriteerror[] = " - unknown write error";
const char dg_couldnotgetpagelockerror[] = " - os could not get page lock on the caller's memory buffer error";

const char dg_segmentgoespastenderror[] = "- offset + length goes past end of buffer error";

const char dg_badmagicerror[] = " - file or structure's magic number not what was expected error";
const char dg_missingexporttableerror[] = " - library file's export table is missing error";
const char dg_exporttablebounderror[] = " - library file export table's declared size goes into something else's memory error";
const char dg_waitabandonederror[] = " - the wait was abandoned";


const char dg_scanforbytename[] = "dg_scanforbyte";
const char dg_comparebytesname[] = "dg_comparebytes";
const char dg_getuint64name[] = "dg_getuint64";
// const char dg_hctwostorename[] = "dg_hctwostore";


void dg_initpbharrayhead(Bufferhandle* pBHarrayhead)
{
    pBHarrayhead->growby = BHarraygrowby;
    pBHarrayhead->maxsize = BHarraymaxsize;
    pBHarrayhead->nextfreeindex = 0;
    pBHarrayhead->nextunusedbyte = 0;
    pBHarrayhead->pbuf = badbufferhandle;
    pBHarrayhead->size = 0;
    pBHarrayhead->id = BHarrayheadid;
    pBHarrayhead->pisapiecb = badbufferhandle;
    pBHarrayhead->errorcount = 0;
    pBHarrayhead->currentoffset = 0;
    pBHarrayhead->pfunctbl = 0;// dg_functiontable;
    // pBHarrayhead->diaperflags = 0;
}

UINT64 dg_getpagesize ()
{
    UINT64 x = 0; // pagesize is 32bit... this is for unsign extending value
    // structures must be aligned to 16 bytes... 2022 July 29
    // https://docs.microsoft.com/en-us/cpp/cpp/alignment-cpp-declarations?view=msvc-170
    // https://docs.microsoft.com/en-us/cpp/c-language/alignment-c?view=msvc-170

    alignas(16) SYSTEM_INFO mysysteminfo;

    GetSystemInfo(&mysysteminfo);

    // assumes little endian
    *((UINT32*)(&x)) = mysysteminfo.dwPageSize;

    return (x); // not sure what minimum resolution is
    // return (0x1000);
}

UINT64 dg_gettruesize()
{
    UINT64 desiredsize = sizeof(Bufferhandle) + jumpbufferlength;
    UINT64 pagesize = dg_getpagesize();
    UINT64 truesize = ((UINT64)((desiredsize - 1) / pagesize) + 1) * pagesize;

    return (truesize);
}

UINT64 dg_isdelimiter(char c)
{
    if (c == ' ') { return(FORTH_TRUE); } // space
    if (c == '\n') { return(FORTH_TRUE); } // line feed
    if (c == '\t') { return(FORTH_TRUE); } // tab
    if (c == '\v') { return(FORTH_TRUE); } // vertical tab I think
    if (c == '\b') { return(FORTH_TRUE); } // shouldn't see this one
    if (c == '\r') { return(FORTH_TRUE); } // carriage return
    if (c == '\f') { return(FORTH_TRUE); } // form feed I think

    return(FORTH_FALSE);
}


UINT64 dg_islineterminator(char c)
{
    if (c == '\n') { return(FORTH_TRUE); } // line feed
    if (c == '\v') { return(FORTH_TRUE); } // vertical tab I think
    if (c == '\b') { return(FORTH_TRUE); } // shouldn't see this one
    if (c == '\r') { return(FORTH_TRUE); } // carriage return
    if (c == '\f') { return(FORTH_TRUE); } // form feed I think

    return(FORTH_FALSE);
}


unsigned char dg_digittochar(UINT64 d)
{
    if (d > 35)
    {
        return('!');
    }

    if (d < 10)
    {
        return ((unsigned char)d + 0x30);
    }

    return ((unsigned char)d - 10 + 'A');
}

UINT64 dg_chartodigit(unsigned char c)
{
    if (c < '0')
    {
        return ((UINT64)-1);
    }
    if (c <= '9')
    {
        return ((UINT64)(c - '0'));
    }
    if (c < 'A')
    {
        return ((UINT64)-1);
    }
    if (c <= 'Z')
    {
        return ((UINT64)(c + 10 - 'A'));
    }

    return ((UINT64)-1);
}


UINT64 dg_chartodigitlowertoo(unsigned char c)
{
    if (c < '0')
    {
        return (0xffffffffffffffff);
    }
    if (c <= '9')
    {
        return ((unsigned int)(c - '0'));
    }
    if (c < 'A')
    {
        return (0xffffffffffffffff);
    }
    if (c <= 'F')
    {
        return ((unsigned int)(c + 10 - 'A'));
    }
    if (c < 'a')
    {
        return (0xffffffffffffffff);
    }
    if (c <= 'f')
    {
        return ((unsigned int)(c + 10 - 'a'));
    }

    return (0xffffffffffffffff);
}


UINT64 dg_pchartonumber(
    UINT8* pnumber,
    UINT64 length,
    UINT64 base,
    UINT64* flag)
{
    UINT64 i = 0;
    INT64 number = 0;
    UINT64 digit = 0;

    UINT64 negative = FORTH_FALSE;

    if (flag == (UINT64*)badbufferhandle)
    {
        return(0);
    }

    *flag = FORTH_FALSE;

    if (pnumber == (unsigned char*)badbufferhandle)
    {
        return(0);
    }

    if (length == 0)
    {
        return(0);
    }

    if (base < 2)
    {
        return(0);
    }

    if (base > 35)
    {
        return(0);
    }

    if (pnumber[0] == '-')
    {
        negative = FORTH_TRUE;
        i++;
    }

    while (i < length)
    {
        digit = dg_chartodigit(pnumber[i]);

        if (digit >= base)
        {
            *flag = FORTH_FALSE;
            break;
        }

        if (digit != 0xffffffffffffffff)
        {
            if (number <= (largestunsignedint / base))
            {
                number *= base;
            }
            else
            {
                number = largestunsignedint;
            }
            if (number <= (largestunsignedint - digit))
            {
                number += digit;
            }
            else
            {
                number = largestunsignedint;
            }

            i++;
            *flag = FORTH_TRUE;
        }
        else
        {
            *flag = FORTH_FALSE;
            break;
        }
    }

    if (negative != FORTH_FALSE)
    {
        number *= -1;
    }

    return (number);
}

// for FORTH floating point conversion
INT64 dg_pchartonumberskipperiod(
    UINT8* pnumber,
    UINT64 length,
    UINT64 base,
    UINT64* pindex,
    UINT64* pdigitsafterperiod)
{
    INT64 number = 0;
    UINT64 digit = 0;
    unsigned char c;

    UINT64 afterperiod = FORTH_FALSE;

    UINT64 negative = FORTH_FALSE;

    *pindex = 0;
    *pdigitsafterperiod = 0;

    if (pnumber == (unsigned char*)badbufferhandle)
    {
        return(0);
    }

    if (length == 0)
    {
        return(0);
    }

    if (pnumber[0] == '-')
    {
        negative = FORTH_TRUE;
        (*pindex)++;
    }

    if (pnumber[0] == '+')
    {
        (*pindex)++;
    }

    while ((*pindex) < length)
    {
        c = pnumber[(*pindex)];

        if (c == '.')
        {

            if (afterperiod != FORTH_FALSE)
            {
                break;
            }
            else
            {
                afterperiod = FORTH_TRUE;
                (*pindex)++;
            }
        }
        else
        {
            digit = dg_chartodigit(c);

            if (digit >= base)
            {
                break;
            }

            if (digit != 0xffffffffffffffff)
            {
                // need to check for overflow...
                if (number <= (largestsignedint / base))
                {
                    number *= base;
                }
                else
                {
                    number = largestsignedint;
                }

                if (number <= (largestsignedint - digit))
                {
                    number += digit;
                }
                else
                {
                    number = largestsignedint;
                }

                (*pindex)++;

                if (afterperiod == FORTH_TRUE)
                {
                    (*pdigitsafterperiod)++;
                }

            }
            else
            {
                break;
            }
        }
    }

    if (negative != FORTH_FALSE)
    {
        number *= -1;
    }

    return (number);
}


INT64 dg_pchartobase10numberandexponent(
    UINT8* pnumber,
    UINT64 length,
    INT64* pexponent,
    UINT64* pflag)
{
    UINT64 digitsafterperiod = 0;
    UINT64 index = 0;
    INT64 number = 0;
    unsigned char c;

    *pexponent = 0;
    *pflag = FORTH_FALSE;

    if (length == 0)
    {
        return(number);
    }

    // when this returns the index has to point to e E d or D 
    //  if the conversion was successful, if not the conversion failed
    number = dg_pchartonumberskipperiod(
        pnumber,
        length,
        10, // base,
        &index,  // pindex,
        &digitsafterperiod);

    if (index >= length)
    {
        // flag = FORTH_FALSE
        return(number);
    }

    c = pnumber[index];

    if ((c != 'e') &&
        (c != 'E') &&
        (c != 'd') &&
        (c != 'D'))
    {
        // flag = FORTH_FALSE
        return(number);
    }

    index++;

    if (index < length) // nothing after e E d E is acceptible and means exponent = 0
    {
        *pexponent = dg_pchartonumber(
            pnumber + index,
            length - index,
            10, // base,
            pflag);

        if (*pflag == FORTH_FALSE)
        {
            return(number);
        }
    }
    else
    {
        *pflag = FORTH_TRUE;
    }

    if ((*pexponent) >= ((INT64)largestnegativeint + (INT64)digitsafterperiod))
    {
        *pexponent = *pexponent - digitsafterperiod;
    }
    else
    {
        *pexponent = (INT64)largestnegativeint;
    }
    return(number);
}

FLOAT64 dg_u64times10totheu64tof64(
    INT64 number,
    INT64 exponent)
{
    FLOAT64 result;

    // need abs of exponent... and sign...
    if (exponent < 0)
    {
        result = 1 / (dg_tentothex(0 - exponent));
    }
    else
    {
        result = dg_tentothex(exponent);
    }

    // not sure what happens if there is overflow/underflow...
    result = dg_i64tof64(number) * result;

    return(result);
}

FLOAT64 dg_pchartof64(
    UINT8* pnumber,
    UINT64 length,
    UINT64* pflag)
{
    INT64 number;
    INT64 exponent;
    FLOAT64 result = 0.0;
    UINT64 i = 0;

    // this is for forth standard requirement for >FLOAT that
    //  a string of all 'blanks' be treated as 0.0, 
    //  I'm gonna assume 'blank' means delimiter, not just the space character
    //  this will also skip leading delimiters
    //  this also means a 0 length string will return 0.0
    while (i < length)
    {
        if (!(dg_isdelimiter(pnumber[i])))
        {
            break;
        }

        i++;
    }

    if (i >= length)
    {
        *pflag = FORTH_TRUE;
        return(result);
    }


    number = dg_pchartobase10numberandexponent(
        pnumber + i,
        length - i,
        &exponent,
        pflag);

    if (*pflag == FORTH_FALSE)
    {
        return(result);
    }

    // probably should check for overflow....
    result = dg_u64times10totheu64tof64(
        number,
        exponent);

    return(result);
}


UINT64 dg_hexdectonumber(
    UINT8* pnumber,
    UINT64 length,
    UINT64* pflag)
{
    UINT64 start = 0;
    UINT64 end = length;
    UINT64 length2;
    UINT64 base = 10;

    // not using trailing whitespace
    //  because html standard allows whitespace after numeric entry Dec 21, 2016
    while (end > 0)
    {
        if (dg_isdelimiter(pnumber[end - 1]))
        {
            end--;
        }
        else
        {
            break;
        }
    }

    // not using leading whitespace
    //  because html standard allows whitespace before numeric entry Dec 21, 2016
    while (start < end)
    {
        if (dg_isdelimiter(pnumber[start]))
        {
            start++;
        }
        else
        {
            break;
        }
    }

    // could skip one leading +
    if (start < end)
    {
        if ('+' == pnumber[start])
        {
            start++;
        }
    }

    length2 = (end - start);

    // only checking for hex 0x or 0X specifier
    // not checking for octal leading 0 specifier because
    //  it is deprecated in html standard Dec 21, 2016
    if (length2 >= 2)
    {
        if ((pnumber[start] == '0')
            && ((pnumber[start + 1] == 'x') || (pnumber[start + 1] == 'X')))
        {
            length2 = length2 - 2;
            start = start + 2;
            base = 16;
        }
    }

    return(dg_pchartonumber(
        pnumber + start,
        length2,
        base, // base,
        pflag));
}

const char* dg_putbyte(unsigned char* paddr, unsigned char c)
{
    const char* pError = dg_success;

    __try
    {
        *paddr = c;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_putuint16(UINT16* paddr, UINT16 n)
{
    const char* pError = dg_success;

    __try
    {
        *paddr = n;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_putuint32(UINT32* paddr, UINT32 n)
{
    const char* pError = dg_success;

    __try
    {
        *paddr = n;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_putuint64(UINT64* paddr, UINT64 n)
{
    const char* pError = dg_success;

    __try
    {
        *paddr = n;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_hctwostore(
    unsigned char* paddr, 
    UINT64* pud) 
{
    const char* pError = dg_success;

    __try
    {
        dg_hctwostoresub(paddr, pud);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_getbyte(unsigned char* paddr, unsigned char* pvalue)
{
    const char* pError = dg_success;

    __try
    {
        *pvalue = *paddr;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_getuint16(UINT16* paddr, UINT16* pvalue)
{
    const char* pError = dg_success;

    __try
    {
        *pvalue = *paddr;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_getuint32(UINT32* paddr, UINT32* pvalue)
{
    const char* pError = dg_success;

    __try
    {
        *pvalue = *paddr;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_getuint64(UINT64* paddr, UINT64* pvalue)
{
    const char* pError = dg_success;

    __try
    {
        *pvalue = *paddr;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_movebytes(
    unsigned char* psrc,    
    unsigned char* pdest,   
    UINT64 stringlength)    
{
    const char* pError = dg_success;

    __try
    {
        dg_movebytessub(psrc, pdest, stringlength);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_moveuint64s(
    UINT64* psrc,     
    UINT64* pdest,   
    UINT64  length)    
{
    const char* pError = dg_success;

    __try
    {
        dg_moveuint64ssub(psrc, pdest, length);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_movebytesforward(
    unsigned char* psrc,    // 0x08 
    unsigned char* pdest,   // 0x0C
    UINT64 stringlength)    // 0x10
{
    const char* pError = dg_success;

    __try
    {
        dg_movebytesforwardsub(psrc, pdest, stringlength);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_movebytesreverse(
    unsigned char* psrc,    // 0x08 
    unsigned char* pdest,   // 0x0C
    UINT64 stringlength)    // 0x10
{
    const char* pError = dg_success;

    __try
    {
        dg_movebytesreversesub(psrc, pdest, stringlength);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_scanforbyte(
    void* pbuf,         // 0x08
    UINT64* plength,    // 0x0C
    UINT64 value)       // 0x10
{
    const char* pError = dg_success;

    __try
    {
        dg_scanforbytesub(pbuf, plength, value);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_scanforuint64(
    void* pbuf,         // 0x08
    UINT64* plength,    // 0x0C
    UINT64 value)       // 0x10
{
    const char* pError = dg_success;

    __try
    {
        dg_scanforuint64sub(pbuf, plength, value);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_scanfornotbytereverse(
    void* pbuf,         // 0x08
    UINT64* plength,    // 0x0C
    UINT64 value)       // 0x10
{
    const char* pError = dg_success;

    __try
    {
        dg_scanfornotbytereversesub(pbuf, plength, value);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}




const char* dg_comparebytes(
    unsigned char* pstring1,    // rcx
    UINT64 string1length,       // rdx
    unsigned char* pstring2,    // r8
    UINT64 string2length,       // r9
    INT64* pflag)               // p5 on return stack
{
    const char* pError = dg_success;

    __try
    {
        dg_comparebytessub(pstring1, string1length, pstring2, string2length, pflag);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_fillwithbyte(
    unsigned char* pbuf, // rcx
    UINT64 length,       // rdx
    unsigned char value) // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_fillwithbytesub(pbuf, length, (UINT64)value);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_readallbytes(
    unsigned char* pbuf, // rcx
    UINT64 length)       // rdx
{
    const char* pError = dg_success;

    __try
    {
        dg_readallbytessub(pbuf, length);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_search(
    unsigned char* caddr1, // target string to search
    UINT64 numlefttocheck, // length of target string 
    unsigned char* caddr2, // string to search for in target string
    UINT64 u2,             // length of string to search for 
    unsigned char** pcaddrout) // pointer to found string or pointer to null
{
    const char* pError = dg_success;

    __try
    {
        dg_searchsub(caddr1, numlefttocheck, caddr2, u2, pcaddrout);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_addbytes(
    unsigned char* psrc,    // rdi // rcx
    unsigned char* pdest,   // rsi // rdx
    UINT64 stringlength,    // rdx // r8
    UINT64* pcarryout)      // rcx // r9
{
    const char* pError = dg_success;

    __try
    {
        dg_addbytessub(psrc, pdest, stringlength, pcarryout);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_adcbytes(
    unsigned char* psrc,    // rdi // rcx
    unsigned char* pdest,   // rsi // rdx
    UINT64 stringlength,    // rdx // r8
    UINT64* pcarryinout)    // rcx // r9
{
    const char* pError = dg_success;

    __try
    {
        dg_adcbytessub(psrc, pdest, stringlength, pcarryinout);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_sbbbytes(
    unsigned char* psrc,    // rdi // rcx
    unsigned char* pdest,   // rsi // rdx
    UINT64 stringlength,    // rdx // r8
    UINT64* pborrowinout)    // rcx // r9
{
    const char* pError = dg_success;

    __try
    {
        dg_sbbbytessub(psrc, pdest, stringlength, pborrowinout);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_andbytes(
    unsigned char* psrc,    // rdi  // rcx
    unsigned char* pdest,   // rsi  // rdx
    UINT64 stringlength)    // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_andbytessub(psrc, pdest, stringlength);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_orbytes(
    unsigned char* psrc,    // rdi  // rcx
    unsigned char* pdest,   // rsi  // rdx
    UINT64 stringlength)    // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_orbytessub(psrc, pdest, stringlength);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_xorbytes(
    unsigned char* psrc,    // rdi  // rcx
    unsigned char* pdest,   // rsi  // rdx
    UINT64 stringlength)    // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_xorbytessub(psrc, pdest, stringlength);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}

const char* dg_nandbytes(
    unsigned char* psrc,    // rdi  // rcx
    unsigned char* pdest,   // rsi  // rdx
    UINT64 stringlength)    // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_nandbytessub(psrc, pdest, stringlength);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_norbytes(
    unsigned char* psrc,    // rdi  // rcx
    unsigned char* pdest,   // rsi  // rdx
    UINT64 stringlength)    // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_norbytessub(psrc, pdest, stringlength);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_xnorbytes(
    unsigned char* psrc,    // rdi  // rcx
    unsigned char* pdest,   // rsi  // rdx
    UINT64 stringlength)    // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_xnorbytessub(psrc, pdest, stringlength);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_shlbytes(
    unsigned char* pdest,    // rdi  // rcx
    UINT64 stringlength,     // rsi  // rdx
    UINT64* pcarryout)       // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_shlbytessub(pdest, stringlength, pcarryout);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_shrbytes(
    unsigned char* pdest,    // rdi  // rcx
    UINT64 stringlength,     // rsi  // rdx
    UINT64* pcarryout)       // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_shrbytessub(pdest, stringlength, pcarryout);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_rclbytes(
    unsigned char* pdest,    // rdi  // rcx
    UINT64 stringlength,     // rsi  // rdx
    UINT64* pcarryinout)     // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_rclbytessub(pdest, stringlength, pcarryinout);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_rcrbytes(
    unsigned char* pdest,    // rdi  // rcx
    UINT64 stringlength,     // rsi  // rdx
    UINT64* pcarryinout)     // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_rcrbytessub(pdest, stringlength, pcarryinout);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_sarbytes(
    unsigned char* pdest,    // rdi  // rcx
    UINT64 stringlength,     // rsi  // rdx
    UINT64* pcarryout)       // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_sarbytessub(pdest, stringlength, pcarryout);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_notbytes(
    unsigned char* pdest,
    UINT64 stringlength) 
{
    const char* pError = dg_success;

    __try
    {
        dg_notbytessub(pdest, stringlength);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_reversebytes(
    unsigned char* pdest,
    UINT64 stringlength) 
{
    const char* pError = dg_success;

    __try
    {
        dg_reversebytessub(pdest, stringlength);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_incbytes(
    unsigned char* pdest,    // rdi  // rcx
    UINT64 stringlength,     // rsi  // rdx
    UINT64* pcarryout)      // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_incbytessub(pdest, stringlength, pcarryout);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_decbytes(
    unsigned char* pdest,    // rdi  // rcx
    UINT64 stringlength,     // rsi  // rdx
    UINT64* pborrowout)      // rdx  // r8
{
    const char* pError = dg_success;

    __try
    {
        dg_decbytessub(pdest, stringlength, pborrowout);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_mulu64tou64s(
    UINT64* pdest,           // rdi // rcx
    UINT64* psrc,            // rsi // rdx
    UINT64  u,               // rdx // r8
    UINT64  srclengthinu64s, // rcx // r9
    UINT64* pcarryout)       // r8  // param4 (after 4 shadow)
{
    const char* pError = dg_success;

    __try
    {
        dg_mulu64tou64ssub(pdest, psrc, u, srclengthinu64s, pcarryout);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


const char* dg_divu64sbyu64(
    UINT64* pdest,            // rdi // rcx // quotient and dividend
    UINT64* premainder,       // rsi // rdx // premainder
    UINT64  u,                // rdx // r8  // divisor
    UINT64  destlengthinu64s) // rcx // r9  // 
{
    const char* pError = dg_success;

    __try
    {
        dg_divu64sbyu64sub(pdest, premainder, u, destlengthinu64s);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        pError = dg_badmemoryerror;
    }

    return (pError);
}


/*
double dg_forthfsfrom (
     Bufferhandle* pBHarrayhead)       // 0x08
{
    double result;

    __try
    {
        result = dg_forthfsfromsub(pBHarrayhead);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        result = 0.0;
    }

    return (result);
}

float dg_forthf64from (
     Bufferhandle* pBHarrayhead)       // 0x08
{
    float result;

    __try
    {
        result = dg_forthf64fromsub(pBHarrayhead);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        result = 0.0;
    }

    return (result);
}
*/

const char dg_getmicrosecondssince1970Jan01name[] = "dg_getmicrosecondssince1970Jan01";

UINT64 dg_getmicrosecondssince1970Jan01()
{
    const char* perror;
    ULARGE_INTEGER mymicrosecondssince1601jan01;
    FILETIME myfiletime; // 64 bit value representing 0.1 microseconds since Jan 01, 1601

    GetSystemTimeAsFileTime(&myfiletime);

    mymicrosecondssince1601jan01.HighPart = myfiletime.dwHighDateTime;
    mymicrosecondssince1601jan01.LowPart = myfiletime.dwLowDateTime;

    mymicrosecondssince1601jan01.QuadPart = (mymicrosecondssince1601jan01.QuadPart - DG_WIN64_FILETIME_1970_JAN_1) / 10;

    return(mymicrosecondssince1601jan01.QuadPart);
}

const char* dg_mallocname = "dg_malloc";

const char* dg_malloc(
     void** phandle,
     UINT64 size, 
     const char* forceerrorflag)
{
    // HANDLE hheap = NULL;
    const char* flag;
    UINT64 pagesize;
    UINT64 lasterror;

    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);

    }
    
    // if (forceerrorflag == dg_outofmemoryerror)
    // {
    //    return(forceerrorflag); 
    // }

    // if (forceerrorflag == dg_badmemoryerror)
    // {
    //     return(forceerrorflag);
    // }

    // check memory at phandle
    flag = dg_putuint64(
        (UINT64*)phandle, 
        (UINT64)badbufferhandle);

    if (flag != dg_success)
    {
        return (flag);
    }

    // if (forceerrorflag == dg_osexception) 
    // {
    //     return(forceerrorflag);
    // }

    pagesize = dg_getpagesize();

    if ((size % pagesize) != 0)
    {
        return(dg_sizenotxpagesizeerror);
    }

    *phandle = ::VirtualAlloc(
        NULL,
        size,
        MEM_COMMIT,
        PAGE_EXECUTE_READWRITE);

    if (*phandle == NULL)
    {
        lasterror = ::GetLastError();

        if ((lasterror == ERROR_OUTOFMEMORY) || (lasterror == ERROR_NOT_ENOUGH_MEMORY))
        {
            return(dg_outofmemoryerror);
        }

        return(dg_oserror);
    }

    /*
    __try
    {
        hheap = ::GetProcessHeap();
        
        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // hheap = (HANDLE)dg_callprocaddressalign16((UINT32*)&GetProcessHeap, 0);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }
    
    if ((hheap == NULL) || (forceerrorflag == dg_oserror))
    {
        return(dg_oserror);
    }

    __try
    {
        // serialized, not generating exceptions, not zeroing memory
        //  putting it in try blocks anyways just in case
        //  all operating system calls get try blocks
        *phandle = ::HeapAlloc(hheap, 0, size);
        
        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // *phandle = (void*)dg_callprocaddressalign16((UINT32*)&HeapAlloc, 3, hheap, 0, size);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }

    if ((*phandle == NULL) || (forceerrorflag == dg_badmemoryerror))
    {
        *phandle = badbufferhandle;
        return(dg_outofmemoryerror);
    }
    */

    return(dg_success);
}



const char* dg_reallocname = "dg_realloc";

const char* dg_realloc(
    void** phandle, 
    UINT64 oldsize, // needed for Linux compatibility
    UINT64 newsize, 
    const char* forceerrorflag)
{
    HANDLE hheap = NULL;
    void* pbuf2 = NULL;
    const char* flag;
    UINT64 myhandle;

    if (forceerrorflag == dg_badmemoryerror)
    {
        return(forceerrorflag); 
    }

    // check memory at phandle
    flag = dg_getuint64((UINT64*)phandle, &myhandle);

    if (flag != dg_success)
    {
         return(flag);
    }

    
    if ( myhandle == (UINT64)badbufferhandle)
    {
        return(dg_success);
    }
    
    if (forceerrorflag == dg_osexception) 
    {
        return(forceerrorflag);
    }

    //if (oldsize <= newsize)
    //{
    //    return(dg_success);
    //}

    // always relocate, for testing purposes
    
    flag = dg_malloc(&pbuf2, newsize, forceerrorflag);

    if (flag != dg_success)
    {
        return (flag);
    }

    flag = dg_movebytes(
        (unsigned char*)*phandle, 
        (unsigned char*)pbuf2, 
        oldsize);

    if (flag != dg_success)
    {
        return (flag);
    }

    flag = dg_free(*phandle, oldsize, forceerrorflag);
    

    *phandle = pbuf2;

    return(dg_success);
}



const char* dg_freename = "dg_free";

const char* dg_free(
        void* pbuf, 
        UINT64 size, 
        const char* forceerrorflag)
{
    UINT64 bflag;

    // HANDLE hheap;

    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }

    if (pbuf == badbufferhandle)
    {
        return (dg_success);
    }

    bflag = VirtualFree(
        pbuf,
        0, //size,  // when using MEM_RELEASE, the size must be 0
        MEM_RELEASE);

    if (bflag == 0)
    {
        return (dg_oserror);
    }

    /*
    __try
    {
        hheap = ::GetProcessHeap();
        
        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // hheap = (HANDLE)dg_callprocaddressalign16((UINT32*)&GetProcessHeap, 0);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_osexception);
    }

    if (hheap == NULL)
    {
        return (dg_oserror);
    }
    
    __try
    {
        // serialized
        bflag = ::HeapFree(hheap, 0, pbuf);
        
        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // bflag = dg_callprocaddressalign16((UINT32*)&HeapFree, 3, hheap, 0, pbuf);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_osexception);
    }

    if (bflag == 0)
    {
        return (dg_oserror);
    }
    */

    return (dg_success);
}



const char* dg_writeisapi(
    EXTENSION_CONTROL_BLOCK* lpECB, 
    unsigned char* pbuf, 
    UINT64 length,
    const char* forceerrorflag)
{
    HCONN myconnid;
    UINT64 bflag = 1;
    UINT64 totalwritten = 0;
    UINT64 numwritten = 0;
    UINT64 lastError;

    __try
    {
        myconnid = lpECB->ConnID;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    __try
    {
        while (totalwritten < length)
        {
            numwritten = length - totalwritten;

            // bflag = dg_callprocaddressalign16(
            //   (UINT32*)(lpECB->WriteClient), // apparently no & is required in front of function
            //   4, 
            //   myconnid,
            //   (void*)(pbuf+totalwritten),
            //   (unsigned long*)(&numwritten),
            //   HSE_IO_SYNC);

            bflag = lpECB->WriteClient(
                myconnid,
                (void*)(pbuf+totalwritten),
                (unsigned long*)(&numwritten),
                HSE_IO_SYNC);

            totalwritten += numwritten;

            if (bflag == 0)
            {
                break;
            }

            if (totalwritten < length)
            {
                // should do a release here
                // dg_callprocaddressalign16(
                //   (UINT32*)&Sleep, 
                //   1, 
                //   1);

                Sleep(1);
            }
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_osexception);
    }

    if (bflag == 0)
    {
        // could get last error and push it to error stack if os 
        //  garauntees memory at error message address is stable
        //  and error message is a 0 string

        lastError = GetLastError();
        // lastError = dg_callprocaddressalign16((UINT32*)&GetLastError, 0);
        
        
        if (lastError == ERROR_IO_PENDING)
        {
            // if this happens, it looks like Diaperglu might not finish sending the stuff...
            // fix this case
            return (dg_success);
        }
        
        if (lastError == ERROR_NOT_ENOUGH_MEMORY)
        {
            return (dg_outofmemoryerror);
        }
        
        if (lastError == ERROR_INVALID_USER_BUFFER)
        {
            return (dg_invaliduserbuffererror);
        }
        
        if (lastError == ERROR_NOT_ENOUGH_QUOTA)
        {
            return (dg_couldnotgetpagelockerror);
        }

        if (lastError == ERROR_NOACCESS)
        {
            return (dg_badmemoryerror);
        }

        return (dg_unknownwriteerror);
    }
    
    return(dg_success);
}



const char* dg_readisapi(
    EXTENSION_CONTROL_BLOCK* lpECB, 
    unsigned char* pbuf, 
    UINT64 length,
    const char* forceerrorflag)
{
    HCONN myconnid;

    UINT64 bflag;
    
    if (length == 0)
    {
        return(dg_success);
    }

    if (length > 0xFFFFFFFF)
    {
        return(dg_filelengthtoobigerror);
    }

    __try
    {
        myconnid = lpECB->ConnID;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    __try
    {
        bflag = lpECB->ReadClient(
            myconnid,
            (void*)pbuf,
            (unsigned long*)(&length));

        // bflag = dg_callprocaddressalign16(
        //    (UINT32*)(lpECB->ReadClient), // apparently no & is required in front of function
        //    3, 
        //    myconnid,
        //  (void*)pbuf,
        //  (unsigned long*)(&length));
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_osexception);
    }

    if (bflag == 0)
    {
        // could get last error and push it to error stack if os 
        //  garauntees memory at error message address is stable
        //  and error message is a 0 string
        return (dg_oserror);
    }

    return(dg_success);
}


INT64 dg_getch() 
{

    int fgotcharacter = 0;

    MSG mymsg;

    INPUT_RECORD myinputrecord;
    
    int c = 0;

    unsigned long mynumread = 0;

    HANDLE myhstdin = NULL;

    myhstdin = GetStdHandle(STD_INPUT_HANDLE);

    while (fgotcharacter == 0)
    {
        // Clear app message que
        while(PeekMessage(&mymsg, NULL, 0, 0, PM_REMOVE) != 0)
        {
            TranslateMessage(&mymsg);

            DispatchMessage(&mymsg);
        }

        // Check console message que
        PeekConsoleInput(myhstdin, &myinputrecord, 1, &mynumread);

        // check for error

        if (mynumread != 0)
        {
            // if its a key message, extract key and exit loop
            if (myinputrecord.EventType == KEY_EVENT)
            {
                if (myinputrecord.Event.KeyEvent.bKeyDown != 0)
                {
                    c = (int)myinputrecord.Event.KeyEvent.uChar.AsciiChar;

                    if (c != 0)
                    {
                        fgotcharacter = -1;
                        Sleep(0);
                    }                
                }
            }
            
            // remove message from the console message que
            ReadConsoleInput(myhstdin, &myinputrecord, 1, &mynumread);      
        }
        else
        {
            Sleep(10);
            // WaitMessage();
        }
    }

    return((INT64)c);
}

/*
unsigned char dg_limitchartosimpleedit (unsigned char c)
{
    if ((8 == c) || (0x7f == c) ) 
    { 
        return (8);  // keep backspace delete ( and eventually escape ) 
    } 

    if (dg_islineterminator (c) != FORTH_FALSE) 
    { 
        return(0x0a); 
    }
   
    if (dg_isdelimiter(c) != FORTH_FALSE) 
    { 
        return(0x20);  // changing tab and others to space 
    } 

    if ((c < 0x20) || (c > 0x7f)) 
    { 
        return(0); // accepting only text
    }

    return(c);
}

UINT64 dg_getlinefromconsolewithecho(
    unsigned char* pbuf,
    UINT64 maxlength) 
{

    INT32 fgotcharacter = 0;

    MSG mymsg;

    INPUT_RECORD myinputrecord;
    
    unsigned char c = 0;

    DWORD mynumread = 0;
    DWORD mynumwritten = 0;

    HANDLE myhstdin = NULL;

    HANDLE myhstdout = NULL;

    UINT64 bufpos = 0;

    if (0 == maxlength)
    {
        return(0);
    }

    myhstdin = GetStdHandle(STD_INPUT_HANDLE);

    myhstdout = GetStdHandle(STD_OUTPUT_HANDLE);

    while (c != 0x0a)
    {
        fgotcharacter = 0;

        while (fgotcharacter == 0)
        {
            // Clear app message que
            while(PeekMessage(&mymsg, NULL, 0, 0, PM_REMOVE) != 0)
            {
                TranslateMessage(&mymsg);

                DispatchMessage(&mymsg);
            }

            // Check console message que
            PeekConsoleInput(myhstdin, &myinputrecord, 1, &mynumread);

            // check for error

            if (mynumread != 0)
            {
                // if its a key message, extract key and exit loop
                if (myinputrecord.EventType == KEY_EVENT)
                {
                    if (myinputrecord.Event.KeyEvent.bKeyDown != 0)
                    {
                        c = myinputrecord.Event.KeyEvent.uChar.AsciiChar;

                        c = dg_limitchartosimpleedit(c);

                        if (c != 0)
                        {
                            fgotcharacter = -1;

                            Sleep(0);
                        }                  
                    }
                }
            
                // remove message from the console message que
                ReadConsoleInput(myhstdin, &myinputrecord, 1, &mynumread);      
            }
            else
            {
                Sleep(10);
                // WaitMessage();
            }
        }

        if (8 == c) // got backspace
        {
            if (bufpos > 0)
            {
                bufpos--
                pbuf[bufpos] = 0;

                // need to write backspace space backspace
            }
        }
        else 
        {
             if (bufpos < maxlength)
             {
                 pbuf[bufpos] = c;
                 bufpos++;
             }

             // need to write character
        }

    }

    return(bufpos);
}
*/

// option1: ptr to buf and max length
//   routine puts characters into buf until cr is found
//   if user tries to backspace off start, just stop at the start
//   if user tries to enter characters past the end... ignore or change last character

// option2: use a bufferid
//   routine pushes or pops characters to/from buffer... can get errors..

// option1 is better I think... since it's just getting characters from a user


// https://docs.microsoft.com/en-us/windows/console/console-handles
// https://docs.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea

// if reading from the console... use a message pump...

const char* dg_readfilename =   "dg_readfile";

const char* dg_readfile(
     Bufferhandle* pBHarrayhead,
     UINT64 fileid, 
     unsigned char* pbuf,
     UINT64 length,
     UINT64 timeout,
     UINT64* pnumread,
     const char* forceerrorflag)
{    
    int flag = 0;
    DWORD oserror;
    const char* result = dg_success;
    const char* filetype;
    INT64 c;
    const char* perror;

    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }

    *pnumread = 0; // to clear out the high 32 bits

    // code assumes length is not 0 later on in this routine
    if (length == 0)
    {
        return(dg_success);
    }

    if (length > 0xFFFFFFFF)
    {
        return(dg_filelengthtoobigerror);
    }
/*
    perror = dg_getfiletype(
        pBHarrayhead,
        fileid,
        &filetype,
        dg_success);

    // if filetype = console, length = 1 then do dg_getch to use windows message pump
    if ((dg_filetypeconsole == filetype) && (1 == length)) 
    {
        c = dg_getkeywithsimpleecho();

        perror = dg_putuint64(
            pnumread,
            1);

        if (perror != dg_success)
        {
            return(perror);
        }

        perror = dg_putbyte(
            pbuf,
            (unsigned char)c);

        return(perror);
    }
*/
    __try
    {
        flag = ::ReadFile(
           (HANDLE)fileid, 
           pbuf, 
           length, 
           (LPDWORD)pnumread, 
           NULL);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }

    // windows ReadFile synchronous results
    //  flag = 0, numread = 0; end of file
    //  flag != 0, success
    //  

    if (0 == flag)
    {
        __try
        {
            oserror = ::GetLastError();
            
            // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
            // oserror = dg_callprocaddressalign16((UINT32*)&GetLastError, 0);
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            return(dg_osexception);
        }

        if (ERROR_MORE_DATA == oserror)
        {
            // this isn't an error the way this engine uses readfile
            return (dg_success);
        }

        if (ERROR_BROKEN_PIPE == oserror)
        {
            // this means the pipe was closed
            *pnumread = 0;
            return (dg_success);
        }

        if (ERROR_NOT_ENOUGH_MEMORY == oserror)
        {
            // I think this is for asynchronous only so we should not see it
            //  we could try waiting instead of returning an error...
            return (dg_outofmemoryerror);
        }

        if (ERROR_INVALID_USER_BUFFER == oserror)
        {
            // I think this is for asynchronous only so we should not see it
            //  we could try waiting instead of returning an error...
            return (dg_outofmemoryerror);
        }
        
        return (dg_oserror);
    }

    // need to parse other error conditions here

    return(dg_success);
}



const char* dg_writefilename = "dg_writefile";

const char* dg_writefilesub(
     Bufferhandle* pBHarrayhead,
     UINT64 fileid,
     unsigned char* pbuf,
     UINT64 length,
     const char* forceerrorflag)
{
    DWORD numwritten = 0;
    DWORD totalwritten = 0;
    INT64 flag = 1;
    UINT64 badpisapi = FORTH_FALSE;
    UINT64 lastError;

    EXTENSION_CONTROL_BLOCK* lpECB;

    if (length > 0xFFFFFFFF)
    {
        return(dg_filelengthtoobigerror);
    }
    
    __try
    {
        lpECB = (EXTENSION_CONTROL_BLOCK*)pBHarrayhead->pisapiecb;
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        //ignoring bad pBHarrayhead problems on purpose
        badpisapi = FORTH_TRUE;
    }

    if (badpisapi == FORTH_FALSE)
    {
        if ((lpECB != (EXTENSION_CONTROL_BLOCK*)-1) && (isapistdinfilehandle == fileid))
        {
            // can't write to isapi stdin    
            return (dg_success);
        }

        // isapi stdout
        if ((lpECB != (EXTENSION_CONTROL_BLOCK*)-1) && (isapistdoutfilehandle == fileid))
        {
            return(dg_writeisapi(
                lpECB,
                pbuf,
                length,
                dg_success)
                );
        }

        // isapi stderr
        if ((lpECB != (EXTENSION_CONTROL_BLOCK*)-1) && (isapistderrfilehandle == fileid))
        {
            // can't write to isapi stderr I think
            // doesn't have one
            return (dg_success);
        }
    }

    __try
    {
        
            // windows os won't let me set timeout for stdout set to console
            //flag = ::SetCommTimeouts(hfile, &timeouts);
        

        

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
        //   realigns the stack for 64 bit code.

        // keep tryin till it's all gone... Windows may not write everything you asked, especially on XP and earlier.
        // Something about only having 64K of buffer space for I/O shared among everything in the system.
        // This also means the largest size you can write is 64k
        while (totalwritten < length)
        {
            flag = ::WriteFile(
                (HANDLE)fileid, 
                pbuf + totalwritten, 
                length - totalwritten, 
                &numwritten, 
                NULL);

            // flag = dg_callprocaddressalign16(
            //    (UINT32*)&WriteFile, 
            //    5, 
            //    fileid, 
            //    pbuf + totalwritten, 
            //    length - totalwritten, 
            //    &numwritten, 
            //    NULL);

            totalwritten += numwritten;

            if (flag == 0)
            {
                break;
            }

            if (totalwritten < length)
            {
                ::Sleep(1);
                // should do a release here
                // dg_callprocaddressalign16(
                //    (UINT32*)&Sleep, 
                //    1, 
                //    1);
            }
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }

    if (flag == 0)
    {
        lastError = ::GetLastError();
        
        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // lastError = dg_callprocaddressalign16((UINT32*)&GetLastError, 0);
        
        if (lastError == ERROR_IO_PENDING)
        {
            return (dg_success);
        }
        
        if (lastError == ERROR_NOT_ENOUGH_MEMORY)
        {
            return (dg_outofmemoryerror);
        }
        
        if (lastError == ERROR_INVALID_USER_BUFFER)
        {
            return (dg_invaliduserbuffererror);
        }
        
        if (lastError == ERROR_NOT_ENOUGH_QUOTA)
        {
            return (dg_couldnotgetpagelockerror);
        }

        if (lastError == ERROR_NOACCESS)
        {
            return (dg_badmemoryerror);
        }

        return(dg_unknownwriteerror);
    }
    
    __try
    {
        ::FlushFileBuffers((HANDLE)fileid);

        // force write to finish before returning from this subroutine
          // this is necessary because Windows writes from the buffer passed in and may not be done with the
          // the write when the WriteFile returns
        // flag = dg_callprocaddressalign16(
        //    (UINT32*)&FlushFileBuffers, 
        //    1, 
        //    fileid);
        
        // ignoring return flag since trying to close the console WILL return an error
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }

    return (dg_success);
}


const char* dg_writefile(
     Bufferhandle* pBHarrayhead,
     UINT64 fileid,
     unsigned char* pbuf,
     UINT64 length,
     const char* forceerrorflag)
{
    UINT64 i = 0;

    UINT64 writelength;

    const char* pError = dg_success;

    // to force compiler to make mybuf page aligned, page size on Windows is 8 bytes.
    //UINT64 x = 0;

    //unsigned char mybuf[0x1000];


    while (i < length)
    {
        if ((length - i) < 0x1000)
        {
            writelength = length - i;
        }
        else
        {
            writelength = 0x1000;
        }

        // doing copy to align write buffer to page...
          // Vista may require this...
          
        //dg_movebytes(pbuf + i, (unsigned char*)mybuf, writelength);

        pError = dg_writefilesub(
            pBHarrayhead,
            fileid,
            (unsigned char*)pbuf + i,
            writelength,
            forceerrorflag);

        i = i + writelength;

        if (pError != dg_success)
        {
            break;
        }
    }

    return(pError);
}



// no character translation for console
const char* dg_writestdoutrawname = "dg_writestdoutraw";

const char* dg_writestdoutraw(
    Bufferhandle* pBHarrayhead, 
    unsigned char* pbuf,
    UINT64 length)
{
    DWORD oldmode;
    UINT64 fileid;
    const char* filetype;

    const char* perror;

    perror = dg_gethstdout(
        pBHarrayhead,
        &fileid,
        dg_success);

    if (perror != dg_success)
    {
        return (perror);
    }

    perror = dg_getfiletype(
        pBHarrayhead,
        fileid,
        &filetype,
        dg_success);

    if (filetype != dg_filetypeconsole)
    {
        // I wonder if we could catch html mode?
        return(dg_writefile(
            pBHarrayhead,
            fileid,
            pbuf,
            length,
            dg_success)
        );
    }

    // setting windows console to non translation mode
    __try
    {
        ::GetConsoleMode((HANDLE)fileid, &oldmode);

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // dg_callprocaddressalign16(
        //    (UINT32*)&GetConsoleMode, 
        //    2, 
        //    fileid, 
        //    &oldmode);

        ::SetConsoleMode((HANDLE)fileid, 0);

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // dg_callprocaddressalign16(
        //    (UINT32*)&SetConsoleMode, 
        //    2, 
        //    fileid, 
        //    0);

    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }
    
    perror = ::dg_writefile(
        pBHarrayhead,
        fileid,
        pbuf,
        length,
        dg_success);

    // restoring windows console
    __try
    { 
        ::SetConsoleMode((HANDLE)fileid, oldmode);

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // dg_callprocaddressalign16(
        //    (UINT32*)&SetConsoleMode, 
        //    2, 
        //    fileid, 
        //    oldmode);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }

    return (perror);
}



const char* dg_closefilename = "dg_closefile";

const char* dg_closefile(
     UINT64 fileid,
     const char* forceerrorflag)
{
    UINT64 flag = 0;

    __try
    {
        flag = ::CloseHandle((HANDLE)fileid);

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // flag = dg_callprocaddressalign16(
        //    (UINT32*)&CloseHandle, 
        //    1, 
        //    fileid);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }

    if (flag == 0)
    {
        // need to parse error here
        return(dg_oserror);
    }
    
    return (dg_success);
}



const char* dg_filetypeconsole  = "console";
const char* dg_filetypepipe     = "pipe";
const char* dg_filetypedisk     = "disk";
const char* dg_filetypeunknown  = "unknown";

const char* dg_getfiletypename = "dg_getfiletype";

const char* dg_getfiletype(
     Bufferhandle* pBHarrayhead,
     UINT64 fileid,
     const char** pfiletype,
     const char* forceerrorflag)
{
    UINT64 winfiletype = FILE_TYPE_UNKNOWN;
    unsigned long lasterror = 0;

    EXTENSION_CONTROL_BLOCK* lpECB;

    __try
    {
        *pfiletype = dg_filetypeunknown;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }

    // see if this is isapi stdin 
    __try
    {
        lpECB = (EXTENSION_CONTROL_BLOCK*)pBHarrayhead->pisapiecb;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    if ((lpECB != (EXTENSION_CONTROL_BLOCK*)-1) && (isapistdinfilehandle == fileid))
    {
        __try
        {
            *pfiletype = dg_filetypepipe;
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            return(dg_badmemoryerror);
        }
        
        return (dg_success);        
    }

    // isapi stdout
    if ((lpECB != (EXTENSION_CONTROL_BLOCK*)-1) && (isapistdoutfilehandle == fileid))
    {
        __try
        {
            *pfiletype = dg_filetypepipe;
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            return(dg_badmemoryerror);
        }
        
        return (dg_success);
    }

    // isapi stderr
    if ((lpECB != (EXTENSION_CONTROL_BLOCK*)-1) && (isapistderrfilehandle == fileid))
    {
        __try
        {
            *pfiletype = dg_filetypepipe;
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            return(dg_badmemoryerror);
        }
        
        return (dg_success);
    }

    __try
    {
        winfiletype = ::GetFileType((HANDLE)fileid);

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // winfiletype = dg_callprocaddressalign16(
        //    (UINT32*)&GetFileType, 
        //    1, 
        //    fileid);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_osexception);
        //result = dg_getfiletypegetfileexception;
    }
    
    if (winfiletype == FILE_TYPE_CHAR)
    {
        *pfiletype = dg_filetypeconsole;
        return (dg_success);
    }
    else if (winfiletype == FILE_TYPE_DISK)
    {
        *pfiletype = dg_filetypedisk;
        return (dg_success);
    }
    else if (winfiletype == FILE_TYPE_PIPE)
    {
        *pfiletype = dg_filetypepipe;
        return (dg_success);
    }
    else if (winfiletype != FILE_TYPE_UNKNOWN)
    {
        //It is some new windows file type
        //leave *pfiletype set to unknown
        return (dg_success);
    }

    // winfiletype is unknown

    __try
    {
        lasterror = ::GetLastError();

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // lasterror = dg_callprocaddressalign16(
        //    (UINT32*)&GetLastError, 
        //    1, 
        //    fileid);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_osexception);
    }
        
    if (NO_ERROR == lasterror)
    {
        return (dg_success);
    }

    return (dg_oserror);
}



const char* dg_gethstdinname = "dg_gethstdin";

const char* dg_gethstdin(
     Bufferhandle* pBHarrayhead,
     UINT64* pfileid,
     const char* forceerrorflag)
{
    EXTENSION_CONTROL_BLOCK* lpECB;

    __try
    {
        *pfileid = (UINT64)-1;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    lpECB = (EXTENSION_CONTROL_BLOCK*)pBHarrayhead->pisapiecb;

    if (pBHarrayhead->pisapiecb != (void*)-1)
    {
        *pfileid = isapistdinfilehandle;
        return (dg_success);        
    }

    __try
    {
        *pfileid = (UINT64)::GetStdHandle(STD_INPUT_HANDLE);

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // *pfileid = dg_callprocaddressalign16(
        //    (UINT32*)&GetStdHandle, 
        //    1, 
        //    STD_INPUT_HANDLE);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }

    // the IIS that comes with Vista returns INVALID_HANDLE_VALUE if stdin is not being used
    if (*pfileid == (UINT64)INVALID_HANDLE_VALUE)
    {
        return (dg_oserror);
    }
    
    return(dg_success);
}



const char* dg_gethstdoutname = "dg_gethstderror";

const char* dg_gethstdout(
     Bufferhandle* pBHarrayhead,
     UINT64* pfileid,
     const char* forceerrorflag)
{
    EXTENSION_CONTROL_BLOCK* lpECB;

    __try
    {
        *pfileid = (UINT64)-1;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    lpECB = (EXTENSION_CONTROL_BLOCK*)pBHarrayhead->pisapiecb;

    if (pBHarrayhead->pisapiecb != (void*)-1)
    {
        *pfileid = isapistdoutfilehandle;
        return (dg_success);        
    }

    __try
    {
        *pfileid = (UINT64)::GetStdHandle(STD_OUTPUT_HANDLE);

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // *pfileid = dg_callprocaddressalign16(
        //    (UINT32*)&GetStdHandle, 
        //    1, 
        //    STD_OUTPUT_HANDLE);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }

    if (*pfileid == (UINT64)INVALID_HANDLE_VALUE)
    {
        return(dg_oserror);
    }
    
    return(dg_success);
}



const char* dg_gethstderrorname = "dg_gethstderror";

const char* dg_gethstderror(
     Bufferhandle* pBHarrayhead,
     UINT64* pfileid,
     const char* forceerrorflag)
{
    EXTENSION_CONTROL_BLOCK* lpECB;

    __try
    {
        *pfileid = (UINT64)-1;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    lpECB = (EXTENSION_CONTROL_BLOCK*)pBHarrayhead->pisapiecb;

    if (pBHarrayhead->pisapiecb != (void*)-1)
    {
        *pfileid = isapistderrfilehandle;
        return (dg_success);        
    }

    __try
    {
        *pfileid = (UINT64)::GetStdHandle(STD_ERROR_HANDLE);

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // *pfileid = dg_callprocaddressalign16(
        //    (UINT32*)&GetStdHandle, 
        //    1, 
        //    STD_ERROR_HANDLE);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }

    if (*pfileid == (UINT64)INVALID_HANDLE_VALUE)
    {
        return(dg_oserror);
    }
    
    return(dg_success);
}



const char* dg_getfilelengthname = "dg_getfilelength";

const char* dg_getfilelength(
     Bufferhandle* pBHarrayhead,
     UINT64 fileid,
     UINT64* pfilelength,
     const char* forceerrorflag)
{
    const char* flag = dg_success;
    const char* result = dg_success;
    const char* filetype = NULL;

    // DWORD filelengthlo = 0;
    // DWORD filelengthhi = 0;

    long bflag = 0;

    alignas(16) MSG mymsg;
    alignas(16) INPUT_RECORD myinputrecord;
    unsigned long mynumread = 0;

    BOOL retflag;
    UINT32 lasterror;

    alignas(16) struct _FILE_STANDARD_INFO mystandardinfo;

    EXTENSION_CONTROL_BLOCK* lpECB;

    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }

    // see if valid memory at pfilelength
    __try
    {
        *pfilelength = 0;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    // see if this is isapi stdin 
    __try
    {
        lpECB = (EXTENSION_CONTROL_BLOCK*)pBHarrayhead->pisapiecb;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    if ((lpECB != (EXTENSION_CONTROL_BLOCK*)-1) && (isapistdinfilehandle == fileid))
    {
        __try
        {
            *pfilelength = lpECB->cbAvailable;
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            return(dg_badmemoryerror);
        }
        
        return (dg_success);        
    }

    // isapi stdout
    if ((lpECB != (EXTENSION_CONTROL_BLOCK*)-1) && (isapistdoutfilehandle == fileid))
    {
        // length already 0
        return (dg_success);
    }

    // isapi stderr
    if ((lpECB != (EXTENSION_CONTROL_BLOCK*)-1) && (isapistderrfilehandle == fileid))
    {
        // length already 0
        return (dg_success);
    }

    flag = dg_getfiletype(
        pBHarrayhead,
        fileid, 
        &filetype, 
        dg_success);

    if (flag != dg_success)
    {
        return (flag);
    }

    if (filetype == dg_filetypedisk)
    {
        // windows doesn't have a way to return the current file pointer position.
        // application has to keep track of it, so returning the length of the file
        // filelengthlo = ::GetFileSize((HANDLE)fileid, &filelengthhi);

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // filelengthlo = dg_callprocaddressalign16(
        //    (UINT32*)&GetFileSize, 
        //    2, 
        //    fileid, 
        //    &filelengthhi);

        // if (filelengthhi != 0)
        // {
        //    return(dg_filetoobigerror);
        //}

        // if (filelengthlo == INVALID_FILE_SIZE)  // what happens if a large file is exactly the size of INVALID_FILE_SIZE?
        // {
        //    return(dg_oserror);
        // }
        
        // *pfilelength = filelengthlo;

        // PLARGE_INTEGER is a signed 64 bit integer
        retflag = GetFileInformationByHandleEx(
            (HANDLE)fileid,
            FileStandardInfo, 
            (LPVOID)&mystandardinfo,
            sizeof(_FILE_STANDARD_INFO));

        if (0 != retflag)
        {
            *((PLARGE_INTEGER)pfilelength) = mystandardinfo.EndOfFile;
            return(dg_success);
        }

        lasterror = ::GetLastError();
        
        // I guessed on what the errors might be
        switch (lasterror)
        {
        case ERROR_ACCESS_DENIED:
            result = dg_accessdeniederror;
            break;
        case ERROR_ARENA_TRASHED:
            result = dg_filesystemcorrupterror;
            break;
        case ERROR_NOT_ENOUGH_MEMORY:
            result = dg_outofmemoryerror;
            break;
        case ERROR_INVALID_BLOCK:
            result = dg_filesystemcorrupterror;
            break;
        case ERROR_OUTOFMEMORY:
            result = dg_outofmemoryerror;
            break;
        case ERROR_INVALID_DRIVE:
            result = dg_drivenotfounderror;
            break;
        case ERROR_BAD_UNIT:
            result = dg_devicenotfounderror;
            break;
        case ERROR_NOT_READY:
            result = dg_devicenotreadyerror;
            break;
        case ERROR_NOT_DOS_DISK:
            result = dg_filesystemunknownerror;
            break;
        case ERROR_GEN_FAILURE:
            result = dg_devicebrokenerror;
            break;
        case ERROR_SHARING_VIOLATION:
            result = dg_fileinuseerror;
            break;
        case ERROR_LOCK_VIOLATION:
            result = dg_fileislockederror;
            break;
        case ERROR_SHARING_BUFFER_EXCEEDED:
            result = dg_toomanyopenfileserror;
            break;

        default:
            result = dg_oserror;
            break;
        }

        return(dg_oserror);
    }
    else if (filetype == dg_filetypeconsole)
    {
        
        // Clear app message que
        //***align16here***
        while(PeekMessage(&mymsg, NULL, 0, 0, PM_REMOVE) != 0)
        // while(
        //    dg_callprocaddressalign16(
        //        (UINT32*)&PeekMessage, 
        //        5, 
        //        &mymsg, 
        //        NULL, 
        //        0, 
        //        0, 
        //        PM_REMOVE) != 0
        //    )
        {
            //***align16here***
            TranslateMessage(&mymsg);
            // dg_callprocaddressalign16(
            //    (UINT32*)&TranslateMessage, 
            //    1, 
            //    &mymsg);

            //***align16here***
            DispatchMessage(&mymsg);
            // dg_callprocaddressalign16(
            //    (UINT32*)&DispatchMessage, 
            //    1, 
            //    &mymsg);
        }

        // Check console message que
        bflag = PeekConsoleInput((HANDLE)fileid, &myinputrecord, 1, &mynumread);

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
        // bflag = dg_callprocaddressalign16(
        //    (UINT32*)&PeekConsoleInput, 
        //    4, 
        //    fileid, 
        //    &myinputrecord, 
        //    1, 
        //    &mynumread);

        if (bflag == 0)
        {
            // error
            return (dg_oserror);
        }

        while (mynumread != 0)
        {
            // if its a key message, extract key and exit loop
            if (myinputrecord.EventType == KEY_EVENT)
            {
                if (myinputrecord.Event.KeyEvent.bKeyDown != 0)
                {
                    // yay found a key!
                    // mynumread = 1
                    break;
                }
            }
            else
            {
                // throw away message from the console message que
                // non key events can safely be discarded because
                //  the two Windows internal events can safely be ignored
                //  and the two user events, windows resizing and mouse move are not used by this application
                //  note: windows resizing not enabled by default. I would like to turn off mouse move
                ReadConsoleInput((HANDLE)fileid, &myinputrecord, 1, &mynumread);

                // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
                //   realigns the stack for 64bit code.
                // bflag = dg_callprocaddressalign16(
                //    (UINT32*)&ReadConsoleInput, 
                //    4, 
                //    fileid, 
                //    &myinputrecord, 
                //    1, 
                //    &mynumread);

            }

            // Check console message que
            bflag = PeekConsoleInput((HANDLE)fileid, &myinputrecord, 1, &mynumread);

            // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
            //   realigns the stack for 64bit code.
            // bflag = dg_callprocaddressalign16(
            //    (UINT32*)&PeekConsoleInput, 
            //    4, fileid, 
            //    &myinputrecord, 
            //    1, 
            //    &mynumread);


            if (bflag == 0)
            {
                // error
                return (dg_oserror);
            }
        }
        

        // *pfilelength = mynumread; // temporarily removed 9/11/2020
        * pfilelength = 0;
    }
    else if (filetype == dg_filetypepipe)
    {
        bflag = PeekNamedPipe((HANDLE)fileid, NULL, 0, NULL, &mynumread, NULL);

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
        //   realigns the stack for 64bit code.
        // bflag = dg_callprocaddressalign16(
        //    (UINT32*)&PeekNamedPipe, 
        //    6, 
        //    fileid, 
        //    NULL, 
        //    0, 
        //    NULL, 
        //    &mynumread, 
        //    NULL);



        if (bflag == 0)
        {
            // error
            return (dg_oserror);
        }

        *pfilelength = mynumread;
    }

    return (dg_success);
}


const char* dg_freelibraryname = "dg_freelibrary";

const char* dg_freelibrary(
     UINT64 hlibrary,
     const char* forceerrorflag)
{
    INT32 errflag = 0;

    __try
    {
        errflag = ::FreeLibrary((HINSTANCE)hlibrary);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }
    
    if (errflag == 0)
    {
        return (dg_oserror);
    }

    return (dg_success);
}



const char* dg_loadlibraryname = "dg_loadlibrary";

const char* dg_loadlibrary(
     const char* libraryname,
     UINT64* phlibrary,
     const char* forceerrorflag)
{
    UINT32 lasterror;
    const char* result = dg_success;

    __try
    {
        *phlibrary = badlibraryhandle;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    __try
    {
        *phlibrary = (UINT64)::LoadLibrary(libraryname);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        *phlibrary = badlibraryhandle;
        return(dg_osexception);
    }

    if (*phlibrary == (UINT64)NULL)
    {
        *phlibrary = badlibraryhandle;

        lasterror = ::GetLastError();

        switch (lasterror)
        {
        case ERROR_FILE_NOT_FOUND:
            result = dg_filenotfounderror;
            break;
        case ERROR_PATH_NOT_FOUND:
            result = dg_pathnotfounderror;
            break;
        case ERROR_TOO_MANY_OPEN_FILES:
            result = dg_toomanyopenfileserror;
            break;
        case ERROR_ACCESS_DENIED:
            result = dg_accessdeniederror;
            break;
        case ERROR_ARENA_TRASHED:
            result = dg_filesystemcorrupterror;
            break;
        case ERROR_NOT_ENOUGH_MEMORY:
            result = dg_outofmemoryerror;
            break;
        case ERROR_INVALID_BLOCK:
            result = dg_filesystemcorrupterror;
            break;
        case ERROR_OUTOFMEMORY:
            result = dg_outofmemoryerror;
            break;
        case ERROR_INVALID_DRIVE:
            result = dg_drivenotfounderror;
            break;
        case ERROR_BAD_UNIT:
            result = dg_devicenotfounderror;
            break;
        case ERROR_NOT_READY:
            result = dg_devicenotreadyerror;
            break;
        case ERROR_NOT_DOS_DISK:
            result = dg_filesystemunknownerror;
            break;
        case ERROR_GEN_FAILURE:
            result = dg_devicebrokenerror;
            break;
        case ERROR_SHARING_VIOLATION:
            result = dg_fileinuseerror;
            break;
        case ERROR_LOCK_VIOLATION:
            result = dg_fileislockederror;
            break;
        case ERROR_SHARING_BUFFER_EXCEEDED:
            result = dg_toomanyopenfileserror;
            break;
    
        default:
            result = dg_oserror;
            break;
        }
    }

    return (result);
}



const char* dg_openfileforreadname = "dg_openfileforread";

const char* dg_openfileforread(
              const char* filename, 
              UINT64* pfileid, 
              const char* forceerrorflag)
{
    UINT64 lasterror;
    const char* result = dg_success;

    if (forceerrorflag != dg_success)
    {
        return(forceerrorflag);
    }

    __try
    {
        *pfileid = badfilehandle;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    __try
    {
        *pfileid = (UINT64)CreateFile(
            filename,                  // open filename 
            GENERIC_READ,              // open for reading 
            FILE_SHARE_READ,           // share for reading 
            NULL,                      // no security 
            OPEN_EXISTING,             // existing file only 
            FILE_ATTRIBUTE_NORMAL,     // normal file 
            NULL);                       // no attr. templ

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
        //   realigns the stack for 64bit code.
        // *pfileid = dg_callprocaddressalign16(
        //    (UINT32*)&CreateFile, 
        //    7,
        //    filename,                  // open filename 
        //    GENERIC_READ,              // open for reading 
        //    FILE_SHARE_READ,           // share for reading 
        //    NULL,                      // no security 
        //    OPEN_EXISTING,             // existing file only 
        //    FILE_ATTRIBUTE_NORMAL,     // normal file 
        //    NULL);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }
 
    if (*pfileid == (UINT64)INVALID_HANDLE_VALUE) 
    { 
        *pfileid = badfilehandle;

        lasterror = ::GetLastError();

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
        //   realigns the stack for 64bit code.
        // lasterror = dg_callprocaddressalign16(
        //    (UINT32*)&GetLastError, 
        //    0);

        switch (lasterror)
        {
        case ERROR_FILE_NOT_FOUND:
            result = dg_filenotfounderror;
            break;
        case ERROR_PATH_NOT_FOUND:
            result = dg_pathnotfounderror;
            break;
        case ERROR_TOO_MANY_OPEN_FILES:
            result = dg_toomanyopenfileserror;
            break;
        case ERROR_ACCESS_DENIED:
            result = dg_accessdeniederror;
            break;
        case ERROR_ARENA_TRASHED:
            result = dg_filesystemcorrupterror;
            break;
        case ERROR_NOT_ENOUGH_MEMORY:
            result = dg_outofmemoryerror;
            break;
        case ERROR_INVALID_BLOCK:
            result = dg_filesystemcorrupterror;
            break;
        case ERROR_OUTOFMEMORY:
            result = dg_outofmemoryerror;
            break;
        case ERROR_INVALID_DRIVE:
            result = dg_drivenotfounderror;
            break;
        case ERROR_BAD_UNIT:
            result = dg_devicenotfounderror;
            break;
        case ERROR_NOT_READY:
            result = dg_devicenotreadyerror;
            break;
        case ERROR_NOT_DOS_DISK:
            result = dg_filesystemunknownerror;
            break;
        case ERROR_GEN_FAILURE:
            result = dg_devicebrokenerror;
            break;
        case ERROR_SHARING_VIOLATION:
            result = dg_fileinuseerror;
            break;
        case ERROR_LOCK_VIOLATION:
            result = dg_fileislockederror;
            break;
        case ERROR_SHARING_BUFFER_EXCEEDED:
            result = dg_toomanyopenfileserror;
            break;
    
        default:
            result = dg_oserror;
            break;
        }
    }

    // need to check to see if windows allocated a fileid this script engine uses for
    //  isapi stdin, stdout, and stderr while in isapi mode

    return(result);
}



const char* dg_openfileforwritenewname = "dg_openfileforwritenew";

const char* dg_openfileforwritenew(
    const char* filename, 
    UINT64* pfileid, 
    const char* forceerrorflag)
{
    UINT64 lasterror;
    const char* result = dg_success;


    if (forceerrorflag != dg_success)
    {
        return(forceerrorflag);
    }

    __try
    {
        *pfileid = badfilehandle;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }


    __try
    {
        *pfileid = (UINT64)CreateFile(
            filename,                     // create MYFILE.TXT 
            GENERIC_WRITE,                // open for writing 
            0,                            // do not share 
            NULL,                         // no security 
            CREATE_ALWAYS,                // overwrite existing 
            FILE_ATTRIBUTE_NORMAL         // normal file 
             ,         // asynchronous I/O  // ( | FILE_FLAG_OVERLAPPED )
            NULL); // no attr. template

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
        //   realigns the stack for 64bit code.
        // *pfileid = dg_callprocaddressalign16((UINT32*)&CreateFile, 7,
        //    filename,                     // create MYFILE.TXT 
        //    GENERIC_WRITE,                // open for writing 
        //    0,                            // do not share 
        //    NULL,                         // no security 
        //    CREATE_ALWAYS,                // overwrite existing 
        //    FILE_ATTRIBUTE_NORMAL         // normal file 
        //     ,         // asynchronous I/O  //  | FILE_FLAG_OVERLAPPED 
        //    NULL);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_osexception);
    }
 
    if (*pfileid == (UINT64)INVALID_HANDLE_VALUE) 
    { 
        *pfileid = badfilehandle;
        
        lasterror = ::GetLastError();

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
        //   realigns the stack for 64bit code.
        // lasterror = dg_callprocaddressalign16((UINT32*)&GetLastError, 0);

        switch (lasterror)
        {
        case ERROR_PATH_NOT_FOUND:
            result = dg_pathnotfounderror;
            break;
        case ERROR_TOO_MANY_OPEN_FILES:
            result = dg_toomanyopenfileserror;
            break;
        case ERROR_ACCESS_DENIED:
            result = dg_accessdeniederror;
            break;
        case ERROR_ARENA_TRASHED:
            result = dg_filesystemcorrupterror;
            break;
        case ERROR_NOT_ENOUGH_MEMORY:
            result = dg_outofmemoryerror;
            break;
        case ERROR_INVALID_BLOCK:
            result = dg_filesystemcorrupterror;
            break;
        case ERROR_OUTOFMEMORY:
            result = dg_outofmemoryerror;
            break;
        case ERROR_INVALID_DRIVE:
            result = dg_drivenotfounderror;
            break;
        case ERROR_BAD_UNIT:
            result = dg_devicenotfounderror;
            break;
        case ERROR_NOT_READY:
            result = dg_devicenotreadyerror;
            break;
        case ERROR_NOT_DOS_DISK:
            result = dg_filesystemunknownerror;
            break;
        case ERROR_GEN_FAILURE:
            result = dg_devicebrokenerror;
            break;
        case ERROR_SHARING_VIOLATION:
            result = dg_fileinuseerror;
            break;
        case ERROR_LOCK_VIOLATION:
            result = dg_fileislockederror;
            break;
        case ERROR_SHARING_BUFFER_EXCEEDED:
            result = dg_toomanyopenfileserror;
            break;
        case ERROR_WRITE_PROTECT:
            result = dg_writeprotectederror;
            break;
        case ERROR_HANDLE_DISK_FULL:
            result = dg_diskisfullerror;
            break;
    
        default:
            result = dg_oserror;
            break;
        }
    }

    // need to check to see if windows allocated a fileid this script engine uses for
    //  isapi stdin, stdout, and stderr while in isapi mode

    return(result);
}

void dg_printzerostring(
    Bufferhandle* pBHarrayhead,
    UINT8* addr)
{
    UINT64 i = largestsignedint;
    const char* flag;
    UINT64 fileid;

    if (addr == (unsigned char*)badbufferhandle)
    {
        // this is used to print out errors... so not gonna push more errors
        // and do not have pointer to pBHarrayhead
        return;
    }

    flag = dg_gethstdout(
        pBHarrayhead,
        &fileid,
        dg_success);

    if (flag != dg_success)
    {
        return;
    }
    
    // get length of zero string
    flag = dg_scanforbyte(
        addr,
        &i,
        0);

    if (flag != dg_success)
    {
        return;
    }

    // assumes you will hit bad memory before using up largestsignedint characters
    
    dg_writefile(
        pBHarrayhead,
        fileid,
        addr,
        i,
        dg_success);
}

const char* dg_writestdoutname = "dg_writestdout";

const char* dg_writestdout(
    Bufferhandle* pBHarrayhead,
    UINT8* pbuf,
    UINT64 length)
{
    UINT64 fileid;
    const char* pError;

    pError = dg_gethstdout(
        pBHarrayhead,
        &fileid,
        dg_success);

    if (pError != dg_success)
    {
        return (pError);
    }

    pError = dg_writefile(
        pBHarrayhead,
        fileid,
        pbuf,
        length,
        dg_success);

    return (pError);
}


void dg_writefileuint64todec(
    Bufferhandle* pBHarrayhead,
    UINT32 fileid,
    UINT32 i)
{
    unsigned char buf[64];
    UINT64 r;
    UINT64 n = 0;

    if (0 == i)
    {
        dg_writefile(
            pBHarrayhead,
            fileid,
            (unsigned char*)"0",
            1,
            dg_success);

        return;
    }

    while (i > 0)
    {
        r = i % 10;
        i = i / 10;
        buf[19 - n] = (unsigned char)(r + 0x30);
        n++;
    }

    // need blocking writestdout, or writestdout does copy
    dg_writefile(
        pBHarrayhead,
        fileid,
        &(buf[20 - n]),
        n,
        dg_success);
}

void dg_writestdoutuinttodec(
    Bufferhandle* pBHarrayhead,
    UINT64 i)
{
    unsigned char buf[64];
    UINT64 r;
    UINT64 n = 0;

    if (0 == i)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"0");
        return;
    }

    while (i > 0)
    {
        r = i % 10;
        i = i / 10;
        buf[19 - n] = (unsigned char)(r + 0x30);
        n++;
    }

    // need blocking writestdout, or writestdout does copy
    dg_writestdout(pBHarrayhead, &(buf[20 - n]), n);
}


void dg_writestdoutuint64tohex(
    Bufferhandle* pBHarrayhead,
    UINT64 i)
{
    unsigned char buf[64];
    UINT64 r;
    UINT64 n = 0;

    if (0 == i)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"0x00000000");
        return;
    }

    while (i > 0)
    {
        r = i % 0x10;
        i = i / 0x10;
        buf[19 - n] = dg_digittochar(r);
        n++;
    }

    dg_writestdout(pBHarrayhead, (unsigned char*)"0x", 2);

    while (n < 16) // may want to add a leading zero any time n is odd
    {
        buf[19 - n] = '0';
        n++;
    }

    // need blocking writestdout, or writestdout does copy
    dg_writestdout(pBHarrayhead, &(buf[20 - n]), n);
}

void dg_writestdoutuint8tohex(
    Bufferhandle* pBHarrayhead,
    UINT8 i)
{
    UINT8 buf[4];

    buf[0] = '0';
    buf[1] = 'x';

    if (0 == i)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"0x00");
        return;
    }

    buf[3] = dg_digittochar(i & 0x0F);
    buf[2] = dg_digittochar(i / 0x10);

    // need blocking writestdout, or writestdout does copy
    dg_writestdout(pBHarrayhead, &buf[0], 4);
}


const char* dg_newmutexname = "dg_newmutex";

const char* dg_newmutex(
    struct DG_Mutex_Holder *pmutexholder,
    const char* forceerrorflag)
{
    UINT64 lasterror;
    const char* perror;

    perror = dg_fillwithbyte(
        (unsigned char*)pmutexholder,
        sizeof(DG_Mutex_Holder),
        0);

    if (perror != dg_success)
    {
        return (perror);
    }

    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }

    pmutexholder->magic = DG_MUTEX_HOLDER_MAGIC;

    // pmutexholder->ismutexlockedflag = FORTH_FALSE; // fillwithbyte already did this

    pmutexholder->mutexhandle = (UINT64)CreateMutexA(
        NULL,
        FALSE,
        NULL);

    if (NULL != pmutexholder->mutexhandle)
    {
        return(dg_success);
    }

    lasterror = GetLastError();

    if ((lasterror == ERROR_OUTOFMEMORY) || (lasterror == ERROR_NOT_ENOUGH_MEMORY))
    {
        return(dg_outofmemoryerror);
    }

    // unknown error
    return (dg_oserror);
}

const char* dg_freemutexname = "dg_freemutex";

const char* dg_freemutex(
    struct DG_Mutex_Holder* pmutexholder,
    const char* forceerrorflag)
{
    UINT64 lasterror;
    const char* perror;

    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }

    // I want to return an error if the mutex is already locked...
    //  this is for portability, and to force programmers to be careful
    if (pmutexholder->ismutexlockedflag != FORTH_FALSE)
    {
        return(dg_freemutexwhilelockederror);
    }

    if (pmutexholder->mutexhandle == (UINT64)-1)
    {
        return(dg_invalidhandleerror);
    }

    lasterror = CloseHandle((HANDLE)(pmutexholder->mutexhandle));

    if (lasterror != 0)
    {
        pmutexholder->mutexhandle = (UINT64)-1;
        return(dg_success);
    }

    lasterror = GetLastError();

    if (ERROR_INVALID_HANDLE == lasterror)
    {
        return(dg_invalidhandleerror);
    }

    // unknown error
    return (dg_oserror);
}


const char* dg_lockmutexname = "dg_lockmutex";

const char* dg_lockmutex(
    struct DG_Mutex_Holder* pmutexholder,
    const char* forceerrorflag)
{
    UINT64 lasterror;
    const char* perror;

    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }

    if (pmutexholder->ismutexlockedflag != FORTH_FALSE)
    {
        return(dg_woulddeadlockerror);
    }

    lasterror = WaitForSingleObject(
        (HANDLE)(pmutexholder->mutexhandle),
        INFINITE);

    if (WAIT_OBJECT_0 == lasterror)
    {
        pmutexholder->ismutexlockedflag = FORTH_TRUE;
        return(dg_success);
    }

    if (WAIT_ABANDONED == lasterror)
    {
        return(dg_waitabandonederror);
    }

    // unknown error
    return (dg_oserror);
}


const char* dg_unlockmutexname = "dg_unlockmutex";

const char* dg_unlockmutex(
    struct DG_Mutex_Holder* pmutexholder,
    const char* forceerrorflag)
{
    UINT64 lasterror;
    const char* perror;

    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }

    if (pmutexholder->ismutexlockedflag == FORTH_FALSE)
    {
        return(dg_mutexisnotlockederror);
    }

    // probably a good idea to change the flag while it is still protected by the mutex
    pmutexholder->ismutexlockedflag = FORTH_FALSE; 

    lasterror = ReleaseMutex((HANDLE)(pmutexholder->mutexhandle));

    if (0 != lasterror)
    {
        return (dg_success);
    }

    lasterror = GetLastError();

    if (lasterror == ERROR_INVALID_HANDLE)
    {
        return(dg_invalidhandleerror);
    }

    // unknown error
    return (dg_oserror);
}


void dg_hexdumpsegment(
    Bufferhandle* pBHarrayhead,
    UINT8* pstring,
    UINT64 length)
{
    UINT64 i = 0;
    UINT8 c = ' ';
    const char* pError;

    if (0 == length)
    {
        return;
    }

    // slooow way to do it
    for (i = 0; i < length; i++)
    {
        //c = pstring[i];
        pError = dg_getbyte(
            pstring + i,
            &c);

        if (pError != dg_success)
        {
            // trying to look at memory process does not own
            // c = 0xff;
            dg_writestdout(
                pBHarrayhead,
                (unsigned char*)"!! ",
                3);
        }
        else
        {
            dg_writestdoutuint8tohex(
                pBHarrayhead,
                c);

            // could skip showing last trailing space
            dg_writestdout(
                pBHarrayhead,
                (unsigned char*)" ",
                1);
        }
    }
}

UINT64 dg_isnegative(UINT64 x)  // could call this dg_zeroless
{
    if (x < 0x8000000000000000)
    {
        return (FORTH_FALSE);
    }
    else
    {
        return (FORTH_TRUE);
    }
}


// If the source and the destination segments overlap, this blockmove will not copy any bytes from within
//  the destination segment. Instead it will split the source into two segments if necessary and continue 
//  the copy from the first byte after the destination.

// This routine is used to handle the case where a copy and insert is done from a string into the middle
//  of the same string.

const char* dg_movebytesskipdestinationname = "dg_movebytesskipdestination";

const char* dg_movebytesskipdestination(
    unsigned char* psrc,
    unsigned char* pdest,
    UINT64 stringlength)
{
    UINT64 length1;
    UINT64 length2;

    const char* pError;

    // check for calculation overflow
    //  assuming buffers can not wrap around past 0x00000000
    if (((UINT64)psrc) > ((UINT64)(0 - (INT64)stringlength)))
    {
        return (dg_segmentgoespastenderror);
    }

    // check for calculation overflow
    //  assuming buffers can not wrap around past 0x00000000
    if (((UINT64)pdest) > ((UINT64)(0 - (INT64)stringlength)))
    {
        return (dg_segmentgoespastenderror);
    }

    // case 1, source segment is before destination - no overlap
    if (((UINT64)psrc + stringlength) <= ((UINT64)pdest))
    {
        pError = dg_movebytes(psrc, pdest, stringlength);
        return (pError);
    }

    // case 2, source is after destination segment - no overlap
    if (((UINT64)psrc) >= ((UINT64)pdest + stringlength))
    {
        pError = dg_movebytes(psrc, pdest, stringlength);
        return (pError);
    }

    // case 3, psrc starts somewhere in pdest - copy from after destination
    if (((UINT64)psrc) >= ((UINT64)pdest))
    {
        pError = dg_movebytes(pdest + stringlength, pdest, stringlength);
        return (pError);
    }

    // case 4 pscr starts before pdest - split source around pdest
    length1 = (UINT64)pdest - (UINT64)psrc;
    length2 = stringlength - length1;

    pError = dg_movebytes(psrc, pdest, length1);

    if (pError != dg_success)
    {
        return (pError);
    }

    pError = dg_movebytes(pdest + stringlength, pdest + length1, length2);

    return (pError);
}

// push query string to script file name buffer
        // first parameter is supposed to be script file name so...
        //   throw out everything after ; or &
        // if first parameter is in parameter=value form we only
        //   need the value, so throw out everything before an =
// this only works for isapi mode on iis7
// for cgi mode on iis7 can't use args buffer, have to go directly to PATH_TRANSLATED


const char* dg_getsvaluename = "dg_getsvalue";

const char* dg_getsvalue(
    unsigned char* pbuf,
    UINT64 buflength,
    UINT64* pfirstvaluestartoffset,
    UINT64* pfirstvaluelength)
{
    UINT64 n;
    UINT64 startoffset = 0;
    UINT64 endoffset = buflength;

    const char* perror;


    perror = dg_putuint64(pfirstvaluestartoffset, 0);

    if (perror != dg_success)
    {
        return (perror);
    }

    perror = dg_putuint64(pfirstvaluelength, 0);

    if (perror != dg_success)
    {
        return (perror);
    }

    // drop everything after first &
    n = endoffset;

    perror = dg_scanforbyte((void*)pbuf, &n, (UINT64)'&');

    if (perror != dg_success)
    {
        return (perror);
    }

    if (n < endoffset)
    {
        // & found
        endoffset = n;
    }

    // drop everything after first ;
    n = endoffset;

    perror = dg_scanforbyte((void*)pbuf, &n, (UINT64)';');

    if (perror != dg_success)
    {
        return (perror);
    }

    if (n < endoffset)
    {
        // ; found
        endoffset = n;
    }

    // drop everything before first =
    n = endoffset;

    perror = dg_scanforbyte((void*)pbuf, &n, (UINT64)'=');

    if (perror != dg_success)
    {
        return (perror);
    }

    if (n < endoffset)
    {
        // = found
        startoffset = n + 1;
    }

    if (startoffset <= endoffset)
    {
        // don't see how it couldn't be
        *pfirstvaluelength = (endoffset - startoffset);
        *pfirstvaluestartoffset = startoffset;
    }

    return (dg_success);
}

// for Linux, FreeBSD
//   apparently Mac OS X doesn't do this...
//   neither does Win32
// pointers to environment variables passed to diaperglu are in argv array starting at 
//  index argc+1 and go until argv[x]=0;
// environment variable strings are null terminated and are of form name=value
//  the =value part is not necessarily there

const char* dg_getsenvnamevalue(
    INT64 argc,
    char* argv[],
    const char* pnametofind,
    UINT64 nametofindlength,
    char** ppfoundname,
    UINT64* pfoundnamelength,
    char** ppfoundvalue,
    UINT64* pfoundvaluelength)
{
    const char* pError;

    // gonna assume output parameters are good
    *ppfoundname = NULL;
    *pfoundnamelength = 0;
    *ppfoundvalue = NULL;
    *pfoundvaluelength = 0;

    UINT64 i = argc + 1;
    UINT64 lengthto0;
    UINT64 lengthtoequals;

    INT64 compareflag;

    while (FORTH_TRUE)
    {
        pError = dg_getuint64((UINT64*)&argv[i], (UINT64*)ppfoundname);

        if (pError != dg_success)
        {
            *ppfoundname = NULL;
            *pfoundnamelength = 0;
            *ppfoundvalue = NULL;
            *pfoundvaluelength = 0;

            return (dg_getuint64name);
        }

        // got to end of list without finding a match case 
        if (NULL == *ppfoundname)
        {
            //*ppfoundname = NULL;
            *pfoundnamelength = 0;
            *ppfoundvalue = NULL;
            *pfoundvaluelength = 0;

            return (dg_success);
        }

        // lengthto0 = scan for 0 for largest signed int, do not count 0
        lengthto0 = largestsignedint;

        pError = dg_scanforbyte(*ppfoundname, &lengthto0, 0);

        // bad memory encountered which means 0 not found so error out
        if (pError != dg_success)
        {
            *ppfoundname = NULL;
            *pfoundnamelength = 0;
            *ppfoundvalue = NULL;
            *pfoundvaluelength = 0;

            return (dg_scanforbytename);
        }

        // this case can't really happen...
        if ((UINT64)-1 == lengthto0)
        {
            *pfoundnamelength = 0;
            *ppfoundvalue = NULL;
            *pfoundvaluelength = 0;

            return (pError);
        }

        // lengthto= = scan for = up to 0, do not count =
        lengthtoequals = lengthto0;

        pError = dg_scanforbyte(*ppfoundname, &lengthtoequals, '=');

        // bad memory encountered
        if (pError != dg_success)
        {
            *ppfoundname = NULL;
            *pfoundnamelength = 0;
            *ppfoundvalue = NULL;
            *pfoundvaluelength = 0;

            return (dg_scanforbytename);
        }

        // = not found so there is no value
        if (lengthtoequals >= lengthto0) // should be -1 if not found
        {
            *pfoundnamelength = lengthto0;
            *ppfoundvalue = *ppfoundname + lengthto0;  // points to the 0 at end of name
            *pfoundvaluelength = 0;
        }
        else
        {
            *pfoundnamelength = lengthtoequals;
            *ppfoundvalue = (*ppfoundname) + lengthtoequals + 1;
            *pfoundvaluelength = lengthto0 - (lengthtoequals + 1);
        }

        // compare  pnametofind with pfoundname
        pError = dg_comparebytes(
            (unsigned char*)pnametofind,
            nametofindlength,
            (unsigned char*)*ppfoundname,
            *pfoundnamelength,
            &compareflag);

        // this shouldn't happen unless nametofind is corrupt,
        // foundname already checked
        if (pError != dg_success)
        {
            *ppfoundname = NULL;
            *pfoundnamelength = 0;
            *ppfoundvalue = NULL;
            *pfoundvaluelength = 0;

            return (dg_comparebytesname);
        }

        // if they match, return what you have
        if (0 == compareflag)
        {
            return (dg_success);
        }

        // if they don't match, i = i+1 and try again
        i++;
    }

    // will never get here
}

UINT64 dg_getuleb128size(UINT64 u)
{
    if (0 == u)
    {
        return (1);
    }

    return((dg_hibit(u) / 7) + 1);
}

UINT64 dg_getlengthwithuleb128length(UINT64 currentlength)
{
    UINT64 newlength, probableuleb128length, trueuleb128length;

    // get number of bits in current length
    // divide by 7, truncate, and add 1
    probableuleb128length = dg_getuleb128size(currentlength);

    // add this value to current length
    newlength = probableuleb128length + currentlength; // 0-7 = 1; 8-14 = 2; 9-21 = 3;

    // get number of bits in new length
    // divide by 7, truncate, and add 1
    trueuleb128length = dg_getuleb128size(newlength);

    // if new value = old value, return current length plus value
    if (trueuleb128length == probableuleb128length)
    {
        return (newlength);
    }

    // otherwise return current length plus value plus 1
    return (newlength + 1);
}

/*
const char dg_pushhctwotobuffername[] = "dg_pushhctwotobuffer";

void dg_pushhctwotobuffer(
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT128 ud)
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

    hclength = dg_gethctwolength(ud);

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

    perror = dg_hctwostore(pbuffer + oldbufferlength, ud);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_hctwostorename);
        dg_pusherror(pBHarrayhead, dg_pushhctwotobuffername);
        return;
    }
}
*/

////////////////////////////////////////////////////////////////////////
//
// mygetplibraryexporttables
//
// Inputs:
//  Bufferhandle* pBHarrayhead          pointer to a Bufferhandle structure which is 
//                                       used as the bufferhandle for the array where the other 
//                                       bufferhandles are stored.  
//  HINSTANCE hlibrary                  handle of the dll. in Windows, this is a pointer to the memory
//                                       where the dll was loaded
//  
// Outputs:
//  UINT32* pnumberoffunctions    the number of functions in the function offset array
//  UINT32* pnumberofnames        the number of function names and ordinals in 
//                                       the name offset and ordinal arrays
//  void** ppfunctionoffsetarray        the address of the function offset array
//  void** ppnameoffsetarray            the address of the name offset array
//  void** ppordinalarray               the address of the ordinal array
//
// Action:
//  Gets the number of functions, number of function names, a pointer to the function offset array,
//   a pointer to the name offset array, and ordinal array from a dll (library) that is loaded into memory.
// 
// Failure cases:
//  null library handle passed in
//  error accessing memory, dlldg_forth doesn't have access to all the memory hlibrary points to
//  dll's e_magic field incorrect. it's not a dos/windows file
//  pe format signature field incorrect, it's not a pe format file
//  optional header's size too small, file does not have an export table
//  dll says export directory goes outside the dll's memory space
//  dll says function offset array goes outside the dll's memory space
//  dll says name offset array goes outside the dll's memory space
//  dll says ordinal array goes outside the dll's memory space
//  
////////////////////////////////////////////////////////////////////////
/*
const char* dg_getplibraryexporttables( 
                                HINSTANCE hlibrary,
                                UINT64* pimagesize,
                                UINT64* pnumberoffunctions,
                                UINT64* pnumberofnames,
                                void** ppfunctionoffsetarray,
                                void** ppnameoffsetarray,
                                void** ppordinalarray)
{
    WORD x = 0;
    UINT64 y = 0;
    IMAGE_NT_HEADERS* pntheader = NULL;
    UINT64 imagesize = 0;
    UINT64 optionalheadersize = 0;
    UINT64 exporttablesize = 0;
    IMAGE_EXPORT_DIRECTORY* pimageexportdirectory = NULL;
    UINT64 functionoffsetarrayoffset = 0;
    UINT64 nameoffsetarrayoffset = 0;
    UINT64 ordinalarrayoffset = 0;
    const char* result = dg_success;

    __try
    {
        *pimagesize = 0;
        *pnumberoffunctions = 0;
        *pnumberofnames = 0;
        *ppfunctionoffsetarray = NULL;
        *ppnameoffsetarray = NULL;
        *ppordinalarray = NULL;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    __try
    {
        x = ((IMAGE_DOS_HEADER*)(hlibrary))->e_magic;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    if (x != IMAGE_DOS_SIGNATURE)
    {
        return (dg_badmagicerror);
    }

    __try
    {
        y = ((IMAGE_DOS_HEADER*)(hlibrary))->e_lfanew;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    pntheader = (IMAGE_NT_HEADERS*)(((UINT64)(hlibrary)) + y);

    __try
    {
        y = pntheader->Signature;
        optionalheadersize = pntheader->FileHeader.SizeOfOptionalHeader;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    if (y != IMAGE_NT_SIGNATURE)
    {
        return (dg_badmagicerror);
    }

    if (optionalheadersize < 200)
    {
        return (dg_missingexporttableerror);
    }

    __try
    {
        imagesize = pntheader->OptionalHeader.SizeOfImage;
        y = pntheader->OptionalHeader.DataDirectory[0].VirtualAddress;
        exporttablesize = pntheader->OptionalHeader.DataDirectory[0].Size;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    *pimagesize = imagesize;

    // could check lower bound too, needs to be after end of optional header
    if ((y >= imagesize) || ((y + exporttablesize) >= imagesize))
    {
        return (dg_exporttablebounderror);
    }

    pimageexportdirectory = (IMAGE_EXPORT_DIRECTORY*)(((UINT64)(hlibrary)) + y);

    __try
    {
        *pnumberoffunctions = pimageexportdirectory->NumberOfFunctions;
        *pnumberofnames = pimageexportdirectory->NumberOfNames;
        functionoffsetarrayoffset = pimageexportdirectory->AddressOfFunctions;
        nameoffsetarrayoffset = pimageexportdirectory->AddressOfNames;
        ordinalarrayoffset = pimageexportdirectory->AddressOfNameOrdinals;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    // know we have access to output variables from above
    *ppfunctionoffsetarray = (void*)(functionoffsetarrayoffset + ((UINT64)(hlibrary)));
    *ppnameoffsetarray = (void*)(nameoffsetarrayoffset + ((UINT64)(hlibrary)));
    *ppordinalarray = (void*)(ordinalarrayoffset + ((UINT64)(hlibrary)));

    // could check lower bound too, needs to be after end of optional header
    if ((functionoffsetarrayoffset >= imagesize) || 
        ((functionoffsetarrayoffset + (*pnumberoffunctions * sizeof(DWORD))) >= imagesize))
    {
        return (dg_exporttablebounderror);
    }

    // could check lower bound too, needs to be after end of optional header
    if ((nameoffsetarrayoffset >= imagesize) || 
        ((nameoffsetarrayoffset + (*pnumberofnames * sizeof(DWORD))) >= imagesize))
    {
        return (dg_exporttablebounderror);
    }

    // could check lower bound too, needs to be after end of optional header
    if ((ordinalarrayoffset >= imagesize) || 
        ((ordinalarrayoffset + (*pnumberofnames * sizeof(DWORD))) >= imagesize))
    {
        return (dg_exporttablebounderror);
    }

    return (dg_success);
}
*/

/*
// need function to get number of symbols in library
const char dg_getnumberoflibrarysymbolsname[] = "dg_getnumberoflibrarysymbols";

const char* dg_getnumberoflibrarysymbols (
                HINSTANCE hlibrary, 
                UINT64* pnumberofsymbols,
                const char* forceerrorflag)
{
    UINT64 imagesize = 0;
    UINT64 numberofnames = 0;
    UINT64 numberoffunctions = 0;
    void* pfunctionoffsetarray = NULL;
    void* pnameoffsetarray = NULL;
    void* pordinalarray = NULL;

    const char* flag = dg_success;

    __try
    {
        *pnumberofsymbols = 0;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    flag = dg_getplibraryexporttables(
        hlibrary,
        &imagesize,
        &numberoffunctions,
        &numberofnames,
        &pfunctionoffsetarray,
        &pnameoffsetarray,
        &pordinalarray);

    if (flag != dg_success)
    {
        return (flag);
    }

    *pnumberofsymbols = numberofnames;

    return (dg_success);
}
*/

/*
// need function to given symbol number (not ordinal) get pname, namelength, type, and value
const char dg_symboltypefunction[] = "function";
const char dg_symboltypeconstant[] = "constant";
const char dg_symboltypeunknown[] = "unknown";

const char dg_getlibrarysymbolname[] = "dg_getlibrarysymbol";

const char* dg_getlibrarysymbol(
                HINSTANCE hlibrary,
                UINT64 symbolnumber,     // not ordinal
                const char** psymbolname,
                UINT64* pnamelength,
                const char** psymboltype,
                UINT64* psymbolvalue,
                const char* forceerrorflag)
{
    
    const char* flag = dg_success;
    UINT64 numberofsymbols = 0;
    UINT64 i = 0;

    UINT64 imagesize = 0;
    UINT64 numberofnames = 0;
    UINT64 numberoffunctions = 0;
    void* pfunctionoffsetarray = NULL;
    void* pnameoffsetarray = NULL;
    void* pordinalarray = NULL;

    __try
    {
        *psymboltype = dg_symboltypeunknown;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    __try
    {
        *psymbolname = NULL; // should use -1
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    __try
    {
        *pnamelength = 0;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    __try
    {
        *psymbolvalue = 0;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    // check output variables for invalid pointer memory
    flag = dg_getplibraryexporttables(
        hlibrary,
        &imagesize,
        &numberoffunctions,
        &numberofnames,
        &pfunctionoffsetarray,
        &pnameoffsetarray,
        &pordinalarray);

    if (flag != dg_success)
    {
        return (flag);
    }

    if (symbolnumber >= numberofnames)
    {
        // symbolnumber too high error
        return (flag);
    }

    
    *psymbolname = (LPCSTR)(((UINT32*)(pnameoffsetarray))[symbolnumber] + ((UINT64)(hlibrary)));

    __try
    {
        // align16 here?
        *psymbolvalue = (UINT64)::GetProcAddress(hlibrary, *psymbolname);
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_oserror);
    }

    
    *psymboltype = dg_symboltypefunction;
    

    __try
    {
        i = 0;
        
        while (true)
        {
            if ( i >= ((((UINT64)(hlibrary)) - ((UINT64)(*psymbolname))) + imagesize) )
            {
                break;
            }

            if ((*psymbolname)[i] == 0x00)
            {
                break;
            }

            i++;
        }
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (dg_badmemoryerror);
    }

    *pnamelength = i;
    

    return (dg_success);
}
*/

/*
// Microsoft Visual C++ call convention
const char* dg_determinecalltypefromname (
    const char* pname, 
    UINT32 namelength, 
    UINT32* pcalltype)
{
    unsigned char c = ' ';
    const char* flag = dg_success;
    UINT32 namelength2 = namelength;

    // if no @, it is cdecl
    // if no ? at start, it is cdecl
    // if ?name@@stuff, it is cdecl
    // if ?name@classname@@stuff, it is cpp class member
    // if ??1classname@@stuff, it is a cpp class destructor
    // if ??0classname@@stuff, it is a cpp class constructor
    // if ??4classname@@stuff, not sure what it is but it's cpp
    // if _DllMain@12, it is stdcall
    // if _name@n, it is stdcall

    __try
    {
        *pcalltype = (UINT32)&dg_forthdocompiletypecdecl;        
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    if (namelength < 2)
    {
        return(dg_success);
    }

    __try
    {
        c = pname[0];        
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    if ('_' == c)
    {
        //*pcalltype = (UINT32)&dg_forthdocompiletypestdcall;
        *pcalltype = (UINT32)&dg_forthdocompiletypecdecl;
        return(dg_success);
    }

    if ('?' != c)
    {
        // *pcalltype already set to cdecl
        return(dg_success);
    }

    __try
    {
        c = pname[1];        
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    // ?? at start means it is cpp member function
    if ('?' == c)
    {
        *pcalltype = (UINT32)&dg_forthdocompiletypecppmemberfunction;
        return(dg_success);
    }

    // if double @@ is next occurence of @, it is cdecl
    //  single @ is cpp member function
    namelength2 = namelength;

    flag = dg_scanforbyte((void*)pname, &namelength2, '@');

    if (flag != dg_success)
    {
        return(flag);
    }

    if (-1 == namelength2)
    {
        // No @ in name; this shouldn't happen; defaulting to cdecl.
        return(dg_success);
    }

    if (namelength2 + 1 >= namelength)
    {
        // Single @ at end of string; this shouldn't happen; defaulting to cdecl.
        return(dg_success);
    }

    __try
    {
        c = pname[namelength2 + 1];        
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    if ('@' != c)
    {
        // single @ found after single ?, it's cpp member function
        *pcalltype = (UINT32)&dg_forthdocompiletypecppmemberfunction;
    }

    // @@ found after single ?, it's cdecl
    return(dg_success);    
}
*/


// windows supports calling this function with null buffer and buflength to return length of value
//  not sure of equivalent linux function
// using badbufferhandle as null buffer for this function
// returned valuelength includes null terminator most of the time
//   sometimes when the variable is declared but is empty windows sends back 0
const char* dg_getenvironmentvariablename = "dg_getenvironmentvariable";

const char* dg_getenvironmentvariable(
                Bufferhandle* pBHarrayhead,
                const char* pvarname,
                unsigned char* pbuf,
                UINT64 buflength,
                UINT64* pvaluelength, 
                const char* forceerrorflag)
{
    DWORD bflag = false;
    unsigned char* pbuffer = pbuf;
    UINT64* faddress;
    DWORD lasterror;
    DWORD valuelength32;

    EXTENSION_CONTROL_BLOCK* lpECB;

    if ((unsigned char*)badbufferhandle == pbuffer)
    {
        // windows uses NULL
        pbuffer = NULL;
    }

    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }

    __try
    {
        *pvaluelength = buflength; // for isapi mode must set valuelength to buflength
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return(dg_badmemoryerror);
    }

    // see if this is isapi
    __try
    {
        lpECB = (EXTENSION_CONTROL_BLOCK*)pBHarrayhead->pisapiecb;
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        *pvaluelength = (UINT64)-1;
        return(dg_badmemoryerror);
    }

    if (lpECB != (EXTENSION_CONTROL_BLOCK*)-1)
    {
        __try
        {
            // faddress = (UINT64*)(((_EXTENSION_CONTROL_BLOCK*)(pBHarrayhead->pisapiecb))->GetServerVariable);

            // dg_openfileforwritenew((const char*)"c:\\dglu\\address.txt", &hfile, dg_success);
            // dg_writefile(pBHarrayhead, hfile, (unsigned char*)"address = ", 10, dg_success);
            // dg_writefileuint32todec(pBHarrayhead, hfile, (UINT32)faddress);
            // dg_closefile(hfile, dg_success);

            //***align16here***
            bflag = ((_EXTENSION_CONTROL_BLOCK*)(pBHarrayhead->pisapiecb))->GetServerVariable(
                ((_EXTENSION_CONTROL_BLOCK*)(pBHarrayhead->pisapiecb))->ConnID,
                (char*)pvarname, 
                pbuffer, 
                &valuelength32); // includes null terminator on output

            *pvaluelength = (UINT64)valuelength32;

            lasterror = 0;
            /*
            if (0 != faddress)
            {
                bflag = dg_callprocaddressalign16(
                    faddress,
                    4,
                    ((_EXTENSION_CONTROL_BLOCK*)(pBHarrayhead->pisapiecb))->ConnID,
                    pvarname,        // pointer to 0 terminated environment variable name
                    pbuffer,         // pointer to destination buffer
                    pvaluelength);   // pointer to destination buffer length
            }
            */

            if (false == bflag) // yes it's false on failure, true (1) = success
            {
                 lasterror = ::GetLastError();
            //    dg_openfileforwritenew((const char*)"c:\\dglu\\goterror.txt", &hfile, dg_success);
            //    dg_writefile(pBHarrayhead, hfile, (unsigned char*)"got error getting environment variable - code ", 45, dg_success);
            //    dg_writefileuint32todec(pBHarrayhead, hfile, bflag);
            //    dg_closefile(hfile, dg_success);
            }
        }
        __except(EXCEPTION_EXECUTE_HANDLER)
        {
            *pvaluelength = (UINT64)-1;
            return(dg_osexception);
        }

        if (0 != lasterror)
        {
            // this means either pointer to control block is bad, the name string is bad, 
              // or the return buffer is bad
            if (ERROR_INVALID_PARAMETER == lasterror)
            {
                *pvaluelength = (UINT64)-1;
                return (dg_invalidparametererror);
            }

            // this one is ok, you get this under iis for not found case
            if (ERROR_INVALID_INDEX == lasterror)
            {
                *pvaluelength = (UINT64)-1;
                return (dg_success);
            }

            // this one is ok
            if (ERROR_INSUFFICIENT_BUFFER == lasterror)
            {
                // value length returned from win32 includes null terminator soo...
                if (*pvaluelength > 0)
                {
                    *pvaluelength--;
                }

                return (dg_success);
            }

            // this one is ok too I think
            if (ERROR_NO_DATA == lasterror)
            {
                // I'm guessing the server set the value length to 0 in this case
                //  but I'll do it anyways
                *pvaluelength = 0;
                return (dg_success);
            }
        }

        // value length returned from win32 includes null terminator soo...
        if (*pvaluelength > 0)
        {
            *pvaluelength--;
        }

        return (dg_success);
    }

    __try
    {
        // this is probably reentrant since windows copies the string from a PEB
        //  and windows has functions to lock access to the PEB
        //  see http://undocumented.ntinternals.net/UserMode/Undocumented%20Functions/NT%20Objects/Process/PEB.html
        bflag = ::GetEnvironmentVariable(
            pvarname, 
            (char*)pbuffer, 
            (UINT32)buflength); // gonna assume buflength will fit into a UINT32

        // 64bit code IS getting called somehow and diaperglu compiled code confuses alignment. This
        //   realigns the stack for 64bit code.
        /*
        bflag = dg_callprocaddressalign16(
            (UINT32*)&GetEnvironmentVariable, 
            3,
            pvarname, 
            pbuffer, 
            buflength);
        */

    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        *pvaluelength = (UINT64)-1;

        return (dg_osexception);
    }

    // if found and the buffer passed in is large enough, the length in bytes of
    //  the value is returned and the value is copied; however Windows requires
    //  a buffer 1 larger than the value length for the null terminator
    // if found and the buffer passed in is NOT large enough, the length of the 
    //  value in bytes + 1 byte for the null terminator is returned
    // if not found, the return value is 0 and GetLastError 
    //  returns ERROR_ENVVAR_NOT_FOUND
    
    if (0 == bflag)
    {
        bflag = ::GetLastError();

        if (bflag == ERROR_ENVVAR_NOT_FOUND)
        {
            *pvaluelength = (UINT64)-1;
            return (dg_success);
        }
        else
        {
            // environment variable exists,
            // buffer was big enough to hold it
            // but it's length was 0?
            *pvaluelength = 0;
            return (dg_success);
        }
    }

    // memory for pvaluelength checked earlier
    *pvaluelength = (UINT64)bflag;

    if (bflag >= buflength) // can't really be = except for 0 case
    {
        (*pvaluelength)--;
    }

    return (dg_success);
}





/////////////////////////////////////////////////////////////////
// Internet Services Application Programming Interface (ISAPI) //
/////////////////////////////////////////////////////////////////

BOOL WINAPI GetExtensionVersion(HSE_VERSION_INFO *pVer)
{
    Bufferhandle BHarrayhead;
    UINT32 i;
    char c;
    UINT32 dflag;

    UINT64 hfile;

    dg_initpbharrayhead(&BHarrayhead);

    // make sure this string is less than 256 characters
    const char* src = "DiaperGlu ISapi server extension";

    // dg_openfileforwritenew((const char*)"c:\\Users\\thain\\desktop\\gothere.txt", &hfile, dg_success);
    // dg_writefile(&BHarrayhead, hfile, (unsigned char*)"got here GEV", 12, dg_success);
    // dg_closefile(hfile, dg_success);

    // ::MessageBeep(0xFFFFFFFF);

    __try
    {
        pVer->dwExtensionVersion = 4; // version of dglu

        dflag = 1;

        for (i = 0; i< HSE_MAX_EXT_DLL_NAME_LEN; i++)
        {
            if (dflag != 0)
            {
                c = src[i];

                (pVer->lpszExtensionDesc)[i] = c;

                if (c == 0)
                {
                    dflag = 0;
                }
            }
            else
            {
                (pVer->lpszExtensionDesc)[i] = 0;
            }
        }
        
    }
    __except(EXCEPTION_EXECUTE_HANDLER)
    {
        return (false);
    }

    

    return(true); // windows true
}




BOOL WINAPI TerminateExtension(DWORD dwFlags)
{
    return(true); // true means to unload the extension
}


/*
BOOL WINAPI DllMain(
  HINSTANCE hinstDLL,
  DWORD fdwReason,
  LPVOID lpvReserved
)
{
    //HANDLE hfile;
    //dg_openfileforwritenew((const char*)"c:\\dglu\\didmain.txt", &hfile, dg_success);
    //dg_writefile(hfile, (unsigned char*)"got here", 8, dg_success);
    //dg_closefile(hfile, dg_success);
    return (true);
}
*/

// need to add support for full path isapi mode filename
// need to add support for ~\filename
// need to add support for ..\filename
// need to add support for .\filename





/*
const char* dg_forthloadcdecllibwordlistname = "dg_forthloadcdecllibwordlist";

void dg_forthloadcdecllibwordlist (Bufferhandle* pBHarrayhead)
//                           ( libraryname$ -$- libraryname$ )
//                           ( libraryhandle -openlibraryhandlestack- libraryhandle )
//                           ( -- wordlistid )
{
    UINT32 wordlistid = 0;
    UINT32 definitionid = 0;

    UINT32 i = 0;
    UINT32 j = 0;
    UINT32 namestart = 0;
    UINT32 nameend = 0;

    UINT32 namelength = 0;

    FARPROC procaddress = NULL;
    HINSTANCE libraryhandle = 0;

    UINT32 imagesize = 0;
    UINT32 numberofnames = 0;
    UINT32 numberoffunctions = 0;
    void* pfunctionoffsetarray = NULL;
    void* pnameoffsetarray = NULL;
    void* pordinalarray = NULL;

    LPCSTR pname = NULL;

    const char* flag = dg_success;
    const char* symboltype;
    UINT32 calltype;


    UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    libraryhandle = (HINSTANCE)dg_popbufferdword(pBHarrayhead, DG_LIBHANDLE_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthlibhandlebufferidname);
        dg_pusherror(pBHarrayhead, dg_forthloadcdecllibwordlistname);
        return;
    }

    dg_pushbufferdword(pBHarrayhead, DG_LIBHANDLE_BUFFERID, (UINT32)libraryhandle);

    wordlistid = dg_newwordlist(pBHarrayhead, 0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloadcdecllibwordlistname);
        return;
    }

    dg_pushbufferdword(pBHarrayhead, DG_DATASTACK_BUFFERID, wordlistid);

    flag = dg_getnumberoflibrarysymbols(libraryhandle, &numberofnames, dg_success);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_getnumberoflibrarysymbolsname);
        dg_pusherror(pBHarrayhead, dg_forthloadcdecllibwordlistname);
        return;
    }

    // quitting if no names
    if (numberofnames == 0)
    {
        return;
    }

    for (j = 0; j < numberofnames; j++)
    {
        flag = ::dg_getlibrarysymbol(
            libraryhandle, 
            j, 
            &pname, 
            &nameend, 
            &symboltype, 
            (UINT32*)&procaddress,
            dg_success);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_getlibrarysymbolname);
            dg_pusherror(pBHarrayhead, dg_forthloadcdecllibwordlistname);
            return;
        }

        if (symboltype == dg_symboltypefunction)
        {
            namelength = nameend;

            flag = dg_determinecalltypefromname(pname, namelength, &calltype);

            if (flag != dg_success)
            {
                // originally was no error here...
                dg_pusherror(pBHarrayhead, dg_forthloadcdecllibwordlistname);
                return;
            }

            definitionid = dg_newword(
                pBHarrayhead, 
                DG_CORE_BUFFERID,
                calltype,
                DG_CORE_BUFFERID,
                (UINT32)procaddress,
                DG_CORE_BUFFERID,
                (UINT32)pname,
                nameend);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthloadcdecllibwordlistname);
                return;
            }
        
            dg_linkdefinition(pBHarrayhead, wordlistid, definitionid);    

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_forthloadcdecllibwordlistname);
                return;
            }
        }
    }
}
*/



/*
void dg_forthloadlibrarystringsub (Bufferhandle* pBHarrayhead)
//                 ( libraryname$ -$- libraryname$ ) 
//                 ( -openlibraryhandlestack- libraryhandle )
{
    UINT32 numberofstringsonstack = 0;
    unsigned char* pnamelstring = NULL;
    UINT32 namelength = 0;
    const char* flag;

    UINT32 libraryhandle = 0;

    UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);

    numberofstringsonstack = dg_getnumberoflstringsonstack(pBHarrayhead, DG_STRINGOFFSETSTACK_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
        return;
    }

    if (numberofstringsonstack < 1)
    {
        dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
        return;
    }

    dg_forthturnstringinto0string(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
        return;
    }

    pnamelstring = dg_getplstring(pBHarrayhead, 
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        numberofstringsonstack - 1,
        &namelength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
        return;
    }

    flag = dg_loadlibrary((const char*)pnamelstring, &libraryhandle, dg_success);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
        return;
    }

    if (flag != dg_success)
    {
        // libraryhandle is -1, want to still return a value
        dg_pushbufferdword(pBHarrayhead, DG_DATASTACK_BUFFERID, libraryhandle);
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_loadlibraryname);
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
        return;

    }

    dg_pushbufferdword(pBHarrayhead, DG_LIBHANDLE_BUFFERID, libraryhandle);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
        return;
    }
    
    //dg_pushbufferdword(pBHarrayhead, DG_DATASTACK_BUFFERID, libraryhandle);

    //if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    //{
    //    dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
    //    return;
    //}    
}
*/


/*
void dg_forthloadlibrarystring (Bufferhandle* pBHarrayhead)
//                 ( libraryname$ -$- ) 
//                 ( -openlibraryhandlestack- libraryhandle )
//                 ( -- wordlistid )
{
    UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);

    dg_forthloadlibrarystringsub(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        // error is pushed in subroutine
        return;
    }

    dg_forthloadcdecllibwordlist(pBHarrayhead);

    // error is pushed in subroutine

    dg_forthdropstring(pBHarrayhead);
    return;
}
*/



/*
void dg_forthshowopenlibrary (Bufferhandle* pBHarrayhead)
//                           ( libraryhandle -- )
{
    UINT32 numberofnames;

    UINT32 j = 0;
    UINT32 namestart = 0;
    UINT32 nameend = 0;

    UINT32 namelength = 0;

    FARPROC procaddress = NULL;
    HINSTANCE libraryhandle = 0;

    LPCSTR pname = NULL;

    const char* flag = dg_success;
    const char* symboltype;


    UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    libraryhandle = (HINSTANCE)dg_popdatastack(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
        return;
    }


    flag = dg_getnumberoflibrarysymbols(libraryhandle, &numberofnames, dg_success);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_getnumberoflibrarysymbolsname);
        dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
        return;
    }

    // quitting if no names
    if (numberofnames == 0)
    {
        return;
    }

    for (j = 0; j < numberofnames; j++)
    {
        flag = ::dg_getlibrarysymbol(
            libraryhandle, 
            j, 
            &pname, 
            &nameend, 
            &symboltype, 
            (UINT32*)&procaddress,
            dg_success);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_getlibrarysymbolname);
            dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
            return;
        }

        if (symboltype == dg_symboltypefunction)
        {
            namelength = nameend;

            dg_writestdoutuint32tohex(pBHarrayhead, (UINT32)procaddress);
            dg_printzerostring(pBHarrayhead, (unsigned char*)"  ");
            dg_writestdout(pBHarrayhead, (unsigned char*)pname, namelength);
            dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
        }
    }
}
*/

/*
void dg_forthshowlibrarystring (Bufferhandle* pBHarrayhead)
{
    UINT32 libraryhandle;

    UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_forthopenlibrarystring (pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
        return;
    }

    libraryhandle = dg_popbufferdword(pBHarrayhead, DG_LIBHANDLE_BUFFERID);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
        return;
    }

    dg_forthshowopenlibrary (pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
        return;
    }

    dg_forthdrop(pBHarrayhead);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
        return;
    }

    dg_freelibrary(libraryhandle, dg_success);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
        return;
    }
}

*/

/*
void dg_forthfindlibrarysymbol (Bufferhandle* pBHarrayhead)
//    ( libraryhandle -- symboladdress|NULL )
//    ( symbolname$ -$- )
{
    UINT32 libraryhandle;
    
    UINT32 numberofstringsonstack = 0;
    unsigned char* pnametofind = NULL;
    UINT32 nametofindlength = 0;
    const char* flag;
    INT32 compareflag;
    
    UINT32 numberofnames;

    UINT32 j = 0;
    UINT32 namestart = 0;
    UINT32 nameend = 0;

    UINT32 namelength = 0;

    FARPROC procaddress = NULL;

    LPCSTR pname = NULL;

    const char* symboltype;

    UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
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
    
    flag = dg_getnumberoflibrarysymbols((HINSTANCE)libraryhandle, &numberofnames, dg_success);

    if (flag != dg_success)
    {
        dg_pusherror(pBHarrayhead, flag);
        dg_pusherror(pBHarrayhead, dg_getnumberoflibrarysymbolsname);
        dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
        return;
    }

    // quitting if no names
    if (numberofnames == 0)
    {
        dg_pushdatastack (pBHarrayhead, NULL);
        dg_forthdropstring (pBHarrayhead);
        return;
    }

    // linear search of names
    for (j = 0; j < numberofnames; j++)
    {
        flag = ::dg_getlibrarysymbol(
            (HINSTANCE)libraryhandle, 
            j, 
            &pname, 
            &nameend, 
            &symboltype, 
            (UINT32*)&procaddress,
            dg_success);

        if (flag != dg_success)
        {
            dg_pusherror(pBHarrayhead, flag);
            dg_pusherror(pBHarrayhead, dg_getlibrarysymbolname);
            dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
            return;
        }

        if (symboltype == dg_symboltypefunction)
        {
            namelength = nameend;
            
            if(namelength == nametofindlength)
            {
                flag = dg_comparebytes (
                    pnametofind, 
                    nametofindlength,
                    (unsigned char*)pname,
                    namelength,
                    &compareflag);
                    
                if (0 == compareflag)
                {
                    dg_pushdatastack (pBHarrayhead, (UINT32)procaddress);
                    dg_forthdropstring (pBHarrayhead);
                    return;
                }
            } 
        }
    }
    
    // not found
    dg_pushdatastack (pBHarrayhead, NULL);
    dg_forthdropstring (pBHarrayhead);
}
*/

/*
const char* dg_checkbharrayhead (Bufferhandle* pBHarrayhead)
{
    void* x = NULL;
    
    if ((pBHarrayhead == (Bufferhandle*)(-1)) || (pBHarrayhead == 0))
    {
        return (dg_nullpbharrayheaderror);
    }

    // seeing if can read 1st memory location
    try
    {
        x = pBHarrayhead->pbuf;
    }
    catch (...)
    {
        return (dg_bharrayheadbadmemerror);
    }

    // seeing if can read last memory location and if id is correct
    try
    {
        if (pBHarrayhead->id != BHarrayheadid)
        {
            return(dg_notbharrayheaderror);
        }
    }
    catch (...)
    {
        return (dg_bharrayheadbadmemerror);
    }

    return (dg_success);
}


const char* dg_checkbharray (Bufferhandle* pBHarrayhead)
{
    int x = 0;
    const char* flag = NULL;

    flag = dg_checkbharrayhead(pBHarrayhead);

    if (flag != dg_success)
    {
        return (flag);
    }

    if ((pBHarrayhead->pbuf == (void*)(-1)) || (pBHarrayhead->pbuf == 0))
    {
        return(dg_nullpbharrayerror);
    }

    // just checking first int
    try
    {
        x = *((UINT32*)(pBHarrayhead->pbuf));    
    }
    catch (...)
    {
        return (dg_bharraybadmemerror);
    }

    return (dg_success);
}
*/



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





/*
void dg_trycatchbadmemoryerror()
{
    void (*pnewexceptionfilter)(void);
    
    pnewexceptionfilter = (void (*)())&dg_catchbadmemoryerror;

    SetUnhandledExceptionFilter(
        (LPTOP_LEVEL_EXCEPTION_FILTER)pnewexceptionfilter);
}


void dg_trycatchbadmemoryerrorwithfullframe()
{
    void (*pnewexceptionfilter)(void);

    pnewexceptionfilter = (void (*)())&dg_catchbadmemoryerrorwithfullframe;

    SetUnhandledExceptionFilter(
        (LPTOP_LEVEL_EXCEPTION_FILTER)pnewexceptionfilter);
}


void dg_endtrycatchbadmemoryerror()
{
    // set exception handling back to default
    SetUnhandledExceptionFilter(NULL);
}
*/

const char* dg_runfileandwaitname = "dg_runfileandwait";

const char* dg_runfileandwait(
    Bufferhandle* pBHarrayhead,
    unsigned char* pfilename,        // Win64 limit of  32,767 characters ... this is really the command line on Windows
                                      // win64  .. this should point to the string stack memory and should be r/w
    char* const argv[],              // mac os x... unused in Windows        
    char* const envp[],             
    const char* forceerrorflag)
{
    BOOL errorflag;
    const char* perror;
    DWORD waitstatus;
    DWORD errorstatus;
    UINT64 i;
    DWORD exceptioncode;

    STARTUPINFO mystartupinfo;
    PROCESS_INFORMATION myprocessinformation;

    if (forceerrorflag != dg_success)
    {
        return(forceerrorflag);
    }

    // since the memory is allocated on the stack... it is there... not checking for error
    dg_fillwithbytesub(
        (unsigned char*)&mystartupinfo,
        sizeof(STARTUPINFO),
        0);

    dg_fillwithbyte(
        (unsigned char*)&myprocessinformation,
        sizeof(PROCESS_INFORMATION),
        0);

    mystartupinfo.cb = sizeof(STARTUPINFO);

    __try
    {    
        // This funtion requires 16 byte alignment when called. Found that out the hard way along with a major bug 9/22/2020
        errorflag = CreateProcessA(
            NULL,                  // LPCSTR                lpApplicationName,
            (LPSTR)pfilename,      // (LPSTR)pbuf,           // LPSTR                 lpCommandLine,
            NULL,                  // LPSECURITY_ATTRIBUTES lpProcessAttributes,
            NULL,                  // LPSECURITY_ATTRIBUTES lpThreadAttributes,
            FALSE,                 // BOOL                  bInheritHandles,
            0,                     // DWORD                 dwCreationFlags,
            (LPVOID)envp,          // LPVOID                lpEnvironment,
            NULL,                  // LPCSTR                lpCurrentDirectory,
            &mystartupinfo,        // LPSTARTUPINFOA        lpStartupInfo,
            &myprocessinformation  //  LPPROCESS_INFORMATION lpProcessInformation
        );
        
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
        exceptioncode = GetExceptionCode();

        if (exceptioncode == EXCEPTION_ACCESS_VIOLATION)
        {
            return (dg_badmemoryerror);
        }

        if (exceptioncode == EXCEPTION_INVALID_HANDLE)
        {
            return(dg_invalidhandleerror);
        }

        return (dg_osexception);
    }

    if (errorflag == 0)
    {
        errorstatus = GetLastError();

        if (errorstatus == 1)
        {
            return (dg_invalidfunctionerror);
        }

        if (errorstatus == 2)
        {
            return(dg_filenotfounderror);
        }

        if (errorstatus == 3)
        {
            return(dg_pathnotfounderror);
        }

        if (errorstatus == 4)
        {
            return(dg_toomanyopenfileserror);
        }

        if (errorstatus == 5)
        {
            return (dg_accessdeniederror);
        }

        if ((errorstatus == 8) || (errorstatus == 14))
        {
            return (dg_outofmemoryerror);
        }

        if (errorstatus == 0x0f)
        {
            return (dg_pathnotfounderror);
        }

        if (errorstatus == 0x14)
        {
            return (dg_devicenotfounderror);
        }

        return (dg_oserror);
    }

    waitstatus = WaitForSingleObject(
        myprocessinformation.hProcess,      // HANDLE hHandle,
        INFINITE                            // DWORD  dwMilliseconds
    );

    CloseHandle(myprocessinformation.hProcess);
    CloseHandle(myprocessinformation.hThread);

    if (waitstatus == WAIT_OBJECT_0) {
        return(dg_success);
    }

    if (waitstatus == WAIT_FAILED) {
        errorstatus = GetLastError();
        if ((errorstatus == 8) || (errorstatus = 0x14))
        {
            return(dg_outofmemoryerror);
        }

        if (errorstatus == 0x80)
        {
            // I think this means the child process already finished...
            return (dg_success);
        }

        // unknown error... letting it fall through to dg_oserror
    }

    return (dg_oserror);
}

void dg_forthgothere(Bufferhandle* pBHarrayhead)
{
    dg_printzerostring(pBHarrayhead, (unsigned char*)"got here\n");
}


const char* dg_callfunctionasyncname = "dg_callfunctionasync";

const char* dg_callfunctionasync(
    UINT64* pthreadhandle,
    void* (*pfunction)(void*),
    void* parguments)
{
    const char* pError;
    UINT64 lasterror;

    // check memory at pthreadhandle
    pError = dg_putuint64(
        pthreadhandle,
        0);

    if (pError != dg_success)
    {
        return(pError);
    }

    *pthreadhandle = (UINT64)CreateThread(
        NULL,
        0, // stack size.. 0 = default for process
        (LPTHREAD_START_ROUTINE)pfunction,
        (LPVOID)parguments,
        0,
        NULL);

    if (NULL != *pthreadhandle)
    {
        return(dg_success);
    }

    lasterror = GetLastError();

    switch (lasterror)
    {
    default:
        return(dg_oserror);
    }
}

