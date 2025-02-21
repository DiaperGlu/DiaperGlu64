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

#include <signal.h>
#include <sys/ucontext.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>
#include "../diapergluforth.h"

// //////////////////////////////////////////////////////////////////////
//
// mac os x rules
//   can not trash ebx register
//   if you call a subroutine from assembler, especially an operating system subroutine,
//    then the return stack must be 16 byte aligned at the point of the call
//   probably can not trash the direction flag (must be forward)
// mac os x problems
//   do not know what operating system or compiler is doing during a signal catch (like what happens to ebx)
//     making not returning back from the same subroutine during a signal catch nearly impossible
//     so you pretty much have to go back through the same subroutine UNLESS you enter the signal catching
//     condition from an assembler routine where you know what you did with the saved registers and you
//     restore them in exactly the same way
// signal catching strategy
//   have to do signal catching from an assembler routine I write OR
//   use a C label later in the routine to mark where to continue (if there is such a thing)
//
// custom assembler routine signal catching strategy:
//   save flags if needed
//   save registers if needed (especially ebx)
//   set return flag to success
//   align stack and call enable signal catch routine to return to catch later in routine
//   do whatever it is that can crash
//   skip over catch code
//  catch here:
//   set return flag to fail
//  end catch
//   align stack and call disable signal catch routines 
//   exit

// what if I make a standard catch routine... could pass a subroutine to the catch routine...

// try blocks do not work for memory faults
// must return back through normal channels - its an interrupt, processor and os flags and stuff

// assumes routine causing fault has const char* return type
//   and just wants to exit immediately with "dg_badmemoryerror"

// I need a way to pass either pBHarrayhead or perhaps just the catch address to dg_catchbadmemoryerror
// I could use a register... but that gets tricky... is there any other way?
// Maybe could assume it's at ebp+8?
// If the code that causes the fault is in assembler it is doable...
//  but if it isn't....
//  OR I could put it on the stack at a certain spot and just have a rule, no subroutines during try
//   which is a pain...
//   maybe they have room in the structure somewhere?
//   or maybe... maybe instead of having a subroutine dg_catchbadmemoryerror, I put the dg_catchbadmemoryerror
//   code into dg_trycatchbadmemoryerror and pass in the continue address?
// so what gives? how do I tell this program to skip some code without using assembler or global variables?
//
// Using global variables will work for non rommed code as long as you use a separate global variable for
//  each individual catch address and the operating system will have each application sharing an in use
//  instance of the diaplerglu library use the same base address for the library
// Another way is to a relative offset to the catch address instead of the actual address, this way it doesn't
//  matter if each application thinks the shared in memory copy of the diaperglu library is at the same address.
// Another way is to pass the catch address or offset in the sigaction structure if possible or on the return
//  stack or in a register. If passing the catch address on the return stack, you can't use an ebp offset to a local
//  variable because sometimes the compiler will push the registers to the stack before creating space for
//  local variables. Passing the catch address as a parameter and using an ebp offset to the parameters will work
// Another way is to just code everything in assembler then you know exactly what the stack frame looks like.

/*
void dg_setcatchallcatchaddress((void (*)(int, __siginfo*, void*)) address)
{
    struct sigaction mysigaction;
    UINT32 i;
    
    // this would run a lot faster if I used a predifined (static?) constant structure
    mysigaction.sa_sigaction = address;

    // sa_mask on mac os x is UINT32
    //  blocks signals from occurring during handler
    //  what happens if another signal happens during the handler?
    mysigaction.sa_mask = 0;

    // SA_RESETHAND means throw away further occurrences of signal during handler
    mysigaction.sa_flags = SA_RESETHAND | SA_SIGINFO;

    sigaction(SIGHUP, &mysigaction, NULL);
    sigaction(SIGINT, &mysigaction, NULL);
    sigaction(SIGQUIT, &mysigaction, NULL);
    sigaction(SIGILL, &mysigaction, NULL);
    sigaction(SIGTRAP, &mysigaction, NULL);
    sigaction(SIGABRT, &mysigaction, NULL);
    sigaction(SIGEMT, &mysigaction, NULL);
    sigaction(SIGFPE, &mysigaction, NULL);
    // can't catch SIGKILL
    sigaction(SIGBUS, &mysigaction, NULL);
    sigaction(SIGSEGV, &mysigaction, NULL);
    sigaction(SIGSYS, &mysigaction, NULL);
    sigaction(SIGPIPE, &mysigaction, NULL);
    sigaction(SIGALRM, &mysigaction, NULL);
    sigaction(SIGTERM, &mysigaction, NULL);
    // sigaction(SIGURG, &mysigaction, NULL); // discarded by default
    // can't catch SIGSTOP
    sigaction(SIGTSTP, &mysigaction, NULL);
    // sigaction(SIGCONT, &mysigaction, NULL); // discarded by default
    // sigaction(SIGCHLD &mysigaction, NULL); // discarded by default
    sigaction(SIGTTIN, &mysigaction, NULL);
    sigaction(SIGTTOU, &mysigaction, NULL);
    // sigaction(SIGIO, &mysigaction, NULL); // discarded by default
    sigaction(SIGXCPU, &mysigaction, NULL);
    sigaction(SIGXFSZ, &mysigaction, NULL);
    sigaction(SIGVTALRM, &mysigaction, NULL);
    sigaction(SIGPROF, &mysigaction, NULL);
    // sigaction(SIGWINCH, &mysigaction, NULL); // discarded by default
    // sigaction(SIGINFO, &mysigaction, NULL); // discarded by default
    sigaction(SIGUSR1, &mysigaction, NULL);
    sigaction(SIGUSR2, &mysigaction, NULL);
}

void dg_endtrycatchallerrors ()
{
    signal(SIGHUP, SIG_DFL);     // reset handler to default
    signal(SIGINT, SIG_DFL);     // reset handler to default
    signal(SIGQUIT, SIG_DFL);     // reset handler to default
    signal(SIGILL, SIG_DFL);     // reset handler to default
    signal(SIGTRAP, SIG_DFL);     // reset handler to default
    signal(SIGABRT, SIG_DFL);     // reset handler to default
    signal(SIGEMT, SIG_DFL);     // reset handler to default
    signal(SIGFPE, SIG_DFL);     // reset handler to default
    signal(SIGBUS, SIG_DFL);     // reset handler to default
    signal(SIGSEGV, SIG_DFL);     // reset handler to default
    signal(SIGSYS, SIG_DFL);     // reset handler to default
    signal(SIGPIPE, SIG_DFL);     // reset handler to default
    signal(SIGALRM, SIG_DFL);     // reset handler to default
    signal(SIGTERM, SIG_DFL);     // reset handler to default
    signal(SIGTSTP, SIG_DFL);     // reset handler to default
    signal(SIGTTIN, SIG_DFL);     // reset handler to default
    signal(SIGTTOU, SIG_DFL);     // reset handler to default
    signal(SIGXCPU, SIG_DFL);     // reset handler to default
    signal(SIGXFSZ, SIG_DFL);     // reset handler to default
    signal(SIGVTALRM, SIG_DFL);     // reset handler to default
    signal(SIGPROF, SIG_DFL);     // reset handler to default
    signal(SIGUSR1, SIG_DFL);     // reset handler to default
    signal(SIGUSR2, SIG_DFL);     // reset handler to default
}
*/

const char * dg_catchbadmemoryexit ()
{
    dg_endtrycatchbadmemoryerror();
    return (dg_badmemoryerror);
}

void dg_catchbadmemoryerror (int signum, siginfo_t* pinfo, void* pcontext)
{
    // so what I have to do here is check for addresses to see which subroutine caused the
    //  bad memory error... and return the correct one...
    // syscall(4, 1, (UINT64)"hello\n", 6);
    ((ucontext_t*)(pcontext))->uc_mcontext->__ss.__rip = (UINT64)&dg_catchbadmemoryexit;
}

void dg_trycatchbadmemoryerror ()
{
    struct sigaction mysigaction;
    
    // this would run a lot faster if I used a predifined (static?) constant structure
    mysigaction.sa_sigaction = &dg_catchbadmemoryerror;

    // sa_mask on mac os x is UINT32
    // sigemptyset( &mysigaction.sa_mask );
    mysigaction.sa_mask = 0;

    mysigaction.sa_flags = SA_RESETHAND | SA_SIGINFO;

    sigaction(SIGSEGV, &mysigaction, NULL);
    sigaction(SIGBUS, &mysigaction, NULL);
}

void dg_endtrycatchbadmemoryerror ()
{
    signal(SIGSEGV, SIG_DFL);     // reset handler to default
    signal(SIGBUS, SIG_DFL);     // reset handler to default
}

void dg_catchbadmemoryerror2 (int signum, siginfo_t* pinfo, void* pcontext)
{
    // syscall(4, 1, (UINT64)"hello\n", 6);
    ((ucontext_t*)(pcontext))->uc_mcontext->__ss.__rdi = ((ucontext_t*)(pcontext))->uc_mcontext->__ss.__rip;
    ((ucontext_t*)(pcontext))->uc_mcontext->__ss.__rip = (UINT64)&dg_catchbadmemoryexit2;
}

void dg_trycatchbadmemoryerror2 ()
{
    struct sigaction mysigaction;
    
    // this would run a lot faster if I used a predifined (static?) constant structure
    mysigaction.sa_sigaction = &dg_catchbadmemoryerror2;

    // sa_mask on mac os x is UINT32
    // sigemptyset( &mysigaction.sa_mask );
    mysigaction.sa_mask = 0;

    mysigaction.sa_flags = SA_RESETHAND | SA_SIGINFO;

    sigaction(SIGSEGV, &mysigaction, NULL);
    sigaction(SIGBUS, &mysigaction, NULL);
}

UINT64 dg_fstat(UINT64 fileid, UINT64 pstat)
{
    // 62 old fstat // 189 new fstat
    // old fstat does not do file length correctly
    //return (dg_syscall(189, fileid, pstat, 0, 0, 0));
    return(fstat(fileid, (struct stat*)pstat));
}

UINT64 dg_write(UINT64 fileid, UINT64 pbuf, UINT64 length)
{
    // return (dg_syscall(4, fileid, pbuf, length, 0, 0));
    //  syscall deprecated in OS X 10.11.6
    //  return(syscall(4, fileid, pbuf, length));
    return write(fileid, (const void *)pbuf, length);
}

