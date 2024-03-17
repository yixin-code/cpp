#include <iostream>
#include <unistd.h>
#include <fcntl.h>

int daemon_process();

int main() {
    if (daemon_process()) {
        perror("daemon process create error");
        exit(1);
    }

    return 0;
}

int daemon_process() {
    
}