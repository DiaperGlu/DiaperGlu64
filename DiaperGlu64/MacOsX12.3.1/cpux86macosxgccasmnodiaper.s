/*
// //////////////////////////////////////////////////////////////////////////////////////
//
//    Copyright 2022 James Patrick Norris
//
//    This file is part of DiaperGlu v5.3.
//
//    DiaperGlu v5.3 is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    DiaperGlu v5.3 is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with DiaperGlu v5.3; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// //////////////////////////////////////////////////////////////////////////////////////

// /////////////////////////////
// James Patrick Norris       //
// www.rainbarrel.com         //
// May 15, 2022               //
// version 5.3                //
// /////////////////////////////
*/

// Tells the compiler to not include the code that does the diaper checks
//  except for this one line, this file is identical to cpux86macosxgccasm.s
_DGLU_NO_DIAPER:

/* Requirments:
   // calling convention
   //  rax = f(rdi, rsi, rdx, rcx, r8, r9, rsp[1], rsp[2], rsp[3], ... )

   // syscall calling convention
   //  rax = sys[rax](rdi, rsi, rdx, rcx, r8, r9, rsp[1], rsp[2], rsp[3], ... )
   
   // registers rbp, rbx, r12, r13, r14, and r15 must be preserved

 
   // Also, there is a 16 byte alignment requirement for certain subroutines
 
   Notes:
    Labels starting with L (L_?) are removed. Perhaps this is why the assembler needs exported symbols to start with _ ?
    But why have the .globl thing if you have the L_ convention?
*/


.text

// const char dg_success[]                    = " - dg_success";
.globl _dg_success
_dg_success:
.asciz " - dg_success"

// const char dg_badmemoryerror[]             = " - bad memory error, process did not have permission to access some memory";
.globl _dg_badmemoryerror
_dg_badmemoryerror:
.asciz " - bad memory error, process did not have permission to access some memory"
/*
.globl _dg_badmemoryerrorputbyte
_dg_badmemoryerrorputbyte:
.asciz " - dg_putbyte error, process could not write to memory at destination address"

.globl _dg_badmemoryerrorputuint16
_dg_badmemoryerrorputuint16:
.asciz " - dg_putuint16 error, process could not write to memory at destination address"

.globl _dg_badmemoryerrorputuint32
_dg_badmemoryerrorputuint32:
.asciz " - dg_putuint32 error, process could not write to memory at destination address"

.globl _dg_badmemoryerrorputuint64
_dg_badmemoryerrorputuint64:
.asciz " - dg_putuint64 error, process could not write to memory at destination address"

.globl _dg_badmemoryerrorgetbyte
_dg_badmemoryerrorgetbyte:
.asciz " - dg_getbyte error, process could not read from memory at source address"

.globl _dg_badmemoryerror2getbyte
_dg_badmemoryerror2getbyte:
.asciz " - dg_getbyte error, process could not write to memory at address used to hold the result"

.globl _dg_badmemoryerrorgetuint16
_dg_badmemoryerrorgetuint16:
.asciz " - dg_getuint16 error, process could not read from memory at source address"

.globl _dg_badmemoryerror2getuint16
_dg_badmemoryerror2getuint16:
.asciz " - dg_getuint16 error, process could not write to memory at address used to hold the result"

.globl _dg_badmemoryerrorgetuint32
_dg_badmemoryerrorgetuint32:
.asciz " - dg_getuint32 error, process could not read from memory at source address"

.globl _dg_badmemoryerror2getuint32
_dg_badmemoryerror2getuint32:
.asciz " - dg_getuint32 error, process could not write to memory at address used to hold the result"

.globl _dg_badmemoryerrorgetuint64
_dg_badmemoryerrorgetuint64:
.asciz " - dg_getuint64 error, process could not read from memory at source address"

.globl _dg_badmemoryerror2getuint64
_dg_badmemoryerror2getuint64:
.asciz " - dg_getuint64 error, process could not write to memory at address used to hold the result"

.globl _dg_badmemoryerrorscanforbyte
_dg_badmemoryerrorscanforbyte:
.asciz " - dg_scanforbyte error, process could read from memory at source address"

.globl _dg_badmemoryerror2scanforbyte
_dg_badmemoryerror2scanforbyte:
.asciz " - dg_scanforbyte error, process could not read from memory at plength"

.globl _dg_badmemoryerrorscanfornotbytereverse
_dg_badmemoryerrorscanfornotbytereverse:
.asciz " - dg_scanfornotbytereverse error, process could read from memory at source address"

.globl _dg_badmemoryerror2scanfornotbytereverse
_dg_badmemoryerror2scanfornotbytereverse:
.asciz " - dg_scanfornotbytereverse error, process could not read from memory at plength"

.globl _dg_badmemoryerrorscanforuint32
_dg_badmemoryerrorscanforuint32:
.asciz " - dg_scanforuint32 error, process could read from memory at source address"

.globl _dg_badmemoryerror2scanforuint32
_dg_badmemoryerror2scanforuint32:
.asciz " - dg_scanforuint32 error, process could not read from memory at plength"

.globl _dg_badmemoryerrorscanforuint64
_dg_badmemoryerrorscanforuint64:
.asciz " - dg_scanforuint64 error, process could read from memory at source address"

.globl _dg_badmemoryerror2scanforuint64
_dg_badmemoryerror2scanforuint64:
.asciz " - dg_scanforuint64 error, process could not read from memory at plength"

.globl _dg_badmemoryerrormovebytes
_dg_badmemoryerrormovebytes:
.asciz " - dg_movebytes error, process could not move memory from source to destination"

.globl _dg_badmemoryerrormovebytesforward
_dg_badmemoryerrormovebytesforward:
.asciz " - dg_movebytesforward error, process could not move memory from source to destination"

.globl _dg_badmemoryerrormovebytesreverse
_dg_badmemoryerrormovebytesreverse:
.asciz " - dg_movebytesforward error, process could not move memory from source to destination"

.globl _dg_badmemoryerrorcomparebytes
_dg_badmemoryerrorcomparebytes:
.asciz " - dg_comparebytes error, process could read from memory at source address"

.globl _dg_badmemoryerror2comparebytes
_dg_badmemoryerror2comparebytes:
.asciz " - dg_comparebytes error, process could not write the result to memory at pflag"

.globl _dg_badmemoryerrorfillwithbyte
_dg_badmemoryerrorfillwithbyte:
.asciz " - dg_fillwithbyte error, process could not write to memory at destination address"

.globl _dg_badmemoryerror1search
_dg_badmemoryerror1search:
.asciz " - dg_search error, process could not read from first character in string to find"

.globl _dg_badmemoryerror2search
_dg_badmemoryerror2search:
.asciz " - dg_search error, process could not scan (read) for first character to find in target string"

.globl _dg_badmemoryerror3search
_dg_badmemoryerror3search:
.asciz " - dg_search error, process could not compare (read read) the string to find to a potential match in the target string"

.globl _dg_badmemoryerror4search
_dg_badmemoryerror4search:
.asciz " - dg_search error, process could not write the result to memory at pcaddrout"

.globl _dg_badmemoryerror1hctwostore
_dg_badmemoryerror1hctwostore:
.asciz " - dg_hctwostore error, process could not write 8 bytes to pdest"

.globl _dg_badmemoryerror2hctwostore
_dg_badmemoryerror2hctwostore:
.asciz " - dg_hctwostore error, process could not write 4 bytes to pdest"

.globl _dg_badmemoryerror3hctwostore
_dg_badmemoryerror3hctwostore:
.asciz " - dg_hctwostore error, process could not write 2 bytes to pdest"

.globl _dg_badmemoryerror4hctwostore
_dg_badmemoryerror4hctwostore:
.asciz " - dg_hctwostore error, process could not write 1 byte to pdest"

.globl _dg_badmemoryerrorreadallbytes
_dg_badmemoryerrorreadallbytes:
.asciz " - dg_readallbytes error, process could not read from memory at source address"

.globl _dg_badmemoryaddbytes
_dg_badmemoryerroraddbytes:
.asciz " - dg_addbytes error, process could read or write memory at source or destination address"
*/
// const char dg_oserror[]                    = " - operating system error";
.globl _dg_oserror
_dg_oserror:
.asciz " - operating system error"

// const char dg_outofmemoryerror[]           = " - out of memory error";
.globl _dg_outofmemoryerror
_dg_outofmemoryerror:
.asciz " - out of memory error"

// const char dg_invalidhandleerror[]         = " - os invalid handle error";
.globl _dg_invalidhandleerror
_dg_invalidhandleerror:
.asciz " - os invalid handle error"

// const char dg_movebytesname[]              = "dg_movebytes";
// .globl _dg_movebytes
// _dg_movebytes:
// .asciz "dg_movebytes"

.globl _dg_catchbadmemoryexit2
 _dg_catchbadmemoryexit2:

    pushq %rdi
    call _dg_endtrycatchbadmemoryerror
    popq %rdi

    /* return dg_badmemoryerror for default case */
    /*  (eventually will just do syscall exit for unknown memory error) */
    leaq _dg_badmemoryerror(%rip), %rax

    leaq _dg_putbyteerroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then1
      // leaq _dg_badmemoryerrorputbyte(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then1:

    leaq _dg_putuint16erroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then2
      // leaq _dg_badmemoryerrorputuint16(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then2:

    leaq _dg_putuint32erroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then3
      // leaq _dg_badmemoryerrorputuint32(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then3:

    leaq _dg_putuint64erroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then4
      // leaq _dg_badmemoryerrorputuint64(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then4:

    leaq _dg_getbyteerroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then5
      // leaq _dg_badmemoryerrorgetbyte(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then5:

    leaq _dg_getuint16erroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then6
      // leaq _dg_badmemoryerrorgetuint16(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then6:

    leaq _dg_getuint32erroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then7
      // leaq _dg_badmemoryerrorgetuint32(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then7:

    leaq _dg_getuint64erroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then8
      // leaq _dg_badmemoryerrorgetuint64(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then8:

    leaq _dg_getbyteerroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then9
      // leaq _dg_badmemoryerror2getbyte(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then9:

    leaq _dg_getuint16erroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then10
      // leaq _dg_badmemoryerror2getuint16(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then10:

    leaq _dg_getuint32erroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then11
      // leaq _dg_badmemoryerror2getuint32(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then11:

    leaq _dg_getuint64erroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then12
      // leaq _dg_badmemoryerror2getuint64(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then12:

    leaq _dg_scanforbyteerroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then13
      // leaq _dg_badmemoryerror2scanforbyte(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then13:

    leaq _dg_scanforbyteerroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then14
      // leaq _dg_badmemoryerrorscanforbyte(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then14:

    leaq _dg_scanforuint32erroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then15
      // leaq _dg_badmemoryerror2scanforuint32(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then15:

    leaq _dg_scanforuint32erroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then16
      // leaq _dg_badmemoryerrorscanforuint32(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then16:

    leaq _dg_scanforuint64erroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then17
      // leaq _dg_badmemoryerror2scanforuint64(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then17:

    leaq _dg_scanforuint64erroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then18
      // leaq _dg_badmemoryerrorscanforuint64(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then18:

    leaq _dg_movebyteserroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then19
      // leaq _dg_badmemoryerrormovebytes(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then19:

    leaq _dg_comparebyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then20
      // leaq _dg_badmemoryerror2comparebytes(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then20:

    leaq _dg_comparebyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then21
      // leaq _dg_badmemoryerrorcomparebytes(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then21:

    leaq _dg_searcherroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then22
      // leaq _dg_badmemoryerror1search(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then22:

    leaq _dg_searcherroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then23
      // leaq _dg_badmemoryerror2search(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then23:

    leaq _dg_searcherroraddress3(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then24
      // leaq _dg_badmemoryerror3search(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then24:

    leaq _dg_searcherroraddress4(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then25
      // leaq _dg_badmemoryerror4search(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then25:

    leaq _dg_fillwithbyteerroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then26
      // leaq _dg_badmemoryerrorfillwithbyte(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then26:

    leaq _dg_hctwostoreerroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then27
      // leaq _dg_badmemoryerror1hctwostore(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then27:

    leaq _dg_hctwostoreerroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then28
      // leaq _dg_badmemoryerror2hctwostore(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then28:

    leaq _dg_hctwostoreerroraddress3(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then29
      // leaq _dg_badmemoryerror3hctwostore(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then29:

    leaq _dg_hctwostoreerroraddress4(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then30
      // leaq _dg_badmemoryerror4hctwostore(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then30:
    
    leaq _dg_readallbyteserroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then31
      // leaq _dg_badmemoryerrorreadallbytes(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then31:
    
    leaq _dg_movebytesforwarderroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then32
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then32:
    
    leaq _dg_movebytesreverseerroraddress(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then33
      // leaq _dg_badmemoryerrormovebytesreverse(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then33:
    
    leaq _dg_scanfornotbytereverseerroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then34
      // leaq _dg_badmemoryerror2scanfornotbytereverse(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then34:

    leaq _dg_scanfornotbytereverseerroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then35
      // leaq _dg_badmemoryerrorscanfornotbytereverse(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then35:
    
    leaq _dg_addbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then36
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then36:
    
    leaq _dg_addbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then37
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then37:
    
    leaq _dg_addbyteserroraddress3(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then39
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then39 :
    
    leaq _dg_shlbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then40
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then40 :
    
    leaq _dg_shlbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then41
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then41 :
    
    leaq _dg_adcbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then42
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then42:
    
    leaq _dg_adcbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then43
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then43:
    
    leaq _dg_adcbyteserroraddress3(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then44
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then44:
    
    leaq _dg_rclbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then45
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then45:
    
    leaq _dg_rclbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then46
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then46:
    
    leaq _dg_sbbbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then47
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then47:
    
    leaq _dg_sbbbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then48
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then48:
    
    leaq _dg_sbbbyteserroraddress3(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then49
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then49:
    
    leaq _dg_andbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then50
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then50:
    
    leaq _dg_andbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then51
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then51:
    
    leaq _dg_orbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then52
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then52:
    
    leaq _dg_orbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then53
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then53:
    
    leaq _dg_xorbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then54
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then54:
    
    leaq _dg_xorbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then55
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then55:
    
    leaq _dg_nandbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then56
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then56:
    
    leaq _dg_nandbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then57
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then57:
    
    leaq _dg_nandbyteserroraddress3(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then58
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then58:
    
    leaq _dg_norbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then59
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then59:
    
    leaq _dg_norbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then60
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then60:
    
    leaq _dg_norbyteserroraddress3(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then61
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then61:
    
    leaq _dg_xnorbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then62
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then62:
    
    leaq _dg_xnorbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then63
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then63:
    
    leaq _dg_xnorbyteserroraddress3(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then64
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then64:
    
    leaq _dg_notbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then65
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then65:
    
    leaq _dg_rcrbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then66
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then66:
    
    leaq _dg_rcrbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then67
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then67:
    
    leaq _dg_shrbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then68
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then68:
    
    leaq _dg_shrbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then69
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then69:
    
    leaq _dg_sarbyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then70
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then70:
    
    leaq _dg_sarbyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then71
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then71:
    
    leaq _dg_reversebyteserroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then72
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then72:
    
    leaq _dg_reversebyteserroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then73
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then73:
    
    leaq _dg_reversebyteserroraddress3(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then74
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then74:
    
    leaq _dg_mulu64tou64serroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then75
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then75:
    
    leaq _dg_mulu64tou64serroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then76
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then76:
    
    leaq _dg_mulu64tou64serroraddress3(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then77
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then77:
    
    leaq _dg_mulu64tou64serroraddress4(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then78
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then78:

    leaq _dg_divu64sbyu64erroraddress1(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then79
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then79:
    
    leaq _dg_divu64sbyu64erroraddress2(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then80
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then80:
    
    leaq _dg_divu64sbyu64erroraddress3(%rip), %rsi
    cmpq %rsi, %rdi
    jnz _dg_catchbadmemoryexit2then81
      // leaq _dg_badmemoryerrormovebytesforward(%rip), %rax
      leaq _dg_badmemoryerror(%rip), %rax
    _dg_catchbadmemoryexit2then81:
    
    /* assuming flags register on stack */
    popfq
    ret

.globl _dg_testasm
_dg_testasm:

    movq %rdi, %rax
    incq %rax
    ret


.globl _dg_testasmimport
_dg_testasmimport:

    leaq _dg_success(%rip), %rax
    ret

.globl _dg_testalignment
_dg_testalignment:

    movq %rsp, %rax
    ret


.globl _dg_testalignmentdf
_dg_testalignmentdf:

    movd %rsp, %xmm0
    ret

    
/*  
    unsigned char* dg_putbyte(
      unsigned char* paddr,   // rdi
      unsigned char c)        // rsi
*/

.globl _dg_putbyte
_dg_putbyte:

.ifndef DGLU_NO_DIAPER
    pushfq // for alignment

    pushq %rsi
    pushq %rdi
    call _dg_trycatchbadmemoryerror2
    popq %rdi
    popq %rsi
.endif

.globl _dg_putbyteerroraddress
_dg_putbyteerroraddress:


    movb %sil, (%rdi)
    
.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
    popfq
.endif

    leaq _dg_success(%rip), %rax
    ret

/*
    unsigned char* dg_putuint16(
      unsigned char* paddr,  // rdi
      UINT16 w)              // rsi
*/


.globl _dg_putuint16
_dg_putuint16:

.ifndef DGLU_NO_DIAPER
    pushfq // for alignment

    pushq %rsi
    pushq %rdi
    call _dg_trycatchbadmemoryerror2
    popq %rdi
    popq %rsi
.endif

    movq %rsi, %rax
.globl _dg_putuint16erroraddress
_dg_putuint16erroraddress:
    movw %ax, (%rdi)

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror

    popfq
.endif

    leaq _dg_success(%rip), %rax
    ret

/*  
    unsigned char* dg_putuint32(
      unsigned char* paddr,  // rdi
      UINT32 u)              // rsi
*/

.globl _dg_putuint32
_dg_putuint32:

.ifndef DGLU_NO_DIAPER
    pushfq // for alignment

    pushq %rsi
    pushq %rdi
    call _dg_trycatchbadmemoryerror2
    popq %rdi
    popq %rsi
.endif

    movq %rsi, %rax
.globl _dg_putuint32erroraddress
_dg_putuint32erroraddress:
    movl %eax, (%rdi)

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror

    popfq
.endif

    leaq _dg_success(%rip), %rax
    ret

/*  
    unsigned char* dg_putuint64(
      unsigned char* paddr,  // rdi
      UINT64 ud)             // rsi
*/

.globl _dg_putuint64
_dg_putuint64:

.ifndef DGLU_NO_DIAPER
    pushfq // for alignment

    pushq %rsi
    pushq %rdi
    call _dg_trycatchbadmemoryerror2
    popq %rdi
    popq %rsi
.endif

.globl _dg_putuint64erroraddress
_dg_putuint64erroraddress:


    movq %rsi, (%rdi)

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
    popfq
.endif

    leaq _dg_success(%rip), %rax
    ret

/*  
    unsigned char* dg_getbyte(
      unsigned char* psrcaddr,  // rdi
      unsigned char* pdestaddr) // rsi
*/

.globl _dg_getbyte
_dg_getbyte:

.ifndef DGLU_NO_DIAPER
    pushfq // for alignment

    pushq %rsi
    pushq %rdi
    call _dg_trycatchbadmemoryerror2
    popq %rdi
    popq %rsi
.endif

.globl _dg_getbyteerroraddress
_dg_getbyteerroraddress:
    movb (%rdi), %al
.globl _dg_getbyteerroraddress2
_dg_getbyteerroraddress2:
    movb %al, (%rsi)

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror

    popfq
.endif

    leaq _dg_success(%rip), %rax
    ret

/*  
    unsigned char* dg_getbyte(
      unsigned char* psrcaddr,  // rdi
      unsigned char* pdestaddr) // rsi
*/

.globl _dg_getuint16
_dg_getuint16:

.ifndef DGLU_NO_DIAPER
    pushfq // for alignment

    pushq %rsi
    pushq %rdi
    call _dg_trycatchbadmemoryerror2
    popq %rdi
    popq %rsi
.endif

.globl _dg_getuint16erroraddress
_dg_getuint16erroraddress:
    movw (%rdi), %ax
.globl _dg_getuint16erroraddress2
_dg_getuint16erroraddress2:
    movw %ax, (%rsi)

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror

    popfq
.endif

    leaq _dg_success(%rip), %rax
    ret

/*  
    unsigned char* dg_getbyte(
      unsigned char* psrcaddr,  // rdi
      unsigned char* pdestaddr) // rsi
*/

.globl _dg_getuint32
_dg_getuint32:

.ifndef DGLU_NO_DIAPER
    pushfq // for allignment

    pushq %rsi
    pushq %rdi
    call _dg_trycatchbadmemoryerror2
    popq %rdi
    popq %rsi
.endif

.globl _dg_getuint32erroraddress
_dg_getuint32erroraddress:
    movl (%rdi), %eax
.globl _dg_getuint32erroraddress2
_dg_getuint32erroraddress2:
    movl %eax, (%rsi)

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror

    popfq
.endif

    leaq _dg_success(%rip), %rax
    ret

/*  
    unsigned char* dg_getbyte(
      unsigned char* psrcaddr,  // rdi
      unsigned char* pdestaddr) // rsi
*/

.globl _dg_getuint64
_dg_getuint64:

.ifndef DGLU_NO_DIAPER
    pushfq // for alignment

    pushq %rsi
    pushq %rdi
    call _dg_trycatchbadmemoryerror2
    popq %rdi
    popq %rsi
.endif

.globl _dg_getuint64erroraddress
_dg_getuint64erroraddress:


    movq (%rdi), %rax
.globl _dg_getuint64erroraddress2
_dg_getuint64erroraddress2:
    movq %rax, (%rsi)

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror

    popfq
.endif

    leaq _dg_success(%rip), %rax
    ret


/* returns the address of the stack pointer before the call */
.globl _dg_getretstackpointer
_dg_getretstackpointer:

   movq %rsp, %rax
   addq $8, %rax    /* for the return address */
   ret


.globl _dg_getframepointer
_dg_getframepointer:

   movq %rbp, %rax
   ret


/* void dg_callcoreforthroutine(Bufferhandle* pBHarrayhead, UINT64 forthcoreroutineaddress) */
.globl _dg_callcoreforthroutine
_dg_callcoreforthroutine:

    /* stack is already aligned for immediately after call if you jump */
    /* and parent routine will clean up return stack */
    jmp *%rsi


/*
    UINT64 dg_bswap(UINT64 u)
*/

.globl _dg_bswap
_dg_bswap:

   movq %rdi, %rax
   bswap %rax
   ret
   
   
/* 
   pints pointer assumed to point to valid memory 
   void dg_udmslashmod(UINT64* pints)    // rdi
   pints points to in:  udlo udhi u1
   pints points to out: ud2lo ud2hi rem
*/

.globl _dg_udmslashmod /* (UINT64* pints) */
_dg_udmslashmod:

    movq 8(%rdi), %rax /* udhi */
    movq $0, %rdx
    movq 16(%rdi), %rcx /* u1 */
    orq %rcx, %rcx
    jz L_udmslashmodthen1

    div %rcx
        movq %rax, 8(%rdi) /* udhi */
        movq (%rdi), %rax /* udlo */
        movq 16(%rdi), %rcx /* u1 */
        
        div %rcx
        movq %rdx, 16(%rdi) /* u1 */
        movq %rax, (%rdi) /* udlo */
        jmp L_udmslashmodthen2
        
L_udmslashmodthen1:
        movq $0xffffffffffffffff, %rax
        movq %rax, (%rdi) /* udlo */
        movq %rax, 8(%rdi) /* udhi */
        movq %rax, 16(%rdi) /* u1 */

L_udmslashmodthen2:
        ret
        
/*
   INT64 dg_twoslash (INT64 n1) // rdi
   returns n1/2
*/

.globl _dg_twoslash
_dg_twoslash:
   
   movq %rdi, %rax
   sarq $1, %rax
   ret
   

/*
    UINT64 dg_lshift (
      UINT64 x1,  // rdi
      UINT64 u)   // rsi
    returns x1 shifted left u times
*/

.globl _dg_lshift
_dg_lshift:
    
    movq %rdi, %rax
    movq %rsi, %rcx
    shlq %cl, %rax
    ret
    

/*
    INT128 dg_mstar (
      INT64 n1,   // rdi
      INT64 n2)   // rsi
   returns n1*n2
   
   INT64 dg_mstar (
   INT64 n1,   // rdi
   INT64 n2,   // rsi
   INT64* presult); // rdx  // really an INT128*
*/

.globl _dg_mstar
_dg_mstar:
    
    movq %rdi, %rax
    xchg %rsi, %rdx // movq %rsi, %rdx
    imul %rdx
    movq %rax, (%rsi)
    movq %rdx, 8(%rsi)
    ret
    
    
/*
    UINT64 dg_rshift (
      UINT64 n1,  // rdi
      UINT64 u)   // rsi
   returns x1 shifted right u times
*/

.globl _dg_rshift
_dg_rshift:
    
    movq %rdi, %rax
    movq %rsi, %rcx
    shrq %cl, %rax
    ret


/*
    UINT128 dg_umstar (
      UINT64 n1,   // rdi
      UINT64 n2)   // rsi
   returns u1*u2
   
   UINT64 dg_umstar(
   UINT64 n1,  // rdi
   UINT64 n2,  // rsi
   UINT64* presult); // rdx  // really UINT128*
*/

.globl _dg_umstar
_dg_umstar:
    
    movq %rdi, %rax
    xchg %rsi, %rdx
    mul %rdx
    movq %rax, (%rsi)
    movq %rdx, 8(%rsi)
    ret

/*
   void dg_umslashmod (UINT64* pints)  // rdi
   pints in: udlo udhi u1
   pints out: u2 u3 dontcare
*/
.globl _dg_umslashmod
_dg_umslashmod:

    movq (%rdi), %rax
    movq 8(%rdi), %rdx
    movq 16(%rdi), %rcx
    orq %rcx, %rcx
    jz L_umslashmodthen1
    cmpq %rcx, %rdx
    jnc L_umslashmodthen1
    div %rcx
    movq %rdx, (%rdi)
    movq %rax, 8(%rdi)
    jmp L_umslashmodthen2

L_umslashmodthen1:

    movq $0xFFFFFFFFFFFFFFFF, %rax
    movq %rax, (%rdi)
    movq %rax, 8(%rdi)

L_umslashmodthen2:

    ret

/*
   UINT64 dg_uaddclipped (
    UINT64 u1,          // rdi 
    UINT64 u2)          // rsi
    
   // this is for preventing overflow errors
   
*/

.globl _dg_uaddclipped
_dg_uaddclipped:
  movq %rdi, %rax
  addq %rsi, %rax
  jnc L_dg_uaddclipped
    xorq %rax, %rax
    decq %rax
L_dg_uaddclipped:
    ret
    
/*
const char* dg_scanforbyte (
    void* pbuf,       // rdi
    UINT64* plength,  // rsi
    UINT64 value)     // rdx
*/
    
.globl _dg_scanforbyte
_dg_scanforbyte:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rax // value
    popq %rsi // plength
    popq %rdi // pbuf
.endif

    pushfq      /* save direction flag, required under win32, just in case for others */
                /* mac os requires direction flag set to forward */

.globl _dg_scanforbyteerroraddress1
_dg_scanforbyteerroraddress1:
    movq (%rsi), %rcx      /* rcx = length */
    movq $-1, (%rsi)       /* -1 length passed out means not found */
    movq %rcx, %rdx        /* rdx = length also */
    cld
.globl _dg_scanforbyteerroraddress2
_dg_scanforbyteerroraddress2:
    repne    
    scasb    
    jnz L_dg_scanforbytethen1
    
      decq %rdx
      subq %rcx, %rdx
      movq %rdx, (%rsi)

L_dg_scanforbytethen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif

    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
const char* dg_scanforuint32 (
    void* pbuf,         // rdi
    UINT64* plength,    // rsi
    UINT64 value);      // rdx
*/

.globl _dg_scanforuint32
_dg_scanforuint32:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rax // value
    popq %rsi // plength
    popq %rdi // pbuf
.endif

    pushfq      /* save direction flag, required under win32, just in case for others */
                /* mac os requires direction flag set to forward */

.globl _dg_scanforuint32erroraddress1
_dg_scanforuint32erroraddress1:
    movq (%rsi), %rcx      /* rcx = length */
    movq $-1, (%rsi)       /* -1 length passed out means not found */
    movq %rcx, %rdx        /* rdx = length also */
    cld
.globl _dg_scanforuint32erroraddress2
_dg_scanforuint32erroraddress2:
    repne
    scasl
    jnz L_dg_scanforuint32then1
    
      decq %rdx
      subq %rcx, %rdx
      movq %rdx, (%rsi)

L_dg_scanforuint32then1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
            
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
const char* dg_scanforuint64 (
    void* pbuf,         // rdi
    UINT64* plength,    // rsi
    UINT64 value);      // rdx
*/

.globl _dg_scanforuint64
_dg_scanforuint64:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rax // value
    popq %rsi // plength
    popq %rdi // pbuf
.endif

    pushfq      /* save direction flag, required under win32, just in case for others */
                /* mac os requires direction flag set to forward */

.globl _dg_scanforuint64erroraddress1
_dg_scanforuint64erroraddress1:
    movq (%rsi), %rcx      /* rcx = length */
    movq $-1, (%rsi)       /* -1 length passed out means not found */
    movq %rcx, %rdx        /* rdx = length also */
    cld
.globl _dg_scanforuint64erroraddress2
_dg_scanforuint64erroraddress2:
    repne       
    scasq
    jnz L_dg_scanforuint64then1
    
      decq %rdx
      subq %rcx, %rdx
      movq %rdx, (%rsi)

L_dg_scanforuint64then1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
            
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_movebytes (
        unsigned char* psrc,    // rdi
        unsigned char* pdest,   // rsi
        UINT64 stringlength);   // rdx
*/

.globl _dg_movebytes
_dg_movebytes:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
.endif

    pushfq      /* -0x10  save direction flag, required under win32, just in case for others */
                /* mac os requires direction flag set to forward */

    movq %rdx, %rcx  /* stringlength->rcx */
    cld 
    cmpq %rsi, %rdi
    jc L_dg_movebytesthen1

      addq %rcx, %rdi
      addq %rcx, %rsi
      decq %rdi /* post decrement with std need this */
      decq %rsi /* post decrement with std need this */
      std

L_dg_movebytesthen1:
.globl _dg_movebyteserroraddress
_dg_movebyteserroraddress:
    rep
    movsb

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_movebytesforward (
        unsigned char* psrc,    // rdi
        unsigned char* pdest,   // rsi
        UINT64 stringlength);   // rdx
*/

.globl _dg_movebytesforward
_dg_movebytesforward:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
.endif

    pushfq      /* -0x10  save direction flag, required under win32, just in case for others */
                /* mac os requires direction flag set to forward */

    movq %rdx, %rcx  /* stringlength->rcx */
    cld 
    
.globl _dg_movebytesforwarderroraddress
_dg_movebytesforwarderroraddress:
    rep
    movsb

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_movebytesreverse (
        unsigned char* psrc,    // rdi
        unsigned char* pdest,   // rsi
        UINT64 stringlength);   // rdx
*/

.globl _dg_movebytesreverse
_dg_movebytesreverse:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
.endif

    pushfq      /* -0x10  save direction flag, required under win32, just in case for others */
                /* mac os requires direction flag set to forward */

    movq %rdx, %rcx  /* stringlength->rcx */
    
    addq %rcx, %rdi
    addq %rcx, %rsi
    decq %rdi /* post decrement with std need this */
    decq %rsi /* post decrement with std need this */
    std

.globl _dg_movebytesreverseerroraddress
_dg_movebytesreverseerroraddress:
    rep
    movsb

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


.globl _dg_moveuint64s
_dg_moveuint64s:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
.endif

    pushfq      /* -0x10  save direction flag, required under win32, just in case for others */
                /* mac os requires direction flag set to forward */

    movq %rdx, %rcx  /* stringlength->rcx */
    cld 
    cmpq %rsi, %rdi
    jc L_dg_moveuint64sthen1

      shlq $3, %rdx
      addq %rdx, %rdi
      addq %rdx, %rsi
      decq %rdi /* post decrement with std need this */
      decq %rsi /* post decrement with std need this */
      std

L_dg_moveuint64sthen1:
.globl _dg_moveuint64serroraddress
_dg_moveuint64serroraddress:
    rep
    movsq

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif

    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    DGLU_API const char* dg_comparebytes (
        unsigned char* pstring1,    // rdi
        UINT64 string1length,       // rsi
        unsigned char* pstring2,    // rdx
        UINT64 string2length,       // rcx
        INT64* pflag);              // r8
*/

/*
    JN Dec 27, 2011, _dg_comparebytes min branch function for length fixed
*/
.globl _dg_comparebytes
_dg_comparebytes:

    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx

.ifndef DGLU_NO_DIAPER
    pushq %r8

    call _dg_trycatchbadmemoryerror2

    popq %r8   // pflag
.endif
    popq %rdx  // length2
    popq %rdi  // pstring2
    popq %rcx  // length1
    popq %rsi  // pstring1
    movq %rcx, %r9 // r9 now has length1

    pushfq      /* -0x10  save direction flag, required under win32, just in case for others */
                /* mac os x requires direction flag left in forward direction */

    /* set compare flag to default which is bad memory */
.globl _dg_comparebyteserroraddress1
_dg_comparebyteserroraddress1:
    movq $-2, (%r8)

    /* protected compare bytes */

    //    unsigned char* pstring1,    // rsi
    //    unsigned char* pstring2,    // rdi
    //    UINT64 string1length,       // r9 and rcx
    //    UINT64 string2length,       // rdx

    cmpq %rdx, %rcx            /* length1 - length2 */
    jc L_dg_comparebytesthen0  /* if length1 u< length2 keep length1 - branch changed from jnc to jc Dec 27, 2011 */
    movq %rdx, %rcx            /* length2->rcx */
L_dg_comparebytesthen0:

    cld                        /* this was missing */
.globl _dg_comparebyteserroraddress2
_dg_comparebyteserroraddress2:
    repe                   
    cmpsb                  
    je L_dg_comparebytesthen1   
    movq $1, %rax
    jnc L_dg_comparebytesthen2  
    movq $-1, %rax
    jmp L_dg_comparebytesthen2  

L_dg_comparebytesthen1:             
    movq %r9, %rax          /* length1->rax */
    cmpq %rdx, %rax         /* compare rax with length2 */
    movq $0, %rax
    je L_dg_comparebytesthen2   
    movq $1, %rax
    jnc L_dg_comparebytesthen2  
    movq $-1, %rax

L_dg_comparebytesthen2:
    movq %rax, (%r8)       /* move rax->(pflag) */

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif

    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
unsigned char* dg_search (
    unsigned char* caddr1,      // 08 rdi = target string to search
    UINT32 u1,                  // 0C rsi = length of target string
    unsigned char* caddr2,      // 10 rdx = string to search for in target string
    UINT32 u2,                  // 14 rcx = length of string to search for
    unsigned char** pcaddrout)  // 18 r8 = pointer to found string or pointer to null
    
returns dg_success on success
returns dg_badmemoryerror if memory at strings is not part of current process
*/

.globl _dg_search
_dg_search:
    
    /* enter full standard frame */
//    pushl %ebp  /* +0x00 */
//    movl %esp, %ebp
//    pushl %ebx  /* -0x04 */
//    pushl %esi  /* -0x08 */
//    pushl %edi  /* -0x0C */
//    pushfl      /* -0x10  save direction flag, required under win32, just in case for others */

    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx
.ifndef DGLU_NO_DIAPER
    pushq %r8

    call _dg_trycatchbadmemoryerror2

    popq %r8   // 18 pcaddrout
.endif
    popq %r9   // 14 length2
    popq %rdx  // 10 caddr2
    popq %r11  // 0C length1
    popq %r10  // 08 caddr1

    pushfq      /* -0x10  save direction flag, required under win32, just in case for others */
                /* mac os x requires direction flag left in forward direction */
    /* if length of string to search for is 0, then return a match */
    xorq %rax, %rax
    // movl 0x14(%ebp), %ecx /* u2 */
    
    cmpq %rax, %r9
    jz L_dg_searchsubthen2
    
    /* if string we are looking for is longer than target string, return not found */
    cmpq %r9, %r11
    jc L_dg_searchsubthen1

    /*
       to keep compare from going off end, and to avoid scanning unneccesary bytes
        going to shorten scan length of target string to only look at positions
        where the shorter string can actually start at
    */

    movq %r9, %rcx
    decq %rcx
    subq %rcx, %r11

    /* set direction flag to forwards so string operations go up in memory */
    cld
    
L_dg_searchsubbegin1:

    /* get first character from string to find */
 //   movl 0x0C(%ebp), %ecx /* numlefttocheck */
    movq %r11, %rcx
 //   movl 0x10(%ebp), %ebx /* caddr2 */
 //   movb (%ebx), %al
.globl _dg_searcherroraddress1
_dg_searcherroraddress1:
    movb (%rdx), %al
    
    /* scan for that character in target string */
 //   movl 0x08(%ebp), %edi /* caddr1 */
    movq %r10, %rdi
.globl _dg_searcherroraddress2
_dg_searcherroraddress2:
    repne
    scasb
    movq $0, %rax /* clear eax without altering state of zero flag */
    jne L_dg_searchsubthen1
    
    /* update position in target string */
 //   movl %ecx, 0x0C(%ebp) /* numlefttocheck */
    movq %rcx, %r11
 //   movl %edi, 0x08(%ebp) /* caddr1 */
    movq %rdi, %r10

    /* compare strings */
 //   movl 0x14(%ebp), %ecx /* u2 */
    movq %r9, %rcx
 //   movl 0x10(%ebp), %esi /* caddr2 */
    movq %rdx, %rsi
    incq %rsi /* first character already checked and edi points to one after match */
    decq %rcx
    orq %rcx, %rcx
    jz L_dg_searchsubthen2
.globl _dg_searcherroraddress3
_dg_searcherroraddress3:
    repe
    cmpsb
    jz L_dg_searchsubthen2
    
 //   movl 0x08(%ebp), %edi /* caddr1 */
//    movq %r10, %rdi
 //   movl 0x0C(%ebp), %ecx /* numlefttocheck */
//    movq %r11, %rcx
    orq %r11, %r11
    jz L_dg_searchsubthen1
    jnz L_dg_searchsubbegin1

L_dg_searchsubthen2:
//    movl 0x08(%ebp), %eax /* result = caddr1 saved from before compare */
    movq %r10, %rax
    decq %rax
    
L_dg_searchsubthen1:
    /* set found not found pointer with result */
//    movl 0x18(%ebp), %ecx /* pcaddrout */
//    movl %eax, (%ecx)
.globl _dg_searcherroraddress4
_dg_searcherroraddress4:
    movq %rax, (%r8)
    
    /* disable memory protection */
.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif

    leaq _dg_success(%rip), %rax
    popfq
    ret


/* void dg_savequitstate (UINT64* pquitstate) */
.globl _dg_savequitstate
_dg_savequitstate:

//  rdi = pquitstate
    
    movq %rbp, 0x00(%rdi)
    movq %rsp, 0x08(%rdi)
    addq $8, 0x08(%rdi) // to drop the return address
    pushfq
    popq %rax
    movq %rax, 0x10(%rdi)
    ret


/* void dg_restorequitstate (UINT64* pquitstate) */
.globl _dg_restorequitstate
_dg_restorequitstate:
    
    /* need to jump so that stack frame is correct
        we are eating everything including first return and
        whatever parameters from first call out of quit
    */
      popq %rax /* return address */
//    rdi = pquitstate
    
      movq 0x10(%rdi), %rdx  /* doing eflags first */
      pushq %rdx
      popfq
      movq 0x08(%rdi), %rsp  /* restore stack to state without pquitstate on it */
      movq 0x00(%rdi), %rbp    
      jmp *%rax


.globl _dg_callprocaddress
_dg_callprocaddress:
    
    /* enter frame */
    pushq %rbp
    movq %rsp, %rbp
    pushq %rcx
    pushq %rdx

    movq %rsi, %r11
    
    /* alignment  frame   what it is */
    /* rcx                function address */
    /* rdx                pdatastacklength
    /* rsi                n = number of paramenters */
    /* rdi                pdatastack */
    
    /*            +8      return address */
    /*            +0      saved ebp */
    /*            -8      function address */
    /*            -0x10   pdatastacklength */
    
    // so at this point we still need 0 bytes to get to 16 byte alignment, but just in case
    andq $-0x10, %rsp

    // if number of parameters is > 6 and odd, then do need adjust rsp by 8
    // if number of parameters is <= 6 or even, then you do not need to adjust rsp by 8
    testq $1, %rsi
    jnz L_dg_callprocaddressthen1 // branch if odd to rsp<-rsp-8
    cmpq $7, %rsi
    jc L_dg_callprocaddressthen2 // branch if <7 to don't adjust rsp
L_dg_callprocaddressthen1:
    subq $8, %rsp
L_dg_callprocaddressthen2:

    /* copy parameters from data stack to return stack if needed */
L_dg_callprocaddressbegin1:
    cmpq $7, %rsi
    jc L_dg_callprocaddressthen3 // while number of paramters >=7 push parameters

    pushq (%rdi)
    addq $8, %rdi
    decq %rsi
    jmp L_dg_callprocaddressbegin1

L_dg_callprocaddressthen3:

    /* copy parameters to regs if needed */
    cmpq $6, %r11 // see if there are at least 6 parameters
    jc L_dg_callprocaddressthen4
      movq (%rdi), %r9
      addq $8, %rdi
L_dg_callprocaddressthen4:

    cmpq $5, %r11 // see if there are at least 5 parameters
    jc L_dg_callprocaddressthen5
      movq (%rdi), %r8
      addq $8, %rdi
L_dg_callprocaddressthen5:

    cmpq $4, %r11 // see if there are at least 4 parameters
    jc L_dg_callprocaddressthen6
      movq (%rdi), %rcx
      addq $8, %rdi
L_dg_callprocaddressthen6:

    cmpq $3, %r11 // see if there are at least 3 parameters
    jc L_dg_callprocaddressthen7
      movq (%rdi), %rdx
      addq $8, %rdi
L_dg_callprocaddressthen7:

    cmpq $2, %r11 // see if there are at least 2 parameters
    jc L_dg_callprocaddressthen8
      movq (%rdi), %rsi
      addq $8, %rdi
L_dg_callprocaddressthen8:

    cmpq $1, %r11 // see if there are at least 1 parameters
    jc L_dg_callprocaddressthen9
      movq (%rdi), %rdi
L_dg_callprocaddressthen9:


     /* drop parameters from the data stack - the downside is when there is an error you lose the stack frame
         this is here so that you can call a proc which modifies the data stack */
     movq -0x10(%rbp), %rax
     addq $2, %r11
     shl $3, %r11
     subq %r11, (%rax)
     
     /* call proc */
     call *-0x08(%rbp)
     
     /* drops everything left on return stack
         this is compatible with both cdecl, and stdcall
         also, registers rax and rdx are left untouched which is compatible with ret UINT128 */
     movq %rbp, %rsp
     popq %rbp
     ret
     
.globl _dg_callprocaddressretuint128
_dg_callprocaddressretuint128:
     pushq %r8
     call _dg_callprocaddress
     popq %r8
     movq %rdx, (%r8)
     ret


.globl _dg_calldfpprocaddress
_dg_calldfpprocaddress:
.globl _dg_calldfpprocaddressretuint128
_dg_calldfpprocaddressretuint128:
    
    /* enter frame */
    pushq %rbp
    movq %rsp, %rbp
    pushq %rcx
    pushq %rdx
    pushq %r8
    pushq %rdi

    movq %rsi, %r11
    
    /* alignment  frame   what it is */
    /* r8                 number of double floating point parameters
    /* rcx                function address */
    /* rdx                pdatastacklength
    /* rsi                n = number of paramenters */
    /* rdi                pdatastack */
    
    /*            +8      return address */
    /*            +0      saved ebp */
    /*            -8      function address */
    /*            -0x10   pdatastacklength */
    /*            -0x18   number of floating point parameters */
    /*            -0x20   pdatastack */
    
    // so at this point we still need 0 bytes to get to 16 byte alignment, but just in case
    andq $-0x10, %rsp

    // if number of parameters is > 6
    //  or the number of floating point parameters is > 8
    //  and the number of those parameters 'extra' parameters is odd,
    //  then do need to adjust rsp by 8
    // otherwise you do need to not adjust rsp by 8

    // if the number of floating point parameters is > 8 and odd

    xorq %rax, %rax  // clear rax
    cmpq $7, %rsi    // if rsi >= 7 then
    jc L_dg_calldfpprocaddressthen1
      movq %rsi, %rax
      subq $6, %rax  // rax = rsi - 6
 L_dg_calldfpprocaddressthen1:
    cmpq $9, %r8     // if r8 >= 9 then
    jc L_dg_calldfpprocaddressthen2
      addq %r8, %rax
      subq $8, %rax  // rax = rax + r8 - 8
 L_dg_calldfpprocaddressthen2:
    testq $1, %rax   // if number of extra parameters is odd - could just look at al
    jz L_dg_calldfpprocaddressthen0
     subq $8, %rsp   // adjust rsp for odd extra number of parameters
 L_dg_calldfpprocaddressthen0:


    /* copy floating point parameters from data stack to return stack if needed */
L_dg_calldfpprocaddressbegin2:
    cmpq $9, %r8
    jc L_dg_calldfpprocaddressthen18 // while number of floating point paramters >=9 push parameters

    pushq (%rdi)
    addq $8, %rdi
    decq %r8
    jmp L_dg_calldfpprocaddressbegin2

L_dg_calldfpprocaddressthen18:

    cmpq $8, %r8 // see if there are at least 8 floating point parameters
    jc L_dg_calldfpprocaddressthen10
      movq (%rdi), %xmm7
      addq $8, %rdi
L_dg_calldfpprocaddressthen10:

    cmpq $7, %r8 // see if there are at least 7 floating point parameters
    jc L_dg_calldfpprocaddressthen11
      movq (%rdi), %xmm6
      addq $8, %rdi
L_dg_calldfpprocaddressthen11:

    cmpq $6, %r8 // see if there are at least 6 floating point parameters
    jc L_dg_calldfpprocaddressthen12
      movq (%rdi), %xmm5
      addq $8, %rdi
L_dg_calldfpprocaddressthen12:

    cmpq $5, %r8 // see if there are at least 5 floating point parameters
    jc L_dg_calldfpprocaddressthen13
      movq (%rdi), %xmm4
      addq $8, %rdi
L_dg_calldfpprocaddressthen13:

    cmpq $4, %r8 // see if there are at least 4 floating point parameters
    jc L_dg_calldfpprocaddressthen14
      movq (%rdi), %xmm3
      addq $8, %rdi
L_dg_calldfpprocaddressthen14:

    cmpq $3, %r8 // see if there are at least 3 floating point parameters
    jc L_dg_calldfpprocaddressthen15
      movq (%rdi), %xmm2
      addq $8, %rdi
L_dg_calldfpprocaddressthen15:

    cmpq $2, %r8 // see if there are at least 2 floating point parameters
    jc L_dg_calldfpprocaddressthen16
      movq (%rdi), %xmm1
      addq $8, %rdi
L_dg_calldfpprocaddressthen16:

    cmpq $1, %r8 // see if there are at least 1 floating point parameters
    jc L_dg_calldfpprocaddressthen17
      movq (%rdi), %xmm0
      addq $8, %rdi
L_dg_calldfpprocaddressthen17:

    /* copy parameters from data stack to return stack if needed */
L_dg_calldfpprocaddressbegin1:
    cmpq $7, %rsi
    jc L_dg_calldfpprocaddressthen3 // while number of paramters >=7 push parameters

    pushq (%rdi)
    addq $8, %rdi
    decq %rsi
    jmp L_dg_calldfpprocaddressbegin1

L_dg_calldfpprocaddressthen3:

    /* copy parameters to regs if needed */
    cmpq $6, %r11 // see if there are at least 6 parameters
    jc L_dg_calldfpprocaddressthen4
      movq (%rdi), %r9
      addq $8, %rdi
L_dg_calldfpprocaddressthen4:

    cmpq $5, %r11 // see if there are at least 5 parameters
    jc L_dg_calldfpprocaddressthen5
      movq (%rdi), %r8
      addq $8, %rdi
L_dg_calldfpprocaddressthen5:

    cmpq $4, %r11 // see if there are at least 4 parameters
    jc L_dg_calldfpprocaddressthen6
      movq (%rdi), %rcx
      addq $8, %rdi
L_dg_calldfpprocaddressthen6:

    cmpq $3, %r11 // see if there are at least 3 parameters
    jc L_dg_calldfpprocaddressthen7
      movq (%rdi), %rdx
      addq $8, %rdi
L_dg_calldfpprocaddressthen7:

    cmpq $2, %r11 // see if there are at least 2 parameters
    jc L_dg_calldfpprocaddressthen8
      movq (%rdi), %rsi
      addq $8, %rdi
L_dg_calldfpprocaddressthen8:

    cmpq $1, %r11 // see if there are at least 1 parameters
    jc L_dg_calldfpprocaddressthen9
      movq (%rdi), %rdi
L_dg_calldfpprocaddressthen9:

     /* drop parameters from the data stack - the downside is when there is an error you lose the stack frame
         this is here so that you can call a proc which modifies the data stack */
     movq -0x10(%rbp), %rax
     addq $3, %r11
     addq -0x18(%rbp), %r11
     shl $3, %r11
     subq %r11, (%rax)
     
     /* call proc */
     call *-0x08(%rbp)

     /* move results to the data stack */
     // movq -0x10(%rbp), %rdi
     // addq $0x10, (%rdi)
     // movq -0x20(%rbp), %rdi
     // movq %rax, (%rdi)        // so int result is on bottom
     // movq %xmm0, 0x10(%rdi)   // and double float result is on top
     
     /* drops everything left on return stack
         this is compatible with both cdecl, and stdcall
         also, registers rax and rdx are left untouched which is compatible with ret UINT128 */
     movq %rbp, %rsp
     popq %rbp
     ret


/*
const char* dg_fillwithbyte (
    unsigned char* pbuf,   // rdi
    UINT32 length,         // rsi
    unsigned char cvalue)  // rdx
*/
    
.globl _dg_fillwithbyte
_dg_fillwithbyte:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rsi
    popq %rdi
.endif

    pushfq
    
    /* protected fill with byte */
    movq %rsi, %rcx      /* length */
    movq %rdx, %rax      /* value */
    cld
.globl _dg_fillwithbyteerroraddress
_dg_fillwithbyteerroraddress:
    repne    
    stosb    

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif

    leaq _dg_success(%rip), %rax
    popfq
    ret
    


/*
const char* dg_readallbytes (
    unsigned char* pbuf,   // rdi
    UINT32 length)         // rsi
*/
    
.globl _dg_readallbytes
_dg_readallbytes:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rsi
    popq %rdi
.endif

    pushfq
    
    /* protected fill with byte */
    movq %rsi, %rcx      /* length */
    movq %rdi, %rsi      /* address */
    cld
.globl _dg_readallbyteserroraddress
_dg_readallbyteserroraddress:
    repne
    lodsb

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif

    leaq _dg_success(%rip), %rax
    popfq
    ret
    
/*
    void dg_forthfsfrom (Bufferhandle* pBHarrayhead)
*/

.globl _dg_forthfsfrom
_dg_forthfsfrom:
   
    /* enter frame */ /* actually don't need to save any registers */
    // rdi = pBHarrayhead
    pushq %rbp
    movq %rsp, %rbp

    pushq %rax // making memory location for the result
    fstpl -0x08(%rbp)
    popq %rsi
    
    /* force alignment of return stack to 16 bytes for calling subroutines with 2 parameters */
    andq $0xfffffffffffffff0, %rsp
    subq $8, %rsp
    
    call _dg_pushdatastack

    xorq %rax, %rax // returning 0 even though it's void
    
    /* exit frame */
    movq %rbp, %rsp
    popq %rbp
    ret

/*
    void dg_forthf32from (Bufferhandle* pBHarrayhead)
*/

.globl _dg_forthf32from
_dg_forthf32from:

/* enter frame */ /* actually don't need to save any registers */
    // rdi = pBHarrayhead
    pushq %rbp
    movq %rsp, %rbp

    xorq %rsi, %rsi // clear hi bits
    pushq %rsi
    fstps -0x04(%rbp)
    movl -0x04(%rbp), %esi
    
    /* force alignment of return stack to 16 bytes for calling subroutines with 2 parameters */
    andq $0xfffffffffffffff0, %rsp
    subq $8, %rsp
    
    call _dg_pushdatastack

    xorq %rax, %rax // returning 0 even though it's void
    
    /* exit frame */
    movq %rbp, %rsp
    popq %rbp
    ret

.globl _dg_forthfp0from
_dg_forthfp0from:
   
    /* enter frame */ /* actually don't need to save any registers */
    // rdi = pBHarrayhead
    pushq %rbp
    movq %rsp, %rbp
    
    /* force alignment of return stack to 16 bytes for calling subroutines with 2 parameters */
    andq $0xfffffffffffffff0, %rsp
    subq $8, %rsp

    movd %xmm0, %rsi
    
    call _dg_pushdatastack

    xorq %rax, %rax // returning 0 even though it's void
    
    /* exit frame */
    movq %rbp, %rsp
    popq %rbp
    ret

.globl _dg_forthtofp0
_dg_forthtofp0:
   
    /* enter frame */ /* actually don't need to save any registers */
    // rdi = pBHarrayhead
    pushq %rbp
    movq %rsp, %rbp
    
    /* force alignment of return stack to 16 bytes for calling subroutines with 1 parameters */
    andq $0xfffffffffffffff0, %rsp
    subq $8, %rsp
    
    call _dg_popdatastack

    movd %rax, %xmm0
    
    /* exit frame */
    movq %rbp, %rsp
    popq %rbp
    ret

.globl _dg_tofromxmm0
_dg_toxmm0:
    movd %xmm0, %rax
    movd %rdi, %xmm0
    ret

.globl _dg_tofromxmm1
_dg_tofromxmm1:
    movd %xmm1, %rax
    movd %rdi, %xmm1
    ret

.globl _dg_lobit
_dg_lobit:
    orq %rdi, %rdi
    jz L_dg_lobitthen1
    bsf %rdi, %rax
    ret
L_dg_lobitthen1:
    xorq %rax, %rax
    notq %rax
    ret

.globl _dg_hibit
_dg_hibit:
    orq %rdi, %rdi
    jz L_dg_lobitthen1
    bsr %rdi, %rax
    ret

.globl _dg_countbits
_dg_countbits:
    popcnt %rdi, %rax
    ret

/*
    UINT128 dg_touleb128 (UINT64 u, UINT128* presult)
*/

.globl _dg_touleb128
_dg_touleb128:

    // rdi = u, rsi = presult
    xorq %rdx, %rdx
    xorq %rax, %rax
    xorb %ch, %ch

_dg_touleb128_begin:
      incb %ch
      shrdq $7, %rdx, %rax
      shrdq $7, %rdi, %rdx
      shrq $7, %rdi

    jz _dg_touleb128_repeat
      shrdq $1, %rdx, %rax
      stc
      rcrq $1, %rdx
      jmp _dg_touleb128_begin  
    
_dg_touleb128_repeat: 
    shrdq $1, %rdx, %rax    
    clc
    rcrq $1, %rdx

    // shrd shift is limited to 63 bits so
    cmp $9, %ch

    jnc _dg_touleb128_then

        //  if count is <= 8 need to do this
        movq %rdx, %rax // copy rdx to rax.. this is shift 64
        xorq %rdx, %rdx
        movb %ch, %dl
        bswapq %rdx

        movb $8, %cl
        subb %ch, %cl
        shlb $3, %cl
        shrq %cl, %rax // count = 0 case = no shift
        movq %rax, (%rsi)
        movq %rdx, 8(%rsi)
        ret
      

_dg_touleb128_then:

    movb $0x10, %cl
    subb %ch, %cl
    shlb $3, %cl
    shrdq %cl, %rdx, %rax
    shrq %cl, %rdx

    bswapq %rdx
    movb %ch, %dl
    bswapq %rdx
    movq %rax, (%rsi)
    movq %rdx, 8(%rsi)
    
    ret  // rdx:rax = result


/*
    UINT128 dg_shrd (
        UINT128* pu,   // RDI   // RSI : RDI
        UINT64 count);  // RSI
*/


.globl _dg_shrd
_dg_shrd:

    // shrdq is limited to 63 bits so, doing >=64 this way
    movq %rsi, %rcx
    testb $0x40, %cl
    jz _dg_shrd_then1 

        // shifting 64 or more bits
        subb $0x40, %cl
        movq 8(%rdi), %rax // movq %rsi, %rax
        xorq %rdx, %rdx
        shrq %cl, %rax     // shift hardware masked to be from 0 to 63
        movq %rax, (%rdi)
        movq %rdx, 8(%rdi)
        ret 

_dg_shrd_then1:

    // shifting 63 or less bits
    movq (%rdi), %rax   // movq %rdi, %rax
    movq 8(%rdi), %rdx  // movq %rsi, %rdx
    shrdq %cl, %rdx, %rax  // shift hardware masked to be from 0 to 63
    shrq %cl, %rdx         // shift hardware masked to be from 0 to 63
    movq %rax, (%rdi)
    movq %rdx, 8(%rdi)
    ret


/*
    UINT128 dg_ashrd (
        UINT128* pu,   // RDI   // RSI : RDI
        UINT64 count);  // RSI
*/

.globl _dg_ashrd
_dg_ashrd:

    // shrdq is limited to 63 bits so, doing >=64 this way
    movq %rsi, %rcx    // movb %dl, %cl
    testb $0x40, %cl
    jz _dg_ashrd_then1 

        // shifting 64 or more bits
        // subb $0x40, %cl  // not needed due to hardware masking
        movq 8(%rdi), %rax   // movq %rsi, %rax
        movq %rax, %rdx
        sarq $0x3F, %rdx
        sarq %cl, %rax     // shift hardware masked to be from 0 to 63
        movq %rax, (%rdi)
        movq %rdx, 8(%rdi)
        ret 

_dg_ashrd_then1:

    // shifting 63 or less bits
    movq (%rdi), %rax      // movq %rdi, %rax
    movq 8(%rdi), %rdx     // movq %rsi, %rdx
    shrdq %cl, %rdx, %rax  // shift hardware masked to be from 0 to 63
    sarq %cl, %rdx         // shift hardware masked to be from 0 to 63
    movq %rax, (%rdi)
    movq %rdx, 8(%rdi)
    ret


/*
    UINT128 dg_shld (
        UINT128* pu,    // RDI   // RSI : RDI
        UINT64 count);  // RSI
*/
.globl _dg_shld
_dg_shld:

    // shrdq is limited to 63 bits so, doing >=64 this way
    movq %rsi, %rcx   // movb %dl, %cl
    testb $0x40, %cl
    jz _dg_shld_then1

        // subb $0x40, %cl // not needed due to hardware masking
        movq (%rdi), %rdx  // movq %rdi, %rdx
        xorq %rax, %rax
        shlq %cl, %rdx     // shift hardware masked to be from 0 to 63
        movq %rax, (%rdi)
        movq %rdx, 8(%rdi)
        ret 

_dg_shld_then1:

    movq (%rdi),  %rax     // movq %rdi, %rax
    movq 8(%rdi), %rdx     // movq %rsi, %rdx
    shldq %cl, %rax, %rdx  // shift hardware masked to be from 0 to 63
    shlq %cl, %rax         // shift hardware masked to be from 0 to 63
    movq %rax, (%rdi)
    movq %rdx, 8(%rdi)
    ret
/*
    UINT64 dg_gethctwolength (UINT128* pud); rdi  // rsi : rdi
*/

.globl _dg_gethctwolength
_dg_gethctwolength:

    xorq %rax, %rax
    // bswapq %rsi
    movb 15(%rdi), %al  // movb %sil, %al
    ret


/*
    ;    const char* dg_hctwostore (
    ;        unsigned char* pdest,    rdi  // rdi
    ;        UINT128* pud);           rsi  // rdx : rsi
*/

.globl _dg_hctwostore
_dg_hctwostore:

    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rsi
    popq %rdi

    movq 8(%rsi), %rdx
    movq (%rsi), %rsi
    bswapq %rdx
    movb %dl, %cl
    xorb %dl, %dl
    bswapq %rdx
    movq %rsi, %rax

    cmpb $0x10, %cl
    jnc L_dg_hctwostorethen4

    cmpb $8, %cl
    jc L_dg_hctwostorethen1
      subb $8, %cl
.globl _dg_hctwostoreerroraddress1
_dg_hctwostoreerroraddress1:
      movq %rsi, (%rdi)
      addq $8, %rdi
      movq %rdx, %rax
L_dg_hctwostorethen1:

    cmpb $4, %cl
    jc L_dg_hctwostorethen2
      subb $4, %cl
.globl _dg_hctwostoreerroraddress2
_dg_hctwostoreerroraddress2:
      movl %eax, (%rdi)
      addq $4, %rdi
      shrq $32, %rax
L_dg_hctwostorethen2:

    cmpb $2, %cl
    jc L_dg_hctwostorethen3
      subb $2, %cl
.globl _dg_hctwostoreerroraddress3
_dg_hctwostoreerroraddress3:
      movw %ax, (%rdi)
      addq $2, %rdi
      shrl $16, %eax
L_dg_hctwostorethen3:

    cmpb $1, %cl
    jc L_dg_hctwostorethen4
.globl _dg_hctwostoreerroraddress4
_dg_hctwostoreerroraddress4:
    movb %al, (%rdi)
L_dg_hctwostorethen4:     

    call _dg_endtrycatchbadmemoryerror
    
    leaq _dg_success(%rip), %rax
    ret

// need to make this signed...
.globl _dg_f64infinity
_dg_f64infinity:
.quad 0x7FF0000000000000  


.globl _dg_tentothex
_dg_tentothex:

  cmpq $309, %rdi
  jc L_dg_tentothexthen1
  
    vmovq _dg_f64infinity(%rip), %xmm0
    ret
    
L_dg_tentothexthen1:

  mov $1, %eax
  cvtsi2sd %eax, %xmm0
  
  mov $10, %eax
  cvtsi2sd %eax, %xmm1
  
L_dg_tentothexbegin:
  
  test %rdi, %rdi
  jnz L_dg_tentothexthen2
  
    ret
    
L_dg_tentothexthen2:

  shr $1, %rdi
  
  jnc L_dg_tentothexthen3
  
    mulsd %xmm1, %xmm0
    
L_dg_tentothexthen3:
  
  mulsd %xmm1, %xmm1
  
  jmp L_dg_tentothexbegin
  

.globl _dg_i64tof64
_dg_i64tof64:
    cvtsi2sd %rdi, %xmm0
    ret
    
.globl _dg_timeslog2
_dg_timeslog2:

    movq $301029995663981, %rax
    imul %rdi
    movq $1000000000000000, %rdi
    idiv %rdi
    ret          // since the number in rdi is shrinking... this should work
    
.globl _dg_f64toi64
_dg_f64toi64:
    cvttsd2si %xmm0, %rax
    ret
    
.globl _dg_roundf64tonearesteven
_dg_roundf64tonearesteven:
    roundsd $0, %xmm0, %xmm0
    ret
    
.globl _dg_roundf64tonegativeinfinity
_dg_roundf64tonegativeinfinity:
    roundsd $1, %xmm0, %xmm0
    ret
    
.globl _dg_f64sqrt
_dg_f64sqrt:
    sqrtsd %xmm0, %xmm0
    ret

    
.globl _dg_f64cos
_dg_f64cos:
    // emms
    fninit
    subq $8, %rsp
    movq %xmm0, (%rsp)
    fldl (%rsp)
    fcos
    fnclex
    fstpl (%rsp)
    movq (%rsp), %xmm0
    addq $8, %rsp
    ret
    
.globl _dg_f64sin
_dg_f64sin:
    // emms
    fninit
    subq $8, %rsp
    movq %xmm0, (%rsp)
    fldl (%rsp)
    fsin
    fnclex
    fstpl (%rsp)
    movq (%rsp), %xmm0
    addq $8, %rsp
    ret

.globl _dg_f64tan
_dg_f64tan:
    // emms
    fninit
    subq $8, %rsp
    movq %xmm0, (%rsp)
    fldl (%rsp)
    fptan
    fucomp
    fnclex
    fstpl (%rsp)
    movq (%rsp), %xmm0
    addq $8, %rsp
    ret

// cosresult = dg_f64sincos(angle, psinresult)
.globl _dg_f64sincos
_dg_f64sincos:
    // xmm0 = angle
    // rdi = psinresult
    // emms
    fninit
    subq $8, %rsp
    movq %xmm0, (%rsp)
    fldl (%rsp)
    fsincos
    fnclex
    fstpl (%rsp)
    movq (%rsp), %xmm0  // movq (%rsp), %rdx // cos
    fstpl (%rsp)
    popq (%rdi)
    ret

.globl _dg_f64fyl2x
_dg_f64fyl2x:
    // emms
    fninit
    subq $8, %rsp
    movq %xmm1, (%rsp) // x
    fldl (%rsp)
    movq %xmm0, (%rsp) // y
    fldl (%rsp)
    fyl2x
    fnclex
    fstpl (%rsp)
    movq (%rsp), %xmm0
    addq $8, %rsp
    ret
    
.globl _dg_f64fyl2xp1
_dg_f64fyl2xp1:
    // emms
    fninit
    subq $8, %rsp
    movq %xmm1, (%rsp) // x
    fldl (%rsp)
    movq %xmm0, (%rsp) // y
    fldl (%rsp)
    fyl2xp1
    fnclex
    fstpl (%rsp)
    movq (%rsp), %xmm0
    addq $8, %rsp
    ret
    
.globl _dg_f64f2xm1
_dg_f64f2xm1:
    // emms
    fninit
    subq $8, %rsp
    movq %xmm0, (%rsp) // x
    fldl (%rsp)
    f2xm1
    fnclex
    fstpl (%rsp)
    movq (%rsp), %xmm0
    addq $8, %rsp
    ret

.globl _dg_truncatef64
_dg_truncatef64:
    roundsd $3, %xmm0, %xmm0
    ret

.globl _dg_f64getfractional
_dg_f64getfractional:
    roundsd $3, %xmm0, %xmm1
    subsd %xmm1, %xmm0
    ret
    
 /*   
.globl _dg_f64pi
_dg_f64pi:
    // emms
    fninit
    subq $8, %rsp
    fldpi
    fstpl (%rsp)
    movq (%rsp), %xmm0
    addq $8, %rsp
    ret
*/
    
.globl _dg_f64logbase2of10
_dg_f64logbase2of10:
    // emms
    fninit
    subq $8, %rsp
    fldl2t
    fstpl (%rsp)
    movq (%rsp), %xmm0
    addq $8, %rsp
    ret
    
.globl _dg_f64logbase2ofe
_dg_f64logbase2ofe:
    // emms
    fninit
    subq $8, %rsp
    fldl2e
    fstpl (%rsp)
    movq (%rsp), %xmm0
    addq $8, %rsp
    ret
    
.globl _dg_f64fpatan
_dg_f64fpatan:
    // emms
    fninit
    subq $8, %rsp
    movq %xmm1, (%rsp) // y
    fldl (%rsp)
    movq %xmm0, (%rsp) // x
    fldl (%rsp)
    fpatan
    fnclex
    fstpl (%rsp)
    movq (%rsp), %xmm0
    addq $8, %rsp
    ret
    
.globl _dg_f64tof32
_dg_f64tof32:
    cvtsd2ss %xmm0, %xmm0  // does not clear bits 32 to 63
    ret
    
.globl _dg_f32tof64
_dg_f32tof64:
    cvtss2sd %xmm0, %xmm0
    ret

/*
    UINT128 dg_mstarslash (
      INT128 nd1,   // rsi:rdi
      INT64 n1,     // rdx
      INT64 +n2)    // rcx
   returns (nd1 * n1) / abs(n2) rdx:rax (remainder in r8)
   ;   UINT128 dg_mstarslash (
   ;     INT64* pnd1,  rdi  //  rcx      // rsi
   ;     INT64 n1,     rsi  //  rdx      // rdi
   ;     INT64 +n2)    rdx  //  r8       // rdx
   ;   returns (nd1 * n1) / abs(n2) rdx:rax (remainder in r8)
*/


.globl _dg_mstarslash
_dg_mstarslash:
    // if rcx is zero then return largest number
    pushq %rdi
    xorq %r10, %r10 // for sign
    movq %rdx, %rcx
    movq %rsi, %rdx
    movq 8(%rdi), %rsi
    movq (%rdi), %rdi
    orq %rcx, %rcx
    
    jnz L_dg_mstarslashthen1
      movq $0x7fffffffffffffff, %rdx
      movq $0xffffffffffffffff, %rax
      popq %rdi
      movq %rax, (%rdi)
      movq %rdx, 8(%rdi)
      ret
    L_dg_mstarslashthen1:
    
    // figure out sign of result and get absolute values
    jns L_dg_mstarslashthen2
        negq %rcx
        notq %r10
    L_dg_mstarslashthen2:
    
    orq %rdx, %rdx    
    jns L_dg_mstarslashthen3
        negq %rdx
        notq %r10
    L_dg_mstarslashthen3:
    
    orq %rsi, %rsi
    jns L_dg_mstarslashthen4    
        notq %rsi
        notq %rdi
        addq $1, %rdi
        adcq $0, %rsi
        notq %r10
    L_dg_mstarslashthen4:
        
    // r10 now has sign
    // rsi:rdi, rdx, and rcx are now positive
    movq %rdx, %r11
    movq %rdx, %rax
    mulq %rsi
    movq %rdx, %r9 // intermedhi   
    movq %rax, %r8 // intermedmid  
    
    movq %r11, %rax  
    mulq %rdi        
    addq %rdx, %r8   
    adcq $0, %r9     
    movq %rax, %rsi   
    
    // r9:r8:rsi has intermediate number
    // rcx has denominator
    // sign is in r10
    
    xorq %rdx, %rdx
    
    movq %r9, %rax
    divq %rcx
    
    orq %rax, %rax
    jz L_dg_mstarslashthen5 // if too big for 128 result, return largest
    
      movq $0x7fffffffffffffff, %rdx
      movq $0xffffffffffffffff, %rax
      popq %rdi
      movq %rax, (%rdi)
      movq %rdx, 8(%rdi)
      ret
    
    // figure out sign of result and get absolute values
    L_dg_mstarslashthen5:
    
    // don't need to save hi result because it's 0
    
    movq %r8, %rax
    divq %rcx
    movq %rax, %r8
    
    movq %rsi, %rax
    divq %rcx
    
    //r8:rax now holds result, rdx has remainder
    xchg %r8, %rdx
    
    // rdx:rax now holds result , r8 holds remainder
    // if its too big for signed number return largest
    orq %rdx, %rdx
    jns L_dg_mstarslashthen6
        movq $0x7fffffffffffffff, %rdx
        movq $0xffffffffffffffff, %rax
        popq %rdi
        movq %rax, (%rdi)
        movq %rdx, 8(%rdi)
        ret
    L_dg_mstarslashthen6:
    
    // negate result if it's negative
    orq %r10, %r10
    jns L_dg_mstarslashthen7 
      notq %rdx
      notq %rax
      addq $1, %rax
      adcq $0, %rdx
    L_dg_mstarslashthen7:
    popq %rdi
    movq %rax, (%rdi)
    movq %rdx, 8(%rdi)
    ret
    
.globl _dg_mplus
_dg_mplus:
    movq 16(%rdi), %rax
    cqo
    addq %rax, (%rdi)
    adcq %rdx, 8(%rdi)
    ret
    
// void dg_dplus (UINT128* pints) // points to two back to back UINT128s in memory
.globl _dg_dplus 
_dg_dplus:
  movq 16(%rdi), %rax   // mov rax, [rcx + 10h]
  movq 24(%rdi), %rdx   // mov rdx, [rcx + 18h]
  addq %rax, (%rdi)     // add [rcx], rax
  adcq %rdx, 8(%rdi)    // adc [rcx + 8h], rdx
  ret

// void dg_dminus (UINT128* pints)
.globl _dg_dminus
_dg_dminus:
  movq 16(%rdi), %rax    // mov rax, [rcx + 10h]
  movq 24(%rdi), %rdx    // mov rdx, [rcx + 18h]
  subq %rax, (%rdi)      // sub [rcx], rax
  sbbq %rdx, 8(%rdi)     // sbb [rcx + 8h], rdx
  ret

// note: z flag does not propogate through multi cell subtract

// void dg_dulessthan (UINT128* pints)
.globl _dg_dulessthan
_dg_dulessthan:
  xor %r8, %r8
  movq 16(%rdi), %rax   // mov rax, [rcx + 10h]
  movq 24(%rdi), %rdx   // mov rdx, [rcx + 18h]
  subq %rax, (%rdi)     // sub [rcx], rax
  sbbq %rdx, 8(%rdi)    // sbb [rcx + 8h], rdx
  jnc L_dg_ulessthanthen1
    decq %r8
  L_dg_ulessthanthen1:
  movq %r8, (%rdi)       // mov [rcx], r8
  ret

// void dg_dugreaterequalthan (UINT128* pints)
.globl _dg_dugreaterequalthan
_dg_dugreaterequalthan:
  xor %r8, %r8
  movq 16(%rdi), %rax   // mov rax, [rcx + 10h]
  movq 24(%rdi), %rdx   // mov rdx, [rcx + 18h]
  subq %rax, (%rdi)     // sub [rcx], rax
  sbbq %rdx, 8(%rdi)    // sbb [rcx + 8h], rdx
  jc L_dg_dugreaterequalthanthen1
    decq %r8
  L_dg_dugreaterequalthanthen1:
  movq %r8, (%rdi)       // mov [rcx], r8
  ret

// void dg_dlessthan (UINT128* pints)
.globl _dg_dlessthan
_dg_dlessthan:
  xor %r8, %r8
  movq 16(%rdi), %rax   // mov rax, [rcx + 10h]
  movq 24(%rdi), %rdx   // mov rdx, [rcx + 18h]
  subq %rax, (%rdi)     // sub [rcx], rax
  sbbq %rdx, 8(%rdi)    // sbb [rcx + 8h], rdx
  jge L_dg_dlessthanthen1
    decq %r8
  L_dg_dlessthanthen1:
  movq %r8, (%rdi)       // mov [rcx], r8
  ret

// void dg_dgreaterequalthan (UINT128* pints)
.globl _dg_dgreaterequalthan
_dg_dgreaterequalthan:
  xor %r8, %r8
  movq 16(%rdi), %rax   // mov rax, [rcx + 10h]
  movq 24(%rdi), %rdx   // mov rdx, [rcx + 18h]
  subq %rax, (%rdi)     // sub [rcx], rax
  sbbq %rdx, 8(%rdi)    // sbb [rcx + 8h], rdx
  jl L_dg_dgreaterequalthanthen1
    decq %r8
  L_dg_dgreaterequalthanthen1:
  movq %r8, (%rdi)       // mov [rcx], r8
  ret

// void dg_dumin (UINT128* pints)
.globl _dg_dumin
_dg_dumin:
  movq 16(%rdi), %rax  // mov rax, [rcx + 10h]
  movq 24(%rdi), %rdx  // mov rdx, [rcx + 18h]
  movq 8(%rdi), %r8    // mov r8, [rcx + 8h]
  cmpq %rax, (%rdi)    // cmp [rcx], rax
  sbbq %rdx, %r8        // sbb r8, rdx
  jc L_dg_duminthen1
    movq %rax, (%rdi)  // mov [rcx], rax
    movq %rdx, 8(%rdi) // mov [rcx+8], rdx
  L_dg_duminthen1:
  ret

// void dg_dumax (UINT128* pints)
.globl _dg_dumax
_dg_dumax:
  movq 16(%rdi), %rax  // mov rax, [rcx + 10h]
  movq 24(%rdi), %rdx  // mov rdx, [rcx + 18h]
  movq 8(%rdi), %r8    // mov r8, [rcx + 8h]
  cmpq %rax, (%rdi)    // cmp [rcx], rax
  sbbq %rdx, %r8        // sbb r8, rdx
  jnc L_dg_dumaxthen1
    movq %rax, (%rdi)  // mov [rcx], rax
    movq %rdx, 8(%rdi) // mov [rcx+8], rdx
  L_dg_dumaxthen1:
  ret

// void dg_dmin (UINT128* pints)
.globl _dg_dmin
_dg_dmin:
  movq 16(%rdi), %rax  // mov rax, [rcx + 10h]
  movq 24(%rdi), %rdx  // mov rdx, [rcx + 18h]
  movq 8(%rdi), %r8    // mov r8, [rcx + 8h]
  cmpq %rax, (%rdi)    // cmp [rcx], rax
  sbbq %rdx, %r8        // sbb r8, rdx
  jl L_dg_dminthen1
    movq %rax, (%rdi)  // mov [rcx], rax
    movq %rdx, 8(%rdi) // mov [rcx+8], rdx
  L_dg_dminthen1:
  ret

// void dg_dmax (UINT128* pints)
.globl _dg_dmax
_dg_dmax:
  movq 16(%rdi), %rax  // mov rax, [rcx + 10h]
  movq 24(%rdi), %rdx  // mov rdx, [rcx + 18h]
  movq 8(%rdi), %r8    // mov r8, [rcx + 8h]
  cmpq %rax, (%rdi)    // cmp [rcx], rax
  sbbq %rdx, %r8        // sbb r8, rdx
  jge L_dg_dmaxthen1
    movq %rax, (%rdi)  // mov [rcx], rax
    movq %rdx, 8(%rdi) // mov [rcx+8], rdx
  L_dg_dmaxthen1:
  ret


// void dg_dnegate (UINT128* pints)
.globl _dg_dnegate
_dg_dnegate:
  movq 8(%rdi), %rdx  // mov rdx, [rcx + 8]
  movq (%rdi), %rax   // mov rax, [rcx] 
  notq %rax
  notq %rdx
  addq $1, %rax       // add rax, 1
  adcq $0, %rdx       // adc rdx, 0
  movq %rax, (%rdi)   // mov [rcx], rax
  movq %rdx, 8(%rdi)  // mov [rcx+8], rdx
  ret


// void dg_dabs (UINT128* pints)
.globl _dg_dabs
_dg_dabs:
  movq 8(%rdi), %rdx   // mov rdx, [rcx + 8]
  testq %rdx, %rdx
  jns L_dg_dabsthen1
    movq (%rdi), %rax  // mov rax, [rcx] 
    notq %rax
    notq %rdx
    addq $1, %rax      // add rax, 1
    adcq $0, %rdx      // adc rdx, 0
    movq %rax, (%rdi)  // mov [rcx], rax
    movq %rdx, 8(%rdi) // mov [rcx+8], rdx
  L_dg_dabsthen1:
  ret

.globl _dg_returntestuint128
_dg_returntestuint128:
  movq $-5, %rax      // mov rax, -5
  movq $-1, %rdx       // mov rdx, -1
  ret


.globl _dg_testasmretuint128
_dg_testasmretuint128:
  movq %rdi, %rax     // mov rax, rcx
  movq %rdi, %rdx     // mov rdx, rcx
  incq %rax
  decq %rdx
  ret


// need log function which does fyl2xp1 when in range and fyl2x when not


// string unsigned multiply (faster)
// string unsigned divide
// string signed multiply
// strign signed divide



/*
const char* dg_scanfornotbytereverse (
    void* pbuf,       // rdi
    UINT64* plength,  // rsi
    UINT64 value)     // rdx
*/


.globl _dg_scanfornotbytereverse
_dg_scanfornotbytereverse:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rax // value
    popq %rsi // plength
    popq %rdi // pbuf
.else
    movq %rdx, %rax
.endif

    pushfq      /* save direction flag, required under win32 and Mac OSx */
                /* mac os requires direction flag set to forward */
                
.globl _dg_scanfornotbytereverseerroraddress1
_dg_scanfornotbytereverseerroraddress1:
    movq (%rsi), %rcx      /* rcx = length */
    movq $-1, (%rsi)       /* -1 length passed out means not found */
    movq %rcx, %rdx        /* rdx = length also */
    
    addq %rcx, %rdi
    decq %rdi /* post decrement with std need this */
    std
    
.globl _dg_scanfornotbytereverseerroraddress2
_dg_scanfornotbytereverseerroraddress2:
    repe    
    scasb    
    jz L_dg_scanfornotbytereversethen1
    
      decq %rdx
      subq %rcx, %rdx
      movq %rdx, (%rsi)

L_dg_scanfornotbytereversethen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif

    leaq _dg_success(%rip), %rax
    popfq
    ret
/*
.globl _dg_plusuint128
_dg_plusuint128:


    addq %rdi, %rdx
    adcq %rsi, %rcx
    movq %rdx, %rax
    movq %rcx, %rdx
    ret
*/

.globl _dg_random
_dg_random:
    rdseed %rax
    jnc _dg_random
    ret
    

/*
    const char* dg_addbytes (
        unsigned char* psrc,    // rdi   
        unsigned char* pdest,   // rsi   
        UINT64 stringlength,    // rdx   
        UINT64* pcarryout);     // rcx   
*/

.globl _dg_addbytes
_dg_addbytes:
    pushfq /* for alignment */
    
.ifndef DGLU_NO_DIAPER
    
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rcx
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
    xchg %rdx, %rcx  /* stringlength->rcx */
                     /* pcarrout->rdx */
.endif
                     
    xorq %rax, %rax
.globl _dg_addbyteserroraddress1
_dg_addbyteserroraddress1:
    movq %rax, (%rdx)
    
    clc 
    
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx
    jz L_dg_addbytesthen1
    
.globl _dg_addbyteserroraddress2
_dg_addbyteserroraddress2:
    movb (%rsi), %al
.globl _dg_addbyteserroraddress3
_dg_addbyteserroraddress3:
    adcb %al, (%rdi)

    incq %rsi
    incq %rdi
    loop _dg_addbyteserroraddress2
    
    jnc L_dg_addbytesthen1
    
    incq (%rdx) // set carryout to 1

L_dg_addbytesthen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_adcbytes (
        unsigned char* psrc,    // rdi
        unsigned char* pdest,   // rsi
        UINT64 stringlength,    // rdx
        UINT64* pcarryinout);   // rcx
*/

.globl _dg_adcbytes
_dg_adcbytes:
    pushfq /* for alignment */
    
.ifndef DGLU_NO_DIAPER
    
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx

    call _dg_trycatchbadmemoryerror2

    popq %rdx   /* stringlength->rcx */
    popq %rcx   /* pcarryinout->rdx */
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
    xchg %rdx, %rcx  /* stringlength->rcx */
                     /* pcarryinout->rdx */
                     
.endif
                     
    xorq %rax, %rax
    // movq $9, %rax
    
.globl _dg_adcbyteserroraddress1
_dg_adcbyteserroraddress1:
    xchgq %rax, (%rdx)
    
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx /* orq clears the carry flag and must come before shrb */
    
    jz L_dg_adcbytesthen1
    
    shrb %al  /* move the carryin to the carry flag */
    
.globl _dg_adcbyteserroraddress2
_dg_adcbyteserroraddress2:
    movb (%rsi), %al
.globl _dg_adcbyteserroraddress3
_dg_adcbyteserroraddress3:
    adcb %al, (%rdi)

    incq %rsi
    incq %rdi
    loop _dg_adcbyteserroraddress2
    
    jnc L_dg_adcbytesthen1
    
    incq (%rdx) // set carryout to 1

L_dg_adcbytesthen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_sbbbytes (
        unsigned char* psrc,    // rdi
        unsigned char* pdest,   // rsi
        UINT64 stringlength,    // rdx
        UINT64* pborrowinout);  // rcx
*/

.globl _dg_sbbbytes
_dg_sbbbytes:
    pushfq /* for alignment */
    
.ifndef DGLU_NO_DIAPER
    
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx

    call _dg_trycatchbadmemoryerror2

    popq %rdx   /* stringlength->rcx */
    popq %rcx   /* pborrowinout->rdx */
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
    xchg %rdx, %rcx  /* stringlength->rcx */
                     /* pborrowinout->rdx */
                     
.endif
                     
    xorq %rax, %rax
    
.globl _dg_sbbbyteserroraddress1
_dg_sbbbyteserroraddress1:
    xchgq %rax, (%rdx)
    
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx /* orq clears the carry and must come before shrb */
    
    jz L_dg_adcbytesthen1
    
    shrb %al  /* move the borrowin to the carry flag */
    
.globl _dg_sbbbyteserroraddress2
_dg_sbbbyteserroraddress2:
    movb (%rsi), %al
.globl _dg_sbbbyteserroraddress3
_dg_sbbbyteserroraddress3:
    sbbb %al, (%rdi)

    incq %rsi
    incq %rdi
    loop _dg_sbbbyteserroraddress2
    
    jnc L_dg_sbbbytesthen1
    
    incq (%rdx) // set borrowout to 1

L_dg_sbbbytesthen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret
        
/*
    const char* dg_andbytes (
        unsigned char* psrc,    // rdi
        unsigned char* pdest,   // rsi
        UINT64 stringlength);   // rdx
*/

.globl _dg_andbytes
_dg_andbytes:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
.endif

    pushfq      /* for frame */

    movq %rdx, %rcx  /* stringlength->rcx */ 
    
.globl _dg_andbyteserroraddress1
_dg_andbyteserroraddress1:
    movb (%rsi), %al
.globl _dg_andbyteserroraddress2
_dg_andbyteserroraddress2:
    andb %al, (%rdi)
    incq %rdi
    incq %rsi
    loop _dg_andbyteserroraddress1

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_orbytes (
        unsigned char* psrc,    // rdi
        unsigned char* pdest,   // rsi
        UINT64 stringlength);   // rdx
*/

.globl _dg_orbytes
_dg_orbytes:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
.endif

    pushfq      /* for frame */

    movq %rdx, %rcx  /* stringlength->rcx */ 
    
.globl _dg_orbyteserroraddress1
_dg_orbyteserroraddress1:
    movb (%rsi), %al
.globl _dg_orbyteserroraddress2
_dg_orbyteserroraddress2:
    orb %al, (%rdi)
    incq %rdi
    incq %rsi
    loop _dg_orbyteserroraddress1

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_xorbytes (
        unsigned char* psrc,    // rdi
        unsigned char* pdest,   // rsi
        UINT64 stringlength);   // rdx
*/

.globl _dg_xorbytes
_dg_xorbytes:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
.endif

    pushfq      /* for frame */

    movq %rdx, %rcx  /* stringlength->rcx */ 
    
.globl _dg_xorbyteserroraddress1
_dg_xorbyteserroraddress1:
    movb (%rsi), %al
.globl _dg_xorbyteserroraddress2
_dg_xorbyteserroraddress2:
    xorb %al, (%rdi)
    incq %rdi
    incq %rsi
    loop _dg_xorbyteserroraddress1

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_nandbytes (
        unsigned char* psrc,    // rdi
        unsigned char* pdest,   // rsi
        UINT64 stringlength);   // rdx
*/

.globl _dg_nandbytes
_dg_nandbytes:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
.endif

    pushfq      /* for frame */

    movq %rdx, %rcx  /* stringlength->rcx */ 
    
.globl _dg_nandbyteserroraddress1
_dg_nandbyteserroraddress1:
    movq (%rsi), %rax
.globl _dg_nandbyteserroraddress2
_dg_nandbyteserroraddress2:
    andb (%rdi), %al
    notb %al
.globl _dg_nandbyteserroraddress3
_dg_nandbyteserroraddress3:
    movb %al, (%rdi)
    incq %rdi
    incq %rsi
    loop _dg_nandbyteserroraddress1

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


.globl _dg_norbytes
_dg_norbytes:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
.endif

    pushfq      /* for frame */

    movq %rdx, %rcx  /* stringlength->rcx */ 
    
.globl _dg_norbyteserroraddress1
_dg_norbyteserroraddress1:
    movb (%rsi), %al
.globl _dg_norbyteserroraddress2
_dg_norbyteserroraddress2:
    orb (%rdi), %al
    notb %al
.globl _dg_norbyteserroraddress3
_dg_norbyteserroraddress3:
    movb %al, (%rdi)
    incq %rdi
    incq %rsi
    loop _dg_norbyteserroraddress1

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


.globl _dg_xnorbytes
_dg_xnorbytes:

.ifndef DGLU_NO_DIAPER
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rdi
    popq %rsi
.else
    xchg %rdi, %rsi
.endif

    pushfq      /* for frame */

    movq %rdx, %rcx  /* stringlength->rcx */ 
    
.globl _dg_xnorbyteserroraddress1
_dg_xnorbyteserroraddress1:
    movb (%rsi), %al
.globl _dg_xnorbyteserroraddress2
_dg_xnorbyteserroraddress2:
    xorb (%rdi), %al
    notb %al
.globl _dg_xnorbyteserroraddress3
_dg_xnorbyteserroraddress3:
    movb %al, (%rdi)
    incq %rdi
    incq %rsi
    loop _dg_xnorbyteserroraddress1

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_shlbytes (
        unsigned char* pdest,    // rdi
        UINT64 stringlength,     // rsi
        UINT64* pcarryout);      // rdx
*/
    
.globl _dg_shlbytes
_dg_shlbytes:
    
.ifndef DGLU_NO_DIAPER
    
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rcx
    popq %rdi
.else
    movq %rsi, %rcx  /* stringlength->rcx */
.endif

    pushfq
                     
    xorq %rax, %rax
.globl _dg_shlbyteserroraddress1
_dg_shlbyteserroraddress1:
    movq %rax, (%rdx)
    
    clc 
    
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx
    jz L_dg_shlbytesthen1
    
.globl _dg_shlbyteserroraddress2
_dg_shlbyteserroraddress2:
    rclb (%rdi)
    incq %rdi
    loop _dg_shlbyteserroraddress2
    
    jnc L_dg_shlbytesthen1
    
    incq (%rdx) // set carryout to 1

L_dg_shlbytesthen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret
    
    
/*
    const char* dg_shrbytes (
        unsigned char* pdest,    // rdi
        UINT64 stringlength,     // rsi
        UINT64* pcarryout);      // rdx
*/
    
.globl _dg_shrbytes
_dg_shrbytes:

    addq %rsi, %rdi
    
.ifndef DGLU_NO_DIAPER
    
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rcx
    popq %rdi
.else
    movq %rsi, %rcx  /* stringlength->rcx */
.endif

    pushfq
                     
    xorq %rax, %rax
.globl _dg_shrbyteserroraddress1
_dg_shrbyteserroraddress1:
    movq %rax, (%rdx)
    
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx         /* or clears the carry */
    jz L_dg_shrbytesthen1

L_dg_shrbytesbegin1:

    decq %rdi
    
.globl _dg_shrbyteserroraddress2
_dg_shrbyteserroraddress2:
    
    rcrb (%rdi)
    
    loop L_dg_shrbytesbegin1
    
    jnc L_dg_shrbytesthen1
    
    incq (%rdx) // set carryout to 1

L_dg_shrbytesthen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret
 

/*
    const char* dg_rclbytes (
        unsigned char* pdest,    // rdi
        UINT64 stringlength,     // rsi
        UINT64* pcarryinout);    // rdx
*/    
    
.globl _dg_rclbytes
_dg_rclbytes:
    
.ifndef DGLU_NO_DIAPER
    
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rcx
    popq %rdi
.else
    movq %rsi, %rcx  /* stringlength->rcx */
.endif

    pushfq
                     
    xorq %rax, %rax
.globl _dg_rclbyteserroraddress1
_dg_rclbyteserroraddress1:
    xchgq %rax, (%rdx)
    
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx  /* orq clears the carry and must come before shrb */
    jz L_dg_rclbytesthen1
    
    shrb %al  /* move the carryin to the carry */ 
    
.globl _dg_rclbyteserroraddress2
_dg_rclbyteserroraddress2:
    rclb (%rdi)
    incq %rdi
    loop _dg_rclbyteserroraddress2
    
    jnc L_dg_rclbytesthen1
    
    incq (%rdx) // set carryout to 1

L_dg_rclbytesthen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_rcrbytes (
        unsigned char* pdest,    // rdi
        UINT64 stringlength,     // rsi
        UINT64* pcarryinout);    // rdx
*/    
    
.globl _dg_rcrbytes
_dg_rcrbytes:

    // move pdest to character after string
    addq %rsi, %rdi
    
.ifndef DGLU_NO_DIAPER
    
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rcx
    popq %rdi
.else
    movq %rsi, %rcx  /* stringlength->rcx */
.endif

    pushfq
                     
    xorq %rax, %rax
.globl _dg_rcrbyteserroraddress1
_dg_rcrbyteserroraddress1:
    xchgq %rax, (%rdx)
    
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx  /* orq clears the carry and must come before shrb */
    jz L_dg_rcrbytesthen1
    
    shrb %al  /* move the carryin to the carry */
 
 L_dg_rcrbytesbegin1: 
    decq %rdi
      
.globl _dg_rcrbyteserroraddress2
_dg_rcrbyteserroraddress2:
    
    rcrb (%rdi)
    loop L_dg_rcrbytesbegin1
    
    jnc L_dg_rcrbytesthen1
    
    incq (%rdx) // set carryout to 1

L_dg_rcrbytesthen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_sarbytes (
        unsigned char* pdest,    // rdi
        UINT64 stringlength,     // rsi
        UINT64* pcarryout);      // rdx
*/
    
.globl _dg_sarbytes
_dg_sarbytes:

    addq %rsi, %rdi
    
.ifndef DGLU_NO_DIAPER
    
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rcx
    popq %rdi
.else
    movq %rsi, %rcx  /* stringlength->rcx */
.endif

    pushfq
                     
    xorq %rax, %rax
.globl _dg_sarbyteserroraddress1
_dg_sarbyteserroraddress1:
    movq %rax, (%rdx)
    
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx         
    jz L_dg_sarbytesthen1
    
    /* 1st byte is asr */
    decq %rdi
    sarb (%rdi)
    decq %rcx
    
    jz L_dg_sarbytesthen1

L_dg_sarbytesbegin1:

    decq %rdi
    
.globl _dg_sarbyteserroraddress2
_dg_sarbyteserroraddress2:
    
    rcrb (%rdi)
    
    loop L_dg_sarbytesbegin1
    
    jnc L_dg_sarbytesthen1
    
    incq (%rdx) // set carryout to 1

L_dg_sarbytesthen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret
    

/*
    const char* dg_notbytes (
        unsigned char* pdest,    // rdi
        UINT64 stringlength);    // rsi
*/
    
.globl _dg_notbytes
_dg_notbytes:
    pushfq      /* pushfq is up here for alignment for _dg_trycatchbadmemoryerror2 */
    
.ifndef DGLU_NO_DIAPER
    
    
    pushq %rdi
    pushq %rsi

    call _dg_trycatchbadmemoryerror2

    popq %rcx
    popq %rdi
.else
    movq %rsi, %rcx  /* stringlength->rcx */
.endif
    
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx
    jz L_dg_notbytesthen1
    
.globl _dg_notbyteserroraddress1
_dg_notbyteserroraddress1:
    notb (%rdi)
    incq %rdi
    loop _dg_notbyteserroraddress1

L_dg_notbytesthen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret
    
    
/*
    const char* dg_reversebytes (
        unsigned char* pdest,    // rdi
        UINT64 stringlength);    // rsi
*/
    
.globl _dg_reversebytes
_dg_reversebytes:
    pushfq      /* pushfq is up here for alignment for _dg_trycatchbadmemoryerror2 */
    
.ifndef DGLU_NO_DIAPER
    
    
    pushq %rdi
    pushq %rsi

    call _dg_trycatchbadmemoryerror2

    popq %rcx
    popq %rdi
.else
    movq %rsi, %rcx  /* stringlength->rcx */
.endif
    
    movq %rdi, %rsi
    addq %rcx, %rsi
    shrq %rcx
    
    /* if rcx was < 2 then do nothing */
    // orq %rcx, %rcx
    orq %rcx, %rcx
    jz L_dg_reversebytesthen1
    
.globl _dg_reversebyteserroraddress1
_dg_reversebyteserroraddress1:
    movb (%rdi), %al
    decq %rsi
.globl _dg_reversebyteserroraddress2
_dg_reversebyteserroraddress2:
    xchgb (%rsi), %al
.globl _dg_reversebyteserroraddress3
_dg_reversebyteserroraddress3:
    movb %al, (%rdi)
    incq %rdi
    loop _dg_reversebyteserroraddress1

L_dg_reversebytesthen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret
    

/*
    const char* dg_incbytes (
        unsigned char* pdest,    // rdi
        UINT64 stringlength,     // rsi
        UINT64* pcarryout);      // rdx
*/
    
.globl _dg_incbytes
_dg_incbytes:
    
.ifndef DGLU_NO_DIAPER
    
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rcx
    popq %rdi
.else
    movq %rsi, %rcx  /* stringlength->rcx */
.endif

    pushfq
                     
    xorq %rax, %rax
.globl _dg_incbyteserroraddress1
_dg_incbyteserroraddress1:
    movq %rax, (%rdx)
    
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx  /* this clears the carry */
    jz L_dg_incbytesthen1
    
    stc
    
.globl _dg_incbyteserroraddress2
_dg_incbyteserroraddress2:
    adcb %al, (%rdi)        /* al should be 0 */
    jnc L_dg_incbytesthen1 /* if no carry, no need to look at the rest */
    incq %rdi
    loop _dg_incbyteserroraddress2
    
    incq (%rdx) // set carryout to 1

L_dg_incbytesthen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_decbytes (
        unsigned char* pdest,    // rdi
        UINT64 stringlength,     // rsi
        UINT64* pcarryout);      // rdx
*/
    
.globl _dg_decbytes
_dg_decbytes:
    
.ifndef DGLU_NO_DIAPER
    
    pushq %rdi
    pushq %rsi
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rcx
    popq %rdi
.else
    movq %rsi, %rcx  /* stringlength->rcx */
.endif

    pushfq
                     
    xorq %rax, %rax
.globl _dg_decbyteserroraddress1
_dg_decbyteserroraddress1:
    movq %rax, (%rdx)
    
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx  /* this clears the carry */
    jz L_dg_decbytesthen1
    
    stc
    
.globl _dg_decbyteserroraddress2
_dg_decbyteserroraddress2:
    sbbb %al, (%rdi)        /* al should be 0 */
    jnc L_dg_decbytesthen1 /* if no borrow, no need to look at the rest */
    incq %rdi
    loop _dg_decbyteserroraddress2
    
    incq (%rdx) // set carryout to 1

L_dg_decbytesthen1:

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret


/*
    const char* dg_mulu64tou64s (
        UINT64* pdest,           // rdi 
        UINT64* psrc,            // rsi 
        UINT64  u,               // rdx 
        UINT64  srclengthinu64s, // rcx
        UINT64* pcarryout);      // r8
*/

.globl _dg_mulu64tou64s
_dg_mulu64tou64s:
    
.ifndef DGLU_NO_DIAPER
    
    pushq %rsi
    pushq %rdi
    pushq %rcx
    pushq %rdx
    pushq %r8

    call _dg_trycatchbadmemoryerror2

    popq %r8
    popq %rdx
    popq %rcx
    popq %rdi
    popq %rsi
    
.endif

    pushfq /* for _dg_trycatchbadmemoryerror2 alignment and frame */

    xorq %r9, %r9 // holds carry for next loop
    
    movq %rdx, %r10   /* r10 now has u */
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx
    jz L_dg_mulu64tou64sthen1
    
.globl _dg_mulu64tou64serroraddress1
_dg_mulu64tou64serroraddress1:
    movq (%rsi), %rax    
    addq $8, %rsi
    mulq %r10      // R10 * RAX -> RDX:RAX
    addq %r9, %rdx // to add in carry from previous loop
                   // since it's impossible for RDX to be -1 
                   //  there won't be a carry from this
    xorq %r9, %r9  // clear the r9 to hold the carry...
     
.globl _dg_mulu64tou64serroraddress2
_dg_mulu64tou64serroraddress2:
    addq %rax, (%rdi)
.globl _dg_mulu64tou64serroraddress3
_dg_mulu64tou64serroraddress3:
    adcq %rdx, 8(%rdi)  
    rclq %r9 // to save carry for next time through loop
    addq $8, %rdi
    loop _dg_mulu64tou64serroraddress1

L_dg_mulu64tou64sthen1:

.globl _dg_mulu64tou64serroraddress4
_dg_mulu64tou64serroraddress4:
    movq %r9, (%r8)

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret
    

/*
    const char* dg_divu64sbyu64 (
        UINT64* pdest,            // rdi // quotient and dividend
        UINT64* premainder,       // rsi // remainder
        UINT64  u,                // rdx // divisor
        UINT64  destlengthinu64s) // rcx
*/

.globl _dg_divu64sbyu64
_dg_divu64sbyu64:

    pushfq /* for _dg_trycatchbadmemoryerror2 alignment and frame */
    
.ifndef DGLU_NO_DIAPER
    
    pushq %rsi
    pushq %rdi
    pushq %rcx
    pushq %rdx

    call _dg_trycatchbadmemoryerror2

    popq %rdx
    popq %rcx
    popq %rdi
    popq %rsi
    
.endif
    
    /* checking for divide by 0 case */
    orq %rdx, %rdx
    jnz L_dg_divu64sbyu64then2
    
    
    xorq %rdx, %rdx  // this might be unnecessary since rdx is already 0
    decq %rdx /* setting remainder to max UINT64 for div by 0 case */
    
    jmp L_dg_divu64sbyu64then1 
    
L_dg_divu64sbyu64then2:
    
    movq %rdx, %r10   /* r10 now has u */
    
    /* if rcx is 0 then do nothing */
    orq %rcx, %rcx
    jz L_dg_divu64sbyu64then1
    
    movq %rcx, %rax
    shlq $3, %rax
    addq %rax, %rdi /* move dest pointer to the end */
    
    xorq %rdx, %rdx /* clear rdx for first divide */
    
_dg_divu64sbyu64begin:
    subq $8, %rdi
    
.globl _dg_divu64sbyu64erroraddress1
_dg_divu64sbyu64erroraddress1:
    movq (%rdi), %rax    
    
    divq %r10      // RDX:RAX / R10 -> RAX rem RDX

.globl _dg_divu64sbyu64erroraddress2
_dg_divu64sbyu64erroraddress2:
    movq %rax, (%rdi)
    
    loop _dg_divu64sbyu64begin

L_dg_divu64sbyu64then1:

.globl _dg_divu64sbyu64erroraddress3
_dg_divu64sbyu64erroraddress3:
    movq %rdx, (%rsi)  /* save the remainder */

.ifndef DGLU_NO_DIAPER
    call _dg_endtrycatchbadmemoryerror
.endif
    
    leaq _dg_success(%rip), %rax
    popfq
    ret    

