#include <iostream>

// 点
struct Dot {
    int m_x;
    int m_y;
};

// 蛇
class CSnake {
enum {WIDE = 40, HIGH = 10};
private:
    Dot m_snake[HIGH][WIDE];
    Dot m_food;
    int m_size;
};

int main(int argc, char *argv[]) {


    return 0;
}