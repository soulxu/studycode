#include "sort.h"

void pop_sort(int *data, int num);

struct sort_plugin plugin = {
	.name = "pop sort",
	.sort_fun = pop_sort
};

void pop_sort(int *data, int num) {
	int i = 0;
	int j = 0;
	int tmp = 0;

	for (i = 0; i < num - 1; i++) {
		for (j = 0; j < num - 1 - i; j++) {
			if (data[j] > data[j + 1]) {
				tmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = tmp;
			}
		}
	}
}
