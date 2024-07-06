#include <iostream>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (chmod("/home/yixin/Temp/aaa", 0777) == -1) {
        perror("chomd fail");
        exit(1);
    }

    return 0;
}