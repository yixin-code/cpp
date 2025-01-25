#include <iostream>
#include <string>

class MyClass {
public:
    MyClass(int num) : m_num(num), m_str("default") {
        std::cout << "MyClass(int num) : m_num(num), m_str(\"default\")" << std::endl;
    }

    // MyClass(int num, const std::string &str) : MyClass(num), m_str(str) { // error 委托构造初始化列表中不能在初始化其他成员
    MyClass(int num, const std::string &str) : MyClass(num) {
        std::cout << "MyClass(int num, const std::string &str) : MyClass(num)" << std::endl;
        m_str = str;
    }

    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }

public:
    void display() const {
        std::cout << "m_num: " << m_num << ", m_str: " << m_str << std::endl;
    }
private:
    int m_num;
    std::string m_str;
};

int main(int argc, char *argv[]) {
    MyClass mc(11);
    mc.display();

    MyClass mc2(11, "yixin"); // 会先调用 构造 然后再次调用委托构造 两次构造函数
    mc2.display();

    return 0;
}