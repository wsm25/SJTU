#include <cstdio>
#define MAX 100000

inline int read() { // 1 for non-empty, 0 for empty(including eof)
    signed char ret;
    char ch = getchar();
    if (ch==EOF) return 0;
    if (ch=='@'){ // null
        ret=0;
    } else ret=1;
    do ch=getchar(); while (ch!=EOF && ch!=' ');
    return ret;
}

int isfull(){ // -1 for empty, 0 for non-full and 1 for full
    char node=read();
    if(node==0) return -1;
    char left=isfull(), right=isfull();
    if(left==-1 && right==-1 || left==1 && right==1) return 1;
    else return 0;
}

int main(){
    if (isfull()==1) printf("true");
    else printf("false");
    return 0;
}