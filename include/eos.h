#ifndef EOS_H
#define EOS_H
#include "msp430.h"

#define DCO_FREQ 16 * 1e6


#define MAX_TASKS 4

typedef void (*func)(void*);
typedef unsigned char byte;
typedef unsigned char bool;
#define true 1
#define false 0
#define NULL 0

struct task_struct
{
    func task;
    func init;
    void* data;
    unsigned int interval;
    unsigned int lastRun;
    bool run;
    bool isTask;
};
typedef struct task_struct task;

void eos_init();
void eos_run();

void task_init();
void tasks_init();
int add_task(task *t, int);
void stop_task(int);
void start_task(int);
void remove_task(int);
void configure_interval_task(int, int);
void task_enable();
void task_disable();
void timer_init();
void timer_run();
void debugBlink();

void delay(volatile int);
task tasks[MAX_TASKS];
#endif