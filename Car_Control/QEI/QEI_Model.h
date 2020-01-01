/*
 * QEI_Config.h
 *
 *  Created on: 2018Äê7ÔÂ6ÈÕ
 *      Author: D
 */

#ifndef QEI_QEI_CONFIG_H_
#define QEI_QEI_CONFIG_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/qei.h"

extern void QEI0_Init(unsigned int QEI0_IntTime_ms);
extern void QEI1_Init(unsigned int QEI1_IntTime_ms);
extern void IntHandler_QEI0(void);
extern void IntHandler_QEI1(void);



#endif /* QEI_QEI_CONFIG_H_ */
