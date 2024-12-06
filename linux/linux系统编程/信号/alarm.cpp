#include <iostream>
#include <signal.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    alarm(3);

    sleep(2);

    unsigned int surplus = alarm(5);

    std::cout << "surplus: " << surplus << std::endl; // 1

    // 5秒后被闹钟信号终止
    while (true) {
        std::cout << "wait..." << std::endl;
        sleep(1);
    }

    return 0;
}