#include <iostream>
#include <unistd.h>

int main(int argc, char *argv[]) {
    for (int i = 0; environ[i] != nullptr; ++i) {
        std::cout << environ[i] << '\n';
    }

    std::cout << '\n';

    char *buf = getenv("HOME"); // 查询环境变量
    std::cout << buf << "\n";

    // 设置环境变量，没有添加，有覆盖
        // 参数三 true覆盖 false不覆盖
    // shell中的环境变量传递给了./a.out，修改的是./a.out中的环境变量并不会影响shell中的环境变量
    setenv("yixin", "hello yixin", true);

    buf = getenv("yixin");
    std::cout << buf << "\n";

    setenv("HOME", "hello world", true);

    buf = getenv("HOME");
    std::cout << buf << "\n";

    return 0;
}