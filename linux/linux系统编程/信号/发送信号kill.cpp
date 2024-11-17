#include <iostream>
#include <unistd.h>
#include <signal.h>

int main() {
    pid_t pid;
    pid = fork();
    // 失败返回一个负数，等于0子进程pid，大于0为父进程
    if (pid < 0) {
        perror("7, fork error");
        exit(1);
    } else if (pid == 0) { // 子进程
        while (true) {
            std::cout << "son wait...\n";
            sleep(1);
        }
    } else { // 父进程
        std::cout << "son pid: " << pid << "\n";
        sleep(3);
        kill(pid, SIGINT); // 发送信号给子进程
        while (true) {
            std::cout << "father wait...\n";
            sleep(1);
        }
    }

    std::cout << "main end\n";

    return 0;
}