#ifndef TABLE_H
#define TABLE_H
#include <iostream>

struct Node; // defined in table.cc

class NodeList{
    Node* head;
    Node* tail();
public:
    NodeList();
    ~NodeList();
    bool insert(size_t i, int x);
    void erase(int from, int to);
    size_t len();
    friend std::istream& operator>>(std::istream& is, NodeList& l);
    friend std::ostream& operator<<(std::ostream& os, const NodeList& l);
};
#endif