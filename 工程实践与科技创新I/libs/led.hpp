#ifndef LED_HPP
#define LED_HPP
#include <Energia.h>
typedef unsigned char u8;
/// Wrapper of button, cowork with hardware timer.
class LED{
    u8 led;
    u8 last; // allow minimized digital write
public:
    LED(u8 l, u8 init=0): led(l), last(init){
        pinMode(l, OUTPUT);
        digitalWrite(led, init);
    }
    void write(u8 n){
        if(last!=n) {
            last=n;
            digitalWrite(led, n);
        }
    }
    /// MUST called in timer isr
    void on(){write(1);}
    void off(){write(0);}
};
#endif