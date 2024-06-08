#include <iostream>
#include <pthread.h>

class CReadWrite {
public:
    CReadWrite();
    ~CReadWrite();
public:
    void write(void);
    void read(void);
public:
    bool            m_flag_r;
    bool            m_flag_w;
    int             m_data;
    pthread_mutex_t m_mutex_r;
    pthread_mutex_t m_mutex_w;
    pthread_cond_t  m_cond_r;
    pthread_cond_t  m_cond_w;
};

void *thread_write(void *arg) {
    CReadWrite *p = (CReadWrite*)arg;
    p->write();
    pthread_exit(nullptr);
}

void *thread_read(void *arg) {
    CReadWrite *p = (CReadWrite*)arg;
    p->read();
    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    CReadWrite  read_write;
    pthread_t   tid_w;

    if (pthread_create(&tid_w, nullptr, thread_write, (void*)&read_write) != 0) {
        perror("pthread create tid w fail");
        exit(1);
    }

    pthread_t   tid_r;

    if (pthread_create(&tid_r, nullptr, thread_read, (void*)&read_write) != 0) {
        perror("pthread create tid r fail");
        exit(1);
    }

    pthread_join(tid_w, nullptr);
    pthread_join(tid_r, nullptr);

    return 0;
}

CReadWrite::CReadWrite() : m_flag_r(false), m_flag_w(false), m_data(0) {
    pthread_mutex_init(&this->m_mutex_r, nullptr);
    pthread_mutex_init(&this->m_mutex_w, nullptr);
    pthread_cond_init(&this->m_cond_r, nullptr);
    pthread_cond_init(&this->m_cond_w, nullptr);
}

CReadWrite::~CReadWrite() {
    pthread_mutex_destroy(&this->m_mutex_r);
    pthread_mutex_destroy(&this->m_mutex_w);
    pthread_cond_destroy(&this->m_cond_r);
    pthread_cond_destroy(&this->m_cond_w);
}

void CReadWrite::write(void) {
    for (int i = 1; i <= 11; ++i) {
        pthread_mutex_lock(&this->m_mutex_r);
        this->m_data    = i;
        this->m_flag_r  = true;
        std::cout << "make data: " << this->m_data << std::endl;
        pthread_cond_broadcast(&this->m_cond_r);
        pthread_mutex_unlock(&this->m_mutex_r);

        pthread_mutex_lock(&this->m_mutex_w);
        while (this->m_flag_w == false) {
            pthread_cond_wait(&this->m_cond_w, &this->m_mutex_w);
        }
        this->m_flag_w  = false;
        pthread_mutex_unlock(&this->m_mutex_w);
    }
    return;
}

void CReadWrite::read(void) {
    for (int i = 1; i <= 11; ++i) {
        pthread_mutex_lock(&this->m_mutex_r);
        while (this->m_flag_r == false) {
            pthread_cond_wait(&this->m_cond_r, &this->m_mutex_r);
        }
        this->m_flag_r = false;
        std::cout << "process data: " << this->m_data << std::endl;
        pthread_mutex_unlock(&this->m_mutex_r);

        pthread_mutex_lock(&this->m_mutex_w);
        this->m_flag_w = true;
        pthread_cond_broadcast(&this->m_cond_w);
        pthread_mutex_unlock(&this->m_mutex_w);
    }
    return;
}