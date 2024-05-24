#include <Energia.h>
#include "clock.hpp"
#include "button.hpp"
#include "led.hpp"

Button block(PUSH1), bwater(PUSH2);
LED llock(RED_LED, 1), lwater(GREEN_LED, 0);
Clock cb(20), ck(5000);

int state=0;
void setup(){}

void loop(){
    if(cb.tick()){
        block.update();
        bwater.update();
    }
    // state machine
    switch(state){
    case 0: // normal state
        if(block.fall()) {
            state=1;
            ck.reset(); // 5s for press
        }
        break;
    case 1: // pre-unlock state
        if(ck.tick()){ // time is up, unlock
            llock.off();
            state=2;
            ck.reset(); // 5s for resume
        } else if(block.rise())
            state=0;
        break;
    case 2: // unlock state
        if(ck.tick()){ // time is up, relock
            llock.on();
            state=0;
        } else if(bwater.fall())
            state=3;
        break;
    case 3: // water state with button first down
        if(bwater.rise()){
            lwater.on();
            state=4;
        }
        break;
    case 4: // water state with button up
        if(bwater.fall()){
            ck.cycle=300; // reuse the clock
            state=5;
        }
        break;
    case 5: // pre-close state with button first down
        if(bwater.rise()){
            ck.reset();
            state=6;
        }
        break;
    case 6: // pre-close state with button first up
        if(bwater.down())
            state=7;
        if(ck.tick()) // 300ms is up
            state=4;
        break;
    case 7: // pre-close state with button down
        if(bwater.rise()){ // fin
            lwater.off();
            llock.on();
            ck.cycle=5000; //  reuse the clock
            state=0;
        }
        if(ck.tick()) // 300ms is up
            state=5;
        break;
    }
}