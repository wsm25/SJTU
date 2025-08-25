#include <stdio.h>
#include <vector>

typedef int edge_t[2];
typedef std::vector<edge_t*> vertex_t;

int r() {
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return x;
}

vertex_t* v;
edge_t* e;

int rev(int iv, int src) {
    int cnt = 0;
    for(edge_t *x:v[iv]) {
        if((*x)[0]==src || (*x)[1]==src) continue;
        if((*x)[0]==iv) {
            cnt += rev((*x)[1], iv) + 1;
        } else {
            cnt += rev((*x)[0], iv);
        }
    }
    return cnt;
}

int main() {
    int n = r();
    v = new vertex_t[n];
    e = new edge_t[n-1];
    for(int i=0; i<n-1; i++) {
        int a = r(), b = r();
        v[a].push_back(e+i);
        v[b].push_back(e+i);
        e[i][0]=a; e[i][1]=b;
    }
    printf("%d", rev(0, -1));
    delete []v;
    delete []e;
}