#ifndef _STACK_H_
#define _STACK_H_

template <class T, class Container>
class Stack {
public:

	void push(T t);
	void pop();
	T top();
private:
	Container m_container;
};

template <class T, class Container>
void Stack<T, Container>::push(T t) {
	m_container.append(t);
}

template <class T, class Container>
void Stack<T, Container>::pop() {
	m_container.remove(m_container.size() - 1);
}

template <class T, class Container>
T Stack<T, Container>::top() {
	return m_container.get(m_container.size() - 1);
}

#endif
