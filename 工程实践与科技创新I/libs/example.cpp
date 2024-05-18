#include "clock.hpp"
#include "button.hpp"
#include "led.hpp"

Clock ck_but(20);

// pwm
int n=0;
const int state_n=10;
const u32 states[][2]={{1, 100}, {1, 40}, {1, 20}, {1,10}, {1,5}, {1,3}, {1,2}, {2,3}, {4,5}, {1,1}};

Button but(PUSH2);
LED led(RED_LED);

u32 count=0;

void setup(){}

void loop(){
    // update button, MUST called every loop
    if(ck_but.tick()){
        but.update();
        if(but.fall())
            n=(n+1)%state_n;
    }
    count=(count+1)%states[n][1];
    led.write(count<states[n][0]);
}
