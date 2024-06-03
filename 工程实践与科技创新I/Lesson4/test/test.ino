#include "hx711.h"
#include "button.hpp"
HX711 sensor(P2_7,P4_1);
float K=201.5897251e-5; // 200.9e-5
float B=-675.1557524; // -672.86
float last_result;

// unit
enum Unit{
    Gram,
    Kilogram,
    Ounce,
    Pound,
    Maxunit
};
Unit unit=Gram;
const char* unit_names[]={"g", "kg", "oz", "lb"};
float units[]={1., .001, 0.0352739619, 0.00220462262}; // g, kg, oz, lb
float mods[]={.5, .0005, .0002, .0001};
int digits[]={1, 3, 5, 5};

Button p1(PUSH1), p2(PUSH2), p22(PUSH2);
volatile long unsigned tick=0;
int status=0; // 0 normal, 1 button down

// timer A1
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0(){
    tick++;
    p1.update();
    if(p1.fall()) unit=Unit((unit+1)%Maxunit);
    p2.update();
    if(p2.fall()) B-=last_result;
    p22.update();
    switch(status){
    case 0: 
        if(p22.fall()){
            status=1;
            tick=0;
        }
        break;
    case 1:
        if(tick>=50) status=2;
        else if(p22.rise()) status=0;
        else tick++;
        break;
    }
}

void setup(){
    Serial.begin(9600);

    // set up timer
    // SMCLK = 25MHz, Upmode, source = SMCLK/8
    TA1CTL = TASSEL_2 | MC_1 | ID_3;
    TA1CCR0 =  3125L*20-1; // = 3125*(1/25MHz)*8 = 1 ms
    TA1CCTL0 = CCIE; // TA1CCR0 interrupt enabled
    _BIS_SR(GIE); // Enter LPM0 interrupt

    sleep(10);
    long sum=0;
    for(int i=0; i<5; i++) {
        while(sensor.waiting()); // stuck!
        sum+=sensor.read();
    }
    B=-K*float(sum/5); // assume init 0
};

float floor(float x, float mod){
    return long(x/mod+0.5*mod)*mod;
}

void loop(){
    if(status==2){
        Serial.println("Calibration Starts, please left platform empty and press PUSH2");
        sleep(20);
        do p22.update(); while(p22.down());
        sleep(20);
        do p22.update(); while(p22.up());
        sleep(20);
        do p22.update(); while(p22.down());
        long x1=0;
        for(int i=0; i<5; i++) {
            while(sensor.waiting()); // stuck!
            x1+=sensor.read();
        }
        x1/=5;
        Serial.println("Please put 50g on platform and press PUSH2");
        do p22.update(); while(p22.up());
        sleep(20);
        do p22.update(); while(p22.down());
        long x2=0;
        for(int i=0; i<5; i++) {
            while(sensor.waiting()); // stuck!
            x2+=sensor.read();
        }
        x2/=5;
        Serial.println("Calibration Finished! please left platform empty and press PUSH2");
        K=50./float(x2-x1);
        B=-K*x1;
        status=0;
    }
    long sum=0;
    for(int i=0; i<5; i++) {
        while(sensor.waiting()); // stuck!
        sum+=sensor.read();
    }
    float gram=K*float(sum/5)+B;
    last_result=gram;
    Serial.print(floor(gram*units[unit], mods[unit]), digits[unit]);
    Serial.print(' ');
    Serial.println(unit_names[unit]);
}
