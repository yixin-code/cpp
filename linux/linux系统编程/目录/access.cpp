#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (access("/home/yixin/Code/cpp", F_OK) == 0) {
        std::cout << "文件存在\n";
    }

    if (access("/home/yixin/Code/cpp", R_OK) == 0) {
        std::cout << "文件可读\n";
    }

    if (access("/home/yixin/Code/cpp", W_OK) == 0) {
        std::cout << "文件可写\n";
    }

    if (access("/home/yixin/Code/cpp", X_OK) == 0) {
        std::cout << "文件可执行\n";
    }

    return 0;
}