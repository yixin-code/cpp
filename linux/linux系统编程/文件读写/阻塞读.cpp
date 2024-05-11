#include <iostream>
#include <fcntl.h> // open

int main(int argc, char *argv[]) {
    int fd = open("/dev/tty", O_RDONLY | ); // 终端 对其读写

    return 0;
}