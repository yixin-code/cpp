#include <iostream>
#include <random>
#include <termios.h>
#include <unistd.h>
#include <string.h>

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
    static termios m_ter;
private:
    void init_food(void);
    static void reset_termios(void); // 注册函数用于恢复终端设置
    void set_nonblock(void); // 设置终端非阻塞，且不等待换行符
    int kbhit(void);
    char getch(void);
    void set_cursor_position(int x, int y);
    void show_ui(void);
public:
    CSnake(void);
public:
    void start_game(void);
};

int main(int argc, char *argv[]) {
    CSnake snake;
    snake.start_game();

    std::cout << std::endl;
    // while(true);

    return 0;
}

termios CSnake::m_ter;

CSnake::CSnake(void) {
    // 初始化蛇头
    m_snake[0]->m_x = WIDE / 2;
    m_snake[0]->m_y = HIGH / 2;
    // 初始化蛇尾
    m_snake[1]->m_x = WIDE / 2 - 1;
    m_snake[1]->m_y = HIGH / 2;

    m_size = 2;

    init_food();
}

void CSnake::init_food(void) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> dis(1, WIDE - 2);

    for (int i = 0; i < m_size; ++i) {
        m_food.m_x = dis(mt);
        m_food.m_y = dis(mt);
        while ((m_food.m_x == m_snake[i]->m_x) && (m_food.m_y == m_snake[i]->m_y));
        break;
    }
}

void CSnake::reset_termios(void) {  
    tcsetattr(STDIN_FILENO, TCSANOW, &m_ter);  
}  

void CSnake::set_nonblock(void) {  
    struct termios new_termios;  
  
    tcgetattr(STDIN_FILENO, &m_ter); // 得到原始终端设置
    new_termios = m_ter;  
  
    // read不会等待换行符  
    new_termios.c_lflag &= ~(ICANON | ECHO);  
    // 使read调用变为非阻塞  
    new_termios.c_cc[VMIN] = 0;  
    new_termios.c_cc[VTIME] = 0;  
  
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);  
  
    // 注册reset_termios，退出时恢复终端设置  
    atexit(&CSnake::reset_termios);  
}  

int CSnake::kbhit(void) {  
    struct timeval tv = {0L, 0L};  
    fd_set fds;  
    int temp_res;  
  
    FD_ZERO(&fds);  
    FD_SET(STDIN_FILENO, &fds);  
    temp_res = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);  

    if (temp_res < 0) {
        return -1;
    }  
    if (temp_res == 0) {
        return 0;
    }

    return 1;
}  

char CSnake::getch(void) {  
    char ch;  

    if (read(STDIN_FILENO, &ch, 1) != 1) {  
        return -1;  
    }  

    return ch;  
}  

void CSnake::set_cursor_position(int x, int y) {  
    // system("clear");
    char buf[32] = {0};
    snprintf(buf, sizeof(buf), "\033[%d;%dH", y - 1, x - 1); // \033[%d;%dH是一个ANSI转义序列，用于设置光标位置。%d;%d 会被替换为行号和列号，行号和列号的起始值通常是 1，不是 0。
    // write(STDOUT_FILENO, buf, strlen(buf));  
    std::cout << buf;
}  

void CSnake::show_ui(void) {
    for (int i = 0; i < m_size; ++i) {
        set_cursor_position(m_snake[i]->m_x, m_snake[i]->m_y);
        if (i == 0) {
            std::cout << "@";
        } else {
            std::cout << "*";
        }
    }

    set_cursor_position(m_food.m_x, m_food.m_y);
    std::cout << "#";
}

void CSnake::start_game(void) {
    while(true) {
        show_ui();

        usleep(1000000);
    }
}