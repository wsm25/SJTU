#include <algorithm>
#include <cstdio>
#include <cstdint>

inline unsigned readuint() {
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return x;
}

int main(){
    int n=readuint();
    int *ni=new int[n];
    for(int i=0; i<n; i++) ni[i]=readuint();
    std::sort(ni, ni+n);
    int w=n-1, z=0;
    int64_t wcnt=0, zcnt=0;
    int count=0;
    // ni==0 -> taken
    for(;;){
        // w
        while(w>=0 && (ni[w]==0 || (ni[w]&1))) w--;
        if(w<0) break;
        wcnt+=ni[w]; ni[w]=0;
        // z
        while(z<n && ni[z]==0) z++;
        if(z==n) break;
        zcnt+=ni[z]; ni[z]=0;
    }
    while(z<n) zcnt+=ni[z++]; // remained
    if(wcnt>zcnt) putchar('W');
    else if(wcnt<zcnt) putchar('Z');
    else putchar('0');
}