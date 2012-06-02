#ifndef _SEARCH_TREE_H_
#define _SEARCH_TREE_H_

#include "node.h"

template <class T>
class SearchTree {
public:
	SearchTree();
	SearchTree(T t);
	SearchTree(const SearchTree<T> &other);

	virtual ~SearchTree();

	virtual void insert(T t);
	virtual void remove(T t);
	virtual void clear();

	Node<T> *findMin();
	Node<T> *findMax();
	Node<T> *find(T t);

	bool contain(T t);

	Node<T> *getRoot();

private:
    class NodeCopy : public Visitor<T> {
	public:
        NodeCopy(SearchTree<T> *tree);
        virtual void operator()(T t);
    private:
        SearchTree<T> *m_tree;
	};

	void insertNode(Node<T> *n, T t);
	void clearNode(Node<T> *n);
	Node<T> *findMinNode(Node<T> *n);
	Node<T> *findMaxNode(Node<T> *n);
    Node<T> *findNode(Node<T> *n, T t);
	bool containNode(Node<T> *n, T t);
	Node<T> *removeNode(Node<T> *n, T t);

protected:
	Node<T> *m_root;
};

template <class T>
SearchTree<T>::NodeCopy::NodeCopy(SearchTree<T> *tree) : m_tree(tree) {

}

template <class T>
void SearchTree<T>::NodeCopy::operator()(T t) {
	m_tree->insert(t);
}

template <class T>
SearchTree<T>::SearchTree() : m_root(NULL) {

}

template <class T>
SearchTree<T>::SearchTree(T t) : m_root(new Node<int>(t)) {

}

template <class T>
SearchTree<T>::SearchTree(const SearchTree<T> &other) : m_root(NULL) {
    if (other.m_root != NULL) {
        NodeCopy c(this);
        other.m_root->iteratorPreOrder(c);
    }
}

template <class T>
SearchTree<T>::~SearchTree() {
	clear();
}

template <class T>
void SearchTree<T>::insert(T t) {
	if (this->m_root == NULL) {
		this->m_root = new Node<int>(t);
		return;
	}

	insertNode(this->m_root, t);
}

template <class T>
void SearchTree<T>::insertNode(Node<T> *node, T t) {
	if (t < node->getValue()) {
		if (node->getLeft() == NULL) {
			node->setLeft(new Node<int>(t));
		}
		else {
			insertNode(node->getLeft(), t);
		}
	}
	else if (t > node->getValue()) {
		if (node->getRight() == NULL) {
			node->setRight(new Node<int>(t));
		}
		else {
			insertNode(node->getRight(), t);
		}
	}
}

template <class T>
void SearchTree<T>::clear() {
	clearNode(this->m_root);		
	this->m_root = NULL;
}

template <class T>
void SearchTree<T>::clearNode(Node<T> *node) {
	if (node == NULL) {
		return;
	}

	clearNode(node->getLeft());
	clearNode(node->getRight());
	delete node;
}

template <class T>
Node<T> *SearchTree<T>::findMin() {
		return findMinNode(this->m_root);
}

template <class T>
Node<T> *SearchTree<T>::findMinNode(Node<T> *n) {
    if (n == NULL) {
        return NULL;
    }

	if (n->getLeft() == NULL) {
		return n;
	}

	return findMinNode(n->getLeft());
}

template <class T>
Node<T> *SearchTree<T>::findMax() {
	return findMaxNode(this->m_root);
}

template <class T>
Node<T> *SearchTree<T>::findMaxNode(Node<T> *n) {
    if (n == NULL) {
        return NULL;
    }

	if (n->getRight() == NULL) {
		return n;
	}

	return findMaxNode(n->getRight());
}

template <class T>
Node<T> *SearchTree<T>::find(T t) {
	findNode(this->m_root, t);
}

template <class T>
Node<T> *SearchTree<T>::findNode(Node<T> *node, T t) {
	if (node == NULL) {
		return NULL;
	}

	if (t < node->getValue()) {
		return findNode(node->getLeft(), t);
	}
	else if (t > node->getValue()) {
		return findNode(node->getRight(), t);
	}
	
	return node;
}

template <class T>
bool SearchTree<T>::contain(T t) {
	return containNode(this->m_root, t);
}

template <class T>
bool SearchTree<T>::containNode(Node<T> *node, T t) {
	if (node == NULL) {
		return false;
	}

    if (t < node->getValue()) {
		return containNode(node->getLeft(), t);
	}
	else if (t > node->getValue()) {
		return containNode(node->getRight(), t);
	}

	return true;
}

template <class T>
Node<T> *SearchTree<T>::removeNode(Node<T> *n, T t) {
	if (n == NULL) {
		return NULL;
	}

	if (t < n->getValue()) {
		n->setLeft(removeNode(n->getLeft(), t));
	}
	else if (t > n->getValue()) {
		n->setRight(removeNode(n->getRight(), t));
	}
	else {
		if ((n->getLeft() != NULL) && (n->getRight() != NULL)) {
            Node<T> *min = findMinNode(n->getRight());
			n->setValue(min->getValue());
            n->setRight(removeNode(n->getRight(), min->getValue()));
		}
		else {
            Node<T> *o = n;

			if (n->getLeft() == NULL) {
				n = n->getRight();
				delete o;
			}
			else if (n->getRight() == NULL) {
				n = n->getLeft();
				delete o;
			}
		}
	}

	return n;
}

template <class T>
void SearchTree<T>::remove(T t) {
	this->m_root = removeNode(this->m_root, t);
}

template <class T>
Node<T> *SearchTree<T>::getRoot() {
	return m_root;
}

#endif
