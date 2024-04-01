#include <cstdio>
#define MAX 100000

inline signed char read() { // 0 for 0, 1 for 1, 2 for null, -1 for error
    signed char ret;
    char ch = getchar();
    if (ch==EOF) return -1;
    if (ch=='n'){ // null
        ret=2;
    } else if (ch=='0'){ // number
        ret=0;
    } else if (ch=='1'){ // number
        ret=1;
    } else ret=-1;
    do ch=getchar(); while (ch!=EOF && ch!=' ');
    return ret;
}

class Tree{
    char* raw;
    int len;
    bool _strip0(int i){ // true if stripped
        if (i>len || raw[i]==2) return true;
        if(raw[i]==0){
            bool left=_strip0((i<<1)+1), right=_strip0(i<<1);
            if(left&&right){
                raw[i]=2; // strip
                return true;
            }
        } else {
            _strip0(i<<1);
            _strip0((i<<1)+1);
        }
        return false;
    }
    void _strip_null(){
        while(raw[len]==2) len--;
    }
public:
    Tree(char* src, int len): raw(src), len(len){}
    void strip0(){
        _strip0(1);
        _strip_null();
    }
    void print(){
        for(int i=1; i<=len; i++){
            char node=raw[i];
            if (node==0) printf("0 ");
            else if(node==1) printf("1 ");
            else printf("null ");
        }
    }
};

int main(){
    char tree[MAX];
    int len=0;
    for(signed char k=read(); k!=-1; k=read()){
        tree[++len]=k;
    }
    Tree t(tree, len);
    t.strip0();
    t.print();
    return 0;
}