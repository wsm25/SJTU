#include "table.h"
#include <iostream>

struct Node{
    int value;
    Node* next;
    Node(){next=nullptr;}
    Node(int n){value=n;next=nullptr;}
    Node* forward(size_t);
};

NodeList::NodeList(){
    head=new Node();
}

NodeList::~NodeList(){
    auto p=head;
    while(p->next!=nullptr){
        head=p;
        p=head->next;
        delete head;
    }
}

size_t NodeList::len(){
    auto p=head->next;
    size_t n=0;
    while(p!=nullptr){
        p=p->next;
        n++;
    }
    return n;
}

Node* Node::forward(size_t n){
    auto p=this;
    while(n>0&&p!=nullptr){
        p=p->next;
        n--;
    }
    return p;
}

bool NodeList::insert(size_t i, int x){
    auto p=head->forward(i);
    if(p==nullptr) return false;
    auto insnode=new Node(x);
    auto pnext=p->next;
    p->next=insnode;
    insnode->next=pnext;
    return true;
}

void unsafe_delete(Node* from, Node* to){
    while(from!=nullptr && from!=to){
        auto p=from->next;
        delete from;
        from=p;
    }
}

void NodeList::erase(int from, int to){
    if (from>to) return;
    auto p=head;
    while(p->next!=nullptr){
        int n=p->next->value;
        if(n>=from && n<=to){
            auto tmp=p->next->next;
            delete p->next;
            p->next=tmp;
        }
        else p=p->next;
    }
}

Node* NodeList::tail(){
    auto p=head;
    while(p->next!=nullptr) p=p->next;
    return p;
}

using std::istream;
istream& operator>>(istream& is, NodeList& l){
    int i;
    char ch;
    auto p=l.tail();
    for(;;){
        is>>i;
        p->next=new Node(i);
        p=p->next;
        is.get(ch);
        if (ch!=' ') break;
    }
    return is;
}

using std::ostream;
ostream& operator<<(ostream& os, const NodeList& l){
    auto p=l.head->next;
    if (p==nullptr){
        return os<<"null";
    }
    while(p->next!=nullptr){
        os<<p->value<<' ';
        p=p->next;
    }
    return os<<p->value;
}