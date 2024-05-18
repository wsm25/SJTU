#include "clock.hpp"

// ClocksClass

ClocksClass Clocks;

/// NEVER construct it!
ClocksClass::ClocksClass():
    tick(0), head(0){
    // set up timer
    TA1CTL = TASSEL_2 | MC_1 | ID_3; // SMCLK = 25MHz, source = SMCLK/8, Upmode   
    TA1CCR0 =  3125L;      // = 3125*(1/25M)*8 = 1m
    TA1CCTL0 = CCIE; // TA1CCR0 interrupt enabled
    _BIS_SR(GIE); // Enter LPM0 interrupt
}

void ClocksClass::timerisr(){
    tick++;
    // run ISRs
    for(Clock* ck=head; ck!=0; ck=ck->next){
        if(ck->tick()) (ck->isr)();
    }
};

// timer A1
#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer1_A0 (){Clocks.timerisr();}