

/* Requirments:
   // calling convention
   //  int: x0, x1 = f(x0, x1, x2, x3, x4, x5, x6, x7, sp[0], sp[1], sp[2], ... )
   //  float: d0, d1 = f(d0, d1, d2, d3, d4, d5, d6, d7, sp[0], sp[1], sp[2], ... ) ( ? docs not clear )

   // syscall calling convention
   //  rax = sys[rax](rdi, rsi, rdx, rcx, r8, r9, rsp[1], rsp[2], rsp[3], ... )
   
   //  registers sp, x19 - x28 must be preserved
   //  ip0 (x16), ip1 (x17) are reserved for linker use during the main body of a procedure ( used to do long branches among other things )
   //  pr (x18) platform reserve register - Apple says do not use this register
   //  fp (x29) is used as the frame pointer. Apple says this must always address a valid frame record
   //  lr (x30) is used to hold the procedure return address 
   //  (x31) no idea except google AI says this is either sp or xzr depending on instruction
 
   // Also, there is a 16 byte alignment requirement for certain subroutines

   // other registers
   //  xzr, wzr ( zero registers ) 
   //  pc ( program counter - use adr instruction to copy pc to another register )
 
   Notes:
    Labels starting with L (L_?) are removed. Perhaps this is why the assembler needs exported symbols to start with _ ?
    But why have the .globl thing if you have the L_ convention?
*/


.text


.globl _dg_testasm1
_dg_testasm1:

    movz x0, #0x1234
    ret

.globl _dg_testasm2
_dg_testasm2:

    movz x0, #0x1122
    nop
    nop
    nop
    ret




    

