#include "Timer.h"
unsigned clock=0; // in 10ms
unsigned buttoncount=0;
unsigned buttonstate=0; // 0 for off and 1 for on

volatile int greenstate=0; // 20 ms * 50

void timer_cb(){
    greenstate++;
}


// the setup routine runs once when you press reset:
void setup() {
    pinMode(PUSH2, INPUT_PULLUP);
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    SetTimer(timer_cb);
}

// the loop routine runs over and over again forever:
void loop() {
    // red
    int but = digitalRead(PUSH2);
    if (but!=buttonstate) {
        delay(10);
        int newbut = digitalRead(PUSH2);
        if (newbut==but) {
            if (but==LOW) buttoncount++;
            buttonstate=but;
        }
    }
    if (buttoncount%4) digitalWrite(RED_LED, LOW);
    else digitalWrite(RED_LED, HIGH);
    // green
    digitalWrite(GREEN_LED, (greenstate%100 < 50));
}
