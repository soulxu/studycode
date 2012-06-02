    .text 
.globl _start
    .code16
_start:
    #movw $0, %ax
    #movw %ax, %cs
    #movw %ax, %ds
    movw $0x7000, %ax
    movw %ax, %ss

set_screen_mode:
    #80x25
#    movw $0x0003, %ax
#    int  $0x10
    #1024x768x256
    #movw $0x4f02, %ax
    #movw $0x0107, %bx
    #int $0x10
clear_screen:
    movb $0x06, %ah
    movb $0, %al
    movw $0, %bx
    int  $0x10
    
    jmp main_loop

#print_number:
#    push %ebp
#    movl %esp, %ebp
#    movw $0, %ax
#    movw 4(%ebp), %dx
#    addw $60, %dx
#    movb %dl, %al
#    movw $0, %bx
#    int $0x10
#    leave
#    ret

print:
    push %ebp
    movl %esp, %ebp
    movw 6(%ebp), %ax
    movw 8(%ebp), %dx
    movw %ax, %bp
    movw $12, %cx
    movw $0x1301, %ax
    movw $0x000d, %bx
    int $0x10
    pop %ebp
    ret

main_loop:
    push $0x0105
    push $output
    call print
    pop %ax
    pop %ax
    push $0x0200
    push $output1
    call print
    pop %ax
    pop %ax
	

output:
    .ascii "Hello world!"
output1:
    .ascii "Hello world2!"
    .=_start + 0x1fe
    .word 0xaa55
