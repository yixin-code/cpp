#include <iostream>
#include <cstring>

class Parent {
private:
    int *m_parent_p;
public:
    Parent() : m_parent_p(new int[11]) {
        std::cout << "Parent(int num)" << std::endl;
        for (int i = 0; i < 11; ++i) {
            m_parent_p[i] = i + 1;
        }
    }
    // Parent(const Parent &p) = default; // error
    Parent(const Parent &p) {
        std::cout << "Parent(const Parent &p)" << std::endl;
        if (this != &p) {
            m_parent_p = new int[11];
            memcpy(m_parent_p, p.m_parent_p, sizeof(int) * 11);
        }
    }
    ~Parent() {
        std::cout << "~Parent()" << std::endl;
        delete[] m_parent_p;
    }
public:
    Parent& operator=(const Parent &p) {
        std::cout << "Parent& operator=(const Parent &p)" << std::endl;
        if (this == &p) {
            return *this;
        }

        delete[] m_parent_p;

        if (p.m_parent_p == nullptr) {
            m_parent_p = nullptr;
        } else {
            m_parent_p = new int[11];
            memcpy(m_parent_p, p.m_parent_p, sizeof(int) * 11);
        }

        return *this;
    }
};

class Son : public Parent {
private:
    int *m_son_p;
public:
    Son() {
        std::cout << "Son()" << std::endl;
        m_son_p = new int[11];
        for (int i = 0; i < 11; ++i) {
            m_son_p[i] = i + 1;
        }
    }
    Son(const Son &son) : Parent(son) { // 需要显示调用父类拷贝构造
        std::cout << "Son(const Son &son)" << std::endl;
        if (this != &son) {
            m_son_p = new int[11];
            memcpy(m_son_p, son.m_son_p, sizeof(int) * 11);
        }
    }
    ~Son() {
        std::cout << "~Son()" << std::endl;
        delete[] m_son_p;
    }
public:
    Son& operator=(const Son &s) {
        std::cout << "Son& operator=(const Son &s)" << std::endl;
        if (this == &s) {
            return *this;
        }

        Parent::operator=(s); // 需要显示调用父类赋值运算符

        delete[] m_son_p;

        if (s.m_son_p == nullptr) {
            m_son_p = nullptr;
        } else {
            m_son_p = new int[11];
            memcpy(m_son_p, s.m_son_p, sizeof(int) * 11);
        }

        return *this;
    }
public:
    void display() {
        for (int i = 0; i < 11; ++i) {
            std::cout << m_son_p[i] << ' ';
        }
        std::cout << std::endl;
    }
};

int main(int argc, char *argv[]) {
    Son s;
    Son s2(s);
    s.display();
    s2.display();

    Son s3;
    s3 = s;
    s3.display();


    return 0;
}