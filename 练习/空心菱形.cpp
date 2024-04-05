#include <iostream>

int main()
{
    for (int i = 1; i <= 5; ++i)
    {
        for (int j = 5; j > i; --j)
        {
            std::cout << ' ';
        }
        for (int k = 1; k <= i; ++k) {
            if (k == 1 || k == i) {
                std::cout << "* ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << '\n';
    }
    for (int i = 1; i <= 4; ++i)
    {
        for (int k = 1; k <= i; ++k) {
            std::cout << ' ';
        }
        for (int j = 4; j >= i; --j)
        {
            if (j == 4 || j == i) {
                std::cout << "* ";
            } else {
                std::cout << "  ";
            }
        }
        std::cout << '\n';
    }

    return 0;
}