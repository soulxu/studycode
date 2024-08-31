#pragma once

#include <iostream>
#include <memory>

using namespace std;

namespace Algo {

class LinkList {
public:
    class LinkObject {
    public:
        LinkObject(int data, LinkObject* next) : data_(data), next_(next) {}
        int data_{0};
        LinkObject* next_{nullptr};
    };

    LinkList() {}
    ~LinkList() {
        while(!empty()) {
            popFront();
        }
    }

    void pushBack(int data) {
        LinkObject* newNode = new LinkObject(data, nullptr);
        if (head_ == nullptr) {
            head_ = newNode;
            return;
        }

        LinkObject* cur = head_;
        while (cur->next_ != nullptr) {
            cur = cur->next_;
        }
        
        cur->next_ = newNode;
    }
    int popFront() {
        if (head_ == nullptr) {
            return 0;
        }
        int ret = head_->data_;
        LinkObject* to_delete = head_;
        head_ = head_->next_;
        delete to_delete;
        return ret;
    }
    bool empty() {
        return head_ == nullptr;
    }
    void print() {
        LinkObject* cur = head_;
        while (cur != nullptr) {
            cout << cur->data_ << " ";
            cur = cur->next_;
        }
        cout << endl;
    }
private:
    LinkObject* head_{nullptr};
};

} // Algo