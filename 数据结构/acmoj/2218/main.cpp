#include <cstdio>
#include <vector>
#include <algorithm>

bool readint(int& x) {
    int sign=1;
    x=0;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch==EOF) return false;
        if(ch=='-') sign=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    x*=sign;
    return true;
}

int main(){
    int x;
    std::vector<int> arr;
    while(readint(x))
        if(x!=-1) arr.push_back(x);
    std::sort(arr.begin(), arr.end());
    int end=arr.size()-1, mindif=2000000;
    for(int i=0; i<end; i++){
        int diff=arr[i+1]-arr[i];
        if(diff<mindif) mindif=diff;
    }
    printf("%d", mindif);
}