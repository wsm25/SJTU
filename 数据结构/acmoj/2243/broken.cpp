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

// 35*4=140
struct Node{
    int depth;
    unsigned parents[17]; // parent[i] is (1<<n) level parent node
};


int main(){
    int n=readuint(), Q=readuint(), m=n-1;
    readuint();
    Node *nodes=new Node[n+1]; // 14M max
    for(int i=1; i<=n; i++) nodes[i].depth=-1; // set as new
    // first input
    unsigned root=readuint(); // let first input node as root
    nodes[root].depth=0;
    unsigned next=readuint();
    nodes[next].depth=1;
    nodes[next].parents[0]=root;
    // other input
    while((--m)>0){
        unsigned some=readuint(), next=readuint();
        // let next the new
        if(nodes[some].depth==-1) {int t=some; some=next; next=t;}
        auto &node=nodes[next];
        // first parent
        node.depth=nodes[some].depth+1;
        node.parents[0]=some;
        auto *parent=nodes[some].parents;
        int depth=nodes[some].depth-1, i=1;
        while(depth>=0){
            node.parents[i]=*parent;
            // next
            depth-=(1<<i);
            parent=&nodes[*parent].parents[i++];
        }
    }
    // query
    while(Q--){
        int x=readuint(), y=readuint();
        // let x deeper
        if(nodes[x].depth<nodes[y].depth) {int t=x; x=y; y=t;}
        // jump to same depth
        int diff=nodes[x].depth-nodes[y].depth;
        while(diff>0){
            int step=LOG2(diff);
            int next=nodes[x].parents[step];
            x=next;
            diff-=(1<<step);
        }
        // check if same
        if (x==y) {putuint(x); putchar('\n'); continue;}
        // jump to common parent
        int depth=nodes[x].depth-1;
        for(;;){
            int step=LOG2(depth);
            // assume x!=y
            if(nodes[x].parents[0]==nodes[y].parents[0]){ // found
                break;
            }
            int xx=nodes[x].parents[step], 
                yy=nodes[y].parents[step];
            if(xx==yy) { // rollback
                depth=(1<<step)-1;
            } else { // jump
                x=xx, y=yy;
                depth-=1<<step;
            }
        }
        putuint(nodes[x].parents[0]); putchar('\n');
    }
    delete []nodes;
    return 0;
}