#include <iostream>
#include <signal.h>
#include <unistd.h>

void func_sigint(int val) {
    std::cout << "sigint capture\n";
    sleep(1);
    signal(val, SIG_DFL);
    std::cout << "sigint restore default\n";
}

int main() {
    sigset_t new_make, old_make;  // 信号集结构体
    sigemptyset(&new_make);       // 清空信号集
    sigaddset(&new_make, SIGINT); // 设置SIGINT信号

    signal(SIGINT, func_sigint);

    // 设置信号集，保存原信号集
    if (sigprocmask(SIG_BLOCK, &new_make, &old_make) == -1) {
        perror("20, if (sigprocmask(SIG_BLOCK, &new_make, &old_make) == -1)");
        exit(1);
    }

    // 测试信号是否被阻塞
    if (sigismember(&new_make, SIGINT) == 1) {
        std::cout << "sigint signal obstruct\n";
    }

    sleep(11);

    if (sigprocmask(SIG_SETMASK, &old_make, nullptr) == -1) { // 恢复原始信号集
        perror("31, if (sigprocmask(SIGINT, &old_make, nullptr) == -1) {");
        exit(1);
    }

    std::cout << "sigint signal restore\n";

    return 0;
}