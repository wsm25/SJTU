#include <cstdio>
#include <vector>
#include <queue>

inline unsigned readuint() {
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return x;
}

struct Node{
    std::vector<Node*> edges;
    int count=0;
};

int main(){
    unsigned n=readuint();
    unsigned m=readuint();
    Node* nodes=new Node[n];
    while(m--){
        unsigned i=readuint();
        unsigned j=readuint();
        nodes[i].edges.push_back(nodes+j);
        nodes[j].count++;
    }
    std::priority_queue<Node*, std::vector<Node*>, std::greater<Node*>> q;
    for(unsigned i=0; i<n; i++)
        if(nodes[i].count==0)
            q.push(nodes+i);
    while(!q.empty()){
        Node* node=q.top(); q.pop();
        printf("%lld ", node-nodes);
        for(auto p:node->edges){
            if(--p->count == 0)
                q.push(p);
        }
    }
    delete []nodes;
    return 0;
}