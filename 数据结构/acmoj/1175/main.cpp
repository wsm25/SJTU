#include <cstdio>
#include <cstdint>
#include <algorithm>

inline int64_t readint() {
    int64_t x=0, sign=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-') sign=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return sign*x;
}

int main(){
    int64_t N=readint();
    int64_t *li=new int64_t[N+1];
    int64_t sum=0;
    li[0]=0;
    for(int i=1; i<=N; i++) li[i]=(sum+=readint());
    int64_t M=readint();
    int64_t *tboys =new int64_t[M],
            *tgirls=new int64_t[M];
    int boys_head =0, boys_tail =0,
        girls_head=0, girls_tail=0;
    
    for(int i=0; i<M; i++){
        if(readint()==1) tboys[boys_tail++]=readint();
        else tgirls[girls_tail++]=readint();
    }
    // sort?
    std::sort(tboys, tboys+boys_tail);
    std::sort(tgirls, tgirls+girls_tail);
    // ball begins!
    int64_t boys_sum=0, girls_sum=0;
    for(int i=0; i<N-1; i++){
        int64_t t=li[i];
        while(boys_head<boys_tail && tboys[boys_head]<=t &&
              girls_head<girls_tail && tgirls[girls_head]<=t){
            boys_sum+=t-tboys[boys_head++];
            girls_sum+=t-tgirls[girls_head++];
        }
        if(boys_head==boys_tail || girls_head==girls_tail) break;
    }
    int64_t t=li[N-1], tt=li[N];
    while(boys_head<boys_tail) boys_sum+=t-tboys[boys_head++];
    while(girls_head<girls_tail) girls_sum+=t-tgirls[girls_head++];
    printf("%.2lf %.2lf", double(boys_sum)/boys_tail, double(girls_sum)/girls_tail);
    delete []li;
    delete []tboys; delete[]tgirls;
}