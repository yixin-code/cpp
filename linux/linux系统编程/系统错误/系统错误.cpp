#include <iostream>
#include <cerrno>
#include <fstream>
#include <cstring>

int main() {
    std::ifstream fin;
    fin.open("a.txt");
    std::cout << "errno: " << errno << strerror(errno) << "\n";

    return 0;
}