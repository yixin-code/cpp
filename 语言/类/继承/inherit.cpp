#include <iostream>

// private 可以继承 但是子类无法访问
// protected 子类可以正常访问
class Parent {
private:
    int m_num;
public:
    Parent(int num = 22) : m_num(num) {
        std::cout << "Parent(int num)" << std::endl;
    }
    ~Parent() {
        std::cout << "~Parent()" << std::endl;
    }
public:
    void display_parent() const {
        std::cout << "m_num: " << m_num << std::endl;
    }
};

// 权限决定对外访问
// private 继承 父类的public和protected都是私有的
// protected 继承 父类的public和protected都是保护的
// public 继承 父类的public是公有的 protected是保护
class Son : public Parent {
private:
    int m_num;
public:
    Son(int num) : Parent(), m_num(num) {
        std::cout << "Son(int num)" << std::endl;
    }
    ~Son() {
        std::cout << "~Son()" << std::endl;
    }
public:
    void display_son() const {
        std::cout << "m_num: " << m_num << std::endl;
    }
};

int main(int argc, char *argv[]) {
    Son s(11); // 会先构造父类再构造子类
    s.display_parent();
    s.display_son();

    return 0;
}