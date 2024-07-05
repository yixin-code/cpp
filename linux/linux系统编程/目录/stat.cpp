#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <iomanip>

int main(int argc, char *argv[]) {
    struct stat st;
    memset(&st, 0, sizeof(st));

    stat("/home/yixin/Code/cpp", &st);
    if (S_ISDIR(st.st_mode)) { // 是目录
        std::cout << "cpp is dir\n";
        std::cout << st.st_size << '\n'; // 文件大小

        time_t      tt = st.st_mtim.tv_sec; // 最后修改时间
        struct tm   t;
        localtime_r(&tt, &t);
        std::cout << t.tm_year + 1990 << "-"
            << std::setw(2) << std::setfill('0') << t.tm_mon + 1 << "-"
            << std::setw(2) << std::setfill('0') << t.tm_mday << " "
            << std::setw(2) << std::setfill('0') << t.tm_hour << ":"
            << std::setw(2) << std::setfill('0') << t.tm_min << ":"
            << std::setw(2) << std::setfill('0') << t.tm_sec << '\n';
    }

    if (S_ISREG(st.st_mode) == false) { // 是文件
        std::cout << "cpp not file\n";
        std::cout << st.st_size << '\n'; // 文件大小

        time_t      tt      = st.st_mtim.tv_sec; // 最后修改时间
        struct tm   *p_t    = localtime(&tt);
        char        buf[80] = {0};

        strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", p_t);
        std::cout << buf << "\n";
    }

    return 0;
}