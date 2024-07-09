#include <iostream>
#include <unistd.h>
#include "ngx_conf.h"
#include "ngx_func.h"
#include "ngx_global.h"
#include "ngx_macro.h"

static void free_resource();

char    *g_p_environ            = nullptr; // 环境变量
int     g_environ_len           = 0; // 环境变量字节数
int     g_argv_len              = 0; // 命令行参数字节数
int     g_argc                  = 0; // 命令行参数个
bool    g_daemon                = false; // 是否启动守护进程标准
char    **g_p_argv              = nullptr; // 命令行参数
pid_t   g_pid                   = 0; // 当前进程pid
pid_t   g_ppid                  = 0; // 当前父进程pid
bool    g_process_flag          = NGX_PROCESS_FLAG_MASTER; // 进程标志
bool    g_worker_process_state  = false; // worker进程状态变化

int main(int argc, char *argv[]) {
    int ret_code    = 0; // 退出代码0表示正常退出
    g_pid           = getpid();
    g_ppid          = getppid();
    g_p_argv        = argv;
    g_argc          = argc;
    log_t.m_fd      = -1;
    g_process_flag  = NGX_PROCESS_FLAG_MASTER;

    CConfig *p_config = CConfig::get_instance();
    if (p_config->load_config("./nginx.conf") == false) {
        ngx_log_stderr(0, "配置文件[%s]载入失败", "nginx.conf");
        ret_code = 2; // No such file or directory 文件不存在
        goto fly;
    }

    ngx_log_init(); // 打开初始化日志

    if (ngx_init_signal() == -1) { // 初始化信号
        ret_code = 1;
        goto fly;
    }

    save_environ_arg(); // 保存环境变量

    if (strcmp(p_config->get_string("daemon"), "true") == 0) { // 创建守护进程， 让守护进程变成后续创建进程的父进程
        int ret = ngx_daemon();

        if (ret == -1) { // 守护进程创建失败
            ret_code = 1;
            goto fly;
        }

        if (ret == 1) { // 父进程  正常退出
            free_resource();
            ret_code = 0;

            return ret_code;
        }

        g_daemon = true; // 标记启动守护进程
    }

    ngx_master_process(); // 创建worker子进程
    write(STDERR_FILENO, "asdf", 4);

fly:
    free_resource();
    std::cout << "program exit\n";
    return ret_code;
}

void free_resource() {
    if (g_p_environ != nullptr) {
        delete[] g_p_environ;
        g_p_environ = nullptr;
    }

    if (log_t.m_fd != STDERR_FILENO && log_t.m_fd != -1) {
        close(log_t.m_fd);
        log_t.m_fd = -1; // 防止重复释放
    }
}