#include <iostream>

int main()
{
    for (int i = 1; i <= 5; ++i)
    {
        for (int j = 5; j > i; --j) {
            std::cout << ' ';
        }
        for (int k = i; k > 0; --k)
        {
            std::cout << "* ";
        }
        std::cout << '\n';
    }

    for (int i = 1; i <= 4; ++i) {
        for (int k = i; k > 0; --k)
        {
            std::cout << " ";
        }
        for (int j = 5; j > i; --j) {
            std::cout << "* ";
        }
        std::cout << '\n';
    }

    return 0;
}