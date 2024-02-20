#include <iostream>

#define func(x) ((x) * (x) + 11)
#define print() do { \
printf("hello "); \
printf("world\n"); \
}while(0)

int main()
{
    int num = func(3);
    std::cout << num << "\n"; // 20

    int i = 2;
    num = func(++i);
    std::cout << num << "\n"; // 4 * 4 + 11 = 27

    print(); // hello world

    return 0;
}