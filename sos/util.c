#include "util.h"

struct _Char {
    char ch;
    unsigned char attr;
};

typedef struct _Char Char;

static int x;
static int y;

void print_init() {
    x = 0;
    y = 0;
}

void print_char(char ch, unsigned char attr) {
    Char chs = {ch, attr};
    Char *p = (Char *)0xb8000;

    p += (y * 80 + x);
    *p = chs;

    if (((x + 1) % 80) == 0) {
        y++;
        x = 0;
    }
    else {
        x++;
    }
}

void print_str(char *str, unsigned char attr) {
    while (*str != '\0') {
        print_char(*str, attr);
        str++;
    }
}
