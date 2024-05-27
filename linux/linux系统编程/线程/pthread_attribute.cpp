#include <iostream>
#include <unistd.h>
#include <pthread.h>

void print_state(pthread_attr_t *attribute) {
    int state = 0;
    if (pthread_attr_getdetachstate(attribute, &state) != 0) {
        perror("pthread_attr_getdetachstate");
        exit(1);
    } else { 
        if (state == PTHREAD_CREATE_DETACHED) {
            std::cout << "thread detached\n";
        } else if (state == PTHREAD_CREATE_JOINABLE) {
            std::cout << "thread joinable\n";
        }
    }
}

void *thread_func(void *arg) {
    int64_t num = (int64_t)arg;
    for (int i = 0; i < num; ++i) {
        std::cout << i << "\n";
    }
    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    pthread_attr_t attribute;
    pthread_attr_init(&attribute); // 初始化
    pthread_attr_setdetachstate(&attribute, PTHREAD_CREATE_DETACHED); // 设置分离

    print_state(&attribute);

    pthread_t tid = 0;
    int64_t num = 11;
    if (pthread_create(&tid, &attribute, thread_func, (void*)num) != 0) {
        perror("pthread_create thread_func");
        exit(1);
    }

    sleep(1);
    std::cout << "main end\n";
    pthread_attr_destroy(&attribute);

    return 0;
}