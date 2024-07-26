#include <iostream>

int main(int argc, char *argv[]) {
    FILE *p_fp = popen("cat ./test", "r");
    if (p_fp == nullptr) {
        perror("popen fail");
        exit(1);
    }

    int ch = 0;
    while ((ch = fgetc(p_fp)) != EOF) {
        std::cout << (char)toupper(ch);
    }

    pclose(p_fp);

    return 0;
}