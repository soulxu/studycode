#include "sort.h"

void select_heap_sort(int *data, int num);

struct sort_plugin plugin = {
	.name = "select heap sort",
	.sort_fun = select_heap_sort
};

#define LEFT_CHILD(n) ((n) * 2) + 1
/*
 * data: 数据
 * i: 被调整的元素
 * num: 元素个数
 */
void head_adjust(int *data, int i, int num) {
	int child = LEFT_CHILD(i);
	int tmp = 0;
	for (tmp = data[i]; LEFT_CHILD(i) < num; i = child) {
		child = LEFT_CHILD(i);
		
		//如果右子树大，使用右子树
		if ((child < (num -1)) && (data[child] < data[child + 1])) {
			child++;
		}

                //与子树交换，否则退出
		if (tmp < data[child]) {
			data[i] = data[child];
		}
		else {
			break;
		}
	}

	data[i] = tmp;
}

void select_heap_sort(int *data, int num) {
	int i = 0;
	int tmp = 0;

	// 将无序数列变成堆,从最后一个非叶子节点开始调整。也就是num/2的位置
	for (i = (num / 2); i >= 0; i--) {
		head_adjust(data, i, num);
	}	

	//print_sort_list(data, num);

 	//依次取堆顶元素放入序列最后
	for (i = num - 1; i > 0; i--) {
		tmp = data[i];
		data[i] = data[0];
		data[0] = tmp;

		head_adjust(data, 0, i);		
	}
}
