#include <iostream>

void file_cp(char *argv[]);

int main(int argc, char *argv[]) {
    file_cp(argv);

    return 0;
}

void file_cp(char *argv[]) {
    FILE *fp_read = fopen(argv[1], "r");
    if (fp_read == nullptr) {
        perror("14, fopen error");
        exit(1);
    }

    FILE *fp_write = fopen(argv[2], "r");
    if (fp_write == nullptr) {
        perror("20, fopen error");
        exit(1);
    }

    char ch = 0;

    while ((ch = fgetc(fp_read)) != EOF) {
        fputc(ch, fp_write);
    }

    fclose(fp_read);
    fclose(fp_write);
}