#pragma once

#include <memory>
#include <vector>

#include <stdio.h>

namespace Algo {

template <class T>
class Heap {
public:
    Heap() {}
    Heap(std::vector<T> d) : data(std::move(d)){
        build();
    }
    void insert(T d) {
        data.emplace_back(d);
        int index = data.size() - 1;
        while (index > 0) {
            //printf("%d, %d\n", data.at(parent(index)), data.at(index));
            if (data.at(parent(index)) < data.at(index)) {
                T tmp = data.at(parent(index));
                data.at(parent(index))  = data.at(index);
                data.at(index) = tmp;
            }
            index = parent(index);
        }
    }

    T peekMax() {
        return data.front();
    }

    void delMax() {
        if (data.size() == 0) {
            return;
        }
        data[0] = data[data.size() - 1];
        data.pop_back();
        int index = 0;
        int max = 0;
        while (true) {
            int l = left(max);
            int r = right(max);
            if (l < data.size() && data[l] > data[max]) {
                max = l;
            }
            if (r < data.size() && data[r] > data[max]) {
                max = r;
            }
            if (index == max) {
                break;
            }
            T tmp = data[max];
            data[max] = data[index];
            data[index] = tmp;
            
            index = max;
        }
    }

    void sink(int size, int max) {
        int i = max;
        while (true) {
            int l = left(max);
            int r = right(max);
            if (l < size && data[l] > data[max]) {
                max = l;
            }
            if (r < size && data[r] > data[max]) {
                max = r;
            }
            if (i == max) {
                return;
            }
            swap(max, i);
            i = max;
        }
    }

    void sort() {
        int i = data.size() - 1;
        while (i > 0) {
            swap(0, i);
            i--;
            sink(i + 1, 0);
        }
    }
    void print() {
        printf("==\n");
        for (int i = 0; i < data.size(); i++) {
            printf("%d ", data[i]);
        }
        printf("\n==\n");
    }
private:
    void build() {
        for (int i = parent(data.size() - 1); i >= 0; i--) {
            sink(data.size(), i);
        }
    }
    void swap(int i, int j) {
        T tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }
    int left(int i) {
        return i * 2 + 1;
    }
    int right(int i) {
        return i * 2 + 2;
    }
    int parent(int i) {
        return (i - 1) / 2;
    }

    std::vector<T> data;
};

} // Algo