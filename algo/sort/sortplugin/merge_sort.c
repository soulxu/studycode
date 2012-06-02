#include "sort.h"

#include <stdlib.h>

void merge_sort(int *data, int num);

struct sort_plugin plugin = {
	.name = "merge sort",
	.sort_fun = merge_sort
};

void merge(int *data, int *tmp, int left, int mid, int right) {
	int lindex = left;
	int rindex = mid + 1;
	int index = left;

	while ((lindex <= mid) && (rindex <= right)) {
		

		if (data[lindex] < data[rindex]) {
			tmp[index] = data[lindex];
			lindex++;
		}
		else {
			tmp[index] = data[rindex];
			rindex++;
		}

		index++;
	}

	while (lindex <= mid) {
		tmp[index++] = data[lindex++];
	}

	while (rindex <= right) {
		tmp[index++] = data[rindex++];
	}

	int i;

	index--;

	for (i = 0; i < (right - left + 1); i++, index--) {
		data[index] = tmp[index];
	}
}

void m_sort(int *data, int *tmp, int left, int right) {
	int center = 0;
	
	if (left < right) {
		center = (left + right) / 2;
		m_sort(data, tmp, left, center);
		m_sort(data, tmp, center + 1, right);
		merge(data, tmp, left, center, right);
	}
}

void merge_sort(int *data, int num) {
	int *tmp = (int *)malloc(num * sizeof(int));

	if (tmp != NULL) {
		m_sort(data, tmp, 0, num - 1);
		free(tmp);
	}
}
