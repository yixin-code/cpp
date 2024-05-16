#include <iostream>
#include <string.h>
#include <fstream>

int main(int argc, char *argv[]) {
    std::ifstream fin(argv[1]);
    if (!fin.is_open()) {
        perror("fin");
        exit(1);
    }

    std::ofstream fout(argv[2]);
    if (!fout.is_open()) {
        perror("fout");
        exit(1);
    }

    constexpr int32_t DATA_MAX_LEN = 1024;
    char buf[DATA_MAX_LEN] = {0};

    // fin.read(buf, DATA_MAX_LEN);
    // fout.write(buf, strlen(buf));
    // std::cout << buf << std::endl;
    // std::cout << fin.gcount() << std::endl;

    while (fin.getline(buf, DATA_MAX_LEN)) {
        fout << buf << std::endl;
        // std::cout << buf << std::endl;
        // fout.write(buf, strlen(buf));
        memset(buf, 0, DATA_MAX_LEN);
    } 

    fin.close();
    fout.close();

    return 0;
}