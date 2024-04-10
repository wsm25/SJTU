#include <cstdio>
#include <cstring>

inline const int max(const int x, const int y){
    return x>y?x:y;
}
inline int readint() {
    int x = 0, sign = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') sign = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
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
    putchar('\n');
}

class SegTree{ // max segment tree
    int* heap;
    int n;
    void _init_max(const int* starts, int from, int to, int index){
        if(from==to){
            heap[index]=from-starts[from]+1;
            // printf("%d: %d @heap[%d]\n", from, heap[index], index);
            return;
        }
        // from<to
        int mid=(from+to)/2;
        _init_max(starts, from, mid, index*2);
        _init_max(starts, mid+1, to, index*2+1);
        heap[index]=max(heap[index*2], heap[index*2+1]);
        return;
    }
    int _max_range(int from, int to, int rfrom, int rto, int index){
        // printf("_max_range(%d, %d) in (%d, %d)\n", from, to, rfrom, rto);
        if(from==rfrom && to==rto) return heap[index];  // match
        int mid=(rfrom+rto)/2;
        if(to<=mid) return _max_range(from, to, rfrom, mid, index*2); // all left
        if(from>mid) return _max_range(from, to, mid+1, rto, index*2+1); // all right
        return max(
            _max_range(from, mid, rfrom, mid, index*2), // left
            _max_range(mid+1, to, mid+1, rto, index*2+1) // right
        );
    }
public:
    SegTree(int n, const int* starts):n(n){
        heap=new int[n*4];
        _init_max(starts, 0, n-1, 1);
    }
    ~SegTree(){
        delete []heap;
    }
    int max_range(int from, int to){
        // printf("call max_range(%d, %d)\n", from, to);
        return _max_range(from, to, 0, n-1, 1);
    }
};

// return i s.t. starts[i-1]<goal while starts[i]>=goal
inline int spliting(int goal, int* starts, int from, int to){ // [from, to]
    if(starts[from]>=goal) return from;
    if(starts[to]<goal) return to+1;
    // i must exist
    for(;;){
        // printf("this loop: [%d, %d]\n", from, to);
        int mid=(from+to+1)/2;
        if(starts[mid-1]>=goal) to=mid-1;
        else if(starts[mid]<goal) from=mid;
        else return mid;
    }
}

int _main(){
    int starts[]={1,1,2,3,5,5,5,6,8};
    printf("%d\n", spliting(1,starts,0,4));
    printf("%d\n", spliting(2,starts,0,4));
    printf("%d\n", spliting(5,starts,0,4));
    return 0;
}

#define RANGE 1000000

// testcase: 9 2 2 5 4 1 2 3 6 2 4 0 8 2 6
// output: 6\n5
int main(){
    int n=readint(), m=readint();
    int *starts=new int[n+1];
    *starts=0;
    starts+=1;
    int *former=new int[RANGE*2+1]; // 8M mem
    memset(former, -1, (RANGE*2+1)*sizeof(int)); // 1ms runtime
    for(int i=0; i<n; i++){
        int x=readint()+RANGE;
        starts[i]=max(starts[i-1], former[x]+1);
        former[x]=i;
    }
    delete []former;
    SegTree t(n, starts);
    for(int i=0; i<m; i++){ // lookup
        int from=readint(), to=readint();
        int split=spliting(from, starts, from, to);
        // all out of range
        if(split==to+1) putint(split-from); 
        // all in range
        else if(split==from) putint(t.max_range(split, to)); 
        // can be splited
        else putint(max(t.max_range(split, to), split-from));
    }
    delete [](starts-1);
    return 0;
}