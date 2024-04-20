#include "Timer.h"
volatile unsigned clock=0; // *10ms
unsigned buttonstate=0; // 0 for on and 1 for off

void timer_cb() {
    if((clock++)==10000) clock=0;
}

void setup() {
    pinMode(PUSH2, INPUT_PULLUP);
    pinMode(GREEN_LED, OUTPUT);
    SetTimer(timer_cb, 10);
}

void loop() {
    int but = digitalRead(PUSH2);
    if(buttonstate!=but) clock=0; // instant reaction
    buttonstate=but;
    if(but) digitalWrite(GREEN_LED, (clock%400)<200);
    else digitalWrite(GREEN_LED, (clock%20)<10);
}