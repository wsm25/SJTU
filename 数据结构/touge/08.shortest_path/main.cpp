#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
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

// empty if no route
// visited: stack
void min_route(GraphNode* node, GraphVec& visited){
    visited.push_back(node);
    auto &r=node->minroute;
    // DFS relaxation
    if(r.size()==0 || visited.size()<r.size()){
        r=visited;
        for(auto &ch:node->child){
            min_route(ch, visited);
        }
    }
    visited.pop_back();
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
    GraphVec st;
    min_route(buf+from, st);
    auto &r=buf[to].minroute;
    if(r.empty()) printf("false");
    else for(auto &n:r) printf("%d ", n-buf);
    delete []buf;
}