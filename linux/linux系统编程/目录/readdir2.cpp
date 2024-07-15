#include <iostream>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

bool show_dir(const char *dir_name) {
    DIR *p_dir = opendir(dir_name);
    if (p_dir == nullptr) {
        std::cout << "opendir fail" << '\n';
        return false;
    }

    char buf[1024] = {0};
    struct dirent *p_dirent = nullptr;
    while((p_dirent = readdir(p_dir)) != nullptr) {
        if ((strcmp(p_dirent->d_name, ".") == 0) || (strcmp(p_dirent->d_name, "..") == 0)) {
            continue;
        }

        std::cout << p_dirent->d_name << "\t";

        if (p_dirent->d_type == DT_DIR) {
            sprintf(buf, "%s/%s", dir_name, p_dirent->d_name);
            // std::cout << dir_name << '\n';
            show_dir(buf);
        }

        memset(buf, 0, sizeof(1024));
    }

    return true;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        perror("eg: ./a.out path");
        exit(1);
    }

    show_dir(argv[1]);

    std::cout << '\n';

    return 0;
}