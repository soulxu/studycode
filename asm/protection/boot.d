# 1 "boot.s"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "boot.s"
# 21 "boot.s"
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

#print_output:
    # print string from output
# movw $output, %ax
# movw %ax, %bp
# movw $12, %cx
# movw $0x1301, %ax
# movw $0x000c, %bx
# movw $0, %dx
# int $0x10

    cli
    lgdt gdt_r
    movl %cr0, %eax
    orl $1, %eax
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

#write_char:
# movl $0xb8000, %eax
# movb $66, %bl
# movb %bl, 0(%eax)

    movl $_start, %esp

# call main_exec
    jmp setup

# hlt
#dead_loop:
# jmp dead_loop

#output:
# .ascii "Hello world!"

gdt:
    #.quad 0x0 # first desc
    .word 0, 0; .byte 0, 0, 0, 0
    .word (((0xffffffff) >> 12) & 0xffff), ((0x0) & 0xffff); .byte (((0x0) >> 16) & 0xff), (0x90 | (0x8|0x2)), (0xC0 | (((0xffffffff) >> 28) & 0xf)), (((0x0) >> 24) & 0xff)
    .word (((0xffffffff) >> 12) & 0xffff), ((0x0) & 0xffff); .byte (((0x0) >> 16) & 0xff), (0x90 | (0x2)), (0xC0 | (((0xffffffff) >> 28) & 0xf)), (((0x0) >> 24) & 0xff)

gdt_r:
    .word 0x7ff
    .long gdt

#_end:
# .=_start + 0x1fe
# .word 0xaa55
