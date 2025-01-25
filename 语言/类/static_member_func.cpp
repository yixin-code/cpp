// 静态成员函数无法 访问非静态成员 无法调用非静态成员函数
// 通过类名直接调用 不需要实例对象
#include <iostream>

class MyClass {
public:
    void display() const {
        std::cout << "m_num: " << m_num << std::endl;
        std::cout << "m_s_num: " << m_s_num << std::endl;
    }
    static void s_display();

private:
    int m_num = 11;
    static int m_s_num;
};

int main(int argc, char *argv[]) {
    MyClass ms;
    ms.display();
    ms.s_display();

    return 0;
}

int MyClass::m_s_num = 22;

void MyClass::s_display() {
    // display();
    // std::cout << "m_num: " << m_num << std::endl; error 静态成员函数不能调用非静态成员/函数
    std::cout << "m_s_num: " << m_s_num << std::endl;
}