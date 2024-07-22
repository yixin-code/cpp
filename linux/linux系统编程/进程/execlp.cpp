#include <iostream>
#include <unistd.h> // execlp

int main(int argc, char *argv[]) {
    // if (execlp("ls", "ls -la", nullptr) == -1) { // error 并不会正确解析ls -la
    // if (execlp("ls", "ls", "-l", "-a", nullptr) == -1) {
    if (execlp("ls", "ls", "-la", nullptr) == -1) {
        perror("execlp fail");
        exit(1);
    }

    return 0;
}