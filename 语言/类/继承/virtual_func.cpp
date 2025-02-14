#include <iostream>

class Parent {
public:
    virtual void func() const {
        std::cout << "parent func" << std::endl;
    }
    virtual void func2() const final { // 限定子类从写该函数
        std::cout << "parent func final" << std::endl;
    }
};

class Son : public Parent {
public:
    virtual void func() const override { // override 说明符 表示函数已被重写
        std::cout << "son func" << std::endl;
    }
    // virtual void func2() const override { // 无法从写final函数 error
    //     std::cout << "son func final" << std::endl;
    // }
};

int main(int argc, char *argv[]) {
    Parent *p = new Son();
    p->func();

    Son s;
    Parent &r = s;
    r.func();

    return 0;
}