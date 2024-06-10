#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>

void sig_catch(int sig) {
    std::cout << "sig_catch: " << pthread_self() << ", received signal: " << sig << "\n";
    alarm(2);
    return;
}

void *thread_receive_signal(void *arg) {
    pthread_detach(pthread_self());

    struct sigaction sa;
    sa.sa_handler   = sig_catch;
    sa.sa_flags     = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGALRM, &sa, nullptr) == -1) {
        perror("sigaction fail");
        exit(1);
    }

    alarm(2);

    for (int i = 1; i < 111; ++i) {
        std::cout << "thread_receive_signal: " << pthread_self() << ": " << i << "\n";
        sleep(1);
    }

    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    pthread_t   pthread;
    if (pthread_create(&pthread, nullptr, thread_receive_signal, nullptr) != 0) {
        perror("pthread_create pthread");
        exit(1);
    }

    while (true) {
        std::cout << "main: " << pthread_self() << "wait...\n";
        sleep(10);
    }

    std::cout << "main end\n";

    return 0;
}