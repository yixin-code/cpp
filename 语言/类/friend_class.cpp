#include <iostream>

class A {
friend class B;
private:
    int m_a;
public:
    A(int a = 11) : m_a(a) {
        std::cout << "A(int a = 11)" << std::endl;
    }
    ~A() {
        std::cout << "~A()" << std::endl;
    }
public:
    void display() const {
        std::cout << "m_a: " << m_a << std::endl;
    }
};

class B {
private:
    int m_b;
public:
    B(int b = 22) : m_b(b) {
        std::cout << "B(int b = 22)" << std::endl;
    }
    ~B() {
        std::cout << "~B()" << std::endl;
    }
public:
    void display(const A &a) const {
        // std::cout << "m_a: " << m_a << std::endl; // error
        std::cout << "m_a: " << a.m_a << std::endl;
        std::cout << "m_b: " << m_b << std::endl;
    }
};

int main() {
    A a;
    a.display();
    B b;
    b.display(a);

    return 0;
}