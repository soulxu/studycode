#ifndef _LIST_H_
#define _LIST_H_

template <class T>
class List {
public:
	struct Node {
		T data;
		struct Node *next;
	};

	List();
	~List();

	void insert(int i, T t);
	void append(T t);
	void remove(int i);
	int find(T t);
	T get(int i);
	int size();

private:
	Node *m_head;
	int m_size;
};

template <class T>
List<T>::List() : m_head(NULL), m_size(0) {
	
}

template<class T>
List<T>::~List() {
	if (m_head != NULL) {
		Node *p = m_head;
		Node *q = NULL;

		while (p != NULL) {
			q = p;
			p = p->next;
			free(q);
		}
	}
}

template <class T>
void List<T>::insert(int i, T t) {
	if (m_head == NULL) {
		if (i = 0) {
			m_head = new Node();
			m_head->data = t;
			m_head->next = NULL;
			m_size++;
		}
	}
	else {
		Node *p = m_head;
		Node *n = NULL;
		Node *q = NULL;

		while ((p != NULL) && (i != 0)) {
			q = p;
			p = p->next;
			i--;
		}

		if (i == 0) {
			if (q == NULL) {
				n = new Node();
				n->data = t;
				n->next = p;
				m_head = n;
			}
			else {
				n = new Node();
				n->data = t;
				q->next = n;
				n->next = p;
			}
			
			m_size++;
		}
	}
}

template <class T>
void List<T>::append(T t) {
	if (m_head == NULL) {
		m_head = new Node();
		m_head->data = t;
		m_head->next = NULL;
		m_size++;
	}
	else {
		Node *p = m_head;

		while (p->next != NULL) {
			p = p->next;
		}

		p->next = new Node();
		p->next->data = t;
		p->next->next = NULL;
		m_size++;
	}
}

template <class T>
void List<T>::remove(int i) {
	Node *p = m_head;
	Node *q = NULL;

	while ((p != NULL) && (i != 0)) {
		q = p;
		p = p->next;
		i--;
	}

	if ((p != NULL) && (i == 0)) {
		if (q == NULL) {
			delete m_head;
			m_head = NULL;
		}
		else {
			q->next = p->next;
			delete p;
		}
		m_size--;
	}
}

template <class T>
int List<T>::find(T t) {
	Node *p = m_head;
	int size = 0;

	while (p != NULL) {
		if (p->data == t) {
			return size;
		}

		size++;
		p = p->next;
	}
}

template <class T>
T List<T>::get(int i) {
	Node *p = m_head;
	
	while ((p != NULL) && (i != 0)) {
		p = p->next;
		i--;
	}

	if ((p != NULL) && (i == 0)) {
		return p->data;
	}
	
	return T();
}
#endif
