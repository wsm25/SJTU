#include <iostream>

int gcm(uint64_t a, uint64_t b){
    if (b==0) return a;
    return gcm(b, a%b);
}

int gcm_simu(uint64_t a, uint64_t b){
    // uint64_t dummy[1000], *rsp=dummy; // Tail recursion optimization
    while(b!=0){
        /* Tail recursion optimization
        *(rsp++)=a;
        *(rsp++)=b;
        */
        uint64_t rdx=a;
        a=b; b=rdx%b;
    }
    uint64_t rax=a;
    /* Tail recursion optimization
    while(rsp>dummy){
        b=*(--rsp);
        a=*(--rsp);
        *rsp=rax;
    }
    ret;
    */
    return rax;
}

int main(){
    uint64_t a,b;
    std::cin>>a>>b;
    std::cout<<gcm_simu(a,b);
    return 0;
}