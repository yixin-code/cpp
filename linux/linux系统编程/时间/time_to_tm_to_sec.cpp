#include <iostream>

int main(int argc, char *argv[]) {
    tm t;
    t.tm_year = 2024 - 1900;
    t.tm_mon  = 5 - 1;
    t.tm_mday = 13;
    t.tm_hour = 19;
    t.tm_min  = 47;
    t.tm_sec  = 0;
    time_t tt = mktime(&t);
    std::cout << tt << "\n";
    tt = time(nullptr); // 获取当前时间秒数
    std::cout << tt << "\n";

    return 0;
}