#include <iostream>
#include <unistd.h> // fork
#include <sys/wait.h> // waitpid

int main(int argc, char *argv[]) {
    pid_t pid = 0;

    for (int i = 0; i < 10; ++i) {
        pid = fork();

        if (pid == 0) {
            std::cout << "child " << i + 1 << ": " << getpid() << ", " << getppid() << '\n';
            exit(0); // 该子进程执行完退出，由父进程继续创建子进程
        }
    }

    std::cout << "parent: "  << getpid() << "\n";
    waitpid(-1, nullptr, 0);

    return 0;
}