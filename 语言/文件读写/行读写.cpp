#include <iostream>

void file_cp(char *argv[]);

int main(int argc, char *argv[])
{
    file_cp(argv);

    return 0;
}

void file_cp(char *argv[]) {
    FILE *fp_read = fopen(argv[1], "r");
    if (fp_read == nullptr)
    {
        perror("6, fopen error");
        exit(1);
    }

    FILE *fp_write = fopen(argv[2], "w");
    if (fp_write == nullptr)
    {
        perror("12, fopen error");
        exit(1);
    }

    char buf[1024] = {0};
    while (fgets(buf, 1024, fp_read) != nullptr) {
        fputs(buf, fp_write);
    }

    fclose(fp_read);
    fclose(fp_write);
}