/*
 * delay.c
 *
 *  Created on: 2018��1��26��
 *      Author: wk
 */

#include "delay.h"

void delay_us(unsigned int n)
{
    SysCtlDelay(n*SysCtlClockGet()/3000000);
}

void delay_ms(unsigned int n)
{
    SysCtlDelay(n*SysCtlClockGet()/3000);
}

void delay_s(unsigned int n)
{
    SysCtlDelay(n*SysCtlClockGet()/3);
}
