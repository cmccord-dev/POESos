#include "eos.h"
#include "led.h"
#include "ports.h"
#include "uart.h"
enum state_t
{
    RED,
    REDGREEN,
    GREEN,
    GREENRED,
    BLINKING
} state = BLINKING;

int red_blink;
int green_blink;
int btn_task;
int state_task;
bool btn_pressed;
bool btn_last;

void blink_led(void *l)
{
    led_toggle((led *)l);
}
void change_state(void *l)
{
    switch (state)
    {
    case BLINKING:
        stop_task(green_blink);
        stop_task(red_blink);
    case GREENRED:
        configure_interval_task(state_task, 500);
        led_off(&green_led);
        led_on(&red_led);
        state = RED;
        break;
    case RED:
        configure_interval_task(state_task, 50);
        led_on(&green_led);
        led_on(&red_led);
        state = REDGREEN;
        break;
    case REDGREEN:
        configure_interval_task(state_task, 500);
        led_on(&green_led);
        led_off(&red_led);
        state = GREEN;
        break;
    case GREEN:
        configure_interval_task(state_task, 50);
        led_on(&green_led);
        led_on(&red_led);
        state = GREENRED;
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
            if (state == RED)
            {
                configure_interval_task(state_task, 50);
                led_on(&green_led);
                led_on(&red_led);
                state = REDGREEN;
            }
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
    t.interval = 40; //in 10 ms
    t.task = blink_led;
    t.data = &red_led;
    t.init = (func)port_init;
    red_blink = add_task(&t); //add_task copies the data so we can safely do this

    t.data = &green_led;
    green_blink = add_task(&t);

    t.interval = 2;
    t.data = &btn1;
    t.task = check_button;
    btn_task = add_task(&t);

    t.interval = 500;
    //t.interval = 30;
    t.init = NULL;
    t.data = &state;
    t.task = change_state;
    state_task = add_task(&t);

    //uart_write("Initialized...");
}

int main()
{
    eos_init();
    setup_tasks();

    eos_run();

    return 1;
}