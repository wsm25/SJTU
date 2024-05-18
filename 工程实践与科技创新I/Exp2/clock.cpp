#include "clock.hpp"

// ClocksClass
ClocksClass Clocks;

// timer A1
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0 (){Clocks.tick++;}