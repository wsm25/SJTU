#include <cstdio>
#include <cstdint>
#include <algorithm>

class Heap{
    uint16_t* heap;
    int size;
    // max root
    void up(int i){
        if(i<=1) return;
        int next=i/2;
        if(heap[next]<heap[i]){
            std::swap(heap[i], heap[next]);
            return up(next);
        }
    }
    void down(int i){
        int next=i*2;
        if(next>size) return;
        if(next+1<=size && heap[next]<heap[next+1])
            next=next+1;
        if(heap[i]<heap[next]){
            std::swap(heap[i], heap[next]);
            return down(next);
        }
    }
public:
    Heap(int cap):size(0){heap=new uint16_t[cap+1];}
    ~Heap(){delete []heap;}
    void push(uint16_t&& x){
        heap[++size]=x;
        up(size);
    }
    uint16_t pop(){
        uint16_t ret=heap[1];
        std::swap(heap[1], heap[size--]);
        down(1);
        return ret;
    }
    int len(){return size;}
};

inline uint16_t readuint() {
    uint16_t x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return x;
}

int main(){
    int n=readuint();
    Heap heap(n);
    for(int i=0; i<n; i++)
        heap.push(readuint());

    while(heap.len()>1){
        uint16_t x=heap.pop(), y=heap.pop();
        if(x>y) heap.push(x-y);
        else if(x<y) heap.push(y-x);
    }
    printf("%u", heap.len()==1 ? heap.pop() : 0);
}