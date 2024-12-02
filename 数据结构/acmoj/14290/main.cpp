// src: https://www.cnblogs.com/vanhopex/p/15943379.html
#include <cstdio>
#include <cstring>
#include <vector>

inline unsigned readuint() {
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return x;
}

inline void putuint(unsigned x) {
    if(x==0) {putchar('0'); return;}
    char buf[12];
    int i=11;
    while(x!=0){
        buf[i--]=x%10;
        x=x/10;
    }
    while((++i)<12) putchar('0'+buf[i]);
}
int ans[100001]={0};
std::vector<int> edges[100001];

void dfs(int u,int k){
	if(ans[u]) return;
	ans[u]=k;
	for(int i=0;i<edges[u].size();i++){
		dfs(edges[u][i],k);
	}
}

int main() {
    int n=readuint(), m=readuint();
	while(m--){
        unsigned a=readuint(), b=readuint();
		edges[b].push_back(a);
	}
	for(int i=n;i>0;i--) dfs(i,i);
	for(int i=1;i<=n;i++){
        putuint(ans[i]);
        putchar(' ');
	}
	return 0;
}