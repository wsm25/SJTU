#include <cstdio>

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

class ListTree{
    int* tree;
    size_t cap;
    void(*op)(int&);
    void _midtranverse(int index){ // stack size: 4
        if(index>cap || tree[index]==-1) return;
        _midtranverse(index<<1);
        op(tree[index]);
        _midtranverse((index<<1)+1);
    }
public:
    ListTree(size_t depth){
        cap=1<<depth;
        tree=new int[cap];
        op=nullptr;
    }
    void read(){
        for(int i=1; i<cap;i++)
            tree[i]=readint();
    }
    void midtranverse(void(*operation)(int&)){
        if (!operation) return;
        op=operation;
        _midtranverse(1);
        op=nullptr;
    }
};

int main(){
    int n = readint();
    ListTree tree(n);
    tree.read();
    // mid trace
    tree.midtranverse([](int& x){printf("%d ",x);});
    return 0;
}

