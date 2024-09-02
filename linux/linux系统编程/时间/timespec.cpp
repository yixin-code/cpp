#include <iostream>
#include <time.h>

int main(int argc, char *argv[]) {
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    ts.tv_sec   += 3;
    ts.tv_nsec  += 0;
    std::cout << "sec: " << ts.tv_sec << ", nsec: " << ts.tv_nsec << '\n';

    return 0;
}