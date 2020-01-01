/*
 * UART_Init.h
 *
 *  Created on: 2018Äê2ÔÂ2ÈÕ
 *      Author: admin
 */

#ifndef UART_INIT_UART_INIT_H_
#define UART_INIT_UART_INIT_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/interrupt.h"
#include "utils/uartstdio.h"

extern void UART0_Init(uint32_t ui32Baud);
extern void UART0printf(char *pString);
extern void IntHandler_UART0(void);

extern void UART1_Init(uint32_t ui32Baud);
extern void UART1printf(char *pString);

#endif /* UART_INIT_UART_INIT_H_ */
