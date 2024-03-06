#include <iostream>

void hanoi(int n, char a, char b,char c);

int main() {
    hanoi(2, 'a', 'b', 'c');

    return 0;
}

void hanoi(int n, char a, char b,char c) { // a b c 三个柱子
    if (n == 1) {
        std::cout << a << "->" << c << std::endl;
        return;
    }

    hanoi(n - 1, a, c, b); // a - > b
    std::cout << a << "->" << c << std::endl; // a -> c
    hanoi(n - 1, b, a, c); // b -> c
}