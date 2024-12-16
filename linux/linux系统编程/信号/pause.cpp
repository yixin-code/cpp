#include <signal.h>
#include <iostream>
#include <unistd.h>

void alarm_handler(int signo) {
    return;
}

uint64_t yx_sleep(uint64_t sec) {
    struct sigaction sa;
    struct sigaction old_sa;

    sa.sa_handler = alarm_handler;
    sa.sa_flags   = 0;

    sigemptyset(&sa.sa_mask);

    sigaction(SIGALRM, &sa, &old_sa);

    alarm(sec);
    pause();

    int temp = alarm(0); // 取消闹钟，返回上一个闹钟剩余时间

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