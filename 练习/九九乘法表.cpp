#include <iostream>

int main() {

    for (int i = 1; i <= 9; ++i) {
        for (int j = 1; j <= i; ++j) {
            std::cout << j << "x" << i << "=" << j * i << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}