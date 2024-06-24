#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

inline int readint() {
    int x=0, sign=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-') sign=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return sign*x;
}

struct Node{
    std::vector<Node*> edge;
    bool visited=false;
    int favlen=0;
    int fav[50];
};

int main(){
    int n=readint();
    int id=readint(), level=readint();
    Node* nodes=new Node[n];
    for(int i=0; i<n; i++){
        int k;
        while((k=readint())!=-1)
            nodes[i].fav[nodes[i].favlen++]=k;
    }
    for(int i=0; i<n; i++){
        int k;
        while((k=readint())!=-1){
            nodes[i].edge.push_back(nodes+k);
            nodes[k].edge.push_back(nodes+i);
        }
    }
    std::vector<std::vector<Node*>> queues;
    queues.push_back(std::move(
        std::vector<Node*>({nodes+id})
    ));
    nodes[id].visited=true;
    while(!queues.back().empty()){
        std::vector<Node*> q;
        for(auto m:queues.back())
            for(auto p:m->edge)
                if(!p->visited){
                    p->visited=true;
                    q.push_back(p);
                }
        queues.push_back(std::move(q));
    }
    auto &selected=queues[level%(queues.size()-1)];
    std::vector<int> favs;
    for(auto p:selected)
        for(int i=0; i<p->favlen; i++)
            favs.push_back(p->fav[i]);
    std::sort(favs.begin(), favs.end());
    auto end=std::unique(favs.begin(), favs.end());
    for(auto p=favs.begin(); p<end; p++)
        printf("%d ", *p);
    delete []nodes;
}