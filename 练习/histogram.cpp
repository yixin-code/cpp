#include <iostream>
#include <time.h>
#include <vector>

class Histogram {
enum {RANGE = 10, SIZE = 11111};
public:
    Histogram();
    ~Histogram();
public:
    void make_rand();
    void make_histogram();
    void show_histogram();
private:
    std::vector<int> m_histogram; // 直方图
    std::vector<int> m_rands; // 随机数
};

int main(int argc, char *argv[]) {
    Histogram his;
    his.make_rand();
    his.make_histogram();
    his.show_histogram();

    return 0;
}

Histogram::Histogram() {
    srand(time(nullptr));

    this->m_rands.reserve(SIZE);

    this->m_histogram.reserve(RANGE);
    this->m_histogram.resize(RANGE);
}

Histogram::~Histogram() {
}

void Histogram::make_rand() {
    for (int i = 0; i < SIZE; ++i) {
        this->m_rands.push_back(rand() % RANGE);
    }
}

void Histogram::make_histogram() {
    for (int i = 0; i < SIZE; ++i) {
        // std::cout << this->m_rands[i] << std::endl;
        std::cout << this->m_histogram[this->m_rands[i]]++ << std::endl;
    }
}

void Histogram::show_histogram() {
    int temp = 0;
    for (const int &val : this->m_histogram) {
        std::cout << temp++ << ": " << val << '\n';
    }
}
