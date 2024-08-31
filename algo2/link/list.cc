#include "list.h"

#include <iostream>

int main(int, char**) {
    List<int> list;
    list.pushBack(1);
    list.pushBack(2);

    std::cout << *(list.at(0)) << std::endl;
    std::cout << *(list.at(1)) << std::endl;
    std::cout << list.at(2) << std::endl;
}