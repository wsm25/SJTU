#include <cstdio>
#define MAX 100000

inline int read() { // 0 for number, 1 for null, -1 for error
    char ch = getchar();
    if (ch==EOF) {return -1;}
    if (ch=='n'){ // null
        do ch=getchar(); while (ch!=EOF && ch!=' ');
        return 1;
    }
    if (ch>='0' && ch<='9'){ // number
        do ch=getchar(); while (ch!=EOF && ch!=' ');
        return 0;
    }
    return -1;
}

int main(){
    bool tree[MAX]; // true for leaf and false for non-leaf or null
    unsigned len=0;
    for(int k=read(); k!=-1; k=read()){
        if (k==1){ // null
            tree[++len]=false;
        } else{ // non-null
            tree[++len]=true;
            tree[len/2]=false;
        }
    }
    int count=0;
    for(int i=1; i<=len; i++){
        count+=tree[i];
    }
    printf("%d", count);
    return 0;
}