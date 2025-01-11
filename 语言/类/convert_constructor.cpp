#include <iostream>

class A {
public:
    A(int num) {}
};

class B {
public:
    explicit B(int num) {} // 防止隐身类型转换
};

int main(int argc, char *argv[]) {
    A a = 11;
    // B b = 11; // error

    return 0;
}