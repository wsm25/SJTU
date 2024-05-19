//! Basic Idea: Classic Quick Sort ranking. Instead of sort both sides of pivot,
//! we only jump into the side with goal rank.
//!
//! Complexity analysis:
//! For best condition, the first pivot is just the median, O(n) complexity.  
//! In an amortized sense, the complexity satisfies T(n)<n+T(3/4 n).
//! According to Master theorem, T(n)<4n=O(n)  
//! For worst condition, every pivot we choose is the greatest or least one,
//! T(n)=n+n-1+...+n/2=O(n^2)
#include <cstdio>
#include <cstdint>

typedef int32_t len_t;

inline int readint() {
    int x=0, sign=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-') sign=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') x=x*10+ch-'0', ch=getchar();
    return sign*x;
}

uint32_t seed=114514;
inline uint16_t qrand(){
    return ((seed = (214013*seed+2531011))>>16);
}

// rank start from 0
template<typename T>
T qrank(T* arr, len_t len, len_t rnk){
    if(len==1) return arr[0];
    T& ppivot=arr[qrand()%len];
    T pivot=ppivot;
    ppivot=arr[0];
    len_t left=0, right=len-1;
    while(left<right) {
        // now arr[left] is free
        while(left<right && arr[right]>=pivot) right--;
        arr[left]=arr[right];
        // now arr[right] is free
        while(left<right && arr[left]<=pivot) left++;
        arr[right]=arr[left];
    }
    arr[left]=pivot;
    // with TRO
    if(rnk==left) return pivot;
    if(rnk< left) return qrank(arr, left, rnk);
    else          return qrank(arr+left+1, len-left-1, rnk-left-1);
}

int main(){
    int arr[50002]; // 200k
    int size=readint();
    for(int i=0; i<size; i++) arr[i]=readint();
    if(size&1) {
        printf("%d", qrank(arr, size, size/2));
    } else {
        int med=qrank(arr, size, size/2) +
                qrank(arr, size, size/2-1);
        if(med&1) {
            printf("%d.5", med/2);
        } else printf("%d", med/2);
    }
}