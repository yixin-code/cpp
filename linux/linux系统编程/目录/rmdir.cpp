#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    rmdir("/home/yixin/Temp/bbb");
    rmdir("/home/yixin/Temp/bb"); // 无法删除文件

    return 0;
}