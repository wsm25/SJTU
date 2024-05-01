#include <iostream>
#include <cstdint>
#include <algorithm>
unsigned primes[100];
#define CAP_INIT UINT64_MAX

struct Dream{ // 16 byte
    uint64_t value;
    int from;
    inline bool operator>(const Dream& rhs){
        return value>rhs.value;}
    Dream operator*(int i){
        return Dream{value*primes[i], i};
    }
};

class BanG{Dream* heap;
    uint64_t size;
    // min root
    void up(uint64_t i){
        if(i<=1) return;
        uint64_t next=i/2;
        if(heap[next]>heap[i]){
            std::swap(heap[next], heap[i]);
            return up(next);
        }
    }
    void down(uint64_t i){
        uint64_t next=i*2;
        if(next>size) return;
        if(next+1<=size && heap[next]>heap[next+1]) next++;
        if(heap[i]>heap[next]){
            std::swap(heap[next], heap[i]);
            return down(next);
        }
    }
public:
    BanG(int cap):size(0){heap=new Dream[cap+2];} // in case cap==0
    ~BanG(){delete []heap;}

    const Dream& min(){
        return heap[1];
    }
    const Dream& max(){
        uint64_t maxi=1, i=size/2; // last layer
        while((++i)<=size)
            if(heap[i]>heap[maxi]) maxi=i;
        return heap[maxi];
    }
    Dream pop(){
        Dream ret=heap[1];
        heap[1]=heap[size--];
        down(1);
        return ret;
    }
    void push(Dream&& x){
        heap[++size]=x;
        up(size);
    }
    uint64_t len(){return size;}
};

int main(){
    int k, n;
    std::cin>>k>>n;
    for(int i=0; i<k; i++) std::cin>>primes[i];
    std::sort(primes, primes+k);
    BanG bb(k*n);
    bb.push(Dream{1, 0});

    uint64_t cap=CAP_INIT;
    for(int i=0; i<n; i++){
        Dream peak=bb.pop();
        // maintain heap
        for(int j=peak.from; j<k; j++){
            Dream topush=peak*j;
            if(topush.value>cap) break;
            bb.push(std::move(topush));
        }
        if(cap==CAP_INIT && bb.len()>n)
            cap=bb.max().value;
    }
    std::cout<<bb.pop().value;
}