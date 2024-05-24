#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <Energia.h>
/// Wrapper of button, cowork with timer.
class Button{
    bool status;
    uint8_t button;
    bool changed; // for edge judgement
public:
    Button(uint8_t b):
        status(1), button(b), changed(false){
        pinMode(b, INPUT_PULLUP);
    }
    /// MUST called in timer isr
    void update(){
        int p=digitalRead(button);
        if(p!=status){
            status=p;
            changed=true;
        }
    }
    bool toggle(){
        bool ret=changed;
        changed=false;
        return ret;
    }
    /// falling edge of button 
    bool fall(){return toggle()?!status:false;}
    /// rising edge of button
    bool rise(){return toggle()? status:false;}
    // whether button is down
    bool down(){return !status;}
    // whether button is up
    bool up(){return status;}
};

#endif