#include <iostream>
#include <unistd.h>
#include <signal.h>

int main()
{
    pid_t pid;
    pid = fork();
    // 失败返回一个负数，等于0子进程pid，大于0为父进程
    if (pid < 0)
    {
        exit(1);
    }
    else if (pid == 0)
    { // 子进程
        std::cout << "son process pid: " << getpid() << ", ppid: " << getppid() << "\n";
    }
    else { // 父进程
        std::cout << "father process pid: " << getpid() << ", son pid: " << pid << "\n";
        sleep(1);
    }

    std::cout << "main end\n";

    return 0;
}