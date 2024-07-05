#include <iostream>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR*    p_dir       = opendir("/home/yixin/Code/cpp");
    dirent* p_dirent    = nullptr;

    while ((p_dirent = readdir(p_dir)) != nullptr) {
    // while (true) {
        // p_dirent = readdir(p_dir);
        // if (p_dirent == nullptr) {
        //     break;
        // }

        if (p_dirent->d_type == DT_DIR) {
            std::cout << p_dirent->d_name << " ";
        }

        if (p_dirent->d_type == DT_REG) {
            std::cout << p_dirent->d_name << " ";
        }
    }
    std::cout << '\n';

    closedir(p_dir);

    return 0;
}