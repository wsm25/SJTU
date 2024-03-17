#include <iostream>

int positive_mod(int n, int mo) {
    if (n >= 0) {
        return n%mo;
    } else {
        return n-(n/mo-1)*mo;
    }
}

class BanG{
    // status
    int index; // status
    int direction; // 0 for left and 1 for right
    // params
    int N; // total number, mutable
    int M; // M
    // id list
    int *l;
    void iter_index(){
        if (direction){
            index+=M-1;
        } else{
            index-=M;
        }
        index=positive_mod(index, (N-1)<<1);
        if (index>N-1) { // reverse
            index=((N-1)<<1)-index;
            direction^=1;
        } else if (index==0){
            direction=1;
        } else if (index==N-1){
            direction=0;
        }
    }
    int remove(int i){
        int ret = l[i];
        for(;i<N-1;i++) l[i]=l[i+1];
        N--;
        return ret;
    }
public:
    BanG(int M, int N): M(M), N(N), index(0), direction(1) {
        l=new int[N];
        for(int i=0;i<N;i++) l[i]=i+1; 
    }
    int next(){
        iter_index();
        std::cout<<"remove "<<index<<":"<<l[index]<<"\n";
        return remove(index);
    }
    int last(){
        if (direction){
            return l[index];
        } else {
            return l[index-1];
        }
    }
};

int main(){
    int M,N;
    std::cin>>N>>M;
    BanG dream(M,N);
    for(;N>1;N--) 
        dream.next();
    std::cout<<dream.last();
    return 0;
}