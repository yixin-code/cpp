#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (chown("/home/yixin/Temp/aaa", 1001, 1001) == -1) {
        perror("chown fail");
        exit(1);
    }

    return 0;
}