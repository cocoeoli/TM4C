/*
 * Timer_Init.c
 *
 *  Created on: 2018Äê4ÔÂ5ÈÕ
 *      Author: admin
 */
#include "Timer_Init.h"

void SysTick_Init(uint8_t ui8IntTime_ms)//ui8IntTime_ms < 415
{
    uint32_t period = ui8IntTime_ms*(SysCtlClockGet()/1000);
    SysTickPeriodSet(period);

    SysTickIntRegister(IntHandler_SysTick);
    SysTickIntEnable();
    SysTickDisable();
}

void Timer0A_Init(uint8_t ui8IntTime_ms)//ui8IntTime_ms < 10
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);

    TimerConfigure(TIMER0_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);

    TimerPrescaleSet(TIMER0_BASE, TIMER_A, 8 - 1);

    //If ui8IntTime_ms = 10, period = 49999
    uint32_t period = ui8IntTime_ms*(SysCtlClockGet()/(TimerPrescaleGet(TIMER0_BASE, TIMER_A)+1)/1000) - 1;
    TimerLoadSet(TIMER0_BASE, TIMER_A, period);

    IntPrioritySet(INT_TIMER0A, 0<<5 + 1);
    TimerIntRegister(TIMER0_BASE, TIMER_A, IntHandler_Timer0);
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    TimerDisable(TIMER0_BASE, TIMER_A);
}
void Timer1A_Init(uint8_t ui8IntTime_ms)//ui8IntTime_ms <= 200
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);

    TimerConfigure(TIMER1_BASE, TIMER_CFG_SPLIT_PAIR | TIMER_CFG_A_PERIODIC);

    TimerPrescaleSet(TIMER1_BASE, TIMER_A, 160 - 1);

    //If ui8IntTime_ms = 200, period = 49999
    uint32_t period = ui8IntTime_ms*(SysCtlClockGet()/(TimerPrescaleGet(TIMER1_BASE, TIMER_A)+1)/1000) - 1;
    TimerLoadSet(TIMER1_BASE, TIMER_A, period);

    IntPrioritySet(INT_TIMER1A, 0<<5 + 0);
    TimerIntRegister(TIMER1_BASE, TIMER_A, IntHandler_Timer1);
    IntEnable(INT_TIMER1A);
    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);

    TimerDisable(TIMER1_BASE, TIMER_A);
}


