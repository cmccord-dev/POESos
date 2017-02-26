#include "ports.h"
#include "eos.h"
//button btn1;
portbase *port1;
//portbase port2;
//portbase port3;
button btn1 = {.pin = BTN1_PIN, .port = BTN1_PORT, .mode = PORT_IN};

void ports_init()
{
    //P1REN = 0;
    //P1IE = 0;//disable interrupts... for now
    //P1OUT = 0;
    port1 = (portbase *)&P1IN;
    //port1->ren = 0;
}
void port_init(io_port *p)
{
    switch (p->port)
    {
    case 1:
        p->base = port1;
    default:
        p->base = port1; //todo log an error here
        break;
    }
    if (p->mode == PORT_OUT)
        port_enable_out(p);
    else
        port_enable_in(p);
}

void port_enable_out(io_port *p)
{
    p->base->dir |= p->pin;
    p->base->ren &= ~p->pin;
    port_off(p);
}
void port_enable_in(io_port *p)
{
    p->base->dir &= ~p->pin;//input
    p->base->ren |= p->pin;//don't float (pull) 
    p->base->out |= p->pin;//pull up
}
void port_toggle(io_port *p)
{
    p->base->out ^= p->pin;
}
void port_off(io_port *p)
{
    p->base->out &= ~p->pin;
}
void port_on(io_port *p)
{
    p->base->out |= p->pin;
}
bool port_read(io_port *p)
{
    if ((p->base->in) & BIT3) //buttons pull low
        return true;
    return false;
}