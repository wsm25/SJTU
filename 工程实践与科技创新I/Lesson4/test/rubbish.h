#ifndef __HX711__H__
#define __HX711__H__

#include <Energia.h>    //使用Energia的头文件

class HX711
{
    int SCK, DT; // output and input pin
    // read one bit from DT pin with 
    inline int readDT() {
        digitalWrite(SCK, HIGH);  // SCK=1 
        // pause for 5 cycles, 0.2 us
        // asm("nop\n\tnop\n\tnop\n\tnop\n\tnop");
        delayMicroseconds(1);
        int read=digitalRead(DT); // read
        digitalWrite(SCK, LOW);  // SCK=0
        // asm("nop\n\tnop\n\tnop\n\tnop\n\tnop");
        delayMicroseconds(1);
        return read;
    }
public:
    HX711(int SCK,int DT):SCK(SCK), DT(DT){}
    // 初始化HX711 
    void begin() { 
        pinMode(SCK, OUTPUT);	
        pinMode(DT, INPUT);
        digitalWrite(SCK, LOW);
    }
    // 传感器数据读取函数
    long read() {
        while(digitalRead(DT)); // wait for AD conversion
        noInterrupts(); // prevent serial error
        long count=0;
        for(int i = 0; i < 24; i++) // 24 valid bits
            count=(count<<1)+readDT();
        readDT(); // Channel A, Gain 128
        interrupts();
        // 2's complement with msb of 23
        if(count&(1<<23)) count|=-(1<<24); // complete bit 24-31
        return count;
    }
};
#endif