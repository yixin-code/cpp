#include <iostream>
#include <unistd.h>
#include <pthread.h>

void *thread_return(void *arg) {
    std::cout << "thread_return: " << *(int*)arg + 11 << '\n';

    return arg;
}

void *thread_exit(void *arg) {
    std::cout << "thread_exit: " << *(int*)arg + 11 << '\n';

    pthread_exit(arg);
}

void *thread_cancel(void *arg) {
    while (true) {
        std::cout << "thread_cancel: " << *(int*)arg + 11 << '\n';
        sleep(1);
    }

    pthread_exit(arg);
}

int main(int argc, char *argv[]) {
    pthread_t   tid     = 0;
    int         num     = 11;
    void        *p_res  = nullptr;

    if (pthread_create(&tid, nullptr, thread_return, &num) != 0) {
        perror("pthread_create thread_return");
        exit(1);
    }
    pthread_join(tid, &p_res);
    std::cout << "p_res: " << *(int*)p_res << '\n';

    if (pthread_create(&tid, nullptr, thread_exit, &num) != 0) {
        perror("pthread_create thread_exit");
        exit(1);
    }
    pthread_join(tid, &p_res);
    std::cout << "p_res: " << *(int*)p_res << '\n';

    if (pthread_create(&tid, nullptr, thread_cancel, &num) != 0) {
        perror("pthread_create thread_cancel");
        exit(1);
    }
    // pthread_join(tid, &p_res);
    sleep(5);
    pthread_cancel(tid);
    std::cout << "p_res: " << *(int*)p_res << '\n';

    return 0;
}