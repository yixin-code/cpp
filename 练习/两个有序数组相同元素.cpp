#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6};
    std::vector<int> vec2{4, 5, 6, 7, 8};
    std::vector<int> v_res;

    int i = 0;
    int j = 0;

    while (i != (vec.size() - 1) && j != (vec2.size() - 1)) {
        if (vec[i] == vec2[j]) {
            v_res.push_back(vec[i]);
            ++i;
            ++j;
        } else if (vec[i] < vec2[j]) {
            ++i;
        } else if (vec[i] > vec2[j]) {
            ++j;
        }
    }

    for (const int &val : v_res) {
        std::cout << val << " ";
    }
    std::cout << "\n";

    return 0;
}
