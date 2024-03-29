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
    // 1.2M mem max
    unsigned *cost=new unsigned[n];
    // prefix sum, sum of [i,j] is prefixsum[j]-prefixsum[i-1]
    uint64_t *prefixsum=new uint64_t[n+1];
    uint64_t sum=0;
    *(prefixsum++)=0;
    for(int i=0; i<n; i++){
        unsigned input=cost[i]=readuint();
        prefixsum[i]=(sum+=input);
    }
    // nearest less
    int *left=new int[n], *right=new int[n];
    unsigned *stack=new unsigned[n], *p=stack-1;
    for(int i=0; i<n; i++){
        unsigned x=cost[i];
        while(p>=stack && cost[*p]>=x) p--;
        left[i] = p>=stack ? *p : -1;
        *(++p)=i;
    }
    p=stack-1;
    for(int i=n-1; i>=0; i--){
        unsigned x=cost[i];
        while(p>=stack && cost[*p]>=x) p--;
        right[i] = p>=stack ? (*p)-1 : n-1;
        *(++p)=i;
    }
    // maxbuild
    uint64_t maxbuild=0;
    for(int i=0; i<n; i++){
        uint64_t build=
            uint64_t(cost[i])*
            (prefixsum[right[i]]-prefixsum[left[i]]);
        if (build>maxbuild) maxbuild=build;
    }
    printf("%llu", maxbuild);
    delete []cost;
    delete []left;
    delete []right;
    delete [](prefixsum-1);
    delete []stack;
}