#include "ports.h"
#include "led.h"

led red_led = {.pin = RED_LED_PIN, .port = RED_LED_PORT, .mode = PORT_OUT};
led green_led = {.pin = GREEN_LED_PIN, .port = GREEN_LED_PORT, .mode = PORT_OUT};

/*
void _led_init(led *l)
{
    *l->dir |= l->pin;
    led_off(l);
}
bool leds_initialized = false;
void led_init()
{
    if (leds_initialized)
        return;
    red_led.dir = &RED_LED_DIR;
    red_led.out = &RED_LED_OUT;
    red_led.pin = RED_LED_PIN;
    green_led.dir = &GREEN_LED_DIR;
    green_led.out = &GREEN_LED_OUT;
    green_led.pin = GREEN_LED_PIN;
    _led_init(&red_led);
    _led_init(&green_led);
    leds_initialized = true;
}*/