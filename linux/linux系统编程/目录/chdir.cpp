#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buf[256] = {0};

    getcwd(buf, sizeof(buf));
    std::cout << "change before: " << buf << '\n';

    chdir("/home/yixin/Temp");

    getcwd(buf, sizeof(buf));
    std::cout << "change after: " << buf << '\n';

    return 0;
}