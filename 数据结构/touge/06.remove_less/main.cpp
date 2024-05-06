// For design ideas, see the comments inside the function `remove_less`.
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
    int value;
    Node(int v):value(v), left(nullptr), right(nullptr){}
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
// safety: heap.size()>tree
// returns max index
int flush(std::vector<Node*>& heap, int index, Node* node){
    if(!node) return 0;
    heap[index]=node;
    int maxindex=index;
    
    {int t=flush(heap, index*2+1, node->left);
    if(t>maxindex) maxindex=t;}
    {int t=flush(heap, index*2+2, node->right);
    if(t>maxindex) maxindex=t;}
    return maxindex;
}
// returns if any removed
bool remove_less(Node* &node, int k){
    if(!node) return false;
    bool suc=remove_less(node->left, k);
    if(node->value>=k) return suc;
    printf("%d ", node->value);
    // value<k, meaning left and node are all deleted.
    // replace node with its right child
    node=node->right;
    remove_less(node, k);
    return true;
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
    // k 
    if(!remove_less(root, readint())) printf("none");
    putchar('\n');
    if(!root){
        putchar('\n');
        return 0;
    }
    for(int i=0; i<heap.size(); i++) heap[i]=nullptr;
    int maxindex=flush(heap, 0, root);
    for(int i=0; i<=maxindex; i++){
        if(heap[i]) printf("%d ", heap[i]->value);
        else printf("null ");
    }
    return 0;
}