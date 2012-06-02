all: boot.x boot.exec main.x main.exec diskimg

boot.exec: boot.x
	#ld -m elf_i386 -N -e _start -Ttext 0x7c00 -o boot.exec boot.o
	ld -m elf_i386 -N -e _start -Ttext 0x7c00 -T ./boot.lds -o boot.exec boot.o setup.o

boot.x: boot.o setup.o
	#ld -m elf_i386 --oformat binary -N -e _start -Ttext 0x7c00 -o boot.x boot.o
	ld -m elf_i386 --oformat binary -N -e _start -Ttext 0x7c00 -T ./boot.lds -o boot.x boot.o setup.o

setup.o: setup.c
	gcc -m32 -g -c setup.c -o setup.o

boot.o: boot.d
        #as -a boot.s -o boot.o
	as -32 boot.d -o boot.o -gstags

boot.d: boot.s
	cpp boot.s -o boot.d

util.o: util.c
	gcc -m32 -g -c util.c -o util.o

main.o: main.c
	gcc -m32 -g -c main.c -o main.o

main.x: main.o util.o
	ld -m elf_i386 --oformat binary -N -e main_exec -Ttext 0x10000 -T ./main.lds -o main.x main.o util.o

main.exec: main.o
	ld -m elf_i386 -N -e main_exec -Ttext 0x10000 -T ./main.lds -o main.exec main.o util.o

diskimg: main.x boot.x
	cat boot.x > diskimg
	cat main.x >> diskimg
	cat boot.x >> diskimg
	cat boot.x >> diskimg

.PHONY:clean

clean:
	rm boot.d boot.o boot.x boot.exec setup.o main.o main.x main.exec util.o diskimg
