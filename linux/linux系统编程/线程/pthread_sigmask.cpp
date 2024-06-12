#include <iostream>
#include <string.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

void catch_alarm_signal(int signo) {
    return;
}

void *thread_rece_signal(void *arg) {
    pthread_detach(pthread_self());

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler   = catch_alarm_signal;
    sa.sa_flags     = 0;
    sigemptyset(&sa.sa_mask);
    
    if (sigaction(SIGALRM, &sa, nullptr) == -1) {
        perror("sigaction fail");
        exit(1);
    }

    for (int i = 0)

    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    sigset_t   sigset;
    sigemptyset(&sigset);
    sigaddset(&sigset, SIGALRM);    // SIGALRM添加到信号集，进行阻塞
    // SIG_BLOCK    设置阻塞信号
    // SIG_UNBLOCK  移除阻塞信号
    // SIG_SETMASK  设置当前信号集为第二参数指向
    if (sigprocmask(SIG_SETMASK, &sigset, nullptr) == -1) {
        perror("sigprocmask fail");
        exit(1);
    }

    pthread_t   pthread;
    if (pthread_create(&pthread, nullptr, thread_rece_signal, nullptr) != 0) {
        perror("pthread_create pthread");
        exit(1);
    }

    while(true) {
        std::cout << pthread_self() << "main wait...\n";
        sleep(5);
    }

    return 0;
}