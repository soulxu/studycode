all: boot.x boot.exec main_setup.x main_setup.exec main.exec diskimg  

boot.x: boot.o setup.o ide.o
	#ld -m elf_i386 --oformat binary -N -e _start -Ttext 0x7c00 -o boot.x boot.o
	ld -m elf_i386 --oformat binary -N -e _start -Ttext 0x7c00 -T ./boot.lds -o boot.x boot.o setup.o ide.o

boot.o: boot.d
        #as -a boot.s -o boot.o
	as -32 boot.d -o boot.o -gstags

boot.d: boot.S
	cpp boot.S -o boot.d

boot.exec: boot.x
	#ld -m elf_i386 -N -e _start -Ttext 0x7c00 -o boot.exec boot.o
	ld -m elf_i386 -N -e _start -Ttext 0x7c00 -T ./boot.lds -o boot.exec boot.o setup.o ide.o

setup.o: setup.c x86.h ide.h
	gcc -m32 -g -c setup.c -o setup.o

util.o: util.c
	gcc -m32 -g -c util.c -o util.o

ide.o: ide.c
	gcc -m32 -g -c ide.c -o ide.o

main_setup.o: main_setup.c
	gcc -m32 -g -c main_setup.c -o main_setup.o

main_setup.x: main_setup.o util.o ide.o
	ld -m elf_i386 --oformat binary -N -e main_setup -Ttext 0x100000 -T ./main_setup.lds -o main_setup.x main_setup.o util.o ide.o

main_setup.exec: main_setup.o ide.o
	ld -m elf_i386 -N -e main_setup -Ttext 0x100000 -T ./main_setup.lds -o main_setup.exec main_setup.o util.o ide.o

main.exec: main.o
	ld -m elf_i386 -N -e main -Ttext 0x101000 -o main.exec main.o util.o

main.o: main.c
	gcc -m32 -g -c main.c -o main.o

diskimg: boot.x main.exec main_setup.x
	dd if=boot.x bs=1 count=512 of=diskimg
	dd if=main_setup.x bs=1 count=4096 of=diskimg seek=512 
	dd if=main.exec bs=1 of=diskimg seek=4608
	cat main.exec >> diskimg
	cat main.exec >> diskimg
.PHONY:clean

clean:
	rm boot.d boot.o boot.x boot.exec setup.o main_setup.o main_setup.x main_setup.exec util.o diskimg main.o main.exec
