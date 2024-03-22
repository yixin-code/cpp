#include <iostream>
#include <list>

void joseph(int peoples, int rule, int num = 0);

int main()
{
    joseph(10, 3);

    return 0;
}

// peoples 总人数
// rule 规则
// num 剩余人数
void joseph(int peoples, int rule, int num)
{
    std::list<int> l(peoples);
    std::list<int>::iterator it = l.begin();
    int temp = 0;
    for (std::list<int>::iterator it = l.begin(); it != l.end(); ++it, ++temp) {
        *it = temp;
    }

    while (l.size() > num) {
        for (int i = 0; i < rule - 1; ++i) {
            it = std::next(it);
            if (it == l.end()) {
                std::advance(it, 1);
            }
        }
        std::cout << "清除的为：" << *it << "\n";
        it = l.erase(it);
        // index = index % peoples;
        // std::cout << "------------------------------\n";
        // for (const int &val : l) {
        //     std::cout << val << " ";
        // }
        // std::cout << "\n------------------------------\n";
    }
    std::cout << "剩余的人：\n";
    for (const int &val : l) {
        std::cout << val << "\n";
    }
    std::cout << "\n";
}