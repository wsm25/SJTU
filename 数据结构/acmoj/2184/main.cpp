#include <cstdio>
#include <cstring>
inline unsigned readuint() {
    int x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') ch = getchar();
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return x;
}

inline void putuint(unsigned x) {
    char buf[12];
    int i=11;
    while(x!=0){
        buf[i--]=x%10;
        x=x/10;
    }
    while((++i)<12) putchar('0'+buf[i]);
}

class SegTree{
    struct Node{unsigned value, lazy;}; // lazy: lazy<value
    Node* heap;
    int n; // size
    unsigned _get(int i, int from, int to, int index){
        // printf("call _get on heap[%d] in (%d, %d)\n", index, from, to);
        // lazy
        Node &node=heap[index];
        if(node.value>node.lazy){
            heap[index*2].lazy=
                heap[index*2+1].lazy=
                node.value=
                node.lazy;
        }
        if(from==to) return node.value; // current
        int mid=(from+to)/2;
        if (i<=mid) return _get(i, from, mid, index*2); // left
        else return _get(i, mid+1, to, index*2+1); // right
    }
    void _setrange(unsigned value, int from, int to, int rfrom, int rto, int index){
        // printf("call _setrange on heap[%d]: (%d, %d) in (%d, %d)\n", index, from, to, rfrom, rto);
        if (from==rfrom && to==rto){ // current
            heap[index].lazy=value;
            return;
        }
        int rmid=(rfrom+rto)/2;
        if(to<=rmid) return _setrange(value, from, to, rfrom, rmid, index*2); // all left
        else if(from>rmid) return _setrange(value, from, to, rmid+1, rto, index*2+1); // all right
        _setrange(value, from, rmid, rfrom, rmid, index*2); // left
        _setrange(value, rmid+1, to, rmid+1, rto, index*2+1); // right
    }
public:
    SegTree(int n):n(n){
        heap=new Node[4*n];
        memset(heap, -1, 4*n*sizeof(Node)); // set to uint::MAX
    }
    ~SegTree(){
        delete []heap;
    }
    unsigned get(int index){
        // printf("call get %d\n", index);
        return _get(index, 1, n, 1);
    }
    void setrange(unsigned value, int from, int to){
        // printf("call setrange %d on (%d, %d)\n", value, from, to);
        if(from<=to)
        _setrange(value, from>=1?from:1, to<=n?to:n, 1, n, 1);
    }
};

int _main(){
    const int N=480230;
    SegTree t(N);
    for(int i=1; i<=N; i++) t.get(i);
    return 0;
}

// sample: 5 2 11 12 13 14 15 12 1 3 13 2 4
// output: 11 12 12 13 15
int main(){
    int n=readuint(), m=readuint();
    unsigned *height=new unsigned(n);
    SegTree bombs(n);
    
    for(int i=0; i<n; i++){
        height[i]=readuint();
    }
    for(int i=0; i<m; i++){
        int x=readuint(), from=readuint(), to=readuint();
        if(from>to) continue;
        bombs.setrange(x, from, to);
    }
    for(int i=0; i<n; i++){
        // can be optimized for sequent read
        unsigned b=bombs.get(i+1), h=height[i];
        putuint(h<b?h:b);
        putchar(' ');
    }
    return 0;
}