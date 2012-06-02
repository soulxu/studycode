#ifndef _KTIME_H
#define _KTIME_H

#include <stdio.h>
#include <time.h>

static time_t _start;
static time_t _end;

#define START_TIME _start = clock(); \
		printf("start at: %ld, %ld\n", _start, _start / CLOCKS_PER_SEC)

#define END_TIME _end = clock(); \
		printf("end at: %ld\n", _end); \
		printf("using time: %ld, %ld\n", _end - _start, (_end - _start) / CLOCKS_PER_SEC)

#define START_TIME_ _start=clock()

#define END_TIME_ _end = clock(); \
		printf("%ld %ld\n", _end - _start, (_end - _start) / CLOCKS_PER_SEC)
#endif
