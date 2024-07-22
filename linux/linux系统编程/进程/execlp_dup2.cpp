#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        std::cout << "eg ./a.out test test2\n";
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open read fail");
        exit(1);
    }

    dup2(fd, STDIN_FILENO);

    close(fd);

    fd = open(argv[2], O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open write fail");
        exit(1);
    }

    dup2(fd, STDOUT_FILENO);

    close(fd);

    if (execl("./toupper", "./toupper", nullptr) == -1) {
        perror("execl fail");
        exit(1);
    }

    return 0;
}