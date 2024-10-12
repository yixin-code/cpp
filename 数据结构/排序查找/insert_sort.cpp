#include <iostream>
#include <vector>

void insert_sort(std::vector<int> &nums) {
    int size = nums.size();

    for (int i = 1; i < size; ++i) { // 首元素为有序
        int j = i - 1; // 已有序位置

        // nums[j + 1] 为待插入元素
        while (j >= 0 && nums[j] > nums[j + 1]) { // 未有序位置和有序位置逐一比较交换(插入)
            std::swap(nums[j], nums[j + 1]);
            --j;
        }
    }
}

int main(int argc, char *argv[]) {
    std::vector<int> nums = {5, 4, 3, 2, 1};

    insert_sort(nums);

    for (auto num : nums) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}