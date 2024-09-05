#include <iostream>
#include <vector>
#include <string.h>
#include <semaphore.h> // 

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
    sem_t               m_producer;
    sem_t               m_consumer;
    std::vector<int>    m_s_tore;
};

int main(int argc, char *argv[]) {


    return 0;
}

ProducerConsumer::ProducerConsumer() {
    sem_init(&this->m_producer, 0, MAXSIZE);
    sem_init(&this->m_consumer, 0, 0);
}

ProducerConsumer::~ProducerConsumer() {
    sem_destroy(&this->m_producer);
    sem_destroy(&this->m_consumer);
}
