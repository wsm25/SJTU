#include <iostream>
#include <cstdint>
#define MOD 1000000007
uint64_t p(unsigned n){
    if(n<=1) return 1;
    uint64_t base[1001];
    base[0]=base[1]=1;
    for(unsigned j=2; j<=n; j++){
        uint64_t sum=0;
        for(int i=0; i<j; i++)
            sum=(sum+base[i]*base[j-i-1])%MOD;
        base[j]=sum;
    }
    return base[n];
}
int main(){
    unsigned n;
    std::cin>>n;
    std::cout<<p(n);
    return 0;
}