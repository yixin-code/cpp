#include <iostream>
#include <utime.h>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
    struct utimbuf time_buf;
    memset(&time_buf, 0, sizeof(time_buf));

    if (utime("/home/yixin/Temp/nginx", &time_buf) == -1) {
        perror("utime fail");
        exit(1);
    }

    time_buf.actime     = time(nullptr); // 访问时间
    time_buf.modtime    = time(nullptr); // 修改时间

    return 0;
}