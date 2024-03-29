#include <cstdio>
#include <cstdint>

#undef DEBUG_QUEUE

const int twopow(int x){ // returns 2<<([lb(x)]+1)
    return 1<<(32 - __builtin_clzll((x)));
}

inline int readint() {
    int x = 0, sign = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') sign = 0;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return sign?x:-x;
}

#ifdef DEBUG_QUEUE
void printqueue(int* p, unsigned head, unsigned tail, int m){
    while(head<tail){
        printf("%d|%d ",p[(head)%m], p[(head+1)%m]);
        head+=2;
    }
}
#endif

int main(){
    int n=readint(), m=readint();
    int len=twopow(m+1)*2;
    // maxqueue may empty, while minqueue never empties
    int *maxqueue=new int[len], *minqueue=new int[len]; // structure: [[index, sum],...]
    int mask=len-1;
    unsigned maxhead=0, maxtail=0, minhead=0, mintail=0;
    int maxsum=INT32_MIN, sum=0, maxitem=INT32_MIN;
    // left border
    minqueue[mintail++]=-1;
    minqueue[mintail++]=0;
    for(int i=0;i<n;i++){
        int input = readint();
        sum+= input;
        if (input>maxitem) maxitem=input; // patch for no positive item
        // pop front invalid items
        if (minqueue[minhead&mask]<i-m) minhead+=2;
        while (maxtail>maxhead && maxqueue[maxhead&mask]<=minqueue[minhead&mask]) maxhead+=2;
        // pop back unordered items
        while(maxtail>maxhead && maxqueue[(maxtail-1)&mask]<=sum) maxtail-=2;
        while(mintail>minhead && minqueue[(mintail-1)&mask]>=sum) mintail-=2;
        // push back for ith number
        maxqueue[(maxtail++)&mask]=minqueue[(mintail++)&mask]=i;
        maxqueue[(maxtail++)&mask]=minqueue[(mintail++)&mask]=sum;
        // maxsum
        // as minqueue.head index may bump, once more pop front is necessary, with little cost
        while (maxtail>maxhead && maxqueue[maxhead&mask]<=minqueue[minhead&mask]) maxhead+=2;
        if (maxtail>maxhead){
            int s=maxqueue[(maxhead+1)&mask]-minqueue[(minhead+1)&mask];
            if (s>maxsum) maxsum=s;
        }
#ifdef DEBUG_QUEUE
        printf("%d:\t", sum);
        printf("minqueue: ");
        printqueue(minqueue,minhead,mintail,len);
        printf("\t maxqueue: ");
        printqueue(maxqueue,maxhead,maxtail,len);
        putchar('\n');
#endif
    }
    printf("%d", maxsum>maxitem?maxsum:maxitem);
    delete []maxqueue;
    delete []minqueue;
}