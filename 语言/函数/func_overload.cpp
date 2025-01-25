// 参数 类型 个数 顺序 可以重载
// const type* 可以重载
#include <iostream>
#include <string>
int func(int num, const std::string &str = "yixin") {
    std::cout << "int func(int num, const std::string &str)" << std::endl;
    return 0;
}

int func(const std::string &str, int num = 11) {
    std::cout << "int func(const std::string &str, int num = 11)" << std::endl;
    return 0;
}

void func(int *p) {}
void func(const int *p) {}

// error const 普通对象不能构成重载
// int func(const int num, const std::string &str = "yixin") {
//     std::cout << "int func(const int num, const std::string &str)" << std::endl;
//     return 0;
// }

// double func(int num, const std::string &str) {} // error 返回值无法重载

int main(int argc, char *argv[]) {
    func(11);
    func("yixin");
    // int num = 11;
    // func(num, "yixin");

    return 0;
}