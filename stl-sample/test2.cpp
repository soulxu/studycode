#include "LinkList.hpp"

#include <iostream>

using namespace std;

class A {
public:
	A(int i) : m_i(i) {
		cout << "construct A: " << i << endl;
	}

	A(const A &other) : m_i(other.m_i) {
		cout << "copy construct A: " << m_i << endl;
	}

	~A() {
		cout << "destruct A: " << m_i << endl;
	}

	int getNum() { return m_i; }

private:
	int m_i;
};

int main() {
	LinkList<A> l;
    

	for (int i = 0; i < 10; i++) {
        cout << "push_back: " << i << endl;
		l.push_back(A(i));
	}

    cout << "end push_back" << endl;

    LinkList<A>::iterator iter = l.begin();
    LinkList<A>::iterator end = l.end();

	while (iter != end) {
        cout << "iter: " << (*(iter++)).getNum() << endl;
    }
    
    cout << "end: " << l.size() << endl;
	return 0;
}
