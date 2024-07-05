#include <iostream>
#include <dirent.h>

int main(int argc, char *argv[]) {
    DIR* p_dir = opendir("/home/yixin/Code");
    closedir(p_dir);

    return 0;
}