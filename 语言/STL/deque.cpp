#include <iostream>
#include <deque>

int main(int argc, char *argv[]) {
    std::deque<int> dq = {1, 2, 3, 4, 5, 6};

    // 增加元素
    dq.push_back(7);
    dq.push_front(0);
    dq.insert(dq.begin() + 2, 9);
    dq.insert(dq.begin(), 9);
    for (const int &val : dq) {
        std::cout << val << " "; // 9 0 1 9 2 3 4 5 6 7
    }
    std::cout << std::endl;

    // 删除元素
    dq.pop_back();
    dq.pop_front();
    dq.erase(dq.begin() + 2);
    dq.erase(dq.begin());
    for (const int &val : dq) {
        std::cout << val << " "; // 1 2 3 4 5 6
    }
    std::cout << std::endl;

    return 0;
}