/// 思路：这不哈夫曼树最小带权路径和吗
#include <cstdio>
inline bool readint_s(int* dst){
    int x=0, sign=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch==EOF) return false;
        if(ch=='-') sign=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    *dst=sign*x;
    return true;
}

// min root heap
class Heap{
    int *heap;
    int heaplen;
    #define SWAP(x,y) do{auto t=y; y=x; x=t;}while(0)
    void up(int i){
        if(i<=1) return;
        if(heap[i]>=heap[i/2]) return;
        SWAP(heap[i], heap[i/2]);
        return up(i/2);
    }
    void down(int i){
        int child=i*2;
        if(child>heaplen) return;
        if(child+1<=heaplen && heap[child]>heap[child+1]) child++;
        if(heap[i]<=heap[child]) return;
        SWAP(heap[i], heap[child]);
        return down(child);
    }
    #undef SWAP
public:
    Heap(int *heap, int len): heap(heap), heaplen(len){
        for(int i=len/2; i>=1; i--) down(i);
    }
    // unsafe: do not automatically allocate memory
    void push(int i){
        heap[++heaplen]=i;
        up(heaplen);
    }
    // unsafe: do not check length
    int pop(){
        int ret=heap[1];
        heap[1]=heap[heaplen--];
        down(1);
        return ret;
    }
    int len(){
        return heaplen;
    }
};

int main(){
    int len; readint_s(&len);
    int *buf=new int[len]-1;
    for(int i=1; i<=len; i++){
        if (readint_s(buf+i)==false) { // less
            puts("error");
            delete [](buf+1);
            return -1;
        }
    }
    int x;
    if (readint_s(&x)==true) { // more
        puts("error");
        delete [](buf+1);
        return -1;
    }
    Heap heap(buf, len);
    // build huffman tree
    int wpl=0;
    while(heap.len()>=2){
        int m=heap.pop()+heap.pop();
        wpl+=m;
        heap.push(m);
    }
    printf("%d", wpl);
    delete [](buf+1);
}