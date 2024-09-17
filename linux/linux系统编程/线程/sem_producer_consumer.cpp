#include <iostream>
#include <vector>
#include <random>
#include <string.h>
#include <semaphore.h> // sem_wait
#include <pthread.h>
#include <unistd.h>

class ProducerConsumer {
private:
    enum {MAXSIZE = 5};
public:
    ProducerConsumer();
    ~ProducerConsumer();
public:
    void producer();
    void consumer();
private:
    sem_t               m_producer; // 生产者
    sem_t               m_consumer; // 消费者
    std::vector<int>    m_s_tore;   // 仓库
    std::mt19937        m_mt;       // 随机数算法和种子
};

void* producer_work(void *arg) {
    ProducerConsumer *p = (ProducerConsumer*)arg;
    p->producer();
    pthread_exit(nullptr);
}

void* consumer_work(void *arg) {
    ProducerConsumer *p = (ProducerConsumer*)arg;
    p->consumer();
    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    ProducerConsumer pc;

    pthread_t pid = 0;
    if (pthread_create(&pid, nullptr, producer_work, (void*)&pc) != 0) {
        perror("pthread_create pid fail");
        exit(1);
    }

    pthread_t pid2 = 0;
    if (pthread_create(&pid2, nullptr, consumer_work, (void*)&pc) != 0) {
        perror("pthread_create pid2 fail");
        exit(1);
    }

    pthread_join(pid, nullptr);
    pthread_join(pid2, nullptr);

    return 0;
}

ProducerConsumer::ProducerConsumer() : m_mt(std::random_device{}()) {
    sem_init(&this->m_producer, 0, MAXSIZE);
    sem_init(&this->m_consumer, 0, 0);
}

ProducerConsumer::~ProducerConsumer() {
    sem_destroy(&this->m_producer);
    sem_destroy(&this->m_consumer);
}

void ProducerConsumer::producer() {
    while(true) {
        std::uniform_int_distribution<int> dis(1, 100); // 包含1和100

        sem_wait(&this->m_producer); // 仓库中位置减一 为0时阻塞

        this->m_s_tore.push_back(dis(this->m_mt));
        std::cout << "producer: " << this->m_s_tore.back() << std::endl;

        sem_post(&this->m_consumer); // 通知消费者仓库中有货物

        sleep(1);
    }
}

void ProducerConsumer::consumer() {
    while (true) {
        sem_wait(&this->m_consumer);

        std::cout << "consumer: " << this->m_s_tore.front() << std::endl;
        this->m_s_tore.erase(this->m_s_tore.begin());

        sem_post(&this->m_producer);

        sleep(1);
    }
}