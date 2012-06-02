.section .data
output:
  .asciz "The cpu id is ''\n"
i:
.section .bss
  .lcomm buffer, 12
.section .text

.globl _start
_start:
  nop
#  movl $0, %eax
#  cpuid
#  movq $buffer, %rdi
#  movl %ebx, (%edi)
#  movl %edx, 4(%edi)
#  movl %ecx, 8(%edi)
#  push $buffer
  push $0
  push $output
  call printf
  addq $64, %rsp
  push $0
  call exit
