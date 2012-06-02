#ifndef _X86_H_
#define _X86_H_

#define MAIN_SETUP_ENTRY 0x100000

static inline void outb(unsigned short port, unsigned char data) {
     asm volatile ("out %0,%1" : : "a"(data), "d"(port));
}

static inline unsigned char inb(unsigned short port) {
     unsigned char ret = 0;
     asm volatile ("in %1, %0" : "=a"(ret) : "d"(port));
     return ret; 
}

static inline void insl(unsigned short port, void *addr, int cnt) {
     asm volatile ("cld\n \
                    rep insl" :
                    :
                    "d"(port), "c"(cnt), "D"(addr) );
}

static inline void sti() {
    asm volatile ("sti");
}

static inline void cli() {
    asm volatile ("cli");
}

#endif
