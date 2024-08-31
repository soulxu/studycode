#pragma once

#include <functional>

namespace Algo {
template <class T>
class ArrayTree {
public:
    ArrayTree(int c) : capacity(c) {
        tree = new T[c];
    }

    bool add(int index, T data) {
        if (index >= capacity) {
            return false;
        }
        tree[index] = data;
        size++;
        return true;
    }

    using DataVisitor = std::function<void(T)>;

    void travelPreOrder(DataVisitor visitor) {
        travelPreOrderImpl(0, visitor);
    }

private:

    void travelPreOrderImpl(int index, DataVisitor visitor) {
        if (index >= size) {
            return;
        }
        visitor(tree[index]);
        travelPreOrderImpl(index * 2 + 1, visitor);
        travelPreOrderImpl(index * 2 + 2, visitor);
    }

    T* tree{nullptr};
    int capacity{0};
    int size{-1};
};

}