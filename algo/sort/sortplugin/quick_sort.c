#include "sort.h"

void quick_sort(int *data, int num);

struct sort_plugin plugin = {
	.name = "quick sort",
	.sort_fun = quick_sort
};

void swap(int *left, int *right) {
	int tmp = *left;
	*left = *right;
	*right = tmp;
}

int partition(int *data, int left, int right) {
	int center = (left + right) / 2;

	if (data[left] > data[center]) {
		swap(data + left, data + center);
	}

	if (data[center] > data[right]) {
		swap(data + center, data + right);
	}

	if (data[left] > data[right]) {
		swap(data + left, data + right);
	}

	swap(data + center, data + right);

	return data[right];
}

void q_sort(int *data, int left, int right) {
	int i = left;
	int j = right - 1;	

	if (left >= right) {
		return;
	}

	int midval = partition(data, left, right);

	while (1) {
		while (data[i] < midval) {
			i++;
		}

		while (data[j] > midval) {
			j--;
		}

		if (data[i] == data[j]) {
			i++;
			j--;
			continue;
		}

		if (i < j) {
			swap(data + i, data + j);
		}
		else {
			break;
		}
	}

	swap(data + i, data + right);

	q_sort(data, left, i - 1);
	q_sort(data, i + 1, right);
}

void quick_sort(int *data, int num) {
	q_sort(data, 0, num - 1);
}
