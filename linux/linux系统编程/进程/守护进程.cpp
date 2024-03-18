#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int daemon_process();

int main() {
    if (daemon_process()) {
        perror("daemon process create error");
        exit(1);
    }

    while (true) {
        std::cout << "daemon process\n";
        sleep(1);
    }

    return 0;
}

int daemon_process() {
    switch (fork()) { // 创建子进程以便调用setsid()
        case -1: {
            perror("19, fork error");
            return -1;
        }
        case 0: { // 子进程，脱离终端会话
            if (setsid() == -1) { // 创建新会话进程成为改组组长，进程为当前进程组组长时创建失败
                perror("24, setsid error");
                exit(1);
            }

            umask(0); // 解除文件权限限制
            int fd = open("/dev/null", O_RDWR);
            if (fd == -1) {
                perror("31, open error");
                exit(1);
            }

            if (dup2(fd, STDIN_FILENO) == -1) { // 复制一份fd，将标准输入赋值给复制的fd
                perror("37, dup2 error");
                exit(1);
            }

            if (dup2(fd, STDOUT_FILENO) == -1) {
                perror("42, dup2 error");
                exit(1);
            }

            close(fd); // 关闭fd，释放文件描述符，避免造成资源浪费

            break;
        }
        default: { // 父进程直接退出
            exit(0);
        }
    }

    return 0;
}