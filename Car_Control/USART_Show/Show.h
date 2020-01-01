/*
 * Show.h
 *
 *  Created on: 2018Äê4ÔÂ6ÈÕ
 *      Author: admin
 */

#ifndef USART_SHOW_SHOW_H_
#define USART_SHOW_SHOW_H_

#include "UART_Init.h"

#define UART_BASE_ADDRESS_Show UART1_BASE

extern void ShowValue(uint8_t Pos, int16_t Value);

#endif /* USART_SHOW_SHOW_H_ */
