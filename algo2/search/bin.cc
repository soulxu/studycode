#include <vector>
#include <stdlib.h>
#include <iostream>

bool search(std::vector<int> data, int d) {
    int i = 0;
    int j = data.size();
    while (i <= j) {
        int m = (i + j) / 2;
        if (d > data[m]) {
            i = m + 1;
        } else if (d < data[m]) {
            j = m - 1;
        } else {
            return true;
        }
        
    }
    return false;
}

int main(int, char**) {
    std::vector<int> data;
    for (int i = 0; i < 10; i++) {
        int d = random() % 10;
        std::cout << "get num = " << d << std::endl;
        data.emplace_back(d);
    }

    for (int i = 0; i < 5; i++) {
        int d = random() % 10;
        std::cout << "search " << d << ", result " << search(data, d) << std::endl;
    }
    return 0;
}