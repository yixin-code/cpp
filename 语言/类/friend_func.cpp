#include <iostream>

class MyClass {
public:
    MyClass(int num) : m_num(num) {
        std::cout << "MyClass(int num)" << std::endl;
    }
    void display() const {
        std::cout << "m_num:" << m_num << std::endl;
    }
    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }

public:
    friend void func(MyClass &mc); // 友元函数 访问权限和实际操作无关 起到设计作用

private:
    int m_num;
};

void func(MyClass &mc) {
    mc.m_num = 22;
}

int main(int argc, char *argv[]) {
    MyClass mc(11);
    mc.display();
    func(mc);
    mc.display();

    return 0;
}