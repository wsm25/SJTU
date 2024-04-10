#include <cstdio>
#include <cstring>
inline unsigned readuint() {
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x;
}

class Dsu{
public:
    // msb is root flag; if root, it is negative counter
    unsigned *nodes, n;
    Dsu(int n):n(n){
        nodes=new unsigned[n+1];
        memset(nodes, -1, (n+1)*sizeof(unsigned));
    }
    ~Dsu(){delete []nodes;}
    unsigned rootof(unsigned x){ // with route compression
        return (nodes[x]&(1<<31)) ? x : (nodes[x]=rootof(nodes[x]));
    }
    void connect(unsigned x, unsigned y){
        nodes[rootof(x)]=rootof(y); // connect two sets
    }
};

// sample: 3 2 1 2 1 3
// output: 3
int main(){
    unsigned n=readuint(), m=readuint();
    Dsu forest(n);
    for(int i=0; i<m; i++)
        forest.connect(readuint(), readuint());
    for(int i=1; i<=n; i++)
        forest.nodes[forest.rootof(i)]--;
    unsigned maxsum=0;
    for(int i=1; i<=n; i++){
        unsigned t=forest.nodes[i];
        if ((t&(1<<31)) && (~t)>maxsum)
            maxsum=~t;
    }
    printf("%d", maxsum);
    return 0;
}