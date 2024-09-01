#include <iostream>
#include <pthread.h> // pthread_t pthread_create pthread_exit pthread_self
#include <time.h> // timespec
  
// int main() {  
//     // 声明 timespec 结构体变量  
//     struct timespec ts;  
  
//     // 获取当前时间  
//     if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {  
//         // 处理错误  
//         perror("clock_gettime");  
//         return 1;  
//     }  

//     printf("设置前的时间: %ld 秒, %ld 纳秒\n", ts.tv_sec, ts.tv_nsec);  
  
//     // 设置 ts 为当前时间加1秒  
//     ts.tv_sec += 1; // 秒数加1  
//     ts.tv_nsec = 0; // 纳秒数设为0  
  
//     // 打印设置后的时间  
//     printf("设置后的时间: %ld 秒, %ld 纳秒\n", ts.tv_sec, ts.tv_nsec);  
  
//     // 这里只是演示设置时间，并未实际使用（如休眠）  
  
//     return 0;  
// }
// void func(int a, b, c) {

// }

// int main(int argc, char *argv[]) {


//     return 0;
// }

// int     num     = 0;
// int     temp    = 0;

// void* func(void *arg) {
//     for (int i = 0; i < 50000; ++i) {
//         temp = num;
//         std::cout << "tid: " << pthread_self() << ", num: " << num << '\n';
//         num = temp + 1;
//     }

//     pthread_exit(nullptr);
// }

// void work() {
//     pthread_t   tid   = 0;
//     pthread_t   tid2  = 0;

//     if (pthread_create(&tid, nullptr, func, nullptr) != 0) {
//         perror("pthread_create tid");
//         exit(1);
//     }

//     if (pthread_create(&tid2, nullptr, func, nullptr) != 0) {
//         perror("pthread_create tid2");
//         exit(1);
//     }

//     pthread_join(tid, nullptr);
//     pthread_join(tid2, nullptr);
// }

// int main(int argc, char *argv[]) {
//     work();

//     return 0;
// }