// faster if hash table is used
#include <cstdio>

inline unsigned readuint() {
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return x;
}
// example: 5 1 5 7 9 10 3 5 8 9
// example output: 1 -1 3
int main(){
    int n=readuint();
    int *arr=new int[n];
    for(int i=0; i<n; i++) arr[i]=readuint();
    int m=readuint();
    for(int i=0; i<m; i++){ // search x
        int x=readuint();
        int from=0, to=n-1;
        int mid;
        while(from<=to){
            mid=(from+to)/2;
            if(arr[mid]==x) break;
            else if(x<arr[mid]) to=mid-1;
            else from=mid+1;
        }
        if(from>to) puts("-1");
        else printf("%d\n", mid);
    }
}