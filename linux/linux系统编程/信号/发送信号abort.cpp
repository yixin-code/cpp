#include <iostream>
#include <signal.h>
#include <unistd.h>

void catch_sig(int signo) {
    std::cout << "catch signal: " << signo << std::endl;
    std::cout << "abort success" << std::endl;
    abort();
}

int main(int argc, char *argv[]) {
    alarm(5); // 5秒后发送闹钟信号

    struct sigaction sa;

    sa.sa_handler  = catch_sig;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    sigaction(SIGALRM, &sa, nullptr);

    while (true) {
        std::cout << "send message..." << std::endl;
        sleep(1);
    }
    
    return 0;
}