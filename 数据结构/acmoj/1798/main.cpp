#include <stdio.h>
#include <stdint.h>

#undef DEBUG_QUEUE

const int twopow(int x){ // returns 2<<([lb(x)]+1)
    return 1<<(32 - __builtin_clzll((x)));
}

class IntReader{
    char buf[65536]; // 4k buffer
    char *p, *tail; // pointer
    inline void read(){
        size_t n =fread(buf, 1, 65536, stdin);
        if(n<65536) buf[n]=EOF;
        p=buf;
    }
public:
    IntReader():p(buf+65536),tail(buf+65536){}
    int get(){
        int x = 0, sign = 1;
        if (p>=tail) read();
        while (p<tail && (*p < '0' || *p > '9'))
            if (*(p++) == '-') sign = 0;
        if (p>=tail){
            read();
            while (*p < '0' || *p > '9')
                if (*(p++) == '-') sign = 0;
        }
        
        while (p<tail && *p >= '0' && *p <= '9'){
            x = x * 10 + *(p++) - '0';
        }
        if (p>=tail){
            read();
            while (*p >= '0' && *p <= '9')
                x = x * 10 + *(p++) - '0';
        }
        return sign?x:-x;
    }
};

#ifdef DEBUG_QUEUE
void printqueue(int* p, unsigned head, unsigned tail, int m){
    while(head<tail){
        printf("%d|%d ",p[(head)%m], p[(head+1)%m]);
        head+=2;
    }
}
#endif

int main(){
    IntReader reader;
    int n=reader.get(), m=reader.get();
    int len=twopow(m+1)*2;
    // maxqueue may empty, while minqueue never empties
    int *minqueue=new int[len]; // structure: [[index, sum],...]
    int mask=len-1;
    unsigned minhead=0, mintail=0;
    int maxsum=INT32_MIN, sum=0, maxitem=INT32_MIN;
    // left border
    minqueue[mintail++]=-1;
    minqueue[mintail++]=0;
    for(int i=0;i<n;i++){
        int input = reader.get();
        sum+= input;
        if (input>maxitem) maxitem=input; // patch for no positive item
        // pop front invalid items
        if (minqueue[minhead&mask]<i-m) minhead+=2;
        // pop back unordered items
        while(mintail>minhead && minqueue[(mintail-1)&mask]>=sum) mintail-=2;
        // push back for i-th number
        minqueue[(mintail++)&mask]=i;
        minqueue[(mintail++)&mask]=sum;
        // maxsum
        int s=sum-minqueue[(minhead+1)&mask];
        if (s>maxsum) maxsum=s;
#ifdef DEBUG_QUEUE
        printf("%d:\t", sum);
        printf("minqueue: ");
        printqueue(minqueue,minhead,mintail,len);
        putchar('\n');
#endif
    }
    printf("%d", maxsum>maxitem?maxsum:maxitem);
    delete []minqueue;
}