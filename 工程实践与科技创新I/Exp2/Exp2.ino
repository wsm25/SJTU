#include "clock.hpp"
#include "button.hpp"
#include "led.hpp"

Button block(PUSH1), bwater(PUSH2);
LED llock(RED_LED, 1), lwater(GREEN_LED, 0);
Clock ck(3000), ckb(20);

int state=0;

void setup(){}

void loop(){
    // update button
    if(ckb.tick()) {
        block.update();
        bwater.update();
    }
    // state machine
    switch(state){
    case 0: // normal state
        if(block.fall()) {
            state=1;
            ck.reset(); // 3s for press
        }
        break;
    case 1: // pre-unlock state
        if(ck.tick()){ // time is up, unlock
            llock.off();
            state=2;
            ck.reset(); // 3s for resume
        } else if(block.rise())
            state=0;
        break;
    case 2: // unlock state
        if(ck.tick()){ // time is up, relock
            llock.on();
            state=0;
        } else if(bwater.fall()){
            ck.reset();
            state=3;
        }
        break;
    case 3: // water state with button down
        if(ck.tick()){
            lwater.on();
            state=5;
        }
        else if(bwater.rise()){
            lwater.on();
            state=4;
        }
        break;
    case 4: // water state with button up
        if(bwater.fall())
            state=5;
        break;
    case 5: // pre-close state with button down
        if(bwater.rise()){
            lwater.off();
            llock.on();
            state=0;
        }
    }
}