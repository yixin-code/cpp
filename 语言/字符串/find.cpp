// 返回字符下标
#include <string>
#include <iostream>
int main(int argc, char *argv[]) {
    std::string str = "hello world";

    uint64_t    pos = str.find("world");
    if (pos == std::string::npos) {
        std::cout << "not found" << std::endl;
    } else {
        std::cout << "pos: " << pos << std::endl; // 6 字符下标
    }

    pos = str.find('o');
    if (pos == std::string::npos) {
        std::cout << "not found" << std::endl;
    } else {
        std::cout << "pos: " << pos << std::endl; // 4
    }

    return 0;
}