#include <iostream>
#include <vector>

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
    std::vector<int> vec(peoples);
    for (int i = 0; i < peoples; ++i) {
        vec[i] = i;
    }
    int index = 0;
    while (vec.size() > num) {
        for (int i = 0; i < rule - 1; ++i) {
            index = (index + 1) % vec.size(); // 移动rule-1次，一次移动一个
        }
        std::cout << "清除的为：" << vec[index] << "\n";
        vec.erase(vec.begin() + index);
        // index = index % peoples;
        // std::cout << "------------------------------\n";
        // for (const int &val : vec) {
        //     std::cout << val << " ";
        // }
        // std::cout << "\n------------------------------\n";
    }
    std::cout << "剩余的人：\n";
    for (const int &val : vec) {
        std::cout << val << "\n";
    }
    std::cout << "\n";
}