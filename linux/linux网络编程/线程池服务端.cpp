#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

constexpr int POST  = 8435;

int main(int argc, char *argv[]) {
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

    // 监听套接字 最大排队数 超过会忽略
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
    }


    return 0;
}