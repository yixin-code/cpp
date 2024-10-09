#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
    std::string str;
    int sum = 0;

    std::cin >> str;

    for (std::string::iterator it = str.begin(); it != str.end(); ++it) {
        sum = sum * 10 + (*it - '0');
    }

    std::cout << "sum: " << sum << std::endl;

    return 0;
}