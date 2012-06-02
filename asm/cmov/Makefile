all: cmov

cmov: cmov.o
	ld -dynamic-linker /lib32/ld-2.13.so -m elf_i386 cmov.o -L/lib32 -lc-2.13 -o cmov

cmov.o: cmov.S
	as --32 cmov.S -o cmov.o -gstabs
