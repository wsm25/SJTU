#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_set>
bool readuint(unsigned &x) {
    x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    if(ch=='\n') return false;
    return true;
}

struct GraphNode;
typedef std::vector<GraphNode*> GraphVec;
struct GraphNode{
    GraphVec child;
    GraphVec minroute;
};

// GraphNode* for dijkstra priority_queue
// Node minroute must non-empty
struct DNode{
    GraphNode* p;
    size_t weight;
    DNode(GraphNode* p):p(p){
        weight=p->minroute.size();
    }
    bool operator>(const DNode& rhs) const{
        return weight>rhs.weight ||
               weight==rhs.weight && p>rhs.p;
    }
};

template<typename T>
using min_queue=std::priority_queue<T, std::vector<T>, std::greater<T>>;

void dijkstra(GraphNode* src){
    min_queue<DNode> Q;
    std::unordered_set<GraphNode*> visited;
    src->minroute.push_back(src);
    Q.push(DNode(src));
    while(!Q.empty()){
        GraphNode* n=Q.top().p;
        Q.pop();
        if(visited.find(n)!=visited.end()) continue;
        else visited.insert(n);
        for(auto p:n->child){
            auto sp=p->minroute.size(),
                 sn=n->minroute.size();
            // relaxation
            if(sp==0 || sp>sn+1){
                p->minroute=n->minroute;
                p->minroute.push_back(p);
                Q.push(DNode(p));
            }
        }
    }
}

int main(){
    unsigned N;
    readuint(N);
    GraphNode* buf=new GraphNode[N+1];
    bool oldline=true;
    while(oldline){ // assume at least one edge
        unsigned m,n;
        readuint(m);
        oldline=readuint(n);
        buf[m].child.push_back(buf+n);
    }
    // ensure less node is at front
    for(int i=1; i<=N; i++){
        auto& child=buf[i].child;
        std::sort(child.begin(), child.end());
    }
    unsigned from, to;
    readuint(from); readuint(to);
    dijkstra(buf+from);
    auto &r=buf[to].minroute;
    if(r.empty()) printf("false");
    else for(auto &n:r) printf("%d ", n-buf);
    delete []buf;
}