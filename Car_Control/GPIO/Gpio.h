/*
 * Gpio.h
 *
 *  Created on: 2018Äê2ÔÂ1ÈÕ
 *      Author: wk
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_


#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/qei.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/rom.h"


void Led_Key_Init(void);
unsigned char key_scan(void);



#endif /* GPIO_GPIO_H_ */
