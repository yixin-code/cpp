#include <iostream>
#include <pthread.h>

void* func(void *arg) {
    int64_t *p = (int64_t*)arg;
    std::cout << "func: " << *p << std::endl;
    ++(*p);
    pthread_exit((void*)p); // pthread_join可接收返回值 不关心可以nullpter
}

int main(int argc, char *argv[]) {
    pthread_t tid = 0;
    int64_t num = 11;
    // 成功返回0 失败返回errno
        // 参数2设置线程属性，nullptr为默认
    pthread_create(&tid, nullptr, func, (void*)&num);
    void *p_exit = nullptr;
    pthread_join(tid, &p_exit); // 阻塞等待线程结束回收资源
    std::cout << "main: " << *(int64_t*)p_exit << std::endl;

    return 0;
}