#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int ch = 0;

    while ((ch = getchar()) != EOF) {
        std::cout << (char)(toupper(ch));
    }

    return 0;
}