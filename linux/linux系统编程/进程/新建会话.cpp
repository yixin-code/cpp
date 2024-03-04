#include <iostream>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("11, fork error");
    }
    else if (pid > 0) {
        while (true) {
            std::cout << getpid() << " -- " << getpgid(0) << ", father wait...\n";
            sleep(1);
        }
    }
    else if (pid == 0) {
        setsid(); // 新建会话，并成为进程组组长
        while (true) {
            std::cout << getpid() << " -- " << getpgid(0) << ", son wait...\n";
            sleep(1);
        }
    }

    std::cout << "main end" << std::endl;

    return 0;
}
