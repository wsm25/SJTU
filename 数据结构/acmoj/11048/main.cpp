#include <cstdio>
#include <cstdint>
#define MAXCAP 1024
#undef DEBUG

struct Node{short parent,left, right, _;};
Node tape[MAXCAP]={0}; // 8k

inline unsigned readuint() {
    unsigned x = 0;
    char ch = getchar();
    while (ch<'0' || ch>'9')
        ch = getchar();
    while (ch>='0' && ch<='9'){
        x = x*10+ch-'0';
        ch = getchar();
    } 
    return x;
}

void readtape(){
    short i     = readuint(),
        left  = readuint(),
        right = readuint();
    tape[i].left=left;
    tape[i].right=right;
    tape[left].parent=
    tape[right].parent=
        i;
}

int main(){
    int n=readuint(); // n inputs makes 2n+1 nodes
    for(int i=0; i<(n>>1); i++){
        readtape();
    }
    // find root
    short root=1;
    while(tape[root].parent!=0) root=tape[root].parent;
#ifdef DEBUG
    for(int i=1; i<=n; i++)
        printf("%d: %d, %d, %d\n", i, tape[i].parent, tape[i].left, tape[i].right);
#endif
    // level tranverse
    short queue[MAXCAP]; // 2k 
    short *plast=queue, *pcurrent=queue+1;
    printf("%d", root);
    *plast=root;
    while(plast<pcurrent){
        short *end=pcurrent;
        while(plast<end){
            Node node=tape[*(plast++)];
            if (node.left){
                printf("\n%d\n%d", node.left, node.right);
                *(pcurrent++)=node.left;
                *(pcurrent++)=node.right;
            }
        }
    }
}
