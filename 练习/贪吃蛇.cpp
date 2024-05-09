#include <iostream>
#include <random>

// 点
struct Dot {
    int m_x;
    int m_y;
};

// 蛇
class CSnake {
private:
    enum {WIDE = 40, HIGH = 10};
private:
    Dot m_snake[HIGH][WIDE];
    Dot m_food;
    int m_size;
private:
    void init_food();
public:
    CSnake();
};

int main(int argc, char *argv[]) {
    CSnake snake;

    return 0;
}

CSnake::CSnake() {
    // 初始化蛇头
    m_snake[0]->m_x = WIDE / 2;
    m_snake[0]->m_y = HIGH / 2;
    // 初始化蛇尾
    m_snake[1]->m_x = WIDE / 2 - 1;
    m_snake[1]->m_y = HIGH / 2;

    m_size = 2;

    this->init_food();
}

void CSnake::init_food() {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dis(0, WIDE - 1);
    std::uniform_int_distribution<> dis2(0, HIGH - 1);

    m_food.m_x = dis(mt);
    m_food.m_y = dis2(mt);
}