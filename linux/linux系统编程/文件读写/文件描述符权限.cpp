#include <iostream>
#include <fcntl.h>
#include <unistd.h>

//  O_ACCMODE->0x3->0011(表示读写执行) o_rdonly->0x0->0000 O_WRONLY->0x1->0001 O_RDWR->0x2->0010
int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("eg: ./a.out 1");
        exit(1);
    }

    int flag = 0;
    // if ((flag = fcntl(std::stoi(argv[1]), F_GETFL)) == -1) {
    // if ((flag = fcntl(std::stoi(argv[1]), F_GETFL)) == -1) {
    if ((flag = fcntl(atoi(argv[1]), F_GETFL)) == -1) {
        perror("fcntl f_getfl");
        exit(1);
    }

    std::cout << std::hex << "hex: " << flag << "\n"; // 402->0100 0000 0010
    std::cout << std::dec << "dec: " << flag << "\n"; // 1024
    // std::cout << "O_WRONLY: " << O_WRONLY << "\n"; // 1
    if (flag & O_WRONLY) {
        std::cout << "exist O_WRONLY: " << O_WRONLY << "\n"; // 1
    }
    if (flag & O_RDWR) {
        std::cout << "exist O_RDWR: " << O_RDWR << "\n"; // 2
    }
    if (flag & O_APPEND) {
        std::cout << "exist O_APPEND: " << O_APPEND << "\n"; // 1024
    }

    std::cout << "O_ACCMODE: " << O_ACCMODE << "\n"; // 3

    return 0;
}