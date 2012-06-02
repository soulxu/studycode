#include "ide.h"
#include "x86.h"

void setup(void) {
    int i;
    char *p = (char *)MAIN_SETUP_ENTRY;

    for (i = 0; i < 8; i++) {
        read_sect(p, 1+i);
        p += 512;
    }

    void (*main_setup)(void) = (void (*)())MAIN_SETUP_ENTRY;
    main_setup();
}
