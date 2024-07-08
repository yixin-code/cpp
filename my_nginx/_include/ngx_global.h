#ifndef __NGX_GLOBAL_H__
#define __NGX_GLOBAL_H__

#include <string.h>
#include <iostream>

struct ConfigItem {
    char m_item_name[40]; // 配置名
    char m_item_content[400]; // 配置内容

    ConfigItem() {
        memset(this->m_item_content, 0, sizeof(this->m_item_content));
        memset(this->m_item_name, 0, sizeof(this->m_item_name));
    }
};

struct Log_t {
    int m_log_level; // 日志等级
    int m_fd; // 日志文件描述符
};

extern char *g_p_environ; // 环境变量
extern int  g_environ_len; // 环境变量字节数
extern int  g_argv_len; // 命令行参数字节数
extern int  g_argc; // 命令行参数个
extern char **g_p_argv; // 命令行参数
extern bool g_daemon; // 是否启动守护进程标准

extern Log_t log_t;
extern pid_t g_pid; // 当前进程pid
extern pid_t g_ppid; // 父进程pid

extern bool g_process_flag; // 进程标志
extern bool g_worker_process_state; // worker进程状态变化

#endif