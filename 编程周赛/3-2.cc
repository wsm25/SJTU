#include <stdio.h>
#include <numeric>
#define M 998244353ll

typedef long long u64;

int main() {
    int s, n;
    scanf("%d%d", &s, &n);
    // dp[j] is count of i+1-lengthed line in j+1 color
    // obviously dp[0] === 1
    u64* dp = new u64[s]();
    dp[0]=1;
    for(int i=0; i<n-1; i++)
        for(long long j=s-1; j>0; j--)
            dp[j] = (dp[j]*(j+1)+dp[j-1]) % M;
    u64 sum = 0;
    
    for(int i=0; i<s; i++) sum = (sum+dp[i])%M;
    printf("%d", sum);
    delete []dp;
    return 0;
}
