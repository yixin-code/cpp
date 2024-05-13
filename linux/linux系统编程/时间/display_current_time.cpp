#include <iostream>
#include <sys/time.h> // gettimeofday
#include <iomanip>

int main(int argc, char *argv[]) {
    timeval tv;
    tm t;
    gettimeofday(&tv, nullptr); // 获取当前时间得到1970-01-01至今的秒和以过去的微妙
    localtime_r(&tv.tv_sec, &t); // 线程安全函数
    // time_t tt = time(nullptr);
    // localtime_r(&tt, &t); // 线程安全函数
    std::cout << t.tm_year + 1900 << "-"
        << std::setw(2) << std::setfill('0') << t.tm_mon + 1 << "-"
        << std::setw(2) << std::setfill('0') << t.tm_mday << " "
        << std::setw(2) << std::setfill('0') << t.tm_hour << ":"
        << std::setw(2) << std::setfill('0') << t.tm_min << ":"
        << std::setw(2) << std::setfill('0') << t.tm_sec << '\n';

    return 0;
}