#include <iostream>

class A {
private:
    int m_num;

public:
    A(int num) : m_num(num) {}
};

class B {
private:
    int m_num;

public:
    explicit B(int num) : m_num(num) {} // 防止隐身类型转换
};

int main(int argc, char *argv[]) {
    A a = 11;
    // B b = 11; // error

    return 0;
}