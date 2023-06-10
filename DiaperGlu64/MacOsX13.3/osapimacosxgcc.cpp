// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2023 James Patrick Norris
//
//    This file is part of DiaperGlu v5.11.
//
//    DiaperGlu v5.11 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.11 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.11; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// June 10, 2023              //
// version 5.11               //
// /////////////////////////////

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
#include <fcntl.h>
#include <dlfcn.h>
// #include <pthread.h>
//#include <elf.h>

#include <termios.h>
#include <unistd.h>
#include <sys/syslimits.h>
#include <stdlib.h>  // for getenv... need to use post args array instead
                     // doesn't look like Mac OS X has the post args array
//#include <stdio.h>
#include "mach-o/dyld.h"
#include "mach-o/nlist.h"
#include "objc/runtime.h"
#include "objc/message.h"
#include "mach-o/reloc.h"

//#include "ImageLoaderMachO.h"

#include "../diapergluforth.h"

// const char dg_success[] = "success";
// const char dg_badmemoryerror[] = "bad memory error";

// const char dg_oserror[] = "operating system error";
const char dg_osexception[] = "operating system exception";
// const char dg_outofmemoryerror[] = "out of memory error";
// const char dg_invalidhandleerror[] = " - os invalid handle error";
const char dg_invalidfunctionerror[] = "invalid function error";

const char dg_sizenotxpagesizeerror[] = "size not a multiple of system page size error";

// const char dg_filenotfounderror[]          = " - file not found error";
// const char dg_pathnotfounderror[]          = " - path not found error";
// const char dg_accessdeniederror[]          = " - access denied error";
// const char dg_toomanyopenfileserror[]      = " - too many open files error";

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
const char dg_badprocessiderror[] = " - process does not exist or is not a child of the calling process";
const char dg_interruptedbysignalerror[] = " - call was interrupted and not restarted error";
const char dg_toomanyprocesseserror[] = " - too many processes error";
const char dg_freemutexwhilelockederror[] = " - can't free a mutex while it is locked error";
const char dg_woulddeadlockerror[] = " - waiting for mutex will cause a deadlock error";
const char dg_mutexisnotlockederror[] = " - mutex is not locked error";

// const char dg_writeprotectederror[]        = " - write protected error";
const char dg_diskisfullerror[] = " - disk is full error";
const char dg_invaliduserbuffererror[] = " - invalid user buffer error, probably means too many pending i/o requests - os couldn't keep up and ran out of buffers";
const char dg_unknownwriteerror[] = " - unknown write error";
const char dg_couldnotgetpagelockerror[] = " - os could not get page lock on the caller's memory buffer error";

const char dg_segmentgoespastenderror[] = "- offset + length goes past end of buffer error";

const char dg_badmagicerror[] = " - file or structure's magic number not what was expected error";
const char dg_missingexporttableerror[] = " - library file's export table is missing error";
const char dg_exporttablebounderror[] = " - library file export table's declared size goes into something else's memory error";


const char dg_scanforbytename[] = "dg_scanforbyte";
const char dg_comparebytesname[] = "dg_comparebytes";
const char dg_getuint64name[] = "dg_getuint64";
// const char dg_hctwostorename[] = "dg_hctwostore";


// From the handle returned from dlopen which is of type ImageLoaderMachO (and is a class)
// I need fDynamicInfo and fSymbols, these are pointers..... soo
//  if I find out the offsets of these pointers in the ImageLoaderMachO structure, 
//  I should be able to kick butt

// ///////////////////////
// Note to self:
//   To make this api the same on all platforms, need to standardize the value
//   of a bad buffer handle. I read somewhere that NULL is a valid buffer address
//   in Linux, but now the man page I'm reading says mmap will never return 0 
//   for an address. In any case I'm going to make -1 the bad buffer handle value
//   from this api's point of view. 
// ///////////////////////


// struct relocation_info {
//    int32_t    r_address;    /* offset in the section to what is being
//                    relocated */
//    uint32_t     r_symbolnum:24,    /* symbol index if r_extern == 1 or section
//                    ordinal if r_extern == 0 */
//         r_pcrel:1,     /* was relocated pc relative already */
//         r_length:2,    /* 0=byte, 1=word, 2=long, 3=quad */
//         r_extern:1,    /* does not include value of sym referenced */
//         r_type:4;    /* if not 0, machine specific relocation type */
// };


/*
struct dg_macosx_dylibhandle;

struct dg_dependentLibrary {
    struct dg_macosx_dylibhandle*	pimage;
	UINT32	required : 1,
            checksumMatches : 1,
            isReExported : 1,
            isSubFramework : 1;
};
        
struct dg_macosx_dylibhandle {
    //UINT32 (**imp)()                       pVtable pointer; // 00
    Class                                   *isa; // 00  This is not it....
    const char*                             pPath;  // 04
    const char*                             pLogicalPath; // 08
    dev_t                                   device; // 0C
	ino_t                                   inode; // 10
	time_t                                  lastModified; // 18
	UINT64                                  offsetInFatFile; // 1C
	struct dg_dependentLibrary*             pLibraries; // 24
	UINT32                                  librariesCount; // 28
	UINT32                                  pathHash; // 2C
	UINT32                                  dlopenReferenceCount;	// 30 // count of how many dlopens have been done on this image
	UINT32                                  staticReferenceCount;	// 34 // count of images that have a fLibraries entry pointing to this image
	UINT32                                  dynamicReferenceCount;	// 38 // count of images that have a fDynamicReferences entry pointer to this image
	struct dg_macosx_dylibhandle*           pDynamicReferences;     // 3C
    UINT32                                  depthLoadOrder; // 40
    UINT32                                  flags; // 44
    UINT32                                  initializerLocak; // 48
    const struct mach_header*               pMachHeader; // 4C
	const unsigned char*                    pLinkEditBase; // add any internal "offset" to this to get actual address
	const unsigned char*                    pSymbolTable; // this can be either array of NLIST or NLIST64
	const unsigned char*                    pStringTable;
	const struct dysymtab_command*          pDynamicInfo;
	UINT32                                  slide; // might be 64
	const struct twolevel_hints_command*	pTwoLevelHints;
	const struct dylib_command*				pDylibID;
	//class SegmentMachO*						fSegmentsArray;
	//class SegmentMachO*						fReadOnlyImportSegment; // NULL unless __IMPORT segment built with -read_only_stubs
	//static uint32_t							fgReadOnlyImportSpinLock;
};
*/

// I think the length of this structure is probably 0x68
// struct dg_macosx10_6_8_dylibhandle {
    //dg_macosx10_6_8_dylibvtable             *pVtable;               // 00  This is probably it....
//    UINT32                                  (**pFunctions)(UINT32, ...);
//    const char*                             pPath;                  // 04
//    const char*                             pLogicalPath;           // 08
//    dev_t                                   device;                 // 0C
//	ino_t                                   inode;                  // 10
//	time_t                                  lastModified;           // 18
//	UINT32                                  pathHash;               // 1C
//	UINT32                                  dlopenReferenceCount;	// 20 // count of how many dlopens have been done on this image
//	UINT32                                  staticReferenceCount;	// 24 // count of images that have a fLibraries entry pointing to this image
//	UINT32                                  dynamicReferenceCount;	// 2C // count of images that have a fDynamicReferences entry pointer to this image
//	struct dg_macosx_dylibhandle*           pDynamicReferences;     // 30
//  void*                                   pInitializerRecursiveLock; // 34 /* recursive_lock*				fInitializerRecursiveLock; */
//    UINT32                                  depthLoadOrder;            // 38
//    UINT32                                  //flags;                   // 3C
//        fState : 8,
//        fLibraryCount : 10,
//        fAllLibraryChecksumsAndLoadAddressesMatch : 1,
//        fLeaveMapped : 1,		// when unloaded, leave image mapped in cause some other code may have pointers into it
//        fNeverUnload : 1,		// image was statically loaded by main executable
//        fHideSymbols : 1,		// ignore this image's exported symbols when linking other images
//        fMatchByInstallName : 1,// look at image's install-path not its load path
//        fInterposed : 1,
//        fRegisteredDOF : 1,
//        fAllLazyPointersBound : 1,
//    fBeingRemoved : 1,
//        fAddFuncNotified : 1,
//        fPathOwnedByImage : 1,
//        fIsReferencedDownward : 1,
//        fIsReferencedUpward : 1,
//        fWeakSymbolsBound : 1;
    
 //   const struct mach_header*               pMachHeader;               // 40
//	const unsigned char*                    pLinkEditBase;             // 44 // add any internal "offset" to this to get actual address
//	UINT32                                  slide;                     // 48 // might be 64
//    uint32_t								fEHFrameSectionOffset;     // 4C
//    uint32_t								fUnwindInfoSectionOffset;  // 50
//    uint32_t								fDylibIDOffset;            // 54
    
//    uint32_t				                                           // 58
//        fSegmentsCount : 8,
//        fIsSplitSeg : 1,
//        fInSharedCache : 1,
        //#if TEXT_RELOC_SUPPORT
//        fTextSegmentRebases : 1,
//        fTextSegmentBinds : 1,
        //#endif
        //#if __i386__
//        fReadOnlyImportSegment : 1,
        //#endif
//        fHasSubLibraries : 1,
//        fHasSubUmbrella : 1,
//        fInUmbrella : 1,
//        fHasDOFSections : 1,
//        fHasDashInit : 1,
//        fHasInitializers : 1,
//        fHasTerminators : 1,
 //       fRegisteredAsRequiresCoalescing : 1; 	// <rdar://problem/7886402> Loading MH_DYLIB_STUB causing coalescable miscount
    
	//const unsigned char*                    pStringTable;             // 5C
    //const unsigned char*                    pSymbolTable;             // 60 // this can be either array of NLIST or NLIST64
	//const struct dysymtab_command*          pDynamicInfo;             // 64
// };


// psublibImagearray =  (dg_macosx10_6_8_dylibhandle & -4) + sizeof(ImageLoaderMachOClassic) + fSegmentsCount * sizeof(UINT32)
//                   =  plibImage + 0x68 + fSegmentsCount * 4
//  need to and values fetched from array with -4 to get pointer to sub images

// libraryCount = member function library count
// so... get symbols from this library... which is based on state of fDynamicInfo->tocoff
//   if fDynamicInfo->tocoff == 0
//     first symbol is at fSymbolTable[fDynamicInfo->iextdefsym]
//     number of symbols is fDynamicInfo->nextdefsym
//   else
//     use the table of contents to get the symbol names...
//     first table of contents entry is at (dylib_table_of_contents*)&fLinkEditBase[fDynamicInfo->tocoff]
//     number of entries in table of contents is at fDynamicInfo->ntoc
//     number of externally defined symbols is still fDynamicInfo->nextdefsym I guess

//   non toc method going from 0 to fDynamicInfo->nextdefsym
//      const struct macho_nlist* pSymbol = &pSymbolTable[n + fDynamicInfo->iextdefsym];
//      need to check if pSymbol != NULL
//		const char* pSymbolNameString = &pStringTable[pSymbol->n_un.n_strx];

//   using toc method going from 0 to fDynamicInfo->ntoc
//      pTableOfContents = (dylib_table_of_contents*)&fLinkEditBase[fDynamicInfo->tocoff]
//      const uint32_t index = pTableOfContents[n].symbol_index;
//		const struct macho_nlist* pSymbol = &pSymbolTable[index];
//      need to check if pSymbol != NULL
//		const char* pSymbolNameStringn = &pStringTable[pSymbol->n_un.n_strx];


const char dg_filenotfounderror[]          = " - file not found error";
const char dg_pathnotfounderror[]          = " - path not found error";
const char dg_accessdeniederror[]          = " - access denied error";
const char dg_toomanyopenfileserror[]      = " - too many open files error";
const char dg_writeprotectederror[]        = " - write protected error";

// for Linux compatibility
UINT64 dg_getpagesize () // uses <unistd.h>
{
	// this os call does not return errors according to man page
	return ((UINT64)getpagesize());
}

// const char dg_getmicrosecondssince1970Jan01name[] = "dg_getmicrosecondssince1970Jan01";

UINT64 dg_getmicrosecondssince1970Jan01()
{
    struct timeval mytimeval;
    UINT64 x;
    
    gettimeofday(&mytimeval, NULL);
    
    x = (1000000 * mytimeval.tv_sec) + mytimeval.tv_usec;
    return(x);
}

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
    pBHarrayhead->pfunctbl = dg_functiontable;
    // pBHarrayhead->diaperflags = 0;
}


UINT64 dg_gettruesize()
{
    UINT64 desiredsize = sizeof(Bufferhandle) + jumpbufferlength;
    UINT64 pagesize = dg_getpagesize();
    UINT64 truesize = ((UINT64)((desiredsize-1) / pagesize) + 1) * pagesize;
    
    return (truesize);
}

// This allocates a page.
// Unfortunately, the x86 can only have so many pages in memory at one time. Once
//  all the page handles on the x86 processor are used up, the virtual memory manager starts
//  swapping out pages to disk.
// It's probably a good idea to keep the number of pages allocated with dg_malloc to a minimum.

const char* dg_mallocname = "dg_malloc";

const char* dg_malloc(
	void** ppbuffer, 
	UINT64 size,
	const char* pforceerror)
{
	UINT64 pagesize;

	const char* perror;

	// check pphandle memory
	perror = dg_putuint64((UINT64*)ppbuffer, (UINT64)badbufferhandle);
	// *ppbuffer = badbufferhandle; // -1 in Linux
	
	if (perror != dg_success)
	{
		return (perror);
	}

	if (pforceerror != dg_success)
	{
		return(pforceerror);
	}

	pagesize = getpagesize();

	if ((size % pagesize) != 0)
	{
		return(dg_oserror);
	}

	//pphandle checked above
	*ppbuffer = mmap(	
		0, 
		size, 
		PROT_READ | PROT_WRITE | PROT_EXEC, 
		MAP_ANON | MAP_PRIVATE, 
		-1, 
		0);

	if (MAP_FAILED == *ppbuffer)
	{
		*ppbuffer = badbufferhandle;
		return (dg_outofmemoryerror);
	}

	return(dg_success);
}


const char* dg_reallocname = "dg_realloc";

const char* dg_realloc(	
		void** ppbuffer, 
		UINT64 oldsize,
		UINT64 newsize,
		const char* pforceerror)
{
	UINT64 pagesize;

	void* poldbuffer;
	const char* perror;

	perror = dg_putuint64((UINT64*)(&poldbuffer), (UINT64)(*ppbuffer));
	// poldbuffer = *ppbuffer;

	if (perror != dg_success)
	{
		return (perror);
	}

	//in case *ppbuffer is read only
	// perror = dg_putuint32((UINT32*)ppbuffer, (UINT32)badbufferhandle);
	*ppbuffer = badbufferhandle;
	
	if (perror != dg_success)
	{
		return (dg_success);
	}

	if (pforceerror != dg_success)
	{
		if (dg_outofmemoryerror == pforceerror)
		{
			*ppbuffer = poldbuffer;
		}

		return(pforceerror);
	}

	pagesize = getpagesize();

	if (((UINT64)(poldbuffer) % pagesize) != 0)
	{
		return(dg_invalidhandleerror);
	}

	if ((newsize % pagesize) != 0)
	{
		return(dg_invalidhandleerror);
	}

	if ((oldsize % pagesize) != 0) 
	{
		return(dg_invalidhandleerror);
	}

	if (newsize <= oldsize)
	{
		*ppbuffer = poldbuffer;
		return(dg_success);
	}

	perror = dg_malloc(ppbuffer, newsize, pforceerror);

	if (perror != dg_success)
	{
		// old buffer not freed
		*ppbuffer = poldbuffer;
		return(dg_outofmemoryerror);
	}

	if (poldbuffer == *ppbuffer)
	{
		// can this happen in Linux?
		// technically Linux should not give me back the same buffer...
		return(dg_success);
	}

	// I'm pretty sure you can assume move will be longword aligned on x86
	//   could move uint64s instead to make this faster...
	//   could build that into dg_movebytes...
	perror = dg_movebytes(
		(unsigned char*)poldbuffer, 
		(unsigned char*)(*ppbuffer), 
		oldsize);

	if (perror != dg_success)
	{
		// probably old buffer handle was invalid
		dg_free(*ppbuffer, newsize, dg_success);
		*ppbuffer = badbufferhandle;
		return (dg_badmemoryerror);
	}

	// don't need to clear rest of new stuff

	// free old buffer
	perror = dg_free(poldbuffer, oldsize, dg_success); 

	if (perror != dg_success)
	{
		// probably old buffer handle was invalid
		dg_free(*ppbuffer, newsize, dg_success);
		*ppbuffer = badbufferhandle;
		return (dg_invalidhandleerror);
	}

	return(dg_success);
}


const char* dg_freename = "dg_free";

const char* dg_free(
		void* pbuffer, 
		UINT64 size,
		const char* forceerrorflag)
{
	UINT64 pagesize = 0;
	int errflag;

	pagesize = getpagesize();

	if (forceerrorflag != dg_success)
	{
		return (forceerrorflag);
	}

	if (((UINT64)pbuffer % pagesize) != 0)
	{
		return (dg_invalidhandleerror);
	}

	if ((size % pagesize) != 0)
	{
		return (dg_invalidhandleerror);
	}

	//  munmap returns -1 on error, 0 on success
	errflag = munmap(pbuffer, size); 

	if (errflag != 0)
	{
		return (dg_invalidhandleerror);
	}

	return (dg_success);
}


const char* dg_readfilename = "dg_readfile";

const char* dg_readfile(
    Bufferhandle* pBHarrayhead,
    UINT64 fileid,
    unsigned char* pbuf,
    UINT64 length,
    UINT64 timeout,
    UINT64* pnumread,
    const char* forceerrorflag)
{
	INT64 myerrno;

	const char* perror;

	perror = dg_putuint64(pnumread, 0);
	// *pnumread = 0;

	if (perror != dg_success)
	{
		return (perror);
	}

	if (forceerrorflag != dg_success)
	{
		return (forceerrorflag);
	}

	if (length == 0)
	{
		return (dg_success);
	}

	*pnumread = read(fileid, (void*)pbuf, length);
	myerrno = errno;

	if (*pnumread == length)
	{
		return (dg_success);
	}

	if (-1 == *pnumread)
	{
		if (EINTR == myerrno)
		{
			// signal interrupted read before any data transferred
			return (dg_oserror);
		}
		
		if (EIO == myerrno)
		{
			// low level i/o error
			return (dg_oserror);
		}

		if (EISDIR == myerrno)
		{
			// trying to read a directory
			//  could use a more specific error here
			return (dg_accessdeniederror);
		}

		if (EBADF == myerrno)
		{
			// bad file descriptor... file not open
			return (dg_invalidhandleerror);
		}

		if (EINVAL == myerrno)
		{
			// object does not support reading
			return (dg_accessdeniederror);
		}

		if (EFAULT == myerrno)
		{
			// buffer not in process memory space
			return (dg_badmemoryerror);
		}

		if (EACCES == myerrno)
		{
			// access denied, no read permission
			//  this is not in list of errors for read but makes
			//  sense it could occur
			return (dg_accessdeniederror);
		}
	
		return (dg_oserror);
	}

	// read() is supposed to be allowed to return less than the number of bytes
	//  you asked for. But since you are supposed to see how many bytes are
	//  available before calling this function and only ask for that many,
	//  not getting that many bytes is an error.
	return (dg_oserror);
}

const char* dg_writefilename = "dg_writefile";

const char* dg_writefile(
    Bufferhandle* pBHarrayhead,
    UINT64 fileid,
    unsigned char* pbuf,
    UINT64 length,
    const char* forceerrorflag)
{
	UINT64 numwritten;

	if (forceerrorflag != dg_success)
	{
		return (forceerrorflag);
	}

	if (length == 0)
	{
		return (dg_success);
	}
	
	//numwritten = write(fileid, (const void*)pbuf, length);
	numwritten = dg_write(fileid, (UINT64)pbuf, length);

	if (numwritten == (UINT64)-1)
	{
		// need to parse errno for correct error here
		return (dg_oserror);
	}

	return (dg_success);
}


const char* dg_filetypeconsole   = "console";
const char* dg_filetypepipe      = "pipe";
const char* dg_filetypedisk      = "disk";
const char* dg_filetypeunknown   = "unknown";

const char* dg_writestdoutrawname = "dg_writestdoutraw";

const char* dg_writestdoutraw(
    Bufferhandle* pBHarrayhead, 
    unsigned char* pbuf,
    UINT64 length)
{
    const char* perror;
    const char* filetype;
 //   struct termios mytermios, mytermios2;
//    INT64 flag;
//    INT64 myerrno;
    UINT64 i;
    unsigned char c;
    
    perror = dg_getfiletype(
        pBHarrayhead,
        STDOUT_FILENO,
        &filetype,
        dg_success);
      
    if (perror != dg_success)
    {
        return (perror);
    }
    
    if (filetype != dg_filetypeconsole)
    {
        return (
            dg_writefile(
                pBHarrayhead,
                STDOUT_FILENO,
                pbuf,
                length,
                dg_success)
                );
    }
    
    for (i=0; i<length; i++)
    {
        c = pbuf[i];
        
        if (c >= 0x80)
        {
            c = c - 0x80;
        }
        
        if (c < 0x20)
        {
            c = '.';
        }
        
        if (0x7F == c)
        {
            c = '.';
        }
        
        dg_writefile(
            pBHarrayhead,
            STDOUT_FILENO,
            &c,
            1,
            dg_success);
    }
    
    return (dg_success);
}


const char* dg_closefilename = "dg_closefile";

const char* dg_closefile(
    UINT64 fileid,
    const char* forceerrorflag)
{
	INT64 errflag;
	INT64 myerrno;
	const char* perror;

	if (forceerrorflag != dg_success)
	{
		return (forceerrorflag);
	}

	errflag = fsync((INT64)fileid);
	myerrno = errno;

	if (EBADF == myerrno)
	{
		// not a handle to an open file
		return (dg_invalidhandleerror);
	}

	if (EIO == myerrno)
	{
		//I/O error during close
		return (dg_oserror);
	}

	// ignoring 'it's a pipe' error on purpose

	errflag = ::close((INT64)fileid);
	myerrno = errno;

	if (0 == errflag)
	{
		return (dg_success);
	}

	if (EBADF == myerrno)
	{
		// not an open file
		return (dg_invalidhandleerror);
	}
	
	// EINTR and EIO are the others and indicate an interrupt or i/o error
	return (dg_oserror);
}


const char* dg_getfiletypename = "dg_getfiletype";

const char* dg_getfiletype(
    Bufferhandle* pBHarrayhead,
    UINT64 fileid,
    const char** pfiletype,
    const char* forceerrorflag)
{
	UINT64 flag;
	struct stat mystat;
	INT64 myerrno;
    const char* perror;
	UINT64 filetype;

	perror = dg_putuint64(
        (UINT64*)(pfiletype),
        (UINT64)dg_filetypeunknown);

	if (perror != dg_success)
	{
		return (perror);
	}

	if (forceerrorflag != dg_success)
	{
		// should check for each error...
		return (forceerrorflag);
	}

	//Fedora 8 gcc chokes on fstat label
	//flag = ::fstat(fileid, &mystat);
	flag = dg_fstat(
        (UINT64)fileid,
        (UINT64)&mystat);

	if (0 != flag)
	{
		//myerrno = errno;
		myerrno = 0 - (INT64)flag;

		if (EBADF == myerrno)
		{
			// not an open file
			return (dg_invalidhandleerror);
		}

		if (EFAULT == myerrno)
		{
			// bad memory at mystat... should not see this one
			return (dg_badmemoryerror);
		}

		if (EACCES == myerrno)
		{
			// permission denied
			return (dg_accessdeniederror);
		}

		if (ENOMEM == myerrno)
		{
			// os out of memory
			return (dg_outofmemoryerror);
		}
		
		return (dg_oserror);
	}

	filetype = ((mystat.st_mode & 0xf000) >> 12);

	switch(filetype)
	{
		case 0:	
			*pfiletype = dg_filetypeunknown;
			break;
		case 1:
			*pfiletype = dg_filetypepipe;
			break;
		case 2:
			*pfiletype = dg_filetypeconsole;
			break;
		case 3:
			*pfiletype = dg_filetypeunknown;
			break;
		case 4:
			*pfiletype = dg_filetypeunknown;
			break;
		case 5:
			*pfiletype = dg_filetypeunknown;
			break;
		case 6:
			*pfiletype = dg_filetypedisk;
			break;
		case 7:
			*pfiletype = dg_filetypeunknown;
			break;
		case 8:
			*pfiletype = dg_filetypedisk;
			break;
		case 9:
			*pfiletype = dg_filetypeunknown;
			break;
		case 10:
			*pfiletype = dg_filetypeunknown;
			break;
		case 11:
			*pfiletype = dg_filetypeunknown;
			break;
		case 12:
			*pfiletype = dg_filetypepipe;
			break;
		case 13:
			*pfiletype = dg_filetypeunknown;
			break;
		case 14:
			*pfiletype = dg_filetypeunknown;
			break;
		default:
			*pfiletype = dg_filetypeunknown;
			break;			
	}

	return (dg_success);	
}


const char* dg_gethstdinname = "dg_gethstdin";

const char* dg_gethstdin(
    Bufferhandle* pBHarrayhead,
    UINT64* pfileid,
    const char* forceerrorflag)
{
	if (forceerrorflag != dg_success)
	{
		// should check for each error...
		return (forceerrorflag);
	}

	return (dg_putuint64(pfileid, STDIN_FILENO));
}


const char* dg_gethstdoutname = "dg_gethstdout";

const char* dg_gethstdout(
    Bufferhandle* pBHarrayhead,
    UINT64* pfileid,
	const char* forceerrorflag)
{
	if (forceerrorflag != dg_success)
	{
		// should check for each error...
		return (forceerrorflag);
	}

	return (dg_putuint64(pfileid, STDOUT_FILENO));
}


const char* dg_gethstderrorname = "dg_gethstderror";

const char* dg_gethstderror(
	Bufferhandle* pBHarrayhead,
	UINT64* pfileid,
	const char* forceerrorflag)
{
	if (forceerrorflag != dg_success)
	{
		// should check for each error...
		return (forceerrorflag);
	}

	return (dg_putuint64(pfileid, STDERR_FILENO));
}


const char* dg_getfilelengthname = "dg_getfilelength";

const char* dg_getfilelength( 
	Bufferhandle* pBHarrayhead,
	UINT64 fileid,
	UINT64* pfilelength,  // number ready for non disk files
	const char* forceerrorflag)
{
	UINT64 flag;
	const char* perror;
	int myerrno;

	struct stat mystat;

	if (forceerrorflag != dg_success)
	{
		// should check for each error...
		return (forceerrorflag);
	}

	perror = dg_putuint64(pfilelength, 0);
	
	if (dg_success != perror)
	{
		return (perror);
	}
	
	// Fedora 8 chokes on fstat label
	//flag = ::fstat((int)fileid, &mystat);
	flag = dg_fstat(
        (UINT64)fileid,
        (UINT64)&mystat);
	

	if (flag != 0)
	{
		//myerrno = errno;
		myerrno = 0 - (int)flag;

		if (EBADF == myerrno)
		{
			// not an open file
			return (dg_invalidhandleerror);
		}

		if (EFAULT == myerrno)
		{
			// bad memory at mystat... should not see this one
			return (dg_badmemoryerror);
		}

		if (EACCES == myerrno)
		{
			// permission denied
			return (dg_accessdeniederror);
		}

		if (ENOMEM == myerrno)
		{
			// os out of memory
			return (dg_outofmemoryerror);
		}
		
		
		return (dg_oserror);
	}

	*pfilelength = mystat.st_size;

	return (dg_success);
}


int dg_fgetc(UINT64 forceerror)
{
	char c = 0;

	int result = 0;

	if (forceerror != FORTH_FALSE)
	{
		return(-1);
	}

	result = read(
        STDIN_FILENO,
        (void*)&c,
        1);

	if (result != 1)
	{
		return(-1);
	}

	return ((int)c);
}


const char* dg_openfileforreadname = "dg_openfileforread";

const char* dg_openfileforread(
	const char* filename, 
	UINT64* pfileid,
	const char* forceerrorflag)
{
	int myerrno;

	const char* perror;

	perror = dg_putuint64(
        pfileid,
        badfilehandle);

	if (perror != dg_success)
	{
		return (perror);
	}
    
    // *pfileid = badfilehandle;

	if (forceerrorflag != dg_success)
	{
		return (forceerrorflag);
	}
	
	*pfileid = open(
        filename,
        O_RDONLY);
    
	myerrno = errno;

	if (*pfileid != badfilehandle)
	{
		return (dg_success);
	}
	
	if (ENOMEM == myerrno)
	{
		return (dg_outofmemoryerror);
	}

	if (EMFILE == myerrno)
	{
		return (dg_toomanyopenfileserror);
	}

	if (ENFILE == myerrno)
	{
		return (dg_toomanyopenfileserror);
	}

	if (EFAULT == myerrno)
	{
		// bad memory in filename
		return (dg_badmemoryerror);
	}

	if (ENOTDIR == myerrno)
	{
		// bad directory in path
		return (dg_pathnotfounderror);
	}

	if (ENOENT == myerrno)
	{
		// file not found
		return (dg_filenotfounderror);
	}

	if (ENAMETOOLONG == myerrno)
	{
		// path name too long - need to add a specific error
		return (dg_pathnotfounderror);
	}
	
	if (EACCES == myerrno)
	{
		// do not have correct permissions
		return (dg_accessdeniederror);
	}
	
	return (dg_oserror);
}


const char* dg_openfileforwritenewname = "dg_openfileforwritenew";

const char* dg_openfileforwritenew(
    const char* filename, 
    UINT64* pfileid,
    const char* forceerrorflag)
{
	int myerrno;

	const char* perror;
    
    int flag;

	perror = dg_putuint64(pfileid, badfilehandle);
	// *pfileid = badfilehandle;

	if (perror != dg_success)
	{
		return (perror);
	}

	if (forceerrorflag != dg_success)
	{
		return (forceerrorflag);
	}

	*pfileid = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
	myerrno = errno;

	if (*pfileid == badfilehandle)
	{
        if (ENOMEM == myerrno)
        {
            return (dg_outofmemoryerror);
        }

        if (EMFILE == myerrno)
        {
            return (dg_toomanyopenfileserror);
        }

        if (ENFILE == myerrno)
        {
            return (dg_toomanyopenfileserror);
        }

        if (EFAULT == myerrno)
        {
            // bad memory in filename
            return (dg_badmemoryerror);
        }

        if (ENOTDIR == myerrno)
        {
            // bad directory in path
            return (dg_pathnotfounderror);
        }

        if (ENOENT == myerrno)
        {
            // file not found
            return (dg_filenotfounderror);
        }

        if (ENAMETOOLONG == myerrno)
        {
            // path name too long - need to add a specific error
            return (dg_pathnotfounderror);
        }
	
        if (EACCES == myerrno)
        {
            // do not have correct permissions
            return (dg_accessdeniederror);
        }
        
        if (EIO == myerrno)
        {
            // i/o error
            return (dg_oserror);
        }
	
        // unknown error
        return (dg_oserror);
    }
    
    flag = fchmod(
        (INT64)(*pfileid),
        S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH );
    
    myerrno = errno;
    
    if (flag != 0)
    {
        if (EACCES == myerrno)
        {
            // do not have correct permissions
            return (dg_accessdeniederror);
        }
        
        if (EINTR == myerrno)
		{
			// signal interrupted operation
			return (dg_oserror);
		}
		
		if (EIO == myerrno)
		{
			// low level i/o error
			return (dg_oserror);
		}
        
        if (EPERM == myerrno)
        {
            // effective user does not match file owner or superuser
             return (dg_accessdeniederror);
        }
        
        if (EROFS == myerrno)
        {
            // read only file system
            return (dg_writeprotectederror);
        }
        
        // unknown error
        return (dg_oserror);
    }
    
    return (dg_success);
}



INT64 dg_getch()
{
    const char* perror;
    const char* filetype;
    
    struct termios mytermiosave;
	struct termios mytermio;
    
    INT64 statsflag, result;
    
    Bufferhandle BHarrayhead;
    
    // kinda slow... but script is waiting for keypress anyways
    dg_initpbharrayhead(&BHarrayhead);
    
    // on Mac Os X, BHarrayhead isn't used... so I might be able to get rid of the init call...
    perror = dg_getfiletype(
        &BHarrayhead,
        STDIN_FILENO,
        &filetype,
        dg_success);
      
    if (perror != dg_success)
    {
        return (-1);
    }
    
    if (filetype != dg_filetypeconsole)
    {
        return (dg_fgetc(FORTH_FALSE));
    }
    
    // get term 
    statsflag = tcgetattr(
        STDOUT_FILENO,
        &mytermio);
    
    if (statsflag != 0)
    {
        return (-1);
    }
    
    perror = dg_movebytes (
        (unsigned char*)&mytermio,
        (unsigned char*)&mytermiosave,
        sizeof(struct termios));
    
    if (perror != dg_success)
    {
        return (-1);
    }
    
    // disable echo, disable echo on new line override, set input to character mode
    mytermio.c_lflag &= ~(ECHO | ECHONL | ICANON);
    mytermio.c_cc[VTIME] = 0; // no timeout
    mytermio.c_cc[VMIN] = 1;  // one character only
    
    statsflag = tcsetattr(
        STDOUT_FILENO,
        TCSADRAIN | TCSASOFT,
        &mytermio);
    
    if (statsflag != 0)
    {
        return (-1);
    }

    // wait for character
    result = dg_fgetc(FORTH_FALSE);
    
    // reenable old mode regardless of error in dg_fgetc
    statsflag = tcsetattr(
        STDOUT_FILENO,
        TCSADRAIN | TCSASOFT,
        &mytermiosave);
    
    if (statsflag != 0)
    {
        // unknown error
        return (-1);
    }
    
    return (result);
}


const char* dg_getlinegetbufiderror 	= "dg_getline - error getting bufferid";
const char* dg_getlinedg_clearbuffererror 	= "dg_getline - error clearing buffer";
const char* dg_getlinereaderror 	= "dg_getline - error reading character from stdin";

void dg_getline(
	Bufferhandle* pBHarrayhead, 
	UINT64 bufferid,
	UINT64 forceerror)
{
	Bufferhandle* pBH = NULL;
	INT64 c = 0;

	unsigned char strlen = 0;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	dg_clearbuffer(
        pBHarrayhead,
        bufferid);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_getlinedg_clearbuffererror);
		return;
	}

	// get all characters from user until they press cr
	while(c != 10)
	{
		c = dg_fgetc(forceerror);

		if (c != 10) // end of buffer is a delimiter so we don't need to push the end of line character
		{
			if (c == -1) // we aren't checking to see what caused -1... might need to somewhere
			{
				dg_pusherror(pBHarrayhead, dg_getlinereaderror);
				c = 10;
			}
			else
			{
				dg_pushbufferbyte(pBHarrayhead, bufferid, (unsigned char)c);
			    // check for push error
			}
		}
	}
}


const char* dg_freelibraryname = "dg_freelibrary";

const char* dg_freelibrary(
    UINT64 libraryhandle,
    const char* forceerrorflag)
{
	int errflag;

	if (forceerrorflag != dg_success)
	{
		return (forceerrorflag);
	}

	errflag = dlclose((void*)libraryhandle);

	if (errflag != 0)
	{
		return (dg_oserror);
	}

	return (dg_success);
}


const char* dg_loadlibraryname = "dg_loadlibrary";

const char* dg_loadlibrary(
	 const char* libraryname,
	 UINT64* plibraryhandle,
	 const char* forceerrorflag)
{
	void* phlibrary;
	const char* perror;

	perror = dg_putuint64(
        plibraryhandle,
        badlibraryhandle);

	if (perror != dg_success)
	{
		return (perror);
	}
    
    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }

	phlibrary = dlopen(
        libraryname,
        RTLD_LAZY);

	if (NULL == phlibrary)
	{
		// parse error using dlerror?  most likely it's not found
		return (dg_oserror);
	}

	*plibraryhandle = (UINT64)phlibrary;

	return (dg_success);
}


/*
// this function has to take the name string on the string stack
const char* dg_findlibrarysymbolvaluename = "dg_findlibrarysymbolvalue";

const char* dg_findlibrarysymbolvalue(
    UINT32 libraryhandle,
    const char* psymbolname,
    UINT32* pvalue
    const char* forceerrorflag,
)
{
    
}
*/



//  this routine does copy the null terminator
const char* dg_getenvironmentvariablename = "dg_getenvironmentvariable";

const char* dg_getenvironmentvariable (
    Bufferhandle* pBHarrayhead,
    const char* pvarname,
    unsigned char* pbuf,
    UINT64 buflength,
    UINT64* pvaluelength,
    const char* forceerrorflag)
{
	unsigned char* pvalue;
	const char* perror;
	UINT64 minlength;

	perror = dg_putuint64(
        pvaluelength,
        (UINT64)-1);

	if (perror != dg_success)
	{
        // if there is a problem finding the varname, valuelength is -1
		return (perror);
	}
    
    // *pvaluelength = (UINT32)-1;

	// could check pvarname memory here...
    // this is not reentrant, see this:
	// http://blogs.sun.com/pgdh/entry/caring_for_the_environment_making
	pvalue = (unsigned char*)::getenv(pvarname);

    if (pvalue == NULL) // why don't they use -1 since NULL is a valid address?
	{
        // if varname not found,  then valuelength is -1
        return (dg_success);	
	}

	// need to copy string here to pbuf
	// *pvaluelength = largestsignedint;
    // *pvaluelength already -1

	perror = dg_scanforbyte(
        pvalue,
        pvaluelength,
        0);

	if (perror != dg_success)
	{
		// operating system returned a pointer to bad memory
        // if varname is found but the value's memory is bad, then
        //  valuelength is -1 
        *pvaluelength = (UINT64)-1;
		return (perror);
	}

	// if buffer not big enough for value and null terminator,
    //  just return number of bytes in value
	if ( ((*pvaluelength) + 1 > buflength) ||
         ((*pvaluelength) > buflength) )  // shouldn't happen, but just in case *pvaluelength is -1
	{
        // pvaluelength points to correct length
		return (dg_success);
	}

    // technically it's an error to pass in a bad memory pointer if
    //  the buflength is not 0, but I'm gonna return success anyways
	if ((unsigned char*)badbufferhandle == pbuf)
	{
		return (dg_success);
	}

	perror = dg_movebytes(
        pvalue,
        pbuf,
        (*pvaluelength) + 1);

	return (perror);
    
    // if varname is found but there is bad memory at pbuf, then
    //  this is the length of the environment variable's value in
    //  bytes not including the null terminator
    
    // if varname is found with no problems, then
    //  this is the length of the environment
    //  variable's value in bytes not including the null terminator
}


// const char* dg_getprocessidname = "dg_getprocessid";

pid_t dg_getcurrentprocessid()
{
    return(getpid());
}


const char* dg_forkname = "dg_fork";

const char* dg_fork(
    pid_t* ppid,
    const char* forceerrorflag)
{
    int myerrno;
    const char* perror;
    
    perror = dg_putuint64(
        (UINT64*)ppid,
        (UINT64)-1);
    
    if (perror != dg_success)
    {
        return (perror);
    }
    
    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }
    
    *ppid = fork();
    
    if (*ppid == -1)
    {
        if (EAGAIN == myerrno)
        {
            return(dg_toomanyprocesseserror);
        }
        
        if (ENOMEM == myerrno)
        {
            return(dg_outofmemoryerror);
        }
        
        return(dg_oserror);
    }
    
    return(dg_success);
}


const char* dg_execvename = "dg_execve";

const char* dg_execve(
    // Bufferhandle* pBHarrayhead,
    const char* pfilename,
    char *const argv[],
    char *const envp[],
    const char* forceerrorflag)
{
    int flag;
    int myerrno;
    
    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }
    
    // this call should not return... if it does then there was an error
    flag = execvp(
        pfilename,
        argv);
    
    myerrno = errno;
    
    // if the call returns there was an error and the flag is supposed to be -1
    /*
    if (flag != -1)
    {
        return(dg_oserror);
    }
    */
    
    if (ENOMEM == myerrno)
    {
        return (dg_outofmemoryerror);
    }
        
    if (E2BIG == myerrno)
    {
        return(dg_parametersovermaxsizeerror);
    }
        
    if (EACCES == myerrno)
    {
        // do not have correct permissions
        return (dg_accessdeniederror);
    }
        
    if (EFAULT == myerrno)
    {
        return (dg_badmemoryerror);
    }
        
    if (EIO == myerrno)
    {
        return (dg_ioerror);
    }
        
    if (ELOOP == myerrno)
    {
        return (dg_toomanysymboliclinkserror);
    }
        
    if (ENAMETOOLONG == myerrno)
    {
        return (dg_pathorfilenametoolongerror);
    }
        
    if (ENOENT == myerrno)
    {
        return (dg_filenotfounderror);
    }
        
    if (ENOEXEC == myerrno)
    {
        return (dg_notexecutablefileerror);
    }
        
    if (ENOTDIR == myerrno)
    {
        return (dg_partofpathnotdirectoryerror);
    }
        
    if (ETXTBSY == myerrno)
    {
        return (dg_fileopenforwriteerror);
    }
        
    // unknown error
    return (dg_oserror);
}


const char* dg_waitpidname = "dg_waitpid";

const char* dg_waitpid(
    // Bufferhandle* pBHarrayhead,
    pid_t pid,
    int *pstatus,
    int options,
    pid_t* pchildprocessid,
    const char* forceerrorflag)
{
    int myerrno;
 
    const char* perror;
    
    perror = dg_putuint64(
        (UINT64*)pchildprocessid,
        (UINT64)-1);
    
    if (perror != dg_success)
    {
        return (perror);
    }
 
    // could check the memory at stat_loc too
    
    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }
    
    *pchildprocessid = waitpid(
        pid,
        pstatus,
        options);
    
    myerrno = errno;
 
    if (*pchildprocessid != -1)
    {
        if (WIFEXITED((*pstatus))) // this means the program exited with 0
        {
            // must be same flag value used in dg_runfileandwait
            if ( ( (WEXITSTATUS((*pstatus))) & 0xFF ) == 0xFF )
            {
                return(dg_couldnotrunfileerror);
            }
            
            // must be same flag value used in dg_runfileandwait
            if ( (WEXITSTATUS((*pstatus)) ) == 0 )
            {
                return(dg_success);
            }
            
            // program ran but returned an error code
            return(dg_programexitedwitherrorerror);
        }
        
        // program did not exit normally but also did not return an error
        return (dg_oserror);
    }
    
    // if WNOHANG was specified, you can't get the ECHILD error
    
    // there were no children to wait on
    //   is this what happens if the child finishes running between the execve and the waitpid calls?
    //   if so, then this is not an error
    if (ECHILD == myerrno)
    {
        return (dg_badprocessiderror);
    }
        
    if (EINTR == myerrno)
    {
        return (dg_interruptedbysignalerror);
    }
        
    if (EINVAL == myerrno)
    {
        // the options are invalid
        return (dg_invalidparametererror);
    }
        
    // unknown error
    return (dg_oserror);
}

UINT64 dg_getmutexhandlesize()
{
    return(DG_MUTEX_MEM_SIZE);
}

// Windows returns a mutex handle, user does not have to allocate any memory
// Mac expects you to allocate fixed memory for a structure and uses the address
//  of the structure as the handle

// 2022 Jan 28
// The problem is, allocating fixed memory for something small for an OS function
//  is a bit tricky... I could:
//  use cmalloc (not an option)
//  recreate the functionality of cmalloc (don't like this one)
//  have the user do the allocation... that way it could go whereever the user wants...
//   but it would be better to automate it...
//  allocate a fixed size buffer to specifically hold mutex handles....
//   but then what if someoene is using and freeing them a lot...
//  allocate a fixed size buffer to hold mutex handles that has a header
//   and the header keeps track of which ones are free or in use (one bit each)
//   and in the documentation tell the user about the limit on the number of open
//   mutexes at once... and add a function to allow them to resize it, but you have
//   do use the function when there are no in use mutexes...
//     the header would have:
//      magic
//      size of each array element
//      (number of elements can be calculated from array size... but...)
//      one bit for each array element
//      number of UINT64s used to hold the free list (64 * this number is the number of elements)
//     or
//      instead of a bit for each element... use a separate buffer and have next free list like freeable lstrings

/*
struct DG_Mutex_Holder
    {
        UINT64 magic; // 'mtxh'
        UINT64 mutexhandle;
        UINT64 ismutexlockedflag;
        unsigned char mutexmem[DG_MUTEX_MEM_SIZE]; // not really used on windows... except for testing... 
        UINT64 aftermutexmem;  // for testing... to see if memory after mutexmem gets corrupted by os call
    };
*/

const char* dg_newmutexname = "dg_newmutex";

const char* dg_newmutex(
    struct DG_Mutex_Holder* pmutexholder,
    const char* forceerrorflag)
{
    int myerrno;
    const char* perror;
    
    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }
    
    // check the memory at the mutex handle
    perror = dg_fillwithbyte (
        (unsigned char*)pmutexholder,
        sizeof(DG_Mutex_Holder),  // length,
        0);                       // value);
    
    if (perror != dg_success)
    {
        return (perror);
    }
    
    pmutexholder->magic = DG_MUTEX_HOLDER_MAGIC;
    
    // pmutexholder->ismutexlockedflag = 0; // is done with dg_fillwithbyte
    
    myerrno = pthread_mutex_init(
        (pthread_mutex_t*)(&(pmutexholder->mutexmem)), 
        NULL);
    
    if (0 == myerrno)
    {
        pmutexholder->mutexhandle = (UINT64)(&(pmutexholder->mutexmem));
        return (dg_success);
    }
    
    if (EAGAIN == myerrno)
    {
        return (dg_toomanyprocesseserror);
    }
        
    if (ENOMEM == myerrno)
    {
        return (dg_outofmemoryerror);
    }
        
    if (EINVAL == myerrno)
    {
        // the options are invalid
        return (dg_invalidparametererror);
    }
        
    // unknown error
    return (dg_oserror);
}


const char* dg_freemutexname = "dg_freemutex";

const char* dg_freemutex(
    struct DG_Mutex_Holder* pmutexholder,
    const char* forceerrorflag)
{
    int myerrno;
    const char* perror;
    
    // check the memory at the mutex handle
    perror = dg_readallbytes (
        (unsigned char*)pmutexholder,
        sizeof(DG_Mutex_Holder));  // length,
    
    if (perror != dg_success)
    {
        return (perror);
    }
    
    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }
    
    if (pmutexholder->magic != DG_MUTEX_HOLDER_MAGIC)
    {
        return(dg_badmagicerror);
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
    
    myerrno = pthread_mutex_destroy((pthread_mutex_t*)(pmutexholder->mutexhandle));
    
    if (0 == myerrno)
    {
        pmutexholder->mutexhandle = (UINT64)-1;
        return (dg_success);
    }
    
    if (EBUSY == myerrno)
    {
        return (dg_freemutexwhilelockederror);
    }
        
    if (EINVAL == myerrno)
    {
        // the options are invalid
        return (dg_invalidparametererror);
    }
        
    // unknown error
    return (dg_oserror);
}


const char* dg_lockmutexname = "dg_lockmutex";

const char* dg_lockmutex(
    struct DG_Mutex_Holder* pmutexholder,
    const char* forceerrorflag)
{
    int myerrno;
    const char* perror;
    
    // check the memory at the mutex handle
    perror = dg_readallbytes (
        (unsigned char*)pmutexholder,
        sizeof(DG_Mutex_Holder));  // length,
    
    if (perror != dg_success)
    {
        return (perror);
    }
    
    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }
    
    if (pmutexholder->magic != DG_MUTEX_HOLDER_MAGIC)
    {
        return(dg_badmagicerror);
    }
    
    if (pmutexholder->ismutexlockedflag != FORTH_FALSE)
	{
		return(dg_woulddeadlockerror);
	}
    
    myerrno = pthread_mutex_lock((pthread_mutex_t*)(pmutexholder->mutexhandle));
    
    if (0 == myerrno)
    {
        pmutexholder->ismutexlockedflag = FORTH_TRUE;  // locked while holding the mutex
        return (dg_success);
    }
    
    if (EDEADLK == myerrno)
    {
        return (dg_woulddeadlockerror);
    }
        
    if (EINVAL == myerrno)
    {
        // the options are invalid
        return (dg_invalidparametererror);
    }
        
    // unknown error
    return (dg_oserror);
}


const char* dg_unlockmutexname = "dg_unlockmutex";

const char* dg_unlockmutex(
    struct DG_Mutex_Holder* pmutexholder, 
    const char* forceerrorflag)
{
    int myerrno;
    const char* perror;
    
    // check the memory at the mutex handle
    perror = dg_readallbytes (
        (unsigned char*)pmutexholder,
        sizeof(DG_Mutex_Holder));  // length,
    
    if (perror != dg_success)
    {
        return (perror);
    }
    
    if (forceerrorflag != dg_success)
    {
        return (forceerrorflag);
    }
    
    if (pmutexholder->ismutexlockedflag == FORTH_FALSE)
	{
		return(dg_mutexisnotlockederror);
	}
    
    if (pmutexholder->magic != DG_MUTEX_HOLDER_MAGIC)
    {
        return(dg_badmagicerror);
    }
    
    pmutexholder->ismutexlockedflag = FORTH_FALSE; // unlocked while holding the mutex
    
    myerrno = pthread_mutex_unlock((pthread_mutex_t*)(pmutexholder->mutexhandle));
    
    if (0 == myerrno)
    {
        return (dg_success);
    }
    
    if (EPERM == myerrno)
    {
        return (dg_mutexisnotlockederror);
    }
        
    if (EINVAL == myerrno)
    {
        // the options are invalid
        return (dg_invalidparametererror);
    }
        
    // unknown error
    return (dg_oserror);
}


const char* dg_runfileandwaitname = "dg_runfileandwait";

const char* dg_runfileandwait(
    Bufferhandle* pBHarrayhead,
    const char* pfilename,
    char *const argv[],
    char *const envp[],
    const char* forceerrorflag)
{
    int pid;
    int pchildprocessid;
    int stat_loc;
    const char* perror;
    
    // skipping checks of memory at ppid, forceerrorflag, and init of ppid
    //   because dg_fork does it
    perror = dg_fork(
        &pid,
        forceerrorflag);
    
    if (perror != dg_success)
    {
        return(perror);
    }
    
    if (pid == -1)
    {
        // this shouldn't happen because dg_fork is supposed to catch this
        return(dg_oserror);
    }
    
    if (pid == 0)
    {
        // this is the child process
        perror = dg_execve(
            pfilename,
            argv,
            envp,
            dg_success);
        
        // this call should not return... if it does then there was an error
          // like the file could not be found or something... is there an way to let
          // the parent know if you are not doing a wait for it to finish?
          // is there a way to wait for a process to start?
          // ... the child could send a message to the parent....
        
        // exiting the child process... the exit status passed to parent only uses 8 bits
        // when I pass a bad filename to execve, this exit does not get called
        _exit(0xFFFF);
    }
    
    // this is the parent process
    perror = dg_waitpid(
        // pBHarrayhead,
        pid,
        &stat_loc,
        WUNTRACED,
        &pchildprocessid,
        dg_success);
    
    return (perror);
}


// needed for windows compatibility
void dg_forthfixpathstring (Bufferhandle* pBHarrayhead)
{
}

/*
// const char* dg_forthloadlibrarystringsubname = "dg_forthloadlibrarystringsub";

void dg_forthloadlibrarystringsub (Bufferhandle* pBHarrayhead)
//     ( libraryname$ -$- )
//     ( -openlibraryhandlestack- libraryhandle )
{
	UINT64 numberofstringsonstack = 0;
	unsigned char* pnamelstring = NULL;
	UINT64 namelength = 0;
	const char* flag;

	UINT64 libraryhandle = 0;

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

	numberofstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
		return;
	}

	if (numberofstringsonstack < 1)
	{
		dg_pusherror(pBHarrayhead, dg_stringstackunderflowerror);
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
		return;
	}

	dg_forthturnstringinto0string(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
		return;
	}

	pnamelstring = dg_getplstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		numberofstringsonstack - 1,
		&namelength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
		return;
	}

	flag = dg_loadlibrary(
        (const char*)pnamelstring,
        &libraryhandle,
        dg_success);

	if (flag != dg_success)
	{
		// libraryhandle is -1, want to still return a value
		dg_pushbufferuint64(
            pBHarrayhead,
            DG_DATASTACK_BUFFERID,
            libraryhandle);
        
		dg_pusherror(pBHarrayhead, flag);
		dg_pusherror(pBHarrayhead, dg_loadlibraryname);
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
		return;

	}

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_LIBHANDLE_BUFFERID,
        libraryhandle);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthlibhandlebufferidname);
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
		return;
	}
	
	dg_forthdropstring(pBHarrayhead);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
		return;
	}
	
}
*/

/*
const char* dg_getlibdysyminfo10_6_8name = "dg_getlibdysyminfo10_6_8";

void dg_getlibdysyminfo10_6_8 (
    Bufferhandle* pBHarrayhead,
    dg_macosx10_6_8_dylibhandle* pLibrary,
    UINT32* pFirstSymbolIndex,
    UINT32* pNumberOfSymbols,
    UINT32* pSymbolSize,
    UINT32* pStringTableSize,
    const char** ppSymbolTable,
    const char** ppSymbolTableStrings)
{
    UINT32 numberofcommands = pLibrary->pMachHeader->ncmds;
    
    UINT32 machoheadersize;
    
    UINT32 i;
    
    *ppSymbolTable = NULL;
    const struct load_command* pCommand = NULL;
    
    // mach_header has 2 sizes but both are same except 64 has 1 extra reserved UINT32 on end
    const struct mach_header* mypMachHeader;
    
    struct dysymtab_command* pDynSymbolCommand = NULL;
    const struct symtab_command* pSymbolTableCommand = NULL;
    
    const char* pSymbolTableStrings = NULL;
    
    *ppSymbolTable = NULL;
    *pSymbolSize = 0;
    *pNumberOfSymbols = 0;
    *pFirstSymbolIndex = 0;
    
    mypMachHeader = pLibrary->pMachHeader;
    
    // could do more thorough check here
    if ((mypMachHeader->magic == MH_MAGIC) || (mypMachHeader->magic == MH_CIGAM))
    {
        machoheadersize = sizeof(struct mach_header);
        *pSymbolSize = sizeof(struct nlist);
    }
    else if ((mypMachHeader->magic == MH_MAGIC_64) || (mypMachHeader->magic == MH_CIGAM_64))
    {
        machoheadersize = sizeof(struct mach_header_64);
        *pSymbolSize = sizeof(struct nlist_64);
    }
    else
    {
        dg_pusherror(pBHarrayhead, (const char*)"unknown mach header size");
        dg_pusherror(pBHarrayhead, dg_getlibdysyminfo10_6_8name);
        return;
    }
    
    pCommand = (const struct load_command*)((unsigned char*)mypMachHeader + machoheadersize);
    
    for (i = 0; i < numberofcommands; i++)
    {
        switch (pCommand->cmd) {
			case LC_SYMTAB: // this might just be for the local symbols
				{
					pSymbolTableCommand = (struct symtab_command*)pCommand;
					*ppSymbolTableStrings = (const char*)(pLibrary->pLinkEditBase + pSymbolTableCommand->stroff);
					*ppSymbolTable = (const char*)(pLibrary->pLinkEditBase + pSymbolTableCommand->symoff);
                    *pStringTableSize = pSymbolTableCommand->strsize;
				}
				break;
			case LC_DYSYMTAB:
            {
				pDynSymbolCommand = (struct dysymtab_command*)pCommand;
				break;
            }
		}
        
        pCommand = (const struct load_command*)(((unsigned char*)pCommand)+pCommand->cmdsize);
    }
    
    if (
        (pSymbolTableCommand == NULL) ||
        (pDynSymbolCommand == NULL)
       )
    {
        return;
    }
    
    // source code shows actual count as nextdefsym - iextdefsym
    *pNumberOfSymbols = pDynSymbolCommand->nextdefsym;
    
    *pFirstSymbolIndex = pDynSymbolCommand->iextdefsym;
}
*/
/*
const char* dg_addsymbolname10_6_8name = "dg_addsymbolname10_6_8";

void dg_addsymbolname10_6_8 (
    Bufferhandle* pBHarrayhead,
    void* libraryhandle,
    UINT32 stringTableSize,
    const char* pStringTable,
    struct nlist_64* pSymbol,
    UINT32 mynewwordlist)
{
    
	void* mysymboladdr;
    unsigned char* psymbolnamestring;
    
    const char* pError;
    UINT32 n;
    UINT32 mywordtoken;
	
	unsigned char c;
    
    UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
        
    // make sure start of name is in the string table
    if (pSymbol->n_un.n_strx < stringTableSize)
    {
        // same for both 32 and 64 bit images
        psymbolnamestring = (unsigned char*)(pStringTable + pSymbol->n_un.n_strx);
			
        // skip leading _ if there is one, what if there is more than one underscore?
        //  is there a dlsym equivalent function which does not require stripping the underscore?
        //  I tested it against libdiaperglu.so and it seems you only remove 1 underscore even if the function
        //   has two
        pError = dg_getbyte(psymbolnamestring, &c);
			
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_getbytename);
            dg_pusherror(pBHarrayhead, dg_addsymbolname10_6_8name);
        }
			
        if ('_' == c)
        {
            psymbolnamestring++;
        }
                
        n = largestsignedint;
                
        pError = dg_scanforbyte (psymbolnamestring, &n, 0);
		
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_scanforbytename);
            dg_pusherror(pBHarrayhead, dg_addsymbolname10_6_8name);
            return;
        }
        
        if (  (n != 0) &&
              (n <= maxwordlength) ) // need way to import dylib words with name lengths > maxwordlength
        {
            // ok have valid pointer to name, all I have to do now is call dlsym and link it into current new word wordlist
            // in 32 bit mode, does dlsym always return a 32bit address?
            mysymboladdr = dlsym(libraryhandle, (const char*)psymbolnamestring);
            
            // dlsym returns 0 if something is wrong or it can't find the symbol
            if (0 == mysymboladdr)
            {
                // symbol was not found, not necessarily an error
                return;
            }
            
            // don't need to copy name... but this routine copies name anyways now
            mywordtoken = dg_new0stringcorenameword (
                pBHarrayhead, 
                DG_CORE_BUFFERID, 
                (UINT32)&dg_forthdocompiletypecdecl,
                DG_CORE_BUFFERID,
                (UINT32)mysymboladdr,
                psymbolnamestring);
				
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_addsymbolname10_6_8name);
                return;
            }
			
            dg_linkdefinition (
                pBHarrayhead,
                mynewwordlist,
                mywordtoken);
			
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_addsymbolname10_6_8name);
                return;
            }
        }
    }
    else
    {
        // index was off end, could push an error here.. but... would rather have
        // diaperglu load what it can and ignore errors in dylibs as much as possible
    }			
}
*/

/*
const char* dg_loadlibsymbols10_6_8name = "dg_loadlibsymbols10_6_8";

void dg_loadlibsymbols10_6_8 (
    Bufferhandle* pBHarrayhead,
    void* libraryhandle,
    UINT32 usedsublibhandlebufferid,
    UINT32 mynewwordlist)
{
    UINT32 firstSymbolIndex;
    UINT32 numberOfSymbols;
    UINT32 symbolSize;
    UINT32 stringTableSize;
    const char* pSymbolTable;
    const char* pSymbolTableStrings;
    
    UINT32 symbolIndex;
    
    unsigned char* pSymbol;
    
    //struct nlist_64 mysymbol;
    
    UINT32 i;
    
    const char* pError;
    
    unsigned char* pBuffer;
    UINT32* pBufferLength;
    UINT32 scanLength;
    
    dg_macosx10_6_8_dylibhandle* pLibrary;
    void* sublibraryhandle;
    
    UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pLibrary = (dg_macosx10_6_8_dylibhandle*)((UINT32)libraryhandle & (-4));
    
    pBuffer = dg_getpbuffer (
        pBHarrayhead,
        usedsublibhandlebufferid,
        &pBufferLength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_loadlibsymbols10_6_8name);
        return;
    }
    
    scanLength = *pBufferLength >> 2;
    
    pError = dg_scanforuint32 (
        (void*)pBuffer,
        &scanLength,
        (UINT32)pLibrary);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_scanforuint32name);
        dg_pusherror(pBHarrayhead, dg_loadlibsymbols10_6_8name);
        return;
    }
    
    if (scanLength != (UINT32)-1)
    {
        // sub library already loaded - not an error
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        usedsublibhandlebufferid,
        (UINT32)pLibrary);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_loadlibsymbols10_6_8name);
        return;
    }
    
    dg_getlibdysyminfo10_6_8 (
        pBHarrayhead,
        pLibrary,
        &firstSymbolIndex,
        &numberOfSymbols,
        &symbolSize,
        &stringTableSize,
        &pSymbolTable,
        &pSymbolTableStrings);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_loadlibsymbols10_6_8name);
        return;
    }
    
    if (i != 0)
    {
        for (i = 0; i < numberOfSymbols; i++)
        {
            // index and copy symbol
            symbolIndex = firstSymbolIndex + i;
    
            pSymbol = (unsigned char*)(pSymbolTable + (symbolIndex*symbolSize));
    
            // copy not needed because nlist and nlist_64 are identical
            // for the structure elements the subroutine accesses
              // could just set nlist_64->n to 0 instead
            */

            /*
            pError = dg_fillwithbyte (
                (unsigned char*)&mysymbol,
                sizeof(nlist_64),
                0);
        
            if (pError != dg_success)
            {
                dg_pusherror(pBHarrayhead, pError);
                dg_pusherror(pBHarrayhead, dg_fillwithbytename);
                dg_pusherror(pBHarrayhead, dg_loadlibsymbols10_6_8name);
                return;
            }

            pError = dg_movebytes(
                pSymbol,
                (unsigned char*)&mysymbol,
                symbolSize);
        
            if (pError != dg_success)
            {
                dg_pusherror(pBHarrayhead, pError);
                dg_pusherror(pBHarrayhead, dg_movebytesname);
                dg_pusherror(pBHarrayhead, dg_loadlibsymbols10_6_8name);
                return;
            }
            */

/*
            dg_addsymbolname10_6_8 (
                pBHarrayhead,
                libraryhandle,
                stringTableSize,
                pSymbolTableStrings,
                (struct nlist_64*)pSymbol, // might be a lie but should be ok
                mynewwordlist);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_loadlibsymbols10_6_8name);
                return;
            }
        }
    }
    
    
    if (pLibrary->fLibraryCount != 0)
    {
        for (i = 0; i < pLibrary->fLibraryCount ; i++)
        {
            sublibraryhandle = (void*)pLibrary->pFunctions[62]((UINT32)pLibrary, i);
            
            if (((UINT32)sublibraryhandle & 1) != 0) // this is library not reexported flag
            {
                //dg_printzerostring(pBHarrayhead, (unsigned char*)"  sublibrary not reexported found\n\n");
            }
            else
            {
                dg_loadlibsymbols10_6_8 (
                    pBHarrayhead,
                    sublibraryhandle,
                    usedsublibhandlebufferid,
                    mynewwordlist);
                    
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_loadlibsymbols10_6_8name);
                    return;
                }
            }
        }
    }
}
*/

/*
const char* dg_showsymbolname10_6_8name = "dg_showsymbolname10_6_8";

void dg_showsymbolname10_6_8 (
    Bufferhandle* pBHarrayhead,
    void* libraryhandle,
    UINT32 stringTableSize,
    const char* pStringTable,
    struct nlist_64* pSymbol)
{
    void* mysymboladdr;
    unsigned char* psymbolnamestring;
    
    const char* pError;
    UINT32 n;
	
	unsigned char c;
        
    // make sure start of name is in the string table
    if (pSymbol->n_un.n_strx < stringTableSize)
    {
        // same for both 32 and 64 bit images
        psymbolnamestring = (unsigned char*)(pStringTable + pSymbol->n_un.n_strx);
			
        // skip leading _ if there is one, what if there is more than one underscore?
        //  is there a dlsym equivalent function which does not require stripping the underscore?
        //  I tested it against libdiaperglu.so and it seems you only remove 1 underscore even if the function
        //   has two
        pError = dg_getbyte(psymbolnamestring, &c);
			
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_getbytename);
            dg_pusherror(pBHarrayhead, dg_showsymbolname10_6_8name);
        }
			
        if ('_' == c)
        {
            psymbolnamestring++;
        }
                
        n = largestsignedint;
                
        pError = dg_scanforbyte (psymbolnamestring, &n, 0);
		
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, pError);
            dg_pusherror(pBHarrayhead, dg_scanforbytename);
            dg_pusherror(pBHarrayhead, dg_showsymbolname10_6_8name);
            return;
        }
        
            // this algorithm is from mac os x command nm,
            //  code has section where this is used for the exports
        if (
              // ((pSymbol->n_type & N_EXT) != 0) && // doesn't look like this is used
              //((pSymbol->n_type & N_TYPE) != N_UNDF) &&
              // ((pSymbol->n_type & N_TYPE) != N_PBUD) && // doesn't look like this is used
              (n != 0) &&
              (n <= maxwordlength) ) // need way to import dylib words with name lengths > maxwordlength
        {
            // ok have valid pointer to name, all I have to do now is call dlsym and link it into current new word wordlist
            // in 32 bit mode, does dlsym always return a 32bit address?
            mysymboladdr = dlsym(libraryhandle, (const char*)psymbolnamestring);
            
            // dlsym returns 0 if something is wrong or it can't find the symbol
            if (0 == mysymboladdr)
            {
                dg_printzerostring(pBHarrayhead, (unsigned char*)"    (not found)  ");
                dg_printzerostring(pBHarrayhead, (unsigned char*)psymbolnamestring);
                dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
                return;
            }
            
            dg_printzerostring(pBHarrayhead, (unsigned char*)"    ");
            dg_writestdoutuint32tohex(pBHarrayhead, (UINT32)mysymboladdr);
            dg_printzerostring(pBHarrayhead, (unsigned char*)"  ");
            dg_printzerostring(pBHarrayhead, (unsigned char*)psymbolnamestring);
            dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
        }
    }
    else
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"    (index off end)  ");
        dg_printzerostring(pBHarrayhead, (unsigned char*)psymbolnamestring);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    }
}


const char* dg_showlibsymbols10_6_8name = "dg_showlibsymbols10_6_8";

void dg_showlibsymbols10_6_8 (
    Bufferhandle* pBHarrayhead,
    void* libraryhandle,
    UINT32 usedsublibhandlebufferid)
{
    UINT32 firstSymbolIndex;
    UINT32 numberOfSymbols;
    UINT32 symbolSize;
    UINT32 stringTableSize;
    const char* pSymbolTable;
    const char* pSymbolTableStrings;
    
    UINT32 symbolIndex;
    
    unsigned char* pSymbol;
    
    //struct nlist_64 mysymbol;
    
    UINT32 i;
    
    const char* pError;
    
    unsigned char* pBuffer;
    UINT32* pBufferLength;
    UINT32 scanLength;
    
    dg_macosx10_6_8_dylibhandle* pLibrary;
    void* sublibraryhandle;
    
    const char* pPath;
    
    UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pLibrary = (dg_macosx10_6_8_dylibhandle*)((UINT32)libraryhandle & (-4));
    
    pBuffer = dg_getpbuffer (
        pBHarrayhead,
        usedsublibhandlebufferid,
        &pBufferLength);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_showlibsymbols10_6_8name);
        return;
    }
    
    scanLength = *pBufferLength >> 2;
    
    pError = dg_scanforuint32 (
        (void*)pBuffer,
        &scanLength,
        (UINT32)pLibrary);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_scanforuint32name);
        dg_pusherror(pBHarrayhead, dg_showlibsymbols10_6_8name);
        return;
    }
    
    if (scanLength != (UINT32)-1)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n  library with image address = ");
        dg_writestdoutuint32tohex(pBHarrayhead, (UINT32)pLibrary);
        dg_printzerostring(pBHarrayhead, (unsigned char*)" already shown\n");
        return;
    }
    
    dg_pushbufferuint64(
        pBHarrayhead,
        usedsublibhandlebufferid,
        (UINT32)pLibrary);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_showlibsymbols10_6_8name);
        return;
    }
    
    dg_getlibdysyminfo10_6_8 (
        pBHarrayhead,
        pLibrary,
        &firstSymbolIndex,
        &numberOfSymbols,
        &symbolSize,
        &stringTableSize,
        &pSymbolTable,
        &pSymbolTableStrings);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_showlibsymbols10_6_8name);
        return;
    }
    
    pPath = pLibrary->pPath;

    
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n\nlibrary:\n\n  path = ");
    dg_printzerostring(pBHarrayhead, (unsigned char*)pPath);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    
    dg_printzerostring(pBHarrayhead, (unsigned char*)"  library handle with flags = ");
    dg_writestdoutuint32tohex(pBHarrayhead, (UINT32)libraryhandle);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    
    dg_printzerostring(pBHarrayhead, (unsigned char*)"  library image address = ");
    dg_writestdoutuint32tohex(pBHarrayhead, (UINT32)pLibrary);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");
    
    dg_printzerostring(pBHarrayhead, (unsigned char*)"  number of symbols = ");
    dg_writestdoutuint32tohex(pBHarrayhead, (UINT32)numberOfSymbols);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n\n");
    
    if (i != 0)
    {
        for (i = 0; i < numberOfSymbols; i++)
        {
            // index and copy symbol
            symbolIndex = firstSymbolIndex + i;
    
            pSymbol = (unsigned char*)(pSymbolTable + (symbolIndex*symbolSize));
            
            // copy not needed because nlist and nlist_64 are identical for the
            //   structure elements the subroutine actually accesses
            */

            /*
              // could just set nlist_64->n to 0 instead
            pError = dg_fillwithbyte (
                (unsigned char*)&mysymbol,
                sizeof(nlist_64),
                0);
        
            if (pError != dg_success)
            {
                dg_pusherror(pBHarrayhead, pError);
                dg_pusherror(pBHarrayhead, dg_fillwithbytename);
                dg_pusherror(pBHarrayhead, dg_showlibsymbols10_6_8name);
                return;
            }

            pError = dg_movebytes(
                pSymbol,
                (unsigned char*)&mysymbol,
                symbolSize);
        
            if (pError != dg_success)
            {
                dg_pusherror(pBHarrayhead, pError);
                dg_pusherror(pBHarrayhead, dg_movebytesname);
                dg_pusherror(pBHarrayhead, dg_showlibsymbols10_6_8name);
                return;
            }
            */

/*
            dg_showsymbolname10_6_8 (
                pBHarrayhead,
                libraryhandle,
                stringTableSize,
                pSymbolTableStrings,
                (struct nlist_64*)pSymbol); // cast could be a lie, but should be ok
                
            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_showlibsymbols10_6_8name);
                return;
            }
        }
    }
    
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n  number of sublibraries = ");
    dg_writestdoutuint32tohex(pBHarrayhead, (UINT32)pLibrary->fLibraryCount);
    dg_printzerostring(pBHarrayhead, (unsigned char*)"\n\n");
    
    if (pLibrary->fLibraryCount != 0)
    {
        for (i = 0; i < pLibrary->fLibraryCount ; i++)
        {
            sublibraryhandle = (void*)pLibrary->pFunctions[62]((UINT32)pLibrary, i);
            
            if (((UINT32)sublibraryhandle & 1) != 0) // this is library not reexported flag
            {
                dg_printzerostring(pBHarrayhead, (unsigned char*)"  sublibrary not reexported found\n\n");
            }
            else
            {
                dg_showlibsymbols10_6_8 (
                    pBHarrayhead,
                    sublibraryhandle,
                    usedsublibhandlebufferid);
                    
                if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
                {
                    dg_pusherror(pBHarrayhead, dg_showlibsymbols10_6_8name);
                    return;
                }
            }
        }
    }
}
*/

/*
void dg_forthshowopenlibrary (Bufferhandle* pBHarrayhead)
//			( openlibraryhandle -- )
{
    void* libraryhandle;
    UINT32* plibrary;
    UINT32 sublibhandlebufferid;
    const char* pError;
    
    
	UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}
    
    
    libraryhandle = (void*)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
		return;
	}
    
	if (-1 == (UINT32)libraryhandle)
	{
		// maybe push could not find image error?
		dg_pusherror(pBHarrayhead, (const char*)"library handle is for the not found case");
		dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
		return;
	}

    
    sublibhandlebufferid = dg_newbuffer(
        pBHarrayhead,
        0x1000, // growby,
        largestsignedint, // maxsize,
        &pError, // const char** pError,
        FORTH_FALSE); // forceoutofmemory) )
        
    if (pError != dg_success)
	{
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
		dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
		return;
	}
    
    
    dg_showlibsymbols10_6_8 (
        pBHarrayhead,
        libraryhandle,
        sublibhandlebufferid);
        
    // free buffer no matter what
    dg_freebuffer(pBHarrayhead, sublibhandlebufferid);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
		return;
	}
}
*/




void dg_forthopenlibrarystring (Bufferhandle* pBHarrayhead)
//                      ( filename$ -$- )
//			( -- wordlistid libraryhandle )
{
    void* libraryhandle;
    UINT64 mynewwordlist;
    
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	dg_forthloadlibrarystringsub(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
		return;
	}
    
    libraryhandle = (void*)dg_popbufferuint64(
        pBHarrayhead,
        DG_LIBHANDLE_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
		return;
	}
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_LIBHANDLE_BUFFERID,
        (UINT64)libraryhandle);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
		return;
	}
    
	if (-1 == (UINT64)libraryhandle)
	{
		// maybe push could not find image error?
		dg_pusherror(pBHarrayhead, (const char*)"object handle of last thing dlopened not found");
		dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
		return;
	}
    
    // make a new wordlist
	mynewwordlist = dg_newwordlist (
        pBHarrayhead,
        0);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
		return;
	}
	
	dg_pushdatastack(
        pBHarrayhead,
        mynewwordlist);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
		return;
	}
    
    dg_pushdatastack(
        pBHarrayhead,
        (UINT64)libraryhandle);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthopenlibrarystringname);
		return;
	}

}

/*
void dg_forthloadlibrarystring (Bufferhandle* pBHarrayhead)
//     ( filename$ -$- )
//     ( -- wordlistid )
{
    void* libraryhandle;
    UINT64 mynewwordlist;
    UINT64 sublibhandlebufferid;
    const char* pError;
    
	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	dg_forthloadlibrarystringsub(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
		return;
	}
    
    libraryhandle = (void*)dg_popbufferuint64(
        pBHarrayhead,
        DG_LIBHANDLE_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
		return;
	}
    
    dg_pushbufferuint64(
        pBHarrayhead,
        DG_LIBHANDLE_BUFFERID,
        (UINT64)libraryhandle);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
		return;
	}
    	
	if (-1 == (UINT64)libraryhandle)
	{
		// maybe push could not find image error?
		dg_pusherror(pBHarrayhead, (const char*)"object handle of last thing dlopened not found");
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
		return;
	}
    
    // make a new wordlist
	mynewwordlist = dg_newwordlist(
        pBHarrayhead,
        0);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
		return;
	}
	
	dg_pushdatastack(
        pBHarrayhead,
        mynewwordlist);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
		return;
	}
	
	//dg_forthloadmachosymbols (pBHarrayhead,
    //    mynewwordlist,
    //    libraryhandle,
    //    libraryhandle);
    
    sublibhandlebufferid = dg_newbuffer(
        pBHarrayhead,
        0x1000, // growby,
        largestsignedint, // maxsize,
        &pError, // const char** pError,
        FORTH_FALSE); // forceoutofmemory) )
        
    if (pError != dg_success)
	{
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
		dg_pusherror(pBHarrayhead, dg_forthshowopenlibraryname);
		return;
	}
    
    dg_loadlibsymbols10_6_8(
        pBHarrayhead,
        libraryhandle,
        sublibhandlebufferid,
        mynewwordlist);
	
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringname);
		return;
	}
}
*/

/*
void dg_forthshowlibrarystring (Bufferhandle* pBHarrayhead)
//                      ( filename$ -$- )
{
    void* libraryhandle;
    UINT32 mynewwordlist;
    const char* pError;
    
	UINT32 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}

	dg_forthloadlibrarystringsub(pBHarrayhead);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthshowlibrarystringname);
		return;
	}
    
    libraryhandle = (void*)dg_popbufferuint64(pBHarrayhead, DG_LIBHANDLE_BUFFERID);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthshowlibrarystringname);
		return;
	}
    
    if (-1 == (UINT32)libraryhandle)
	{
		// maybe push could not find image error?
		dg_pusherror(pBHarrayhead, (const char*)"object handle of last thing dlopened not found");
		dg_pusherror(pBHarrayhead, dg_forthshowlibrarystringname);
		return;
	}
    
    dg_pushdatastack(pBHarrayhead, (UINT32)libraryhandle);
    	
    dg_forthshowopenlibrary(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthshowlibrarystringname);
		return;
	}
    
    pError = dg_freelibrary(
        (UINT32)libraryhandle,
        dg_success);
        
    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_freelibraryname);
        dg_pusherror(pBHarrayhead, dg_forthshowlibrarystringname);
    }
}
*/

const char* dg_dlsymname = "dg_dlsym";

const char* dg_dlsym(
    void* libraryhandle,
    const char* pnamelstring,
    void** psymboladdress,
    const char* pforcerror)
{
    int myerrno;
    
    const char* perror;
    
    if (pforcerror != dg_success)
    {
        return(perror);
    }
    
    perror = dg_putuint64(
        (UINT64*)psymboladdress,
        (UINT64)-1);

    if (perror != dg_success)
    {
        return (perror);
    }
    
    *psymboladdress = dlsym(
        libraryhandle,
        pnamelstring);
    
    if (*psymboladdress == 0)
    {
        myerrno = errno;

        /*
        if (EBADF == myerrno)
        {
            // not a handle to an open file
            return (dg_invalidhandleerror);
        }

        if (EIO == myerrno)
        {
            //I/O error during close
            return (dg_oserror);
        }
        */
        
        return(dg_symbolnotfounderror);
    }
    
    return(dg_success);
}


// symbol lookup needs to append null to string
//  that's why this function uses the string and data stacks
void dg_forthfindlibrarysymbol (Bufferhandle* pBHarrayhead)
// ( symbolname$ -$- )
// ( openlibraryhandle -- symboladdress )
{
    void* libraryhandle;
    UINT64 numberofstringsonstack;
    unsigned char* pnamelstring;
    UINT64 namelength;
    void* mysymboladdr;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

	if (baderrorcount == olderrorcount)
	{
		return;
	}
    
    libraryhandle = (void*)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
		return;
	}
    
    numberofstringsonstack = dg_getnumberoflstringsonstack(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthloadlibrarystringsubname);
		return;
	}
    
    dg_forthturnstringinto0string(pBHarrayhead);

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

	pnamelstring = dg_getplstring(
        pBHarrayhead,
		DG_STRINGOFFSETSTACK_BUFFERID,
		DG_STRINGSTRINGSTACK_BUFFERID,
		numberofstringsonstack - 1,
		&namelength);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthfindlibrarysymbolname);
		return;
	}
    
    mysymboladdr = dlsym(
        libraryhandle,
        (const char*)pnamelstring);
    
    dg_pushdatastack(pBHarrayhead, (UINT64)mysymboladdr);
    
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


const char* dg_callbuffername = "dg_callbuffer";

UINT64 dg_callbuffer (
	Bufferhandle* pBHarrayhead,
	UINT64 bufferid,
	UINT64 offset)
{
	unsigned char* addr;
    UINT64 result = (UINT64)-1;   

	UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
	
	if (baderrorcount == olderrorcount)
	{
		return(result);
	}
	
	addr = dg_getpbufferoffset(
        pBHarrayhead,
        bufferid,
        offset);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_callbuffername);
		return(result);
	}
    
    result = dg_callcoreforthroutine(
        pBHarrayhead,
        (UINT64)addr);
        
    return(result); // making this function return a value for testing purposes
}


void dg_forthcallprocaddress (Bufferhandle* pBHarrayhead)
//     ( paramn paramn-1 paramn-2 ... param1 n procaddress -- returnvalue )
{
	UINT64* address;
	UINT64 n;

	UINT64* plength;
	unsigned char* pbuffer;

	UINT64* pints;

	UINT64 returnvalue;

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
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
		return;
	}

	if (*plength < (2 * sizeof (UINT64)))
	{
		dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
		return;
	}

	n = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
	address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

	if (((*plength) / sizeof(UINT64)) < (n + 2) ) // pretty sure overflow indexing is caught by this
	{
		dg_pusherror(pBHarrayhead, dg_procparamsmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
		return;
	}

	pints = (UINT64*)(pbuffer + *plength - (( n + 2) * sizeof(UINT64)));

	returnvalue = (UINT64)(dg_callprocaddress(
        pints,
        n,
        plength,
        address));

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		return;
	}

    dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        returnvalue);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressname);
		return;
	}
}

void dg_forthcallprocaddressretuint128 (Bufferhandle* pBHarrayhead)
//     ( paramn paramn-1 paramn-2 ... param1 n procaddress -- returnvaluelo returnvaluehi )
{
	UINT64* address;
	UINT64 n;

	UINT64* plength;
	unsigned char* pbuffer;

	UINT64* pints;

	UINT64 returnvaluelo;
    UINT64 returnvaluehi;   

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
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
		return;
	}

	if (*plength < (2 * sizeof(UINT64)))
	{
		dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
		return;
	}

	n = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
	address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

	if (((*plength) / sizeof(UINT64)) < (n + 2) ) // pretty sure overflow indexing is caught by this
	{
		dg_pusherror(pBHarrayhead, dg_procparamsmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
		return;
	}

	pints = (UINT64*)(pbuffer + *plength - ((n + 2) * sizeof(UINT64)));
    
    returnvaluelo = dg_callprocaddressretuint128(
        pints,
        n,
        plength,
        address,
        &returnvaluehi);

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        returnvaluelo);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
		return;
	}

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        returnvaluehi);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcallprocaddressretuint128name);
		return;
	}
}

void dg_forthcalldfpprocaddress (Bufferhandle* pBHarrayhead)
//     ( dfparamn dfparamn-1 ... dfparam1
//       paramn paramn-1 paramn-2 ... param1
//       nfloats n procaddress -- dfpreturnvalue )
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

	if (*plength < (3 * sizeof (UINT64)))
	{
		dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcalldfpprocname);
		return;
	}

	nfloats = *((UINT64*)(pbuffer + *plength - (3 * sizeof(UINT64))));
    n = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
	address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

	if (((*plength) / sizeof(UINT64)) < (n + nfloats + 3) ) // pretty sure overflow indexing is caught by this
	{
		dg_pusherror(pBHarrayhead, dg_dfpprocparamsmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcalldfpprocname);
		return;
	}

	pints = (UINT64*)(pbuffer + *plength - (( n + nfloats + 3) * sizeof(UINT64)));

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
	UINT64* address;
	UINT64 n;

	UINT64* plength;
	unsigned char* pbuffer;

	UINT64* pints;

	UINT64 returnvalue;

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
		dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
		return;
	}

	if (*plength < (2 * sizeof(UINT64)))
	{
		dg_pusherror(pBHarrayhead, dg_datastacknoraddrmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
		return;
	}

	n = *((UINT64*)(pbuffer + *plength - (2 * sizeof(UINT64))));
	address = *((UINT64**)(pbuffer + *plength - (sizeof(UINT64))));

	if (((*plength) / sizeof(UINT64)) < n+2 ) // pretty sure overflow indexing is caught by this
	{
		dg_pusherror(pBHarrayhead, dg_procparamsmissingerror);
		dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
		return;
	}

	pints = (UINT64*)(pbuffer + *plength - (n+2)*sizeof(UINT64));

	returnvalue = (UINT64)(dg_callcppmemberwin32(
        pints,
        n,
        plength,
        address));
    
	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		return;
	}

	dg_pushbufferuint64(
        pBHarrayhead,
        DG_DATASTACK_BUFFERID,
        returnvalue);

	if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
	{
		dg_pusherror(pBHarrayhead, dg_forthdatastackbufferidname);
		dg_pusherror(pBHarrayhead, dg_forthcallcppmemberfunctionname);
		return;
	}
}


*/

// 33 virtual uint32_t					getExportedSymbolCount() const = 0;
			
										// gets the i'th exported symbol
// 34	virtual const Symbol*				getIndexedExportedSymbol(uint32_t index) const = 0;

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


UINT64 dg_isdelimiter (char c)
{
	if (c == ' ')  { return(FORTH_TRUE); } // space
	if (c == '\n') { return(FORTH_TRUE); } // line feed
	if (c == '\t') { return(FORTH_TRUE); } // tab
	if (c == '\v') { return(FORTH_TRUE); } // vertical tab I think
	if (c == '\b') { return(FORTH_TRUE); } // shouldn't see this one
	if (c == '\r') { return(FORTH_TRUE); } // carriage return
	if (c == '\f') { return(FORTH_TRUE); } // form feed I think

	return(FORTH_FALSE);
}


UINT64 dg_islineterminator (char c)
{
	if (c == '\n') { return(FORTH_TRUE); } // line feed
	if (c == '\v') { return(FORTH_TRUE); } // vertical tab I think
	if (c == '\b') { return(FORTH_TRUE); } // shouldn't see this one
	if (c == '\r') { return(FORTH_TRUE); } // carriage return
	if (c == '\f') { return(FORTH_TRUE); } // form feed I think

	return(FORTH_FALSE);
}


unsigned char dg_digittochar (UINT64 d)
{
	if (d > 35)
	{ 
		return('!');
	}
	
	if (d<10)
	{
		return ((unsigned char)d + 0x30);
	}
	
	return ((unsigned char)d - 10 + 'A');
}

UINT64 dg_chartodigit (unsigned char c)
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


UINT64 dg_chartodigitlowertoo (unsigned char c)
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


UINT64 dg_pchartonumber (
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
            if (number <= (largestunsignedint/base))
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

/*
 if ((c == 'e') ||
     (c == 'E') ||
     (c == 'd') ||
     (c == 'D'))
 {
   i++;
   
   // doing exponent
   if (negative != FORTH_FALSE)
   {
       number *= -1;
   }
   
   negative = FORTH_FALSE;
   
   if (length <= i) // this means no explicit exponent which is ok... so it's 0 - number after period
   {
       *flag = FORTH_TRUE;
       return(number);
   }
   
   if (pnumber[i] == '-')
   {
       negative = FORTH_TRUE;
       i++;
   }
   
   if (pnumber[i] == '+')
   {
       i++;
   }
   
   while (i < length)
   {
       c = pnumber[i];
       
       digit = dg_chartodigit(c);

       if (digit >= base)
       {
           *flag = FORTH_FALSE;
           break;
       }

       if (digit != 0xffffffffffffffff)
       {
           *pexponent *= base;
           *pexponent += digit;
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
     *pexponent *= -1;
   }

   *pexponent -= digitsafterperiod;
   return (number);
   
   
   break;
 }
*/

// for FORTH floating point conversion
INT64 dg_pchartonumberskipperiod (
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
                if (number <= (largestsignedint/base))
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


INT64 dg_pchartobase10numberandexponent (
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
    number = dg_pchartonumberskipperiod (
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
        *pexponent = dg_pchartonumber (
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

    if ( (*pexponent) >= ((INT64)largestnegativeint + (INT64)digitsafterperiod) )
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
        result = 1/(dg_tentothex(0-exponent));
    }
    else
    {
        result = dg_tentothex(exponent);
    }
    
    // not sure what happens if there is overflow/underflow...
    result = dg_i64tof64(number) * result;
    
    return(result);
}

FLOAT64 dg_pchartof64 (
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
        if ( !(dg_isdelimiter(pnumber[i])) )
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
    
    
    number = dg_pchartobase10numberandexponent (
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


UINT64 dg_hexdectonumber (
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
    while(end > 0)
    {
        if (dg_isdelimiter(pnumber[end-1]))
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
    while(start < end)
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
    if(start < end)
    {
        if ('+' == pnumber[start])
        {
            start++;
        }
    }
    
    length2 = (end-start);
    
    // only checking for hex 0x or 0X specifier
    // not checking for octal leading 0 specifier because
    //  it is deprecated in html standard Dec 21, 2016
    if (length2 >= 2)
    {
        if ((pnumber[start] == '0')
            && ((pnumber[start+1] == 'x') || (pnumber[start+1] == 'X')))
        {
            length2 = length2 - 2;
            start = start + 2;
            base = 16;
        }
    }

    return(dg_pchartonumber (
        pnumber+start,
        length2,
        base, // base,
        pflag));
}


// since I'm going to call this repeatedly... ideally I'd check the memory only once
//  when I start... so this routine probably shouldnt' check memory...
const char* dg_getnextwordoffsetsname = "dg_getnextwordoffsets";

const char* dg_getnextwordoffsets (
    unsigned char* pstring,
    UINT64 stringlength,
    UINT64 startoffset,
    UINT64* pwordbeginoffset,
    UINT64* pwordendoffset)
{
    // const char* perror = dg_success;
    
    UINT64 currentoffset = startoffset;
    
    /*
    perror = dg_readallbytes(pstring, stringlength); // checking memory at perror
    
    if (perror != dg_success)
    {
        return (perror);
    }
    */
    
    // need to check memory in string....
    //  unless I assume this will always be on the string stack...
    //  and trust the string stack memory....

    //get off delimiters
    while(currentoffset < stringlength)
    {
        if (dg_isdelimiter(pstring[currentoffset]))
        {
            currentoffset++;
        }
        else
        {
            break;
        }
    }

    //perror = dg_putuint64(pwordbeginoffset, currentoffset);
    *pwordbeginoffset = currentoffset;
    
    /*
    if (perror != dg_success)
    {
        return (perror);
    }
    */

    // get on delimiter
    while(currentoffset < stringlength)
    {
        if (dg_isdelimiter(pstring[currentoffset]))
        {
            break;
        }
        else
        {
            currentoffset++;
        }
    }
    
    //perror = dg_putuint64(pwordendoffset, currentoffset);
    *pwordendoffset = currentoffset;
    
    /*
    if (perror != dg_success)
    {
        return (perror);
    }
    */
    
    return(dg_success);
}



const char* dg_writestdoutname = "dg_writestdout";

const char* dg_writestdout(
    Bufferhandle* pBHarrayhead,
    UINT8* pbuf,
    UINT64 length)
{
	UINT64 fileid;
	const char*  pError;

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
    UINT64 n=0;

    if (0==i)
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
        buf[19-n] = (unsigned char)(r + 0x30);
        n++;
    }

    // need blocking writestdout, or writestdout does copy
    dg_writefile(
        pBHarrayhead,
        fileid, 
        &(buf[20-n]), 
        n, 
        dg_success);
}

void dg_writestdoutuinttodec(
    Bufferhandle* pBHarrayhead,
    UINT64 i)
{
    unsigned char buf[64];
    UINT64 r;
    UINT64 n=0;

    if (0==i)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"0");
        return;
    }

    while (i > 0)
    {
        r = i % 10;
        i = i / 10;
        buf[19-n] = (unsigned char)(r + 0x30);
        n++;
    }

    // need blocking writestdout, or writestdout does copy
    dg_writestdout(pBHarrayhead, &(buf[20-n]), n);
}


void dg_writestdoutuint64tohex(
	Bufferhandle* pBHarrayhead,
	UINT64 i)
{
    unsigned char buf[64];
    UINT64 r;
    UINT64 n=0;
	
    if (0==i)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"0x00000000");
        return;
    }
	
    while (i > 0)
    {
        r = i % 0x10;
        i = i / 0x10;
        buf[19-n] = dg_digittochar(r);
        n++;
    }
	
	dg_writestdout(pBHarrayhead, (unsigned char*)"0x", 2);
	
	while (n<16) // may want to add a leading zero any time n is odd
	{
		buf[19-n] = '0';
		n++;
	}
	
    // need blocking writestdout, or writestdout does copy
    dg_writestdout(pBHarrayhead, &(buf[20-n]), n);
}

void dg_writestdoutuint8tohex(
    Bufferhandle* pBHarrayhead,
    UINT8 i)
{
    UINT8 buf[4];
    
    buf[0] = '0';
    buf[1] = 'x';
	
    if (0==i)
    {
        dg_printzerostring(pBHarrayhead, (unsigned char*)"0x00");
        return;
    }

    buf[3] = dg_digittochar(i & 0x0F);
    buf[2] = dg_digittochar(i / 0x10);
	
    // need blocking writestdout, or writestdout does copy
    dg_writestdout(pBHarrayhead, &buf[0], 4);
}

void dg_hexdumpsegment (
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

UINT64 dg_isnegative (UINT64 x)  // could call this dg_zeroless
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
        startoffset = n+1;
    }

    if (startoffset <= endoffset)
    {
        // don't see how it couldn't be
        *pfirstvaluelength = (endoffset - startoffset);
        *pfirstvaluestartoffset = startoffset;
    }

    return (dg_success);
}
/*
// gonna assume these buffers are ok since they came from dg_getpbuffer just after init
 // user didn't have a chance to mess them up yet
 // (the value after slash should be diaperglu, diaperglu.exe, diaperglu.dll or scriptfilename.dglu)
UINT64 dg_checkformatchafterslash(
    unsigned char* pbufa,
    UINT64 bufalength,
    unsigned char* pbufb,
    UINT64 bufblength)
{
    UINT64 i, j;

    i = bufalength;
    j = bufblength;

    if ((0 == i) || (0 == j))
    {
        // empty strings are NOT matches
        // need the file names to match and for that there have to be files
        return (FORTH_FALSE);
    }

    // skipping null terminators
    if (0 == pbufa[i-1])
    {
        i--;
    }

    if (0 == pbufb[j-1])
    {
        j--;
    }

    if ((0 == i) || (0 == j))
    {
        // empty strings are NOT matches
        // need the file names to match and for that there have to be files
        return (FORTH_FALSE);
    }

    if (('/' == pbufa[i-1]) || ('\\' == pbufa[i-1]))
    {
        i--;
    }

    if (('/' == pbufb[j-1]) || ('\\' == pbufb[j-1]))
    {
        j--;
    }

    if ((0 == i) || (0 == j))
    {
        // empty strings are NOT matches
        // need the file names to match and for that there have to be files
        return (FORTH_FALSE);
    }

    while (true)
    {
        if ((0 == i) || (j == 0))
        {
            // one of the strings did not have a slash
            // in order to match, both i and j must be 0
            // or the one that is not 0 must have slash as next character
            if ((0 == i) && (0 == j))
            {
                return (FORTH_TRUE);
            }
            
            if (0 == i)
            {
                if (('/' == pbufb[j-1]) || ('\\' == pbufb[j-1]))
                {
                    return (FORTH_TRUE);
                }
                else
                {
                    return (FORTH_FALSE);
                }
            }

            // then j is 0

            if (('/' == pbufa[i-1]) || ('\\' == pbufa[i-1]))
            {
                return (FORTH_TRUE);
            }

            return (FORTH_FALSE);
        }

        // if one is a slash, the other must be a slash
        // otherwise they must match
        if (('/' == pbufa[i-1]) || ('\\' == pbufa[i-1]))
        {
            if (('/' == pbufb[j-1]) || ('\\' == pbufb[j-1]))
            {
                return (FORTH_TRUE);
            }
            else
            {
                return (FORTH_FALSE);
            }
        }

        if (pbufa[i-1] != pbufb[j-1])
        {
            return (FORTH_FALSE);
        }

        i--;
        j--;
    }
}
*/
/*
// did it this way for two reasons
//  1) its difficult to predict when an overflow will occur using IDIV
//  2) less assembly language routines makes it easier to port
void dg_smslashrem (UINT64* pints)
//     pints points to a UINT64 array of 3 entries
//     notation: ( pints_array_in -- pints_array_out )
//     ( numeratorlo numeratorhi denominator -- remainder quotient denominator )
{
    UINT64 quotientsign = 0;
    UINT64 remaindersign = 0;
    
    // see if numerator is negative
    if ( ((INT64)(pints[1])) < 0  )
    {
        quotientsign = ~quotientsign;
        
        //remainder gets same sign as numerator
        remaindersign = ~remaindersign;
        // get absolute value of numerator
        *((INT128*)pints) = -(*((INT128*)pints));
    }
    
    // check for divide by 0 error
    if (0 == pints[2])
    {
        if (0 == quotientsign)
        {
            // return max positive value
            pints[0] = 0x7FFFFFFFFFFFFFFF;
            pints[1] = 0x7FFFFFFFFFFFFFFF;
        }
        else
        {
            // return max negative value 
            pints[0] = 0x8000000000000000;
            pints[1] = 0x8000000000000000;
        }
        return;
    }
    
    // see if denominator is negative
    if (((INT64)(pints[2])) < 0)
    {
        quotientsign = ~quotientsign;
        // get absolute value of denominator
        pints[2] = (UINT64)(-((INT64)(pints[2])));
    }
    
    // do divide
    dg_umslashmod(pints);
    
    // see if remainder is supposed to be negative
    if (remaindersign != 0)
    {
        pints[0] = (UINT64)(-((INT64)(pints[0])));
    }
    
    // see if quotient is supposed to be negative
    if (quotientsign != 0)
    {
        pints[1] = (UINT64)(-((INT64)(pints[1])));
        
        // check for negative overflow
        if (pints[1] < 0x8000000000000000)
        {
            // set quotient to max negative value
            pints[1] = 0x8000000000000000;
            
            // set remainder to max (impossible) value having correct sign
            if (remaindersign != 0)
            {
                pints[0] = 0x8000000000000000;
            }
            else
            {
                pints[0] = 0x7FFFFFFFFFFFFFFF;
            }
        }
    }
    else
    {
        // check for positive overflow
        if (pints[1] >= 0x8000000000000000)
        {
            // set quotient to max negative value
            pints[1] = 0x7FFFFFFFFFFFFFFF;
            
            // set remainder to max (impossible) value having correct sign
            if (remaindersign != 0)
            {
                pints[0] = 0x8000000000000000;
            }
            else
            {
                pints[0] = 0x7FFFFFFFFFFFFFFF;
            }
        }
    }
}
*/
/*
// did it this way for two reasons
//  1) its difficult to predict when an overflow will occur using IDIV
//  2) less assembly language routines makes it easier to port
void dg_fmslashmod (UINT64* pints)
//     pints points to a UINT64 array of 3 entries
//     notation: ( pints_array_in -- pints_array_out )
//     ( numeratorlo numeratorhi denominator -- remainder quotient denominator )
{
    UINT64 quotientsign = 0;
    UINT64 remaindersign = 0;
    
    // see if numerator is negative
    if ( ((INT64)(pints[1])) < 0  )
    {
        quotientsign = ~quotientsign;
        
        // get absolute value of numerator
        *((INT128*)pints) = -(*((INT128*)pints));
    }
    
    // check for divide by 0 error
    if (0 == pints[2])
    {
        if (0 == quotientsign)
        {
            // return max positive value
            pints[0] = 0x7FFFFFFFFFFFFFFF;
            pints[1] = 0x7FFFFFFFFFFFFFFF;
        }
        else
        {
            // return max negative value 
            pints[0] = 0x8000000000000000;
            pints[1] = 0x8000000000000000;
        }
        return;
    }
    
    // see if denominator is negative
    if (((INT64)(pints[2])) < 0)
    {
        quotientsign = ~quotientsign;
        
        //remainder gets same sign as denominator
        remaindersign = ~remaindersign;
        
        // get absolute value of denominator
        pints[2] = (UINT64)(-((INT64)(pints[2])));
    }
    
    // do divide
    dg_umslashmod(pints);
    
    // see if remainder is supposed to be negative
    if (remaindersign != 0)
    {
        pints[0] = (UINT64)(-((INT64)(pints[0])));
    }
    
    // see if quotient is supposed to be negative
    if (quotientsign != 0)
    {
        pints[1] = (UINT64)(-((INT64)(pints[1])));
        
        // if remainder is not 0, need to adjust result for flooring
        if (pints[0] != 0)
        {
            // adjust quotient flooring
            pints[1] -= 1; // unsigned
            
            // adjust remainder for flooring
            //  denominator is now absolute value of original denominator
            if (remaindersign != 0)
            {
                // remainder is negative, need rem = -denom - rem
                pints[0] =  (UINT64)(-((INT64)(pints[2])) - ((INT64)(pints[0])));
            }
            else
            {
                // remainder is positive case, need rem = denom - rem
                pints[0] = pints[2] - pints[0];
            }
        }

        // check for negative overflow
        if (pints[1] < 0x8000000000000000)
        {
            // set quotient to max negative value
            pints[1] = 0x8000000000000000;
            
            // set remainder to max (impossible) value having correct sign
            if (remaindersign != 0)
            {
                pints[0] = 0x8000000000000000;
            }
            else
            {
                pints[0] = 0x7FFFFFFFFFFFFFFF;
            }
        }
    }
    else
    {
        // check for positive overflow
        if (pints[1] >= 0x8000000000000000)
        {
            // set quotient to max negative value
            pints[1] = 0x7FFFFFFFFFFFFFFF;
            
            // set remainder to max (impossible) value having correct sign
            if (remaindersign != 0)
            {
                pints[0] = 0x8000000000000000;
            }
            else
            {
                pints[0] = 0x7FFFFFFFFFFFFFFF;
            }
        }
    }
}
*/
// If the source and the destination segments overlap, this blockmove will not copy any bytes from within
//  the destination segment. Instead it will split the source into two segments if necessary and continue 
//  the copy from the first byte after the destination.

// This routine is used to handle the case where a copy and insert is done from a string into the middle
//  of the same string.

const char* dg_movebytesskipdestinationname = "dg_movebytesskipdestination";

const char* dg_movebytesskipdestination (
    unsigned char* psrc, 
    unsigned char* pdest, 
    UINT64 stringlength)
{
    UINT64 length1;
    UINT64 length2;
    
    const char* pError;
    
    // check for calculation overflow
    //  assuming buffers can not wrap around past 0x00000000
    if ( ((UINT64)psrc) > ((UINT64)(0-(INT64)stringlength)) )
    {
        return (dg_segmentgoespastenderror);
    }
    
    // check for calculation overflow
    //  assuming buffers can not wrap around past 0x00000000
    if ( ((UINT64)pdest) > ((UINT64)(0-(INT64)stringlength)) )
    {
        return (dg_segmentgoespastenderror);
    }
    
    // case 1, source segment is before destination - no overlap
    if ( ((UINT64)psrc + stringlength) <= ((UINT64)pdest) )
    {
        pError = dg_movebytes(psrc, pdest, stringlength);
        return (pError);
    }
    
    // case 2, source is after destination segment - no overlap
    if ( ((UINT64)psrc) >= ((UINT64)pdest + stringlength) )
    {
        pError = dg_movebytes(psrc, pdest, stringlength);
        return (pError);
    }
    
    // case 3, psrc starts somewhere in pdest - copy from after destination
    if ( ((UINT64)psrc) >= ((UINT64)pdest) )
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


// for Linux, FreeBSD, and MacOSX
// pointers to environment variables passed to diaperglu are in argv array starting at 
//  index argc+1 and go until argv[x]=0;
// environment variable strings are null terminated and are of form name=value
//  the =value part is not necessarily there

// for Windows, this may also be true but I'm not sure.
const char* dg_checkargs (
    int argc,              // assumes argc is at least one less than largest signed int
    char* argv[])
{
    const char* pError;
    int i;
    UINT64 lengthto0;
    
    char* pfoundname;

    // check for isapi mode, if so then success
    if ((UINT64)-1 == (UINT64)argv)
    {
        return (dg_success);
    }
    
    // Bufferhandle BHarrayhead;
    // dg_initpbharrayhead(&BHarrayhead);
    
    // gonna assume output parameters are good
    pfoundname = NULL;
    
    // checking arguments memory
    i = 0;
    
    // dg_printzerostring(&BHarrayhead, (unsigned char*)"starting list\n");
    
    while (FORTH_TRUE)
    {
        pError = dg_getuint64 ((UINT64*)&argv[i], (UINT64*)&pfoundname);
        
        if (pError != dg_success)
        {
            return (pError);
        }
        
        // could be a null at end of arguments list
        if (pfoundname == NULL)
        {            
            break;
        }
        
        // 
        if (i >= argc)
        {
            break;
        }
		
		// lengthto0 = scan for 0 for largest signed int, do not count 0
        lengthto0 = largestsignedint;
        
        pError = dg_scanforbyte(pfoundname, &lengthto0, 0);
        
        // bad memory encountered which means 0 not found so error out
        if (pError != dg_success)
        {
            return (pError);
        }
        
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pfoundname);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        // this case can't really happen...
        //  basically null missing at end of list and does not occur anywhere in memory
        //  and all memory is valid...
        if (lengthto0 == (UINT64)-1)
        {
            return (dg_outsideofbuffererror);
        }
        
		// if they don't match, i = i+1 and try again
        i++;
	}

#ifdef DGLU_OS_WIN32

    return (dg_success);

#else
        
    // checking environment variable memory
    i = argc + 1;
    
	// dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
    
    while (FORTH_TRUE)
    {
        pError = dg_getuint64 ((UINT64*)&argv[i], (UINT64*)&pfoundname);
        
        if (pError != dg_success)
        {
            return (pError);
        }
        
        // got to end of list without finding a match case 
        if (pfoundname == NULL)
        {            
            return (dg_success);
        }
		
		// lengthto0 = scan for 0 for largest signed int, do not count 0
        lengthto0 = largestsignedint;
        
        pError = dg_scanforbyte(pfoundname, &lengthto0, 0);
        
        // bad memory encountered which means 0 not found so error out
        if (pError != dg_success)
        {
            return (pError);
        }
        
        // dg_printzerostring(&BHarrayhead, (unsigned char*)pfoundname);
        // dg_printzerostring(&BHarrayhead, (unsigned char*)"\n");
        
        // this case can't really happen...
        //  basically null missing at end of list and does not occur anywhere in memory
        //  and all memory is valid...
        if (lengthto0 == (UINT64)-1)
        {
            return (dg_outsideofbuffererror);
        }
        
		// if they don't match, i = i+1 and try again
        i++;
	}

#endif
    
    // will never get here
}


// for Linux, FreeBSD
//   apparently Mac OS X doesn't do this...
//   neither does Win32
// pointers to environment variables passed to diaperglu are in argv array starting at 
//  index argc+1 and go until argv[x]=0;
// environment variable strings are null terminated and are of form name=value
//  the =value part is not necessarily there

const char* dg_getsenvnamevalue (
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
        pError = dg_getuint64 ((UINT64*)&argv[i], (UINT64*)ppfoundname);
        
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
        pError = dg_comparebytes (
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

/*
FLOAT64 dg_f32tof64 (FLOAT32 f32)
{
    return ((FLOAT64)f32);
}


FLOAT32 dg_f64tof32 (FLOAT64 f64)
{
    return ((FLOAT32)f64);
}
*/

// for forth standard F>D
INT64 dg_ftod (FLOAT32 f32)
{
    return ((INT64)f32);
}
/*
INT64 dg_dftod (FLOAT64 f64)
{
    return ((INT64)f64);
}
*/
FLOAT64 dg_dtodf(INT64 i64)
{
    return ((FLOAT64)i64);
}

/*
UINT64 dg_getnumberofboxesatleastone (
    UINT64 total, 
    UINT64 boxsize)
{
    if ((0 == total) || (0 == boxsize))
    {
        return(1);
    }

    return(((total - 1)/boxsize)+1);
}
*/

UINT64 dg_getuleb128size (UINT64 u)
{
    if (0 == u) 
    {
        return (1);
    }

    return((dg_hibit(u)/7) + 1);
}

UINT64 dg_getlengthwithuleb128length (UINT64 currentlength)
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


const char dg_pushhctwotobuffername[] = "dg_pushhctwotobuffer";

void dg_pushhctwotobuffer (
    Bufferhandle* pBHarrayhead,
    UINT64 bufferid,
    UINT64* pud)
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

    oldbufferlength = dg_growbuffer (
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

    pbuffer = dg_getpbuffer (
        pBHarrayhead,
        bufferid,
        &pnewbufferlength);

    if (dg_geterrorcount(pBHarrayhead)!= olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_pushhctwotobuffername);
        return;
    }

    perror = dg_hctwostore (pbuffer + oldbufferlength, pud);

    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_hctwostorename);
        dg_pusherror(pBHarrayhead, dg_pushhctwotobuffername);
        return;
    }
}

// trienode:
//   uleb128 lengthofparentvalue // of type and value... can be 0
//     uleb128 parentvaluetype
//     uleb128 parentvalue
//   byte numberofsymbolnames // can be 0
//     cstring symbolname0
//     uleb128 offsettovalue
//     ...
//     cstring symbolnamen-1
//     uleb128 offsettovaluen-1

// export trie with less than 256 symbols requires only one parent node
//   which holds all the symbol names
//   and 1 node for each symbol's value

// generate value only trie nodes
//  given hlist id and a parent element id,
//   for each value:
//    push a new empty lstring to top of lstring stack  
//    push uleb128(uleb128length(value) + 1) to top lstring
//    push type (will be 0 I think...)
//    push uleb128(value)

// generate root node for < 256 symbols
//  given:
//   hlist id and a parent element id 
//   lstring with value trie nodes (for the offsets)
//   base offset of value trie nodes
//
//   push a 0 byte (no parent value)
//   push number of symbols byte
//   for each symbol name:
//    push prefix passed in (will be '-' most likely or nothing)
//    push symbol's name
//    push null terminator
//    push offset to value trie node for this symbol name

// generate trie for < 256 symbols
// generate value only trie nodes
// get base offset of value trie nodes (assumes number of bytes per offset to value is same for all)
//  (if I want to save space, I can figure out how to pack more in)
// generate root node for < 256 symbols
// push root node to a buffer
// pad (grow) buffer to base offset of value trie nodes
// push value trie nodes to buffer
// voila!

UINT64 dg_calcoffsettovalue (
    UINT64 baseoffsetofnode,
    UINT64 nodefixedlength,
    UINT64 numberofsymbols,
    UINT64 offsetfrom1stvaluetolast,
    UINT64* pbytesperoffsettovalue)
{
    UINT64 firstvalueoffset;
    UINT64 lastvalueoffset;
    UINT64 firstvalueoffsetlength;
    UINT64 lastvalueoffsetlength;

    *pbytesperoffsettovalue = 1;

    while(true)
    {
        // I need to check for overflows...
        firstvalueoffset = baseoffsetofnode + nodefixedlength + (numberofsymbols * (*pbytesperoffsettovalue));
        dg_getuleb128size(firstvalueoffset); 
        lastvalueoffset = firstvalueoffset + offsetfrom1stvaluetolast;
        firstvalueoffsetlength = dg_getuleb128size(firstvalueoffset);
        lastvalueoffsetlength = dg_getuleb128size(lastvalueoffset);

        if ((firstvalueoffsetlength == (*pbytesperoffsettovalue)) &&
            (lastvalueoffsetlength == (*pbytesperoffsettovalue)))
        {
            return (firstvalueoffset);
        }

        *pbytesperoffsettovalue = lastvalueoffsetlength;
    }
}

const char dg_dumplstringname[] = "dg_dumplstring";

void dg_dumplstring(
    Bufferhandle* pBHarrayhead,
    UINT64 lstringoffsetbufferid,
    UINT64 lstringstringbufferid,
    UINT64 lstringid)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    UINT64 lstringlength;
    unsigned char* plstring;

    plstring = dg_getplstring(
        pBHarrayhead,
        lstringoffsetbufferid,
        lstringstringbufferid,
        lstringid,
        &lstringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_dumplstringname);
        return;
    }

    dg_hexdumpsegment (
        pBHarrayhead,
        plstring,
        lstringlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_dumplstringname);
        return;
    }
}
/*
const char dg_makemachotrieforlt256name[] = "dg_makemachotrieforlt256";

void dg_makemachotrieforlt256 (
    Bufferhandle* pBHarrayhead,
    UINT64 srchlistid,
    UINT64 srcparentelementid,
    unsigned char* pprefix, // this will likely be a pointer to a '-'
    UINT64 prefixlength,    // this will likely be 1
    UINT64 valuelstringoffsetbufferid,
    UINT64 valuelstringstringbufferid,
    UINT64 destbufid)
{
    unsigned char* pname;
    UINT64 namelength;

    unsigned char* pvalue;
    UINT64 valuelength;
    
    Hlistheader mysrchlistheader;
    
    UINT64 srcsortedkeyslstringlength = 0;
    unsigned char* psrcsortedkeyslstring;
    
    UINT64 srcnumberofsortedchildren, i, numlefttodo, numberofnodechildren, srcchildelementid, lengthofsymbols;
    
    UINT64 srcchildvalue;
    UINT128 srcchildvalueuleb128;
    UINT128 valueexportlengthuleb128;
    UINT64 valueoffset;
    UINT128 valueoffsetuleb128;
    UINT64 destbuflengthwithoutvalues;

    unsigned char* pvaluelstringstringbuffer;
    UINT64* pvaluelstringstringbufferlength;

    UINT64 offsetfrom1stvaluetolast;
    
    const char* pError;

    UINT64 offsettofirstvalue, bytesperoffsettovalue, nodefixedlength;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);

    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_clearbuffer(
        pBHarrayhead, 
        destbufid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;
    }

    // using this function so that we know the memory at the hlist header is valid
    dg_gethlistheader(
        pBHarrayhead,
        srchlistid,
        &mysrchlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;
    }
    
    psrcsortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        mysrchlistheader.sortedchildidslstroffsetbufid,
        mysrchlistheader.sortedchildidslstrstringbufid,
        srcparentelementid,
        &srcsortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;
    }
    
    if ((srcsortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;
    }
    
    srcnumberofsortedchildren = srcsortedkeyslstringlength >> 3;

    if (0 == srcnumberofsortedchildren)
    {
        // generate an empty trie

        // no export
        dg_pushbufferbyte(
            pBHarrayhead,
            destbufid,
            0);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }

        // no prefixes
        dg_pushbufferbyte(
            pBHarrayhead,
            destbufid,
            0);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }

        return;
    }

    if (srcnumberofsortedchildren > 255)
    {
        dg_pusherror(pBHarrayhead, (const char*)" - more than 255 symbols not supported yet error\n");
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;
    }

    // get size in bytes of all symbol names
    lengthofsymbols = 0;

    for (i = 0; i < srcnumberofsortedchildren; i++)
    {
        srcchildelementid = ((UINT64*)psrcsortedkeyslstring)[i];
        
        // get the child's name using the source hlist element id
        pname = dg_getshlistelementnom (
            pBHarrayhead,
            srchlistid,
            srcchildelementid,
            &namelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }

        lengthofsymbols += namelength;    
    }

    dg_clearbuffer(
        pBHarrayhead, 
        valuelstringoffsetbufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;
    }

    dg_clearbuffer(
        pBHarrayhead, 
        valuelstringstringbufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;
    }

    dg_printzerostring(pBHarrayhead, (unsigned char*)" value exports:\n");

    // generate lstring array of value exports
    for (i = 0; i < srcnumberofsortedchildren; i++)
    {
        srcchildelementid = ((UINT64*)psrcsortedkeyslstring)[i];
        
        // find the child's name in the source hlist
        pvalue = dg_getshlistelementvalue (
            pBHarrayhead,
            srchlistid,
            srcchildelementid,
            &valuelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }

        if (valuelength < sizeof(UINT64))
        {
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }

        // make a new lstring
        dg_pushlstring (
            pBHarrayhead,
            valuelstringoffsetbufferid,
            valuelstringstringbufferid,
            0, // length,
            (unsigned char*)"");

        // get uleb128 of value
        srcchildvalueuleb128 = dg_touleb128(*((UINT64*)pvalue));

        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n value = ");
        dg_writestdoutuinttodec(pBHarrayhead, *((UINT64*)pvalue));
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

        // push length of uleb128(value) and type to lstring
        valueexportlengthuleb128 = dg_touleb128((1 + dg_gethctwolength(srcchildvalueuleb128)));

        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n value export length = ");
        dg_writestdoutuinttodec(pBHarrayhead, 1 + dg_gethctwolength(srcchildvalueuleb128));
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n value uleb128 = ");
        dg_writestdoutuint64tohex(pBHarrayhead, srcchildvalueuleb128);
        dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

        dg_stotoplstring (
            pBHarrayhead,
            valuelstringoffsetbufferid,
            valuelstringstringbufferid,
            dg_gethctwolength(valueexportlengthuleb128),
            (unsigned char*)&valueexportlengthuleb128);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }
        
        // push type (0) to lstring
        dg_stotoplstring (
            pBHarrayhead,
            valuelstringoffsetbufferid,
            valuelstringstringbufferid,
            1,
            (unsigned char*)"\0");

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }

        // push uleb128(value) to lstring
        dg_stotoplstring (
            pBHarrayhead,
            valuelstringoffsetbufferid,
            valuelstringstringbufferid,
            dg_gethctwolength(srcchildvalueuleb128),
            (unsigned char*)&srcchildvalueuleb128);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }    

        dg_dumplstring(
            pBHarrayhead,
            valuelstringoffsetbufferid,
            valuelstringstringbufferid,
            i);

         dg_printzerostring(pBHarrayhead, (unsigned char*)"\n");

    }
        

    // get offset of last value export
    offsetfrom1stvaluetolast = dg_getlstringstartoffset (
        pBHarrayhead,
        valuelstringoffsetbufferid,
        srcnumberofsortedchildren - 1); 

    // nodefixedlength = 
    //   no values 0 (1 bytes)
    //   + numberofsymbols (1 byte)
    //   + (prefixlength * numberofsymbols)
    //   + numberofsymbols (1 byte per null terminator)
    //   lengthofsymbols ... is there a fast way to get this?

    nodefixedlength = 2 + ((prefixlength + 1)*srcnumberofsortedchildren) + lengthofsymbols;

    offsettofirstvalue = dg_calcoffsettovalue (
        0, // UINT64 baseoffsetofnode,
        nodefixedlength,
        srcnumberofsortedchildren, // UINT64 numberofsymbols,
        offsetfrom1stvaluetolast,
        &bytesperoffsettovalue);

    // generate root node
    // no export
    dg_pushbufferbyte(
        pBHarrayhead,
        destbufid,
        0);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;
    }

    // n symbols
    dg_pushbufferbyte(
        pBHarrayhead,
        destbufid,
        srcnumberofsortedchildren);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;
    }

    // push the symbol strings and uleb128offsets to values
    for (i = 0; i < srcnumberofsortedchildren; i++)
    {
        srcchildelementid = ((UINT64*)psrcsortedkeyslstring)[i];
        
        // get the child's name using the source hlist element id
        pname = dg_getshlistelementnom (
            pBHarrayhead,
            srchlistid,
            srcchildelementid,
            &namelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }

        // push the prefix
        dg_pushbuffersegment (
            pBHarrayhead,
            destbufid,
            prefixlength,
            pprefix);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }

        // push the symbol's name
        dg_pushbuffersegment (
            pBHarrayhead,
            destbufid,
            namelength,
            pname);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }

        // push the null terminator
        dg_pushbufferbyte(
            pBHarrayhead,
            destbufid,
            0);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }

        // push the uleb128 offset to the symbol's value node
        valueoffset = offsettofirstvalue + dg_getlstringstartoffset (
            pBHarrayhead,
            valuelstringoffsetbufferid,
            i);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }

        valueoffsetuleb128 = dg_touleb128(valueoffset);

        dg_pushbuffersegment (
            pBHarrayhead,
            destbufid,
            dg_gethctwolength(valueoffsetuleb128),
            (unsigned char*)&valueoffsetuleb128);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
            return;
        }
    }

    // grow buffer if needed to start offset of values
    destbuflengthwithoutvalues = dg_getbufferlength(
        pBHarrayhead,
        destbufid);

    if (offsettofirstvalue < destbuflengthwithoutvalues)
    {
        // something went wrong with the math... this shouldn't happen
        dg_pusherror(pBHarrayhead, (const char*)" - calculated offset of value nodes too small... something wrong with the math\n");
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;    
    }

    dg_growbuffer (
        pBHarrayhead,
        destbufid,
        offsettofirstvalue - destbuflengthwithoutvalues, // length,  // in bytes
        &pError,
        FORTH_FALSE);

    if (pError != dg_success)
    {
        dg_pusherror(pBHarrayhead, dg_growbuffername);
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;
    }

    pvaluelstringstringbuffer = dg_getpbuffer (
        pBHarrayhead,
        valuelstringstringbufferid,
        &pvaluelstringstringbufferlength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;
    }  

    dg_pushbuffersegment (
        pBHarrayhead,
        destbufid,
        *pvaluelstringstringbufferlength,
        pvaluelstringstringbuffer);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makemachotrieforlt256name);
        return;
    }   
}
*/


/*
HEX FEEDFACF U32, // magic
    01000007 U32, // cputype
           3 U32, // cpusubtype
           2 U32, // filetype  // 2 = exe, 6 = dylib
           2 U32, // ncmds
OHERE CONSTANT machheader.sizeofcmds  
           0 U32, // sizeofcmds = sizeof(textsegment structure) + sizeof(dyld_info_command structure)
          85 U32, // flags      1 MH_NOUNDEF 4 MH_DYLDLINK 80 MH_TWOLEVEL
           0 U32, // reserved   might be caps = 80

HEX
OHERE CONSTANT textsegment
         19 U32, // cmd = LC_SEGMENT_64
OHERE CONSTANT textsegment.cmdsize
         0 U32, // cmdsize = sizeof(textsegment structure)
  $" __TEXT"  myexefilebuffer $>BUF  // segname - read only
          0 U64, 0 C, 0 C,
          0 U64,  // vmaddr
OHERE CONSTANT textsegment.vmsize
          0 U64,  // vmsize
          0 U64,  // fileoffset
OHERE CONSTANT textsegment.filesize
          0 U64,  // filesize
          7 U32, // max VM protection   at least I think this is a UINT32
          5 U32, // initial VM protection  at least I think this is a UINT32
          0 U32, // number of sections in segment
          0 U32, // flags
*/ 
// struct dyld_info_command {
//    uint32_t   cmd;      /* LC_DYLD_INFO = 0x22 or LC_DYLD_INFO_ONLY */
//    uint32_t   cmdsize;      /* sizeof(struct dyld_info_command) */

//    uint32_t   rebase_off;  /* 0 file offset to rebase info  */
//    uint32_t   rebase_size; /* 0 size of rebase info   */

//    uint32_t   bind_off;    /* 0 file offset to binding info   */
//    uint32_t   bind_size;   /* 0 size of binding info  */

//    uint32_t   weak_bind_off;   /* 0 file offset to weak binding info   */
//    uint32_t   weak_bind_size;  /* 0 size of weak binding info  */

//    uint32_t   lazy_bind_off;   /* 0 file offset to lazy binding info */
//    uint32_t   lazy_bind_size;  /* 0 size of lazy binding infs */

//    uint32_t   export_off;  /* offset of trie - file offset to lazy binding info */
//    uint32_t   export_size; /* length of trie - size of lazy binding infs */
// };

// given:
//   pcode
//   codelength
//   ptrie
//   trielength
//
// generate a mach-o file image in a new buffer

const char dg_makesharedlibtobufname[] = "dg_makesharedlibtobuf";

void dg_makesharedlibtobuf (
    Bufferhandle* pBHarrayhead,
    unsigned char* pcode,
    UINT64 codelength,
    unsigned char* pexportrie,
    UINT64 exporttrielength,
    UINT64 destbuf)
{
    struct mach_header_64 mymach_header_64;
    struct segment_command_64 mysegment_command_64;
    struct section_64 mysection_64;
    struct symtab_command mysymtab_command;
    struct dysymtab_command mydysymtab_command;
    struct dyld_info_command mydyld_info_command;
    // struct version_min_command myversion_min_command;
    struct build_version_command mybuild_version_command; // changed for Monterey 2022 May 14
    struct nlist_64 mynlist;

    mymach_header_64.magic = 0xFEEDFACF;
    mymach_header_64.cputype = 0x01000007;
    mymach_header_64.cpusubtype = 3;
    mymach_header_64.filetype = 6; // 2 = exe, 6 = dylib
    mymach_header_64.ncmds = 2;
    mymach_header_64.sizeofcmds = sizeof(struct segment_command_64) + sizeof(struct dyld_info_command);
    mymach_header_64.flags = 0x85; // MH_NOUNDEF | MH_DYLDLINK | MH_TWOLEVEL; 
    mymach_header_64.reserved = 0;

    mysegment_command_64.cmd = LC_SEGMENT_64;
    mysegment_command_64.cmdsize = sizeof(struct segment_command_64);
    mysegment_command_64.segname[0] = '_';
    mysegment_command_64.segname[1] = '_';
    mysegment_command_64.segname[2] = 'T';
    mysegment_command_64.segname[3] = 'E'; 
    mysegment_command_64.segname[4] = 'X';
    mysegment_command_64.segname[5] = 'T';
    mysegment_command_64.segname[6] = 0;
    mysegment_command_64.segname[7] = 0; 
    mysegment_command_64.segname[8] = 0;
    mysegment_command_64.segname[9] = 0;
    mysegment_command_64.segname[0xa] = 0;
    mysegment_command_64.segname[0xb] = 0;
    mysegment_command_64.segname[0xc] = 0;
    mysegment_command_64.segname[0xd] = 0;
    mysegment_command_64.segname[0xe] = 0;
    mysegment_command_64.segname[0xf] = 0;
    mysegment_command_64.vmaddr = 0;
    mysegment_command_64.vmsize = dg_calcnearestpagesize(codelength);
    mysegment_command_64.fileoff = 0;
//        sizeof(mach_header_64) + 
//        sizeof(struct segment_command_64) + 
//        sizeof(struct dyld_info_command);
    mysegment_command_64.filesize = codelength +
        sizeof(mach_header_64) + 
        sizeof(struct segment_command_64) + 
        sizeof(struct dyld_info_command);
    mysegment_command_64.maxprot = 7;
    mysegment_command_64.initprot = 5;
    mysegment_command_64.nsects = 0;
    mysegment_command_64.flags = 0;

    mydyld_info_command.cmd = LC_DYLD_INFO;
    mydyld_info_command.cmdsize = sizeof(struct dyld_info_command);
    mydyld_info_command.rebase_off = 0;
    mydyld_info_command.rebase_size = 0;
    mydyld_info_command.bind_off = 0;
    mydyld_info_command.bind_size = 0;
    mydyld_info_command.weak_bind_off = 0;
    mydyld_info_command.weak_bind_size = 0;
    mydyld_info_command.lazy_bind_off = 0;
    mydyld_info_command.lazy_bind_size = 0;
    mydyld_info_command.export_off = 
        mysegment_command_64.fileoff +
        mysegment_command_64.filesize;
    mydyld_info_command.export_size = exporttrielength;

    mysymtab_command.cmd = LC_SYMTAB;
    mysymtab_command.cmdsize = sizeof(struct symtab_command);
    mysymtab_command.symoff = 0;
    mysymtab_command.nsyms = 2;
    mysymtab_command.stroff = 0;
    mysymtab_command.strsize = 0; // length of symbol names + 1 byte per symbol + 1

    mydysymtab_command.cmd = LC_DYSYMTAB;
    mydysymtab_command.cmdsize = sizeof(struct dysymtab_command);
    mydysymtab_command.ilocalsym = 0;
    mydysymtab_command.nlocalsym = 0;
    mydysymtab_command.iextdefsym = 0;
    mydysymtab_command.nextdefsym = 2;
    mydysymtab_command.iundefsym = 2;
    mydysymtab_command.nundefsym = 0;
    mydysymtab_command.tocoff = 0;
    mydysymtab_command.ntoc = 0;
    mydysymtab_command.modtaboff = 0;
    mydysymtab_command.nmodtab = 0;
    mydysymtab_command.extrefsymoff = 0;
    mydysymtab_command.nextrefsyms = 0;
    mydysymtab_command.indirectsymoff = 0;
    mydysymtab_command.nindirectsyms = 0;
    mydysymtab_command.extreloff = 0;
    mydysymtab_command.nextrel = 0;
    mydysymtab_command.locreloff = 0;
    mydysymtab_command.nlocrel = 0;

    // myversion_min_command.cmd = LC_VERSION_MIN_MACOSX;
    // myversion_min_command.cmdsize = sizeof(struct version_min_command);
    // myversion_min_command.version = 0x000A0B00; // 10.11
    // myversion_min_command.reserved = 0;
    
    // switched to LC_BUILD_VERSION for Monterey 2022 May 14
    mybuild_version_command.cmd = LC_BUILD_VERSION;
    mybuild_version_command.cmdsize = sizeof(struct build_version_command);
    mybuild_version_command.platform = PLATFORM_MACOS;
    mybuild_version_command.minos = 0x000B0000; // 11.00
    mybuild_version_command.sdk = 0;
    mybuild_version_command.ntools = 0;

    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    dg_clearbuffer(
        pBHarrayhead, 
        destbuf);
        
    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        sizeof(struct mach_header_64),
        (unsigned char*)&mymach_header_64);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makesharedlibtobufname);
        return;
    }

    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        sizeof(struct segment_command_64),
        (unsigned char*)&mysegment_command_64);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makesharedlibtobufname);
        return;
    }

    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        sizeof(struct dyld_info_command),
        (unsigned char*)&mydyld_info_command);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makesharedlibtobufname);
        return;
    }

    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        codelength,
        pcode);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makesharedlibtobufname);
        return;
    }

    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        exporttrielength,
        pexportrie);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makesharedlibtobufname);
        return;
    }
}

// header
// __TEXT segment command
//   __text section command
// min version command
// symtab command
// dysymtab command
// code
// symbol values nlist
// symbol name strings
// relocation entries

// export symbol list is a set of name value pairs where the value is an offset in the code buffer
//  the names are unique

// import symbol list is a set of name value pairs where the value is an offset in the code buffer
//   immediately after where the linker will put a 32bit offset to the GOTRELOC entry for the symbol
//   the names are not necessarily unique
//   the linker will generate the GOTRELOC table

const char dg_makedototobufsubname[] = "dg_makedototobufsub";

void dg_makedototobufsub (
    Bufferhandle* pBHarrayhead,
    unsigned char* pcode,
    UINT64 codelength,
    UINT64 exportsymbollisthlistid,
    UINT64 exportsymbollistparentelementid,
    UINT64 importsymbollisthlistid,          // (UINT64)-1 means not using imports
    UINT64 importsymbollistparentelementid,
    UINT64 destbuf,
    UINT64 stringtablelstringoffsetbufferid,
    UINT64 stringtablelstringstringbufferid,
    UINT64 relocationtablebufferid)
{
    struct mach_header_64 mymach_header_64;
    struct segment_command_64 mysegment_command_64;
    struct section_64 mysection_64;
    struct symtab_command mysymtab_command;
    struct dysymtab_command mydysymtab_command;
    struct dyld_info_command mydyld_info_command;
    // struct version_min_command myversion_min_command;
    struct build_version_command mybuild_version_command; // changed for Monterey 2022 May 14
    struct nlist_64 mynlist;
    struct relocation_info myrelocation_info;
    
    UINT64 codelengthaligned = dg_getnearesthighestmultiple (
        codelength, // n,
        8); // pagesize);

    unsigned char* pname;
    UINT64 namelength;
    unsigned char* pvalue;
    UINT64 valuelength;
    UINT64 value;
    
    unsigned char* plastimportname = (unsigned char*)"";
    UINT64 lastimportnamelength = (UINT64)-1;  // making this -1 in case someone defines an empty string
                                               //  as the first import symbol name... so that the empty
                                               //  string will be seen as a new import symbol name

    UINT64 totallengthofsymbolnames;
    
    Hlistheader myexportsymbolhlistheader;
    UINT64 exportsymbolsortedkeyslstringlength = 0;
    unsigned char* pexportsymbolsortedkeyslstring;
    UINT64 numberofexportsymbols = 0;
    
    UINT64 i, srcchildelementid;
    UINT64 srcsortedkeyslstringlength;
   
    Hlistheader myimportsymbolhlistheader;
    UINT64 importsymbolsortedkeyslstringlength = 0;
    unsigned char* pimportsymbolsortedkeyslstring;
    UINT64 numberofrelocationentries = 0;
    UINT64 numberofimportsymbols = 0;
    
    UINT64 stringtablesize, stringtablesizealigned;
    
    INT64 compareflag;
    
    UINT64 totalnumberofsymbols = 0;

    unsigned char* pbuf;
    UINT64* pbuflength;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    // has to be at least one export symbol
    if (DG_ENDOFLIST == exportsymbollisthlistid)
    {
        return;
    }
    
    if (DG_ENDOFLIST == exportsymbollistparentelementid)
    {
        return;
    }
    
    mymach_header_64.magic = 0xFEEDFACF;
    mymach_header_64.cputype = 0x01000007;
    mymach_header_64.cpusubtype = 3;
    mymach_header_64.filetype = MH_OBJECT;
    mymach_header_64.ncmds = 4;
    mymach_header_64.sizeofcmds =
        sizeof(struct segment_command_64) +
        sizeof(struct section_64) +
        // sizeof(struct version_min_command) + moo
        sizeof(struct build_version_command) +
        sizeof(struct symtab_command) +
        sizeof(struct dysymtab_command);
    mymach_header_64.flags = 0x0;
    mymach_header_64.reserved = 0;

    mysegment_command_64.cmd = LC_SEGMENT_64;
    mysegment_command_64.cmdsize =
        sizeof(struct segment_command_64) +  // changed for Monterey 2022 May 14... may have been incorrect...
        sizeof(struct section_64);
    mysegment_command_64.segname[0] = 0 ; // '_'; // changed for Monterey 2022 May 14...
    mysegment_command_64.segname[1] = 0; // '_';
    mysegment_command_64.segname[2] = 0; // 'T';
    mysegment_command_64.segname[3] = 0; // 'E';
    mysegment_command_64.segname[4] = 0; // 'X';
    mysegment_command_64.segname[5] = 0; // 'T';
    mysegment_command_64.segname[6] = 0;
    mysegment_command_64.segname[7] = 0;
    mysegment_command_64.segname[8] = 0;
    mysegment_command_64.segname[9] = 0;
    mysegment_command_64.segname[0xa] = 0;
    mysegment_command_64.segname[0xb] = 0;
    mysegment_command_64.segname[0xc] = 0;
    mysegment_command_64.segname[0xd] = 0;
    mysegment_command_64.segname[0xe] = 0;
    mysegment_command_64.segname[0xf] = 0;
    mysegment_command_64.vmaddr = 0;
    mysegment_command_64.vmsize = codelength; // dg_calcnearestpagesize(codelength); changed for Monterey 2022 May 14
    mysegment_command_64.fileoff =
        sizeof(struct mach_header_64) +
        mymach_header_64.sizeofcmds;
    mysegment_command_64.filesize = codelength;
    mysegment_command_64.maxprot = 7;
    mysegment_command_64.initprot = 7;  // changed to match Monterey 2022 May 14
    mysegment_command_64.nsects = 1;
    mysegment_command_64.flags = 0;

    mysection_64.sectname[0] = '_';
    mysection_64.sectname[1] = '_';
    mysection_64.sectname[2] = 't';
    mysection_64.sectname[3] = 'e';
    mysection_64.sectname[4] = 'x';
    mysection_64.sectname[5] = 't';
    mysection_64.sectname[6] = 0;
    mysection_64.sectname[7] = 0;
    mysection_64.sectname[8] = 0;
    mysection_64.sectname[9] = 0;
    mysection_64.sectname[0xa] = 0;
    mysection_64.sectname[0xb] = 0;
    mysection_64.sectname[0xc] = 0;
    mysection_64.sectname[0xd] = 0;
    mysection_64.sectname[0xe] = 0;
    mysection_64.sectname[0xf] = 0;

    mysection_64.segname[0] = '_';
    mysection_64.segname[1] = '_';
    mysection_64.segname[2] = 'T';
    mysection_64.segname[3] = 'E';
    mysection_64.segname[4] = 'X';
    mysection_64.segname[5] = 'T';
    mysection_64.segname[6] = 0;
    mysection_64.segname[7] = 0;
    mysection_64.segname[8] = 0;
    mysection_64.segname[9] = 0;
    mysection_64.segname[0xa] = 0;
    mysection_64.segname[0xb] = 0;
    mysection_64.segname[0xc] = 0;
    mysection_64.segname[0xd] = 0;
    mysection_64.segname[0xe] = 0;
    mysection_64.segname[0xf] = 0;

    mysection_64.addr = 0;
    mysection_64.size = codelength;
    mysection_64.offset = mysegment_command_64.fileoff;
    mysection_64.align = 0; // 1; changed for Monterey 2022 May 14
    mysection_64.reloff = 0;
    mysection_64.nreloc = numberofrelocationentries;
    mysection_64.flags = S_REGULAR | S_ATTR_PURE_INSTRUCTIONS | S_ATTR_SOME_INSTRUCTIONS;
    mysection_64.reserved1 = 0;
    mysection_64.reserved2 = 0;
    mysection_64.reserved3 = 0;

    // myversion_min_command.cmd = LC_VERSION_MIN_MACOSX;
    // myversion_min_command.cmdsize = sizeof(struct version_min_command);
    // myversion_min_command.version = 0x000B0000; // 11.0 changed for Monterey 2022 May 14 from 10.11
    // myversion_min_command.sdk = 0; // added for Monterey 2022 May 14
    
    // switched to LC_BUILD_VERSION for Monterey 2022 May 14
    mybuild_version_command.cmd = LC_BUILD_VERSION;
    mybuild_version_command.cmdsize = sizeof(struct build_version_command);
    mybuild_version_command.platform = PLATFORM_MACOS;
    mybuild_version_command.minos = 0x000B0000; // 11.00
    mybuild_version_command.sdk = 0;
    mybuild_version_command.ntools = 0;
    
    // need to check for the not using export hlist case
    
    // using this function so that we know the memory at the hlist header is valid
    dg_gethlistheader(
        pBHarrayhead,
        exportsymbollisthlistid,
        &myexportsymbolhlistheader,
        sizeof(Hlistheader));
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }
    
    // export symbol list
    pexportsymbolsortedkeyslstring = dg_getplstring(
        pBHarrayhead,
        myexportsymbolhlistheader.sortedchildidslstroffsetbufid,
        myexportsymbolhlistheader.sortedchildidslstrstringbufid,
        exportsymbollistparentelementid,
        &srcsortedkeyslstringlength);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }
    
    if ((srcsortedkeyslstringlength % sizeof(UINT64)) != 0)
    {
        dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
        dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }
    
    numberofexportsymbols = srcsortedkeyslstringlength >> 3;

    /*
    if (0 == numberofexportsymbols)
    {
        return;
    */

    // calculate length of all export symbol names
    //  and build export string table
    totallengthofsymbolnames = 0;

    // make a new lstring, an empty string starts the string table
    dg_pushlstring (
        pBHarrayhead,
        stringtablelstringoffsetbufferid,
        stringtablelstringstringbufferid,
        1, // length,
        (unsigned char*)"\0");

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    // this goes through children alphabetically
    for(i=0; i < numberofexportsymbols; i++)
    {
        // make a new lstring
        dg_pushlstring (
            pBHarrayhead,
            stringtablelstringoffsetbufferid,
            stringtablelstringstringbufferid,
            1, // length,
            (unsigned char*)"_");

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }

        srcchildelementid = ((UINT64*)pexportsymbolsortedkeyslstring)[i];
        
        // find the child's name in the source hlist
        pname = dg_getshlistelementnom (
            pBHarrayhead,
            exportsymbollisthlistid,
            srcchildelementid,
            &namelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }

        dg_stotoplstring (
            pBHarrayhead,
            stringtablelstringoffsetbufferid,
            stringtablelstringstringbufferid,
            namelength,
            pname);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }

        dg_stotoplstring (
            pBHarrayhead,
            stringtablelstringoffsetbufferid,
            stringtablelstringstringbufferid,
            1,
            (unsigned char*)"\0");

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }

        totallengthofsymbolnames += namelength;
    }
    
    // import symbol list
    // need to check for the not using import hlist case
    
    if (importsymbollisthlistid != (UINT64)-1)
    {
        // using this function so that we know the memory at the hlist header is valid
        dg_gethlistheader(
            pBHarrayhead,
            importsymbollisthlistid,
            &myimportsymbolhlistheader,
            sizeof(Hlistheader));
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
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
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
    
        if ((srcsortedkeyslstringlength % sizeof(UINT64)) != 0)
        {
            dg_pusherror(pBHarrayhead, dg_arraymisalignederror);
            dg_pusherror(pBHarrayhead, dg_sortedkeyslstringname);
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
    
        numberofrelocationentries = srcsortedkeyslstringlength >> 3;
    }
    
    dg_clearbuffer(
        pBHarrayhead,
        relocationtablebufferid);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }
    
    // this goes through children alphabetically
    //  if numberofimportsymbols is 0, this for loop should not go....
    for(i=0; i < numberofrelocationentries; i++)
    {
        // if this is a new import symbol name, then this symbol name
        //   needs to get added to the import symbol list

        srcchildelementid = ((UINT64*)pimportsymbolsortedkeyslstring)[i];
        
        // find the child's name in the source hlist
        pname = dg_getshlistelementnom (
            pBHarrayhead,
            importsymbollisthlistid,
            srcchildelementid,
            &namelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
        
        pError = dg_comparebytes (
            (unsigned char*)pname,
            namelength,
            (unsigned char*)plastimportname,
            lastimportnamelength,
            &compareflag);
        
        // this shouldn't happen
        if (pError != dg_success)
        {
            dg_pusherror(pBHarrayhead, dg_comparebytesname);
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
        
        // if they don't match then we need to add a symbol to the .o import symbol list
        if (0 != compareflag)
        {
            // make a new lstring
            dg_pushlstring (
                pBHarrayhead,
                stringtablelstringoffsetbufferid,
                stringtablelstringstringbufferid,
                1, // length,
                (unsigned char*)"_");

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
                return;
            }

            dg_stotoplstring (
                pBHarrayhead,
                stringtablelstringoffsetbufferid,
                stringtablelstringstringbufferid,
                namelength,
                pname);

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
                return;
            }

            dg_stotoplstring (
                pBHarrayhead,
                stringtablelstringoffsetbufferid,
                stringtablelstringstringbufferid,
                1,
                (unsigned char*)"\0");

            if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
            {
                dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
                return;
            }

            totallengthofsymbolnames += namelength;
            numberofimportsymbols++;
        }
        
        // need to add the relocation entry
        // srcchildelementid = ((UINT64*)pimportsymbolsortedkeyslstring)[i];
        
        // get the source child element's value. This is the offset in the buffer to be patched.
        pvalue = dg_getshlistelementvalue (
            pBHarrayhead,
            importsymbollisthlistid,
            srcchildelementid,
            &valuelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
        
        if (valuelength < sizeof(UINT64))
        {
            // need a better error here... something like hlist value too small
            // or patch offset missing or corrupt
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
        
        // type
        // X86_64_RELOC_UNSIGNED = 0 // absolute... I'm guessing this will only work
        //                           //   for the mov immediate 64 bit, and arrays of 64 bit pointers
        // X86_64_RELOC_SIGNED = 1 // wouldn't 1 and 2 be treated the same?.. used for data
        // X86_64_RELOC_BRANCH = 2 // used for relative calls... don't need labels for a forth assembler
        //                         // to do branching so... is this really needed?
        //                         // I think they use this for calling stuff in other .o files or other
        //                         // statically linked libraries... but if you are dynamically linking
        //                         // libraries where you don't know what address they will load at, or
        //                         //  if you compile all your stuff into one buffer and generate only
        //                         //  one .o file for the project... this probably isn't needed...
        //                             //  unless.. you want to do forward references
        // X86_64_RELOC_GOT_LOAD = 3   // a MOVQ load of a GOT entry ... this will always work I think...
        //                             //  it's just slow...
        // X86_64_RELOC_GOT = 4        // other GOT references
        // X86_64_RELOC_SUBTRACTOR = 5 // must be followed by a X86_64_RELOC_UNSIGNED
        // X86_64_RELOC_SIGNED_1,      // for signed 32-bit displacement with a -1 addend
        // X86_64_RELOC_SIGNED_2,      // for signed 32-bit displacement with a -2 addend
        // X86_64_RELOC_SIGNED_4,      // for signed 32-bit displacement with a -4 addend
        // X86_64_RELOC_TLV,           // for thread local variables
        //
        // final executables only use X86_64_RELOC_UNSIGNED (I'm guessing to fill out the pointer table)
        
        // could make sure that value fits into an INT32
        myrelocation_info.r_address = *((UINT64*)pvalue);
        myrelocation_info.r_symbolnum = numberofexportsymbols + numberofimportsymbols - 1;
        myrelocation_info.r_pcrel = 1;
        myrelocation_info.r_length = 2; // only int32s for now. 0=byte, 1=16bits, 2=32bits, 3=64bits
        myrelocation_info.r_extern = 1;
        myrelocation_info.r_type = 4;
        
        // struct relocation_info {
        //    int32_t    r_address;    /* offset in the section to what is being
        //                    relocated */
        //    uint32_t     r_symbolnum:24,    /* symbol index if r_extern == 1 or section
        //                    ordinal if r_extern == 0 */
        //         r_pcrel:1,     /* was relocated pc relative already */
        //         r_length:2,    /* 0=byte, 1=word, 2=long, 3=quad */
        //         r_extern:1,    /* does not include value of sym referenced */
        //         r_type:4;    /* if not 0, machine specific relocation type */
        // };
        
        // need to push this to a temporary buffer...
        dg_pushbuffersegment (
            pBHarrayhead,
            relocationtablebufferid,
            sizeof(relocation_info),
            (unsigned char*)&myrelocation_info);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
    }
    
    totalnumberofsymbols = numberofexportsymbols + numberofimportsymbols;
    
    mysymtab_command.cmd = LC_SYMTAB;
    mysymtab_command.cmdsize = sizeof(struct symtab_command);
    mysymtab_command.symoff =
        mysegment_command_64.fileoff + codelengthaligned; // probably should align here...
    mysymtab_command.nsyms = totalnumberofsymbols;
    mysymtab_command.stroff =
        mysymtab_command.symoff +
        (totalnumberofsymbols * sizeof(struct nlist_64));
    
    stringtablesize = 1 +            // empty string is always symbol zero for some reason 
        totalnumberofsymbols +       // 1 byte for null terminators
        totalnumberofsymbols +       // 1 byte for '_' prefix
        totallengthofsymbolnames;    // n
        
    stringtablesizealigned = dg_getnearesthighestmultiple (
        stringtablesize,    // length of symbol names, 
        8);                 // pagesize);

    mysymtab_command.strsize = stringtablesizealigned;

    mydysymtab_command.cmd = LC_DYSYMTAB;
    mydysymtab_command.cmdsize = sizeof(struct dysymtab_command);
    mydysymtab_command.ilocalsym = 0;
    mydysymtab_command.nlocalsym = 0;
    mydysymtab_command.iextdefsym = 0;
    mydysymtab_command.nextdefsym = numberofexportsymbols;
    mydysymtab_command.iundefsym = numberofexportsymbols;
    mydysymtab_command.nundefsym = numberofimportsymbols;
    mydysymtab_command.tocoff = 0;
    mydysymtab_command.ntoc = 0;
    mydysymtab_command.modtaboff = 0;
    mydysymtab_command.nmodtab = 0;
    mydysymtab_command.extrefsymoff = 0;
    mydysymtab_command.nextrefsyms = 0;
    mydysymtab_command.indirectsymoff = 0;
    mydysymtab_command.nindirectsyms = 0;
    mydysymtab_command.extreloff = 0;
    mydysymtab_command.nextrel = 0;
    mydysymtab_command.locreloff = 0;
    mydysymtab_command.nlocrel = 0;
    
    // check for 0 added for Monterey 2022 May 14 because Monterey added check to make sure reloff is in file
    //  even if it wasn't used
    if (0 == numberofrelocationentries)
    {
        mysection_64.reloff = 0;
    }
    else
    {
        mysection_64.reloff = mysymtab_command.stroff + stringtablesizealigned;
    }
    
    mysection_64.nreloc = numberofrelocationentries;
    mysection_64.flags = S_REGULAR | S_ATTR_PURE_INSTRUCTIONS | S_ATTR_SOME_INSTRUCTIONS;
    mysection_64.reserved1 = 0;
    mysection_64.reserved2 = 0;
    mysection_64.reserved3 = 0;

    dg_clearbuffer(
        pBHarrayhead, 
        destbuf);
        
    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        sizeof(struct mach_header_64),
        (unsigned char*)&mymach_header_64);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        sizeof(struct segment_command_64),
        (unsigned char*)&mysegment_command_64);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        sizeof(struct section_64),
        (unsigned char*)&mysection_64);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        sizeof(struct build_version_command),
        (unsigned char*)&mybuild_version_command); 

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        sizeof(struct symtab_command),
        (unsigned char*)&mysymtab_command);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        sizeof(struct dysymtab_command),
        (unsigned char*)&mydysymtab_command);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        codelength,
        pcode);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }
    
    // align to 8...  assuming codelengthaligned >= codelength...
    for ( i = 0; i < (codelengthaligned - codelength); i++)
    {
        dg_pushbuffersegment (
            pBHarrayhead,
            destbuf,
            1,
            (unsigned char*)"\0");
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
    }

    // push export symbol value nlist entries
    // this goes through children alphabetically
    for(i=0; i < numberofexportsymbols; i++)
    {
        srcchildelementid = ((UINT64*)pexportsymbolsortedkeyslstring)[i];
        
        // get the source child element's value. This is the offset in the buffer to be patched.
        pvalue = dg_getshlistelementvalue (
            pBHarrayhead,
            exportsymbollisthlistid,
            srcchildelementid,
            &valuelength);
        
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
        
        if (valuelength < sizeof(UINT64))
        {
            // need a better error here... something like hlist value too small
            // or patch offset missing or corrupt
            dg_pusherror(pBHarrayhead, dg_structuretoosmallerror);
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
        
        mynlist.n_un.n_strx = dg_getlstringstartoffset (
            pBHarrayhead,
            stringtablelstringoffsetbufferid,
            i + 1); // offset to symbol name string
        
        mynlist.n_type = 0x0f; // external, defined in section .sect... does external here mean exported?
        mynlist.n_sect = 1;    //   if (n_type & 0x0e) == 0x0e, symbol is defined in this section
        mynlist.n_desc = 0;
        mynlist.n_value = *((UINT64*)(pvalue));

        dg_pushbuffersegment (
            pBHarrayhead,
            destbuf,
            sizeof(struct nlist_64),
            (unsigned char*)&mynlist);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }   
    }
    
    // push import symbol value nlist entries
    // this goes through children alphabetically
    for(i=0; i < numberofimportsymbols; i++)
    {
        mynlist.n_un.n_strx = dg_getlstringstartoffset (
            pBHarrayhead,
            stringtablelstringoffsetbufferid,
            numberofexportsymbols + i + 1); // offset to symbol name string
        
        mynlist.n_type = 0; // undefined symbol
        mynlist.n_sect = 0;
        mynlist.n_desc = 0;
        mynlist.n_value = 0;

        dg_pushbuffersegment (
            pBHarrayhead,
            destbuf,
            sizeof(struct nlist_64),
            (unsigned char*)&mynlist);

        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
    }

    // push the strings...
    pbuf = dg_getpbuffer (
        pBHarrayhead,
        stringtablelstringstringbufferid,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        *pbuflength,
        pbuf);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }
    
    // align it multiple of 8 bytes
    for (i = 0; i < (stringtablesizealigned - stringtablesize); i++)
    {
        dg_pushbuffersegment (
            pBHarrayhead,
            destbuf,
            1,
            (unsigned char*)"\0");
            
        if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
        {
            dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
            return;
        }
    }
    
    // push the relocation table
    pbuf = dg_getpbuffer (
        pBHarrayhead,
        relocationtablebufferid,
        &pbuflength);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }

    dg_pushbuffersegment (
        pBHarrayhead,
        destbuf,
        *pbuflength,
        pbuf);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufsubname);
        return;
    }
}

// call this makedotobuf
const char dg_makedototobufname[] = "dg_makedototobuf";

void dg_makedototobuf (
    Bufferhandle* pBHarrayhead,
    unsigned char* pcode,
    UINT64 codelength,
    UINT64 exportsymbollisthlistid,
    UINT64 exportsymbollistparentelementid,
    UINT64 importsymbollisthlistid,
    UINT64 importsymbollistparentelementid,
    UINT64 destbuf)
{
    UINT64 exportstringoffsetbufferid = (UINT64)dg_badbufferid; // needed for dg_freebuffer
    UINT64 exportstringstringbufferid = (UINT64)dg_badbufferid;
    UINT64 relocationtablebufferid = (UINT64)dg_badbufferid;
    
    const char* pError;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }

    exportstringoffsetbufferid = dg_newbuffer(
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

    exportstringstringbufferid = dg_newbuffer(
        pBHarrayhead,
        0x1000, // growby,
        largestsignedint, // maxsize,
        &pError, // const char** pError,
        FORTH_FALSE); // forceoutofmemory) )
        
    if (pError != dg_success)
    {
        dg_freebuffer(pBHarrayhead, exportstringoffsetbufferid);

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
        dg_freebuffer(pBHarrayhead, exportstringoffsetbufferid);
        dg_freebuffer(pBHarrayhead, exportstringstringbufferid);

        dg_pusherror(pBHarrayhead, pError);
        dg_pusherror(pBHarrayhead, dg_newbuffername);
        dg_pusherror(pBHarrayhead, dg_makedototobufname);
        return;
    }
    
    // copy the entry symbol list to the export symbol list here...
    
    
    dg_makedototobufsub (
        pBHarrayhead,
        pcode,
        codelength,
        exportsymbollisthlistid,
        exportsymbollistparentelementid,
        importsymbollisthlistid,
        importsymbollistparentelementid,
        destbuf,
        exportstringoffsetbufferid,
        exportstringstringbufferid,
        relocationtablebufferid);

    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_makedototobufname);
        // not returning here on purpose so the buffers will be freed
    }

    // if the buffer wasn't allocated, the id should be dg_badbufferid
      // dg_freebuffer will not give an error or try to free dg_badbufferid
    dg_freebuffer(pBHarrayhead, exportstringoffsetbufferid);
    dg_freebuffer(pBHarrayhead, exportstringstringbufferid);
    dg_freebuffer(pBHarrayhead, relocationtablebufferid);
}

// dg_forthdotofiletodylibfile
//   given pointer to .o filename
//   and .dylib filename...
//   build argv on return stack
//   use runfileandwait on ld
const char dg_dotofiletodylibfilename[] = "dg_dotofiletodylibfile";

const char* dg_dotofiletodylibfile (
    Bufferhandle* pBHarrayhead,
    char* pdotofilename,
    char* pdotdylibfilename)
{
    const char* perror;
    char* argv[11];
    
    argv[0] = (char*)"ld\0";
    argv[1] = (char*)"-macosx_version_min\0";
    argv[2] = (char*)"10.11";
    argv[3] = (char*)"-dynamic";
    argv[4] = (char*)"-dylib";
    argv[5] = (char*)"-no_uuid";
    argv[6] = (char*)"-no_eh_labels";
    argv[7] = (char*)"-o";
    argv[8] = pdotdylibfilename;
    argv[9] = pdotofilename;
    argv[10] = (char*)NULL;
    
    perror = dg_runfileandwait(
        pBHarrayhead,
        "ld",  // filename
        argv,
        (char**)NULL,  // envp
        dg_success);
    
    return (perror);
    
}

// dg_forthmakedlibfile

// ( pargv[] penvp[] pfilename -- )
void dg_forthrunfileandwait (Bufferhandle* pBHarrayhead)
{
    const char* perror;
    const char* pfilename;
    char** argv;
    char** envp;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    pfilename = (const char*)dg_popbufferuint64(
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

void dg_forthrunfileandwaitnoenvquotessub(Bufferhandle* pBHarrayhead)
{
    UINT64 n;
    UINT64* pstringptrs;
    const char* perror;
    const char* pfilename;
    
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    n = dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
      return;
    }
    
    if (n < 1)
    {
        dg_pusherror(pBHarrayhead, (const char*)"file name missing");
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
        return;
    }
    
    dg_pushdatastack(pBHarrayhead, n);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
      return;
    }
    
    dg_forthgetargsfromnstrings(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
      return;
    }
    
    pstringptrs = (UINT64*)dg_popdatastack(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
      return;
    }
    
    pfilename = (const char*)pstringptrs[0];
    
    perror = dg_runfileandwait(
        pBHarrayhead,
        pfilename,
        (char *const *)pstringptrs,  // argv[],
        NULL,                         // envp[],
        dg_success);               // forceerrorflag)
       
    if (perror != dg_success)
    {
        dg_pusherror(pBHarrayhead, perror);
        dg_pusherror(pBHarrayhead, dg_runfileandwaitname);
        // not returning here to drop the strings even if there is an error
    }
    
    olderrorcount = dg_geterrorcount(pBHarrayhead); // just in case there were errors from running file
    
    dg_dropnlstrings(
        pBHarrayhead,
        DG_STRINGOFFSETSTACK_BUFFERID,
        DG_STRINGSTRINGSTACK_BUFFERID,
        n+1);
        
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
        dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
        return;
    }
}


void dg_forthrunfileandwaitnoenvquotes(Bufferhandle* pBHarrayhead)
{
    UINT64 olderrorcount = dg_geterrorcount(pBHarrayhead);
    
    if (baderrorcount == olderrorcount)
    {
        return;
    }
    
    dg_forthwords0stringquotes(pBHarrayhead);
    
    if (dg_geterrorcount(pBHarrayhead) != olderrorcount)
    {
      dg_pusherror(pBHarrayhead, dg_forthrunfileandwaitnoenvquotesname);
      return;
    }
    
    dg_forthrunfileandwaitnoenvquotessub(pBHarrayhead);
}


void dg_forthrunfileandwaitnoenvstring(Bufferhandle* pBHarrayhead)
{
/*
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
        (const char*)pstring,    // pfilename,   really the command line
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
    */
}

/*
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
*/
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

const char* dg_callfunctionasyncname = "dg_callfunctionasync";

const char* dg_callfunctionasync(
    UINT64* pthreadhandle,
    void *(*pfunction)(void *), 
    void *parguments)
{
    const char* pError;
    UINT64 myerrno;
    
    // check memory at pthreadhandle
    pError = dg_putuint64(
        pthreadhandle,
        0);
        
    if (pError != dg_success)
    {
        return(pError);
    }
    
    myerrno = pthread_create(
        (pthread_t *)pthreadhandle, 
        NULL, // pthread_attributes
        pfunction, 
        parguments);
    
    switch(myerrno)
    {
        case 0:
            return(dg_success);
        case EAGAIN:
            return (dg_toomanyprocesseserror);
        case EPERM:
            return(dg_accessdeniederror);
        case EINVAL:
            return (dg_invalidparametererror);
        default:
            return(dg_oserror);
    }
}

// I need a word that parses a string and pushes the parsed words as zero strings to an lstring array
// I also think I need another lstring stack and data stack for holding local data in subroutines...
//   I already have those for handling LOCALS| ... can I just use those? Be nice to keep it simple...
// soo... after I do that I need build an array of pointers to the strings

// parse string to lstrings array....
//  parse for whitespace... push each word to an lstring array and push a 0x00 byte onto the end
//  does it matter what kind of strings I use? (unicode, ascii)
//  need to remember start index in the lstring array, and the number of words pushed

// parse lstring array and build pointer array
//   need an lstring array, start id, and number of lstrings to do...
//   pointers only valid until you push more stuff onto the lstring array
