#include <cstdio>
#include <functional>
struct Node;
Node* nodes;
inline int ri() {
    int x = 0, sign = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') sign = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return sign*x;
}

template<typename T>
struct Vec{
    T* buf;
    size_t n;
    Vec():buf(nullptr), n(0){}
    Vec(size_t cap):n(0){buf=new T[cap];}
    ~Vec(){if(buf) delete[]buf;}
    operator T*() {return buf;}
    void push(T value){buf[n++]=value;}
};

struct Node{
    int x,y;
    short index;
    short n=0;
    bool visited=false;
    short peers[100]; // 2k, static alloc
    void set(int x, int y, short index)
        {this->x=x; this->y=y; this->index=index;}
    void connect(short peer){peers[n++]=peer;}
    // can only call once
    bool has_peer(std::function<bool(int)> judge){
        if(judge(y)) return true;
        this->visited=true;
        short queue[1000];
        short* qhead=queue, *qtail=queue;
        *(qhead++)=index;
        while(qhead>qtail){
            Node &node=nodes[*(qtail++)];
            // printf("visiting node %d with %d peers\n", node-nodes, node->n);
            node.visited=true;
            if(judge(node.y)) return true;
            for(int i=0; i<node.n; i++){
                short in=node.peers[i];
                Node& n=nodes[in];
                // printf("got node %d from queue\n", n-nodes);
                if (!n.visited){
                    // printf("pushing node %d\n", n-nodes);
                    n.visited=true;
                    *(qhead++)=in;
                }
            }
        }
        return false;
    }
};

inline int sqr(int x){return x*x;}

// testcase: 2 1 4 1 1 1 3
// testcase2: 5 1 5  0 0  1 1  2 2  4 8  8 10
// testcase2: 8 1 5  0 0  1 1  2 2  3 1  4 2  5 1  6 2  6 4
int main(){
    int n=ri(), r=ri(), w=ri();
    int R=4*r*r;
    nodes=new Node[n];
    Vec<Node*> start(n);
    for(int i=0; i<n; i++){
        int x=ri(), y=ri();
        nodes[i].set(x,y,i);
    }
    for(short i=0; i<n; i++){
        int x=nodes[i].x, y=nodes[i].y;
        // connect
        for(short j=i+1; j<n; j++)
            if(sqr(x-nodes[j].x)+sqr(y-nodes[j].y)<=R){
                // printf("connect node %d, %d\n", i, j);
                nodes[i].connect(j);
                nodes[j].connect(i);
            }
        // start
        if(y<=r && y>=-r)
            start.push(nodes+i);
    }
    int w1=w-r, w2=w+r;
    bool canpass=false;
    for(size_t i=0; i<start.n; i++){
        if(start[i]->has_peer([=](int y){
            return y>=w1 && y<=w2;
        })){canpass=true; break;}
    }
    putchar('0'+canpass);
    delete []nodes;
    return 0;
}