#include <iostream>
#include <algorithm>

int main(){
    unsigned primes[100], p[100]={0};
    unsigned long long dp[10001];
    dp[0]=1;
    unsigned k, n;
    std::cin>>k>>n;
    for(int i=0; i<k; i++) std::cin>>primes[i];
    unsigned long long minprod=*std::min_element(primes, primes+k);
    for(int i=1; i<=n; i++){
        auto last=minprod;
        dp[i]=last;
        minprod=1145141919810;
        for(int j=0; j<k; j++){
            unsigned long long prod;
            while((prod=dp[p[j]]*primes[j])<=last) p[j]++;
            if(prod<minprod) minprod=prod;
        }
    }
    std::cout<<dp[n];
}