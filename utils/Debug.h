#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>
#include <string.h>

#ifndef NO_DEBUG
#  define D_ERROR(str) fprintf(stderr, "%s:%d:%s -" str ": %s\n", __FILE__, __LINE__, __func__, strerror(errno))
#  define D_PRINT(str) printf("%s:%d:%s - " str "\n", __FILE__, __LINE__, __func__)
#  define D_PVAR_STR(mem) printf("%s:%d:%s - " #mem " = %s\n", __FILE__, __LINE__, __func__, mem)
#  define D_PVAR_INT(mem) printf("%s:%d:%s - " #mem " = %d\n", __FILE__, __LINE__, __func__, mem)
#  define D_PVAR_EMU(mem,emu) ( ( ( mem ) & emu ) ? printf("%s:%d:%s - " #mem " = " #emu "\n", __FILE__, __LINE__, __func__) : printf(""))
#else
#  define D_ERROR(str)
#  define D_PRINT(str)
#  define D_PVAR_STR(obj,mem)
#  define D_PVAR_INT(obj,mem)
#  define D_PVAR_INT(obj,mem,emu)
#endif

#endif
