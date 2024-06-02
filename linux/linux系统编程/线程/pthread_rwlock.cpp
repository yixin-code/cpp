#include <iostream>
#include <pthread.h>
#include <string.h>
// r r两次都可以成功拿到锁
// r w拿写锁的时候会阻塞
// w r拿读锁的时候会失败
// w w第二次拿写锁的时候会失败
int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("example: ./a.out r w");
        exit(1);
    }

    pthread_rwlock_t rwlock;
    pthread_rwlock_init(&rwlock, nullptr);

    if (strcmp(argv[1], "r") == 0) {
        if (pthread_rwlock_rdlock(&rwlock) == 0) {
            std::cout << "first rdlock success\n";
        } else {
            std::cout << "first rdlock fail\n";
        }
    }

    if (strcmp(argv[1], "w") == 0) {
        if (pthread_rwlock_wrlock(&rwlock) == 0) {
            std::cout << "first wrlock success\n";
        } else {
            std::cout << "first wrlock fail\n";
        }
    }

    if (strcmp(argv[2], "r") == 0) {
        if (pthread_rwlock_rdlock(&rwlock) == 0) {
            std::cout << "second rdlock success\n";
        } else {
            std::cout << "second rdlock fail\n";
        }
    }

    if (strcmp(argv[2], "w") == 0) {
        if (pthread_rwlock_wrlock(&rwlock) == 0) {
            std::cout << "second wrlock success\n";
        } else {
            std::cout << "second wrlock fail\n";
        }
    }

    pthread_rwlock_unlock(&rwlock);
    pthread_rwlock_unlock(&rwlock);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}