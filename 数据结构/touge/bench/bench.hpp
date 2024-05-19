// for mingw windows, please use ucrt version
#ifndef WSM_BENCH_H
#define WSM_BENCH_H
#include <cstdio>
#include <cstdlib>
#include <ctime>

#define TIMEOUT 2e8 // 200ms
#define MAX_TRY 62

/*
Usage:
```cpp
void bench_xxx(Benchmark& b){
    // some init
    b.reset_timer(); // optional
    for(auto i=0; i<b.N; i++){
        // loop
        // you may use `b.rand()` to get u16 random with 1.33 ns/op
    }
    b.stop_timer(); // optional
    // clear work
}

int main(){
    Bench(bench_xxx);
}
```
*/
class Benchmark{
    typedef struct timespec Time;
    unsigned int g_seed;
    
    Time begin, from, to;
    bool timer_end;
    void(*fn)(Benchmark& b);
    double duration(const Time& ss, const Time& tt){
        return (tt.tv_sec-ss.tv_sec)*1e9+(tt.tv_nsec-ss.tv_nsec);
    }
public:
    long long unsigned N;
    Benchmark(void(*fn)(Benchmark& b)):fn(fn), N(1){
        g_seed=time(0)&0xffff;
        timespec_get(&begin, TIME_UTC);
        for(int i=0;i<MAX_TRY;i++){
            N*=2;
            timer_end=false;
            timespec_get(&from, TIME_UTC);
            fn(*this);
            if(!timer_end) timespec_get(&to, TIME_UTC);
            Time now;
            timespec_get(&now, TIME_UTC);
            if (duration(begin, now)>=TIMEOUT) break;
        }
        printf("%lf ns/op, %lld ops in total\n", duration(from, to)/N, N);
    }
    unsigned rand(){return ((g_seed = (214013*g_seed+2531011))>>16);}
    void restart_timer(){
        timespec_get(&from, TIME_UTC);
    }
    void stop_timer(){
        timer_end=true;
        timespec_get(&to, TIME_UTC);
    }
};

#define Bench(bb) do{printf("%s: ", #bb); Benchmark b(bb);}while(0)

#endif