#include <stdio.h>

#define SIZE 10

void method1(int *data) {
	int i = 0;
	int sum = 0;
	int average = 0;

	for (i = 0; i < SIZE; i++) {
		sum += data[i];		
	}

	average = sum / SIZE;

	printf("sum: %d average: %d\n", sum, average);


	for (i = 0; i < SIZE; i++) {
		if (data[i] > average) {
			printf("%d\n", data[i]);
		}
	}
}

int main(int argc, char **argv) {
	int i = 0;
	int data[SIZE] = {0};
	int ret[SIZE] = {0};

	for (i = 0; i < SIZE; i++) {
		scanf("%d", &(data[i]));
	}

	printf("result:\n");
	method1(data);
	return 0;
}
