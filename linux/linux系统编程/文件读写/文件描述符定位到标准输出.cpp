#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    write(3, "yixin\n", 6);

    return 0;
}