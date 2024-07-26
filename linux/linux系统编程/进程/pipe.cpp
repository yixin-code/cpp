#include <iostream>
#include <sys/wait.h> // waitpid
#include <unistd.h> // pipe fork close write read
#include <string.h>

int main(int argc, char *argv[]) {
    int fds[2] = {0};
    if (pipe(fds) == -1) {
        perror("pipe fail");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork fail");
        exit(1);
    } else if (pid == 0) {
        close(fds[1]); // 关闭写端

        char buf[20] = {0};

        read(fds[0], buf, 20);

        std::cout << buf << '\n';

        close(fds[0]);

        std::cout << "child end\n";
    } else {
        close(fds[0]); // 关闭读端

        write(fds[1], "hello world", strlen("hello world"));

        waitpid(-1, nullptr, 0);

        close(fds[1]);

        std::cout << "parent end\n";
    }

    return 0;
}