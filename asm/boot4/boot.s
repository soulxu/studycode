    .text 
.globl _start
    .code16
_start:
set_screen_mode:
    #80x25
    movw $0x0003, %ax
    int  $0x10
    #1024x768x256
    #movw $0x4f02, %ax
    #movw $0x0107, %bx
    #int $0x10
clear_screen:
    movb $0x06, %ah
    movb $0, %al
    movw $0, %bx
    int  $0x10
    
    #jmp write_vga_ram

print_output:
    # print string from output
    movw $output, %ax
    movw %ax, %bp
    movw $12, %cx
    movw $0x1301, %ax
    movw $0x000c, %bx
    movw $0, %dx
    int $0x10
    #ret
    # just print one char
    #movb $0x0e, %ah
    #movb $96, %al
    #movw $0, %bx
    #int $0x10
    #ret

write_vga_ram:
    movw $0xb000, %ax
    movw %ax, %ds
    movw $0xffff, %cx
loop1:
    movb $0x4, -0xffff(%ecx)
    #call print_output
    #subw $1, %cx
    loop loop1
    #jmp loop1

output:
    .ascii "Hello world!"
    .=_start + 0x1fe
    .word 0xaa55
