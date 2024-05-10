#include <fcntl.h>
#include <sys/stat.h>
#include <iostream>

int main(int argc, char *argv[]) {
    // 读写方式打开文件不存在创建文件存在截断
        // 未umask权限为rwxr-xr-x
    mode_t uk = umask(0); // 添加umask后会是rwxrwxrwx
    int fd = open("./umask.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
    if (fd == -1) {
        perror("6 open");
        exit(1);
    }
    umask(uk);

    return 0;
}