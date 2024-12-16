#include <signal.h>
#include <iostream>
#include <unistd.h>

void alarm_handler(int signo) {
    return;
}

uint64_t yx_sleep(uint64_t sec) {
    struct sigaction sa;
    struct sigaction old_sa;
    sigset_t sigset;
    sigset_t old_sigset;

    sa.sa_handler = alarm_handler;
    sa.sa_flags   = 0;

    sigemptyset(&sa.sa_mask);

    sigaction(SIGALRM, &sa, &old_sa);

    sigemptyset(&sigset);
    sigaddset(&sigset, SIGALRM);
    sigprocmask(SIG_BLOCK, &sigset, &old_sigset);

    alarm(sec);

    sigset_t temp_sigset = old_sigset;
    sigdelset(&temp_sigset, SIGALRM);
    sigsuspend(&temp_sigset); // 临时设置信号屏蔽，等待信号到来自动恢复原屏蔽字

    int temp = alarm(0); // 取消闹钟，返回上一个闹钟剩余时间

    sigaction(SIGALRM, &old_sa, nullptr); // 先恢复动作 以防止屏蔽恢复处理动作不是想要动作
    sigprocmask(SIG_SETMASK, &old_sigset, nullptr);

    return temp;
}

int main(int argc, char *argv[]) {
    for (int i = 0; i < 5; ++i) {
        std::cout << i + 1 << "sec" << std::endl;
        yx_sleep(1);
    }

    std::cout << "end" << std::endl;

    return 0;
}