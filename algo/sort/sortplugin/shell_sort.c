#include "sort.h"

void shell_sort(int *data, int num);

struct sort_plugin plugin = {
	.name = "shell sort",
	.sort_fun = shell_sort
};

void shell_sort(int *data, int num) {
	int i= 0;
	int j = 0;
	int inc = 0;
	int tmp = 0;

	for (inc = num / 2; inc > 0; inc = inc / 2) {
		for (i = inc; i < num; i++) {
			tmp = data[i];

			for (j = i; j >= inc; j -= inc) {
				if (tmp < data[j - inc]) {
					data[j] = data[j - inc];
				}
				else {
					break;
				}
			}
		
			data[j] = tmp;

/*			
			for (j = i - 1; j >= i - inc; j--) {
				if (tmp >= data[j]) {
					break;
				}

				data[j + 1] = data[j];
			}
*/
		}
	}
}
