#include "sort.h"

#include <memory.h>

void bucket_sort(int *data, int num);

struct sort_plugin plugin = {
	.name = "bucket sort",
	.sort_fun = bucket_sort
};

void bucket_sort(int *data, int num) {
	char *tmp = (char *)malloc(num);
	int i = 0;	
	int j = 0;

	memset(tmp, 0, num);

	for (i = 0; i < num; i++) {
		tmp[data[i]] = 1;
	}

	for (i = 0, j = 0; i < num; i++) {
		if (tmp[i] == 1) {
			data[j] = i;
			j++;
		}
	}

	free(tmp);
}
