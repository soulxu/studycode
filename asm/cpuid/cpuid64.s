.section .data
output:
  .ascii "The cpu id is 'xxxxxxxxxxxx'\n"
.section .bss

.section .text

.globl _start
_start:
  nop
  movl $0, %eax
  cpuid
  movl $output, %edi
  movl %ebx, 15(%edi)
  movl %edx, 19(%edi)
  movl %ecx, 23(%edi)
  movq $4, %rax
  movq $1, %rbx
  movq $output, %rcx
  movq $29, %rdx
  int $0x80
  movq $1, %rax
  movq $0, %rbx
  int $0x80
