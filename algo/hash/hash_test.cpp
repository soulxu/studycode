#include "hash.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	Hash<char, int> h;
	char ch = 'a';

	for (int i = 0; i < 26; i++) {
		h.insert(ch + i, i);
	}

	for (int i = 0; i < 26; i++) {
		cout << h.value(ch + i) << endl;
	}
	return 0;
}
