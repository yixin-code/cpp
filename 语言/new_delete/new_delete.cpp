#include <iostream>

int main(int argc, char *argv[]) {
    int *p = new int[11]{0};

    for (int i = 0; i < 11; ++i) {
        std::cout << p[i] << " "; // 11个0
    }
    std::cout << std::endl;

    int *p2 = new int[11];

    for (int i = 0; i < 11; ++i) {
        std::cout << p2[i] << " "; // 11个0
    }
    std::cout << std::endl;

    delete[] p;
    // delete[] p; 非空连续释放会崩溃
    p = nullptr;

    delete[] p; // 空指针可以连续释放

    return 0;
}