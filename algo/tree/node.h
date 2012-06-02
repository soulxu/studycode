#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <stdlib.h>

template <class T>
class Visitor {
public:
	virtual void operator()(T t) = 0;
    virtual ~Visitor() {};
};

template <class T>
class Node {
public:
	Node();
	Node(T value);
	Node(Node<T> *left, Node<T> *right);
	Node(T value, Node<T> *left, Node<T> *right);

	virtual ~Node();	

	int getHeight();

	void setValue(T);
	T getValue() const;

	Node<T> *getLeft() const;
	Node<T> *getRight() const;

	void setLeft(Node<T> *left);
	void setRight(Node<T> *right);	

	void iteratorPreOrder(Visitor<T> &v);
	void iteratorMidOrder(Visitor<T> &v);
	void iteratorPastOrder(Visitor<T> &v);

private:
	Node<T> *m_left;
	Node<T> *m_right;
	T m_value;
};

template <class T>
Node<T>::Node() : m_left(NULL), m_right(NULL) { }

template <class T>
Node<T>::Node(T value) : m_left(NULL), m_right(NULL), m_value(value) { }

template <class T>
Node<T>::Node(Node<T> *left, Node<T> *right) : m_left(left), m_right(right) { }

template <class T>
Node<T>::Node(T value, Node<T> *left, Node<T> *right) : m_left(left), m_right(right), m_value(value) { }

template <class T>
Node<T>::~Node() { }

template <class T>
Node<T> *Node<T>::getLeft() const {
	return m_left;
}

template <class T>
Node<T> *Node<T>::getRight() const {
	return m_right;
}

template <class T>
void Node<T>::setLeft(Node<T> *left) {
	m_left = left;
}

template <class T>
void Node<T>::setRight(Node<T> *right) {
	m_right = right;
}

template <class T>
T Node<T>::getValue() const {
	return m_value;
}

template <class T>
void Node<T>::setValue(T value) {
	m_value = value;
}

template <class T>
void Node<T>::iteratorPreOrder(Visitor<T> &v) {
	v(m_value);
	if (m_left != NULL) { m_left->iteratorPreOrder(v); }
	if (m_right != NULL) { m_right->iteratorPreOrder(v); }
}

template <class T>
void Node<T>::iteratorMidOrder(Visitor<T> &v) {
	if (m_left != NULL) m_left->iteratorMidOrder(v);
	v(m_value);
	if (m_right != NULL) m_right->iteratorMidOrder(v);
}

template <class T>
void Node<T>::iteratorPastOrder(Visitor<T> &v) {
	if (m_left != NULL) m_left->iteratorPastOrder(v);
	if (m_right != NULL) m_right->iteratorPastOrder(v);
	v(m_value);
}

template <class T>
int Node<T>::getHeight() {
	int height = 0;

        if ((m_left == NULL) && (m_right == NULL)) {
		height = 1;
	}
	else if (m_right == NULL) {
		height = m_left->getHeight() + 1;
	}
	else if (m_left == NULL) {
		height = m_right->getHeight() + 1;
	}
	else {
		int leftHeight = m_left->getHeight() + 1;
		int rightHeight = m_right->getHeight() + 1;

		height = (leftHeight >= rightHeight) ? leftHeight : rightHeight;
	}

	return height;
}


#endif
