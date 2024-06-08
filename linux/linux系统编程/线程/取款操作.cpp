#include <iostream>
#include <semaphore.h>
#include <pthread.h>

class CBank {
public:
    CBank(double deposit);  // 存款
    ~CBank();
public:
    double get_withdrawal_total();      // 返回取款总数
    double withdrawal(double money);    // 取款 返回余额
private:
    double  m_balance;          // 余额
    double  m_withdrawal_total; // 取款总数
    sem_t   sem;
};

void *thread_func(void *arg) {
    CBank *p = (CBank*)arg;
    
    p->withdrawal(9999);

    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    CBank bank(11111);

    pthread_t   pthread;
    if (pthread_create(&pthread, nullptr, thread_func, (void*)&bank) != 0) {
        perror("pthread create pthread fail");
        exit(1);
    }

    pthread_t   pthread2;
    if (pthread_create(&pthread2, nullptr, thread_func, (void*)&bank) != 0) {
        perror("pthread create pthread2 fail");
        exit(1);
    }

    pthread_join(pthread, nullptr);
    pthread_join(pthread2, nullptr);

    std::cout << "withdrawal: " << bank.get_withdrawal_total() << "\n";

    return 0;
}

CBank::CBank(double deposit) : m_balance(deposit), m_withdrawal_total(0) {
    sem_init(&sem, 0, 1);
}

CBank::~CBank() {
    sem_destroy(&sem);
}

double CBank::get_withdrawal_total() {
    return this->m_withdrawal_total;
}

double CBank::withdrawal(double money) {
    sem_wait(&sem);
    double  temp = 0;
    if (this->m_balance == 0 || this->m_balance < money) {
        this->m_withdrawal_total += this->m_balance;
        std::cout << pthread_self() << " balance: " << temp << ", withdrawal: " << this->m_balance << "\n";
        this->m_balance = 0;
        temp = this->m_balance;
    } else {
        this->m_withdrawal_total += money;
        this->m_balance -= money;
        temp = this->m_balance;
        std::cout << pthread_self() << " balance: " << temp << ", withdrawal: " << money << "\n";
    }
    sem_post(&sem);

    return temp;
}