#include "ngx_func.h"
#include <ctype.h>
#include <string.h>

// 清除字符串前空白字符
void left_space(char *str) {
    char *temp = str;
    while (isspace(*temp)) {
        ++temp;
    }

    while (*temp != '\0') {
        *str = *temp;
        ++str;
        ++temp;
    }

    *str = '\0';
}

// 清除字符串后空白字符
void right_space(char *str) {
    int temp_size = strlen(str);
    while (isspace(str[temp_size - 1]) && temp_size > 0) {
        str[--temp_size] = 0;
    }
}