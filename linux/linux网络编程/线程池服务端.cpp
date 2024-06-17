// 队列
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

constexpr int POST  = 8435;

struct Node {
    Node(void) : m_fd(0), m_next(nullptr) {}
    Node(int fd) : m_fd(fd), m_next(nullptr) {}
    int     m_fd;
    Node*   m_next;
};

class CThreadPool {
public:
    CThreadPool(void);
    ~CThreadPool(void);
public:
    void    push(int fd);
    Node    pop(void);
private:
    Node*           m_p_head;
    Node*           m_p_tail;
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;
};

void* thread_func(void *arg) {
    pthread_detach(pthread_self());

    CThreadPool* p = (CThreadPool*)arg;

    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    CThreadPool thread_pool;
    pthread_t   thread[4];

    for (int i = 0; i < 4; ++i) {
        if (pthread_create(&thread[i], nullptr, thread_func, (void*)&thread_pool) == -1) {
            perror("pthread_create fail");
            exit(1);
        }
    }

    int socket_fd   = socket(AF_INET, SOCK_STREAM, 0);    // socket文件描述符
    if (socket_fd == -1) {
        perror("socket socket_fd fail");
        exit(1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr   = htonl(INADDR_ANY);
    server_addr.sin_family        = AF_INET;
    server_addr.sin_port          = htonl(POST);

    // 绑定套接字
    if (bind(socket_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind fail");
        exit(1);
    }

    // 监听套接字 以便能够接受来自客户的请求
        // 最大排队数 超过会忽略
    if (listen(socket_fd, 5) == -1) {
        perror("listen fail");
        exit(1);
    }

    struct sockaddr_in  client_addr;
    int                 connect_fd      = 0;
    socklen_t           client_addr_len = 0;
    char                buf[20]         = {0};

    while (true) {
        memset(&client_addr, 0, sizeof(client_addr));
        memset(buf, 0, sizeof(buf));
        // 阻塞等待客户端连接 返回连接套接字 用于传输数据
        if ((connect_fd = accept(socket_fd, (sockaddr*)&client_addr, &client_addr_len)) == -1) {
            perror("accept fail");
            exit(1);
        }
        std::cout << inet_ntop(AF_INET, &client_addr.sin_addr, buf, INET_ADDRSTRLEN) << ", connected\n";
        thread_pool.push(connect_fd);
    }

    return 0;
}

CThreadPool::CThreadPool(void) : m_p_head(nullptr), m_p_tail(nullptr) {
    pthread_mutex_init(&this->m_mutex, nullptr);
    pthread_cond_init(&this->m_cond, nullptr);
}

CThreadPool::~CThreadPool(void) {
    pthread_mutex_destroy(&this->m_mutex);
    pthread_cond_destroy(&this->m_cond);

    Node*   p_temp  = this->m_p_head;
    Node*   p_cur   = nullptr;
    while (p_temp != nullptr) {
        p_cur   = p_temp;
        p_temp  = p_temp->m_next;

        delete p_cur;
        p_cur = nullptr;
    }
}

void CThreadPool::push(int fd) {
    pthread_mutex_lock(&this->m_mutex);

    Node*   new_node    = new Node{fd};

    if (this->m_p_head == nullptr) {
        this->m_p_head = new_node;
    } else {
        this->m_p_tail->m_next = new_node;
    }
    this->m_p_tail = new_node;

    pthread_cond_broadcast(&this->m_cond);
    pthread_mutex_unlock(&this->m_mutex);
}

Node CThreadPool::pop(void) {
    pthread_mutex_lock(&this->m_mutex);

    while (this->m_p_head == nullptr) {
        pthread_cond_wait(&this->m_cond, &this->m_mutex);
    }

    Node*   p_temp = this->m_p_head;

    this->m_p_head = this->m_p_head->m_next;

    if (this->m_p_head == nullptr) {
        this->m_p_head = this->m_p_tail = nullptr;
    }

    pthread_mutex_unlock(&this->m_mutex);

    delete p_temp;

    return *p_temp;
}
