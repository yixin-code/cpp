#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int g_num = 11;

int main()
{
    pid_t pid = fork();

    if (pid == -1) {
        perror("3 fork, ");
        exit(1);
    }

    if (pid == 0) {
        g_num = 22;
        std::cout << "child g_num: " << g_num << ", &g_num: " << &g_num  << std::endl; // 22 0xb050
        g_num = 33;
        std::cout << "child g_num: " << g_num << ", &g_num: " << &g_num  << std::endl; // 33 0xb050
        g_num = 44;
        std::cout << "child g_num: " << g_num << ", &g_num: " << &g_num  << std::endl; // 44 0xb050
    } else if (pid > 0) {
        wait(nullptr);
        std::cout << "parent g_num: " << g_num << ", &g_num: " << &g_num << std::endl; // 11 0xb050
    }

    return 0;
}