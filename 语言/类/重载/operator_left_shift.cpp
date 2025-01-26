// 重载左移运算符
#include <iostream>
#include <vector>

std::ostream &operator<<(std::ostream &os, const std::vector<int> &v) {
    for (const int &val : v) {
        os << val << " ";
    }

    return os;
}

int main(int argc, char *argv[]) {
    std::vector<int> v{1, 2, 3, 3, 4, 5};

    std::cout << v << std::endl;

    return 0;
}