#include <iostream>
#include <vector>

int main() {
    std::vector<int> v_i_vec    {1, 2, 3, 4, 5, 6, 7};
    std::vector<int> v_i_vec2   {3, 4, 5, 6, 7, 8};
    std::vector<int> v_i_vec3   {5, 6, 7, 8, 9};
    std::vector<int> v_i_res;

    int i = 0;
    int j = 0;
    int k = 0;

    while (i != (v_i_vec.size() - 1) && (v_i_vec2.size() - 1) && (v_i_vec3.size() - 1)) {
        if (v_i_vec[i] == v_i_vec2[j] == v_i_vec3[k]) {
            v_i_res.push_back(v_i_vec[i]);
            ++i;
            ++j;
            ++k;
        } else if ()
    }

    return 0;
}