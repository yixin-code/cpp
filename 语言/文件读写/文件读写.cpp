#include <iostream>
#include <fstream>
#include <assert.h>

void file_cp(char *argv[]);
void file_cp2(char *argv[]);

int main(int argc, char *argv[]) {
    file_cp(argv);
    // file_cp2(argv);

    return 0;
}

void file_cp(char *argv[]) {
    std::ifstream fin(argv[1]);
    assert(fin.is_open());

    std::ofstream fout(argv[2]);
    assert(fout.is_open());

    char buf[1024] = {0};
    while (fin >> buf) { // 不能读取空白字符
        fout << buf << std::endl;
    }

    fin.close();
    fout.close();
}

void file_cp2(char *argv[]) {
    std::ifstream fin(argv[1]);
    assert(fin.is_open());

    std::ofstream fout(argv[2]);
    assert(fout.is_open());

    char buf[1024] = {0};
    while (fin.getline(buf, sizeof(buf))) { // 不会读取换行符
        fout << buf << std::endl;
    }

    fin.close();
    fout.close();
}