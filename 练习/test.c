#include <stdio.h>
#include <math.h> // pow

// int g_num = pow(2, 3); error 常量表达式中不允许使用函数调用

int main(int argc, char *argv[]) {
    printf("g_num: %d\n", pow);

    return 0;
}