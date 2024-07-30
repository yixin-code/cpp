#include <iostream>
#include <fcntl.h> // open
#include <unistd.h> // read

int main(int argc, char *argv[]) {
    int fd = open("./linux/linux系统编程/进程/FIFO/p_file", O_RDONLY);
    if (fd == -1) {
        perror("open fail");
    }

    char buf[20] = {0};
    read(fd, buf, 20);

    std::cout << buf << '\n';

    close(fd);

    return 0;
}