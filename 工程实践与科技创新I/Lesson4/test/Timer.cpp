#include "Timer.h"
 
void (*timerFunc)(void);

void SetTimer(void (*timerFunction)(void), uint32_t timerPeriod_ms)
{
    if(timerPeriod_ms <= 0)       
       timerPeriod_ms = 1;
    if(timerPeriod_ms >= 20)
       timerPeriod_ms = 20;
   
    timerFunc = timerFunction;             // Set ISR 
    TA1CTL = TASSEL_2 + MC_1+ ID_3;        // SMCLK = 25MHz, source = SMCLK/8, Upmode   
    TA1CCR0 = timerPeriod_ms * 3125L;      // = ms * 1e5 / 2e5
    TA1CCTL0 = CCIE;                       // TA1CCR0 interrupt enabled
    _BIS_SR(GIE);                          // Enter LPM0 interrupt
}

void SetTimer_us(void (*timerFunction)(void), uint16_t timerPeriod_us)
{
    if(timerPeriod_us <= 0) return;        // invalid period, never run
    if(timerPeriod_us >= 20972)
       timerPeriod_us = 20971;
   
    timerFunc = timerFunction;             // Set ISR 
    TA1CTL = TASSEL_2 + MC_1+ ID_3;        // SMCLK = 25MHz, source = SMCLK/8, Upmode   
    TA1CCR0 = (timerPeriod_us * 25)/8;     // = us * 1e2 / 2e5
    TA1CCTL0 = CCIE;                       // TA1CCR0 interrupt enabled
    _BIS_SR(GIE);                          // Enter LPM0 interrupt
}

// 中断服务程序
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0 (void)
{
	timerFunc();
}
