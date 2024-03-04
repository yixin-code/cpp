#include <iostream>
#include <signal.h>

int main() {
    signal(SIGHUP, SIG_IGN);

    while (true) {
        std::cout << "sleep\n";
        sleep(1);
    }

    std::cout << "main end\n";

    return 0;
}