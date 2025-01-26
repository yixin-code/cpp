#include <iostream>
#include <set>

class Comp {
private:
    bool m_flag;
public:
    Comp(bool flag = true) : m_flag(flag) {}
public:
    bool operator()(int num, int num2) {
        if (m_flag) {
            return num < num2;
        } else {
            return num > num2;
        }
    }
};

int main(int argc, char *argv[]) {
    std::set<int, Comp> s{3, 4, 1, 2, 5, 23, 53, 99, 22, 33, 8, 9};

    for (const int &val : s) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    std::set<int, Comp> s2(Comp(false));
    s2.insert(s.begin(), s.end());

    for (const int &val : s2) {
        std::cout << val << " ";
    }
    std::cout << std::endl;

    return 0;
}