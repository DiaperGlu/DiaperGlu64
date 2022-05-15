
.text

.globl _dg_firstfunction
_dg_firstfunction:

   movq $0x1122334455667788, %rax
   ret

.globl _dg_secondfunction
_dg_secondfunction:

   movq $0x1213141516171819, %rax
   ret
   




