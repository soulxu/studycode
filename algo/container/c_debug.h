#ifndef _C_DEBUG_H_
#define _C_DEBUG_H_

#include <stdio.h>
#include <stdarg.h>

void dprint(const char *func, const char *format, ...); 

#define DPRINT(...) \
	dprint(__func__, __VA_ARGS__)

#endif

