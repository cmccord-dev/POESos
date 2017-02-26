#ifndef PORTS_H
#define PORTS_H
#include "msp430.h"
#include "eos.h"


struct portbase_struct{
    volatile unsigned char in;
    volatile unsigned char out;
    volatile unsigned char dir; 
    volatile unsigned char ifg; 
    volatile unsigned char ies; 
    volatile unsigned char ie; 
    volatile unsigned char sel;
    volatile unsigned char ren;  
};
typedef struct portbase_struct portbase;
struct port_struct
{
    portbase *base;
    int pin;
    char port;
    char mode;
};
typedef struct port_struct io_port;

void ports_init();

void port_init(io_port *);
void port_enable_in(io_port *);
void port_enable_out(io_port *);
void port_toggle(io_port *);
void port_off(io_port *);
void port_on(io_port *);
bool port_read(io_port *);


#define RED_LED_PORT 1 
#define RED_LED_PIN BIT0
#define GREEN_LED_PORT 1
#define GREEN_LED_PIN BIT6

#define BTN1_PORT 1
#define BTN1_PIN BIT3

#define PORT_OUT 1
#define PORT_IN 2

typedef io_port button;
extern button btn1;
extern portbase *port1;
//extern portbase port2;
//extern portbase port3;
#endif