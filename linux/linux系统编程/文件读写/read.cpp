#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    char buf[11] = {0};
    ssize_t count = read(STDIN_FILENO, buf, 11); // 输入abcd
    std::cout << "count: " << count << ", " << buf; // 输出5 abcd换行
    write(STDOUT_FILENO, buf, count); // 输出abcd换行

    return 0;
}