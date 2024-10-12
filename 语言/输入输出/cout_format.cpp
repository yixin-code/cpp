#include <iostream>

int main(int argc, char *argv[]) {
    double num = 3.14159265358979323846;

    std::cout << "num: ";

    std::cout.precision(3); // 小数包含整数
    std::cout.fill('0');
    std::cout.width(10);

    std::cout << num << '\n'; // 0000003.14

    return 0;
}