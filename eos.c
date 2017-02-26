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
    timer_init(); //could be done implicitly using a task but we'll put it here for now
    task_init();
    uart_init();
}
void eos_run()
{
    tasks_init();
    __enable_interrupt();
    uart_write("\r\nstarting!\r\n");
    while (1)
    {
        //uart_write("starting!");
        //delay(32);
        LPM1;
    }

    //LPM3;
}

#define RED_LED BIT0
#define GREEN_LED BIT6
void debugBlink()
{
    task_disable();
    P1DIR |= RED_LED | GREEN_LED; // Set P1.0,6 to output direction

    P1OUT = (P1OUT & ~RED_LED) | GREEN_LED;
    while (1)
    {
        P1OUT ^= RED_LED | GREEN_LED; // Toggle P1.0,6 using exclusive-OR
        delay(32);
    }
}

void delay(volatile int c)
{
    volatile int i;
    while (c--)
    {              //i like longer delays...
        i = 10000; // SW Delay
        do
            i--;
        while (i != 0);
    }
}



extern void setup_tasks();
int main()
{
    eos_init();
    setup_tasks();

    eos_run();

    return 1;
}