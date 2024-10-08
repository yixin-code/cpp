#include <iostream>
#include <string.h>

int main(int argc, char *argv[]) {
    char str[]      = "hello";
    char str2[6]    = "";

    for (int i = 0; str[i] != '\0'; i++) {
        str2[strlen(str) - i - 1] = str[i];
    }

    std::cout << "str: " << str << "\n";
    std::cout << "str2: " << str2 << "\n";

    return 0;
}