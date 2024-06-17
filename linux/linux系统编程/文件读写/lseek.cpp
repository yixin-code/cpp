#include <iostream>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int fd = 0;
    if ((fd = open("lseek.txt", O_CREAT | O_RDWR, 0664)) == -1) {
        perror("open lseek fail");
        exit(1);
    }

    write(fd, "123456789", 9);

    // 返回距离文件开始处的位置 == ftell
        // 位置是0开始的，seek_end 是在最后字符后
    int pos = lseek(fd, SEEK_SET, 0);
    std::cout << "pos: " << pos << "\n"; // 0
    char ch = 0;
    read(fd, &ch, 1);
    std::cout << ch << "\n"; // 1
    pos = lseek(fd, 2, SEEK_CUR);
    read(fd, &ch, 1);
    std::cout << ch << "\n"; // 4
    std::cout << "pos: " << pos << "\n"; // 3
    pos = lseek(fd, 0, SEEK_END);
    std::cout << "pos: " << pos << "\n"; // 9

    return 0;
}