#include <iostream>
#include <unistd.h>
#include <signal.h>

void alarm_func(int sig) {
    std::cout << "收到信号: " << sig << ", 执行定时任务\n";
    alarm(3); // 之后每3秒执行一次，并不是递归
}

int main() {
    signal(SIGALRM, alarm_func);
    alarm(3); // 3秒后执行

    while (true) {
        std::cout << "等待中...\n";
        sleep(1);
    }

    return 0;
}