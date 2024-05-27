#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
bool readuint(unsigned &x) {
    x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch==EOF) return false;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return true;
}

struct GraphNode;
typedef std::vector<GraphNode*> GraphVec;
struct GraphNode{
    GraphVec child;
    int ins=0;
};

template<typename T>
using min_queue=std::priority_queue<T, std::vector<T>, std::greater<T>>;

// implemented with Kahn Algorithm
GraphVec toposort(GraphNode* G, size_t n) {
    GraphVec L;
    min_queue<GraphNode*> S;
    for(size_t i=1; i<=n; i++)
        if (G[i].ins == 0) S.push(G+i);
    while(!S.empty()) {
        GraphNode* u=S.top();
        S.pop();
        L.push_back(u);
        for(auto v : u->child) 
            if ((--v->ins)==0) S.push(v);
    }
    return L;
}

int main(){
    unsigned N;
    readuint(N);
    GraphNode* buf=new GraphNode[N+1];
    while(true){ // assume at least one edge
        unsigned m,n;
        if(!readuint(m)) break;
        readuint(n);
        buf[m].child.push_back(buf+n);
        buf[n].ins++;
    }
    // ensure less node is at front
    for(int i=1; i<=N; i++){
        auto& child=buf[i].child;
        std::sort(child.begin(), child.end());
    }
    GraphVec L=toposort(buf, N);
    if(L.size()==N)
        for(auto p:L) printf("%d ", int(p-buf));
    else printf("loop");
    delete []buf;
}