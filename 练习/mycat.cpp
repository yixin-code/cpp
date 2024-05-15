#include <iostream>
#include <string.h>
#include <fstream>

int main(int argc, char *argv[]) {
    std::ifstream fin(argv[1]);
    if (!fin.is_open()) {
        perror("6 fin");
        exit(1);
    }
    
    char buf[1024] = {0};
    while (fin.getline(buf, 1024)) {
        std::cout << buf << '\n';
        memset(buf, 0, 1024);
    }

    fin.close();

    return 0;
}