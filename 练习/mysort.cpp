// 一个基准 比基准小的放左边 比基准大的放右边
#include <iostream>
#include <vector>
#include <algorithm>

void quick_sort(std::vector<int> &v, int l, int r) {
    if (l >= r) { // 递归终止条件
        return;
    }

    int temp_l = l;
    int temp_r = r;
    int temp = v[l]; // 基准

    while (temp_l < temp_r) { // l == r 时退出
        // 需要先从右边开始比较
        while (temp <= v[temp_r] && temp_l < temp_r) { // 右边找出小于基准的值 哨兵向左移动
            --temp_r;
        }
        while (temp >= v[temp_l] && temp_l < temp_r) { // 左边找出大于基准的值 哨兵向右移动
            ++temp_l;
        }
        std::swap(v[temp_l], v[temp_r]); // 将左边大于基准 和 右边小于基准的值 进行交换
    }
    // 此时两个哨兵的位置相同 和基准交换 使基准值到准确位置
    v[l] = v[temp_l];
    v[temp_l] = temp;

    quick_sort(v, l, temp_l - 1); // 左边
    quick_sort(v, temp_l + 1, r); // 右边
}

int main(int argc, char *argv[]) {
    std::vector<int> v = {3, 2, 55, 11, 66, 2, 9, 9, 11};

    quick_sort(v, 0, v.size() - 1);

    for (const int &i : v) {
        std::cout << i << " ";
    }

    return 0;
}