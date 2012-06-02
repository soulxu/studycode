all: boot.x

boot.x: boot.o
	ld --oformat binary -N -e _start -Ttext 0x7c00 -o boot.x boot.o

boot.o: boot.s
        #as -a boot.s -o boot.o
	as boot.s -o boot.o
