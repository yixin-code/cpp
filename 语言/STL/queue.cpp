#include <iostream>
#include <queue>

int main(int argc, char *argv[]) {
    // std::queue<int> q{1, 2, 3, 4, 5}; // error
    std::queue<int> q;
    q.push(1);  // 队尾插入元素
    q.emplace(2); // 队尾插入元素
    std::cout << q.front() << '\n'; // 1队头元素
    std::cout << q.back() << '\n'; // 2队尾元素
    std::cout << q.size() << '\n'; // 2元素个数
    q.pop(); // 删除对头元素
    if (!q.empty()) { // 空返回真
        std::cout << "no empty\n";
    }

    return 0;
}