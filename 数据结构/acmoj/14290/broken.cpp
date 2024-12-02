#include <cstdio>
#include <algorithm>

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

struct Edge{
    unsigned from, to;
    bool operator<(const Edge &rhs){
        return to>rhs.to;
    }
};

int main(){
    unsigned n=readuint();
    int m=readuint();
    Edge *edges=new Edge[m];
    unsigned *max=new unsigned[n+1];
    for(unsigned i=0; i<=n; i++) max[i]=i;
    for(int i=0; i<m; i++)
        edges[i]={readuint(), readuint()};
    std::sort(edges, edges+m);
    for(int i=0; i<m; i++){
        unsigned from=edges[i].from;
        unsigned to=edges[i].to; // to decreases
        if(max[from]<max[to]) max[from]=max[to];
    }
    delete []edges;
    for(unsigned i=1; i<=n; i++){
        putuint(max[i]);
        putchar(' ');
    }
    delete []max;
}