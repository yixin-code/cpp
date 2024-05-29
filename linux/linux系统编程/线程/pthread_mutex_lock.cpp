#include <iostream>
#include <unistd.h>
#include <pthread.h>

class Account {
public:
    Account(int number, double balance);
    ~Account();
public:
    double  withdraw_money(const double money);    // 取钱
    double  get_balance(void);                     // 余额
private:
    int             m_number;   // 编号
    double          m_balance;  // 余额
    pthread_mutex_t m_mutex;    // 互斥锁
};

struct User {
    std::string m_name;
    Account*    m_p_account;
};

void *thread_func(void *arg) {
    if (arg == nullptr) {
        perror("arg is nullptr");
        exit(1);
    }

    User* p = (User*)arg;
    p->m_p_account->withdraw_money(1111.1111);
    std::cout << p->m_name << " balance: " << p->m_p_account->get_balance() << std::endl;

    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    Account account{1234, 1111.1111};

    User user;
    user.m_name         = "aaa";
    user.m_p_account    = &account;

    User    user2;
    user2.m_name        = "bbb";
    user2.m_p_account   = &account;

    pthread_t tid   = 0;
    pthread_t tid2  = 0;

    if (pthread_create(&tid, nullptr, thread_func, (void*)&user) != 0) {
        perror("pthread_create tid");
        exit(1);
    }

    if (pthread_create(&tid2, nullptr, thread_func, (void*)&user2) != 0) {
        perror("pthread_create tid2");
        exit(1);
    }

    pthread_join(tid, nullptr);
    pthread_join(tid2, nullptr);

    return 0;
}

Account::Account(int number, double balance) : m_number(number), m_balance(balance) {
    pthread_mutex_init(&this->m_mutex, nullptr);
}

Account::~Account() {
    pthread_mutex_destroy(&this->m_mutex);
}

double Account::withdraw_money(const double money) {
    pthread_mutex_lock(&this->m_mutex);

    if (this->m_balance < money) {
        std::cout << "balance greater money\n";
        pthread_mutex_unlock(&this->m_mutex);
        return 0.0;
    }
    // 模拟存储操作
    double temp_balance = this->m_balance;
    sleep(1);
    temp_balance -= money;
    this->m_balance = temp_balance;

    pthread_mutex_unlock(&this->m_mutex);

    return money;
}

double Account::get_balance(void) {
    pthread_mutex_lock(&this->m_mutex);

    double temp_balance = this->m_balance;

    pthread_mutex_unlock(&this->m_mutex);

    return temp_balance;
}