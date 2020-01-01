/*
 * Timer_Init.h
 *
 *  Created on: 2018Äê4ÔÂ5ÈÕ
 *      Author: admin
 */

#ifndef TIMER_INIT_H_
#define TIMER_INIT_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"


extern void SysTick_Init(uint8_t ui8IntTime_ms);//ui8IntTime_ms < 415ms
extern void IntHandler_SysTick(void);

extern void Timer0A_Init(uint8_t ui8IntTime_ms);//ui8IntTime_ms < 10
extern void IntHandler_Timer0(void);

extern void Timer1A_Init(uint8_t ui8IntTime_ms);//ui8IntTime_ms <= 200
extern void IntHandler_Timer1(void);

#endif /* TIMER_INIT_H_ */
