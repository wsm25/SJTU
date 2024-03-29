#include <algorithm>
#include <cstdio>
#include <cstdint>

struct Corr{
    unsigned x,y;
    bool operator<(const Corr rhs){return y<rhs.y;}
};

inline unsigned readuint() {
    unsigned x = 0;
    char ch = getchar();
    while (ch<'0' || ch>'9')
        ch = getchar();
    while (ch>='0' && ch<='9'){
        x = x*10+ch-'0';
        ch = getchar();
    } 
    return x;
}

inline unsigned uabs(unsigned x){
    return x>=0?x:-x;
}

int main(){
    unsigned N=readuint(), D=readuint();
    Corr* missles=new Corr[N];
    for(int i=0;i<N;i++){
        missles[i].x=readuint();
        missles[i].y=readuint();
    }
    unsigned mindx=UINT32_MAX;
    for(int i=0; i<N; i++){
        for(int j=i+1; j<N; j++){
            if (uabs(missles[j].y-missles[i].y)<D) continue;
            unsigned dx=uabs(missles[j].x-missles[i].x);
            if (dx<mindx) mindx=dx;
        }
    }
    if (mindx==UINT32_MAX) printf("-1");
    else printf("%d", mindx);
}