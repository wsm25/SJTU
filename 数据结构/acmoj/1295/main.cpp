#include <cstdio>
#include <cmath>

int main(){
    unsigned n; scanf("%d", &n);
    if(n<=1) {
        printf("0.0000000000");
        return 0;
    }
    if(n>6e4){
        printf("%.10lf", 2./((log(n)-1.1)*n));
        return 0;
    }
    // isprime[n] is flag for n*2+1
    bool* isprime=new bool[n+1];
    for(int i=1; i<=(n-1)/2; i++) isprime[i]=true;
    isprime[1]=true;
    int count=1;
    for(int i=1; i<=(n-1)/2; i++){
        int k=i*2+1;
        if(!isprime[i]) continue;
        count++;
        for(int pn=i; pn<=(n-1)/2; pn+=k) 
            isprime[pn]=false;
    }
    printf("count: %u\n", count);
    printf("%.10lf", 2.*count/(n*n));
    return 0;
}