#include <iostream>
#include <string>

class A {
public:
    A(int num, const std::string &str) : m_num(num), m_str(str) {
        std::cout << "A(int num, const std::string &str)" << std::endl;
    }

    ~A() {
        std::cout << "~A()" << std::endl;
    }

public:
    void display() const {
        std::cout << "m_num: " << m_num << ", m_str: " << m_str << std::endl;
    }

private:
    int m_num;
    std::string m_str;
};

class MyClass {
public:
    MyClass(int num, const std::string &str, int num2, const std::string &str2) : m_a(num, str), m_num(num2), m_str(str2) {
        std::cout << "MyClass(int num, const std::string &str, int num2, const std::string &str2)" << std::endl;
    }

    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }

public:
    void display() const {
        std::cout << "m_num: " << m_num << ", m_str: " << m_str << std::endl;
        m_a.display();
    }
private:
    A m_a;
    int m_num;
    std::string m_str;
};

int main(int argc, char *argv[]) {
    MyClass mc(11, "kg", 22, "yixin");
    mc.display();

    return 0;
}