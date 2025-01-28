// 智能指针，独占指针，使用最多
// 只能由一个指针管理内存
// 超出作用域，内存自动释放
// 不能copy只能move
// unique_ptr.get() 获取原始指针 可同原始指针一样操作
// unique_ptr.release() 释放所有权返回裸指针（原始指针）
// std::move(unique_ptr) 释放所有权转移指针
#include <iostream>
#include <memory>

class MyClass {
private:
    int m_num;
public:
    MyClass(int num = 11) {
        std::cout << "MyClass()" << std::endl;
    }
    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }
public:
    void display() const {
        std::cout << "display" << std::endl;
    }
};

int main(int argc, char *argv[]) {
    std::unique_ptr<MyClass> up(new MyClass);
    std::unique_ptr<MyClass> up2(std::move(up)); // 智能移动不能赋值
    // up = up2; // error
    up = std::move(up2);

    up->display();

    up.get()->display(); // 返回原始指针

    MyClass *p = up.release(); // 释放所有权返回裸指针 指针不再智能
    p->display();
    delete p;

    std::unique_ptr<MyClass[]> up3(new MyClass[5]{1, 2, 3, 4, 5}); // 数组

    return 0;
}