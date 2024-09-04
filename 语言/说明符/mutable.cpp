#include <iostream>

class A {
public:
    A(int num) : m_num(num) {}
public:
    void func() const {
        std::cout << "num: " << this->m_num << '\n'; // 11
        this->m_num = 22;
        std::cout << "num: " << this->m_num << '\n'; // 22
    }

private:
    mutable int m_num;
};

int main(int argc, char *argv[]) {
    A a(11);
    a.func();

    return 0;
}