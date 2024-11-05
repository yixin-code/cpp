#include <iostream>
#include <vector>

void merge(std::vector<int> &nums, int left, int mid, int right) {
    // 两个元素时 left = 0, mid = 0, right = 1
    // mid = 0, left = 0, left_size = 1
    int left_size = mid - left + 1; // 左边临时数组长度
    // right = 1, mid = 0, right_size = 1
    int right_size = right - mid; // 右边临时数组长度

    std::vector<int> left_arr(left_size);
    std::vector<int> right_arr(right_size);

    for (int i = 0; i < left_size; ++i) {
        left_arr[i] = nums[left + i];
    }
    for (int i = 0; i < right_size; ++i) {
        right_arr[i] = nums[mid + 1 + i];
    }

    int i = 0;
    int j = 0;
    int k = left;

    // 小于放入左边元素,否则放入右边元素
    while (i < left_size && j < right_size) {
        if (left_arr[i] < right_arr[j]) {
            nums[k++] = left_arr[i++];
        } else {
            nums[k++] = right_arr[j++];
        }
    }

    // 如果存在剩余元素，拷贝剩余元素
    while (i < left_size) {
        nums[k++] = left_arr[i++];
    }
    while (j < right_size) {
        nums[k++] = right_arr[j++];
    }
}

void merge_sort(std::vector<int> &nums, int left, int right) {
    if (left >= right) { // 一个数不需要排序
        return;
    }

    int mid = (left + right) / 2; // 拿到中间点

    // 两个元素时 left = 0, mid = 0, right = 1
    // left = 0, mid = 0
    merge_sort(nums, left, mid); // 左边排序
    // mid = 1 , right = 1
    merge_sort(nums, mid + 1, right); // 右边排序 

    merge(nums, left, mid, right); // 合并
}
int main(int argc, char *argv[]) {
    // std::vector<int> nums{8, 7, 6, 5, 4, 3, 2, 1};
    std::vector<int> nums{8, 7, 6, 5, 4, 3, 2};

    merge_sort(nums, 0, nums.size() - 1);

    for (const int &val : nums) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}