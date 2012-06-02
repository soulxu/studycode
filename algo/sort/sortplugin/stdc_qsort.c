#include "sort.h"

#include <stdlib.h>

void stdc_qsort(int *data, int num);

struct sort_plugin plugin = {
	.name = "stdc qsort",
	.sort_fun = stdc_qsort
};

int comp(const void *left, const void *right) {
	return *(int *)left - *(int *)right;
}

void stdc_qsort(int *data, int num) {
	qsort(data, num, sizeof(int), comp);
}
