#include <iostream>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "ngx_func.h"
#include "ngx_macro.h"

// 格式化读写
void ngx_log_stderr(int error_num, const char* format, ...) {
    u_char err_str[MAX_ERR_INFO_LEN] = {0}; // 错误信息字符串
    u_char *p_cur = err_str; // 错误信息指针当前位置
    u_char *p_end = err_str + MAX_ERR_INFO_LEN; // 错误信息字符串最后\0的位置

    p_cur = NGX_MEMCPY_RET_CUR(err_str, "nginx: ", strlen("nginx: ")); // p_cur 指向当前可写入位置

    va_list ap;
    va_start(ap, format);

    p_cur = format_printf(p_cur, p_end, format, ap);

    va_end(ap);

    if (error_num) { // 处理错误码
        p_cur = display_errno_info(p_cur, p_end, error_num);
    }

    if (p_cur >= p_end) { // p_end \0
        p_cur = p_end - 1;
    }
    *(p_cur++) = '\0';

    write(STDERR_FILENO, err_str, p_cur - err_str);

    return;
}