#include <cstdio>

inline bool read_1() { // no need to calculate number
    bool sign = true;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') sign = false;
        ch = getchar();
    }
    if(!sign && ch=='1') {
        ch=getchar();
        if (ch < '0' || ch > '9') return true;
    }
    while (ch >= '0' && ch <= '9') ch = getchar();
    return false;
}

int maxdepth(int depth){ // stack size: 12
    if (read_1()){
        return depth;
    }
    int left = maxdepth(depth+1); // left
    int right = maxdepth(depth+1); // right
    return left>right?left:right;
}

int main(){
    printf("%d", maxdepth(0));
}