#include <iostream>

int main()
{
    char ch = 0;
    scanf("%c", &ch); // 输入：   a
    printf("[%c]", ch); // [ ]

    // 空白字符可以匹配0个或多个
    scanf(" %c", &ch); // 输入：   a
    printf("[%c]", ch); // [a]

    return 0;
}