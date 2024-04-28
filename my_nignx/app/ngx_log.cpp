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

// 显示错误编号和信息
u_char* display_errno_info(u_char* p_cur, u_char* p_end, int err_num) {
    char *p_error_info = strerror(err_num);
    size_t error_info_len = strlen(p_error_info);

    char temp_buf[10] = {0};
    sprintf(temp_buf, " (%d: ", err_num);
    size_t temp_buf_len = strlen(temp_buf);

    char temp_buf2[] = ") ";
    size_t temp_buf2_len = strlen(temp_buf2);

    if ((p_cur + error_info_len + temp_buf_len + temp_buf2_len) < p_end) {
        p_cur = NGX_MEMCPY_RET_CUR(p_cur, temp_buf, temp_buf_len);
        p_cur = NGX_MEMCPY_RET_CUR(p_cur, p_error_info, error_info_len);
        p_cur = NGX_MEMCPY_RET_CUR(p_cur, temp_buf2, temp_buf2_len);
    }

    return p_cur;
}
