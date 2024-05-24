#include <iostream>
#include <unistd.h>
#include <pthread.h>

void cleanup_func(void *arg) {
    std::cout << "cleanup func\n";
    return;
}

void *thread_func(void *arg) {
    pthread_cleanup_push(cleanup_func, nullptr); // 取消时会调用cleanup_func

    while (1) {
        pthread_testcancel(); // 测试是否为其他线程取消
        std::cout << "thread_func\n";
        sleep(1);
    }

    pthread_cleanup_pop(0); // 非零调用cleanup_func

    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    pthread_t tid = 0;
    if (pthread_create(&tid, nullptr, thread_func, nullptr) != 0) {
        perror("pthread_create thread_func");
        exit(1);
    }

    sleep(3);
    if (pthread_cancel(tid) != 0) {
        perror("pthread_cancel");
        exit(1);
    }

    pthread_join(tid, nullptr);

    std::cout << "main end\n";

    return 0;
}