#include "Timer.h"
 
void (*timerFunc)(void);

/// @brief 定时器设置函数
/// @param timerFunction 定期器中断服务程序函数名
/// @param timerPeriod_ms 定期周期，单位为ms,取值范围1-20
void SetTimer(void (*timerFunction)(void), uint32_t timerPeriod_ms)
{
    if(timerPeriod_ms <= 0)       
       timerPeriod_ms = 1;
    if(timerPeriod_ms >= 20)
       timerPeriod_ms = 20;
   
    timerFunc = timerFunction;             // Set ISR 
    TA1CTL = TASSEL_2 + MC_1+ ID_3;        // SMCLK = 25MHz, source = SMCLK/8, Upmode   
    TA1CCR0 = timerPeriod_ms * 3125L;          
    TA1CCTL0 = CCIE;                       // TA1CCR0 interrupt enabled
    _BIS_SR(GIE);                          // Enter LPM0 interrupt
}

// 中断服务程序
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0 (void)
{
	timerFunc();
}
