#include <iostream>
#include <vector>

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6};
    std::vector<int> vec2{4, 5, 6, 7, 8};
    std::vector<int> v_res;

    int i = 0;
    int j = 0;

    while (i != vec.size() || j != vec2.size()) {
        if (vec[i] == vec2[j]) {
            ++i;
            ++j;
        } else if (vec[i] < vec2[j]) {
            ++i;
        }
    }

    return 0;
}
