#include <iostream>
#include <vector>

class Stack {
public:
    Stack(void);
    ~Stack(void);
public:
    void push(int val);
    void pop();
    int top();
    bool empty();
private:
    std::vector<int> m_data;
};

int main(int argc, char *argv[]) {
    Stack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    while (!stack.empty()) {
        std::cout << stack.top() << std::endl;
        stack.pop();
    }

    return 0;
}

Stack::Stack(void) {}

Stack::~Stack(void) {}

void Stack::push(int val) {
    this->m_data.push_back(val);
}

void Stack::pop() {
    this->m_data.pop_back();
}

int Stack::top() {
    return this->m_data.back();
}

bool Stack::empty() {
    if (this->m_data.empty()) {
        return true;
    }

    return false;
}
