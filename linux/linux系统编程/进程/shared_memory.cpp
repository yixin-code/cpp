#include <iostream>
#include <string.h>
#include <sys/shm.h> // shmget shmat
#include <wait.h> // waitpid
#include <sys/ipc.h> // ftok
#include <unistd.h> // fork

int main(int argc, char *argv[]) {
    key_t key = ftok("/home/yixin/Temp", 22); // 随机整数
    if (key == -1) {
        perror("ftok fail");
        exit(1);
    }

    int shm_id = shmget(key, 1024, IPC_CREAT | 0664); // 创建共享内存返回共享内存标识符
    if (shm_id == -1) {
        perror("shmget fail");
        exit(1);
    }

    char *p_shm = (char*)shmat(shm_id, nullptr, 0); // 连接到共享内存，返回共享内存指针
    if (p_shm == (char*)-1) {
        perror("shmat fail");
        exit(1);
    }

    pid_t pid = fork();
    switch (pid) {
    case -1: {
        perror("fork fail");
        exit(1);
    }
    case 0: { // 子进程
        while (true) {
            if (strcasecmp(p_shm, "quit") == 0) {
                break;
            }
            if (*p_shm != 0) {
                std::cout << "son thread: " << '[' << p_shm << ']' << '\n';
            }
            memset(p_shm, 0, 1024);
        }
    }
    default: { // 父进程
        while (true) {
            scanf("%s", p_shm);
            if (strcasecmp(p_shm, "quit") == 0) {
                break;
            }
        }
        waitpid(-1, nullptr, 0);
    }
    }

    shmdt(p_shm); // 将共享内存从当前进程分离

    return 0;
}