# 1 "boot.S"
# 1 "<built-in>"
# 1 "<命令行>"
# 1 "boot.S"
# boot.S: Bootloader.

# 1 "asm.h" 1
# 4 "boot.S" 2

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
    int $0x10

# disable interrupt
    cli
    lgdt gdt_reg
    movl %cr0, %eax
    orl 1, %eax
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
    .word 0, 0; .byte 0, 0, 0, 0 #The first desc must be Zero
    .word (((0xffffffff) >> 12) & 0xffff), ((0x0) & 0xffff); .byte (((0x0) >> 16) & 0xff), (0x90 | (0x8|0x2)), (0xC0 | (((0xffffffff) >> 28) & 0xf)), (((0x0) >> 24) & 0xff) # Code Seg Desc
    .word (((0xffffffff) >> 12) & 0xffff), ((0x0) & 0xffff); .byte (((0x0) >> 16) & 0xff), (0x90 | (0x2)), (0xC0 | (((0xffffffff) >> 28) & 0xf)), (((0x0) >> 24) & 0xff) # Data Seg Desc

# GDT register, It will be loaded to GDT register
gdt_reg:
    .word 0x7ff
    .long gdt
