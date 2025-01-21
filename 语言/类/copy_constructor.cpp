#include <iostream>

class A {
public:
    A(int num) : m_num(num) {
        std::cout << "A(int)" << std::endl;
    }
    A(const A &a) : m_num(a.m_num) {
        std::cout << "A(const A&)" << std::endl;
    }
    ~A() {
        std::cout << "~A()" << std::endl;
    }

public:
    A& operator=(const A &a) {
        this->m_num = a.m_num;

        std::cout << "A& operator=(const A&)" << std::endl;

        return *this;
    }

public:
    void display() const {
        std::cout << "m_num: " << m_num << std::endl;
    }

private:
    int m_num;
};

// void func (A a) { // 调用的是拷贝构造
void func (A &a) {
    a.display();
}

int main(int argc, char *argv[]) {
    A a(11);
    func(a);

    return 0;
}