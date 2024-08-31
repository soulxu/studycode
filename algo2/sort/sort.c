#include <stdio.h>
#include <stdlib.h>

#define DATA_LENGTH 8

void select_sort(int* data) {
    for (int i = 0; i < DATA_LENGTH; i++) {
        int min_index = i;
        for (int j = i + 1; j <  DATA_LENGTH; j++) {
            if (data[j] < data[min_index]) {
                min_index = j;
            }
        }
        int tmp = data[i];
        data[i] = data[min_index];
        data[min_index] = tmp;
    }
}


void insertion_sort(int* data) {
    for (int i = 1; i < DATA_LENGTH; i++) {
        int base = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > base) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = base;
    }
}

int quick_partition(int* data, int left, int right) {
    int i = left;
    int j = right;
    while (i < j) {
        while (i < j && data[j] >= data[left]) {
            j--;
        }
        while (i < j && data[i] <= data[left]) {
            i++;
        }
        int tmp = data[j];
        data[j] = data[i];
        data[i] = tmp;
    }
    int tmp = data[i];
    data[i] = data[left];
    data[left] = tmp;
    return i;
}

void quick_sort(int* data, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = quick_partition(data, left, right);
    quick_sort(data, left, mid - 1);
    quick_sort(data, mid + 1, right);
}

void print_data(int* data) {
    for (int i = 0; i < DATA_LENGTH; i++) {
        printf("%d ", data[i]);
    }
    printf("\n");
}

int main(int, char**) {
    int data[DATA_LENGTH] = {0};

    printf("selection sort\n");
    for (int i = 0; i < DATA_LENGTH; i++) {
        data[i] = random() % 100;
    }
    print_data(data);
    select_sort(data);
    print_data(data);

    printf("insertion sort\n");
    for (int i = 0; i < DATA_LENGTH; i++) {
        data[i] = random() % 100;
    }
    print_data(data);
    insertion_sort(data);
    print_data(data);

    printf("quick sort\n");
    for (int i = 0; i < DATA_LENGTH; i++) {
        data[i] = random() % 100;
    }
    print_data(data);
    quick_sort(data, 0, DATA_LENGTH - 1);
    print_data(data);
}