#include "Debug.h"

#include <QString>
#include <stdlib.h>

void dprint(const char *obj, const char *func, const char *format, ...) {
    QString formated;
    va_list args;

    if (format != NULL) {
        va_start(args, format);
        formated.vsprintf(format, args);
        va_end(args);
    }

    qDebug("%s::%s - %s", obj, func, qPrintable(formated));
}

void dwarning(const char *obj, const char *func, const char *format, ...) {
    QString formated;
    va_list args;

    if (format != NULL) {
        va_start(args, format);
        formated.vsprintf(format, args);
        va_end(args);
    }

    qWarning("%s::%s - %s", obj, func, qPrintable(formated));
}
