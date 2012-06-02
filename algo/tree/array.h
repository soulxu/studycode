#ifndef _ARRAY_H_
#define _ARRAY_H_

template <class T, int inflate_size = 20>
class Array {
public:
	Array();
	~Array();
	
	void insert(int i, T t);
	void append(T t);
	T get(int i);
	void remove(int i);
	int size();
	int find(T t);

private:
	void inflateStorage();

private:
	int m_storageSize;
	int m_size;
	T *m_data;
};

template <class T, int inflate_size>
int Array<T, inflate_size>::size() {
	return m_size;
}

template <class T, int inflate_size>
Array<T, inflate_size>::Array() : m_data(NULL), m_storageSize(0), m_size(0) {
	m_storageSize = inflate_size;
	m_data = new T[inflate_size];
}

template <class T, int inflate_size>
Array<T, inflate_size>::~Array() {
	delete[] m_data;
}

template <class T, int inflate_size>
void Array<T, inflate_size>::inflateStorage() {
	T *newData = new T[m_storageSize + inflate_size];
	
	for (int i = 0; i < m_storageSize; i++) {
		newData[i] = m_data[i];
	}

	m_storageSize += inflate_size;
}

template <class T, int inflate_size>
void Array<T, inflate_size>::append(T t) {
	if (m_size == m_storageSize) {
		inflateStorage();
	}

	m_data[m_size] = t;
	m_size++;
}

template <class T, int inflate_size>
void Array<T, inflate_size>::insert(int i, T t) {
	for (int j = m_size; j > i; j--) {
		m_data[j] = m_data[j - 1];
	}

	m_data[i] = t;
	m_size++;
}

template <class T, int inflate_size>
T Array<T, inflate_size>::get(int i) {
	return m_data[i];
}

template <class T, int inflate_size>
void Array<T, inflate_size>::remove(int i) {
	if (i > 0) {
		for ( ; i < m_size - 1; i++) {
			m_data[i] = m_data[i + 1];
		}

		m_size--;
	}
}

template <class T, int inflate_size>
int Array<T, inflate_size>::find(T t) {
	for (int i = 0; i < m_size; i++) {
		if (m_data[i] == t) {
			return i;
		}
	}
}

#endif
