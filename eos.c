#include "eos.h"
#include "ports.h"
#include "uart.h"
void disable_watchdog()
{
    WDTCTL = WDTPW | WDTHOLD;
}
void eos_init()
{
    disable_watchdog(); //maybe later we can handle this appropriately..
    ports_init();
    timer_init();       //could be done implicitly using a task but we'll put it here for now
    task_init();
    uart_init();
}
void eos_run()
{
    tasks_init();
    __enable_interrupt();
    while (1)
        LPM1;

    //LPM3;
}

#define RED_LED BIT0
#define GREEN_LED BIT6
void debugBlink()
{
    P1DIR |= RED_LED | GREEN_LED; // Set P1.0,6 to output direction

    P1OUT = (P1OUT & ~RED_LED) | GREEN_LED;
    while (1)
    {
        volatile unsigned int i; // volatile to prevent optimization
        volatile unsigned int c;
        P1OUT ^= RED_LED | GREEN_LED; // Toggle P1.0,6 using exclusive-OR

        c = 32;
        while (c--)
        {              //i like longer delays...
            i = 10000; // SW Delay
            do
                i--;
            while (i != 0);
        }
    }
}