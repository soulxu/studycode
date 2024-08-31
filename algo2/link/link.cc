#include <string>
#include <cstring>
#include <cassert>

#include "link.h"

int main(int, char**) {
    Algo::LinkList l;
    for (int i = 0; i < 10; i++) {
        l.pushBack(i);
        l.print();
    }
    while(!l.empty()) {
        l.popFront();
        l.print();
    }
    return 0;
}