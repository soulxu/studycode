#! cmov test
#  .data
#output:
#  .asciz "The largest value is %d\n"
#value:
#  .int 10, 200, 158, 42, 39, 95, 1, 9, 80, 55

  .text
.globl _start
_start:
  movl $0, %ebx
  movl $0, %eax
loop:
  cmp %ebx, value(, %eax, 4)
  cmova value(, %eax, 4), %ebx
  inc %eax
  cmp $10, %eax
  jne loop
  push %ebx
  push $output
  call printf
  addl $8, %esp
  push $0
  call exit
  
  .data
output:
  .asciz "The largest value is %d\n"
value:
  .int 10, 200, 158, 42, 39, 95, 1, 9, 80, 55
