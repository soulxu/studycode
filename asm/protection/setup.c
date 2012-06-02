#include "x86.h"

void wait_disk(void) {
    while((inb(0x1f7) & 0xc0) != 0x40) { }
}

void read_sect(void *dst, unsigned int offset) {
    wait_disk();

    outb(0x1f2, 1);;
    outb(0x1f3, offset);
    outb(0x1f4, offset >> 8);
    outb(0x1f5, offset >> 16);
    outb(0x1f6, (offset >> 24) | 0xe0);
    outb(0x1f7, 0x20);

    wait_disk();
    insl(0x1f0, dst, 512/4);    
}

void setup(void) {
   void (*main)(void);
   main = 0x10000;
   read_sect(main, 1);
   main();
}
