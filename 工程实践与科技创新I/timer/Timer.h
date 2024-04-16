#ifndef _TIMER_H
#define _TIMER_H

extern void (*timerFunc)(void);

// SetTimer : 定时器设置函数
// timerFunction : 定期器中断服务程序函数名
// timerPeriod_ms ：定期周期，单位为ms,取值范围1-20
void SetTimer(void (*timerFunction)(void), uint32_t timerPeriod_ms = 20);

#endif