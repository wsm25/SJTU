#ifndef CLOCK_HPP
#define CLOCK_HPP
#include <stdint.h>
#include <Energia.h>
class Clock;
// collection of clocks
class ClocksClass{
    // fields
    volatile uint32_t tick; // 1ms per tick, run off after about 49.7 days
    Clock* head;
    friend class Clock;
public:
    /// NEVER construct it!
    ClocksClass();
    void timerisr();
};

extern ClocksClass Clocks;

// clock bound to Clocks
class Clock{ // 16B
    uint32_t offset; // clock begin tick
    
    void (*isr)(); // callback function, null if no callback
    Clock* next; // linked structure to allow deletion
    friend class ClocksClass;
public:
    uint32_t cycle; // clock cycle
    Clock(uint32_t cycle, void(*isr)()=0):
        cycle(cycle), isr(isr){
        offset=Clocks.tick;
        // only callbacked clock should be inserted
        if(isr){
            next=Clocks.head;
            Clocks.head=this;
        }
    }
    ~Clock(){drop();}
    uint32_t read_ms(){
        return Clocks.tick-offset;
    }
    // returns whether clock is within the tick ms
    bool tick(){
        return (Clocks.tick-offset)%cycle==0;
    }
    /// returns tick count of clock
    uint32_t count(){
        return (Clocks.tick-offset)/cycle;
    }
    void reset(){
        offset=Clocks.tick;
    }
    // drop the clock from clocks
    void drop(){
        if(isr==0 || Clocks.head==0) return;
        if(this==Clocks.head) {
            Clocks.head=Clocks.head->next; 
            return;
        }
        for(Clock& ck=*Clocks.head; ck.next!=0; ck=*(ck.next)){
            if(this==ck.next){ // found, remove from list
                ck.next=this->next;
                return;
            }
        }
    }
};
#endif