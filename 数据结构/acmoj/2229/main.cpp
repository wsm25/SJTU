#include <cstdio>
#include <cstdint>

// 0 if invalid
uint64_t readstr() {
    uint64_t n=0; int empty=6;
    char ch=getchar();
    while(ch!='#' && (ch<'a' || ch>'z')) ch=getchar();
    if(ch=='#') {return 0;}
    while(ch>='a' && ch<='z'){
        empty--;
        n=(n<<8)|ch;
        ch=getchar();
    }
    n<<=empty*8;
    return n;
}

template<typename T>
struct Pool{
    T *base, *cur;
    Pool(size_t n){base=cur=new T[n];}
    ~Pool(){delete []base;}
    T* get(){return cur++;}
};

struct Node{
    uint64_t str;
    Node *left, *right;
    Node* find(const uint64_t s){
        Node* p=this;
        while(p!=nullptr){
            if(s==p->str) return p;
            else if(s<p->str) p=p->left;
            else p=p->right;
        }
        return nullptr;
    }
};

Pool<Node> *pool;


Node* readtree(int& n){
    if(n==0) return nullptr;
    uint64_t s=readstr();
    n--;
    if(s==0) return nullptr;
    Node* p=pool->get();
    p->str=s;
    p->left=readtree(n);
    p->right=readtree(n);
    return p;
}

int main(){
    int k,m;
    (void)scanf("%d %d", &k, &m);
    pool=new Pool<Node>(k>1000000?1000000:k);
    Node* tree=readtree(k);
    for(int i=0; i<m; i++){
        auto s=readstr();
        if(tree->find(s))
            putchar('T');
        else putchar('F');
    }
    delete pool;
    return 0;
}
