#include <iostream>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == -1) {
        perror("8, fork");
        exit(1);
    }

    if (pid == 0) {
        int num = 11;

        while (num > 0) {
            std::cout << "child process, pid: " << getpid() << ", ppid: " << getppid() << "\n";
            sleep(1);
            --num;
        }

        std::cout << "child process end\n";

        exit(5);
    } else if (pid > 0) {
        int stat = 0;

        waitpid(-1, &stat, 0); // 阻塞等待所有子进程结束

        std::cout << "parent process, pid: " << getpid() << ", ppid: " << getppid() << "\n";

        if (WIFEXITED(stat)) { // 正常退出
            std::cout << "status code: " << WEXITSTATUS(stat) << "\n"; // 返回值 5
        } else if (WIFSIGNALED(stat)) { // 信号退出
            std::cout << "terminated code: " << WTERMSIG(stat) << "\n"; // 信号码
        }

        std::cout << "parent precess end\n";
    }

    return 0;
}