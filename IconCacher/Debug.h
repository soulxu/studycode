#ifndef DEBUG_H
#define DEBUG_H

#include <QtGlobal>
#include <stdlib.h>
#include <QHash>

void dprint(const char *obj, const char *func, const char *format, ...);
void dwarning(const char *obj, const char *func, const char *format, ...);
void dtimer(const char *obj, const char *func, const char *format, ...);

#ifdef CODEBUG
#   define DPRINT(...) dprint(this->metaObject()->className(),  __func__,  __VA_ARGS__)
#   define CDPRINT(...)
#   define DWARNING(...) dwarning(this->metaObject()->className(),  __func__,  __VA_ARGS__)
#   define CDWARNING(...)
#else
#   define DPRINT(...)
#   define CDPRINT(...)
#   define DWARNING(...)
#   define CDWARNING(...)
#endif // CODEBUG


#ifdef TIMER
#   define DTIMER(...) dtimer(this->metaObject()->className(),  __func__,  __VA_ARGS__)
#   define DFTIMER(...) dtimer("",  __func__,  __VA_ARGS__)
#else
#   define DTIMER(...)
#endif //TIMER

#endif // DEBUG_H
