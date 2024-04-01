#include <cstdio>
#define MAX 100000
const char* BAD_INPUT="bad input";

inline char read() { // 0 for null, -1 for error, others char
    char ch = getchar();
    if (ch=='n'){

    }
    return ch;
}

int main(){
    char tree[MAX]; // 0 for null
    tree[0]='X';
    int len=0;
    // input tree
    char ch=getchar();
    while(ch!='\n'){
        if(ch==' ') ch=getchar();
        if(ch=='n'){
            ch=getchar();
            if(ch=='u'){
                tree[++len]=0; // null
                getchar(); getchar(); // ll
                ch=getchar();
            }
            else tree[++len]='n';
            continue;
        }
        tree[++len]=ch;
        if(tree[len>>1]==0){
            printf(BAD_INPUT);
            return 0;
        }
        ch=getchar();
    }
        
    int x,y;
    scanf("%d %d", &x, &y);
    if(x>len || y>len || tree[x]==0 || tree[y]==0){
        printf(BAD_INPUT);
        return 0;
    }
    if (x>y) {int t=x; x=y; y=t;}
    y>>=__builtin_clz(x)-__builtin_clz(y);
    while(x!=y){ x>>=1; y>>=1;}
    putchar(tree[x]);
    return 0;
}