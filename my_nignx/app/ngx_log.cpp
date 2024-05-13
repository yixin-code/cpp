#include <iostream>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include "ngx_func.h"
#include "ngx_macro.h"
#include "ngx_conf.h"
#include "ngx_global.h"

Log_t log_t; // 日志类型，文件描述后续关闭

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

// 打开日志文件
    // 将日志等级和文件路径赋予默认值
void ngx_log_init() {
    CConfig *p_config = CConfig::get_instance();
    u_char *p_log_name = (u_char*)p_config->get_string("Log");
    if (p_log_name == nullptr) {
        p_log_name = (u_char*)LOG_NAME_PATH; // 给初始路径
    }
    log_t.m_log_level = p_config->get_int_default("LogLevel", NGX_LOG_NOTICE); // 给初始日志等级

    // log_t.m_fd = open((const char*)p_log_name, O_WRONLY | O_APPEND, 0644);
    log_t.m_fd = open((const char*)p_log_name, O_WRONLY | O_APPEND | O_CREAT, 0644);
    if (log_t.m_fd == -1) {
        ngx_log_stderr(errno, "[alert] 73 open error %s", p_log_name);
        log_t.m_fd = STDERR_FILENO; // 文件描述符定位到标准错误
    }
    return;
}

// 日志核心文件
    // 日志写入文件
void ngx_log_core(int level, int error_num, const char* format, ...) {
    u_char log_buf[MAX_ERR_INFO_LEN] = {0};
}