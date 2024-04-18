#include "ngx_func.h"
#include <stdint.h>
#include <stdarg.h>

// 格式化输出
u_char* format_printf(u_char* p_cur, u_char* p_end, const char* format, va_list ap) {
    u_char      zero        = 0;        // 处理填充0或空格
    uintptr_t   with        = 0;        // 处理宽度
    uintptr_t   sign        = 1;        // 有无符号，0无符号，1有符号
    uintptr_t   hex         = 0;        // 十六进制，0不是十六进制，1小写，2大写
    uintptr_t   float_with  = 0;        // 浮点数.10f
    int64_t     i64         = 0;        // 有符号整数
    u_int64_t   ui64        = 0;        // 无有符号数
    u_char      *p_str      = nullptr;  // 字符串

    while (*format && p_cur < p_end) {
        if (*format == '%') {
            zero = (u_char)(*(++format) == '0' ? '0' : ' '); // %后是0, zero = '0'否则zero = ' '

            with = 0;
            while (*format >= '0' && *format <= '9') { // 循环一次加一位, 宽度只有一位不加，宽度前填充0不加
                with = with * 10 + (*(format++) - '0'); // 需要先计算在自增，包含填充的0
            }

            while (true) {
                switch (*format) {
                case 'u': { // 无符号 %ud
                    sign = 0;
                    format++;
                    continue;
                }
                case 'x': { // 小写十六进制
                    hex = 1; // 小写 %xd
                    sign = 0;
                    format++;
                    continue;
                }
                case 'X': { // 大写十六进制
                    hex = 2; // 大写 %Xd
                    sign = 0;
                    format++;
                    continue;
                }
                case '.': { // 小数部分
                    ++format;
                    while (*format >= '0' && *format <= '9') {
                        float_with = float_with * 10 + (*(format++) - '0');
                    }
                    break;
                }
                }
                break;
            }

            switch (*format) {
            case '%': { // %%拼接到字符串中
                *(p_cur++) = '%';
                ++format;
                continue;
            }
            case 'd': { // 有无符号整数
                if (sign) {
                    i64 = (int64_t)va_arg(ap, int64_t); // 有符号
                } else {
                    ui64 = (u_int64_t)va_arg(ap, u_int64_t);
                }
                break; // 跳出switch后续还需要处理正负数
            }
            case 's': { // 字符串
                p_str = (u_char*)va_arg(ap, u_char*);
                while (*p_str && p_end > p_cur) {
                    *p_cur = *p_str;
                }
                ++format;
                continue;
            }
            case 'P': { // PID
                i64 = (int16_t)va_arg(ap, pid_t);
                sign = 1;
                break; // 有负数同样需要后续处理
            }
            } // switch
        } // if
    } // while
}