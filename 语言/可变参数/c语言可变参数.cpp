#include <iostream>
#include <stdarg.h>

void func(int count, ...) {
    va_list ap; // 参数列表
    va_start(ap, count); // 初始化参数列表

    for (int i = 0; i < count; ++i) {
        std::cout << va_arg(ap, char*) << " ";
    }
    std::cout << "\n";

    va_end(ap);
}

void func2(const char* format, ...) {
    va_list ap;
    va_start(ap, format);

    const char *temp_p = format;

    for (; *temp_p != 0; ++temp_p) {
        if (*temp_p != '%') {
            putchar(*temp_p);
            continue;
        } else {
            switch (*(++temp_p)) {
            case 'd' : {
                std::cout << va_arg(ap, int);
                break;
            }
            default : {
                vprintf(--temp_p, ap);
                ++temp_p; // 跳过占位符
                break;
            }
            }
        }
    }
    std::cout << "\n";

    va_end(ap);
}

int main() {
    func(3, "aaa", "bbb", "ccc");
    func2("%d %s", 1, "aaa");

    return 0;
}