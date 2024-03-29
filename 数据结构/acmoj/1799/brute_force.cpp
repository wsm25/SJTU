#include <cstdio>
#include <cstdint>

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

int main(){
    int n=readuint();
    unsigned *cost=new unsigned[n];
    for(int i=0; i<n; i++){
        cost[i]=readuint();
    }
    uint64_t maxbuild=0;
    for(int i=0; i<n; i++){
        uint64_t sum=0, min=cost[i];
        for(int j=i; j<n; j++){
            sum+=cost[j];
            if (cost[j]<min) min=cost[j];
            uint64_t build=sum*min;
            if (build>maxbuild)
                maxbuild=build;
        }
    }
    printf("%lld", maxbuild);
    delete cost;
}