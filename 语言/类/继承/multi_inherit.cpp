#include <iostream>

class A {
public:
    int m_data;
public:
    A(int data) : m_data(data) {
        std::cout << "A(int data): " << &m_data << std::endl;
    }
};

class AB : public A {
public:
    AB() : A(11) {
        std::cout << "AB(): " << &(A::m_data) << std::endl;
    }
};

class AC : public A {
public:
    AC() : A(11) {
        std::cout << "AC(): " << &(A::m_data) << std::endl;
    }
};

class ABC : public AB, public AC {
public:
    ABC() {
        std::cout << "ABC(): " << &(AB::m_data) << std::endl;
        std::cout << "ABC(): " << &(AC::m_data) << std::endl;
    }
};

int main(int argc, char *argv[]) {
    // AB ab; // A AB 中的m_data地址相同
    // AC ac; // A AC 中的m_data地址相同
    ABC abc; // ABC 中会出现两个 AB AC 中的m_data地址不相同

    return 0;
}