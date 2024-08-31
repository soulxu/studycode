#include "list2.h"

int main(int, char**) {
    List<int> list;
    list.pushBack(1);
    list.pushBack(2);
    list.print();
    list.insertAfter(-1, 0);
    list.print();
    list.insertAfter(0, 3);
    list.print();
}