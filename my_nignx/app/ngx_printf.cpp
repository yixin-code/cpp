#include "ngx_func.h"
#include <stdint.h>

// 格式化输出
u_char* format_printf(u_char* p_cur, u_char* p_end, const char* format, va_list ap) {
    u_char      zero = 0;   // 处理填充0或空格
    uintptr_t   with = 0;   // 处理宽度

    while (*format && p_cur < p_end) {
        zero = (u_char)(*(++format) == '0' ? '0' : ' '); // %后是0, zero = '0'否则zero = ' '

        with = 0;
        while (*format >= '0' && *format <= '9') { // 循环一次加一位, 宽度只有一位不加，宽度前填充0不加
            with = with * 10 + (*(++format) - '0');
        }
    }
}