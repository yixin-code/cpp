#include <iostream>
#include <string.h>
#include <netinet/ip.h> // sockaddr_in
#include <sys/socket.h> // socket recvfrom sendto
#include <unistd.h>     // close
#include <arpa/inet.h>  // inet_ntop

constexpr u_int16_t SERVER_PORT = 8973;
constexpr uint32_t DATA_MAX_LEN = 1024;

int main(int argc, char *argv[]) {
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1) {
        perror("sock_fd");
        exit(1);
    }

    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = ntohs(SERVER_PORT);
    server_addr.sin_addr.s_addr = ntohl(INADDR_ANY);

    if (bind(socket_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(1);
    }

    char buf[DATA_MAX_LEN] = {0};
    sockaddr_in client_addr;
    memset(&client_addr, 0, sizeof(client_addr));
    socklen_t client_addr_len = sizeof(client_addr);
    uint32_t count = 0;
    char addr_buf[16] = {0};

    while (true) {
        std::cout << "wait connect...\n";
        count = recvfrom(socket_fd, buf, DATA_MAX_LEN, 0, (sockaddr*)&client_addr, &client_addr_len); // 默认会阻塞等待

        std::cout << inet_ntop(AF_INET, &client_addr.sin_addr, addr_buf, 16) << " connected\n";
        
        memcpy(buf + count - 1, " processed", 10); // 收到的有换行符
        sendto(socket_fd, buf, count + 10, 0, (sockaddr*)&client_addr, sizeof(client_addr));

        memset(&client_addr, 0, sizeof(client_addr));
        memset(buf, 0, DATA_MAX_LEN);
    }

    close(socket_fd);

    return 0;
}