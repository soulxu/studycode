#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#include <iostream>

template <class T, int presize = 10>
class LinkList {
public:
    LinkList() : mem(NULL), psize(0), used(0) { }
    ~LinkList();

    void push_back(const T &t);
    void push_front(const T &t);
    void pop_back();
    void pop_front();

    T &at(int index);

    T &operator[](int index) {
        return at(index);  
    }

    size_t size();

    struct Node {
        Node(const T &t, LinkList *l) : data(t), next(NULL), list(l) { } 
        T data;
        Node *next;

        LinkList *list;

        void *operator new(std::size_t size) {
            using namespace std;
            return list->getNode();
        }

        void operator delete(void *rawmemory) {
        
        }
    };

    friend struct Node;

    class iterator {
    public:
        iterator(Node *node) : p(node) { }

        T &operator*() const {
            return p->data;
        }

        T *operator++() {
            p = p->next;
            return &(p->data);
        }

        T *operator++(int) {
            Node *r = p;
            p = p->next;
            return &(r->data);
        }

        bool operator==(const iterator &iter) const {
            return (p == iter.p);
        }
    
        bool operator!=(const iterator &iter) const {
            return (p != iter.p);
        }

    private:
        Node *p;
    };

    friend class iterator;

    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(NULL);
    }

private:
    void expandMem() {
        int newSize = psize + presize;
        char *newMem = (char *)realloc(mem, sizeof(T) + newSize);
        
        if (newMem != NULL) {
            mem = newMem;
            psize = newSize;
        }
    }

    void *getNodeMem() {
        if (used == psize) {
            expandMem();
        }

        return mem + (sizeof(T) * (used));
    }

private:
    char *mem;
    int psize;
    int used;
    Node *head;
};

template <class T, int presize>
size_t LinkList<T, presize>::size() {
    size_t count = 0;
    Node *p = head;
    
    while (p != NULL) {
        p = p->next;
        count++;
    }

    return count;
}

template <class T, int presize>
void LinkList<T, presize>::push_front(const T &t) {
    Node *newNode = new Node(t);
    newNode->next = head;
    head = newNode;
}

template <class T, int presize>
void LinkList<T, presize>::pop_back() {
    Node *cur = head;
    Node *prev = NULL;
    
    if (cur == NULL) {
        return;
    }

    while (cur->next != NULL) {
        prev = cur;
        cur = cur->next;
    }

    if (prev == NULL) {
        head = NULL;
    }
    else {
        prev->next = NULL;
    }

    delete cur;
}

template <class T, int presize>
void LinkList<T, presize>::pop_front() {
    if (head == NULL) {
        return;
    }

    Node *p = head;
    head = head->next;
    delete p;
}

template <class T, int presize>
LinkList<T, presize>::~LinkList() {
    Node *cur = head;
    Node *prev = NULL;

    while (cur != NULL) {
        prev = cur;
        cur = cur->next;
        delete prev;
    }
}

template <class T, int presize>
LinkList<T, presize>::LinkList() : head(NULL) {

}

template <class T, int presize>
T &LinkList<T, presize>::at(int index) {
    Node *p = head;

    while (index--) {
        p = p->next;
    }

    return p->data;
}

template <class T, int presize>
void LinkList<T, presize>::push_back(const T &t) {
    Node *cur = head;

    Node *newNode = new Node(t, this);
    newNode->next = NULL;

    if (cur == NULL) {
        head = newNode;
        return;
    }

    while (cur->next != NULL) {
        cur = cur->next;
    }

    cur->next = newNode;
}

#endif
