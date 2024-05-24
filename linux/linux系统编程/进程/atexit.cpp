#include <iostream>
#include <unistd.h> // fork

void func() {
    std::cout << "clean\n";
}

int main(int argc, char *argv[]) {
    std::cout << "main strat\n";

    pid_t pid = fork();

    if (pid > 0) {
        std::cout << "father process exit\n";
        exit(1);
    }

    if (pid == 0) {
        atexit(func);
        std::cout << "son process start\n";
        std::cout << "son process exit\n";
    }

    std::cout << "main end\n";

    return 0;
}