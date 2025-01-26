#include <iostream>

class MyClass {
public:
    MyClass() = default;

    MyClass(int num) : m_num(num) {
        std::cout << "MyClass(int num)" << std::endl;
    }

    MyClass(const MyClass &mc) : m_num(mc.m_num) {
        std::cout << "MyClass(const MyClass &mc)" << std::endl;
    }

    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }

private:
    int m_num;
};

MyClass func() {
    MyClass mc(11);

    return mc;
}

int main(int argc, char *argv[]) {
    MyClass mc = func(); // 因为返回值优化 只会调用一次构造 一次析构

    return 0;
}