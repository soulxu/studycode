#include "Debug.h"

#include <QString>
#include <stdlib.h>
#include <QTime>
#include <QDateTime>

QTime current = QTime::currentTime();

void dprint(const char *obj, const char *func, const char *format, ...) {
    QString formated;
    va_list args;

    if (format != NULL) {
        va_start(args, format);
        formated.vsprintf(format, args);
        va_end(args);
    }

    qDebug("%u-%d::%s::%s - %s", QDateTime::currentDateTime().toTime_t(), QTime::currentTime().msecsTo(current), obj, func, qPrintable(formated));
}

void dwarning(const char *obj, const char *func, const char *format, ...) {
    QString formated;
    va_list args;

    if (format != NULL) {
        va_start(args, format);
        formated.vsprintf(format, args);
        va_end(args);
    }

    qWarning("%u-%d::%s::%s - %s", QDateTime::currentDateTime().toTime_t(), QTime::currentTime().msecsTo(current), obj, func, qPrintable(formated));
}

void dtimer(const char *obj, const char *func, const char *format, ...) {
    QString formated;
    va_list args;

    if (format != NULL) {
        va_start(args, format);
        formated.vsprintf(format, args);
        va_end(args);
    }

    qDebug("%u-%d::%s::%s - %s", QDateTime::currentDateTime().toTime_t(), QTime::currentTime().msecsTo(current), obj, func, qPrintable(formated));
}
