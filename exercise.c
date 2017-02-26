#include "eos.h"
#include "led.h"
#include "ports.h"
#include "uart.h"
#include "msp430.h"
#define TEMP_SENSOR INCH_10

int blink_task, temp_task;
int btn_task;
bool btn_pressed;
bool btn_last;
bool blink = true;

int tempval = 20;

#define ADC_30 *((int *)(&TLV_ADC10_1_TAG + CAL_ADC_15T30))
#define ADC_85 *((int *)(&TLV_ADC10_1_TAG + CAL_ADC_15T85))

enum state_t
{
    READ_START,
    READ_READ
} state = READ_START;

void blink_led(void *ptr)
{
    if (blink)
    {
        led_toggle(&red_led);
        led_toggle(&green_led);
    }
    else
    {
        led_off(&red_led);
        led_off(&green_led);
    }
}
void init_leds(void *ptr)
{
    led_init(&red_led);
    led_init(&green_led);
}
void init_sensor(void *ptr)
{
    ADC10CTL0 = SREF_1 | REFON | ADC10ON | ADC10SHT_3;
    ADC10CTL1 = TEMP_SENSOR | ADC10DIV_3;
}

int calc_f(int temp)
{
    return (temp - ADC_30) * (185 - 86) / (ADC_85 - ADC_30) + 86;
}
int calc_c(int temp)
{
    return (temp - ADC_30) * (85 - 30) / (ADC_85 - ADC_30) + 30;
}
void read_temp(void *ptr)
{
    switch (state)
    {
    case READ_START:
        //ADC10CTL0 |= ENC | ADC10SC;
        state = READ_READ;
        configure_interval_task(temp_task, 1); //run read after 1ms
        break;
    case READ_READ:
        __delay_cycles(1000);
        ADC10CTL0 |= ENC | ADC10SC;
        while (ADC10CTL1 & BUSY)
            ;
        tempval = ADC10MEM;
        ADC10CTL0 &= ~ENC;

        uart_write("RAW: ");
        uart_writei(tempval);
        uart_write("\r\n");
        int cval = calc_c(tempval);
        int fval = calc_f(tempval);
        uart_write("Current temperature: ");
        uart_writei(cval);
        uart_write("c (");
        uart_writei(fval);
        uart_write("f)\r\n");
        state = READ_START;
        configure_interval_task(temp_task, 999);
        configure_interval_task(blink_task, 1000/cval);
        break;
    }
}

void check_button(void *b)
{
    bool state = port_read((button *)b);
    if (!btn_pressed)
    {
        if (btn_last == state && state == false)
        {
            btn_pressed = true;
            blink = !blink;
        }
    }
    else
    {
        if (btn_last == state && state == true)
        {
            btn_pressed = false;
        }
    }
    btn_last = state;
}

void setup_tasks()
{
    task t;
    t.interval = 500; //in  ms
    t.task = blink_led;
    t.data = NULL;
    t.init = (func)init_leds;
    blink_task = add_task(&t, 0); //add_task copies the data so we can safely do this

    t.interval = 20;
    t.data = &btn1;
    t.task = check_button;
    t.init = (func)port_init;
    btn_task = add_task(&t, 0);

    t.interval = 1; //in 10 ms
    t.task = read_temp;
    t.data = NULL;
    t.init = (func)init_sensor;
    temp_task = add_task(&t, 500); //add_task copies the data so we can safely do this
    //uart_write("Initialized...");
}