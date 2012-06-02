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
  movq $0, %rax
  cpuid
  movw $buffer, %di
  movl %ebx, (%di)
  movl %edx, 4(%di)
  movl %ecx, 8(%di)
  pushq $buffer
  pushq $output
  call printf
  addq $16, %rsp
  pushq $0
  call exit
