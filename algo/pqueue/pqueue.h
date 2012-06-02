#ifndef _PQUEUE_H_
#define _PQUEUE_H_

#include <iostream>

template <class T, int size>
class PQueue {
public:
	PQueue();
	~PQueue();

	void insert(T t);
	T deleteMin();

	void print() {
		for (int i = 1; i <= m_elementNum; i++) {
			std::cout << m_elements[i] << ", ";
		}
		std::cout << std::endl;
	}
private:
	int m_elementNum;
	T *m_elements;
};

template <class T, int size>
PQueue<T, size>::PQueue() {
	m_elementNum = 0;
	m_elements = new T[size + 1];
	m_elements[0] = T();
}

template <class T, int size>
PQueue<T, size>::~PQueue() {
	delete[] m_elements;
}

template <class T, int size>
void PQueue<T, size>::insert(T t) {
	if (m_elementNum >= size) {
		return;
	}

	m_elementNum++;
	int n = m_elementNum;
	m_elements[n] = t;

	for (n = m_elementNum; n > 1; n /= 2) {
		if (t >= m_elements[n / 2]) {
			break;
		}

		m_elements[n] = m_elements[n / 2];
	}

	m_elements[n] = t;
	
}

template <class T, int size>
T PQueue<T, size>::deleteMin() {
	if (m_elementNum <= 1) {
		return T();
	}

	T ret = m_elements[1];
	T last = m_elements[m_elementNum--];
	int i = 1;
	int left = 2;
	int right =3;

	while ((i * 2) <= m_elementNum) {
        if (m_elements[left] >= m_elements[right]) {
            m_elements[i] = m_elements[right];
            i = right;
        }
        else {
            m_elements[i] = m_elements[left];
            i = left;
        }

		left = i * 2;
		right = left + 1;
	}
	
    m_elements[i] = last;
	return ret;
}



#endif
