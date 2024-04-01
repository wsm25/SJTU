#include <stdio.h>
int main(){
    int x,y;
    scanf("%d %d", &x, &y);
    if (x>y) {int t=x; x=y; y=t;}
    y>>=__builtin_clz(x)-__builtin_clz(y);
    while(x!=y){ x>>=1; y>>=1;}
    printf("%d", x);
}