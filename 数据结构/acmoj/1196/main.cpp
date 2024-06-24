#include <cstdio>
#include <vector>

using std::vector;

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

static size_t k;

struct Node{
    // path
    struct Path{
        int* max_k; // k longest edges
        int max_k_len=0;
        int len;
        Path(){
            max_k=new int[k];
        }
        Path& operator+=(int x){

        }
        inline int min_max() const{
            return max_k[max_k_len-1];
        }
        int operator+(int x){
            if(max_k_len<k) return 0;
            else{
                return len+(
                    min_max() < x ?
                    min_max() : x
                );
            }
        }
        bool operator<(Path& rhs){
            return max_k_len<rhs.max_k_len || 
                   max_k_len==rhs.max_k_len && 
                   min_max()<rhs.min_max();
            
        }
        ~Path(){delete []max_k;}
    };
    
};