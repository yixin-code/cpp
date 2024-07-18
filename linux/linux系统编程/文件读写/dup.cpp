#include <iostream>
#include <string.h>
#include <fcntl.h> // open
#include <unistd.h> // write
// #include <sys/stat.h> // umask

int main(int argc, char *argv[]) {
    int fd = 0;
    // umask(0);

    if ((fd = open("./test", O_WRONLY | O_CREAT, 0644)) < 0) {
        perror("open fail");
        exit(1);
    }

    int copy_fd = dup(STDOUT_FILENO); // 复制文件描述符 copy_fd -> STDOUT_FILENO

    dup2(fd, STDOUT_FILENO); // 重定向 STDOUT_FILENO -> fd

    close(fd);

    write(STDOUT_FILENO, "hello world", strlen("hello world"));

    dup2(copy_fd, STDOUT_FILENO); // STDOUT_FILENO -> copy_fd

    close(copy_fd);

    write(STDOUT_FILENO, "hello world", strlen("hello world"));

    return 0;
}