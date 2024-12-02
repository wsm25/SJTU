#include <cstdio>
#define DEBUG
int val[36];
struct Cost{
    int len=0x1919810;
    int status;
};

Cost min[36];
#define INF 0x1919810

bool bellman_ford(int x){
    for(int i=0; i<36; i++)
        min[i].len=INF;
    min[x]={0, 1};
    bool relaxed=false;
    for(int i=0; i<120; i++) { // 60 edges
        relaxed = false;
        for (int j=0; j < 36; j++) {
            if(min[j].len==INF) continue;
            int peers[4]={j-6, j-1, j+1, j+6};
            for(int k=0; k<4; k++){
                int n=peers[k];
                if(n<0 || n>=36 ||
                    (j%6==0 && n==j-1) ||
                    (j%6==5 && n==j+1)
                    ) continue;
                int cost=min[j].status*val[n];
                if(min[n].len>min[j].len+cost ||
                    ((min[n].len==min[j].len+cost && (cost%4)+1<min[n].status))){
                    min[n]={min[j].len+cost, (cost%4)+1};
                    relaxed=true;
                }
            }
        }
        if (!relaxed) break; // will never continue to relax
    }
    // 第 n 轮循环仍然可以松弛时说明 s 点可以抵达一个负环
    return relaxed;
}

int main(){
    int n;
    (void)scanf("%d", &n);
    while(n--){
        for(int i=0; i<36; i++)
            (void)scanf("%d", &val[i]);
        int a,b,c,d;
        (void)scanf("%d %d %d %d", &a, &b, &c, &d);
        bellman_ford(a*6+b);
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