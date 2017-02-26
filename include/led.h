#ifndef LED_H
#define LED_H
#include "eos.h"
#include "ports.h"

typedef io_port led;

extern led red_led;
extern led green_led;

//void led_init();
#define led_init port_init
#define led_toggle port_toggle
#define led_on port_on
#define led_off port_off
//void led_toggle(led *);
//void led_off(led *);
//void led_on(led *);

#endif