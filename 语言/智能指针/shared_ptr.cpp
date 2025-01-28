// sp = nullptr; // 同样会释放掉资源
// 共享指针又称计数指针
// 与uniptr不同是可以复制，shared中有计数器，复制+1，销毁-1(use_count)
#include <iostream>
#include <memory>

class MyClass {
private:
    int m_num;
public:
    MyClass(int num = 11) : m_num(num) {
        std::cout << "MyClass(int num = 11)" << std::endl;
    }
    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }
public:
    void display() const {
        std::cout << "m_num: " << m_num << std::endl;
    }
};

int main(int argc, char *argv[]) {
    std::shared_ptr<MyClass> sp(new MyClass(33));
    sp->display();
    sp.get()->display();
    std::cout << "count: " << sp.use_count() << std::endl; // 1

    std::shared_ptr<MyClass> sp2 = sp;
    std::cout << "count: " << sp.use_count() << std::endl; // 2
    sp2 = nullptr;
    std::cout << "count: " << sp.use_count() << std::endl; // 1
    sp = nullptr; // 同样会释放掉资源

    std::cout << "yixin" << std::endl; // 会在析构函数之后输出

    return 0;
}