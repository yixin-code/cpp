#include <iostream>
#include <math.h>

// 两点之间距离
double distance(double x, double y, double x2, double y2) {
    return sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
}

int main(int argc, char *argv[]) {
    std::cout << distance(1, 2, 9, 8) << std::endl;

    return 0;
}