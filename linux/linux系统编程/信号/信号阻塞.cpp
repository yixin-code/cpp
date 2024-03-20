#include <iostream>
#include <signal.h>
#include <unistd.h>

void func_sigusr1(int sig) {
    int limit = 0;
    while (limit < 10) {
        std::cout << "###### " << limit << "\n";
        ++limit;
        sleep(1);
    }
    std::cout << "#####################################\n";
}

void func_sigusr2(int sig) {
    int limit = 0;
    while (limit < 10) {
        std::cout << "@@@@@@ " << limit << "\n";
        ++limit;
        sleep(1);
    }
    std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
}

int main() {
    if (signal(SIGUSR1, func_sigusr1) == SIG_ERR) {
        perror("25, signal");
        exit(1);
    }

    if (signal(SIGUSR2, func_sigusr2) == SIG_ERR) {
        perror("30, signal");
        exit(1);
    }

    while (true);

    return 0;
}