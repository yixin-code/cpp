#include <signal.h>
#include "ngx_func.h"
#include "ngx_macro.h"

// 创建worker子进程
void ngx_master_process() {
    // 该函数执行期间不会被信号干扰
    sigset_t    sigset; // 信号集

    sigemptyset(&sigset); // 清空信号集

    sigaddset(&sigset, SIGCHLD); // 子进程状态改变
    sigaddset(&sigset, SIGALRM); // 定时器超时
    sigaddset(&sigset, SIGIO); // 异步io
    sigaddset(&sigset, SIGINT); // 终端中断 ctrl+c
    sigaddset(&sigset, SIGHUP); // 连接断开 关闭终端
    sigaddset(&sigset, SIGUSR1); // 用户自定义信号
    sigaddset(&sigset, SIGUSR2); // 用户自定义信号
    sigaddset(&sigset, SIGWINCH); // 终端窗口大小改变
    sigaddset(&sigset, SIGTERM); // 终止 kill -9 xxx
    sigaddset(&sigset, SIGQUIT); // 终端退出 ctrl+'\'

    if (sigprocmask(SIG_BLOCK, &sigset, nullptr) == -1) {
        ngx_log_core(NGX_LOG_ALERT, errno, "ngx_master_process sigprocmask fail");
    }

    // 设置主进程标题
}