#pragma once

#include <memory>

template <class T>
class List {
public:

    void pushBack(T data) {
        std::unique_ptr<Node>* new_node = nullptr;
        if (head_ == nullptr) {
            new_node = &head_;
        } else {
            new_node = last();
        }
        addNewNode(*new_node, data);
    }

    // T popFront() {

    // }

    T* at(int index) {
        Node* cur = head_.get();
        for (int i = 0; i < index && cur != nullptr; i++) {
            cur = cur->next_.get();
        }
        if (cur == nullptr) {
            return nullptr;
        }
        return cur->data_.get();
    }

    
private:
    struct Node {
        Node(T data, std::unique_ptr<Node>&& next) :
            data_(std::make_unique<T>(data)), next_(std::move(next)){}

        std::unique_ptr<T> data_{nullptr};
        std::unique_ptr<Node> next_{nullptr};
    };

    void addNewNode(std::unique_ptr<Node>& node, T data) {
       node = std::make_unique<Node>(data, nullptr);
    }

    std::unique_ptr<Node>* last() {
        std::unique_ptr<Node>* cur = &head_;
        while (*cur != nullptr) {
            cur = &((*cur)->next_);
        }
        return cur;
    }

    std::unique_ptr<Node> head_{nullptr};
};