#include <cstdio>
inline unsigned readuint() {
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return x;
}

inline void putuint(unsigned x) {
    if(x==0) {putchar('0'); return;}
    char buf[12];
    int i=11;
    while(x!=0){
        buf[i--]=x%10;
        x=x/10;
    }
    while((++i)<12) putchar('0'+buf[i]);
}

#define LOG2(X) (63 - __builtin_clzll(X))

struct Parent{
    unsigned index;
    unsigned distance;
};

// 35*4=140
struct Node{
    unsigned depth;
    Parent parents[17]; // parent[i] is (1<<n) level parent node
};


int main(){
    unsigned n=readuint(), m=readuint();
    Node *nodes=new Node[n+1]; // 14M max
    for(int i=1; i<=n; i++) nodes[i].depth=-1; // set as new
    // first input
    unsigned root=readuint(); // let first input node as root
    nodes[root].depth=0;
    unsigned next=readuint(), dist=readuint();
    nodes[next].depth=1;
    nodes[next].parents[0]={root, dist};
    // other input
    while(--m){
        unsigned some=readuint(), next=readuint(), dist=readuint();
        // let next the new
        if(nodes[some].depth==-1) {int t=some; some=next; next=t;}
        auto &node=nodes[next];
        // first parent
        node.depth=nodes[some].depth+1;
        node.parents[0]={some, dist};
        auto *parent=nodes[some].parents;
        int depth=nodes[some].depth-1, i=1;
        while(depth>=0){
            // parent: parent 1<<(i-1) of parent 1<<(i-1)
            dist+=parent->distance;
            node.parents[i]={parent->index, dist};
            // next
            depth-=(1<<i);
            parent=&nodes[parent->index].parents[i++];
        }
    }
    // query
    int Q=readuint();
    while(Q--){
        int x=readuint(), y=readuint();
        int dist=0;
        // let x deeper
        if(nodes[x].depth<nodes[y].depth) {int t=x; x=y; y=t;}
        // jump to same depth
        int diff=nodes[x].depth-nodes[y].depth;
        while(diff>0){
            int step=LOG2(diff);
            int next=nodes[x].parents[step].index;
            dist+=nodes[x].parents[step].distance;
            x=next;
            diff-=(1<<step);
        }
        // check if same
        if (x==y) {putuint(dist); putchar('\n'); continue;}
        // jump to common parent
        int depth=nodes[x].depth-1;
        for(;;){
            int step=LOG2(depth);
            // assume x!=y
            if(nodes[x].parents[0].index==nodes[y].parents[0].index){ // found
                dist+=nodes[x].parents[0].distance+nodes[y].parents[0].distance;
                break;
            }
            int xx=nodes[x].parents[step].index, 
                yy=nodes[y].parents[step].index;
            if(xx==yy) { // rollback
                depth=(1<<step)-1;
            } else { // jump
                dist+=nodes[x].parents[step].distance+
                      nodes[y].parents[step].distance;
                x=xx, y=yy;
                depth-=1<<step;
            }
        }
        putuint(dist); putchar('\n');
    }
    delete []nodes;
    return 0;
}