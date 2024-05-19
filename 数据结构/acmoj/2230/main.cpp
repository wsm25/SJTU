#include <algorithm>
#include <cstdio>

inline unsigned readuint() {
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return x;
}

int main(){
    int n=readuint(), limit=readuint();
    int *people=new int[n];
    for(int i=0; i<n; i++) people[i]=readuint();
    std::sort(people, people+n);
    int first=0, last=n-1;
    int count=0;
    while(first<last){
        if(people[first]+people[last--]<=limit) first++;
        count++;
    }
    count+=(first==last);
    printf("%d", count);
    delete []people;
}