#include <iostream>
#include <pthread.h> // pthread_t pthread_create pthread_exit pthread_self

int     num     = 0;
int     temp    = 0;

void* func(void *arg) {
    for (int i = 0; i < 50000; ++i) {
        temp = num;
        std::cout << "tid: " << pthread_self() << ", num: " << num << '\n';
        num = temp + 1;
    }

    pthread_exit(nullptr);
}

void work() {
    pthread_t   tid   = 0;
    pthread_t   tid2  = 0;

    if (pthread_create(&tid, nullptr, func, nullptr) != 0) {
        perror("pthread_create tid");
        exit(1);
    }

    if (pthread_create(&tid2, nullptr, func, nullptr) != 0) {
        perror("pthread_create tid2");
        exit(1);
    }

    pthread_join(tid, nullptr);
    pthread_join(tid2, nullptr);
}

int main(int argc, char *argv[]) {
    work();

    return 0;
}