#include <stdio.h>
#include <algorithm>
#include <numeric>

typedef unsigned u32;

u32 readuint() {
    u32 x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return x;
}

int main() {
    u32 n = readuint(), m = readuint();
    u32 *a = new u32[n];
    for(int i=0; i<n; i++) a[i] = readuint();
    std::sort(a, a+n);
    u32 s = std::accumulate(a, a+n, 0u);
    int cap = a[n-1];
    for(int i = n-1; i>=0; i--) {
        if(s<=m) break;
        u32 bot = i==0 ? 0 : a[i-1];
        // attempt: cut at [a[i], cap)
        u32 b = (a[i]-bot)*(n-i);
        if(s-b<=m) {
            cap = a[i] - (s-m+n-i-1)/(n-i);
            break;
        }
        s -= b;
        cap = bot;
    }
    if(cap==a[n-1]) printf("infinite");
    else printf("%u", cap);
    delete []a;
}