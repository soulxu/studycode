#include <iostream>
#include <vector>


void move(std::vector<int>& src, std::vector<int>& tar) {
    int i = src.back();
    src.pop_back();
    tar.push_back(i);
}


void hannota(int n, std::vector<int>& src, std::vector<int>& buf, std::vector<int>& tar) {
    if (n == 1) {
        move(src, tar);
        return;
    }
    hannota(n - 1, src, tar, buf);
    move(src, tar);
    hannota(n - 1, buf, src, tar);
}

int main(int, char**) {
    std::vector<int> A;
    std::vector<int> B;
    std::vector<int> C;
    for (int i = 0; i < 10; i++) {
        A.push_back(i);
    }
    hannota(A.size(), A, B, C);
    for (int i = 0; i < C.size(); i++) {
        std::cout << C[i] << " " << std::endl;
    }
    return 0;
}