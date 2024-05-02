#include <iostream>
#include <sys/socket.h> // socket bind listen accept
#include <netinet/ip.h> // sockaddr_in
#include <string.h>
#include <arpa/inet.h> // inet_ntop htonl htons ntohs
#include <unistd.h> // write read

int main(int argc, char *argv[]) {
    constexpr uint32_t SERVER_PORT = 8354; // 端口号
    constexpr uint32_t MAX_RECV_DATA = 1024; // 最大接收数据
    // constexpr u_char ADDR_LEN = 16; // ip地址长度

    // 分配一个监听描述符
        // domain
            // AF_UNIX, AF_LOCAL   本地
            // AF_INET             ipv4
            // AF_INET6            ipv6
        // type
            // SOCK_STREAM         tcp协议
            // SOCK_DGRAM          udp协议
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1) {
        perror("14 socket");
        exit(1);
    }

    // 绑定ip地址
    sockaddr_in server_addr;
    // 服务端初始化
    memset(&server_addr, 0, sizeof(server_addr)); // 后续有8个字节填充需要置空
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(SERVER_PORT); // 需要转为网络字节序 网络字节序是大端
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // 监听所有ip地址 0.0.0.0 不指定ip
    
    if (bind(socket_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("31 bind");
        exit(1);
    }

    // 监听套接字文件描述符
    if (listen(socket_fd, 5) == -1) { // 最大排队个数(超过个数会被忽略)
        perror("37 listen");;
        exit(1);
    }
    std::cout << "wait connect...\n";

    int connect_fd = 0;
    sockaddr_in client_addr;
    socklen_t client_addr_len = 0;
    // int temp_ret = 0;
    char temp_buf[MAX_RECV_DATA] = {0};

    while (true) {
        // 阻塞等待客户端连接, 返回连接套接字 用于传输数据
            // 参数2 3是客户端信息 不关心可以添null
        memset(&client_addr, 0, sizeof(client_addr));
        client_addr_len = sizeof(client_addr);
        if ((connect_fd = accept(socket_fd, (sockaddr*)&client_addr, &client_addr_len)) == -1) {
            perror("51 accept");
            exit(1);
        }

        // char temp_buf2[INET_ADDRSTRLEN] = {0}; // INET_ADDRSTRLEN 16
        // char temp_buf2[ADDR_LEN] = {0};
        // std::cout << "客户端: "
        //           << inet_ntop(AF_INET, &client_addr.sin_addr, temp_buf, INET_ADDRSTRLEN) // 返回字符串
        //           << ", 端口号: " << ntohs(client_addr.sin_port) << " 已连接" << '\n';
        std::cout << "客户端: " << inet_ntoa(client_addr.sin_addr) // 返回字符串
                  << ", 端口号: " << ntohs(client_addr.sin_port) << " 已连接" << '\n';
        
        memset(temp_buf, 0, MAX_RECV_DATA);
        read(connect_fd, temp_buf, MAX_RECV_DATA); // 返回读到的字节数
        std::cout << temp_buf << '\n';
        
        write(connect_fd, "你好客户端", sizeof( "你好客户端"));

        close(connect_fd);
    }

    return 0;
}