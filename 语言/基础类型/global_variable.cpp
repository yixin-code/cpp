#include <iostream>
#include <math.h> // pow

int g_num = pow(2, 3); // 2的3次幂

int main(int argc, char *argv[]) {
    std::cout << "g_num: " << g_num << '\n';

    return 0;
}