/// O(mn) brute-force solution, space optimized
#include <cstdio>
#include <cstdint>

template<class T>
class Ringbuf{ // reduce mem usage
    T *p;
    size_t cap;
public:
    Ringbuf(size_t cap):cap(cap){p=new T[cap];}
    ~Ringbuf(){delete p;}
    T& operator[](int64_t i){return p[i%cap];}
};

int readint() {
    int x = 0, sign = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') sign = 0;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return sign?x:-x;
}

int main(){
    int n=readint(), m=readint();
    int64_t sum=0, max=0;
    Ringbuf<int64_t> sum_list(m+1);
    sum_list[-1]=0;
    int i=0;
    while(i<m){
        int input=readint();
        sum+=input;
        sum_list[i++]=sum;
    }
    while(i<n){
        int input=readint();
        sum+=input;
        sum_list[i]=sum;
        if (input>0){
            for(int j=i-m;j<i;j++){
                int s=sum-sum_list[j];
                if(s>max) max=s;
            }
        }
        i++;
    }
    printf("%ld", max);
}