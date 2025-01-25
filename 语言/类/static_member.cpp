// 静态成员属于整个类，所有对象共享
// 静态成员类外初始化
#include <iostream>

class MyClass {
public:
    void set_num(int num) {
        m_s_num = num;
    }
    void display() const {
        std::cout << "m_s_num: " << m_s_num << std::endl;
    }

private:
    static int m_s_num;
};

int main(int argc, char *argv[]) {
    MyClass mc;
    mc.display();
    
    MyClass mc2;
    mc2.set_num(11);

    mc.display();

    return 0;
}

int MyClass::m_s_num = 0;