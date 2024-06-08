#include <iostream>
#include <semaphore.h>
#include <pthread.h>

sem_t   sem;
sem_t   sem2;

void *thread_func(void* arg) {
    std::cout << pthread_self() << " thread func\n";
    sem_post(&sem);

    pthread_exit(nullptr);
}

void *thread_func2(void* arg) {
    sem_wait(&sem);
    std::cout << pthread_self() << " thread func2\n";
    sem_post(&sem2);

    pthread_exit(nullptr);
}

void *thread_func3(void* arg) {
    sem_wait(&sem2);
    std::cout << pthread_self() << " thread func3\n";
    
    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    // 参数2 0 其他进程不共享 1 其他进程共享
    sem_init(&sem, 0, 0);
    sem_init(&sem2, 0, 0);

    pthread_t   pthread;
    pthread_t   pthread2;
    pthread_t   pthread3;

    if (pthread_create(&pthread, nullptr, thread_func, nullptr) != 0) {
        perror("pthread create pthread fail");
        exit(1);
    }

    if (pthread_create(&pthread2, nullptr, thread_func2, nullptr) != 0) {
        perror("pthread create pthread fail");
        exit(1);
    }

    if (pthread_create(&pthread3, nullptr, thread_func3, nullptr) != 0) {
        perror("pthread create pthread fail");
        exit(1);
    }

    pthread_join(pthread, nullptr);
    sem_destroy(&sem);
    sem_destroy(&sem2);

    return 0;
}