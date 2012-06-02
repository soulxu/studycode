    .text 
    .code16
.globl _start
_start:
print_output:
    pushl $1
    pushl $2
#    call test
    call add
   
    addl $97, %eax
    movl $12, %ecx
    addl %eax, %ebx
    movb %bl, 11(%ecx)

    movl $output, %eax
    movw %ax, %bp
    movl $12, %ecx
    movw $0x1301, %ax
    movw $0x000c, %bx
    movb $0, %dl
    int $0x10

#test:
#    nop
#    ret
output:
    .ascii "Hello world!"

