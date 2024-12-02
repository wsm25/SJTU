#include <cstdio>
#undef DEBUG
int val[36];
int maxpeerval[36];
struct Cost{
    int len;
    int status;
};

Cost min[36];
#define INF 0x1919810

template <typename F>
inline void for_each_peer(int _j, F&& func){
    int peers[4]={_j-6, _j-1, _j+1, _j+6}; 
    for(int k=0; k<4; k++){ 
        int n=peers[k]; 
        if(n<0 || n>=36 || 
            (_j%6==0 && n==_j-1) || 
            (_j%6==5 && n==_j+1) 
            ) continue; 
        func(n);
    }
}

void gen_peerval(){
    for(int j=0; j<36; j++){
        maxpeerval[j]=0;
        for_each_peer(j, [j](int n){
            if(val[n]>maxpeerval[j])
                maxpeerval[j]=val[n];
        });
    }
}

void gen_min(int i, int len, int status){
    for_each_peer(i, [len, status](int n){
        int cost=status*val[n];
        int newlen=len+cost;
        int newstatus=(cost%4)+1;
        // strip branch
        if(newlen>min[n].len+maxpeerval[n]*status) return;
        if(newlen<min[n].len || (newlen==min[n].len&&newstatus<min[n].status))
            min[n]={newlen, newstatus};
        gen_min(n, newlen, newstatus);
    });
}


int main(){
    int n;
    void(scanf("%d", &n));
    while(n--){
        for(int i=0; i<36; i++)
            (void)(scanf("%d", &val[i]));
        int a,b,c,d;
        (void)(scanf("%d %d %d %d", &a, &b, &c, &d));
        for(int i=0; i<36; i++) min[i].len=INF;
        gen_peerval();
        min[a*6+b]={0, 1};
        gen_min(a*6+b, 0, 1);
        printf("%d\n", min[c*6+d].len);
        #ifdef DEBUG
        for(int i=0; i<6; i++){
            for(int j=0; j<6; j++){
                int n=i*6+j;
                printf("%d(%d) ", min[n].len, min[n].status);
            }
            putchar('\n');
        }
        #endif
    }
}