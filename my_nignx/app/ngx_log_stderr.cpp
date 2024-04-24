#include <iostream>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include "ngx_func.h"
#include "ngx_macro.h"

// 紧急信息直接显示到屏幕
void ngx_log_stderr(int log_grade, const char* format, ...) {
    u_char err_str[MAX_ERR_INFO_LEN] = {0}; // 错误信息字符串
    u_char *p_cur = err_str; // 错误信息指针当前位置
    u_char *p_end = err_str + MAX_ERR_INFO_LEN; // 错误信息字符串最后\0的位置

    p_cur = NGX_MEMCPY_RET_CUR(err_str, "nginx: ", strlen("nginx: ")); // p_cur 指向当前可写入位置

    va_list ap;
    va_start(ap, format);

    p_cur = format_printf(p_cur, p_end, format, ap);

    va_end(ap);

    if (log_grade) { // 处理日志级别非最高0
        p_cur = display_errno_info(p_cur, p_end, log_grade);
    }

    if (p_cur >= p_end) { // p_end \0
        p_cur = p_end - 1;
    }
    *(p_cur++) = '\0';

    write(STDERR_FILENO, err_str, p_cur - err_str);

    return;
}