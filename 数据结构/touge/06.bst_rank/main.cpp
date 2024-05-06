#include <cstdio>
#include <vector>
#define W_NULL 114514

bool lineend=false;
inline int readint() {
    int x=0, sign=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='n'){
            getchar(); getchar(); getchar(); getchar();
            return W_NULL;
        }
        if(ch=='-') sign=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    if(ch=='\n') lineend=true;
    return sign*x;
}
struct Node{
    Node *left, *right;
    int value, size;
    Node(int v):value(v), left(nullptr), right(nullptr){}
};
struct BSInfo{
    bool valid;
    int min, max;
    int size;
    BSInfo():valid(false){}
    BSInfo(int min, int max, int size):
        valid(true), min(min), max(max), size(size){}
};
void connect(const std::vector<Node*> heap, int index){
    if(index>=heap.size() || heap[index]==nullptr) return;
    int next=index*2+1;
    if(next<heap.size()) {
        heap[index]->left=heap[next];
        connect(heap, next);
        if((++next)<heap.size()){
            heap[index]->right=heap[next];
            connect(heap, next);
        }
    }
}
// node!=nullptr
BSInfo check(Node& n){
    if(n.left){
        BSInfo li=check(*n.left);
        if((!li.valid) || li.max>n.value) return BSInfo(); // invalid
        if(n.right){
            BSInfo lr=check(*n.right);
            if((!lr.valid) || lr.min<n.value) return BSInfo(); // invalid
            n.size=li.size+lr.size+1;
            return BSInfo(li.min, lr.max, n.size);
        } else {
            n.size=li.size+1;
            return BSInfo(li.min, n.value, n.size);
        }
    } else {
        if(n.right){
            BSInfo lr=check(*n.right);
            if((!lr.valid) ||lr.min<n.value) return BSInfo(); // invalid
            n.size=lr.size+1;
            return BSInfo(n.value, lr.max, n.size);
        } else {
            n.size=1;
            return BSInfo(n.value, n.value, n.size);
        }
    }
}
int rank(Node& n, int r){
    if(n.left){
        if(n.left->size>=r) 
            return rank(*(n.left), r);
        r-=n.left->size;
    }
    if(r==1) return n.value;
    // safety: size is guarenteed
    return rank(*(n.right), r-1);
}

int main(){
    std::vector<Node*> heap;
    while(!lineend){
        int input=readint();
        if(input==W_NULL) heap.push_back(nullptr);
        else heap.push_back(new Node(input));
    }
    connect(heap, 0);
    Node* root=heap[0];
    if(!root){
        printf("not BST");
        return -1;
    }
    BSInfo info=check(*root);
    if(!info.valid){
        printf("not BST");
        return -1;
    }
    int k=readint();
    if(root->size<k){
        printf("error");
        return -1;
    }
    printf("%d", rank(*root, k));
    return 0;
}
