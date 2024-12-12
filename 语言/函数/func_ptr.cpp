#include <iostream>

void func() {
    std::cout << "func" << std::endl;
}

using p_func_type = void (*) ();
int main(int argc, char *argv[]) {
    p_func_type p_func = func;
    (*p_func)();

    return 0;
}