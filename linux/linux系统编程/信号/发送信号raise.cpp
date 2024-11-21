#include <iostream>
#include <signal.h>

void catch_sig(int sig) {
    std::cout << "catch sig:" << sig << std::endl;
    raise(SIGINT); // 向父进程发送sigint信号
}

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        while (true) {
            std::cout << "child process" << std::endl;
            sleep(1);
        }
    } else {
        struct sigaction sa;

        sa.sa_flags = 0;
        sa.sa_handler = catch_sig;
        sigemptyset(&sa.sa_mask);

        sigaction(SIGALRM, &sa, nullptr); // 捕捉闹钟信号

        alarm(5); // 5秒后发送sigalrm信号

        while(true) {
            std::cout << "parent process" << std::endl;
            sleep(1);
        }
    }

    return 0;
}