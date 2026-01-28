#include<iostream>

int fib(int n) {
    if (n < 0) return -1;
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fib(n - 1) + fib(n - 2);
}

int main(int argc, char** argv) {
    int n = std::stoi(argv[1]);
    std::printf("n=%i\n", n);

    for (int i = 0; i < n + 1; i++) {
        std::printf("fib(%i)=%i\n", i, fib(i));
    }
    return 0;
}

