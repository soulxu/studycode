#include "sort.h"

void insert_sort(int *data, int num);

struct sort_plugin plugin = {
	.name = "insert sort",
	.sort_fun = insert_sort
};

void insert_sort(int *data, int num) {
	int i = 0;
	int j = 0;

	for (i = 1; i < num; i++) {
		int tmp = data[i];

		for (j = i; j > 0; j--) {
			if (tmp > data[j - 1]) {
				break;
			}
	
			data[j] = data[j - 1];
		}

		data[j] = tmp;
	}
}

