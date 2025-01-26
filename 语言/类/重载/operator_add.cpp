// 前置++是原子操作
#include <iostream>

class MyClass {
public:
    MyClass(int num) : m_num(num) {
        std::cout << "MyClass(int num)" << std::endl;
    }
    MyClass(const MyClass &mc) : m_num(mc.m_num) {
        std::cout << "MyClass(const MyClass &mc)" << std::endl;
    }
    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }
public:
    MyClass& operator++() {
        ++m_num;
        return *this;
    }
    MyClass operator++(int) { // 后置++
        MyClass temp(*this);
        ++(*this);
        return temp;
    }
public:
    void display() const {
        std::cout << "m_num: " << m_num << std::endl;
    }
private:
    int m_num;
};
int main(int argc, char *argv[]) {
    MyClass mc(11);
    mc.display();
    mc++;
    mc.display();
    ++mc;
    mc.display();

    return 0;
}