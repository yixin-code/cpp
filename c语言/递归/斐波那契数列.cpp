#include <iostream>

long long fibonacci(int n);

int main() {
    std::cout << fibonacci(8) << std::endl;
    return 0;
}

long long fibonacci(int n) {
    if (n == 0) {
        return 0;
    }

    if (n == 1) {
        return 1;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}