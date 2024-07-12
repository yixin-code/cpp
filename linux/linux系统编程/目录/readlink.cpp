#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buf[1024] = {0};
    const char * path = "/proc/self/exe";

    if (readlink(path, buf, sizeof(buf) - 1) == -1) {
        perror("readlink fail");
        exit(1);
    }

    std::cout << buf << "\n";

    return 0;
}