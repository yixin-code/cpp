#include <iostream>
#include <list>
#include <vector>
#include <algorithm> // std::find remove_if
#include <pthread.h> // pthread_t pthread_create pthread_exit pthread_self
#include <time.h> // timespec
#include <math.h> // pow round

int main(int argc, char *argv[]) {
    // std::cout << "hello world" << std::endl;

    return 0;
}

// int main(int argc, char *argv[]) {
//     std::cout << "hello world"[2] << '\n';
//     // std::vector<int> v{1, 2, 3};
//     // v[2]++;
//     // std::cout << v[2] << '\n';
//     // v.reserve(1111);
//     // v.resize(1111);
//     // std::cout << v.capacity() << '\n';
//     // std::cout << v.size() << '\n';
//     // v.resize(11);
//     // v[3] = 3;

//     // std::cout << v[3] << '\n';

//     // std::cout << v.size() << '\n';
//     // std::cout << v.capacity() << '\n';

//     // for (const int &val : v) {
//     //     std::cout << val << std::endl;
//     // }

//     return 0;
// }

// // enum {A = 1, B};

// // int main(int argc, char *argv[]) {
// // // enum {A = 1, B};
// //     int A = 11;
// //     std::cout << "A: " << A << std::endl;
    
// //     // std::vector<int> v{1, 2, 3};
// //     // v.insert(v.begin(), 4); // 4 1 2 3
// //     // // std::vector<int> v{1, 2, 3};

// //     // // std::cout << "size: " << v.size() << std::endl; // 3
// //     // // std::cout << "capacity: " << v.capacity() << std::endl; // 3

// //     // // v.resize(11);
// //     // // std::cout << "size: " << v.size() << std::endl; // 11
// //     // // std::cout << "capacity: " << v.capacity() << std::endl; // 11

// //     // // v.resize(4);
// //     // // std::cout << "size: " << v.size() << std::endl; // 4
// //     // // std::cout << "capacity: " << v.capacity() << std::endl; // 11

// //     // for (const int &val : v) {
// //     //     std::cout << val << ' '; // 1 2 3 0
// //     // }
// //     // std::cout << std::endl;
// //     // // std::vector<int> vec2;
// //     // // vec2.resize(11);
// //     // std::cout << vec2.size() << "\n"; // 11
// //     // std::cout << vec2.capacity() << "\n"; // 11
// //     // //////////////////////////////////////////////////////////////////////////////////
// //     // std::vector<int> vec3;
// //     // vec3.reserve(11);
// //     // std::cout << vec3.size() << "\n"; // 0
// //     // std::cout << vec3.capacity() << "\n"; // 11
    

// //     return 0;
// // }

// // // class A {
// // // public:
// // //     void func() {
// // //         for (const int &val : this->m_arr) {
// // //             std::cout << val << '\n';
// // //         }
// // //     }
// // // private:
// // //     int m_arr[11];
// // // };

// // // int main(int argc, char *argv[]) {
// // //     A a;
// // //     a.func();

// // //     return 0;
// // // }

// // // void func() {
// // //     int num;
// // //     std::cout << "num: " << num << ", &num: " << &num << '\n';
// // //     num = 11;
// // // }

// // // int main(int argc, char *argv[]) {
// //     // func();
// //     // std::cout << "------\n";
// //     // func();
// //     // const int num = 11;
// //     // int arr[num];

// //     // for (const int &element : arr) {
// //     //     std::cout << element << '\n';
// //     // }
// //     // std::list<int> l{1, 2, 3, 3, 4, 5};

// //     // l.erase(std::remove_if(l.begin(), l.end(), [](int num){return num > 3;}), l.end()); // 删除元素为3的元素

// //     // for (const int& val : l) {
// //     //     std::cout << val << '\n';
// //     // }
// //     // int num = 3;
// //     // std::list<int>::iterator it = std::find(l.begin(), l.end(), num);
// //     // if (it == l.end()) {
// //     //     std::cout << "not find\n";
// //     // } else {
// //     //     std::cout << "*it: " << *it << ", " << std::distance(l.begin(), it) << '\n'; // 迭代器之间的距离 3 2
// //     // }

// // //     return 0;
// // // }
  
// // // int main() {  
// // //     // 声明 timespec 结构体变量  
// // //     struct timespec ts;  
  
// // //     // 获取当前时间  
// // //     if (clock_gettime(CLOCK_REALTIME, &ts) == -1) {  
// // //         // 处理错误  
// // //         perror("clock_gettime");  
// // //         return 1;  
// // //     }  

// // //     printf("设置前的时间: %ld 秒, %ld 纳秒\n", ts.tv_sec, ts.tv_nsec);  
  
// // //     // 设置 ts 为当前时间加1秒  
// // //     ts.tv_sec += 1; // 秒数加1  
// // //     ts.tv_nsec = 0; // 纳秒数设为0  
  
// // //     // 打印设置后的时间  
// // //     printf("设置后的时间: %ld 秒, %ld 纳秒\n", ts.tv_sec, ts.tv_nsec);  
  
// // //     // 这里只是演示设置时间，并未实际使用（如休眠）  
  
// // //     return 0;  
// // // }
// // // void func(int a, b, c) {

// // // }

// // // int main(int argc, char *argv[]) {


// // //     return 0;
// // // }

// // // int     num     = 0;
// // // int     temp    = 0;

// // // void* func(void *arg) {
// // //     for (int i = 0; i < 50000; ++i) {
// // //         temp = num;
// // //         std::cout << "tid: " << pthread_self() << ", num: " << num << '\n';
// // //         num = temp + 1;
// // //     }

// // //     pthread_exit(nullptr);
// // // }

// // // void work() {
// // //     pthread_t   tid   = 0;
// // //     pthread_t   tid2  = 0;

// // //     if (pthread_create(&tid, nullptr, func, nullptr) != 0) {
// // //         perror("pthread_create tid");
// // //         exit(1);
// // //     }

// // //     if (pthread_create(&tid2, nullptr, func, nullptr) != 0) {
// // //         perror("pthread_create tid2");
// // //         exit(1);
// // //     }

// // //     pthread_join(tid, nullptr);
// // //     pthread_join(tid2, nullptr);
// // // }

// // // int main(int argc, char *argv[]) {
// // //     work();

// // //     return 0;
// // // }