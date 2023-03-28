; ////////////////////////////////////////////////////////////////////////////////////////
; //
; //    Copyright 2023 James Patrick Norris
; // 
; //    This file is part of Diaperglu v5.8.
; //
; //    Diaperglu v5.8 is free software; you can redistribute it and/or modify 
; //    it under the terms of the GNU General PUBLIC License as published by
; //    the Free Software Foundation; either version 2 of the License, or
; //    (at your option) any later version.
; //
; //    Diaperglu v5.8 is distributed in the hope that it will be useful,
; //    but WITHOUT ANY WARRANTY; without even the implied warranty of
; //    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; //    GNU General PUBLIC License for more details.
; //
; //    You should have received a copy of the GNU General PUBLIC License
; //    along with Diaperglu v5.8; if not, write to the Free Software
; //    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
; //
; ////////////////////////////////////////////////////////////////////////////////////////

; ///////////////////////////////
; // James Patrick Norris      //
; // www.rainbarrel.com        //
; // March 27, 2023            //
; // version 5.8               //
; ///////////////////////////////

; MS x86-64 calling convention
;
; first 4 arguments 64 bits or less are passed in registers, 
;  it doesn't matter if they are floating point or integer
;  arguments after 4 are passed on the return stack
; 
; if all the arguments are 64 bit or less integers or pointers, the first 4 are passed in
;  RCX RDX R8 R9
;
; if all the arguments are 64 bit or less floating points, the first 4 are passed in: 
;  XMM0 XMM1 XMM2 XMM3
;
; if the first 4 arguments are mixed floating point and integer/pointer 64 bits or less then,
;  the register for that argument position and type is used, for example:
;  if the first argument is integer and the second argument is floating point then
;  rcx is used for the first argument and xmm1 is used for the second argument
;
; arguments after 4 are passed on the return stack in the order they appear in the c prototype
;  in other words, argument 5 is the first argument after the 4 argument shadow region going up in memory,
;  and argument 6 is the second argument after the 4 argument shadow region going up in memory.

; 64 bit integers and less are return in RAX
;
; parameters over 64 bits are passed in memory
;
; returns over 64 bits are not supported

; RBX, RBP, RDI, RSI, RSP, R12, R13, R14, R15, and XMM6-XMM15 must be preserved

; any functions that can throw an exception such as a bad memory error must use the microsoft standard frame format
;  and leave the RSP 16 byte aligned. (So when the exception happens, the RSP must be 16 byte aligned.)
; https://docs.microsoft.com/en-us/cpp/build/stack-usage?view=vs-2019
; The frame is this:
; param n
; ...
; param 5
; shadow r9
; shadow r8
; shadow rdx
; shadow rcx
; return address
; saved registers that must be preserved
; local variables  // the frame pointer usually points to the lowest memory local variable
;
; functions that can throw exceptions must also generate unwind table data. Masm has directives to make this
;  easier and they are documented here: https://docs.microsoft.com/en-us/cpp/build/exception-handling-x64?view=vs-2019
;
; there are end of subroutine requirements for functions that can throw exceptions which are these:
; https://docs.microsoft.com/en-us/cpp/build/prolog-and-epilog?view=vs-2019
; 
; Docs say you can put stuff on the return stack after the frame, however, pushing registers that do not have
;  to be preserved seems to confuse the unwind code. Pushing flags seems to be ok, but docs suggest this is
;  treated as a stack allocation and you have to use .allocstack 8 with it. Docs also say you have to use
;  sub rsp to allocate space, which may cause problems with my and rsp trick... but I won't be using that in any
;  subroutines that can throw exceptions...

.CODE

dg_success PROC EXPORT 
  DB "success", 0
dg_success ENDP

dg_badmemoryerror PROC EXPORT 
  DB "bad memory error", 0
dg_badmemoryerror ENDP

dg_nop PROC EXPORT

    ret
    
dg_nop ENDP

dg_testasm PROC EXPORT
    
    mov rax, rcx
    inc rax
    ret
    
dg_testasm ENDP


; dg_testasmimport PROC EXPORT

;    mov rax, qword ptr dg_success
;    ret
    
; dg_testasmimport ENDP


dg_testalignment PROC EXPORT

    mov rax, rsp
    movd xmm0, rax
    ret

dg_testalignment ENDP

dg_testalignmentdf PROC EXPORT

    movd xmm0, rsp      ; movd %rsp, %xmm0
    ret

dg_testalignmentdf ENDP


dg_getretstackpointer PROC EXPORT
   
   mov rax, rsp
   sub rax, 8    
   ret
   
dg_getretstackpointer ENDP


dg_getframepointer PROC EXPORT
   
   mov rax, rbp
   ret
   
dg_getframepointer ENDP


; dg_getplocalvariablestackspacestart PROC EXPORT
   
;   lea eax, [ebp-0Ch]
;   ret
   
; dg_getplocalvariablestackspacestart ENDP


; dg_getplocalvariablestackspaceend PROC EXPORT
   
;   mov eax, [ebp-0Ch]
;   ret
   
; dg_getplocalvariablestackspaceend ENDP


; dg_getlocalvariablestackspacelength PROC EXPORT
   
;   lea eax, [ebp-0Ch]
;   sub eax, [ebp-0Ch]
;   ret
   
; dg_getlocalvariablestackspacelength ENDP


; UINT64 dg_callcoreforthroutine(
;     Bufferhandle* pBHarrayhead,     // rcx
;     UINT64 forthcoreroutineaddress) // rdx

dg_callcoreforthroutine PROC EXPORT
    
    sub rsp, 28h ; for shadow regs and alignment
    call rdx
    add rsp, 28h ; undo shadow regs and alignment
    ret
    
dg_callcoreforthroutine ENDP
    
    
; void dg_forthregsfrom(Bufferhandle* pBHarrayhead)
; // ( -- ebp esp edi esi edx ecx ebx eax eflags ) 

; dg_forthregsfrom PROC EXPORT
   
;    push ebp             
;    mov ebp, esp       
;    pushfd                
;    pushad                 
;    ; /*  EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI */
;    sub esp, 0Ch ;
	
;    push qword ptr [ebp] 
;    push qword ptr [ebp+8]  ; /* pBHarrayhead */
;    call dg_pushdatastack
;    ; /* should check error count here */
;    add esp, 8
	
;    push qword ptr [ebp-18h] 
;    push qword ptr [ebp+8]  	
;    call dg_pushdatastack
;    add esp, 8
	
 ;   push qword ptr [ebp-24h] 
 ;   push qword ptr [ebp+8]  	
 ;   call dg_pushdatastack
 ;   add esp, 8
	
;    push qword ptr [ebp-20h] 
;    push qword ptr [ebp+8]  	
;    call dg_pushdatastack
;    add esp, 8
	
;    push qword ptr [ebp-10h] 
;    push qword ptr [ebp+8]
;    call dg_pushdatastack
;    add esp, 8
	
;    push qword ptr [ebp-0Ch] 
;    push qword ptr [ebp+8]
;    call dg_pushdatastack
;    add esp, 8
	
;    push qword ptr [ebp-14h]
;    push qword ptr [ebp+8]  	
;    call dg_pushdatastack
;    add esp, 8
	
;    push qword ptr [ebp-8] 
;    push qword ptr [ebp+8]  	
;    call dg_pushdatastack
;    add esp, 8
	
;    push qword ptr [ebp-4] 
;    push qword ptr [ebp+8] 	
;    call dg_pushdatastack
;    add esp, 8
		
;    add esp, 0Ch
;    popad
;    popfd
;    pop ebp
;    ret
    
; dg_forthregsfrom ENDP


; /* ( ebp esp edi esi edx ecx ebx eax eflags -- ) */

; dg_forthtoregs PROC EXPORT
   
;    push ebp            
;    mov ebp, esp   
;    pushfd        
;    pushad                
;    ; /*  EAX, ECX, EDX, EBX, original ESP, EBP, ESI, and EDI */
	
;    push [ebp+8]
;    call dg_popdatastack
;    mov [ebp-4], eax
;    add esp, 4
	
;    push [ebp+8]
;    call dg_popdatastack
;    mov [ebp-8], eax  
;    add esp, 4
	
;    push [ebp+8]
;    call dg_popdatastack
;    mov [ebp-14h], eax
;    add esp, 4
	
;    push [ebp+8]
;    call dg_popdatastack
;    mov [ebp-0Ch], eax
;    add esp, 4
	
;    push [ebp+8]
;    call dg_popdatastack
;    mov [ebp-10h], eax
;    add esp, 4
	
;    push [ebp+8]
;    call dg_popdatastack
;    mov [ebp-20h], eax
;    add esp, 4
			
;    push [ebp+8]
;    call dg_popdatastack
;    mov [ebp-24h], eax
;    add esp, 4
	
;    push [ebp+8]
;    call dg_popdatastack
;    mov [ebp-18h], eax
;    add esp, 4
	
;    push [ebp+8]
;    call dg_popdatastack
 ;   mov [ebp], eax
 ;   add esp, 4

;    popad
;    popfd
;    pop ebp
;    ret
    
; dg_forthtoregs ENDP
	

dg_bswap PROC EXPORT
   
   mov rax, rcx
   bswap rax
   ret
   
dg_bswap ENDP
        
; /* pints pointer assumed to point to valid memory */
; void dg_udmslashmod(UINT64* pints)
; //  pints points to in:  udlo udhi u1  
; //  pints points to out: ud2lo ud2hi rem

dg_udmslashmod PROC EXPORT
;   pints  rcx  rdi

    push rdi
    mov rdi, rcx

    mov rax, [rdi+8]     ; movq 8(%rdi), %rax /* udhi */
    mov rdx, 0           ; movq $0, %rdx

    mov rcx, [rdi+16]    ; movq 16(%rdi), %rcx /* u1 */
    or rcx, rcx          ; orq %rcx, %rcx

    jz dg_udmslashmodthen1

    div rcx              ; div %rcx
    mov [rdi+8], rax     ; movq %rax, 8(%rdi) /* udhi */
    mov rax, [rdi]       ; movq (%rdi), %rax /* udlo */
    mov rcx, [rdi+16]    ; movq 16(%rdi), %rcx /* u1 */
		
    div rcx              ; div %rcx
    mov [rdi+16], rdx    ; movq %rdx, 16(%rdi) /* u1 */
    mov [rdi], rax       ; movq %rax, (%rdi) /* udlo */
    jmp dg_udmslashmodthen2
		
dg_udmslashmodthen1:
    mov rax, -1 ; 0xffffffffffffffff  ; movq $0xffffffffffffffff, %rax
    mov [rdi], rax       ; movq %rax, (%rdi) /* udlo */
    mov [rdi+8], rax     ; movq %rax, 8(%rdi) /* udhi */
    mov [rdi+16], rax     ; movq %rax, 16(%rdi) /* u1 */
dg_udmslashmodthen2:

    pop rdi
    ret
    
dg_udmslashmod ENDP
        

; INT64 dg_twoslash (INT64 n1)     
; returns n1/2

dg_twoslash PROC EXPORT
   
   mov rax, rcx
   sar rax, 1
   ret
   
dg_twoslash ENDP
  

; UINT64 dg_lshift (UINT64 x1, UINT64 u)
; returns x1 shifted left u times

dg_lshift PROC EXPORT
    
    mov rax, rcx
    mov rcx, rdx
    shl rax, cl
    ret
    
dg_lshift ENDP

    
; INT128 dg_mstar (INT64 n1, INT64 n2, INT128* presult)
; returns n1*n2

dg_mstar PROC EXPORT
    
    mov rax, rcx
    imul rdx
    mov [r8], rax
    mov [r8+8], rdx
    ret
    
dg_mstar ENDP
    

; UINT64 dg_rshift (UINT64 x1, UINT64 u)
; returns x1 shifted right u times

dg_rshift PROC EXPORT
    
    mov rax, rcx
    mov rcx, rdx
    shr rax, cl
    ret
    
dg_rshift ENDP


; UINT128 dg_umstar (UINT64 n1, UINT64 n2, UINT128* presult)
; returns u1*u2

dg_umstar PROC EXPORT
    
    mov rax, rcx
    mul rdx
    mov [r8], rax
    mov [r8+8], rdx
    ret
    
dg_umstar ENDP


; void dg_umslashmod (UINT64* pints)
; pints in: udlo udhi u1
; pints out: u2 u3 dontcare

dg_umslashmod PROC EXPORT

    push rdi
    mov rdi, rcx
    mov rax, [rdi]      ; movq (%rdi), %rax
    mov rdx, [rdi+8]    ; movq 8(%rdi), %rdx
    mov rcx, [rdi+16]   ; movq 16(%rdi), %rcx
    or rcx, rcx         ; orq %rcx, %rcx
    jz umslashmodthen1  ; jz L_umslashmodthen1
    cmp rdx, rcx        ; cmpq %rcx, %rdx
    jnc umslashmodthen1 ; jnc L_umslashmodthen1
    div rcx             ; div %rcx
    mov [rdi], rdx      ; movq %rdx, (%rdi)
    mov [rdi+8], rax    ; movq %rax, 8(%rdi)
    jmp umslashmodthen2 ; jmp L_umslashmodthen2

umslashmodthen1:

    mov rax, -1 ; 0xffffffffffffffff ; movq $0xFFFFFFFFFFFFFFFF, %rax
    mov [rdi], rax              ; movq %rax, (%rdi)
    mov [rdi+8], rax            ; movq %rax, 8(%rdi)

umslashmodthen2:
   
    pop rdi
    ret
    
dg_umslashmod ENDP



;   UINT64 dg_uaddclipped (
;    UINT64 u1,          // rcx  rdi 
;    UINT64 u2)          // rdx  rsi
    
;   // this is for preventing overflow errors
   



dg_uaddclipped PROC EXPORT

  mov rax, rcx    ; movq %rdi, %rax
  add rax, rdx    ; addq %rsi, %rax
  jnc L_dg_uaddclipped
    xor rax, rax  ; xorq %rax, %rax
    dec rax       ; decq %rax
L_dg_uaddclipped:
    ret

dg_uaddclipped ENDP

; const char* dg_scanforbyte (
;     void* pbuf,         // rcx   rdi
;     UINT64* plength,    // rdx   rsi
;     UINT64 value)       // r8    rdx

; since this function can throw bad memory exceptions, unwind data is needed for the try catch block
dg_scanforbytesub PROC EXPORT FRAME ; FRAME starts the construction of the unwind data table

    push rdi
    .pushreg rdi ; for the unwind table
    push rsi
    .pushreg rsi ; for the unwind table
    pushfq             ; /* save direction flag, required under win32, just in case for others */
    .allocstack 8      ; /* mac os requires direction flag set to forward */
                       ; unwind catch code automatically restores flags if an exception occurs
    .endprolog
    
    
    mov rdi, rcx
    mov rcx, [rdx]                    ; movq (%rsi), %rcx      /* rcx = length */
    mov qword ptr [rdx], -1 ; movq $-1, (%rsi)       /* -1 length passed out means not found */
    mov rax, r8
    mov r9, rcx                       ; movq %rcx, %rdx        /* rdx = length also */
    cld

    repne scasb    
    jnz dg_scanforbytesubthen1     ; jnz L_dg_scanforbytethen1
    
    dec r9                         ; decq %rdx
    sub r9, rcx                    ;  subq %rcx, %rdx
    mov [rdx], r9                  ;

dg_scanforbytesubthen1:            ; L_dg_scanforbytethen1:

    popfq
    pop rsi
    pop rdi
    ret

dg_scanforbytesub ENDP


; const char* dg_scanforuint32 (
;     void* pbuf,         // rcx   rdi
;     UINT64* plength,    // rdx   rsi
;     UINT64 value)       // r8    rdx
	
dg_scanforuint32sub PROC EXPORT FRAME

    push rdi
    .pushreg rdi
    push rsi
    .pushreg rsi
    pushfq             ; /* save direction flag, required under win32, just in case for others */
    .allocstack 8      ; /* mac os requires direction flag set to forward */
    .endprolog
    
    mov rdi, rcx
    mov rcx, [rdx]                    ; movq (%rsi), %rcx      /* rcx = length */
    mov qword ptr [rdx], -1 ; 0xffffffffffffffff     ; movq $-1, (%rsi)       /* -1 length passed out means not found */
    mov rax, r8
    mov r9, rcx                       ; movq %rcx, %rdx        /* rdx = length also */
    cld

    repne scasd    
    jnz dg_scanforuint32subthen1     ; jnz L_dg_scanforbytethen1
    
    dec r9                         ; decq %rdx
    sub r9, rcx                    ;  subq %rcx, %rdx
    mov [rdx], r9                  ;

dg_scanforuint32subthen1:            ; L_dg_scanforbytethen1:

    popfq
    mov rsi, [rsp+10h]  ; pop rsi
    mov rdi, [rsp+8]    ; pop rdi
    ret

dg_scanforuint32sub ENDP


; const char* dg_scanforuint64 (
;     void* pbuf,         // rcx   rdi
;     UINT64* plength,    // rdx   rsi
;     UINT64 value)       // r8    rdx
	
dg_scanforuint64sub PROC EXPORT FRAME

    push rdi
    .pushreg rdi
    push rsi
    .pushreg rsi
    
    pushfq           ; /* save direction flag, required under win32, just in case for others */
    .allocstack 8    ; /* mac os requires direction flag set to forward */
    .endprolog
    
    mov rdi, rcx
    mov rcx, [rdx]                    ; movq (%rsi), %rcx      /* rcx = length */
    mov qword ptr [rdx], -1 ; 0xffffffffffffffff      ; movq $-1, (%rsi)       /* -1 length passed out means not found */
    mov rax, r8
    mov r9, rcx                       ; movq %rcx, %rdx        /* rdx = length also */
    cld

    repne scasq    
    jnz dg_scanforuint64subthen1     ; jnz L_dg_scanforbytethen1
    
    dec r9                         ; decq %rdx
    sub r9, rcx                    ;  subq %rcx, %rdx
    mov [rdx], r9                  ;

dg_scanforuint64subthen1:            ; L_dg_scanforbytethen1:

    popfq
    pop rsi
    pop rdi
    ret

dg_scanforuint64sub ENDP


; const char* dg_scanfornotbytereverse (
;     void* pbuf,         // rcx   rdi
;     UINT64* plength,    // rdx   rsi
;     UINT64 value)       // r8    rdx

dg_scanfornotbytereversesub PROC EXPORT FRAME

    push rdi
    .pushreg rdi
    push rsi
    .pushreg rsi
    
    pushfq            ;  /* save direction flag, required under win32 and Mac OSx */
    .allocstack 8     ;  /* mac os requires direction flag set to forward */
    .endprolog
    mov rdi, rcx
    mov rcx, [rdx] ;  (%rsi), %rcx      /* rcx = length */
    mov qword ptr [rdx], -1 ; 0xffffffffffffffff  ; movq $-1, (%rsi)       /* -1 length passed out means not found */
    mov rax, r8    ; movq %rcx, %rdx        /* rdx = length also */
    mov r9, rcx    ;
    
    add rdi, rcx   ; addq %rcx, %rdi
    dec rdi        ; decq %rdi /* post decrement with std need this */
    std
    repe scasb    
    jz dg_scanfornotbytereversethen1
    
    dec r9         ;   decq %rdx
    sub r9, rcx    ;   subq %rcx, %rdx
    mov [rdx], r9  ;  movq %rdx, (%rsi)

dg_scanfornotbytereversethen1:

    popfq
    pop rsi
    pop rdi
    ret

dg_scanfornotbytereversesub ENDP


; const char* dg_movebytes (
;     unsigned char* psrc,    // rcx 
;     unsigned char* pdest,   // rdx
;     UINT32 stringlength);   // r8

dg_movebytessub PROC EXPORT FRAME
    
    push rdi
    .pushreg rdi
    push rsi
    .pushreg rsi
    
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    mov rsi, rcx
    mov rdi, rdx
    mov rcx, r8  ; /* stringlength->rcx */
    cld 
    cmp rdi, rsi
    jc dg_movebytesthen1

      add rdi, rcx    ; addq %rcx, %rdi
      add rsi, rcx    ; addq %rcx, %rsi
      dec rdi ; /* post decrement with std need this */
      dec rsi ; /* post decrement with std need this */
      std

dg_movebytesthen1:
    rep movsb

    popfq
    pop rsi
    pop rdi
    ret

dg_movebytessub ENDP


; const char* dg_moveuint64s (
;     UINT64* psrc,    // rcx 
;     UINT64* pdest,   // rdx
;     UINT64  length); // r8

dg_moveuint64ssub PROC EXPORT FRAME
    
    push rdi
    .pushreg rdi
    push rsi
    .pushreg rsi
    
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    mov rsi, rcx
    mov rdi, rdx
    mov rcx, r8  ; /* length->rcx */
    cld 
    cmp rdi, rsi
    jc dg_moveuint64sthen1

      shl r8, 3
      add rdi, r8    ; addq %rcx, %rdi
      add rsi, r8    ; addq %rcx, %rsi
      sub rdi, 8 ; /* post decrement with std need this */
      sub rsi, 8 ; /* post decrement with std need this */
      std

dg_moveuint64sthen1:
    rep movsq

    popfq
    pop rsi
    pop rdi
    ret

dg_moveuint64ssub ENDP


;    const char* dg_movebytesreverse (
;        unsigned char* psrc,    // rdi
;        unsigned char* pdest,   // rsi
;        UINT64 stringlength);   // rdx


dg_movebytesforwardsub PROC EXPORT FRAME
    push rdi
    .pushreg rdi
    push rsi
    .pushreg rsi
    
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    mov rsi, rcx
    mov rdi, rdx
    mov rcx, r8  ; /* stringlength->rcx */

    cld 
    rep movsb

    popfq
    pop rsi
    pop rdi
    ret
dg_movebytesforwardsub ENDP

dg_movebytesreversesub PROC EXPORT FRAME
    push rdi
    .pushreg rdi
    push rsi
    .pushreg rsi
    
    pushfq           ; /* -0x10  save direction flag, required under win32, just in case for others */
    .allocstack 8    ; /* mac os requires direction flag set to forward */
    .endprolog
    mov rsi, rcx
    mov rdi, rdx
    mov rcx, r8  ; /* stringlength->rcx */
    
    add rdi, rcx ; addq %rcx, %rdi
    add rsi, rcx ; addq %rcx, %rsi
    dec rdi      ; /* post decrement with std need this */
    dec rsi      ; /* post decrement with std need this */

    std
    rep movsb
    
    popfq
    pop rsi
    pop rdi
    ret
dg_movebytesreversesub ENDP


;   JN Dec 27, 2011, _dg_comparebytes min branch function for length fixed


; const char* dg_comparebytes (
;     unsigned char* pstring1,    // rcx   rdi
;     UINT64 string1length,       // rdx   rsi
;     unsigned char* pstring2,    // r8    rdx
;     UINT64 string2length,       // r9    rcx
;     INT64* pflag);              // 0x08  r8

dg_comparebytessub PROC EXPORT FRAME

    push rdi
    .pushreg rdi
    push rsi
    .pushreg rsi
    
    pushfq             ; /* -0x10  save direction flag, required under win32, just in case for others */
    .allocstack 8      ; /* mac os x requires direction flag left in forward direction */
    .endprolog
    ; rdx = length2 <- r9
    ; rdi = pstring2 <- r8
    ; rcx r9 = length1 <- rdx
    ; rsi = pstring1 <- rcx
    ; r8 = pflag <- return stack

    mov rdi, r8    ; // pstring2
    mov rsi, rcx   ; // pstring1
    xchg r9, rdx   ; // stringlength1 stringlength2
    mov rcx, r9   ; // stringlength1
    mov r8, [rsp + 040h]  ; pflag // ret + 4 items shadow space + 3 items on stack

;    /* set compare flag to default which is bad memory */

    mov qword ptr [r8], -2

    ; /* protected compare bytes */

    ; //    unsigned char* pstring1,    // rsi

    cmp rcx, rdx ; cmpq %rdx, %rcx            /* length1 - length2 */
    jc dg_comparebytesthen0  ; /* if length1 u< length2 keep length1 - branch changed from jnc to jc Dec 27, 2011 */
    mov rcx, rdx ; movq %rdx, %rcx            /* length2->rcx */
dg_comparebytesthen0:

    cld                        ; /* this was missing */
    repe cmpsb                  
    je dg_comparebytesthen1   
    mov rax, 1 ; movq $1, %rax
    jnc dg_comparebytesthen2  
    mov rax, -1 ; movq $-1, %rax
    jmp dg_comparebytesthen2  

dg_comparebytesthen1:             
    mov rax, r9  ; movq %r9, %rax          /* length1->rax */
    cmp rax, rdx ; cmpq %rdx, %rax         /* compare rax with length2 */
    mov rax, 0 ; movq $0, %rax
    je dg_comparebytesthen2   
    mov rax, 1 ; movq $1, %rax
    jnc dg_comparebytesthen2  
    mov rax, -1 ; movq $-1, %rax

dg_comparebytesthen2:
    mov [r8], rax ; movq %rax, (%r8)       /* move rax->(pflag) */

    ; mov rax, qword ptr dg_success ; leaq _dg_success(%rip), %rax
    popfq
    pop rsi
    pop rdi
    ret

dg_comparebytessub ENDP



; unsigned char* dg_search (
;     unsigned char* caddr1,      // rcx = target string to search
;     UINT64 u1,                  // rdx = length of target string
;     unsigned char* caddr2,      // r8 = string to search for in target string
;     UINT64 u2,                  // r9 = length of string to search for
;     unsigned char** pcaddrout)  // 08 = pointer to found string or pointer to null
    
; returns dg_success on success
; returns dg_badmemoryerror if memory at strings is not part of current process


dg_searchsub PROC EXPORT FRAME
    push rdi
    .pushreg rdi
    push rsi
    .pushreg rsi
    push r11
    .pushreg r11
    push r10
    .pushreg r10
    
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
    .allocstack 8   ; /* mac os x requires direction flag left in forward direction */
    .endprolog
    ; an odd number of things were push to the return stack so it is aligned
    
    
    mov r11, rdx           ; popq %r11  // r11 = length1
    mov rdx, r8            ; popq %rdx  // rdx = caddr2  
    mov r10, rcx           ; popq %r10  // r10 = caddr1
    mov r8, [rsp + 050h]   ; popq %r8   // r8 = pcaddrout
                           ;            // r9 = length2

    ; /* if length of string to search for is 0, then return a match */
    xor rax, rax
    cmp r9, rax ; cmpq %rax, %r9
    jz dg_searchsubthen2
    
    ; /* if string we are looking for is longer than target string, return not found */
    cmp r11, r9 ; cmpq %r9, %r11
    jc dg_searchsubthen1

    ;   to keep compare from going off end, and to avoid scanning unneccesary bytes
    ;    going to shorten scan length of target string to only look at positions
    ;    where the shorter string can actually start at

    mov rcx, r9 ; movq %r9, %rcx
    dec rcx
    sub r11, rcx ; subq %rcx, %r11

    ; /* set direction flag to forwards so string operations go up in memory */
    cld
    
dg_searchsubbegin1:

    ; /* get first character from string to find */

    mov rcx, r11  ; movq %r11, %rcx
    mov al, [rdx] ; movb (%rdx), %al
    
    ; /* scan for that character in target string */

    mov rdi, r10 ; movq %r10, %rdi
    repne scasb
    mov rax, 0 ; movq $0, %rax /* clear eax without altering state of zero flag */
    jne dg_searchsubthen1
    
    ; /* update position in target string */
    mov r11, rcx ; movq %rcx, %r11
    mov r10, rdi ; movq %rdi, %r10

    ; /* compare strings */
    mov rcx, r9  ; movq %r9, %rcx
    mov rsi, rdx ; movq %rdx, %rsi
    inc rsi ; incq %rsi /* first character already checked and edi points to one after match */
    dec rcx ; decq %rcx
    or rcx, rcx ; orq %rcx, %rcx
    jz dg_searchsubthen2
    repe cmpsb
    jz dg_searchsubthen2
    
    or r11, r11
    jz dg_searchsubthen1
    jnz dg_searchsubbegin1

dg_searchsubthen2:
    mov rax, r10 ; movq %r10, %rax
    dec rax
    
dg_searchsubthen1:
    ; /* set found not found pointer with result */
    mov [r8], rax ; movq %rax, (%r8)

    popfq
    pop r10
    pop r11
    pop rsi
    pop rdi
    ret

dg_searchsub ENDP


; /* void dg_savequitstate (UINT32* pquitstate) */

; dg_savequitstate PROC EXPORT
    
    ; need to pop return address and pquitstate
    ; so that saved stack frame will be that of parent
    
;    pop edx ; /* return address */
;    pop eax ; /* pquitstate */
    
;    mov [eax], edi
;    mov [eax+4], esi
;    mov [eax+8], ebp
;    mov [eax+0Ch], esp
;    mov [eax+10h], ebx
;    pushfd
;    pop ecx
;    mov [eax+14h], ecx
    
;    push eax ; /* need to push pquitstate back on because parent will eat it */
;    jmp edx
    
; dg_savequitstate ENDP

    
; /* void dg_restorequitstate (UINT32* pquitstate) */

; dg_restorequitstate PROC EXPORT
    
    ; need to jump so that stack frame is correct
    ; we are eating everything including first return and
    ; whatever parameters from first call out of quit
    
;    pop edx   ; /* return address */
;    pop eax   ; /* pquitstate */
    
;    mov ecx, [eax+14h]  ; /* doing eflags first */
;    push ecx
;    popfd
;    mov ebx, [eax+10h]
;    mov esp, [eax+0Ch]  ; /* restore stack to state without pquitstate on it */
;    mov ebp, [eax+8]
;    mov esi, [eax+4]
;    mov edi, [eax]
    
;    push eax            ; /* need to push a parameter back on stack because parent will eat one */
;    jmp edx
    
; dg_restorequitstate ENDP
   

; UINT64 dg_callprocaddress (
;     UINT64* pints,     // rcx  rdi
;     UINT64 n,          // rdx  rsi
;     UINT64* plength,   // r8   rdx
;     UINT64* address);  // r9   rcx

dg_callprocaddress PROC EXPORT
    
    ; /* enter frame */
    push rbp
    mov rbp, rsp         ; movq %rsp, %rbp
    push r9              ; push rcx
    push r8              ; rdx

    mov r11, rdx         ; movq %rsi, %r11
    
    ; /* alignment  frame   what it is */
    ; r9   /* rcx                function address */
    ; r8   /* rdx                pdatastacklength
    ; rdx  /* rsi                n = number of paramenters */
    ; rcx  /* rdi                pdatastack */
    
    ; /*            +8      return address */
    ; /*            +0      saved ebp */
    ; /*            -8      function address */
    ; /*            -0x10   pdatastacklength */
    
    ; // so at this point we still need 0 bytes to get to 16 byte alignment, but just in case
    and rsp, -10h         ;   andq $-0x10, %rsp

    ; // if number of parameters is <= 4 or even, then do not need adjust rsp by 8
    ; // if number of parameters is > 4 and odd, then you do need to adjust rsp by 8
    
    cmp rdx, 5        ; cmpq $7, %rsi
    jc dg_callprocaddressthen2     ; // if < 5 do not need to adjust rsp
    test rdx, 1       ; testq $1, %rsi
    jz dg_callprocaddressthen2    ; // if even do not need to adjust rsp
    
; dg_callprocaddressthen1:
    sub rsp, 8        ; subq $8, %rsp
dg_callprocaddressthen2:

    ; /* copy parameters from data stack to return stack if needed */
dg_callprocaddressbegin1:
    cmp rdx, 5        ; cmpq $7, %rsi
    jc dg_callprocaddressthen3 ; // while number of paramters >=5 push parameters

    push [rcx]        ; pushq (%rdi)
    add rcx, 8        ; addq $8, %rdi
    dec rdx           ; decq %rsi
    jmp dg_callprocaddressbegin1

dg_callprocaddressthen3:

    sub rsp, 20h      ; for the shadow regs

    ; /* copy parameters to regs if needed */
    cmp r11, 4        ; cmpq $6, %r11 // see if there are at least 4 parameters
    jc dg_callprocaddressthen4
      mov r9, [rcx]   ; movq (%rdi), %r9
      add rcx, 8      ; addq $8, %rdi
dg_callprocaddressthen4:

    cmp r11, 3        ; cmpq $5, %r11 // see if there are at least 3 parameters
    jc dg_callprocaddressthen5
      mov r8, [rcx]   ; movq (%rdi), %r8
      add rcx, 8      ; addq $8, %rdi
dg_callprocaddressthen5:

    cmp r11, 2        ; cmpq $4, %r11 // see if there are at least 2 parameters
    jc dg_callprocaddressthen6
      mov rdx, [rcx]  ; movq (%rdi), %rcx
      add rcx, 8      ; addq $8, %rdi
dg_callprocaddressthen6:

    cmp r11, 1        ; cmpq $3, %r11 // see if there are at least 1 parameter
    jc dg_callprocaddressthen7
      mov rcx, [rcx]  ; movq (%rdi), %rdx
dg_callprocaddressthen7:

     ; /* drop parameters from the data stack - the downside is when there is an error you lose the stack frame
     ;   this is here so that you can call a proc which modifies the data stack */
     mov rax, [rbp + -10h]     ; movq -0x10(%rbp), %rax
     add r11, 2                ; addq $2, %r11
     shl r11, 3                ; shl $3, %r11
     sub [rax], r11            ; subq %r11, (%rax)
     
     ; /* call proc */
     call qword ptr [rbp + -8]           ; call *-0x08(%rbp)
     
     ; /* drops everything left on return stack
     ;    this is compatible with both cdecl, and stdcall
     ;    also, registers rax and rdx are left untouched which is compatible with ret UINT128 */
     mov rsp, rbp             ; movq %rbp, %rsp
     pop rbp
     ret

dg_callprocaddress ENDP


dg_callprocaddressretuint128 PROC EXPORT
    sub rsp, 28h ; for alignment and shadow regs... doing shadow regs just in case even though they shouldn't be used

    call dg_callprocaddress
    mov rcx, [rsp+50h]   ; pointer to result hi
    mov [rcx], rdx

    add rsp, 28h
    ret
dg_callprocaddressretuint128 ENDP


COMMENT !
.globl _dg_calldfpprocaddressretuint128
_dg_calldfpprocaddressretuint128:
!

; FLOAT64 dg_calldfpprocaddress (   ; ret in XMM0
;        UINT64* pints,      // rcx rdi
;        UINT64 n,           // rdx rsi
;        UINT64* plength,    // r8  rdx
;        UINT64* address,    // r9  rcx
;        UINT64 nfloat);     // [rbp + 30h]  r8

dg_calldfpprocaddress PROC EXPORT
    
    ; /* enter frame */
    push rbp
    mov rbp, rsp     ; movq %rsp, %rbp

    push rdi
    push rsi

    mov rdi, rcx
    mov rsi, rdx
    mov rdx, r8
    mov rcx, r9
    mov r8, [rbp + 30h]

    push rcx                   ; pushq %rcx
    push rdx                   ; pushq %rdx
    push r8                    ; pushq %r8
    push rdi                   ; pushq %rdi

    mov r11, rsi               ; movq %rsi, %r11
    
    ; /* alignment  frame   what it is */
    ; /* r8                 number of double floating point parameters
    ; /* rcx                function address */
    ; /* rdx                pdatastacklength
    ; /* rsi                n = number of paramenters */
    ; /* rdi                pdatastack */
    
    ; /*            +8      return address */
    ; /*            +0      saved ebp */
    ; /*            -8      saved rdi */
    ; /*            -10     saved rsi */
    ; /*            -8      function address */
    ; /*            -0x10   pdatastacklength */
    ; /*            -0x18   number of floating point parameters */
    ; /*            -0x20   pdatastack */
    
    ; // so at this point we still need 0 bytes to get to 16 byte alignment, but just in case
    and rsp, -10h              ; andq $-0x10, %rsp

    ; // if number of parameters is > 4
    ; //  or the number of floating point parameters is > 4
    ; //  and the number of those 'extra' parameters are odd,
    ; //  then do need to adjust rsp by 8
    ; // otherwise you do need to not adjust rsp by 8

    ; // if the number of floating point parameters is > 8 and odd

    mov rax, rsi   ; movq %rsi, %rax  // rax <- number of integer parameters
    add rax, r8    ;                  // rax += number of floating point parameters
    sub rax, 4     ; subq $6, %rax    // rax -= 4
    jbe dg_calldfpprocaddressthen18   ;     // if the number of extra parameters is <= 4 then don't need to adjust rsp
                                      ;     //  or push floating point numbers to the stack
      test rax, 1      ; testq $1, %rax     // if number of extra parameters is odd then bump rsp - could just look at al
    jz dg_calldfpprocaddressthen0
     sub rsp, 8      ; subq $8, %rsp        // adjust rsp for odd extra number of parameters
 dg_calldfpprocaddressthen0:

    ; rax holds the total number of extra parameters

    ; /* copy floating point parameters from data stack to return stack if needed */

    and r8, r8       ; cmpq $9, %r8   
    jz dg_calldfpprocaddressthen17    ; // if no floating point parameters are left we can move on

dg_calldfpprocaddressbegin2:
    and rax, rax
    jz dg_calldfpprocaddressthen18    ; // if no extra parameters are left then done pushing floats to stack
    push [rdi]       ; pushq (%rdi)
    add rdi, 8       ; addq $8, %rdi
    dec rax
    dec r8           ; decq %r8
    jz dg_calldfpprocaddressthen17    ; // if no floating point parameters are left we move on
          
    jmp dg_calldfpprocaddressbegin2

    

dg_calldfpprocaddressthen18:

      and r8, r8                        ; cmpq $9, %r8   
      jz dg_calldfpprocaddressthen17    ; // if no floating point parameters are left we can move on

      add rax, 4                        ; // rax now equals the number of parameters left

      cmp rax, 4
      jc dg_calldfpprocaddressthen14

      movq xmm3, qword ptr [rdi]  ; movq (%rdi), %xmm3
      add rdi, 8                  ; addq $8, %rdi
      dec r8
      jz dg_calldfpprocaddressthen17    ; // if no floating point parameters are left we can move on
dg_calldfpprocaddressthen14: 
      cmp rax, 3
      jc dg_calldfpprocaddressthen15
      movq xmm2, qword ptr [rdi]  ; movq (%rdi), %xmm2
      add rdi, 8                  ; addq $8, %rdi
      dec r8
      jz dg_calldfpprocaddressthen17    ; // if no floating point parameters are left we can move on
dg_calldfpprocaddressthen15:
      cmp rax, 2
      jc dg_calldfpprocaddressthen16
      movq xmm1, qword ptr [rdi]  ; movq (%rdi), %xmm1
      add rdi, 8                  ; addq $8, %rdi
      dec r8
      jz dg_calldfpprocaddressthen17    ; // if no floating point parameters are left we can move on
dg_calldfpprocaddressthen16:
      cmp rax, 1
      jc dg_calldfpprocaddressthen17
      movq xmm0, qword ptr [rdi]  ; movq (%rdi), %xmm0
      add rdi, 8                  ; addq $8, %rdi

dg_calldfpprocaddressthen17:

    ; /* copy parameters from data stack to return stack if needed */
dg_calldfpprocaddressbegin1:
    ; rsi now has the total number of parameters left, and the total number of integer parameters
    cmp rsi, 5                    ; cmpq $7, %rsi
    jc dg_calldfpprocaddressthen3 ; // and integer number of paramters >=5 push parameters

    push [rdi]                    ; pushq (%rdi)
    add rdi, 8                    ; addq $8, %rdi
    dec rsi                       ; decq %rsi
    jmp dg_calldfpprocaddressbegin1

dg_calldfpprocaddressthen3:

    sub rsp, 20h                  ; for the shadow regs

    ; /* copy parameters to regs if needed */
    
    cmp rsi, 4                    ; cmpq $4, %r11 // see if there are at least 4 parameters
    jc dg_calldfpprocaddressthen6
      mov r9, [rdi]              ; movq (%rdi), %rcx
      add rdi, 8                 ; addq $8, %rdi
dg_calldfpprocaddressthen6:

    cmp rsi, 3                   ; cmpq $3, %r11 // see if there are at least 3 parameters
    jc dg_calldfpprocaddressthen7
      mov r8, [rdi]              ; movq (%rdi), %rdx
      add rdi, 8                 ; addq $8, %rdi
dg_calldfpprocaddressthen7:

    cmp rsi, 2                   ; cmpq $2, %r11 // see if there are at least 2 parameters
    jc dg_calldfpprocaddressthen8
      mov rdx, [rdi]             ; movq (%rdi), %rsi
      add rdi, 8                 ; addq $8, %rdi
dg_calldfpprocaddressthen8:

    cmp rsi, 1                   ; cmpq $1, %r11 // see if there are at least 1 parameters
    jc dg_calldfpprocaddressthen9
      mov rcx, [rdi]             ; movq (%rdi), %rdi
dg_calldfpprocaddressthen9:

     ; /* drop parameters from the data stack - the downside is when there is an error you lose the stack frame
     ;     this is here so that you can call a proc which modifies the data stack */
     mov rax, [rbp + -20h]       ; movq -0x10(%rbp), %rax
     add r11, 3                  ; addq $3, %r11
     add r11, [rbp + -28h]       ; addq -0x18(%rbp), %r11
     shl r11, 3                  ; shl $3, %r11
     sub [rax], r11              ; subq %r11, (%rax)
     
     ; /* call proc */
     call qword ptr [rbp + -18h]             ; call *-0x08(%rbp)

     ; /* move results to the data stack */
     ; // movq -0x10(%rbp), %rdi
     ; // addq $0x10, (%rdi)
     ; // movq -0x20(%rbp), %rdi
     ; // movq %rax, (%rdi)        // so int result is on bottom
     ; // movq %xmm0, 0x10(%rdi)   // and double float result is on top
     
     ; /* drops everything left on return stack
     ;     this is compatible with both cdecl, and stdcall
     ;     also, registers rax and rdx are left untouched which is compatible with ret UINT128 */
     lea rsp, [rbp + -10h]              ; movq %rbp, %rsp
     pop rsi
     pop rdi
     pop rbp                            ; popq %rbp
     ret
dg_calldfpprocaddress ENDP

; // NOTE: This routine does NOT check for errors in the parameters. The parent routine must do this
; UINT32 dg_callprocaddress  (
;     UINT32* pints,    // 0x08
;     UINT32 n,         // 0x0c
;     UINT32* plength,  // 0x10
;     UINT32* address)  // 0x14

; dg_callprocaddress PROC EXPORT
    
    ; /* enter frame */
;    push ebp
;    mov ebp, esp
;    push ebx
    
    ; /* align return stack to  16bytes for n parameters */
;    mov eax, esp
;    mov ecx, [ebp+0Ch]   ; /* n */
;    shl ecx, 2
;    and ecx, 0Fh         ; /* is this necessary? */
;    sub eax, ecx
;    and eax, 0Fh
;    sub esp, eax
;    
;    ; /* copy parameters from data stack to return stack */
;    mov eax, [ebp+8]
;    mov ecx, [ebp+0Ch]
;    or ecx, ecx
;    jz dg_callprocaddressthen1
;     
; dg_callprocaddressbegin1:
;    push dword ptr [eax]
;    add eax, 4
;    loop dg_callprocaddressbegin1
;     
; dg_callprocaddressthen1:				  
;    ; drop parameters from the data stack - the downside is when there is an error you lose the stack frame;
	;  this is here so that you can call a PROC C which modifies the data stac;k
;
;    mov ecx, [ebp+0Ch]
;    add ecx, 2
;    shl ecx, 2
;    mov eax, [ebp+10h]
;    sub [eax], ecx;
	 
    ; /* call PROC C */
;    mov eax, [ebp+14h]
;    call eax
     
;    lea esp, [ebp-4]
;    pop ebx
;    pop ebp
;    ret
    
; dg_callprocaddress ENDP


; // NOTE: This routine does NOT check for errors in the parameters. The parent routine must do this
; DGLU_API UINT32 dg_callprocaddressalign16 (
;     UINT32* address,  // +0x08
;     UINT32 n,         // +0x0C  number of UINT32 units in parameters
;     ...);             //          most things are 1 unit, a UINT64 is 2 units


; dg_callprocaddressalign16 PROC EXPORT
    
    ; /* enter full standard frame */
;    push ebp  ; /* +0x00 */
;    mov ebp, esp
;    push ebx  ; /* -0x04 */
;    push esi  ; /* -0x08 */
;    push edi  ; /* -0x0C */
;    pushfd    ; /* -0x10  save direction flag, required under win32, just in case for others */
    
    ; /* align return stack to  16bytes for n parameters */
;    mov eax, esp
;    mov ecx, [ebp+0Ch]   ; /* n */
;    shl ecx, 2
;    and ecx, 0Fh         ; /* is this necessary? */
;    sub eax, ecx
;    and eax, 0Fh
;    sub esp, eax
;    
    ; /* copy parameters from return stack to return stack */
;    lea eax, [ebp+10h]
;    mov ecx, [ebp+0Ch]
;    or ecx, ecx
;    jz dg_callprocaddressalign16then1
;    
;    shl ecx, 2           ; /* not reversing parameters */
;    add eax, ecx
;    shr ecx, 2
  
; dg_callprocaddressalign16begin1:
;    sub eax, 4
;    push qword ptr [eax]
;    loop dg_callprocaddressalign16begin1
   
; dg_callprocaddressalign16then1:				  
    ; drop parameters from the data stack - the downside is when there is an error you lose the stack frame
    ;  this is here so that you can call a PROC C which modifies the data stack
	 
    ; /* call PROC C */
;    mov eax, [ebp+08h]
;    call eax
     
    ; /* exit full standard frame */
;    lea esp, [ebp-10h]
;    popfd
;    pop edi
;    pop esi
;    pop ebx
;    pop ebp
;    ret
  
; dg_callprocaddressalign16 ENDP



; dg_callcppmemberwin32 PROC EXPORT
    
    ; /* enter frame */
;    push ebp
;    mov ebp, esp
;    push ebx
    
;    ; /* align return stack to  16bytes for n parameters */
;    mov eax, esp
;    mov ecx, [ebp+0Ch]   ; /* n */
;    dec ecx              ; /* n-1 */
;    shl ecx, 2
;    and ecx, 0Fh         ; /* is this necessary? */
;    sub eax, ecx
;    and eax, 0Fh
;    sub esp, eax
;    
;    ; /* copy parameters from data stack to return stack */
;    mov eax, [ebp+8]
;    mov ecx, [ebp+0Ch]
;    or ecx, ecx
;    jz dg_callcppmemberwin32then1
;     
; dg_callcppmemberwin32begin1:
;      push qword ptr [eax]
;      add eax, 4
;    loop dg_callcppmemberwin32begin1
;     
; dg_callcppmemberwin32then1:				  

    ; drop parameters from the data stack - the downside is when there is an error you lose the stack frame
    ;  this is here so that you can call a proceedure which modifies the data stack

;    mov eax, [ebp+0Ch]
;    add ecx, 2
;    shl ecx, 2
;    mov eax, [ebp+10h]
;    sub [eax], ecx
	 
    ; /* call proceedure */
;    pop ecx
;    mov eax, [ebp+14h]
;    call eax
     
;    lea esp, [ebp-4]
;    pop ebx
;    pop ebp
;    ret
    
; dg_callcppmemberwin32 ENDP



; const char* dg_fillwithbyte (
;     unsigned char* pbuf,  // rcx   rdi
;     UINT64 length,        // rdx   rsi
;     UINT64 value)         // r8    rdx
	
dg_fillwithbytesub PROC EXPORT FRAME
    push rdi
    .pushreg rdi
    push rsi
    .pushreg rsi ; not needed, just doing it to align stack
    
    pushfq
    .allocstack 8
    .endprolog
    
    ; /* protected fill with byte */
    mov rdi, rcx
    mov rcx, rdx  ; movq %rsi, %rcx      /* length */
    mov rax, r8   ; movq %rdx, %rax      /* value */
    cld

    rep stosb    
    popfq
    pop rsi
    pop rdi
    ret
   
 dg_fillwithbytesub ENDP


 ; const char* dg_readallbytes (
;     unsigned char* pbuf,  // rcx   rdi
;     UINT64 length)        // rdx   rsi
	
dg_readallbytessub PROC EXPORT FRAME
    push rsi
    .pushreg rsi
    push rdi      ; not needed, just doing it to align stack
    .pushreg rdi 
    pushfq
    .allocstack 8
    .endprolog
    
    ; /* protected fill with byte */
    mov rsi, rcx
    mov rcx, rdx  ; movq %rsi, %rcx      /* length */
    cld

    rep lodsb    

    popfq
    pop rdi
    pop rsi
    ret
   
 dg_readallbytessub ENDP



; void dg_forthfsfrom (
;   Bufferhandle* pBHarrayhead)  // 0x08
	
; dg_forthfsfromsub PROC EXPORT
   
    ; /* enter frame */
;    push ebp  ; /* +0x00 */
;    mov ebp, esp
    
;    push eax  
;    push eax  ; /* -0x08 making room for 64bit float */

    ; force alignment of return stack to 16 bytes
    ;  for calling subroutines with no parameters
    ;  probably not required but doing it just in case
 ;   and esp, 0FFFFFFF0h

 ;   fstp qword ptr [ebp-8]
     
 ;   push [ebp-8]      ; /* floating point value low */
 ;   push [ebp+8]      ; /* pBHarrayhead */
    
 ;   call dg_pushdatastack
 ;   add esp, 8
    
 ;   push [ebp-4]      ; /* floating point value high */
 ;   push [ebp+8]      ; /* pBHarrayhead */
	
 ;   call dg_pushdatastack
 ;   add esp, 8

    ; return type is void but setting return value to 0 anyways
 ;   mov eax, 0
    
    ; /* exit frame */
;    lea esp, [ebp-0h]
;    pop ebp
;    ret
    
; dg_forthfsfromsub ENDP


; void dg_forthf32from (
;   Bufferhandle* pBHarrayhead)  // 0x08
	
; dg_forthf32fromsub PROC EXPORT
   
    ; /* enter frame */
;    push ebp  ; /* +0x00 */
;    mov ebp, esp
     
;    push eax  ; /* -0x04 making room for 32bit float */

    ; /* force alignment of return stack to 16 bytes */
    ;  /* for calling subroutines with no parameters */
    ;  /* probably not required but doing it just in case */
;    and esp, 0FFFFFFF0h

;    fstp qword ptr [ebp-4] 
    
;    push [ebp-4]      ; /* floating point value */
;    push [ebp+8]      ; /* pBHarrayhead */
	
;    call dg_pushdatastack
;    add esp, 8

    ; / * return type is void but setting return value to 0 anyways */
;    mov eax, 0
    
    ; /* exit frame */
;    lea esp, [ebp-0h]
;    pop ebp
;    ret
    
; dg_forthf32fromsub ENDP

; ///////////////////////////////////////////////////////////////

dg_tofromxmm0 PROC EXPORT
    movd rax, xmm0 ; movd %xmm0, %rax
    movd xmm0, rcx ; movd %rdi, %xmm0
    ret

dg_tofromxmm0 ENDP

dg_tofromxmm1 PROC EXPORT
    movd rax, xmm1 ; movd %xmm1, %rax
    movd xmm1, rcx ; movd %rdi, %xmm1
    ret

dg_tofromxmm1 ENDP


dg_lobit PROC EXPORT
    or rcx, rcx
    jz dg_lobitthen1
    bsf rax, rcx  ; bsf %rdi, %rax
    ret
dg_lobitthen1:
    xor rax, rax
    not rax
    ret

dg_lobit ENDP

dg_hibit PROC EXPORT
    or rcx, rcx
    jz dg_hibitthen1
    bsr rax, rcx ; bsr %rdi, %rax
    ret
dg_hibitthen1:
    xor rax, rax
    not rax
    ret

dg_hibit ENDP

dg_countbits PROC EXPORT
    popcnt rax, rcx ; popcnt %rdi, %rax
    ret

dg_countbits ENDP


;   UINT128 dg_touleb128 (UINT64 u, UINT128* presult)

dg_touleb128 PROC EXPORT

    ; // rcx = u, rdx = presult
    mov r8, rcx ; r8 = u
    mov r9, rdx ; r9 = presult
    xor rdx, rdx
    xor rax, rax
    xor ch, ch

dg_touleb128_begin:
      inc ch ; incb %ch
      shrd rax, rdx, 7 ; shrdq $7, %rdx, %rax
      shrd rdx, r8, 7  ; shrdq $7, %rdi, %rdx
      shr r8, 7        ; shrq $7, %rdi

    jz dg_touleb128_repeat
      shrd rax, rdx, 1 ; shrdq $1, %rdx, %rax
      stc
      rcr rdx, 1       ; rcrq $1, %rdx
      jmp dg_touleb128_begin  
    
dg_touleb128_repeat: 
    shrd rax, rdx, 1   ; shrdq $1, %rdx, %rax    
    clc
    rcr rdx, 1         ; rcrq $1, %rdx

    ; // shrd shift is limited to 63 bits so
    cmp ch, 9          ; cmp $9, %ch

    jnc dg_touleb128_then

        ; //  if count is <= 8 need to do this
        mov rax, rdx ; movq %rdx, %rax // copy rdx to rax.. this is shift 64
        xor rdx, rdx
        mov dl, ch  ; movb %ch, %dl
        bswap rdx

        mov cl, 8    ; movb $8, %cl
        sub cl, ch   ; subb %ch, %cl
        shl cl, 3    ; shlb $3, %cl
        shr rax, cl  ; shrq %cl, %rax // count = 0 case = no shift
        mov [r9], rax
        mov [r9+8], rdx
        ret

dg_touleb128_then:

    mov cl, 010h       ; movb $0x10, %cl
    sub cl, ch         ; subb %ch, %cl
    shl cl, 3          ; shlb $3, %cl
    shrd rax, rdx, cl  ; shrdq %cl, %rdx, %rax
    shr rdx, cl        ; shrq %cl, %rdx

    bswap rdx
    mov dl, ch         ; movb %ch, %dl
    bswap rdx

    mov [r9], rax
    mov [r9+8], rdx
    
    ret  ; // rdx:rax = result and [presult] = result

dg_touleb128 ENDP


;    UINT128 dg_shrd (
;        UINT128* pu,         rcx     // RSI : RDI also the result
;        UINT64 count);       rdx     // RDX  

dg_shrd PROC EXPORT

    ; // shrdq is limited to 63 bits so, doing >=64 this way
    xchg rdx, rcx      ; movb %dl, %cl

    test cl, 040h      ; testb $0x40, %cl
    jz dg_shrd_then1 

        ; // shifting 64 or more bits
        sub cl, 040h       ; subb $0x40, %cl
        mov rax, [rdx + 8] ; movq %rsi, %rax
        shr rax, cl        ; shrq %cl, %rax     // shift hardware masked to be from 0 to 63
        mov qword ptr [rdx+8], 0     ;
        mov [rdx], rax     ; 
        
        ret 

dg_shrd_then1:

    ; // shifting 63 or less bits
    mov rax, [rdx]         ; movq %rdi, %rax
    mov r8,  [rdx + 8]     ; movq %rsi, %rdx
    shrd rax, r8, cl       ; shrdq %cl, %rdx, %rax  // shift hardware masked to be from 0 to 63
    shr r8, cl             ; shrq %cl, %rdx         // shift hardware masked to be from 0 to 63
    mov [rdx+8], r8
    mov [rdx], rax
    ret

dg_shrd ENDP


;    UINT128 dg_ashrd (
;        UINT128* pu,    rcx     // RSI : RDI  also result
;        UINT64 count);  rdx     // RDX

dg_ashrd PROC EXPORT

    ; // shrdq is limited to 63 bits so, doing >=64 this way
    xchg rdx, rcx   ; movb %dl, %cl
    test cl, 040h  ; testb $0x40, %cl
    jz dg_ashrd_then1 

        ; // shifting 64 or more bits
        ; // subb $0x40, %cl  // not needed due to hardware masking
        mov rax, [rdx+8]    ; movq %rsi, %rax
        mov r8, rax         ; movq %rax, %rdx
        sar r8, 03fh        ; sarq $0x3F, %rdx
        sar rax, cl         ; sarq %cl, %rax     // shift hardware masked to be from 0 to 63
        mov [rdx + 8], r8
        mov [rdx], rax
        ret 

dg_ashrd_then1:

    ; // shifting 63 or less bits
    mov rax, [rdx]     ; movq %rdi, %rax
    mov r8,  [rdx+8]   ; movq %rsi, %rdx
    shrd rax, r8, cl   ; shrdq %cl, %rdx, %rax  // shift hardware masked to be from 0 to 63
    sar r8, cl         ; sarq %cl, %rdx         // shift hardware masked to be from 0 to 63
    mov [rdx + 8], r8
    mov [rdx], rax
    ret

dg_ashrd ENDP


dg_shld PROC EXPORT

    ; // shrdq is limited to 63 bits so, doing >=64 this way
    xchg rdx, rcx    ; movb %dl, %cl
    test cl, 040h  ; testb $0x40, %cl
    jz dg_shld_then1

        ; // subb $0x40, %cl // not needed due to hardware masking
        mov r8, [rdx]     ; movq %rdi, %rdx
        xor rax, rax
        shl r8, cl     ; shlq %cl, %rdx     // shift hardware masked to be from 0 to 63
        mov [rdx], rax
        mov [rdx+8], r8
        ret 

dg_shld_then1:

    mov r8, [rdx + 8]        ; movq %rdi, %rax
    mov rax, [rdx]; movq %rsi, %rdx
    shld r8, rax, cl   ; shldq %cl, %rax, %rdx  // shift hardware masked to be from 0 to 63
    shl rax, cl        ; shlq %cl, %rax         // shift hardware masked to be from 0 to 63
    mov [rdx], rax
    mov [rdx+8], r8 
    ret

dg_shld ENDP


;    UINT64 dg_gethctwolength (UINT128* pud)  rcx // rsi : rdi
    

dg_gethctwolength PROC EXPORT

    xor rax, rax
    mov al, [rcx+15]
    ; bswap rcx
    ; mov al, cl  ; movb %sil, %al
    ret

dg_gethctwolength ENDP



;    const char* dg_hctwostore (
;        unsigned char* pdest,    rcx        // rdi
;        UINT128* pud);           rdx        // rdx : rsi


dg_hctwostoresub PROC EXPORT FRAME
    push rsi
    .pushreg rsi
    push rdi
    .pushreg rdi
    .endprolog
    mov rdi, rcx
    mov rsi, [rdx]
    mov rdx, [rdx+8]

    bswap rdx      ; bswapq %rdx
    mov cl, dl   ; movb %dl, %cl
    mov rax, rsi  ; movq %rsi, %rax
    xor dl, dl
    bswap rdx      ; bswapq %rdx
    

    cmp cl, 010h  ; cmpb $0x10, %cl
    jnc dg_hctwostorethen4

    cmp cl, 8     ; cmpb $8, %cl
    jc dg_hctwostorethen1
      sub cl, 8   ; subb $8, %cl

      mov [rdi], rsi  ; movq %rsi, (%rdi)
      add rdi, 8      ; addq $8, %rdi
      mov rax, rdx    ; movq %rdx, %rax
dg_hctwostorethen1:

    cmp cl, 4         ; cmpb $4, %cl
    jc dg_hctwostorethen2
      sub cl, 4       ; subb $4, %cl
      mov [rdi], eax  ; movl %eax, (%rdi)
      add rdi, 4      ; addq $4, %rdi
      shr rax, 32     ; shrq $32, %rax
dg_hctwostorethen2:

    cmp cl, 2         ; cmpb $2, %cl
    jc dg_hctwostorethen3
      sub cl, 2       ; subb $2, %cl
      mov [rdi], ax   ; movw %ax, (%rdi)
      add rdi, 2      ; addq $2, %rdi
      shr eax, 16     ; shrl $16, %eax
dg_hctwostorethen3:

    cmp cl, 1         ; cmpb $1, %cl
    jc dg_hctwostorethen4
    mov [rdi], al     ; movb %al, (%rdi)
dg_hctwostorethen4:     

    ; mov rax, dg_success  ; leaq _dg_success(%rip), %rax
    pop rdi
    pop rsi
    ret
dg_hctwostoresub ENDP


; need to make this signed...
dg_f64infinity DQ 7FF0000000000000h


dg_tentothex PROC EXPORT

  cmp rcx, 309                       ; cmpq $309, %rdi
  jc dg_tentothexthen1
  
    movq xmm0, qword ptr [dg_f64infinity]     ; vmovq _dg_f64infinity(%rip), %xmm0
    ret
    
dg_tentothexthen1:

  mov eax, 1                         ; mov $1, %eax
  cvtsi2sd xmm0, eax                 ; cvtsi2sd %eax, %xmm0
  
  mov eax, 10                        ; mov $10, %eax
  cvtsi2sd xmm1, eax                 ; cvtsi2sd %eax, %xmm1
  
dg_tentothexbegin:
  
  test rcx, rcx                      ; test %rdi, %rdi
  jnz dg_tentothexthen2
  
    ret
    
dg_tentothexthen2:

  shr rcx, 1                         ; shr $1, %rdi
  
  jnc dg_tentothexthen3
  
    mulsd xmm0, xmm1                 ; mulsd %xmm1, %xmm0
    
dg_tentothexthen3:
  
  mulsd xmm1, xmm1                   ; mulsd %xmm1, %xmm1
  
  jmp dg_tentothexbegin

dg_tentothex ENDP
  

dg_i64tof64 PROC EXPORT
    cvtsi2sd xmm0, rcx  ; cvtsi2sd %rdi, %xmm0
    ret
dg_i64tof64 ENDP

    
dg_timeslog2 PROC EXPORT

    mov rax, 301029995663981          ; movq $301029995663981, %rax
    imul rcx                          ; imul %rdi
    mov rcx, 1000000000000000         ; movq $1000000000000000, %rdi
    idiv rcx                          ; idiv %rdi
    ret          ; // since the number in rdi is shrinking... this should work

dg_timeslog2 ENDP

    
dg_f64toi64 PROC EXPORT
    cvttsd2si rax, xmm0    ; cvttsd2si %xmm0, %rax
    ret
dg_f64toi64 ENDP

    
dg_roundf64tonearesteven PROC EXPORT
    roundsd xmm0, xmm0, 0    ; roundsd $0, %xmm0, %xmm0
    ret
dg_roundf64tonearesteven ENDP

    
dg_roundf64tonegativeinfinity PROC EXPORT
    roundsd xmm0, xmm0, 1   ; roundsd $1, %xmm0, %xmm0
    ret
dg_roundf64tonegativeinfinity ENDP
 

dg_f64sqrt PROC EXPORT
    sqrtsd xmm0, xmm0        ; sqrtsd %xmm0, %xmm0
    ret
dg_f64sqrt ENDP
    

dg_f64cos PROC EXPORT
    ; emms
    fninit
    sub rsp, 8                    ; subq $8, %rsp
    movq qword ptr [rsp], xmm0    ; movq %xmm0, (%rsp)
    fld qword ptr [rsp]           ; fldl (%rsp)
    fcos
    fnclex
    fstp qword ptr [rsp]          ; fstpl (%rsp)
    movq xmm0, qword ptr [rsp]    ; movq (%rsp), %xmm0
    add rsp, 8                    ; addq $8, %rsp
    ret
dg_f64cos ENDP


dg_f64sin PROC EXPORT
    ; emms
    fninit
    sub rsp, 8                   ; subq $8, %rsp
    movq qword ptr [rsp], xmm0   ; movq %xmm0, (%rsp)
    fld qword ptr [rsp]          ; fldl (%rsp)
    fsin
    fnclex
    fstp qword ptr [rsp]         ; fstpl (%rsp)
    movq xmm0, qword ptr [rsp]   ; movq (%rsp), %xmm0
    add rsp, 8                   ; addq $8, %rsp
    ret
dg_f64sin ENDP


dg_f64tan PROC EXPORT
    ; emms
    fninit
    sub rsp, 8        ; subq $8, %rsp
    movq qword ptr [rsp], xmm0  ; movq %xmm0, (%rsp)
    fld qword ptr [rsp]        ; fldl (%rsp)
    fptan
    fucomp
    fnclex
    fstp qword ptr [rsp]      ; fstpl (%rsp)
    movq xmm0, qword ptr [rsp]  ; movq (%rsp), %xmm0
    add rsp, 8       ; addq $8, %rsp
    ret
dg_f64tan ENDP


dg_f64sincos PROC EXPORT ; cosresult = dg_f64sincos(angle, psinresult)
    ; xmm0 = angle
    ; rdx = psinresult
    ; emms
    fninit
    sub rsp, 8       ; subq $8, %rsp
    movq qword ptr [rsp], xmm0  ;  movq %xmm0, (%rsp)
    fld qword ptr [rsp]       ; fldl (%rsp)
    fsincos
    fnclex
    fstp qword ptr [rsp]        ; fstpl (%rsp)
    movq xmm0, qword ptr [rsp]  ;  movq (%rsp), %xmm0 // cos
    fstp qword ptr [rsp]        ; fstpl (%rsp)
    pop qword ptr [rdx]         ; // sin
    ret
dg_f64sincos ENDP


dg_f64fyl2x PROC EXPORT
    ; emms
    fninit
    sub rsp, 8                  ; subq $8, %rsp
    movq qword ptr [rsp], xmm1  ; movq %xmm1, (%rsp) // x
    fld qword ptr [rsp]         ; fldl (%rsp)
    movq qword ptr [rsp], xmm0  ; movq %xmm0, (%rsp) // y
    fld qword ptr [rsp]         ; fldl (%rsp)
    fyl2x
    fnclex
    fstp qword ptr [rsp]        ; fstpl (%rsp)
    movq xmm0, qword ptr [rsp]  ; movq (%rsp), %xmm0
    add rsp, 8                  ; addq $8, %rsp
    ret
dg_f64fyl2x ENDP

  
dg_f64fyl2xp1 PROC EXPORT
    ; emms
    fninit
    sub rsp, 8                  ; subq $8, %rsp
    movq qword ptr [rsp], xmm1  ; movq %xmm1, (%rsp) // x
    fld qword ptr [rsp]         ; fldl (%rsp)
    movq qword ptr [rsp], xmm0  ; movq %xmm0, (%rsp) // y
    fld qword ptr [rsp]         ; fldl (%rsp)
    fyl2xp1
    fnclex
    fstp qword ptr [rsp]        ; fstpl (%rsp)
    movq xmm0, qword ptr [rsp]  ; movq (%rsp), %xmm0
    add rsp, 8                  ; addq $8, %rsp
    ret
dg_f64fyl2xp1 ENDP

     
dg_f64f2xm1 PROC EXPORT
    ; emms
    fninit
    sub rsp, 8                  ; subq $8, %rsp
    movq qword ptr [rsp], xmm0  ; movq %xmm0, (%rsp) // x
    fld qword ptr [rsp]         ; fldl (%rsp)
    f2xm1
    fnclex
    fstp qword ptr [rsp]        ; fstpl (%rsp)
    movq xmm0, qword ptr [rsp]  ; movq (%rsp), %xmm0
    add rsp, 8                  ; addq $8, %rsp
    ret
dg_f64f2xm1 ENDP


dg_truncatef64 PROC EXPORT
    roundsd xmm0, xmm0, 3       ;  roundsd $3, %xmm0, %xmm0
    ret
dg_truncatef64 ENDP

dg_f64getfractional PROC EXPORT
    roundsd xmm1, xmm0, 3       ; roundsd $3, %xmm0, %xmm1
    subsd xmm0, xmm1            ; subsd %xmm1, %xmm0
    ret
dg_f64getfractional ENDP

 COMMENT!   
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
 !
 

dg_f64logbase2of10 PROC EXPORT
    ; emms
    fninit
    sub rsp, 8                   ; subq $8, %rsp
    fldl2t
    fstp qword ptr [rsp]         ; fstpl (%rsp)
    movq xmm0, qword ptr [rsp]   ; movq (%rsp), %xmm0
    add rsp, 8                   ; addq $8, %rsp
    ret
dg_f64logbase2of10 ENDP

   
dg_f64logbase2ofe PROC EXPORT
    ; emms
    fninit
    sub rsp, 8                   ; subq $8, %rsp
    fldl2e
    fstp qword ptr [rsp]         ; fstpl (%rsp)
    movq xmm0, qword ptr [rsp]   ; movq (%rsp), %xmm0
    add rsp, 8                   ; addq $8, %rsp
    ret
dg_f64logbase2ofe ENDP
    
dg_f64fpatan PROC EXPORT
    ; emms
    fninit
    sub rsp, 8                   ; subq $8, %rsp
    movq qword ptr [rsp], xmm1   ; movq %xmm1, (%rsp) // y
    fld qword ptr [rsp]          ; fldl (%rsp)
    movq qword ptr [rsp], xmm0   ; movq %xmm0, (%rsp) // x
    fld qword ptr [rsp]          ; fldl (%rsp)
    fpatan
    fnclex
    fstp qword ptr [rsp]         ; fstpl (%rsp)
    movq xmm0, qword ptr [rsp]   ; movq (%rsp), %xmm0
    add rsp, 8                   ; addq $8, %rsp
    ret
 dg_f64fpatan ENDP
 
dg_f64tof32 PROC EXPORT
    cvtsd2ss xmm0, xmm0          ; // does not clear bits 32 to 63
    ret
dg_f64tof32 ENDP
    
dg_f32tof64 PROC EXPORT
    cvtss2sd xmm0, xmm0
    ret
dg_f32tof64 ENDP


 ;   UINT128 dg_mstarslash (
 ;     INT64* pnd1,  rcx      // rsi
 ;     INT64 n1,     rdx      // rdi
 ;     INT64 +n2)    r8       // rdx
 ;   returns (nd1 * n1) / abs(n2) rdx:rax (remainder in r8)


dg_mstarslash PROC EXPORT
    
    push rdi
    push rsi
    push rcx
    mov rdi, [rcx]
    mov rsi, [rcx+8]
    ; mov rdx, rdx
    mov rcx, r8

    ; // if rcx is zero then return largest number
    xor r10, r10 ; // for sign
    or rcx, rcx
    
    jnz dg_mstarslashthen1
      mov rdx, 7fffffffffffffffh      ; movq $0x7fffffffffffffff, %rdx
      mov rax, -1                      ; movq $0xffffffffffffffff, %rax
      pop rcx
      mov [rcx], rax
      mov [rcx+8], rdx
      pop rsi
      pop rdi
      ret
    dg_mstarslashthen1:
    
    ; // figure out sign of result and get absolute values
    jns dg_mstarslashthen2
        neg rcx
        not r10
    dg_mstarslashthen2:
    
    or rdx, rdx    
    jns dg_mstarslashthen3
        neg rdx
        not r10
    dg_mstarslashthen3:
    
    or rsi, rsi
    jns dg_mstarslashthen4    
        not rsi
        not rdi
        add rdi, 1 ; addq $1, %rdi
        adc rsi, 0 ; adcq $0, %rsi
        not r10
    dg_mstarslashthen4:
        
    ; // r10 now has sign
    ; // rsi:rdi, rdx, and rcx are now positive
    mov r11, rdx ; movq %rdx, %r11
    mov rax, rdx ; movq %rdx, %rax
    mul rsi
    mov r9, rdx  ; movq %rdx, %r9 // intermedhi   
    mov r8, rax  ; movq %rax, %r8 // intermedmid  
    
    mov rax, r11 ; movq %r11, %rax  
    mul rdi        
    add r8, rdx  ; addq %rdx, %r8   
    adc r9, 0    ; adcq $0, %r9     
    mov rsi, rax ; movq %rax, %rsi   
    
    ; // r9:r8:rsi has intermediate number
    ; // rcx has denominator
    ; // sign is in r10
    
    xor rdx, rdx
    
    mov rax, r9 ; movq %r9, %rax
    div rcx
    
    or rax, rax
    jz dg_mstarslashthen5 ; // if too big for 128 result, return largest
    
      ; movq $0x7fffffffffffffff, %rdx
      ; movq $0xffffffffffffffff, %rax
      mov rdx, 7fffffffffffffffh ; movq $0x7fffffffffffffff, %rdx
      mov rax, -1 ; 0xffffffffffffffff ; movq $0xffffffffffffffff, %rax\\

      pop rcx
      mov [rcx], rax
      mov [rcx+8], rdx
      pop rsi
      pop rdi
      
      ret
    
    ; // figure out sign of result and get absolute values
    dg_mstarslashthen5:
    
    ; // don't need to save hi result because it's 0
    
    mov rax, r8 ; movq %r8, %rax
    div rcx
    mov r8, rax ; movq %rax, %r8
    
    mov rax, rsi ; movq %rsi, %rax
    div rcx
    
    ; //r8:rax now holds result, rdx has remainder
    xchg rdx, r8 ; xchg %r8, %rdx
    
    ; // rdx:rax now holds result , r8 holds remainder
    ; // if its too big for signed number return largest
    or rdx, rdx
    jns dg_mstarslashthen6
        ;  movq $0x7fffffffffffffff, %rdx
        ;  movq $0xffffffffffffffff, %rax
        mov rdx, 7fffffffffffffffh ; movq $0x7fffffffffffffff, %rdx
        mov rax, -1 ; 0xffffffffffffffff ; movq $0xffffffffffffffff, %rax

        pop rcx
        mov [rcx], rax
        mov [rcx+8], rdx
        pop rsi
        pop rdi
        ret
    dg_mstarslashthen6:
    
    ; // negate result if it's negative
    or r10, r10
    jns dg_mstarslashthen7 
      not rdx
      not rax
      add rax, 1 ; addq $1, %rax
      adc rax, 0 ; adcq $0, %rdx
    dg_mstarslashthen7:

    pop rcx
    mov [rcx], rax
    mov [rcx+8], rdx
    pop rsi
    pop rdi
    ret

dg_mstarslash ENDP

; void dg_mplus(UINT64* pints) // rcx = pints
;   // pints[0] = xlo  unsigned
;   // pints[1] = xhi  unsigned
;   // pints[2] = n    signed

dg_mplus PROC EXPORT 
  mov rax, [rcx+16]
  cqo
  add [rcx], rax
  adc [rcx+8], rdx
  ret
dg_mplus ENDP


dg_random PROC EXPORT

    rdseed rax
    jnc dg_random
    ret

dg_random ENDP


; /* void dg_savequitstate (UINT64* pquitstate) */
dg_savequitstate PROC EXPORT

; //  rcx rdi = pquitstate
    
    mov [rcx], rbp        ; movq %rbp, 0x00(%rdi)
    mov [rcx+8], rsp      ; movq %rsp, 0x08(%rdi)
    add qword ptr [rcx+8], 8        ; addq $8, 0x08(%rdi) // to drop the return address
    pushfq
    pop rax
    mov [rcx+10h], rax    ; movq %rax, 0x10(%rdi)
    ret

 dg_savequitstate ENDP


; /* void dg_restorequitstate (UINT64* pquitstate) */
dg_restorequitstate PROC EXPORT
    
    ; /* need to jump so that stack frame is correct
    ;    we are eating everything including first return and
    ;    whatever parameters from first call out of quit */

      pop rax              ; /* return address */
; //    rcx rdi = pquitstate
    
      mov rdx, [rcx+10]    ; movq 0x10(%rdi), %rdx  /* doing eflags first */
      push rdx
      popfq
      mov rsp, [rcx+8]     ; movq 0x08(%rdi), %rsp  /* restore stack to state without pquitstate on it */
      mov rbp, [rcx+10]    ; movq 0x00(%rdi), %rbp    
      jmp rax

dg_restorequitstate ENDP


; void dg_dplus (UINT128* pints) // points to two back to back UINT128s in memory
dg_dplus PROC EXPORT
  mov rax, [rcx + 10h]
  mov rdx, [rcx + 18h]
  add [rcx], rax
  adc [rcx + 8h], rdx
  ret
dg_dplus ENDP

; void dg_dminus (UINT128* pints)
dg_dminus PROC EXPORT
  mov rax, [rcx + 10h]
  mov rdx, [rcx + 18h]
  sub [rcx], rax
  sbb [rcx + 8h], rdx
  ret
dg_dminus ENDP

; note: z flag does not propogate through multi cell subtracts

; void dg_dulessthan (UINT128* pints)
dg_dulessthan PROC EXPORT
  xor r8, r8
  mov rax, [rcx + 10h]
  mov rdx, [rcx + 18h]
  sub [rcx], rax
  sbb [rcx + 8h], rdx
  jnc dg_ulessthanthen1
    dec r8
  dg_ulessthanthen1:
  mov [rcx], r8
  ret
dg_dulessthan ENDP

; void dg_dugreaterequalthan (UINT128* pints)
dg_dugreaterequalthan PROC EXPORT
  xor r8, r8
  mov rax, [rcx + 10h]
  mov rdx, [rcx + 18h]
  sub [rcx], rax
  sbb [rcx + 8h], rdx
  jc dg_dugreaterequalthanthen1
    dec r8
  dg_dugreaterequalthanthen1:
  mov [rcx], r8
  ret
dg_dugreaterequalthan ENDP

; void dg_dlessthan (UINT128* pints)
dg_dlessthan PROC EXPORT
  xor r8, r8
  mov rax, [rcx + 10h]
  mov rdx, [rcx + 18h]
  sub [rcx], rax
  sbb [rcx + 8h], rdx
  jge dg_dlessthanthen1
    dec r8
  dg_dlessthanthen1:
  mov [rcx], r8
  ret
dg_dlessthan ENDP

; void dg_dgreaterequalthan (UINT128* pints)
dg_dgreaterequalthan PROC EXPORT
  xor r8, r8
  mov rax, [rcx + 10h]
  mov rdx, [rcx + 18h]
  sub [rcx], rax
  sbb [rcx + 8h], rdx
  jl dg_dgreaterequalthanthen1
    dec r8
  dg_dgreaterequalthanthen1:
  mov [rcx], r8
  ret
dg_dgreaterequalthan ENDP

; void dg_dumin (UINT128* pints)
dg_dumin PROC EXPORT
  mov rax, [rcx + 10h]
  mov rdx, [rcx + 18h]
  mov r8, [rcx + 8h]
  cmp [rcx], rax
  sbb r8, rdx
  jc dg_duminthen1
    mov [rcx], rax
    mov [rcx+8], rdx
  dg_duminthen1:
  ret
dg_dumin ENDP

; void dg_dumax (UINT128* pints)
dg_dumax PROC EXPORT
  mov rax, [rcx + 10h]
  mov rdx, [rcx + 18h]
  mov r8, [rcx + 8h]
  cmp [rcx], rax
  sbb r8, rdx
  jnc dg_dumaxthen1
    mov [rcx], rax
    mov [rcx+8], rdx
  dg_dumaxthen1:
  ret
dg_dumax ENDP

; void dg_dmin (UINT128* pints)
dg_dmin PROC EXPORT
  mov rax, [rcx + 10h]
  mov rdx, [rcx + 18h]
  mov r8, [rcx + 8h]
  cmp [rcx], rax
  sbb r8, rdx
  jl dg_dminthen1
    mov [rcx], rax
    mov [rcx+8], rdx
  dg_dminthen1:
  ret
dg_dmin ENDP

; void dg_dmax (UINT128* pints)
dg_dmax PROC EXPORT
  mov rax, [rcx + 10h]
  mov rdx, [rcx + 18h]
  mov r8, [rcx + 8h]
  cmp [rcx], rax
  sbb r8, rdx
  jge dg_dmaxthen1
    mov [rcx], rax
    mov [rcx+8], rdx
  dg_dmaxthen1:
  ret
dg_dmax ENDP

; void dg_dnegate (UINT128* pints)
dg_dnegate PROC EXPORT
  mov rdx, [rcx + 8]
  mov rax, [rcx] 
  not rax
  not rdx
  add rax, 1
  adc rdx, 0
  mov [rcx], rax
  mov [rcx+8], rdx
  ret
dg_dnegate ENDP

; void dg_dabs (UINT128* pints)
dg_dabs proc export
  mov rdx, [rcx + 8]
  test rdx, rdx
  jns dg_dabsthen1
    mov rax, [rcx] 
    not rax
    not rdx
    add rax, 1
    adc rdx, 0
    mov [rcx], rax
    mov [rcx+8], rdx
  dg_dabsthen1:
  ret
dg_dabs ENDP

dg_returntestuint128 PROC EXPORT
  mov rax, -5
  mov rdx, -1
  ret
dg_returntestuint128 ENDP

dg_testasmretuint128 PROC EXPORT
  mov rax, rcx
  mov rdx, rcx
  inc rax
  dec rdx
  ret
dg_testasmretuint128 ENDP


; const char* dg_addbytes (
;     unsigned char* psrc,    // rdi // rcx
;     unsigned char* pdest,   // rsi // rdx
;     UINT64 stringlength,    // rdx // r8
;     UINT64* pcarryout);     // rcx // r9

dg_addbytessub PROC EXPORT FRAME

    ; push rdi
    ; .pushreg rdi
    ; push rsi
    ; .pushreg rsi
    
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog        
    
    ; movq rsi, rcx   ; /* psrc->rsi */
    ; movq rdi, rdx   ; /* pdest->rdi */
    ; movq rcx, r8    ; /* stringlength->rcx */
    ; movq rdx, r9    ; /* pcarryout->rdx */
    
    xchg r8, rcx      ; /* stringlength->rcx */
                      ; /* psrc->r8 */
                      ; /* pdest->rdx */
                      ; /* pcarryout->r9 */
    xor rax, rax

    mov [r9], rax     ; mov (rdx), rax ; movq %rax, (%rdx)
    
    clc 
    
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx     ; orq %rcx, %rcx
    jz dg_addbytesthen1
    
    dg_addbytesbegin1:
    
      mov al, [r8]   ; mov al, (rsi)  ; movb (%rsi), %al
      adc [rdx], al  ; acd (rdi), al  ; adcb %al, (%rdi)
      inc r8         ; inc rsi        ; incq %rsi
      inc rdx        ; inc rdi        ; incq %rdi
    
    ; loop dg_addbytesbegin1
      dec rcx
    jnz dg_addbytesbegin1
    
    jnc dg_addbytesthen1
    
    inc qword ptr [r9]      ; inc (rdx)        ; incq (%rdx) // set carryout to 1

    dg_addbytesthen1:
    
    ; lea _dg_success(%rip), %rax
    popfq
    ; pop rsi
    ; pop rdi
    ret

  dg_addbytessub ENDP
  

; const char* dg_adcbytes (
;     unsigned char* psrc,    // rdi // rcx
;     unsigned char* pdest,   // rsi // rdx
;     UINT64 stringlength,    // rdx // r8
;     UINT64* pcarryinout);   // rcx // r9

dg_adcbytessub PROC EXPORT FRAME
    
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog        
    
    xchg r8, rcx      ; /* stringlength->rcx */
                      ; /* psrc->r8 */
                      ; /* pdest->rdx */
                      ; /* pcarryinout->r9 */
    xor rax, rax

    xchg [r9], rax
    
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx     ; orq %rcx, %rcx
    jz dg_adcbytesthen1
    
    shr al, 1  ; /* move the carryin to the carry flag */
    
    dg_adcbytesbegin1:
    
      mov al, [r8]   ; movb (%rsi), %al
      adc [rdx], al  ; adcb %al, (%rdi)
      inc r8         ; incq %rsi
      inc rdx        ; incq %rdi
    
    ; loop dg_adcbytesbegin1
      dec rcx
    jnz dg_adcbytesbegin1
    
    jnc dg_adcbytesthen1
    
    inc qword ptr [r9]         ; inc (rdx)        ; incq (%rdx) // set carryout to 1

    dg_adcbytesthen1:
    
    ; lea _dg_success(%rip), %rax
    popfq
    ret

  dg_adcbytessub ENDP
  
  

;    const char* dg_sbbbytes (
;        unsigned char* psrc,    // rdi  // rcx
;        unsigned char* pdest,   // rsi  // rdx
;        UINT64 stringlength,    // rdx  // r8
;        UINT64* pborrowinout);  // rcx  // r9

dg_sbbbytessub PROC EXPORT FRAME

    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog  
    
    xchg r8, rcx     ; /* stringlength->rcx   */
                     ; /* psrc->r8            */
                     ; /* pdest->rdx          */
                     ; /* pborrowinout->r9    */
                     
    xor rax, rax
    
    xchg [r9], rax
    
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx      ; /* orq clears the carry and must come before shrb */
    
    jz dg_sbbbytesthen1
    
      shr al, 1           ; /* move the borrowin to the carry flag */
    
    dg_sbbbytesbegin1:

      mov al, [r8]    ; movb (%rsi), %al
      sbb [rdx], al   ; sbbb %al, (%rdi)
      inc r8
      inc rdx
      
    ; loop dg_sbbbytesbegin1
      dec rcx
      jnz dg_sbbbytesbegin1
    
    jnc dg_sbbbytesthen1
    
      inc qword ptr [r9]        ; // set borrowout to 1

dg_sbbbytesthen1:

    ; leaq _dg_success(%rip), %rax
    popfq
    ret
    
dg_sbbbytessub ENDP



;    const char* dg_andbytes (
;        unsigned char* psrc,    // rdi  // rcx
;        unsigned char* pdest,   // rsi  // rdx
;        UINT64 stringlength);   // rdx  // r8

dg_andbytessub PROC EXPORT FRAME

    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog  

    xchg r8, rcx    ; /* stringlength->rcx */
                    ; /* psrc->r8 */
                    ; /* pdest->rdx */ 
    
  dg_andbytesbegin1:

    mov al, [r8]    ; movb (%rsi), %al
    and [rdx], al   ; andb %al, (%rdi)
    inc r8          ; incq %rdi
    inc rdx         ; incq %rsi
    
  ; loop dg_andbytesbegin1
    dec rcx
  jnz dg_andbytesbegin1
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret
    
dg_andbytessub ENDP


;    const char* dg_orbytes (
;        unsigned char* psrc,    // rdi  // rcx
;        unsigned char* pdest,   // rsi  // rdx
;        UINT64 stringlength);   // rdx  // r8

dg_orbytessub PROC EXPORT FRAME

    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog  

    xchg r8, rcx    ; /* stringlength->rcx */
                    ; /* psrc->r8 */
                    ; /* pdest->rdx */ 
    
  dg_orbytesbegin1:

    mov al, [r8]    ; movb (%rsi), %al
    or [rdx], al   ; andb %al, (%rdi)
    inc r8          ; incq %rdi
    inc rdx         ; incq %rsi
    
  ; loop dg_orbytesbegin1
    dec rcx
  jnz dg_orbytesbegin1
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret
    
dg_orbytessub ENDP


;    const char* dg_xorbytes (
;        unsigned char* psrc,    // rdi  // rcx
;        unsigned char* pdest,   // rsi  // rdx
;        UINT64 stringlength);   // rdx  // r8

dg_xorbytessub PROC EXPORT FRAME

    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog  

    xchg r8, rcx    ; /* stringlength->rcx */
                    ; /* psrc->r8 */
                    ; /* pdest->rdx */ 
    
  dg_xorbytesbegin1:

    mov al, [r8]    ; movb (%rsi), %al
    xor [rdx], al   ; andb %al, (%rdi)
    inc r8          ; incq %rdi
    inc rdx         ; incq %rsi
    
  ; loop dg_xorbytesbegin1
    dec rcx
  jnz dg_xorbytesbegin1
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret
    
dg_xorbytessub ENDP


;    const char* dg_nandbytes (
;        unsigned char* psrc,    // rdi  // rcx
;        unsigned char* pdest,   // rsi  // rdx
;        UINT64 stringlength);   // rdx  // r8

dg_nandbytessub PROC EXPORT FRAME

    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog  

    xchg r8, rcx    ; /* stringlength->rcx */
                    ; /* psrc->r8 */
                    ; /* pdest->rdx */ 
    
  dg_nandbytesbegin1:

    mov al, [r8]    ; movb (%rsi), %al
    and al, [rdx]    
    not al
    mov [rdx], al
    inc r8          ; incq %rdi
    inc rdx         ; incq %rsi
    
  ; loop dg_nandbytesbegin1
    dec rcx
  jnz dg_nandbytesbegin1
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret
    
dg_nandbytessub ENDP


;    const char* dg_norbytes (
;        unsigned char* psrc,    // rdi  // rcx
;        unsigned char* pdest,   // rsi  // rdx
;        UINT64 stringlength);   // rdx  // r8

dg_norbytessub PROC EXPORT FRAME

    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog  

    xchg r8, rcx    ; /* stringlength->rcx */
                    ; /* psrc->r8 */
                    ; /* pdest->rdx */ 
    
  dg_norbytesbegin1:

    mov al, [r8]    ; movb (%rsi), %al
    or al, [rdx] 
    not al
    mov [rdx], al
    inc r8          ; incq %rdi
    inc rdx         ; incq %rsi
    
  ; loop dg_norbytesbegin1
    dec rcx
  jnz dg_norbytesbegin1
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret
    
dg_norbytessub ENDP


;    const char* dg_xnorbytes (
;        unsigned char* psrc,    // rdi  // rcx
;        unsigned char* pdest,   // rsi  // rdx
;        UINT64 stringlength);   // rdx  // r8
 
dg_xnorbytessub PROC EXPORT FRAME

    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog  

    xchg r8, rcx    ; /* stringlength->rcx */
                    ; /* psrc->r8 */
                    ; /* pdest->rdx */ 
    
  dg_xnorbytesbegin1:

    mov al, [r8]    ; movb (%rsi), %al
    xor al, [rdx]
    not al
    mov [rdx], al
    inc r8          ; incq %rdi
    inc rdx         ; incq %rsi
    
  ; loop dg_xnorbytesbegin1
    dec rcx
  jnz dg_xnorbytesbegin1
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret
    
dg_xnorbytessub ENDP


;    const char* dg_shlbytes (
;        unsigned char* pdest,    // rdi  // rcx
;        UINT64 stringlength,     // rsi  // rdx
;        UINT64* pcarryout);      // rdx  // r8

dg_shlbytessub PROC EXPORT FRAME
    
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    
    xchg rcx, rdx    ; /* stringlength->rcx */
                     ; /* pdest->rdx */
                     ; /* pcarryout->r8 */
                     
    xor rax, rax     ; xorq %rax, %rax
    mov [r8], rax    ; movq %rax, (%rdx)
    
    ; clc ; or clears the carry
    
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx      ; orq %rcx, %rcx
    
    jz dg_shlbytesthen1
    
    dg_shlbytesbegin1:
      rcl byte ptr [rdx], 1  ; rclb (%rdi)
      inc rdx             ; incq %rdi
    ; loop dg_shlbytesbegin1
      dec rcx
    jnz dg_shlbytesbegin1
    
    jnc dg_shlbytesthen1
    
      inc qword ptr [r8]     ; incq (%rdx) // set carryout to 1

    dg_shlbytesthen1:
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret

dg_shlbytessub ENDP


;    const char* dg_shrbytes (
;        unsigned char* pdest,    // rdi  // rcx
;        UINT64 stringlength,     // rsi  // rdx
;        UINT64* pcarryout);      // rdx  // r8

    
dg_shrbytessub PROC EXPORT FRAME

    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog

    xchg rcx, rdx  ; movq %rsi, %rcx  /* stringlength->rcx */
                   ; /* pdest->rdx */
                   ; /* pcarryout->r8 */
                   
    add rdx, rcx   ; addq %rsi, %rdi
    
    xor rax, rax   ; xorq %rax, %rax

    mov [r8], rax  ; movq %rax, (%rdx)
    
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx    ; orq %rcx, %rcx         /* or clears the carry */
    
    jz dg_shrbytesthen1

    dg_shrbytesbegin1:

      dec rdx              ; decq %rdi
      rcr byte ptr [rdx], 1   ; rcrb (%rdi)
    
    ; loop dg_shrbytesbegin1
      dec rcx
    jnz dg_shrbytesbegin1
    
    jnc dg_shrbytesthen1
    
      inc qword ptr [r8] ; incq (%rdx) // set carryout to 1

dg_shrbytesthen1:
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret

dg_shrbytessub ENDP


;    const char* dg_rclbytes (
;        unsigned char* pdest,    // rdi  // rcx
;        UINT64 stringlength,     // rsi  // rdx
;        UINT64* pcarryinout);    // rdx  // r8
    
dg_rclbytessub PROC EXPORT FRAME
    
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    
    xchg rdx, rcx   ; movq %rsi, %rcx  /* stringlength->rcx */
                    ; /* pdest->rdx */
                    ; /* pcarryinout->r8 */
                     
    xor rax, rax    ; xorq %rax, %rax

    xchg qword ptr [r8], rax  ; xchgq %rax, (%rdx)
    
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx     ; orq %rcx, %rcx  /* orq clears the carry and must come before shrb */
    jz dg_rclbytesthen1
    
    shr al, 1          ; shrb %al  /* move the carryin to the carry */ 
    
    dg_rclbytebegin1:
      rcl byte ptr [rdx], 1  ; rclb (%rdi)
      inc rdx             ; incq %rdi
    ; loop dg_rclbytebegin1
      dec rcx
    jnz dg_rclbytebegin1
    
    jnc dg_rclbytesthen1
    
    inc qword ptr [r8]    ; incq (%rdx) // set carryout to 1

dg_rclbytesthen1:
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret
    
dg_rclbytessub ENDP


;    const char* dg_rcrbytes (
;        unsigned char* pdest,    // rdi  // rcx
;        UINT64 stringlength,     // rsi  // rdx
;        UINT64* pcarryinout);    // rdx  // r8
    
dg_rcrbytessub PROC EXPORT FRAME
    
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    
    xchg rcx, rdx    ; /* stringlength->rcx */
                     ; /* pdest->rdx */
                     ; /* pcarryinout->r8 */
    
    ; // move pdest to character after string
    add rdx, rcx
    
    ; // clear pcarryinout                
    xor rax, rax
    xchg [r8], rax
    
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx  ; /* orq clears the carry and must come before shrb */
    
    jz dg_rcrbytesthen1
    
    shr al, 1  ; /* move the carryin to the carry */
 
 dg_rcrbytesbegin1: 
      dec rdx  ; decq %rdi
      rcr byte ptr [rdx], 1  ; rcrb (%rdi)
    ; loop dg_rcrbytesbegin1
      dec rcx
    jnz dg_rcrbytesbegin1
    
    jnc dg_rcrbytesthen1
    
    inc qword ptr [r8] ; incq (%rdx) // set carryout to 1

dg_rcrbytesthen1:
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret
dg_rcrbytessub ENDP    


;    const char* dg_sarbytes (
;        unsigned char* pdest,    // rdi  // rcx
;        UINT64 stringlength,     // rsi  // rdx
;        UINT64* pcarryout);      // rdx  // r8
    
dg_sarbytessub PROC EXPORT FRAME

    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    
    xchg rdx, rcx   ; /* stringlength->rcx */
                    ; /* pdest->rdx */
                    ; /* pcarryout->r8 */

    add rdx, rcx    ; addq %rsi, %rdi
                     
    xor rax, rax
    mov [r8], rax   ; movq %rax, (%rdx)
    
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx         
    jz dg_sarbytesthen1
    
    ; /* 1st byte is asr */
    dec rdx ; decq %rdi
    sar byte ptr [rdx], 1 ; sarb (%rdi)
    dec rcx
    
    jz dg_sarbytesthen1

    dg_sarbytesbegin1:
      dec rdx             ; decq %rdi
      rcr byte ptr [rdx], 1  ; rcrb (%rdi)
    ; loop dg_sarbytesbegin1
      dec rcx
    jnz dg_sarbytesbegin1
    
    jnc dg_sarbytesthen1
      inc qword ptr [r8] ; incq (%rdx) // set carryout to 1
    dg_sarbytesthen1:
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret

dg_sarbytessub ENDP


;    const char* dg_notbytes (
;        unsigned char* pdest,    // rdi  // rcx
;        UINT64 stringlength);    // rsi  // rdx
    
dg_notbytessub PROC EXPORT FRAME
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    

    xchg rcx, rdx   ; /* stringlength->rcx */
                    ; /* pdest->rdx */

    
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx
    jz dg_notbytesthen1
    
      dg_notbytesbegin1:
        not byte ptr [rdx] ; notb (%rdi)
        inc rdx            ; incq %rdi
      ; loop dg_notbytesbegin1
        dec rcx
      jnz dg_notbytesbegin1

    dg_notbytesthen1:
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret

dg_notbytessub ENDP


;    const char* dg_reversebytes (
;        unsigned char* pdest,    // rdi  // rcx
;        UINT64 stringlength);    // rsi  // rdx
    
dg_reversebytessub PROC EXPORT FRAME

    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    

    xchg rcx, rdx   ; /* stringlength->rcx */
                    ; /* pdest->rdx */
 
    mov r8, rdx    ; movq %rdi, %rsi
    add r8, rcx    ; addq %rcx, %rsi
    shr rcx, 1
    
    ; /* if rcx was < 2 then do nothing */
    or rcx, rcx
    jz dg_reversebytesthen1
    
      dg_reversebytesbegin1:
        mov al, [rdx] ; movb (%rdi), %al
        dec r8        ; decq %rsi
        xchg al, [r8] ; xchgb (%rsi), %al
        mov [rdx], al ; movb %al, (%rdi)
        inc rdx       ; incq %rdi
      ; loop dg_reversebytesbegin1
        dec rcx
      jnz dg_reversebytesbegin1

    dg_reversebytesthen1:
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret
    
dg_reversebytessub ENDP


;    const char* dg_incbytes (
;        unsigned char* pdest,    // rdi  // rcx
;        UINT64 stringlength,     // rsi  // rdx
;        UINT64* pcarryout);      // rdx  // r8

dg_incbytessub PROC EXPORT FRAME
    
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    
    xchg rcx, rdx    ; /* stringlength->rcx */
                     ; /* pdest->rdx */ 
                     
    xor rax, rax
    mov [r8], rax
    
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx  ; /* this clears the carry */
    jz dg_incbytesthen1
    
      stc
    
      dg_incbytesbegin1:
        adc [rdx], al  ; adc %al, (%rdi)        /* al should be 0 */
        jnc dg_incbytesthen1 ;                  /* if no carry, no need to look at the rest */
        inc rdx
      ; loop dg_incbytesbegin1
        dec rcx
      jnz dg_incbytesbegin1
    
      inc qword ptr [r8]         ; incq (%rdx) // set carryout to 1

    dg_incbytesthen1:
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret

dg_incbytessub ENDP


;    const char* dg_decbytes (
;        unsigned char* pdest,    // rdi  // rcx
;        UINT64 stringlength,     // rsi  // rdx
;        UINT64* pborrowout);     // rdx  // r8

dg_decbytessub PROC EXPORT FRAME
    
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    
    xchg rcx, rdx    ; /* stringlength->rcx */
                     ; /* pdest->rdx */ 
                     
    xor rax, rax
    mov [r8], rax    ; movq %rax, (%rdx)
    
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx      ; /* this clears the carry */
    jz dg_decbytesthen1
    
    stc
    
    dg_decbytesbegin1:
      sbb [rdx], al        ; sbbb %al, (%rdi)        /* al should be 0 */
    jnc dg_decbytesthen1   ; /* if no borrow, no need to look at the rest */
      inc rdx              ; incq %rdi
    ; loop dg_decbytesbegin1
      dec rcx
    jnz dg_decbytesbegin1
    
    inc qword ptr [r8]     ; incq (%rdx) // set borrowout to 1

    dg_decbytesthen1:
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret
    
dg_decbytessub ENDP


;    const char* dg_mulu64tou64s (
;        UINT64* pdest,           // rdi // rcx
;        UINT64* psrc,            // rsi // rdx
;        UINT64  u,               // rdx // r8
;        UINT64  srclengthinu64s, // rcx // r9
;        UINT64* pcarryout);      // r8  // param4 (after 4 shadow)

dg_mulu64tou64ssub PROC EXPORT FRAME

    push rdi
    .pushreg rdi
    push rsi
    .pushreg rsi
    
    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    
    mov rdi, rcx
    mov rsi, rdx
    mov rdx, r8
    mov rcx, r9
    mov r8, [rsp + 040h]

    xor r9, r9 ; // holds carry for next loop
    
    mov r10, rdx   ; movq %rdx, %r10   /* r10 now has u */  ; supposedly don't have to save r10
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx
    jz dg_mulu64tou64sthen1
    
      dg_mulu64tou64sbegin1:
        mov rax, [rsi]    ; movq (%rsi), %rax    
        add rsi, 8        ; addq $8, %rsi
        mul r10           ; mulq %r10      // R10 * RAX -> RDX:RAX
        add rdx, r9       ; addq %r9, %rdx // to add in carry from previous loop
                          ; // since it's impossible for RDX to be -1 
                          ; //  there won't be a carry from this
        xor r9, r9        ; xorq %r9, %r9  // clear the r9 to hold the carry...
     
        add [rdi], rax    ; addq %rax, (%rdi)

        adc 8[rdi], rdx   ; adcq %rdx, 8(%rdi)  
        rcl r9, 1            ; rclq %r9 // to save carry for next time through loop
        add rdi, 8        ; addq $8, %rdi
      ; loop dg_mulu64tou64sbegin1
        dec rcx
      jnz dg_mulu64tou64sbegin1

    dg_mulu64tou64sthen1:

    mov [r8], r9          ; movq %r9, (%r8)
    
    ; leaq _dg_success(%rip), %rax
    popfq
    pop rsi
    pop rdi
    ret

dg_mulu64tou64ssub ENDP


;    const char* dg_divu64sbyu64 (
;        UINT64* pdest,            // rdi // rcx // quotient and dividend
;        UINT64* premainder,       // rsi // rdx // premainder
;        UINT64  u,                // rdx // r8  // divisor
;        UINT64  destlengthinu64s) // rcx // r9  // 

dg_divu64sbyu64sub PROC EXPORT FRAME

    pushfq          ; /* -0x10  save direction flag, required under win32, just in case for others */
                    ; /* for alignment */
    .allocstack 8   ; /* mac os requires direction flag set to forward */
    .endprolog
    
    xchg r9, rcx    ; destlengthinu64s->rcx
                    ; pdest->r9
    xchg r8, rdx    ; premainder->r8
                    ; divisor->rdx
    
    ; /* checking for divide by 0 case */
    or rdx, rdx     ; orq %rdx, %rdx
    jnz dg_divu64sbyu64then2
    
      xor rdx, rdx     ; xorq %rdx, %rdx   // I think r8 is already 0
      dec rdx          ; decq %rdx /* setting remainder to max UINT64 for div by 0 case */
    
      jmp dg_divu64sbyu64then1 
    
    dg_divu64sbyu64then2:
    
    mov r10, rdx       ; movq %rdx, %r10   /* r10 now has u */
    
    ; /* if rcx is 0 then do nothing */
    or rcx, rcx
    jz dg_divu64sbyu64then1
    
      mov rax, rcx     ; movq %rcx, %rax
      shl rax, 3       ; shlq $3, %rax
      add r9, rax      ; addq %rax, %rdi /* move dest pointer to the end */
    
      xor rdx, rdx     ; xorq %rdx, %rdx /* clear rdx for first divide */
    
      dg_divu64sbyu64begin1:

        sub r9, 8        ; subq $8, %rdi    
        mov rax, [r9]    ; movq (%rdi), %rax    
        div r10          ; divq %r10      // RDX:RAX / R10 -> RAX rem RDX
        mov [r9], rax    ; movq %rax, (%rdi)
      
      ; loop dg_divu64sbyu64begin1
      dec rcx
    jnz dg_divu64sbyu64begin1

    dg_divu64sbyu64then1:

    mov [r8], rdx        ; movq %rdx, (%rsi)  /* save the remainder */
    
    ; leaq _dg_success(%rip), %rax
    popfq
    ret   

dg_divu64sbyu64sub ENDP

dg_n8ton64 PROC EXPORT

    mov al, cl
    cbw
    cwde
    cdqe
    ret

dg_n8ton64 ENDP

dg_n16ton64 PROC EXPORT

    mov ax, cx
    cwde
    cdqe
    ret

dg_n16ton64 ENDP

dg_n32ton64 PROC EXPORT

    mov eax, ecx
    cdqe
    ret

dg_n32ton64 ENDP

dg_setbit PROC EXPORT

    mov rax, rcx
    bts rax, rdx
    ret

dg_setbit ENDP

dg_clrbit PROC EXPORT

    mov rax, rcx
    btr rax, rdx
    ret

dg_clrbit ENDP

dg_notbit PROC EXPORT

    mov rax, rcx
    btc rax, rdx
    ret

dg_notbit ENDP

dg_twototheu PROC EXPORT

    xor rax, rax
    inc rax
    shl rax, cl
    ret

dg_twototheu ENDP

; rcx = u
; rdx = which set bit to find from lo to hi (1 = first set  bit)
dg_scanforuthsetbit PROC EXPORT
    mov rax, rcx
    mov rcx, 40h

    or rdx, rdx      ; /* testing for 0 */
    jnz dg_scanforbitthen1
      mov rax, 40h   ; not found
      ret
    dg_scanforbitthen1:

    dg_scanforbitbegin:
      shr rax, 1
      jnc dg_scanforbitthen2
        dec rdx
        jz dg_scanforbitthen3        
      dg_scanforbitthen2:
      dec rcx
    jnz dg_scanforbitbegin

    dg_scanforbitthen3:
    mov rax, 40h
    sub rax, rcx
    ret
     
dg_scanforuthsetbit ENDP


dg_getulowestsetbits PROC EXPORT
    mov rax, rcx
    mov r8, rax
    mov rcx, 40h

    or rdx, rdx      ; /* testing for 0 */
    jnz dg_getulowestsetbitsthen1
      mov rax, rdx   ; /* if getting no bits, return 0 */
      ret
    dg_getulowestsetbitsthen1:

    dg_getulowestsetbitsbegin:
      shr rax, 1
      jnc dg_getulowestsetbitsthen2
        dec rdx
        jz dg_getulowestsetbitsthen3        
      dg_getulowestsetbitsthen2:
      dec rcx
    jnz dg_getulowestsetbitsbegin

    ; if you got here, there were not enough set bits to fill the amount requested
    ; want an all bits set mask... sooo gonna inc rcx to get it
    inc rcx

    dg_getulowestsetbitsthen3:
    mov rax, 40h
    sub rax, rcx
    inc rax
    mov rcx, rax 
    xor rax, rax
    inc rax
    cmp rcx, 40h
    jc dg_getulowestsetbitsthen4
      dec rax
      dec rax
      and rax, r8
      ret
    dg_getulowestsetbitsthen4:
    shl rax, cl
    dec rax
    and rax, r8
    ret
     
dg_getulowestsetbits ENDP

; rcx = uvalue
; rdx = ucount = number of bits to get
dg_getulowestbits PROC EXPORT
    
    xchg rcx, rdx

    ; might not need to do this if overshifting gives 0
    cmp rcx, 40h
    jc dg_getulowestbitsthen2
      mov rax, rdx
      ret
    dg_getulowestbitsthen2:

    ; does uvalue & ((2^(count+1)) - 1)
    ;   also handles ucount = 0 case correctly
    ;   this ands uvalue with a mask, mask has lowest ucount bits set 
    xor rax, rax
    inc rax
    shl rax, cl
    
    dec rax
    and rax, rdx
    ret
     
dg_getulowestbits ENDP

; rcx = ucount = number of set bits in mask
dg_getulowestbitsmask PROC EXPORT

    ; might not need to do this if overshifting gives 0
    cmp rcx, 40h
    jc dg_getulowestbitsmaskthen2
      xor rax, rax
      dec rax
      ret
    dg_getulowestbitsmaskthen2:

    ; does ((2^(count+1)) - 1)
    ;   also handles ucount = 0 case correctly
    ;   mask has lowest ucount bits set 
    xor rax, rax
    inc rax
    shl rax, cl
    
    dec rax
    ret
     
dg_getulowestbitsmask ENDP

END


