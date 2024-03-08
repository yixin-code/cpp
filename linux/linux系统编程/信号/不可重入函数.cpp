#include <iostream>
#include <signal.h>
#include <unistd.h>

int g_num = 11;

void func(int sig) {
    g_num = sig;
    std::cout << "signal: " << sig << ", " << "g_num: " << g_num << "\n";
}

int main() {
    signal(SIGINT, func); // 会改变g_num值

    while (true) {
        g_num = 22;
        sleep(1);
        std::cout << "g_num: " << g_num << ", wait...\n";
    }

    return 0;
}