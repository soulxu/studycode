#include <c_debug.h>

void dprint(const char *func, const char *format, ...) {
        char buf[4096] = {0};
        va_list args;
        va_start(args, format);
        sprintf(buf, "%s:%s\n", func, format);
        printf(buf, args);
        va_end(args);
}
