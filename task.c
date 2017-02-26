#include "eos.h"
#include <string.h> //not sure how much this bloats the executable, maybe make my own
#include "uart.h"

bool tasks_initialized = false;
bool runtasks = true;
void task_init()
{
    runtasks = true;
    for (int i = 0; i < MAX_TASKS; i++)
        tasks[i].isTask = false; //not initialized yet
}

void task_disable()
{
    runtasks = false;
}
void task_enable()
{
    runtasks = true;
}

void tasks_init()
{

    for (int i = 0; i < MAX_TASKS; i++)
    {
        if (tasks[i].isTask && tasks[i].init != NULL)
            tasks[i].init(tasks[i].data);
    }
    tasks_initialized = true;
}
int add_task(task *t, int startDelay) //todo alias int to some better name
{
    t->isTask = true;
    t->run = true;
    t->lastRun = startDelay;
    for (int i = 0; i < MAX_TASKS; i++)
        if (!tasks[i].isTask)
        {
            memcpy(tasks + i, t, sizeof(task));
            if (tasks_initialized)
                tasks[i].init(tasks[i].data);
            return i;
        }
    return -1;
    //todo: error here
}
void timer_run()
{
    if (!runtasks)
        return;
    //uart_write("some tasks!");
    for (int i = 0; i < MAX_TASKS; i++)
    {
        if (!tasks[i].isTask || !tasks[i].run)
            continue;
        if (--tasks[i].lastRun > tasks[i].interval)
        {
            tasks[i].task(tasks[i].data);
            if (tasks[i].interval)
                tasks[i].lastRun = tasks[i].interval;
            else
                remove_task(i);
        }
    }
}

void start_task(int t)
{
    tasks[t].lastRun = tasks[t].interval;
    tasks[t].run = true;
}
void stop_task(int t)
{
    tasks[t].run = false;
}
void remove_task(int t)
{
    tasks[t].isTask = false;
}

void configure_interval_task(int t, int i)
{
    tasks[t].interval = i;
    //tasks[t].lastRun = i;
}