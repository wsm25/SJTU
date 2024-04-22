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
inline void putint(int x) {
    if(x<0) x=-x;
    char buf[12];
    int i=11;
    while(x!=0){
        buf[i--]=x%10;
        x=x/10;
    }
    while((++i)<12) putchar('0'+buf[i]);
}

int main(){
    int len=readint();
    int *heap=new int[len]-1;
    for(int i=1; i<=len; i++) heap[i]=readint();
    // build heap
    for(int i=len/2+1; i>0; i--){
        // down i
        for(int j=i; j*2<=len;){
            int child=j*2;
            if(child+1<=len && heap[child]>heap[child+1]) 
                child++; // select less
            if (heap[j]<=heap[child]) break; // down finished 
            // swap
            int t=heap[child];
            heap[child]=heap[j];
            heap[j]=t;
            // next loop
            j=child;
        }
    }
    int base=readint();
    // find min from base
    int min_from_base=1919810;
    int min_index=0;
    for(int i=1; i<=len; i++){
        if(heap[i]>=base && heap[i]<min_from_base){
            min_from_base=heap[i];
            min_index=i;
        }
    }
    if (min_index==0){
        puts("not exist");
        for(int i=1; i<=len; i++){
            putint(heap[i]);
            putchar(' ');
        }
    } else {
        for(int i=min_index; i<=len; i++){
            putint(heap[i]);
            putchar(' ');
        }
    }
    
    delete [](heap+1);
    return 0;
}