#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    int flag = fcntl(STDIN_FILENO, F_GETFL); // 拿到原标志位
    if (flag == -1) {
        perror("fcntl f_getfl");
        exit(1);
    }

    if (fcntl(STDIN_FILENO, F_SETFL, flag | O_NONBLOCK) == -1) { // 设置新的标志位
        perror("fcntl f_setfl");
        exit(1);
    }

    ssize_t count   = 0;
    char    buf[20] = {0};

    while (true) {
        count = read(STDIN_FILENO, buf, sizeof(buf));
        if (errno != EAGAIN) {
            std::cout << "非阻塞错误\n";
        }
        if (count > 0) {
            std::cout << buf << "\n";
            break;
        }
        std::cout << "wait input\n";
        sleep(1);
    }
    
    std::cout << "main end\n";

    return 0;
}