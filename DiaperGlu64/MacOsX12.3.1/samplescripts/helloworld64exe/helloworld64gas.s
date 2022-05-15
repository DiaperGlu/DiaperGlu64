
.text

_omyhelloworldmessage:
.asciz "\nHello World!\n\n"

.globl _myhelloworldstart
_myhelloworldstart:

   /* align the stack regardless of where it is when this function is called */
   andq $0xfffffffffffffff0, %rsp
   
   movq $1,  %rdi                           /* stdout handle */
   leaq _omyhelloworldmessage(%rip),  %rsi  /* pmessageaddress */
   movq $15, %rdx                           /* messagelength */                       
   call _write
   
   call _exit





