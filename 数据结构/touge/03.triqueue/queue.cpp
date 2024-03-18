#include "queue.h"

NewQueue::NewQueue():
    front(nullptr),
    end(nullptr),
    middle(nullptr),
    len(0)
    {}

NewQueue::~NewQueue(){
    while(front!=nullptr){
        auto p=front->right;
        delete front;
        front=p;
    }
}

// push
inline bool NewQueue::encheck(int x){
    len++;
    if (len==1){
        front=middle=end=new DNode(x);
        return true;
    }
    return false;
}

void NewQueue::EnFront(int x){
    if (encheck(x)) return;
    auto p = new DNode(nullptr, front, x);
    front->left=p;
    front=p;
    if (!(len&1)) {
        middle=middle->left;
    }
    
}

void NewQueue::EnMiddle(int x){
    if (encheck(x)) return;
    if (len&1){ // right of middle
        auto r=middle->right; // never null
        auto p = new DNode(middle, r, x);
        r->left=p;
        middle->right=p;
        middle=p;
    } else {
        auto l=middle->left; // may null
        auto p = new DNode(l, middle, x);
        if (len==2){
            middle->left=p;
            front=p;
        } else {
            l->right=p;
            middle->left=p;
        }
        middle=p;
    }
}

void NewQueue::EnRear(int x){
    if (encheck(x)) return;
    auto p = new DNode(end, nullptr, x);
    end->right=p;
    end=p;
    if ((len&1)) {
        middle=middle->right;
    }
}

//pop
inline DeCheck NewQueue::decheck(){
    if (len==0){
        return DeCheck{-1, true};
    }
    len--;
    if (len==0){
        auto r=DeCheck{middle->x, true};
        delete middle;
        front=middle=end=nullptr;
        return r;
    }
    return DeCheck{0, false};
}

int NewQueue::DeFront(){
    auto ck=decheck();
    if (ck.ok) return ck.x;
    if ((len&1)) {
        middle=middle->right;
    }
    int x = front->x;
    auto p = front;
    front=front->right;
    front->left=nullptr;
    delete p;
    return x;
}

int NewQueue::DeMiddle(){
    auto ck=decheck();
    if (ck.ok) return ck.x;
    int x = middle->x;
    if (len==1){
        front=middle=end=middle->right;
        return x;
    }
    auto p = middle;
    if ((len&1)) {
        auto l = middle->left; // may null
        middle=middle->right; // never null
        delete(p);
        if (l) l->right=middle;
        middle->left=l;
    } else {
        auto r = middle->right; // never null
        middle=middle->left; // never null
        delete(p);
        middle->right=r;
        r->left=middle;
    }
    return x;
}

int NewQueue::DeRear(){
    auto ck=decheck();
    if (ck.ok) return ck.x;
    if (!(len&1)) {
        middle=middle->left;
    }
    int x = end->x;
    auto p = end;
    end=end->left;
    end->right=nullptr;
    delete p;
    return x;
}

ostream& operator<<(ostream& os, const NewQueue& q){
    auto p=q.front;
    if (p==nullptr){
        return os<<"null";
    }
    while(p->right!=nullptr){
        os<<p->x<<' ';
        p=p->right;
    }
    return os<<p->x;
}