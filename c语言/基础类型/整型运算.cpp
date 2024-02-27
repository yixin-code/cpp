#include <iostream>

int main()
{
    // 0000 0000 0000 0000 0000 0000 1001 1001
    // 000 0000 0000 0000 0000 0000 1001 1001 0
    // 0000 0000 0000 0000 0000 0000 1001 1001
    unsigned char num = 0x99 << 1 >> 1; // 99
    printf("%x\n", num);

    // 1001 1001
    // 0011 0010
    // 0001 1001
    unsigned char num2 = 0x99 << 1;
    printf("%x\n", num2); // 32
    num2 = num2 >> 1;
    printf("%x\n", num2); // 19

    return 0;
}