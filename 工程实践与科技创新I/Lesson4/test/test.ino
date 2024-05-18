#include "HX711.h"
#include "Timer.h"
HX711 sensor(P2_7,P4_1);
const float K=201.5897251e-5; // 200.9e-5
float B=-675.1557524; // -672.86

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
float mods[]={.5, .0005, .02, .01};

float last_result;

class Button{
    int status;
    uint8_t button;
public:
    Button(uint8_t b):
        status(1), button(b){}
    bool down(){
        int p=digitalRead(button);
        if(p!=status){
            status=p;
            if(!p) return true;
        }
        return false;
    }
    bool raise(){
        int p=digitalRead(button);
        if(p!=status){
            status=p;
            if(p) return true;
        }
        return false;
    }
};

Button p1(PUSH1), p2(PUSH2);
void push(){
    if(p1.down()) unit=Unit((unit+1)%Maxunit);
    if(p2.down()) B-=last_result;
}

void setup(){
    Serial.begin(9600);
    sensor.begin();
    pinMode(PUSH2, INPUT_PULLUP);
    SetTimer(push, 20);
};

float floor(float x, float mod){
    return long(x/mod+0.5*mod)*mod;
}

void loop(){
    long sum=0;
    for(int i=0; i<5; i++) sum+=sensor.HX711_Read();
    float gram=K*float(sum/5)+B;
    last_result=gram;
    Serial.print(floor(gram*units[unit], mods[unit]));
    Serial.print(' ');
    Serial.println(unit_names[unit]);
}
