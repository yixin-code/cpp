#include <iostream>
#include <string>
#include <pthread.h>
#include <assert.h>

class Account {
public:
    Account(int number, double balance);
    ~Account();
public:
    const double deposit(double money);
    const double get_balance(void);
private:
    int             m_number;
    double          m_balance;
    pthread_mutex_t m_mutex;
};

struct User {
    std::string m_name;
    Account*    m_p_account;
};

void *thread_func(void *arg) {
    assert(arg != nullptr);

    User *p = (User*)arg;
    std::cout << p->m_name << " deposit " << p->m_p_account->deposit(1111.1111) << ", balance "
                << p->m_p_account->get_balance() << "\n";
    pthread_exit(nullptr);
}

int main(int argc, char *argv[]) {
    Account account(1234, 1111.1111);

    pthread_t tid = 0;

    User user;
    user.m_name         = "aaa";
    user.m_p_account    = &account;

    if (pthread_create(&tid, nullptr, thread_func, (void*)&user) != 0) {
        perror("tid pthread_create fail");
        exit(1);
    }

    pthread_t tid2 = 0;

    User user2;
    user2.m_name         = "bbb";
    user2.m_p_account    = &account;

    if (pthread_create(&tid2, nullptr, thread_func, (void*)&user2) != 0) {
        perror("tid2 pthread_create fail");
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

const double Account::deposit(double money) {
    int ret = pthread_mutex_trylock(&this->m_mutex);
    if (ret == 0) {
        if (this->m_balance < money) {
            std::cout << "balance greater money\n";
            return this->m_balance;
        }
        this->m_balance -= money;
        pthread_mutex_unlock(&this->m_mutex);
        return money;
    } else if (ret == EBUSY) { // 锁被其他线程占用
        std::cout << "deposit wait lock\n";
    } else {
        perror("pthread mutex trylock fail");
        exit(1);
    }
    return 0.0;
}

const double Account::get_balance(void) {
    int ret = pthread_mutex_trylock(&this->m_mutex);
    if (ret == 0) {
        double temp_balance = this->m_balance;
        pthread_mutex_unlock(&this->m_mutex);
        return temp_balance;
    } else if (ret == EBUSY) { // 锁被其他线程占用
        std::cout << "get balance wait lock\n";
    } else {
        perror("pthread mutex trylock fail");
        exit(1);
    }
    return 0.0;
}