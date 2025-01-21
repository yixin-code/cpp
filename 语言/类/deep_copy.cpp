#include <iostream>
#include <cstring>

class Array {
public:
    Array(int size) : m_size(size), m_p(new int[size]{0}) {
        std::cout << "Array(int size) : m_size(size), m_p(new int[size]{0})" << std::endl;
    }
    Array(const Array &other) {
        std::cout << "Array(const Array &other)" << std::endl;
        if (this == &other) {
            return;
        }

        m_size = other.m_size;
        m_p = new int[other.m_size];
        memcpy(m_p, other.m_p, other.m_size * sizeof(int));
    }
    ~Array() {
        std::cout << "~Array()" << std::endl;
        delete[] m_p;
    }

public:
    void display() const {
        for (int i = 0; i < m_size; ++i) {
            std::cout << m_p[i] << ' ';
        }
        std::cout << std::endl;
    }
private:
    int m_size;
    int *m_p;
};

int main(int argc, char *argv[]) {
    Array a(11);
    Array b(a);
    a.display();
    b.display();

    return 0;
}