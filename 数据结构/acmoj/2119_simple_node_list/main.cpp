#include<iostream>
using namespace std;

struct Node {
    int value;
    Node* next;
};

class LinkedList {
    int len;
    Node* head;
public:
    void initialize() {
        head=new Node;
        scanf("%d", &len);
        Node* p=head;
        for(int i = 0; i < len; i++){
            p->next=new Node;
            p=p->next;
            scanf("%d", &(p->value));
        }
        p->next=nullptr;
    }

    void insert(int i, int x) {
        Node *p=head;
        while(p!=nullptr && (i--)>0) p=p->next;
        if(p==nullptr) return; //error
        len++;
        Node *next=p->next;
        p->next=new Node;
        p=p->next;
        p->value=x;
        p->next=next;
    }

    void eraseFromHead(int i) {
        Node *p=head;
        while(p!=nullptr && (--i)>0) p=p->next;
        if(p==nullptr) return; //error
        if (p->next!=nullptr){
            Node *next=p->next->next;
            delete p->next;
            p->next=next;
            len--;
        }
    }

    void eraseFromEnd(int i) {
        eraseFromHead(len+1-i);
    }

    void printAll() {
        if (head->next==nullptr) return;
        Node* p=head->next;
        while(p->next!=nullptr){
            printf("%d ", p->value);
            p=p->next;
        }
        printf("%d", p->value);
    }

    void ClearMemory() {
        Node* p=head->next;
        while(p!=nullptr){
            delete head;
            head=p;
            p=p->next;
        }
    }
};

int main() {
    LinkedList List;
    int m, op, i, x;
    List.initialize();
    scanf("%d", &m);
    while(m--) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%d%d", &i, &x);
            List.insert(i, x);
        }
        else if(op == 2) {
            scanf("%d", &i);
            List.eraseFromHead(i);
        }
        else if(op == 3) {
            scanf("%d", &i);
            List.eraseFromEnd(i);
        }
    }
    List.printAll();
    List.ClearMemory();
    return 0;
}