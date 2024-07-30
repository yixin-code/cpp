#include <iostream>
#include <fcntl.h> // open
#include <unistd.h> // write close
#include <string.h>

int main(int argc, char *argv[]) {
    int fd = open("./linux/linux系统编程/进程/FIFO/p_file", O_WRONLY);
    if (fd == -1) {
        perror("open fail");
    }

    write(fd, "hello world", strlen("hello world"));

    close(fd);

    return 0;
}