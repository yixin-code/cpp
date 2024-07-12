#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (truncate("/home/yixin/Temp/test", 100) == -1) {
        perror("truncate fail");
        exit(1);
    }

    return 0;
}