#include <iostream>
#include <fcntl.h> // open

int main(int argc, char *argv[]) {
    int fd = open("/dev/tty", O_RDONLY | O_NONBLOCK); // 终端 非阻塞读终端
    if (fd == -1) {
        perror("5 open");
        exit(1);
    }

    return 0;
}