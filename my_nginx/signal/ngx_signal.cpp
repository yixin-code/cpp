#include "ngx_func.h"
#include "signal.h"
#include <string.h>
#include "ngx_macro.h"
#include "ngx_global.h"

struct ngx_signal_t {
    int m_signo; // 信号值
    const char *m_sig_name; // 信号名
    // void (*m_handler)(int signo); // 信号处理函数指针
    void (*m_handler)(int signo, siginfo_t *p_siginfo, void *p_context); // 信号处理函数指针
};

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

// static void sig_handler(int signo) {
//     std::cout << "收到信号：" << signo << std::endl;
// }

static void sig_handler(int signo, siginfo_t *p_siginfo, void *p_context) {
    ngx_signal_t    *p_sig_t    = nullptr;
    char            *p_action   = nullptr; // 记录动作以便写入日志

    for (p_sig_t = arr_signal; p_sig_t->m_signo != 0; ++p_sig_t) {
        if (p_sig_t->m_signo == signo) { // 接收到信号退出循环后续处理
            break;
        }
    }

    p_action = (char*)"no action";

    if (g_process_flag == NGX_PROCESS_FLAG_MASTER) { // master进程中的信号处理
        switch (signo) {
        case SIGCHLD: {
            g_worker_process_state = true;  // worker进程状态发生改变，记录以便为后续重启一个新的worker进程而准备
            break;
        }
        default: {
            break;
        }
        }
    } else if (g_process_flag == NGX_PROCESS_FLAG_WORKER) { // worker进程中的信号处理

    } else { // 非master进程 非worker进程 信号处理

    }

    if (p_siginfo && p_siginfo->si_pid) { // si_pid 发出信号的进程pid
        ngx_log_core(NGX_LOG_NOTICE, 0, "signo: %d(%s) received from %P, %s",signo, p_sig_t->m_sig_name, p_siginfo->si_pid, p_action);
    }

    if (signo == SIGCHLD) {

    }
}

// 注册捕捉函数
int ngx_init_signal() {
    ngx_signal_t *p_sig_t = nullptr;
    struct sigaction sa;

    for (p_sig_t = arr_signal; p_sig_t->m_signo != 0; ++p_sig_t) {
        memset(&sa, 0, sizeof(struct sigaction));

        if (p_sig_t->m_handler != nullptr) {
            // sa.sa_handler = p_sig_t->m_handler;
            // sa.sa_flags = 0;
            sa.sa_sigaction = p_sig_t->m_handler;
            sa.sa_flags = SA_SIGINFO;
        } else {
            // sa.sa_sigaction = SIG_IGN; // error
            sa.sa_handler = SIG_IGN; // 忽略
        }

        sigemptyset(&sa.sa_mask);

        if (sigaction(p_sig_t->m_signo, &sa, nullptr) == -1) {
            ngx_log_core(NGX_LOG_EMERG, errno, "sigaction[%s] failed", p_sig_t->m_sig_name);
            return -1;
        }
    }

    return 0;
}