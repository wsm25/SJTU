//! Just a O(n^2) simple algorithm, modified from bubble sort.

#include <cstdio>
inline int readint() {
    int x=0, sign=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-') sign=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return sign*x;
}

struct GirlsBandCry{
    int val, count;
};

int main(){
    GirlsBandCry buf[50001];
    int buflen=0, len=readint();
    for(int i=0; i<len; i++){
        int x=readint();
        int j=buflen-1;
        while(j>=0 && buf[j].val!=x) j--;
        if(j<0) buf[buflen++]={x, 1}; // newbie
        else { // found, float up
            auto X=buf[j];
            int cnt=X.count;
            while((--j)>=0 && buf[j].count==cnt){
                buf[j+1]=buf[j];
            }
            X.count++;
            buf[j+1]=X;
        }
    }
    int k=readint();
    int minele, i=0;
    for(int j=0; j<buflen && i<k; i++){
        int cnt=buf[j].count;
        minele=buf[j].val;
        while((++j)<buflen && buf[j].count==cnt)
            if(buf[j].val<minele) minele=buf[j].val;
    }
    if(i==k) printf("%d", minele);
    else printf("error");

}