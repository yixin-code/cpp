#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buf[256] = {0};
    getcwd(buf, sizeof(buf));
    std::cout << buf << "\n";

    return 0;
}