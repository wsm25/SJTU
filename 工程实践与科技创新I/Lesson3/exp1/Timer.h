#ifndef _TIMER_H
#define _TIMER_H
#include <Energia.h>

extern void (*timerFunc)(void);

/// @brief 定时器设置函数
/// @param timerFunction 定期器中断服务程序函数名
/// @param timerPeriod_ms 定期周期，单位为ms,取值范围1-20
void SetTimer(void (*timerFunction)(void), uint32_t timerPeriod_ms = 20);

/// @brief 定时器设置函数
/// @param timerFunction 定期器中断服务程序函数名
/// @param timerPeriod_us 定期周期，单位为 us,取值范围1-20971
void SetTimer_us(void (*timerFunction)(void), uint32_t timerPeriod_us = 20000);

#endif