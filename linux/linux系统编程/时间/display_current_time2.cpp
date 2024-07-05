#include <iostream>
#include <time.h>
#include <string.h>

int main(int argc, char *argv[]) {
    time_t      tt      = time(nullptr);
    char        buf[88] = {0};
    struct tm   p_t;

    memset(&p_t, 0, sizeof(p_t));

    localtime_r(&tt, &p_t);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &p_t);

    std::cout << buf << std::endl;

    return 0;
}