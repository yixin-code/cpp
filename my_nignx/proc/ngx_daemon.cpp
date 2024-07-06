#include "ngx_func.h"
#include <fcntl.h>
#include <sys/stat.h>
#include "ngx_global.h"
#include <unistd.h>
#include "ngx_macro.h"

// 子进程返回 0 父进程返回 1 失败返回 -1
int ngx_daemon(void) {
    switch (fork()) {
    case -1: {
        ngx_log_core(NGX_LOG_EMERG, errno, "ngx_daemon fork fail");
        return -1;
    }
    case 0: { // 子进程
        break;
    }
    default: { // 父进程
        return 1;
    }
    }

    ngx_ppid    = ngx_pid; // ngx_pid 为当前子进程的父进程的pid
    ngx_pid     = getpid(); // 当前子进程的pid

    if (setsid() == -1) {
        ngx_log_core(NGX_LOG_EMERG, errno, "ngx_daemon setsig fail");
        return -1;
    }

    umask(0); // 解除文件权限限制

    int rw_fd = 0;
    if ((rw_fd = open("/dev/null", O_RDWR)) == -1) {
        ngx_log_core(NGX_LOG_EMERG, errno, "ngx_daemon open /dev/null fail");
        return -1;
    }

    if (dup2(rw_fd, STDIN_FILENO) == -1) {
        ngx_log_core(NGX_LOG_EMERG, errno, "ngx_daemon dup2 stdin fail");
        return -1;
    }

    if (dup2(rw_fd, STDOUT_FILENO) == -1) {
        ngx_log_core(NGX_LOG_EMERG, errno, "ngx_daemon dup2 stdout fail");
        return -1;
    }

    if (rw_fd > STDERR_FILENO) {
        close(rw_fd);
    }

    return 0;
}