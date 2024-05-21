#include <iostream>
#include <signal.h>
#include <unistd.h>

void catch_sig(int signo) {
    std::cout << "receive " << signo << std::endl;
}

int main(int argc, char *argv[]) {
    struct sigaction sa;
    // sa.__sigaction_handler.sa_handler -> void(*)(int) -> sa.sa_flags = 0
        // 还可以赋值SIG_DFL默认处理 SIG_IGN忽略
    // sa.__sigaction_handler.sa_sigaction -> void(*)(int, siginfo_t*, void*) -> sa.sa_flags = SA_SIGINFO
    // sa.sa_mask 临时信号集 sigemptyset(&sa.sa_mask);

    sa.sa_handler = catch_sig;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGINT, &sa, nullptr); // 信号 新动作 原动作

    while (true) {
        std::cout << "sleep ..." << std::endl;
        sleep(1);
    }

    return 0;
}