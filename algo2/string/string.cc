#include <iostream>
#include <cassert>
#include <cstring>
#include <memory>
#include <algorithm>


bool isUniqueStr(const std::string str) {
    if (str.size() > 256) {
        return false;
    }
    bool charset[256] = {false};
    for (int i = 0; i < str.size(); i++) {
        int index = str.at(i);
        assert(index <= 256);
        if (charset[index]) {
            return false;
        }
        charset[index] = true;
    }
    return true;
}

void reverseStr(char* const str) {
    assert(str != nullptr);
    char* start = str;
    char* end = str;
    while (*end != '\0') {
        end++;
    }

    end--;
    char tmp;
    while (start < end) {
        tmp = *start;
        *start = *end;
        *end = tmp;
        start++;
        end--;
    } 
}

bool isPermutation(const std::string& s1, const std::string& s2) {
    if (s1.size() != s2.size()) {
        return false;
    }
    std::string tmp1 = s1;
    std::sort(tmp1.begin(), tmp1.end());
    std::string tmp2 = s2;
    std::sort(tmp2.begin(), tmp2.end());
    return tmp1 == tmp2;
}

bool isPermutation2(const std::string& s1, const std::string& s2) {
    if (s1.size() != s2.size()) {
        return false;
    }

    int charset[256] = {0};
    for (int i = 0; i < s1.size(); i++) {
        int c = s1.at(i);
        assert(c <= 256);
        charset[c]++;
    }
    for (int i = 0; i < s2.size(); i++) {
        int c = s2.at(i);
        assert(c <= 256);
        if (--charset[c] < 0) {
            return false;
        }
    }
    return true;
}

void replaceSpaces(char* str, int length) {
    int newLength = 0;
    char* pos = str;
    int numSpaces = 0;
    int strLength = 0;
    while (*pos != '\0') {
        assert((pos - str) < length);
        if (*pos == ' ') {
            numSpaces++;
        }
        pos++;
    }
    strLength = pos - str;
    newLength = strLength + numSpaces * 2;
    assert(newLength + 1 <= length);
    str[newLength + 1] = '\0';
    for (int i = strLength; i >= 0; i--) {
        if (str[i] == ' ') {
            str[newLength] = '0';
            str[newLength - 1] = '2';
            str[newLength - 2] = '%';
            newLength = newLength - 3;

        } else {
            str[newLength] = str[i];
            newLength--;
        }
    }
}


void rotateMatrix(std::vector<std::vector<int>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < n; j++) {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[n - i - 1][j];
            matrix[n - i - 1][j] = tmp;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
    }
}


void printMatrix(std::vector<std::vector<int>> matrix) {
    int n = matrix.size();
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

#define TEST_CSTR "abcdef"

int main(int, char**) {
    std::string test = "abcdef";
    std::cout << "The string " << test << " is unique: " << isUniqueStr(test) << std::endl;
    test ="aabcdef";
    std::cout << "The string " << test << " is unique: " << isUniqueStr(test) << std::endl;

    const char* test_cstr = TEST_CSTR;
    std::unique_ptr<char[]> test_c(new char[7]);
    memcpy(test_c.get(), test_cstr, 7);
    reverseStr(test_c.get());
    std::cout << "Reverse string " << test_cstr << " to: " << test_c.get() << std::endl;

    const std::string s1 = "god";
    const std::string s2 = "dog";
    std::cout << "The string " << s1 << " and " << s2 << " are permutation: " << isPermutation(s1, s2) << std::endl;

    const char* replace_str_orig = "abcdef xyz ";
    std::unique_ptr<char[]> replace_str(new char[16]);
    memcpy(replace_str.get(), replace_str_orig, 12);
    replaceSpaces(replace_str.get(), 16);
    std::cout << "replace spaces for string " <<replace_str_orig << " : " <<  replace_str.get() << std::endl;


    std::vector<std::vector<int>> matrix;
    matrix.resize(4);
    for (int i = 0; i < 4; i++) {
        matrix[i].resize(4);
        for (int j = 0; j < 4; j++) {
            int x = random() % 100;
            matrix[i][j] = x;
        }
    }
    printMatrix(matrix);
    rotateMatrix(matrix);
    std::cout << std::endl;
    printMatrix(matrix);
}