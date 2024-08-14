#include <iostream>
#include <sys/wait.h> // waitpid
#include <sys/ipc.h> // ftok
#include <sys/msg.h> // msgget msgsnd msgrcv
#include <string.h>
#include <unistd.h> // fork

int main(int argc, char *argv[]) {
    pid_t pid = fork();
    switch (pid) {
    case -1: {
        perror("fork fail");
        exit(1);
    }
    case 0: {
        key_t msg_key = ftok("/home/yixin/Temp", 11);
        if (msg_key == -1) {
            perror("child ftok fail");
            exit(1);
        }

        int msg_id = msgget(msg_key, IPC_CREAT | 0664);
        if (msg_id == -1) {
            perror("child msgget fail");
            exit(1);
        }

        struct msgbuf {
            long m_type;
            char m_text[20];
        } msg;
        msg.m_type = 1;
        strncpy(msg.m_text, "yixin", 6);

        if (msgsnd(msg_id, &msg, sizeof(msg.m_text), 0) == -1) {
            perror("child msgsnd fail");
            exit(1);
        }

        msg.m_type = 2;
        strncpy(msg.m_text, "hello world", 12);

        if (msgsnd(msg_id, &msg, sizeof(msg.m_text), 0) == -1) {
            perror("child msgsnd fail");
            exit(1);
        }

        break;
    }
    default: {
        key_t msg_key = ftok("/home/yixin/Temp", 11);
        if (msg_key == -1) {
            perror("parent ftok fail");
            exit(1);
        }

        int msg_id = msgget(msg_key, IPC_CREAT | 0664);
        if (msg_id == -1) {
            perror("parent msgget fail");
            exit(1);
        }

        struct msgbuf {
            long m_type;
            char m_text[20];
        } msg;

        if (msgrcv(msg_id, &msg, sizeof(msg.m_text), 1, 0) == -1) {
            perror("parent msgrcv fail");
            exit(1);
        }

        std::cout << "recv: " << msg.m_text << '\n';

        if (msgrcv(msg_id, &msg, sizeof(msg.m_text), 2, 0) == -1) {
            perror("parent msgrcv fail");
            exit(1);
        }

        std::cout << "recv: " << msg.m_text << '\n';

        waitpid(-1, nullptr, 0);

        break;
    }
    }

    return 0;
}