# boot.S: Bootloader.

#include "asm.h"

.globl _start
    .code16
_start:
    xorw %ax, %ax
    movw %ax, %ds
    movw %ax, %es
    movw $0x7000, %sp
clear_screen:
    movb $0x06, %ah
    movb $0, %al
    movw $0, %bx
    int  $0x10

# disable interrupt
    cli
    lgdt gdt_reg
    movl %cr0, %eax
    orl  CR0_PE, %eax
# enable protection
    movl %eax, %cr0

    ljmp $0x8, $_start32

.code32
_start32:
    movw $0x10, %ax
    movw %ax, %ds    
    movw %ax, %es
    movw %ax, %ss
    movw $0, %ax
    movw %ax, %gs
    movw %ax, %fs

    movl $_start, %esp

# Call setup the C program.
    jmp setup

# temp GDT
gdt:
    SEG_NULLASM    #The first desc must be Zero
    SEG_ASM(STA_X|STA_R, 0x0, 0xffffffff)    # Code Seg Desc
    SEG_ASM(STA_W, 0x0, 0xffffffff)               # Data Seg Desc

# GDT register, It will be loaded to GDT register
gdt_reg:
    .word 0x7ff
    .long gdt

