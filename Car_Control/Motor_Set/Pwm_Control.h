/*
 * Pwm_Control.h
 *
 *  Created on: 2018Äê2ÔÂ1ÈÕ
 *      Author: wk
 */

#ifndef MOTOR_SET_PWM_CONTROL_H_
#define MOTOR_SET_PWM_CONTROL_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/pwm.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/timer.h"

extern void MoTor_Init(void);
extern void MoTor_Set(int Motor_Direction1, int PWMPulseWidth1, int Motor_Direction2, int PWMPulseWidth2);
extern void MoTor_Speed_Set(int PWMPulseWidth1, int PWMPulseWidth2);
extern void MoTor_Left_Speed_Set(int PWMPulseWidth1);
extern void MoTor_Right_Speed_Set(int PWMPulseWidth1);
extern int  MoTor_SET_Direction(int Motor_Direction);
extern void Steering_Gear_SET_Direction(int Steering_Gear_Angle);

#endif /* MOTOR_SET_PWM_CONTROL_H_ */
