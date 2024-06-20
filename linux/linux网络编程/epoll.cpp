#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

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

    pthread_t thread[4] = {0};

    if (listen(sock_fd, 5) == -1) {
        perror("listen fail");
        exit(1);
    }

    return 0;
}