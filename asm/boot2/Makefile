all: boot.x boot.exec

boot.exec: boot.x
	ld -m elf_i386 -N -e _start -Ttext 0x7c00 -T ./boot.lds -o boot.exec boot.o p.o

boot.x: boot.o p.o
	#ld -m elf_i386 --oformat binary -N -e _start -Ttext 0x7c00 -o boot.x boot.o p.o d.o
	ld -m elf_i386 --oformat binary -N -e _start -Ttext 0x7c00 -T ./boot.lds -o boot.x boot.o p.o

# C function .
p.o: p.s
	as -32 p.s -o p.o -gstags

# i didn't need this as end flags. the end flags add at link script
#d.o: d.s
#	as -32 d.s -o d.o -gstags

boot.o: boot.s
        #as -a boot.s -o boot.o
	as -32 boot.s -o boot.o -gstags


.PHONY: clean
clean:
	rm boot.x boot.exec p.o boot.o
