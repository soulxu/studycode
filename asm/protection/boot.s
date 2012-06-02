#define CR0_PE    1  // protected mode enable bit

#define SEG_NULLASM                                             \
        .word 0, 0;                                             \
        .byte 0, 0, 0, 0


#define SEG_ASM(type,base,lim)                                  \
        .word (((lim) >> 12) & 0xffff), ((base) & 0xffff);      \
        .byte (((base) >> 16) & 0xff), (0x90 | (type)),         \
                (0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)

#define STA_X     0x8       // Executable segment
#define STA_E     0x4       // Expand down (non-executable segments)
#define STA_C     0x4       // Conforming code segment (executable only)
#define STA_W     0x2       // Writeable (non-executable segments)
#define STA_R     0x2       // Readable (executable segments)
#define STA_A     0x1       // Accessed


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

#print_output:
    # print string from output
#    movw $output, %ax
#    movw %ax, %bp
#    movw $12, %cx
#    movw $0x1301, %ax
#    movw $0x000c, %bx
#    movw $0, %dx
#    int $0x10

    cli
    lgdt gdt_r
    movl %cr0, %eax
    orl  $1, %eax
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
#    movl $0xb8000, %eax
#    movb $66, %bl
#    movb %bl, 0(%eax)

    movl $_start, %esp

#    call main_exec
    jmp setup

#    hlt
#dead_loop:
#    jmp dead_loop
   
#output:
#    .ascii "Hello world!"

gdt:
    #.quad 0x0       # first desc
    SEG_NULLASM
    SEG_ASM(STA_X|STA_R, 0x0, 0xffffffff)
    SEG_ASM(STA_W, 0x0, 0xffffffff)

gdt_r:
    .word 0x7ff
    .long gdt

#_end:
#    .=_start + 0x1fe
#    .word 0xaa55
