#include <iostream>
#include <sys/time.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <fcntl.h>
#include "ngx_func.h"
#include "ngx_macro.h"
#include "ngx_conf.h"
#include "ngx_global.h"

Log_t log_t; // 日志类型，文件描述后续关闭

static u_char log_level[][20] {
    "stderr", // 0 控制台错误
    "emerg",  // 1 紧急
    "alert",  // 2 警戒
    "crit",   // 3 严重
    "error",  // 4 错误
    "warn",   // 5 警告
    "notice", // 6 注意
    "info",   // 7 信息
    "debug",  // 8 调试
};

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
        // std::cout << p_log_name << std::endl;
        ngx_log_stderr(errno, "[alert] open error %s", p_log_name);
        log_t.m_fd = STDERR_FILENO; // 文件描述符定位到标准错误
    }
    return;
}

// 日志核心文件
    // 日志写入文件
void ngx_log_core(int level, int error_num, const char* format, ...) {
    u_char str_log_buf[MAX_ERR_INFO_LEN] = {0};
    u_char *p_end = str_log_buf + MAX_ERR_INFO_LEN - 1; // 指向log_buf结尾
    u_char *p_cur = str_log_buf;

    timeval *p_tv = nullptr;
    gettimeofday(p_tv, nullptr); // 得到当前时间距1970-1-1的秒数和过去的微妙数
    tm t;
    memset(&t, 0, sizeof(t));
    localtime_r(&(p_tv->tv_sec), &t); // 返回本地时间 使用tm结构表示
    // u_char str_cur_time[20] = {0};
    p_cur = format_sprintf(p_cur, p_end, "%4d-%02d-%02d %02d:%02d:%02d",
        t.tm_year, t.tm_mon, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec);
    p_cur = format_sprintf(p_cur, p_end, " [%s] ", log_level[level]);
    p_cur = format_sprintf(p_cur, p_end, "%P: ", ngx_pid);

    va_list ap;
    va_start(ap, format);
    p_cur = format_printf(p_cur, p_end, format, ap);
    va_end(ap);

    if (error_num) {
        p_cur = display_errno_info(p_cur, p_end, error_num);
    }

    // 位置不够 强行插入换行符
    if (p_cur >= p_end) {
        p_cur = p_end - 1; // 最后一个位置需要存\0
    }
    *(p_cur++) = '\n';

    while (true) {
        if (level > log_t.m_log_level) { // 如果level大于配置文件中的设置不进行处理
            break;
        }

        ssize_t count = write(log_t.m_fd, str_log_buf, p_cur - str_log_buf); // 不写\0
        if (count == -1) {
            if (errno == ENOSPC) { // 磁盘空间不足
                perror("磁盘空间不足");
                exit(1);
            } else {
                write(STDERR_FILENO, str_log_buf, p_cur - str_log_buf);
            } // if else
        } // if
        break;
    } // while
    return;
}