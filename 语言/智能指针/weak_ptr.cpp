// weak_ptr不能单独创建需要使用 
// unique_ptr本身就是独占指针 不存在相互依赖的情况
#include <iostream>
#include <memory>

class MyClass {
private:
    int m_num;
    // std::shared_ptr<MyClass> m_sp_ptr;
    std::weak_ptr<MyClass> m_wp_ptr;
public:
    MyClass(int num = 11) : m_num(num) {
        std::cout << "MyClass(int num)" << std::endl;
    }
    ~MyClass() {
        std::cout << "~MyClass()" << std::endl;
    }
public:
    void set_ptr(std::shared_ptr<MyClass> sp) {
        // m_sp_ptr = sp;
        m_wp_ptr = sp;
    }
    void display() {
        std::cout << "m_num: " << m_num << std::endl;
    }
};

int main(int argc, char *argv[]) {
    // 循环依赖导致 不会调用析构函数 可将类中的shared_ptr改为weak_ptr
    // sp sp2 相互依赖
    std::shared_ptr<MyClass> sp(new MyClass);
    std::shared_ptr<MyClass> sp2(new MyClass);
    sp->set_ptr(sp2);
    sp2->set_ptr(sp);
    sp->display();
    sp2->display();

    return 0;
}