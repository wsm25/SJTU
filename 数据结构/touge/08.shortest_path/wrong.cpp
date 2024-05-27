#include <cstdio>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f
bool readuint(unsigned &x) {
    x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    if(ch=='\n') return false;
    return true;
}

template<typename T>
class Square{
    T* base;
    size_t n;
public:
    Square(size_t n):n(n){
        base=new T[n*n];
        memset(base, INF, n*n*sizeof(T));
    }
    ~Square(){
        delete []base;
    }
    T* operator[](size_t m){
        return base+m*n;
    }
};

struct EdgeDist{
    int id;
    int dist;
    bool operator>(const EdgeDist& rhs) const{
        return dist>rhs.dist;
    }
};

int main(){
    unsigned N;
    readuint(N);
    Square<int> mindist(N+1);
    bool oldline=true;
    while(oldline){ // assume at least one edge
        unsigned m,n;
        readuint(n);
        oldline=readuint(m);
        mindist[n][m]=1;
    }
    unsigned from, to;
    readuint(from); readuint(to);
    // Dijkstra
    std::priority_queue<EdgeDist, std::vector<EdgeDist>, std::greater<EdgeDist>> q;
    int* f=mindist[from];
    for(unsigned i=1; i<=N; i++)
        if(f[i]!=INF)
            q.push(EdgeDist{int(i), f[i]});
    while(!q.empty()){
        EdgeDist d=q.top();
        q.pop();
        int *g=mindist[d.id];
        int suc=0;
        for(unsigned i=1; i<=N; i++){
            if(g[i]+d.dist<f[i]) {
                suc=i;
                f[i]=g[i]+d.dist;
            }
        }
        if(suc!=0) q.push(EdgeDist{suc, f[suc]});
    }
    if(f[to]==INF) printf("false");
    else printf("%d", f[to]);
}