#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char *argv[]) {
    std::vector<int> v = {1, 5, 6, 3, 9};

    std::sort(v.begin(), v.end());

    for (const int &val : v) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    // std::sort(v.begin(), v.end(), std::greater<int>());
    std::sort(v.begin(), v.end(),
        [](int num, int num2) { 
            return num > num2;
        });

    for (const int &val : v) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}