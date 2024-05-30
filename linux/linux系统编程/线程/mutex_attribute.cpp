#include <iostream>
#include <pthread.h>

int main(int argc, char *argv[]) {
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr);   // 初始化互斥锁属性 成功0 失败errno
    int res = 0;
    pthread_mutexattr_getpshared(&mutexattr, &res);   // 获得锁属性
    // PTHREAD_PROCESS_SHARED 用于不同进程中的线程互斥
    // PTHREAD_PROCESS_PRIVATE 用于同进程中的线程互斥(默认值)
    pthread_mutexattr_setpshared(&mutexattr, PTHREAD_PROCESS_SHARED);    // 设置可用于不同进程中线程互斥
    pthread_mutexattr_getpshared(&mutexattr, &res);   // 获得锁属性
    std::cout << "--------------------------------------------------\n";
    pthread_mutexattr_gettype(&mutexattr, &res); // 获得锁类型
    // PTHREAD_MUTEX_NORMAL(标准互斥锁) 大多系统中等同于 PTHREAD_MUTEX_DEFAULT默认值(默认互斥锁)
    // PTHREAD_MUTEX_RECURSIVE(递归互斥锁) 第一次上锁成功 第二次上锁成功 内部计数
    // PTHREAD_MUTEX_ERRORCHECK(检错互斥锁) 第一次上锁成功 第二次上锁失败
    pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_ERRORCHECK); // 设置锁类型
    pthread_mutexattr_gettype(&mutexattr, &res); // 获得锁类型
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, &mutexattr);
    // pthread_mutex_lock(&mutex);
    res = pthread_mutex_lock(&mutex);
    if (res == EDEADLK) {
        std::cout << "上锁失败\n";
        pthread_mutex_destroy(&mutex);
        pthread_mutexattr_destroy(&mutexattr); // 销毁互斥锁属性 成功0 失败errno
        exit(1);
    }
    pthread_mutex_destroy(&mutex);
    std::cout << "--------------------------------------------------\n";
    pthread_mutexattr_destroy(&mutexattr); // 销毁互斥锁属性 成功0 失败errno

    return 0;
}