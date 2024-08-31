#pragma once

#include <iostream>

template <class T>
class List {
public:
    ~List() {
        Node* cur = head;
        while (cur != nullptr) {
            Node* to_delete = cur;
            cur = cur->next;
            delete to_delete;
        }
    }

    void pushBack(T data) {
        Node** node = &head;
        while (*node != nullptr) {
            node = &((*node)->next);
        }
        addNode(node, data);
    }

    void print() {
        Node* cur = head;
        while (cur != nullptr) {
            std::cout << cur->data << std::endl;
            cur = cur->next;
        }
        std::cout << "---" << std::endl;
    }

    bool insertAfter(int index, T data) {
        if (index < -1) {
            return false;
        }

        // replace the head;
        if (index == -1) {
            Node* node = new Node(data, head);
            head = node;
            return true;
        }

        Node* cur = head;
        for (int i = 0; i < index && cur != nullptr; i++) {
            std::cout << "$$" << cur->data << std::endl;
            cur = cur->next;
        }
        if (cur == nullptr) {
            return false;
        }

        Node* node = new Node(data, cur->next);
        cur->next = node;
        return true;
    }

private:
    struct Node {
        Node(T d, Node* n) : data(d), next(n) {}
        T data{nullptr};
        Node* next{nullptr};
    };

    void addNode(Node** node, T data) {
        *node = new Node(data, nullptr);
    }    

    Node* head{nullptr};
};