#include <iostream>
#include <queue>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

class PoolQueue {
public:
    PoolQueue();
    ~PoolQueue();
public:
    void    push(int fd);
    int     pop(void);
private:
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;
    std::queue<int> m_queue;
};

int main(int argc, char *argv[]) {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        perror("socket listen_fd fail");
        exit(1);
    }

    bind(listen_fd, (sockaddr*));

    return 0;
}

PoolQueue::PoolQueue() {
    pthread_mutex_init(&this->m_mutex, nullptr);
    pthread_cond_init(&this->m_cond, nullptr);
}

PoolQueue::~PoolQueue() {
    pthread_mutex_destroy(&this->m_mutex);
    pthread_cond_destroy(&this->m_cond);
}

void PoolQueue::push(int fd) {
    pthread_mutex_lock(&this->m_mutex);

    this->m_queue.push(fd);

    pthread_cond_broadcast(&this->m_cond);

    pthread_mutex_unlock(&this->m_mutex);
}

int PoolQueue::pop(void) {
    pthread_mutex_lock(&this->m_mutex);

    while (this->m_queue.empty()) {
        pthread_cond_wait(&this->m_cond, &this->m_mutex);
    }

    int ret = this->m_queue.front();
    this->m_queue.pop();

    pthread_mutex_unlock(&this->m_mutex);

    return ret;
}
