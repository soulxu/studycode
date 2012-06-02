.data
output:
  .asciz "aa"
.text
.globl _start
_start:
  movl $1, %eax
  push $output
  pushw %ax
  popl %eax
 

