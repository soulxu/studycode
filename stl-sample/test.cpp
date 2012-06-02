#include "Date.h"

#include <iostream>
#include <locale>
#include <vector>

#include "Container.hpp"
#include "LinkList.hpp"

using namespace std;

template<class T>
void printSeq(T &t) {
    for (typename T::iterator b = t.begin(); b != t.end(); b++) {
        cout << *b << endl;
    }
}

int main() {
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    printSeq(v);
    LinkList<int> l;
    l.push_back(1);
    l.push_back(2);
    printSeq(l);
    return 0;
}
