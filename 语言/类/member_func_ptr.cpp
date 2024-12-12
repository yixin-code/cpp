#include <iostream>

class A {
public:
    A(int num) : m_num(num) {}
public:
    void func();
private:
    int m_num;
};

using PA_func = void (A::*) ();

int main(int argc, char *argv[]) {
    PA_func pa_func = &A::func;

    A a(11);

    a.func();
    (a.*pa_func)();

    return 0;
}

void A::func() {
    std::cout << "m_num: " << this->m_num << std::endl;
}