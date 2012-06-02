#ifndef _HASH_H_
#define _HASH_H_

#include <stdlib.h>
#include <string.h>

template <class KeyType>
unsigned int hash(KeyType key, int n);

template <>
unsigned int hash<char *>(char *key, int n) {
	int h = n;

	for (int i = 0; i < strlen(key); i++) {
		h += key[i];
	}

	return h;
}

template <>
unsigned int hash<char>(char key, int n) {
	return key;
}

template<class KeyType, class ValueType>
class HashNode {
public:
	KeyType m_key;
	ValueType m_value;
	unsigned int m_h;
	HashNode<KeyType, ValueType> *next;
};

template<class KeyType, class ValueType, int size = 10>
class Hash {
public:
	Hash();
	~Hash();
	bool contain(const KeyType key) const;
	void insert(const KeyType key, const ValueType val);
	ValueType value(const KeyType key) const;

	HashNode<KeyType, ValueType> *findNode(const KeyType key) const;
private:
	HashNode<KeyType, ValueType>  **nodes;
};

template<class KeyType, class ValueType, int size>
Hash<KeyType, ValueType, size>::Hash() {
	nodes = new HashNode<KeyType, ValueType> *[size];
	for (int i = 0; i < size; i++) {
		nodes[i] = NULL;
	}
}

template <class KeyType, class ValueType, int size>
Hash<KeyType, ValueType, size>::~Hash() {
	for (int i = 0; i < size; i++) {
		if (nodes[i] != NULL) {
			HashNode<KeyType, ValueType> *n = nodes[i];
			HashNode<KeyType, ValueType> *o = n;
			while (n != NULL) {
				o = n;
				n = n->next;
				delete o;
			}
		}
	}
	delete[] nodes;
}

template <class KeyType, class ValueType, int size>
bool Hash<KeyType, ValueType, size>::contain(const KeyType key) const {
	return findNode(key) != NULL;
}

template <class KeyType, class ValueType, int size>
HashNode<KeyType, ValueType> *Hash<KeyType, ValueType, size>::findNode(const KeyType key)  const 
{
	unsigned int h = hash(key, size);
	HashNode<KeyType, ValueType> *n = nodes[h % size];

	if (n != NULL) {
		while ((n->m_h != h) && (n->next != NULL)) {
			n = n->next;
		}

		if (n->m_h == h) {
			return n;
		}
	}

	return NULL;
}

template <class KeyType, class ValueType, int size>
void Hash<KeyType, ValueType, size>::insert(const KeyType key, const ValueType value) {
	uint h = hash(key, size);
	HashNode<KeyType, ValueType> *newNode = new HashNode<KeyType, ValueType>();
	newNode->m_key = key;
	newNode->m_value = value;
	newNode->m_h = h;
	newNode->next = NULL;

	if (nodes[h % size] == NULL) {
		nodes[h % size] = newNode;
	}
	else {
		HashNode<KeyType, ValueType> *n = nodes[h % size];

		while (n->next != NULL) {
			if (n->m_h == h) {
				n->m_key = key;
				n->m_value = value;
				delete newNode;
				return;
			}

			n = n->next;
		}

		n->next = newNode;
	}
}

template <class KeyType, class ValueType, int size>
ValueType Hash<KeyType, ValueType, size>::value(const KeyType key) const {
	HashNode<KeyType, ValueType> *n = findNode(key);
	
	if (n == 0) {
		return ValueType();
	}

	return n->m_value;
}

#endif
