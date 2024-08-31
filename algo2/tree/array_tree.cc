#include "array_tree.h"

#include <iostream>

int main(int, char**) {
    Algo::ArrayTree<int> tree(10);
    for (int i = 0; i < 10; i++) {
        tree.add(i, i);
    }
    std::cout << "----" << std::endl;
    tree.travelPreOrder([](int data){
        std::cout << data << std::endl;
    });

    return 0;
}