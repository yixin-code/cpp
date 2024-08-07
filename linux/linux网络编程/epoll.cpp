#include <iostream>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <queue>

class ThreadPool {
private:
    std::queue<int> m_pool;
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;
public:
    ThreadPool();
    ~ThreadPool();
public:
    void increace(int connect_fd);
    int remove();
};

void* thread_func(void *arg) {
    ThreadPool* temp        = (ThreadPool*)arg;
    int         connect_fd  = 0;
    char        buf[1024]   = {0};
    int         count       = 0;

    while (true) {
        connect_fd = temp->remove();

        std::cout << connect_fd << " reach\n";

        count = read(connect_fd, buf, sizeof(buf));

        if (strncasecmp("quit", buf, 4) == 0) {
            std::cout << connect_fd << " quit\n";
            close(connect_fd);
        } else {
            write(connect_fd, buf, count);
        }

        memset(buf, 0, sizeof(buf));
    }

    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    constexpr int POST  = 8354;

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        perror("socket sock_fd fail");
        exit(1);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(POST);

    if (bind(sock_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind fail");
        exit(1);
    }

    ThreadPool thread_pool;
    pthread_t thread[4] = {0};
    for (int i = 0; i < 4; ++i) {
        pthread_create(&thread[i], nullptr, thread_func, (void*)&thread_pool);
        std::cout << thread[i] << " create\n";
    }

    int epoll_fd = epoll_create(256); // 监听多个文件描述符上的读写事件
    struct epoll_event et;
    et.events   = EPOLLIN | EPOLLET; // 文件描述符上有可读数据时通知，并使用边缘触发模式
    et.data.fd  = sock_fd;
    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_fd, &et); // 添加sock_fd相关事件

    if (listen(sock_fd, 5) == -1) {
        perror("listen fail");
        exit(1);
    }

    int                 connect_fd      = 0;
    struct sockaddr_in  client_addr;
    socklen_t           client_addr_len = sizeof(client_addr);
    char                buf[20]         = {0};
    struct epoll_event  ets[256];
    int                 count_fd        = 0;

    while (true) {
        // -1阻塞 等待准备好的文件描述符 ets事件数组
            // 返回准备好的文件描述符数量
        count_fd = epoll_wait(epoll_fd, ets, 256, -1);
        for (int i = 0; i < count_fd; ++i) { // 处理事件
            if (ets[i].data.fd == sock_fd) { // 事件fd是sock_fd 等待接受连接
                memset(&client_addr, 0, sizeof(client_addr));
                memset(buf, 0, sizeof(buf));
                connect_fd = accept(sock_fd, (sockaddr*)&client_addr, &client_addr_len);
                std::cout << inet_ntop(AF_INET, &client_addr.sin_addr, buf, 16) << " connected\n"; // 线程安全

                et.data.fd  = connect_fd;
                et.events   = EPOLLIN | EPOLLET;
                epoll_ctl(epoll_fd, EPOLL_CTL_ADD, connect_fd, &et); // 添加connect_fd相关事件
            } else if (ets[i].events & EPOLLIN) { // 如果有可读数据
                if (ets[i].data.fd < 3) {
                    continue;
                }

                thread_pool.increace(ets[i].data.fd);
            }
        }
    }

    close(epoll_fd);
    close(sock_fd);

    return 0;
}

ThreadPool::ThreadPool() {
    pthread_mutex_init(&this->m_mutex, nullptr);
    pthread_cond_init(&this->m_cond, nullptr);
}

ThreadPool::~ThreadPool() {
    pthread_mutex_destroy(&this->m_mutex);
    pthread_cond_destroy(&this->m_cond);
}

void ThreadPool::increace(int connect_fd) {
    pthread_mutex_lock(&this->m_mutex);
    this->m_pool.push(connect_fd);
    pthread_cond_broadcast(&this->m_cond);
    pthread_mutex_unlock(&this->m_mutex);
}

int ThreadPool::remove() {
    pthread_mutex_lock(&this->m_mutex);

    while (this->m_pool.empty()) {
        pthread_cond_wait(&this->m_cond, &this->m_mutex);
    }

    int connect_fd = this->m_pool.front();
    this->m_pool.pop();

    pthread_mutex_unlock(&this->m_mutex);

    return connect_fd;
}
