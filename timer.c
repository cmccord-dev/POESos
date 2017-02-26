#include "eos.h"

#define TIMER_INTERVAL 1 //1ms interval

#define DIVIDER 8
#define TMRC (DCO_FREQ / DIVIDER / 1000 * TIMER_INTERVAL)

void timer_init()
{
    BCSCTL1 = CALBC1_16MHZ;
    
    DCOCTL = CALDCO_16MHZ;
    BCSCTL2 = 0x0;

    CCTL0 = CCIE;
    TACTL = TASSEL_2 + MC_1 + ID_3;
    CCR0 = TMRC;

}

__attribute__((interrupt(TIMER0_A0_VECTOR))) void Timer_A(void)
{
    __disable_interrupt();
    timer_run();
    __enable_interrupt();
}
