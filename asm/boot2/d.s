    .code16
    .data
#    .globl output
#output:
#    .ascii "Hello world!"
_end:
    .=_start + 0x1fe
    .word 0xaa55

