.section .data
  output:
    .asciz "The value is %d\n"
  value:
    .int 1
.section .text
.global _start
_start:
	nop
loop:
	movl value, %eax
	push %eax
	push $output
	call printf
	addl $8, %esp
	inc %eax
	movl %eax, value
	cmpl value, $10
	jne loop
	movl $0, %ebx
	movl $1, %eax
	int $0x80
