#include "bench.hpp"
#include <cstdio>
#include <algorithm>

#include "qsort.hpp"
void bench_qsort(Benchmark& b){
    int *arr=new int[b.N];
    for(auto i=0ull; i<b.N; i++) arr[i]=b.rand();
    b.restart_timer();
    qsort(arr, arr+b.N);
    b.stop_timer();
    delete []arr;
}

void bench_sort(Benchmark& b){
    int *arr=new int[b.N];
    for(auto i=0ull; i<b.N; i++) arr[i]=b.rand();
    b.restart_timer();
    std::sort(arr, arr+b.N);
    b.stop_timer();
    delete []arr;
}


int main(){
    Bench(bench_qsort);
    Bench(bench_sort);
}