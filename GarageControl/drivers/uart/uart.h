/*
 * uart.h
 *
 *  Created on: 2019Äê1ÔÂ24ÈÕ
 *      Author: xiong
 */

#ifndef UART_H_
#define UART_H_


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
#include <stdio.h>

void UART_send_string(const char *sendbuf, int32_t URATX);
void UART_send_char(const unsigned char Byte, int32_t URATX);
char UART_recive_char( int32_t URATX);
void UART_recive_string(char *reciveBuf,int num, int32_t URATX);
void UART_send_int16_t_string(const int16_t *temp, uint64_t num, int32_t URATX);
void UART_send_int32_t_string(const int32_t *temp, uint64_t num, int32_t URATX);
void UART_send_int64_t_string(const int64_t *temp, uint64_t num, int32_t URATX);
void UART_send_int16_t(const int16_t temp,char on, int32_t URATX);
void UART_send_int32_t(const int32_t temp,char on, int32_t URATX);
void UART_send_int64_t(const int64_t temp,char on, int32_t URATX);
void UART_send_float(const float temp,int64_t lenth, int32_t URATX);
void UART_send_char_string(const unsigned char *temp, uint64_t num, int32_t URATX);
void UART_send_int64_t_string(const int64_t *temp, uint64_t num, int32_t URATX);
void UART0_init(void);
//void UART1_Init(uint32_t ui32Baud);
void UART0IntHandler(void);
void UART5IntHandler(void);
//void UART1IntHandler(void);

void UART5_Init(uint32_t Baud);

//void Data1pro(void);

#endif /* UART_H_ */
