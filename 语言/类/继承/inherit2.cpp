#include <iostream>
#include <cstring>

class Parent {
private:
    int *m_parent_p;
public:
    Parent() : m_parent_p(new int(11)) {
        std::cout << "Parent(int num)" << std::endl;
        for (int i = 0; i < 11; ++i) {
            m_parent_p[i] = i + 1;
        }
    }
    Parent(const Parent &p) = default;
    ~Parent() {
        std::cout << "~Parent()" << std::endl;
        delete[] m_parent_p;
    }
public:
    void display() {
        for (int i = 0; i < 11; ++i) {
            std::cout << m_parent_p[i] << std::endl;
        }
    }
};

class Son : public Parent {
private:
    int *m_son_p;
public:
    Son() {
        m_son_p = new int[11];
        for (int i = 0; i < 11; ++i) {
            m_son_p[i] = i + 1;
        }
    }
    Son(const Son &son) {
        if (this != &son) {
            m_son_p = new int[11];
            memcpy(m_son_p, son.m_son_p, sizeof(int) * 11);
        }
    }
    ~Son() {
        std::cout << "~Son()" << std::endl;
    }
public:
};

int main(int argc, char *argv[]) {


    return 0;
}