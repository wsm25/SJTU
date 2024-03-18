#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
using std::ostream;

struct DNode{
    DNode *left, *right;
    int x;
    DNode(DNode* left, DNode* right, int x) 
        :left(left), right(right), x(x){}
    DNode(int x) :left(nullptr), right(nullptr), x(x){}
};

struct DeCheck{int x; bool ok;};

class NewQueue{
    DNode *front, *end, *middle;
    size_t len;
    inline bool encheck(int x); // modifies len true return
    inline DeCheck decheck(); // false continue
public:
    NewQueue();
    ~NewQueue();
    void EnFront(int x);
    void EnMiddle(int x);
    void EnRear(int x);

    int DeFront();
    int DeMiddle();
    int DeRear();

    friend ostream& operator<<(ostream& os, const NewQueue& q);
};
#endif