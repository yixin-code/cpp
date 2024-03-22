#include <iostream>

struct People {
    char m_name[1024];
    int m_age;
};

void file_cp(char *argv[]);

int main(int argc, char *argv[]) {
    file_cp(argv);

    return 0;
}

void file_cp(char *argv[]) {
    FILE *fp_rw = fopen(argv[1], "w+"); // 读写
    if (fp_rw == nullptr) {
        perror("13, fopen error");
        exit(1);
    }

    People p {"yixin", 11};
    fprintf(fp_rw, "%s %d", p.m_name, p.m_age);
    fseek(fp_rw, 0, SEEK_SET); // 文件指针恢复到开始位置
    fscanf(fp_rw, "%s%d", p.m_name, &(p.m_age)); // 空白字符会停止读取
    std::cout << "name: " << p.m_name << ", age: " << p.m_age << "\n";

    fclose(fp_rw);
}