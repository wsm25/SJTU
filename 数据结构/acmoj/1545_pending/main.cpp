#include <cstdio>
#include <cstdint>
#include <cstring>

inline int readint() {
    int x = 0, sign = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') sign = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') x = x * 10 + ch - '0', ch = getchar();
    return sign*x;
}

class Layer2D{
    int m,n; // [0,m], [0,n]
    int64_t* buf;
    int64_t dummy;
    bool _valid(int x, int y){
        if((x^y)&1) return false;
        int z=x+y;
        if(z<m || z>(m+(n<<1))) return false;
        z=y-x;
        if(z>m || z<-m) return false;
        return true;
    }
public:
    int64_t& get(int x, int y, bool& valid){
        if (!_valid(x,y)){
            valid=false;
            return dummy;
        }
        valid=true;
        // 0.5(x-y+m, x+y-m)
        return buf[((x+y-m)*m+(x+y-m))>>1];
    }
};
class SegmentTree{

};

int main(){

}