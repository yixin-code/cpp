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
    if (bind(fd, )

    return 0;
}