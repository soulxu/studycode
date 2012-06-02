#ifndef _AVL_TREE_H_
#define _AVL_TREE_H_

#include "search_tree.h"

template <class T>
class AVLTree : public SearchTree<T> {
public:
    AVLTree() { }
    virtual ~AVLTree() {}

    virtual void insert(T t);

private:
    Node<T> *balanceNode(Node<T> *n);

    Node<T> *singleRotateWithLeft(Node<T> *n);

    Node<T> *singleRotateWithRight(Node<T> *n);

    Node<T> *doubleRotateWithLeft(Node<T> *n);

    Node<T> *doubleRotateWithRight(Node<T> *n);

    int getNodeHeight(Node<T> *n);
};

template <class T>
void AVLTree<T>::insert(T t) {
    SearchTree<T>::insert(t);
    this->m_root= balanceNode(this->m_root);
}

template <class T>
int AVLTree<T>::getNodeHeight(Node<T> *n) {
    if (n == NULL) {
        return NULL;
    }

    return n->getHeight();
}

template <class T>
Node<T> *AVLTree<T>::balanceNode(Node<T> *n) {
    if (n == NULL) {
        return NULL;
    }

    n->setLeft(balanceNode(n->getLeft()));
    n->setRight(balanceNode(n->getRight()));

    if ((getNodeHeight(n->getLeft()) - getNodeHeight(n->getRight()) == 2)) {
        if (getNodeHeight(n->getLeft()->getLeft()) > getNodeHeight(n->getLeft()->getRight())) {
            n = singleRotateWithRight(n);
        }
        else {
           n = doubleRotateWithRight(n);
        }
    }

    if ((getNodeHeight(n->getRight()) - getNodeHeight(n->getLeft())) == 2) {
        if (getNodeHeight(n->getRight()->getRight()) > getNodeHeight(n->getRight()->getLeft())) {
            n = singleRotateWithLeft(n);
        }
        else {
            n = doubleRotateWithLeft(n);
        }
    }

    
    return n;
}

template <class T>
Node<T> *AVLTree<T>::singleRotateWithRight(Node<T> *n) {
    Node<T> *tmp = n->getLeft();
    n->setLeft(n->getLeft()->getRight());
    tmp->setRight(n);
    return tmp;
}

template <class T>
Node<T> *AVLTree<T>::singleRotateWithLeft(Node<T> *n) {
    Node<T> *tmp = n->getRight();
    n->setRight(n->getRight()->getLeft());
    tmp->setLeft(n);
    return tmp;
}

template <class T>
Node<T> *AVLTree<T>::doubleRotateWithRight(Node<T> *n) {
    n->setLeft(singleRotateWithLeft(n->getLeft()));
    return n = singleRotateWithRight(n);
}

template <class T>
Node<T> *AVLTree<T>::doubleRotateWithLeft(Node<T> *n) {
    n->setRight(singleRotateWithRight(n->getRight()));
    return n = singleRotateWithLeft(n);
}

#endif
