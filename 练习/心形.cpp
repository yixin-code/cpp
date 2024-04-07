#include <iostream>

int main()
{
    std::cout << "   * *       * *\n";
    std::cout << "  * * *     * * *\n";
    std::cout << " * * * *   * * * *\n";

    for (int i = 1; i <= 10; ++i)
    {
        for (int k = 1; k < i; ++k)
        {
            std::cout << " ";
        }
        for (int j = 10; j >= i; --j)
        {
            std::cout << "* ";
        }
        std::cout << "\n";
    }

    return 0;
}