#include <iostream>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    // system("cd /home/yixin/Temp"); // system会创建一个新的shell环境，这条语句执行完毕就会关闭该shell
    mkdir("/home/yixin/Temp/aaa", 0755);

    return 0;
}