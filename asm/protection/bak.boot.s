#define CR0_PE    1  // protected mode enable bit

#define SEG_ASM(type,base,lim)                                  \
        .word (((lim) >> 12) & 0xffff), ((base) & 0xffff);      \
        .byte (((base) >> 16) & 0xff), (0x90 | (type)),         \
                (0xC0 | (((lim) >> 28) & 0xf)), (((base) >> 24) & 0xff)



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

print_output:
    # print string from output
    movw $output, %ax
    movw %ax, %bp
    movw $12, %cx
    movw $0x1301, %ax
    movw $0x000c, %bx
    movw $0, %dx
    int $0x10

    cli
    lgdt gdt
    movl %cr0, %eax
    orl  $1, %eax
    movl %eax, %cr0

    ljmp $0x8, $_start32

.code32
_start32:
    movw $0x10, %ax
    movw %ax, %ds    
 
write_char:
    movl $1, %eax
    movb $96, %bl
    movb %bl, 0(%eax)

dead_loop:
    jmp dead_loop
   
output:
    .ascii "Hello world!"

gdt:
    .quad 0x0       # first desc

    SEG_ASM(STA_X|STA_R, 0x0, 0xffffffff)
    SEG_ASM(STA_W, 0x0, 0xffffffff)
#    .short 0xffff   # second desc(code seg). seg limit
#    .short 0x0      # base addr
#    .byte 0xff      # base addr
#    .byte 0xA9      # type = (exec | read = 10 = 0x1011) S = 1 DPL=0 P=1
#    .byte 0xfB      # seg limit=0xff avl=1 (0) b=1 g=1
#    .byte 0xff      # base addr

#    .short 0xffff   # third desc(data seg). seg limit
#    .short 0x0      # base addr
#    .byte 0xff      # base addr
#    .byte 0xA9      # type = (exec | read = 10 = 0x1011) S = 1 DPL=0 P=1
#    .byte 0xfB      # seg limit=0xff avl=1 (0) b=1 g=1
#    .byte 0xff      # base addr

_end:
    .=_start + 0x1fe
    .word 0xaa55
