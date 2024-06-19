#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    constexpr uint32_t SERVER_PORT   = 8354;   // 端口号
    constexpr uint32_t MAX_RECV_DATA = 1024; // 最大接收数据
    // 获取套接字文件描述符
        // domain
        //     AF_UNIX, AF_LOCAL   本地
        //     AF_INET             ipv4
        //     AF_INET6            ipv6
        // type
        //     SOCK_STREAM         tcp协议
        //     SOCK_DGRAM          udp协议
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("20 socket");
        exit(1);
    }
    // 客户端地址结构体
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    if (inet_aton("127.0.0.1", &server_addr.sin_addr) ==0) {
        perror("26 inet_aton");
        exit(1);
    }
    server_addr.sin_family = AF_INET;
    server_addr.sin_port   = htons(SERVER_PORT);
    // 阻塞等待发起连接
    if (connect(socket_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("34 connect");
        exit(1);
    }
    // std::cout << "client launch connect\n";
    
    char buf[MAX_RECV_DATA] = {0};
    while (true) {
        memset(buf, 0, MAX_RECV_DATA);
        std::cin.getline(buf, MAX_RECV_DATA);
        buf[strlen(buf)] = '\n';
        if (write(socket_fd, buf, strlen(buf)) == -1) { // 返回写入字节数
            perror("write fail");
            exit(1);
        }
        if (strncasecmp(buf, "quit", 4) == 0) {
            break;
        }
    }

    close(socket_fd);

    // if (read(socket_fd, buf, MAX_RECV_DATA) == -1) {
    //     perror("46 read");
    //     exit(1);
    // }

    // std::cout << buf;

    return 0;
}