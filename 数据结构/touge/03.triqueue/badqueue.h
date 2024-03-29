#ifndef BADQUEUE_H
#define BADQUEUE_H
#include <iostream>
using std::ostream;

template<typename T>
struct Result{
    T value;
    bool ok;
};

template<typename T>
class Deque{
    *T p;
    size_t front, back, cap;
public:
    Deque();
    ~Deque();
    void push_front(T x);
    void push_back(T x);
    Result<T> pop_front();
    Result<T> pop_back();
};

class BadNewQueue{
    Deque<int> vec;
public:
    BadNewQueue();
    ~BadNewQueue();
    void EnFront(int x);
    void EnMiddle(int x);
    void EnRear(int x);

    int DeFront();
    int DeMiddle();
    int DeRear();

    friend ostream& operator<<(ostream& os, const BadNewQueue& q);
};
#endif