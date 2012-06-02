#include "sort.h"

void select_sort(int *data, int num);

struct sort_plugin plugin = {
	.name = "select sort",
	.sort_fun = select_sort
};

void swap(int *left, int *right) {
	int tmp = *left;
	*left = *right;
	*right = tmp;
}

void select_sort(int *data, int num) {
	int i = 0;
	int j = 0;
	int min = -1;

	for (i = 0; i < num; i++) {
		min = i;

		// 选出最小的值
		for (j = i + 1; j < num; j++) {
			if (data[min] > data[j]) {
				min = j;
			}
		} 

		//将最小值放入前面
		swap(data + min, data + i);		
	}
}
