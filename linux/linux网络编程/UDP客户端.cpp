#include <iostream>
#include <unistd.h> // close
#include <netinet/in.h> // sockaddr_in
#include <sys/socket.h> // socket sendto recvfrom
#include <arpa/inet.h>
#include <string.h>

constexpr u_int16_t SERVER_PORT = 8973;
constexpr uint32_t DATA_MAX_LEN = 1024;

int main(int argc, char *argv[]) {
    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket_fd == -1) {
        perror("socket");
        exit(1);
    }

    ssize_t count = 0;
    char buf[DATA_MAX_LEN] = {0};
    sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

    while (count = read(STDIN_FILENO, buf, DATA_MAX_LEN)) {
        sendto(socket_fd, buf, count, 0, (sockaddr*)&server_addr, sizeof(server_addr));
        recvfrom(socket_fd, buf, DATA_MAX_LEN, 0, nullptr, nullptr);
        std::cout << buf << "\n";
    }

    close(socket_fd);

    return 0;
}