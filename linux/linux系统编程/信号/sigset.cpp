#include <iostream>
#include <unistd.h>
#include <signal.h>

void sig_handler(int sig) {
    std::cout << "receive signal: " << sig << std::endl;

    for (int i = 0; i < 10; ++i) {
        sleep(1);
        std::cout << "sleep: " << i + 1 << std::endl;
    }

    exit(0);
}

int main(int argc, char *argv[]) {
    struct sigaction sa;

    sa.sa_handler = sig_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaddset(&sa.sa_mask, SIGINT) == -1) {
        perror("sigaddset");
        exit(1);
    }

    sigset_t old_set;
    if (sigprocmask(SIG_BLOCK, &sa.sa_mask, &old_set) == -1) {
        perror("sigprocmask");
        exit(1);
    }

    sigaction(SIGINT, &sa, nullptr);

    for (int i = 0; i < 10; ++i) {
        sleep(1);
        std::cout << "sleep: " << i + 1 << std::endl;
    }

    sigprocmask(SIG_SETMASK, &old_set, nullptr);

    while (true);

    return 0;
}