#include <iostream>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    FILE *p_fp = popen("./toupper", "w");
    if (p_fp == nullptr) {
        perror("popen fail");
        exit(1);
    }

    fputs("hello world", p_fp);

    pclose(p_fp);

    return 0;
}