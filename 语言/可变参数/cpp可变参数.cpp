#include <iostream>

void func() {}

template <class T, class...Args>
void func(T element, Args...args) {
    std::cout << element << " ";
    func(args...);
}

int main() {
    func(1, "aaa");

    return 0;
}