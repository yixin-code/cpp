#include "ngx_func.h"
#include "ngx_macro.h"
#include <stdint.h>
#include <stdarg.h>

// 显示数字
static u_char* display_num(u_char* p_cur, u_char* p_end, uint64_t ui64, u_char zero, uintptr_t hex, uintptr_t width) {
    u_char  temp_str[MAX_INT64_LEN]     = {0}; // 临时存放数据数组
    u_char  *p_temp_cur                 = temp_str + MAX_INT64_LEN; // 初始指向temp_str结尾

    uint32_t ui32                       = 0; // 32位无符号整数
    size_t char_len                     = 0; // 字符长度

    u_char hex_buf[]                    = "0123456789abcdef";
    u_char HEX_BUF[]                    = "0123456789ABCDEF";


    if (hex == 0) { // 非十六进制
        if (ui64 <= (uint64_t)MAX_UINT32) {
            ui32 = (uint32_t)ui64;
            do { // 12345 -> '1''2''3''4''5'
                *(--p_temp_cur) = (u_char)(ui32 % 10 + '0');
            } while (ui32 /= 10);
        } else {
            do { // 12345 -> '1''2''3''4''5'
                *(--p_temp_cur) = (u_char)(ui64 % 10 + '0');
            } while (ui64 /= 10);
        }
    } else if (hex == 1) {
        do {
            // 12345 十六进制1e240 二进制11110001001000000
            // 0xf 二进制1111
            *(--p_temp_cur) = hex_buf[(uint32_t)(ui64 & 0xf)]; // 一个十六进制4位，与的结果对应数组下标
        } while (ui64 >>= 4); // 一次取最后4位
    } else if (hex == 2) {
        do {
            // 12345 十六进制1e240 二进制11110001001000000
            // 0xf 二进制1111
            *(--p_temp_cur) = HEX_BUF[(uint32_t)(ui64 & 0xf)]; // 一个十六进制4位，与的结果对应数组下标
        } while (ui64 >>= 4); // 一次取最后4位
    }

    char_len = (temp_str + MAX_INT64_LEN) - p_temp_cur;

    while (char_len++ < width && p_cur < p_end) { // 宽度大于实际字符长度时填充
        *(p_cur++) = zero;
    }

    char_len = (temp_str + MAX_INT64_LEN) - p_temp_cur;

    
}

// 格式化输出
u_char* format_printf(u_char* p_cur, u_char* p_end, const char* format, va_list ap) {
    u_char      zero        = 0;        // 处理填充0或空格
    uintptr_t   width       = 0;        // 宽度 2d -> 2

    uintptr_t   sign        = 0;        // 有无符号，0无符号，1有符号
    uintptr_t   hex         = 0;        // 十六进制，0不是十六进制，1小写，2大写

    int64_t     i64         = 0;        // 有符号整数
    u_int64_t   ui64        = 0;        // 无有符号数

    u_char      *p_temp_str = nullptr;  // 临时字符串
    int64_t     temp_num    = 0;        // 临时整数

    uintptr_t   float_width = 0;        // 浮点数.10f -> 2
    double      float_num   = 0;        // 浮点数
    u_int64_t   fraction    = 0;        // 小数部分
    uintptr_t   carry       = 0;        // 进位

    while (*format && p_cur < p_end) {
        if (*format == '%') {
            zero = (u_char)(*(++format) == '0' ? '0' : ' '); // %后是0, zero = '0'否则zero = ' '

            width = 0;
            while (*format >= '0' && *format <= '9') { // 循环一次加一位, 宽度只有一位不加，宽度前填充0不加
                width = width * 10 + (*(format++) - '0'); // 需要先计算在自增，包含填充的0
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
                        float_width = float_width * 10 + (*(format++) - '0');
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
                p_temp_str = (u_char*)va_arg(ap, u_char*);
                while (*p_temp_str && p_end > p_cur) {
                    *p_cur = *p_temp_str;
                }
                ++format;
                continue;
            }
            case 'P': { // PID
                i64 = (int16_t)va_arg(ap, pid_t);
                sign = 1;
                break; // 有负数同样需要后续处理
            }
            case 'f': {
                float_num = va_arg(ap, double);
                if (float_num < 0) { // 对负数进行处理
                    *(p_cur++) = '-';
                    float_num = -float_num;
                }

                ui64 = (int64_t)float_num; // 拿到小数整数部分
                fraction = 0;

                if (float_width) {
                    carry = 1;

                    temp_num = float_width;
                    while (temp_num--) {
                        carry *= 10;
                    }

                    fraction = (int64_t)((float_num - (double)ui64) * carry + 0.5); // (1.123 - 1) * 100 + 0.5 -> 12.8 -> 12

                    if (fraction == carry) { // (1.998 - 1) * 100 + 0.5 -> 100.3 -> 100 进位去除小数部分
                        ++ui64;
                        fraction = 0;
                    }
                }

                p_cur = display_num(p_cur, p_end, ui64, zero, 0, width); // 显示数字
            } // case 'f': {
            } // switch (*format) {
        } // if (*format == '%') {
    } // while (*format && p_cur < p_end) {
}