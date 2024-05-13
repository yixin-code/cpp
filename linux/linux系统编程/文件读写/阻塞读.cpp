#include <iostream>
#include <fcntl.h> // open
#include <unistd.h> // read write
#include <string.h>

int main(int argc, char *argv[]) {
    int fd = open("/dev/tty", O_RDONLY | O_NONBLOCK); // 终端 非阻塞读终端
    if (fd == -1) {
        perror("5 open");
        exit(1);
    }

    char buf[1024] = {0};
    int count = 0;
    while (true) { // 不断的从终端读
        count = read(fd, buf, sizeof(buf));
        if (count != -1) {
            std::cout << "读取成功:\n";
            write(STDOUT_FILENO, buf, count);
            break;
        }
        if (errno != EAGAIN) { //非阻塞错误返回-1 errno设置为 EAGAIN == EWOULDBLOCK == 11
            perror("不是非阻塞错误 报错退出");
            exit(1);
        } else { // 是非阻塞错误导致的 开始循环
            write(STDOUT_FILENO, "未读到信息\n", strlen("未读到信息\n"));
        }
        sleep(1);
    }

    close(fd);

    return 0;
}