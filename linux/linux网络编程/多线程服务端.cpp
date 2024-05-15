#include <iostream>
#include <string.h>     // memset
#include <sys/socket.h> // socket bind listen accept
#include <netinet/ip.h> // sockaddr_in
#include <arpa/inet.h>  // inet_ntop htonl htons ntohs
#include <pthread.h>    // pthread_create pthread_detach
#include <unistd.h>     // read

constexpr uint32_t SERVER_PORT = 8354;
constexpr uint32_t DATA_LEN    = 1024;

void *process_data(void *arg_client_fd) {
    pthread_detach(pthread_self()); // 线程被分离资源自动回收，不需要在join

    int64_t client_fd = (int64_t)arg_client_fd;
    char buf[1024] = {0};
    int count = 0;

    while (true) {
        count = read(client_fd, buf, DATA_LEN);
        if (strncasecmp(buf, "quit", 4) == 0) {
            break;
        }
        write(STDOUT_FILENO, buf, count);
        memset(buf, 0, DATA_LEN);
    } // while

    close(client_fd);

    return nullptr;
}

int main(int argc, char *argv[]) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("34 socket");
        exit(1);
    }

    sockaddr_in sock_addr;
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_port = htons(SERVER_PORT);
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(fd, (sockaddr*)&sock_addr, sizeof(sock_addr)) == -1) {
        perror("21 bind");
        exit(1);
    }

    if (listen(fd, 5) == -1) {
        perror("26 listen");
        exit(1);
    }

    int client_fd = 0;
    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buf[DATA_LEN] = {0};
    while (true) {
        memset(&client_addr, 0, sizeof(client_addr));
        std::cout << "wait for connect...\n";
        if ((client_fd = accept(fd, (sockaddr*)&client_addr, &client_addr_len)) == -1) {
            perror("61 accept");
            exit(1);
        }
        std::cout << inet_ntop(AF_INET, &client_addr.sin_addr, buf, sizeof(buf)) << " connect" << "\n";
        memset(buf, 0, DATA_LEN);

        pthread_t tid;
        pthread_create(&tid, nullptr, process_data, (void*)(int64_t)client_fd);
    } // while

    close(fd);

    return 0;
}