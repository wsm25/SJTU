#include <cstdio>
#include <algorithm>
inline unsigned readuint() {
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x;
}

struct HufNode{
private:
    size_t _wpl(size_t depth){
        if(left) // non null child
            return left->_wpl(depth+1)+right->_wpl(depth+1);
        else return depth*weight;
    }
public:
    unsigned weight;
    HufNode *left, *right;
    bool operator<(const HufNode& rhs){return weight<rhs.weight;}
    size_t wpl(){
        return _wpl(0);
    }
};

// small root heap
template <typename T>
class Heap{
    T** buf; // must be heap mem
    size_t n;
    void up(size_t i){
        while(i>1 && *buf[i]<*buf[i/2]){
            std::swap(buf[i/2], buf[i]);
            i/=2;
        }
    }
    void down(size_t i){
        while(i<=(n/2)){
            size_t in=i*2+1<=n ? // prevent overflow
                (*buf[i*2]<*buf[i*2+1] ? i*2 : i*2+1) : // match smaller
                i*2;
            if(*buf[in]<*buf[i]){
                std::swap(buf[i], buf[in]);
                i=in;
            } else break;
        }
        // print();
    }
public:
    // buf must be heap allocated mem, will automatically dealloc
    Heap(T** buf, size_t n):buf(buf-1), n(n){
        for(size_t i=n; i>=1; i--) down(i);
    }
    T* pop(){
        T* ret=buf[1];
        buf[1]=buf[n--];
        down(1);
        return ret;
    }
    void push(T* x){
        buf[++n]=x;
        up(n);
    }
    size_t len(){return n;}
};

// get only prealloc pool
template<typename T>
class Pool{
    size_t n;
    T* buf;
public:
    Pool(size_t cap):n(cap-1){buf=new T[cap];}
    ~Pool(){delete []buf;}
    T* from(const T&& src){T* obj=buf+(n--); *obj=src; return obj;}
};

// sample: 3 1 2 3
// sample: 7 213 23 234 1 2 89 899
int main(){
    unsigned n=readuint();
    HufNode **data=new HufNode*[n];
    Pool<HufNode> hufpool(2*n);
    for(unsigned i=0; i<n; i++){
        data[i]=hufpool.from({readuint(), nullptr, nullptr});
    }
    Heap hufheap(data, n);
    while(hufheap.len()>1){
        HufNode *n1=hufheap.pop(), *n2=hufheap.pop();
        hufheap.push(hufpool.from({n1->weight+n2->weight, n1, n2}));
    }
    printf("%lu", hufheap.pop()->wpl());
    
}