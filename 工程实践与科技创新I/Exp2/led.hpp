#ifndef LED_HPP
#define LED_HPP
#include <Energia.h>
typedef unsigned char u8;
/// Wrapper of button, cowork with hardware timer.
class LED{
    u8 led;
public:
    LED(u8 l, u8 init=0): led(l){
        pinMode(l, OUTPUT);
        digitalWrite(led, init);
    }
    /// MUST called in timer isr
    void on(){digitalWrite(led, 1);}
    void off(){digitalWrite(led, 0);}
};
#endif