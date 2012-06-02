#include "node.h"
#include "list.h"
#include "array.h"
#include "stack.h"
#include "search_tree.h"
#include "avl_tree.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
/*
	Node<int> tree(1);
	Node<int> l1(2);
	Node<int> l2(3);
	Node<int> r1(4);
	Node<int> r2(5);
	
	tree.setLeft(&l1);
	tree.setRight(&r1);
	l1.setLeft(&l2);
	
	l2.setRight(&r2);
//	IntVistor v;
//	tree.iteratorPreOrder(v);

	Array<int> a;
	
	for (int i = 0; i < 10; i++) {
		a.append(i);
	}

	a.insert(0, 11);
	a.insert(11, 22);
	a.insert(13, 33);
	for (int i = 0; i < 12; i++) {
		cout << a.get(i) << endl;
	}

	Stack<int, List<int> > s;
	
	for (int i = 0; i < 10; i++) {
		s.push(i);
	}
*/

    AVLTree<int> tree;
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);


	return 0;
}
