    .text 
.globl _start
    .code16
_start:
    # set stack base address
    movw $0x6000, %ax
    movw %ax, %ss

    # set screen mode to 80x25, this using BIOS int.
set_screen_mode:
    #80x25
    #movw $0x0003, %ax
    #int  $0x10
    #1024x768x256
    #movw $0x4f02, %ax
    #movw $0x0107, %bx
    #int $0x10

    # clear screen by scroll the screen
clear_screen:
    movb $0x06, %ah
    movb $0, %al
    movw $0, %bx
    int  $0x10
    
    jmp main_loop

    # print one number to hex
    # args: int number.
print_one_hex:
    push %bp
    movw %sp, %bp

    movw 4(%bp), %bx
    cmp $10, %bl
    jge greater_f
    addb $48, %bl
    jmp show_char 
greater_f:
    subb $10, %bl
    addb $97, %bl
show_char:
    movb %bl, %al
    movw $0x0, %bx
    movb $0x0e, %ah
    int $0x10
    #movw $0x0, %bx
    #movb $0x09, %ah
    #int $0x10

    movw %bp, %sp
    pop %bp
    ret

print_hex_16:
    push %bp
    movw %sp, %bp

    movw 4(%bp), %bx
    movw $4, %cx

    # loop display each number
loop_n:
    rolw $4, %bx
    movw %bx, %ax
    andw $0x000f, %ax
    push %bx
    push %cx
    push %ax
    call print_one_hex    
    pop %ax
    pop %cx
    pop %bx
    loop loop_n

    # prepare return
    movw %bp, %sp
    pop %bp
    ret
   
main_loop:
    push $0x0000
    call print_hex_16

output:
    .ascii "Hello world!"
    .=_start + 0x1fe
    .word 0xaa55
