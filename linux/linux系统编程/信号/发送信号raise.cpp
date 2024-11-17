#include <iostream>
#include <signal.h>

int main(int argc, char *argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        while (true) {
            std::cout << "child process" << std::endl;
            sleep(1);
        }
    } else {
        
    }

    return 0;
}