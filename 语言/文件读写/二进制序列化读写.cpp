#include <iostream>
#include <string.h>

void file_cp(char *argv[]);

int main(int argc, char *argv[]) {
    file_cp(argv);

    return 0;
}

void file_cp(char *argv[]) {
    FILE *fp_read = fopen(argv[1], "rb");
    if (fp_read == nullptr) {
        perror("14, fopen error");
        exit(1);
    }

    FILE *fp_write = fopen(argv[2], "wb");
    if (fp_write == nullptr) {
        perror("20, fopen error");
        exit(1);
    }

    char buf[1024] = {0};
    while (fread(buf, 1, sizeof(buf), fp_read)) { // 返回读到的字符数
        fwrite(buf, 1, strlen(buf), fp_write);
        memset(buf, 0, sizeof(buf));
    }

    fclose(fp_read);
    fclose(fp_write);
}