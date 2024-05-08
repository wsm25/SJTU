// faster if hash table is used
#include <cstdio>
#include <cstring>

inline unsigned readuint() {
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return x;
}
inline void putint(int x) {
    if(x==0) {putchar('0'); putchar('\n'); return;}
    if(x<0) {x=-x; putchar('-');}
    char buf[12];
    int i=11;
    while(x!=0){
        buf[i--]=x%10;
        x=x/10;
    }
    while((++i)<12) putchar('0'+buf[i]);
    putchar('\n');
}
int hashtable[200001];
// example: 5 1 5 7 9 10 3 5 8 9
// example output: 1 -1 3
int main(){
    memset(hashtable, -1, 200001*sizeof(int));
    int n=readuint();
    for(int i=0; i<n; i++) hashtable[readuint()]=i;
    int m=readuint();
    for(int i=0; i<m; i++) putint(hashtable[readuint()]);
    return 0;
}