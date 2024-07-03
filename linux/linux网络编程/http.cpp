#include <iostream>
#include <unistd.h>
#include <sys/epoll.h>
#include <string.h>
#include <arpa/inet.h>
#include <queue>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>

constexpr u_short POST = 8354;

class CPoolQueue {
public:
    CPoolQueue();
    ~CPoolQueue();
public:
    void    push(int fd);
    int     pop(void);
private:
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;
    std::queue<int> m_queue;
};

void* thread_func(void *arg) {
    CPoolQueue* p           = (CPoolQueue*)arg;
    int         conncet_fd  = 0;
    char        buf[10240]  = {0};
    int         count       = 0;

    while (true) {
        conncet_fd = p->pop();
        std::cout << "thread_func: " << conncet_fd << "\n";
        std::cout << "conncet_fd: " << conncet_fd << ", thread id: " << pthread_self() << "\n";

        count = read(conncet_fd, buf, sizeof(buf));
        if (count == -1) {
            perror("read fail");
        }

        write(STDOUT_FILENO, buf, count);
        // std::cout << buf << "\n";

        std::cout << "conncet_fd: " << conncet_fd << ", thread id: " << pthread_self() << " quit" << "\n";
        memset(buf, 0, sizeof(buf));
        close(conncet_fd);
    }

    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1) {
        perror("socket listen_fd fail");
        exit(1);
    }

    struct sockaddr_in server_addr;

    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(POST);

    if (bind(listen_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind fail");
        exit(1);
    }

    CPoolQueue  pool_queue;
    pthread_t   thread[4] = {0};

    for (int i = 0; i < 4; ++i) {
        if (pthread_create(&thread[i], nullptr, thread_func, (void*)&pool_queue) == -1) {
            std::cout << "thread[" << i << "] ";
            perror("pthread_create fail");
            exit(1);
        }
        std::cout << thread[i] << " create\n";
    }

    int                 epoll_fd = epoll_create(256);
    struct epoll_event  et;

    memset(&et, 0, sizeof(et));

    et.data.fd  = listen_fd;
    et.events   = EPOLLIN | EPOLLET;
    
    // 添加listen_fd的相关时间
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &et) == -1) {
        perror("listen_fd epoll_ctl fail");
        exit(1);
    }

    if (listen(listen_fd, 5) == -1) {
        perror("listen fail");
        exit(1);
    }

    struct epoll_event  ets[256];
    memset(ets, 0, sizeof(ets));

    int                 ready_event_number  = 0;
    struct sockaddr_in  client_addr;
    socklen_t           client_addr_len     = sizeof(client_addr);
    int                 connect_fd          = 0;
    char                buf[20]             = {0};

    while (true) {
        // 阻塞等待事件发生
        ready_event_number = epoll_wait(epoll_fd, ets, 256, -1);
        for (int i = 0; i < ready_event_number; ++i) {
            if (ets[i].data.fd == listen_fd) { // 如果是监听套接字上的事件 则等待接受连接
                memset(&client_addr, 0, sizeof(client_addr));

                if ((connect_fd = accept(listen_fd, (sockaddr*)&client_addr, &client_addr_len)) == -1) {
                    perror("accept fail");
                    exit(1);
                }

                std::cout << inet_ntop(AF_INET, &client_addr.sin_addr, buf, sizeof(buf)) << " connect\n";

                et.data.fd  = connect_fd;
                et.events   = EPOLLIN | EPOLLET;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connect_fd, &et) == -1) {
                    perror("connect_fd epoll_ctl fail");
                    exit(1);
                }
            } else if (ets[i].events & EPOLLIN) {
                if (ets[i].data.fd < 3) {
                    continue;
                }
                pool_queue.push(ets[i].data.fd);
            }
        }
    }

    close(listen_fd);
    close(epoll_fd);

    return 0;
}

CPoolQueue::CPoolQueue() {
    pthread_mutex_init(&this->m_mutex, nullptr);
    pthread_cond_init(&this->m_cond, nullptr);
}

CPoolQueue::~CPoolQueue() {
    pthread_mutex_destroy(&this->m_mutex);
    pthread_cond_destroy(&this->m_cond);
}

void CPoolQueue::push(int fd) {
    std::cout << "push: " << fd << "\n";
    pthread_mutex_lock(&this->m_mutex);

    this->m_queue.push(fd);

    pthread_cond_broadcast(&this->m_cond);

    pthread_mutex_unlock(&this->m_mutex);
}

int CPoolQueue::pop(void) {
    pthread_mutex_lock(&this->m_mutex);

    while (this->m_queue.empty()) {
        pthread_cond_wait(&this->m_cond, &this->m_mutex);
    }

    int ret = this->m_queue.front();
    std::cout << "pop: " << ret << "\n";
    this->m_queue.pop();

    pthread_mutex_unlock(&this->m_mutex);

    return ret;
}
