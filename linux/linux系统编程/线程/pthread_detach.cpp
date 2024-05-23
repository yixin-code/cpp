#include <iostream>
#include <unistd.h>
#include <pthread.h>

void* func(void *arg) {
    pthread_detach(pthread_self());
    std::cout << "func...\n";
    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    std::cout << "main...\n";
    pthread_t tid = 0;
    pthread_create(&tid, nullptr, func, nullptr);
    sleep(1);

    return 0;
}