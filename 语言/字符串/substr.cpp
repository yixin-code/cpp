// str2 = str.substr(pos); 截取到字符串结尾
// str3 = str.substr(pos, 2); 截取2个字符

#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::string str = "hello world";
    std::string str2;
    std::string str3;
    uint64_t    pos = str.find("world");
    
    if (pos == std::string::npos) {
        std::cout << "not found" << std::endl;
    } else {
        str2 = str.substr(pos);
        std::cout << "str2: " << str2 << std::endl; // world
        str3 = str.substr(pos, 2);
        std::cout << "str3: " << str3 << std::endl; // wo
    }

    return 0;
}