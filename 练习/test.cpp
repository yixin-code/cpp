#include <iostream>

int main(int argc, char *argv[]) {
    int a = 1;
    int b = 2;
    int c = 3;

    (a = b) = c;

    std::cout << a << b << c << "\n";

    return 0;
}