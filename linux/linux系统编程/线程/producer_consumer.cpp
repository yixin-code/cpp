#include <iostream>
#include <pthread.h> // pthread_mutex_t pthread_cond_t pthread_exit 
#include <time.h> // time
#include <unistd.h>

struct Commodity {
    int         m_data;
    Commodity*  m_p_next;
};

Commodity* p_head  = nullptr;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // 静态初始化
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* producer(void*) {
    Commodity* p_temp = nullptr;

    while (true) {
        p_temp = new Commodity;
        p_temp->m_data = rand() % 100;

        pthread_mutex_lock(&mutex);

        p_temp->m_p_next = p_head; // 头插
        p_head = p_temp;

        pthread_cond_broadcast(&cond); // 数据写入完成唤醒
        pthread_mutex_unlock(&mutex);

        std::cout << "producer: " << p_temp->m_data << '\n';
    }

    pthread_exit(nullptr);
}

void* consumer(void*) {
    Commodity* p_temp = nullptr;

    while (true) {
        pthread_mutex_lock(&mutex);

        while (p_head == nullptr) {
            pthread_cond_wait(&cond, &mutex); // 会先解锁，被唤醒后在加锁
        }

        p_temp = p_head; // 头删
        p_head = p_head->m_p_next;

        pthread_mutex_unlock(&mutex);

        std::cout << "consumer: " << p_temp->m_data << '\n';

        delete p_temp;
        p_temp = nullptr;
    }

    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    srand((unsigned)time(nullptr));

    pthread_t producer_id = 0;

    if (pthread_create(&producer_id, nullptr, producer, nullptr) != 0) {
        perror("pthread_create producer_id fail");
        exit(1);
    }

    pthread_t consumer_id = 0;

    if (pthread_create(&consumer_id, nullptr, consumer, nullptr) != 0) {
        perror("pthread_create consumer_id fail");
        exit(1);
    }

    pthread_join(producer_id, nullptr);
    pthread_join(consumer_id, nullptr);

    return 0;
}