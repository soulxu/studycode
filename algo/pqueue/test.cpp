#include "pqueue.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	PQueue<int, 10> p;
	p.insert(3);
	p.print();
	p.insert(2);
	p.print();
	p.insert(1);
	p.print();
	p.insert(8);
	p.print();
	p.insert(5);
	p.print();
	cout << "del min: " << p.deleteMin() << endl;
	p.print();
	cout << "del min: " << p.deleteMin() << endl;
	p.print();
	return 0;
}
