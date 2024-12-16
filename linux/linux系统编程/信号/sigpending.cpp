#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void sig_handler(int signo) {
    std::cout << "signo: " << signo << std::endl;
}

void print_pend(const sigset_t &pend_sig) {
    for (int i = 1; i <= 31; ++i) {
        sigismember(&pend_sig, i) ? std::cout << '1' : std::cout << '0';
    }
}

int main(int argc, char *argv[]) {
    pid_t pid = fork();
    switch (pid) {
    case -1: {
        perror("fork");
        exit(1);
    }
    case 0: {
        sigset_t            old_sig;
        sigset_t            pend_sig;
        struct sigaction    sa;

        sa.sa_handler = sig_handler;
        sa.sa_flags   = 0;

        // 设置临时信号集
        sigemptyset(&sa.sa_mask);

        sigaddset(&sa.sa_mask, 1);
        sigaddset(&sa.sa_mask, 2);
        sigaddset(&sa.sa_mask, 3);

        if (sigprocmask(SIG_BLOCK, &sa.sa_mask, &old_sig) == -1) {
            perror("sigprocmask fail");
            exit(1);
        }

        for (int i = 1; i < 10; ++i) {
            sigpending(&pend_sig);
            print_pend(pend_sig);
            sleep(1);
            std::cout << std::endl;
        }

        std::cout << "child end" << std::endl;

        sigprocmask(SIG_SETMASK, &old_sig, nullptr);
    }
    default: {
        sleep(2);
        kill(pid, 1);
        sleep(2);
        kill(pid, 2);
        sleep(2);
        kill(pid, 3);

        std::cout << "parent end" << std::endl;

        waitpid(-1, nullptr, 0);
    }
    }

    return 0;
}