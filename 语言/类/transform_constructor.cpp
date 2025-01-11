#include <iostream>

class A {
private:
    int m_num;

public:
    // explicit A(int num) : m_num(num) { // explicit可以防止隐式类型转换
    A(int num) : m_num(num) {
        std::cout << "A(int)" << std::endl;
    }
    ~A() {
        std::cout << "~A()" << std::endl;
    }

public:
    A& operator=(const A& a) { // 赋值运算符重载
        std::cout << "operator=" << std::endl;
        this->m_num = a.m_num;

        return *this;
    }

public:
    void display() const {
        std::cout << "m_num: " << this->m_num << std::endl;
    }
};

int main(int argc, char *argv[]) {
    A a = 11;
    a = 22; // a = A(22) 隐式类型转换生成匿名对象
    a.display();

    return 0;
}