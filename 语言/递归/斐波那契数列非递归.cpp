#include <iostream>

long long fibonacci(int n);

int main() {
    std::cout << fibonacci(8) << std::endl; // 21

    return 0;
}

long long fibonacci(int n) {
    if (n == 0) { return 0; }
    if (n == 1) { return 1; }

    long long num = 0;
    long long num2 = 1;

    for (int i = 2; i <= n; ++i) {
        long long temp = num + num2;
        num = num2;
        num2 = temp;
    }

    return num2;
}