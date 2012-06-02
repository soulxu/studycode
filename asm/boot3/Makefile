all: boot.x boot.exec

boot.exec:
	ld -m elf_i386 -N -e _start -Ttext 0x7c00 -o boot.exec boot.o
boot.x: boot.o
	ld -m elf_i386 --oformat binary -N -e _start -Ttext 0x7c00 -o boot.x boot.o

boot.o: boot.s
        #as -a boot.s -o boot.o
	as -32 boot.s -o boot.o -gstags
