#include "sort.h"

#include <stdio.h>

void insert_binary_sort(int *data, int num);

struct sort_plugin plugin = {
	.name = "insert binary sort",
	.sort_fun = insert_binary_sort
};

void insert_binary_sort(int *data, int num) {
	int i = 0;
	int j = 0;
	int left = 0;
	int right = 0;
	int mid = 0;

	for (i = 1; i < num; i++) {
		int tmp = data[i];
		left = 0;
		right = i - 1;
//		printf("loop: %d\n", i);
		while (left < right) {
//			printf("l: %d, r: %d, m: %d\n", left, right, (right + left) / 2);
			mid = (right + left) / 2;

			if (tmp  < data[mid]) {
				right = mid;
			}
			else if (tmp > data[mid]) {
				left = mid + 1;
			}
			else {
				left = right = mid;
			}
		}

		for (j = i; j > right; j--) {
			data[j] = data[j - 1];
		}

		data[right] = tmp;
/*
		int index = binary_search(data, data[i], 0, i - 1);

		for (j = i; j > index; j--) {
			data[j] = data[j - 1];	
		}

		data[index] = tmp;
*/
	}
}

