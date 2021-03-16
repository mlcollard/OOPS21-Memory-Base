/*
    Memory.cpp

    An example of memory resource problems.

    Definitely not a guide to good programming practices.
*/

#include <iostream>

int* producer(int n) {

    int* p = new int(n);

    return p;
}

void consumer(int* pn) {

    // ...

    delete pn;
}

int main() {

    // @error memory leak
    {
        int* p = new int(5);

        std::cerr << "TRACE: " << __FILE__ << ":" << __LINE__ << '\n';
    }

    // @error memory leak
    {
        int* p = producer(5);

        std::cerr << "TRACE: " << __FILE__ << ":" << __LINE__ << '\n';
    }

    // @error memory leak
    {
        int* p = new int(5);

        p = new int(6);

        delete p;

        std::cerr << "TRACE: " << __FILE__ << ":" << __LINE__ << '\n';
    }

    // @error missing initialization and use unallocated memory
    {
        int* p;

        *p = 5;

        std::cerr << "TRACE: " << __FILE__ << ":" << __LINE__ << '\n';
    }

    // @error double free
    {
        int* p = nullptr;

        p = new int(5);

        delete p;

        delete p;

        std::cerr << "TRACE: " << __FILE__ << ":" << __LINE__ << '\n';
    }

    // @error double free
    {
        int* p = new int(5);

        consumer(p);

        delete p;

        std::cerr << "TRACE: " << __FILE__ << ":" << __LINE__ << '\n';
    }

    return 0;
}
