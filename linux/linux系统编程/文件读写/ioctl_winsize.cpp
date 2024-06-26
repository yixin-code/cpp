#include <iostream>
#include <unistd.h>
#include <sys/ioctl.h>

int main(int argc, char *argv[]) {
    struct winsize ws; // 窗口大小

    if (isatty(STDIN_FILENO) == false) {
        perror("STDIN_FILENO not tty");
        exit(1);
    }
    
    if (ioctl(STDIN_FILENO, TIOCGWINSZ, &ws) == -1) {
        perror("ioctl fail");
        exit(1);
    }

    std::cout << "row: " << ws.ws_row << ", col: " << ws.ws_col << "\n";

    return 0;
}