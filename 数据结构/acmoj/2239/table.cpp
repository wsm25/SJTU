#include <cstdio>
#include <algorithm>
#define MAX 1000
bool nonprime[MAX+1]={0};
int primes[MAX+1];
int primes_len=0;
int facts[MAX+1]={0};



int main(){
    // generate prime table
    int n=2;
    while(n<=MAX){
        primes[primes_len++]=n;
        facts[n]=1;
        for(int m=n*2; m<=MAX; m+=n) 
            nonprime[m]=true;
        do n++; while(n<=MAX && nonprime[n]);
    }
    printf("primes: ");
    for(int i=0; i<primes_len; i++) printf("%d ", primes[i]);
    putchar('\n');
    // generate fact count table
    for(int i=2; i<=MAX/2; i++){
        for(int j=0; j<primes_len; j++){
            int cur=primes[j];
            if(i*cur>MAX) break;
            facts[i*cur]=facts[i]+1;
        }
    }
    printf("fact count table: ");
    for(int i=1; i<=MAX; i++) printf("%d ", facts[i]);
    putchar('\n');
    // generate weight table
    int weight[MAX+1];
    for(int i=0; i<=MAX; i++) weight[i]=i;
    std::sort(weight, weight+MAX+1, [](const int lhs, const int rhs){
        return facts[lhs]<facts[rhs] || 
            (facts[lhs]==facts[rhs] && lhs<rhs);
    });
    printf("weight map table: ");
    for(int i=0; i<=MAX; i++) printf("%d, ", weight[i]);
    putchar('\n');
}