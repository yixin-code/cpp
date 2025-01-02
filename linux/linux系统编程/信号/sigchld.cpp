#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void sigchld_handler(int sig) {
    int status = 0;

    waitpid(-1, &status, 0);

    if (WIFEXITED(status)) {
        std::cout << "exit status: " << WEXITSTATUS(status) << std::endl;
    }

    std::cout << "sig: " << sig << std::endl;
}

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    switch (pid) {
    case -1: {
        perror("fork fail");
        exit(1);
    }
    case 0: { // 子进程退出 向父进程发送sigchld信号
        sleep(1);
        std::cout << "child process exit" << std::endl;
        exit(0);
    }
    default: { // 父进程处理sigchld信号，回收子进程资源
        struct sigaction sa;
        struct sigaction old_sa;
        
        sa.sa_handler   = sigchld_handler;
        sa.sa_flags     = 0;
        sigemptyset(&sa.sa_mask);

        sigaction(SIGCHLD, &sa, &old_sa);

        for (int i = 0; i < 5; ++i) {
            std::cout << "parent sleep" << std::endl;
            sleep(1);
        }

        sigaction(SIGCHLD, &old_sa, nullptr);
    }
    }

    std::cout << "main end" << std::endl;

    return 0;
}