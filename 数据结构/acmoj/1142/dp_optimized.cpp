// with careful register optimization, 
// making about 15% performance increase
#include <iostream>
#include <algorithm>
typedef unsigned long long u64;

int main(){
    unsigned primes[100], p[100]={0};
    u64 dp[10001];
    dp[0]=1;
    unsigned k, n;
    std::cin>>k>>n;
    u64 minprod=114514;
    // primes
    for(int i=0; i<k; i++){
        unsigned pi;
        std::cin>>pi;
        if(pi<minprod) minprod=pi;
        primes[i]=pi;
    } 
    for(int i=1; i<=n; i++){
        auto last=minprod;
        dp[i]=last;
        minprod=1145141919810;
        for(int j=0; j<k; j++){
            auto prime=primes[j], pj=p[j];
            u64 prod;
            while((prod=dp[pj]*prime)<=last) pj++;
            if(prod<minprod) minprod=prod;
            p[j]=pj;
        }
    }
    std::cout<<dp[n];
}