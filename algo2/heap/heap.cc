#include "heap.h"

#include <iostream>

int main(int, char**) {
    Algo::Heap<int> h;
    for (int i = 0; i < 10; i++) {
        int tmp = random() % 10;
        std::cout << "gen num " << tmp << std::endl;
        h.insert(tmp);
        std::cout << h.peekMax() << std::endl;
    }
    std::cout << "===" << std::endl;
    h.print();
    for (int i = 0; i < 10; i++) {
        h.delMax();
        std::cout << "peek " << h.peekMax() << std::endl;
        h.print();
    }

    std::vector<int> d;
    for (int i = 0; i < 10; i++) {
        int tmp = random() % 10;
        std::cout << "gen num " << tmp << std::endl;
        d.push_back(tmp);
    }
    Algo::Heap<int> h2(d);
    h2.print();
    for (int i = 0; i < 10; i++) {
        h2.delMax();
        std::cout << "peek " << h2.peekMax() << std::endl;
    }

    h2.sort();
    h2.print();

    std::vector<int> d2;
    for (int i = 0; i < 10; i++) {
        int tmp = random() % 10;
        std::cout << "gen num " << tmp << std::endl;
        d2.push_back(tmp);
    }
    Algo::Heap<int> h3(d2);
    h3.print();
    h3.sort();
    h3.print();

    return 0;
}