#include <cstdio>
#include <cstdint>
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

class Sequence{
    struct Node{int left,right,value;};
    Node* heap; // structure: [(left, right,value)]
    int remain;
    void _write_sequence(int from, int to, int index){
        // assume to-from>=-1
        if(from>=to){ // empty or leaf
            heap[index]={0,0,from};
            return;
        }
        int mid=(from+to+1)/2;
        heap[index]={(mid-from), (to-mid), mid};
        _write_sequence(from, mid-1, index*2);
        _write_sequence(mid+1, to, index*2+1);
        return;
    }
    int _pop_rank(int rank, int remain, int index){
        Node &node=heap[index];
        if (node.left>=rank) { // left
            node.left-=1;
            return _pop_rank(rank, node.left+1, index*2);
        } else if (remain==node.left+node.right){ // right with no current
            node.right-=1;
            return _pop_rank(rank-node.left, node.right+1, index*2+1);
        } else if (rank>=node.left+2){ // right
            node.right-=1;
            return _pop_rank(rank-node.left-1, node.right+1, index*2+1);
        } else { // current
            return node.value;
        }
    }
public:
    Sequence(int n):remain(n){
        heap=new Node[(n+1)*2];
        _write_sequence(1, n, 1);
    }
    ~Sequence(){
        delete []heap;
    }
    int pop_rank(int rank){
        remain-=1;
        return _pop_rank(rank, remain+1, 1);
    }
};

// testcase: 10 0 1 2 0 2 1 1 5 8 0 
int main(){
    int n=readuint();
    unsigned *B=new unsigned[n];
    unsigned remain=n;
    for(int i=0;i<n;i++) B[i]=readuint();
    // sequence
    Sequence set(n);
    for(int i=n-1;i>=0;i--){
        B[i]=set.pop_rank(B[i]+1);
    }
    for(int i=0; i<n; i++) {putuint(B[i]); putchar(' ');}
    return 0;
}