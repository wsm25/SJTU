#include <stdio.h>
#include <unordered_set>

int r() {
    int x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return x;
}

int main() {
    int n = r(), k = r();
    std::unordered_set<int> s;
    s.insert(0);
    int last = r()%k; // inline queue
    int sum = last;
    for(int i=0; i<n-1; i++) {
        sum = (sum+r())%k;
        if(s.find(sum)!=s.end()) {
                putchar('y');
                goto end;
        }
        s.insert(last);
        last = sum;
    }
    putchar('n');
    end:
    return 0;
}