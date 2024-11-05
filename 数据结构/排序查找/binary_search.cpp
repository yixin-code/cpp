#include <iostream>
#include <vector>

int binary_search(std::vector<int> &nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) { // 一个元素时也需要查找
        int mid = (left + right) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) { // 大于中间元素，在右边查找
            left = mid + 1;
        } else { // 小于中间元素，在左边查找
            right = mid - 1;
        }
    }

    return -1;
}

int main(int argc, char *argv[]) {
    // std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> nums{1, 2, 3, 4, 5, 6, 7, 8, 9};

    // std::cout << binary_search(nums, 5) << std::endl;
    std::cout << binary_search(nums, 11) << std::endl;

    return 0;
}