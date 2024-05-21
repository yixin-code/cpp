#include "ngx_func.h"
#include "signal.h"
#include <string.h>
#include "ngx_macro.h"

struct ngx_signal_t {
    int m_signo; // 信号值
    const char *m_sig_name; // 信号名
    void (*m_handler)(int signo); // 信号处理函数指针
};

static void sig_handler(int signo) {
    std::cout << "收到信号：" << signo << std::endl;
}

ngx_signal_t arr_signal[] = {
    {SIGHUP,    "SIGHUP",    sig_handler}, // 关闭终端
    {SIGINT,    "SIGINT",    sig_handler}, // ctrl c
    {SIGTERM,   "SIGTERM",   sig_handler}, // kill杀死进程
    {SIGCHLD,   "SIGCHLD",   sig_handler}, // 子进程退出
    {SIGQUIT,   "SIGQUIT",   sig_handler}, // 'ctrl \'
    {SIGIO,     "SIGIO",     sig_handler}, // 异步通知I\O事件
    {SIGSYS,    "SIGSYS",    nullptr    }, // 无效系统调用
    {0,         nullptr,     nullptr    }, // 信号从1开始，0作为特殊标志
};

// 注册捕捉函数
int ngx_init_signal() {
    ngx_signal_t *p_sig_t = nullptr;
    struct sigaction sa;

    for (p_sig_t = arr_signal; p_sig_t->m_signo != 0; ++p_sig_t) {
        memset(&sa, 0, sizeof(struct sigaction));

        if (p_sig_t->m_handler != nullptr) {
            sa.sa_handler = p_sig_t->m_handler;
            sa.sa_flags = 0;
        } else {
            sa.sa_handler = SIG_IGN; // 忽略
        }

        sigemptyset(&(sa.sa_mask));

        if (sigaction(p_sig_t->m_signo, &sa, nullptr) == -1) {
            ngx_log_core(NGX_LOG_EMERG, errno, "sigaction[%s] failed", p_sig_t->m_sig_name);
            return -1;
        }
    }

    return 0;
}