#include <iostream>
#include <unistd.h>
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
    bool            m_flag;
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;
};

void *func(void *arg) {
    CCalc *p = (CCalc*)arg;
    p->calc();

    pthread_exit(nullptr);
}

void *func2(void *arg) {
    CCalc *p = (CCalc*)arg;
    p->get_res();

    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    CCalc calc;

    pthread_t tid;
    if (pthread_create(&tid, nullptr, func, (void*)&calc) != 0) {
        perror("tid pthread_create");
        exit(1);
    }

    pthread_t tid2;
    if (pthread_create(&tid2, nullptr, func2, (void*)&calc) != 0) {
        perror("tid2 pthread_create");
        exit(1);
    }

    pthread_t tid3;
    if (pthread_create(&tid3, nullptr, func2, (void*)&calc) != 0) {
        perror("tid3 pthread_create");
        exit(1);
    }

    pthread_join(tid, nullptr);
    pthread_join(tid2, nullptr);
    pthread_join(tid3, nullptr);

    return 0;
}

CCalc::CCalc() : m_res(0), m_flag(false) {
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
        // std::cout << "calc\n";
        this->m_res = i;
        if (i == 10) {
            this->m_flag = true;
        }
        pthread_cond_broadcast(&this->m_cond);
        // std::cout << "calc unlock\n";
        pthread_mutex_unlock(&this->m_mutex);
        usleep(5000);
    }

    return;
}

void CCalc::get_res(void) {
    while (1) {
        pthread_mutex_lock(&this->m_mutex);
        // std::cout << "get res\n";
        while (this->m_res == 0 && this->m_flag == false) {
            // 会先释放拿到的锁，阻塞等待被唤醒后，在加锁执行后续代码
            pthread_cond_wait(&this->m_cond, &this->m_mutex);
        }

        if (this->m_flag == true && this->m_res == 0) {
            pthread_mutex_unlock(&this->m_mutex);
            break;
        }

        std::cout << "tid: " << pthread_self() << " " << this->m_res << std::endl;
        this->m_res = 0;
        // int temp = this->m_res;
        // this->m_res = 0;
        // std::cout << temp << std::endl;

        pthread_mutex_unlock(&this->m_mutex);
        // if (temp == 10) {
        //     break;
        // }
    }

    return;
}