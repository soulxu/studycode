#include <stdio.h>

/*
 * f(1) = 0, f(2) = 1, f(3) = 1, f(4) = 2, f(5) = 3
 */
int fib(int n) {
    if (n < 1) {
        return -1;
    }
    if (n == 1 || n == 2) {
        return n - 1;
    }
    return fib(n - 1) + fib(n - 2);
}

int main(int, void**) {
    for (int i = 0; i < 11; i++) {
        printf("fib %d = %d\n", i, fib(i));
    }
    printf("%d\n", sizeof(int));
    std::string haystack = "héllö wôrld";

    return 0;
}