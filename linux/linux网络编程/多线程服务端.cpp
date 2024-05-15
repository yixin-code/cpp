#include <iostream>
#include <string.h>     // memset
#include <sys/socket.h> // socket bind listen accept
#include <netinet/ip.h> // sockaddr_in
#include <arpa/inet.h>  // inet_ntop htonl htons ntohs

constexpr uint32_t SERVER_PORT = 8354;

int main(int argc, char *argv[]) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        perror("7 socket");
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
    socklen_t client_addr_len = 0;
    char buf[1024] = {0};
    while (true) {
        std::cout << "wait for connect...\n";
        if ((client_fd = accept(client_fd, (sockaddr*)&client_addr, &client_addr_len)) == -1) {
            perror("35 accept");
            exit(1);
        }
        std::cout << inet_ntop(AF_INET, &client_addr, buf, sizeof(buf)) << " connect" << "\n";
        memset(buf, 0, 1024);
    }

    return 0;
}