#ifndef _SEARCH_TREE_F_H_
#define _SEARCH_TREE_F_H_

#include "node.h"

template <class T>
class SearchTreeF {
public:
	SearchTreeF();
	SearchTreeF(T t);
	SearchTreeF(const SearchTreeF<T> &other);

	virtual ~SearchTreeF();

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
        NodeCopy(SearchTreeF<T> *tree);
        virtual void operator()(T t);
    private:
        SearchTreeF<T> *m_tree;
	};

	void insertNode(Node<T> *n, T t);
	void clearNode(Node<T> *n);
	Node<T> *findMinNode(Node<T> *n);
	Node<T> *findMaxNode(Node<T> *n);
    Node<T> *findNode(Node<T> *n, T t);
	bool containNode(Node<T> *n, T t);
    void removeNode(Node<T> *n, T t);

protected:
	Node<T> *m_root;
};

template <class T>
SearchTreeF<T>::NodeCopy::NodeCopy(SearchTreeF<T> *tree) : m_tree(tree) {

}

template <class T>
void SearchTreeF<T>::NodeCopy::operator()(T t) {
	m_tree->insert(t);
}

template <class T>
SearchTreeF<T>::SearchTreeF() : m_root(NULL) {

}

template <class T>
SearchTreeF<T>::SearchTreeF(T t) : m_root(new Node<int>(t)) {

}

template <class T>
SearchTreeF<T>::SearchTreeF(const SearchTreeF<T> &other) : m_root(NULL) {
    if (other.m_root != NULL) {
        NodeCopy c(this);
        other.m_root->iteratorPreOrder(c);
    }
}

template <class T>
SearchTreeF<T>::~SearchTreeF() {
	clear();
}

template <class T>
void SearchTreeF<T>::insert(T t) {
	if (this->m_root == NULL) {
		this->m_root = new Node<int>(t);
		return;
	}

	insertNode(this->m_root, t);
}

template <class T>
void SearchTreeF<T>::insertNode(Node<T> *node, T t) {
    while (1) {
	    if (t < node->getValue()) {
		    if (node->getLeft() == NULL) {
			    node->setLeft(new Node<int>(t));
                break;
		    }
		    else {
                node = node->getLeft();
		    }
	    }
	    else if (t > node->getValue()) {
		    if (node->getRight() == NULL) {
			    node->setRight(new Node<int>(t));
                break;
		    }
		    else {
                node = node->getRight();
		    }
	    }
        else {
            //didn't process eque
            break;
        }
    }
}

template <class T>
void SearchTreeF<T>::clear() {
	clearNode(this->m_root);		
	this->m_root = NULL;
}

template <class T>
void SearchTreeF<T>::clearNode(Node<T> *node) {
	if (node == NULL) {
		return;
	}

	clearNode(node->getLeft());
	clearNode(node->getRight());
	delete node;
}

template <class T>
Node<T> *SearchTreeF<T>::findMin() {
		return findMinNode(this->m_root);
}

template <class T>
Node<T> *SearchTreeF<T>::findMinNode(Node<T> *n) {
    if (n == NULL) {
        return NULL;
    }

	while (n->getRight() != NULL) {
		n = n->getRight();
	}

	return n;
}

template <class T>
Node<T> *SearchTreeF<T>::findMax() {
	return findMaxNode(this->m_root);
}

template <class T>
Node<T> *SearchTreeF<T>::findMaxNode(Node<T> *n) {
    if (n == NULL) {
        return NULL;
    }

	while (n->getLeft() != NULL) {
		n = n->getLeft();
	}

	return n;
}

template <class T>
Node<T> *SearchTreeF<T>::find(T t) {
	findNode(this->m_root, t);
}

template <class T>
Node<T> *SearchTreeF<T>::findNode(Node<T> *node, T t) {
    while (node != NULL) {
	    if (t < node->getValue()) {
            node = node->getLeft();
	    }
	    else if (t > node->getValue()) {
            node = node->getRight();
	    }
        else {
            break;
        }
    }
	
	return node;
}

template <class T>
bool SearchTreeF<T>::contain(T t) {
	return containNode(this->m_root, t);
}

template <class T>
bool SearchTreeF<T>::containNode(Node<T> *node, T t) {
    while (node != NULL) {
        if (t < node->getValue()) {
            node = node->getLeft();
	    }
	    else if (t > node->getValue()) {
            node = node->getRight();
	    }
        else {
            break;
        }
    }

	return node;
}

template <class T>
void SearchTreeF<T>::removeNode(Node<T> *n, T t) {
    Node<T> *prev = NULL;

    while (n != NULL) {
	    if (t < n->getValue()) {
                prev = n;
                n = n->getLeft();
	    }
	    else if (t > n->getValue()) {
                prev = n;
                n = n->getRight();
	    }
	    else {
            if ((n->getLeft() != NULL) && (n->getRight() != NULL)) {
                Node<T> *min = findMinNode(n->getRight());
                n->setValue(min->getValue());
                
                Node<T> *prev = n;
                n = n->getRight();

                if (n->getValue() == min->getValue()) {
                    prev->setRight(NULL);
                    delete n;
                }
                else {
                    prev = n;
                    n = n->getLeft();

                    while (n != NULL) {
                        if (n->getValue() == min->getValue()) {
                            prev->setLeft(NULL);
                            delete n;
                            break;
                        }

                        prev = n;
                        n = n->getLeft();
                    }
                }
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

            break;
	    }
    }
}

template <class T>
void SearchTreeF<T>::remove(T t) {
	removeNode(this->m_root, t);
}

template <class T>
Node<T> *SearchTreeF<T>::getRoot() {
	return m_root;
}

#endif
