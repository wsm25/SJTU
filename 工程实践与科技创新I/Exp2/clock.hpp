#ifndef CLOCK_HPP
#define CLOCK_HPP
#include <Energia.h>
typedef unsigned long u32;
class Clock;
// collection of clocks
class ClocksClass{
public:
    // fields

    // 1ms per tick, run off after about 49.7 days
    // warning: DO NOT modify tick
    volatile u32 tick;

    /// NEVER construct it!
    ClocksClass():tick(0){
        // set up timer
        // SMCLK = 25MHz, Upmode, source = SMCLK/8
        TA1CTL = TASSEL_2 | MC_1 | ID_3;
        TA1CCR0 =  3124L; // = 3125*(1/25MHz)*8 = 1 ms
        TA1CCTL0 = CCIE; // TA1CCR0 interrupt enabled
        _BIS_SR(GIE); // Enter LPM0 interrupt
    }
};

extern ClocksClass Clocks;

// clock bound to Clocks
class Clock{ // 12B
    friend class ClocksClass;
    u32 offset; // clock begin tick
public:
    u32 count; // tick count of clock
    u32 cycle; // clock cycle, MUST greater than 0
    Clock(u32 cycle):
        cycle(cycle), offset(Clocks.tick), count(0){}
    u32 read_ms(){
        return Clocks.tick-offset;
    }
    /// returns whether clock is within the tick ms  
    /// promise tick only once each cycle
    bool tick(){
        if(Clocks.tick-offset>=cycle){ // tick!
            count++; // SAFETY: ticks MUST be called within one cycle
            offset=Clocks.tick;
            return true;
        }
        return false;
    }
    // progress in one cycle from 0 to 1
    float progress(){
        return float(Clocks.tick-offset)/cycle;
    }
    void reset(){
        count=0;
        offset=Clocks.tick;
    }
};
#endif