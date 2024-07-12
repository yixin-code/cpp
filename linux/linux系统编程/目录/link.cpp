#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (link("/home/yixin/Temp/test", "/home/yixin/Temp/test3") == -1) {
        perror("link fail");
        exit(1);
    }

    return 0;
}