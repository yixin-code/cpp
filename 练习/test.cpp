#include <iostream>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <map>

int main(int argc, char *argv[]) {
    std::map<int, std::string> m = {{1, "aaa"}, {2, "bbb"}, {3, "ccc"}, {4, "ddd"}, {5, "eee"}};
    // 不小于 大于
    auto er = m.equal_range(3);
    std::cout << er.first->first << " " << er.first->second << std::endl; // 3 ccc
    std::cout << er.second->first << " " << er.second->second << std::endl; // 2 bbb
    // 不小于
    auto lb = m.lower_bound(2);
    std::cout << lb->first << " " << lb->second << std::endl; // 2 bbb
    // 大于
    auto ub = m.upper_bound(3);
    std::cout << ub->first << " " << ub->second << std::endl; // 2 bbb

    return 0;
}

// void sig_handler(int signo) {
//     std::cout << "signo: " << signo << std::endl;
// }

// void print_pend(const sigset_t &pend_sig) {
//     for (int i = 1; i <= 31; ++i) {
//         sigismember(&pend_sig, i) ? std::cout << '1' : std::cout << '0';
//     }
// }

// int main(int argc, char *argv[]) {
//     pid_t pid = fork();
//     switch (pid) {
//     case -1: {
//         perror("fork");
//         exit(1);
//     }
//     case 0: {
//         sigset_t            old_sig;
//         sigset_t            pend_sig;
//         struct sigaction    sa;

//         sa.sa_handler = sig_handler;
//         sa.sa_flags   = 0;

//         // 设置临时信号集
//         sigemptyset(&sa.sa_mask);

//         sigaddset(&sa.sa_mask, 1);
//         sigaddset(&sa.sa_mask, 2);
//         sigaddset(&sa.sa_mask, 3);

//         if (sigprocmask(SIG_BLOCK, &sa.sa_mask, &old_sig) == -1) {
//             perror("sigprocmask fail");
//             exit(1);
//         }

//         // 注册信号处理函数
//         sigaction(1, &sa, nullptr);
//         sigaction(2, &sa, nullptr);
//         sigaction(3, &sa, nullptr);

//         // 解除对信号1、2、3的阻塞
//         if (sigprocmask(SIG_UNBLOCK, &sa.sa_mask, nullptr) == -1) {
//             perror("sigprocmask unblock fail");
//             exit(1);
//         }

//         for (int i = 1; i < 10; ++i) {
//             sigpending(&pend_sig);
//             print_pend(pend_sig);
//             sleep(1);
//             std::cout << std::endl;
//         }

//         std::cout << "child end" << std::endl;
//     }
//     default: {
//         sleep(2);
//         kill(pid, 1);
//         sleep(2);
//         kill(pid, 2);
//         sleep(2);
//         kill(pid, 3);

//         std::cout << "parent end" << std::endl;

//         waitpid(-1, nullptr, 0);
//     }
//     }

//     return 0;
// }
// // #include <iostream>
// // #include <list>
// // #include <vector>
// // #include <algorithm> // std::find remove_if
// // #include <pthread.h> // pthread_t pthread_create pthread_exit pthread_self
// // #include <time.h> // timespec
// // #include <math.h> // pow round
// // #include <string>
// // #include <unistd.h>

// // int main(int argc, char *argv[]) {
// //     int arr[] = {1, 2, 3, 4, 5};

// //     std::cout << "arr: " << arr << std::endl; // 0x00
// //     std::cout << "arr + 1: " << arr + 1 << std::endl; // 0x04
// //     std::cout << "&arr[0]: " << &arr[0] << std::endl; // 0x00
// //     std::cout << "&arr[0] + 1: " << &arr[0] + 1 << std::endl; // 0x04
// //     std::cout << "&arr: " << &arr << std::endl; // 0x00
// //     std::cout << "&arr + 1: " << &arr + 1 << std::endl; // 0xa4

// //     return 0;
// // }

// // // void func() {
// // //     std::cout << "func" << std::endl;
// // // }

// // // using p_func_type = void (*) ();
// // // int main(int argc, char *argv[]) {
// // //     p_func_type p_func = func;
// // //     (*p_func)();

// // //     return 0;
// // // }

// // // class A {
// // // public:
// // //     void func() {
// // //         std::cout << "A" << std::endl;
// // //     }
// // // };

// // // int main(int argc, char *argv[]) {
// // //     using p_A_func = void (A::*) ();
// // //     // p_A_func();
// // //     A a;
// // //     a.func();
// // //     p_A_func();
// // //     // while (true) {
// // //     //     sleep(1);
// // //     // }
// // //     // std::vector<int> v{1, 2, 3};
// // //     // std::vector<int> v2(v); // 1 2 3
// // //     // std::vector<int> v3(3); // 0 0 0

// // //     // std::cout << "v.size = " << v.size() << '\n'; // 3
// // //     // std::cout << "v.size = " << v.capacity() << '\n'; // 3
// // //     // std::cout << "v2.size = " << v2.size() << '\n'; // 3
// // //     // std::cout << "v2.size = " << v2.capacity() << '\n'; // 3
// // //     // std::cout << "v3.size = " << v3.size() << '\n'; // 3
// // //     // std::cout << "v3.size = " << v3.capacity() << '\n'; // 3

// // //     // for (const int &val : v3) {
// // //     //     std::cout << "[" << val << "]" << '\n';
// // //     // }
// // //     // int i = 2;
// // //     // int j = 3;
// // //     // int k = 0;

// // //     // k = j > i ? ++i : j;
// // //     // std::cout << "k: " << k << '\n';
// // //     // std::cout << "i: " << i << ", j: " << j << '\n';
// // //     // std::string str = "hello world";

// // //     // uint64_t    pos = str.find("world");
// // //     // if (pos == std::string::npos) {
// // //     //     std::cout << "not found" << std::endl;
// // //     // } else {
// // //     //     std::cout << "pos: " << pos << std::endl; // 6 字符下标
// // //     // }

// // //     // pos = str.find('o');
// // //     // if (pos == std::string::npos) {
// // //     //     std::cout << "not found" << std::endl;
// // //     // } else {
// // //     //     std::cout << "pos: " << pos << std::endl; // 4
// // //     // }

// // //     return 0;
// // // }

// // // // int main(int argc, char *argv[]) {
// // // //     std::cout << "hello world"[2] << '\n';
// // // //     // std::vector<int> v{1, 2, 3};
// // // //     // v[2]++;
// // // //     // std::cout << v[2] << '\n';
// // // //     // v.reserve(1111);
// // // //     // v.resize(1111);
// // // //     // std::cout << v.capacity() << '\n';
// // // //     // std::cout << v.size() << '\n';
// // // //     // v.resize(11);
// // // //     // v[3] = 3;

// // // //     // std::cout << v[3] << '\n';

// // // //     // std::cout << v.size() << '\n';
// // // //     // std::cout << v.capacity() << '\n';

// // // //     // for (const int &val : v) {
// // // //     //     std::cout << val << std::endl;
// // // //     // }

// // // //     return 0;
// // // // }

// // // // // enum {A = 1, B};

// // // // // int main(int argc, char *argv[]) {
// // // // // // enum {A = 1, B};
// // // // //     int A = 11;
// // // // //     std::cout << "A: " << A << std::endl;
    
// // // // //     // std::vector<int> v{1, 2, 3};
// // // // //     // v.insert(v.begin(), 4); // 4 1 2 3
// // // // //     // // std::vector<int> v{1, 2, 3};

// // // // //     // // std::cout << "size: " << v.size() << std::endl; // 3
// // // // //     // // std::cout << "capacity: " << v.capacity() << std::endl; // 3

// // // // //     // // v.resize(11);
// // // // //     // // std::cout << "size: " << v.size() << std::endl; // 11
// // // // //     // // std::cout << "capacity: " << v.capacity() << std::endl; // 11

// // // // //     // // v.resize(4);
// // // // //     // // std::cout << "size: " << v.size() << std::endl; // 4
// // // // //     // // std::cout << "capacity: " << v.capacity() << std::endl; // 11

// // // // //     // for (const int &val : v) {
// // // // //     //     std::cout << val << ' '; // 1 2 3 0
// // // // //     // }
// // // // //     // std::cout << std::endl;
// // // // //     // // std::vector<int> vec2;
// // // // //     // // vec2.resize(11);
// // // // //     // std::cout << vec2.size() << "\n"; // 11
// // // // //     // std::cout << vec2.capacity() << "\n"; // 11
// // // // //     // //////////////////////////////////////////////////////////////////////////////////
// // // // //     // std::vector<int> vec3;
// // // // //     // vec3.reserve(11);
// // // // //     // std::cout << vec3.size() << "\n"; // 0
// // // // //     // std::cout << vec3.capacity() << "\n"; // 11
    

// // // // //     return 0;
// // // // // }

// // // // // // class A {
// // // // // // public:
// // // // // //     void func() {
// // // // // //         for (const int &val : this->m_arr) {
// // // // // //             std::cout << val << '\n';
// // // // // //         }
// // // // // //     }
// // // // // // private:
// // // // // //     int m_arr[11];
// // // // // // };

// // // // // // int main(int argc, char *argv[]) {
// // // // // //     A a;
// // // // // //     a.func();

// // // // // //     return 0;
// // // // // // }

// // // // // // void func() {
// // // // // //     int num;
// // // // // //     std::cout << "num: " << num << ", &num: " << &num << '\n';
// // // // // //     num = 11;
// // // // // // }

// // // // // // int main(int argc, char *argv[]) {
// // // // //     // func();
// // // // //     // std::cout << "------\n";
// // // // //     // func();
// // // // //     // const int num = 11;
// // // // //     // int arr[num];

// // // // //     // for (const int &element : arr) {
// // // // //     //     std::cout << element << '\n';
// // // // //     // }
// // // // //     // std::list<int> l{1, 2, 3, 3, 4, 5};

// // // // //     // l.erase(std::remove_if(l.begin(), l.end(), [](int num){return num > 3;}), l.end()); // 删除元素为3的元素

// // // // //     // for (const int& val : l) {
// // // // //     //     std::cout << val << '\n';
// // // // //     // }
// // // // //     // int num = 3;
// // // // //     // std::list<int>::iterator it = std::find(l.begin(), l.end(), num);
// // // // //     // if (it == l.end()) {
// // // // //     //     std::cout << "not find\n";
// // // // //     // } else {
// // // // //     //     std::cout << "*it: " << *it << ", " << std::distance(l.begin(), it) << '\n'; // 迭代器之间的距离 3 2
// // // // //     // }

// // // // // //     return 0;
// // // // // // }
  
// // // // // // int main() {  
// // // // // //     // 声明 timespec 结构体变量  
// // // // // //     struct timespec ts;  
  
// // // // // //     // 获取当前时间  
// // // // // //     if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {  
// // // // // //         // 处理错误  
// // // // // //         perror("clock_gettime");  
// // // // // //         return 1;  
// // // // // //     }  

// // // // // //     printf("设置前的时间: %ld 秒, %ld 纳秒\n", ts.tv_sec, ts.tv_nsec);  
  
// // // // // //     // 设置 ts 为当前时间加1秒  
// // // // // //     ts.tv_sec += 1; // 秒数加1  
// // // // // //     ts.tv_nsec = 0; // 纳秒数设为0  
  
// // // // // //     // 打印设置后的时间  
// // // // // //     printf("设置后的时间: %ld 秒, %ld 纳秒\n", ts.tv_sec, ts.tv_nsec);  
  
// // // // // //     // 这里只是演示设置时间，并未实际使用（如休眠）  
  
// // // // // //     return 0;  
// // // // // // }
// // // // // // void func(int a, b, c) {

// // // // // // }

// // // // // // int main(int argc, char *argv[]) {


// // // // // //     return 0;
// // // // // // }

// // // // // // int     num     = 0;
// // // // // // int     temp    = 0;

// // // // // // void* func(void *arg) {
// // // // // //     for (int i = 0; i < 50000; ++i) {
// // // // // //         temp = num;
// // // // // //         std::cout << "tid: " << pthread_self() << ", num: " << num << '\n';
// // // // // //         num = temp + 1;
// // // // // //     }

// // // // // //     pthread_exit(nullptr);
// // // // // // }

// // // // // // void work() {
// // // // // //     pthread_t   tid   = 0;
// // // // // //     pthread_t   tid2  = 0;

// // // // // //     if (pthread_create(&tid, nullptr, func, nullptr) != 0) {
// // // // // //         perror("pthread_create tid");
// // // // // //         exit(1);
// // // // // //     }

// // // // // //     if (pthread_create(&tid2, nullptr, func, nullptr) != 0) {
// // // // // //         perror("pthread_create tid2");
// // // // // //         exit(1);
// // // // // //     }

// // // // // //     pthread_join(tid, nullptr);
// // // // // //     pthread_join(tid2, nullptr);
// // // // // // }

// // // // // // int main(int argc, char *argv[]) {
// // // // // //     work();

// // // // // //     return 0;
// // // // // // }