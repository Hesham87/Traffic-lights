#include "liberary.h"

void Timer0_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, 16000000);
    TimerEnable(TIMER0_BASE, TIMER_A);
}
void Timer1_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER1_BASE, TIMER_A, 16000000);
    TimerEnable(TIMER1_BASE, TIMER_A);
}
void T0_delay(int sec)
{
    Timer0_Init();
    volatile int counter = 0;
    while (counter < sec)
    {
        while ((TIMER0_RIS_R & 0X01) == 0);
        counter++;
        TIMER0_ICR_R = 0X1;
    }
}
void T1_delay(int sec)
{
    Timer1_Init();
    volatile int counter = 0;
    while (counter < sec)
    {
        while ((TIMER1_RIS_R & 0X01) == 0);
        counter++;
        TIMER1_ICR_R = 0X1;
    }
}