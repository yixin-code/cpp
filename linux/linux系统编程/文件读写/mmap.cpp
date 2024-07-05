#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char *argv[]) {
    int write_fd = open("./test.txt", O_RDWR); // 需要可读可写 否则mmap -> permission denied
    if (write_fd == -1) {
        perror("open fail");
        exit(1);
    }

    // int *p = (int*)mmap(nullptr, 9, PROT_WRITE, MAP_SHARED, write_fd, 0);
    char *p = (char*)mmap(nullptr, 9, PROT_WRITE, MAP_SHARED, write_fd, 0);
    if (p == MAP_FAILED) {
        perror("mmap fail");
        close(write_fd);
        exit(1);
    }

    // 文件中数据 123456789 -> DCBA56789
        // 41(A)高位，9高地址 小端低存低高存高
    // p[0] = 0x41424344;

    // 文件中数据 DCBA56789 -> abcd56789
    strcpy(p, "abcd");

    munmap((void*)p, 9);
    close(write_fd);

    return 0;
}