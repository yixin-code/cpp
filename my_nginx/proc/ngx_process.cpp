#include <signal.h>
#include "ngx_conf.h"
#include "ngx_func.h"
#include "ngx_macro.h"
#include "ngx_global.h"

static const char master_process[] = "master process";

// 创建进程数量
static void create_process_number(int process_number);
// 创建进程
static int  create_process(int number, const char* process_name);
// 子进程
static void sub_process(int number, const char* process_name);
// 进程初始化
static void process_init(int number);

// 创建worker子进程
void ngx_master_process() {
    // 该函数执行期间不会被信号干扰 创建子进程时建议写法 子进程创建完毕清空屏蔽信号
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
    int limit = 0;

    limit += sizeof(master_process);
    limit += g_argv_len;

    if (limit < 1024) {
        char title_name[1024] = {0};

        strcat(title_name, master_process);

        for (int i = 0; i < g_argc; ++i) {
            strcat(title_name, " ");
            strcat(title_name, g_p_argv[i]);
        }

        set_process_title(title_name);
    }

    // 创建子进程子进程创建后将信号屏蔽清空(并不表示当前信号集中被屏蔽的信号清空)
    CConfig*    p_config        = CConfig::get_instance();
    int         process_number  = p_config->get_int_default("workerprocesses", 1); // 默认创建一个子进程
    create_process_number(process_number);
    sigemptyset(&sigset); // 为了后续设置不屏蔽任何信号

    while (true) { // 父进程
        // std::cout << "parent process loop\n";
        // sleep(10);
        sigsuspend(&sigset); // 会临时替换当前的信号屏蔽，使进程在此挂起。待接收到信号后，恢复原信号屏蔽，进程继续执行
    }

    return;
}

// 创建进程数量
void create_process_number(int process_number) {
    for (int i = 1; i <= process_number; ++i) {
        create_process(i, "worker process");
    }

    return;
}

// 创建进程
int create_process(int number, const char* process_name) {
    pid_t pid = fork();
    switch (pid) {
    case -1: { // fail
        ngx_log_core(NGX_LOG_ALERT, errno, "create_process fork fail, number = %d", number);
        return -1;
    }
    case 0: { // 子进程进入循环
        g_ppid    = g_pid;
        g_pid     = getpid();
        sub_process(number, process_name);
        break;
    }
    default: // 父进程直接退出
        break;
    }

    return pid;
}

// 子进程
void sub_process(int number, const char* process_name) {
    g_process_flag = NGX_PROCESS_FLAG_WORKER;

    process_init(number);
    set_process_title(process_name);
    ngx_log_core(NGX_LOG_NOTICE, 0, "%s %P 已启动", process_name, g_pid);

    while (true) {
        std::cout << "subprocess loop\n";
        sleep(10);
    }

    return;
}

// 进程初始化
void process_init(int number) {
    sigset_t sigset;
    sigemptyset(&sigset);

    if (sigprocmask(SIG_SETMASK, &sigset, nullptr) == -1) {
        ngx_log_core(NGX_LOG_ALERT, errno, "process_init sigprocmask fail, number = %d", number);
    }

    return;
}