#include <iostream>
#include <pthread.h>

class CCalc {
public:
    CCalc();
    ~CCalc();
public:
    void    calc(void);
    void    get_res(void);
private:
    int             m_res;
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;
};

void *func(void *arg) {

}

void *func2(void *arg) {

}

int main(int argc, char *argv) {

    return 0;
}

CCalc::CCalc() : m_res(0) {
    pthread_mutex_init(&this->m_mutex, nullptr);
    pthread_cond_init(&this->m_cond, nullptr);
}

CCalc::~CCalc() {
    pthread_mutex_destroy(&this->m_mutex);
    pthread_cond_destroy(&this->m_cond);
}

void CCalc::calc(void) {
    for (int i = 1; i <= 10; ++i) {
        pthread_mutex_lock(&this->m_mutex);
        this->m_res = i;
        pthread_mutex_unlock(&this->m_mutex);
        pthread_cond_broadcast(&this->m_cond);
    }
}

void CCalc::get_res(void) {
    while (1) {
        pthread_mutex_lock(&this->m_mutex);
        while (this->m_res == 0) {
            // 会先释放拿到的锁，等待被唤醒在加锁
            pthread_cond_wait(&this->m_cond, &this->m_mutex);
        }
        std::cout << this->m_res << "\n";
        this->m_res = 0;
        if (this->m_res == 10) {
            break;
        }
        pthread_mutex_unlock(&this->m_mutex);
    }
}