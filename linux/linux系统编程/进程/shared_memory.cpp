#include <iostream>
#include <sys/shm.h> // shmget shmat
#include <sys/ipc.h> // ftok
#include <unistd.h> // fork

int main(int argc, char *argv[]) {
    key_t key = ftok("/home/yixin/Temp", 22);
    if (key == -1) {
        perror("ftok fail");
        exit(1);
    }

    int shm_id = shmget(key, 1024, IPC_CREAT | 0664);
    if (shm_id == -1) {
        perror("shmget fail");
        exit(1);
    }

    char *p_shm = (char*)shmat(shm_id, nullptr, 0);
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
    case 0:
    }

    shmdt(p_shm);

    return 0;
}