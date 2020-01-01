/*
 * My_uart.h
 *
 *  Created on: 2014Äê7ÔÂ28ÈÕ
 *      Author: Itheaven
 */

#ifndef MY_UART_H_
#define MY_UART_H_
/************
 *
 */
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/adc.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "uartstdio.h"

#define Get_Distance 0x55
#define Get_Temp 0x50

void UART_INIT(void);
void UART1_send_string(const char *sendbuf);
void UART1_send_char(const char Byte);
void Get_SDistance(int *Distance);
void Get_STemp(int *Shen_V);
//char UART1_recive_char(void);
//void UART1_recive_string(char *reciveBuf,int num);
//void UART1_send_int16_t_string(const int16_t *temp, uint64_t num);
//void UART1_send_int32_t_string(const int32_t *temp, uint64_t num);
//void UART1_send_int64_t_string(const int64_t *temp, uint64_t num);
//void UART1_send_int16_t(const int16_t temp,char on);
//void UART1_send_int32_t(const int32_t temp,char on);
//void UART1_send_int64_t(const int64_t temp,char on);
//void UART1_send_float(const float temp,int64_t lenth);
//void UART1_send_char_string(const unsigned char *temp, uint64_t num);
//void UART1_send_int64_t_string(const int64_t *temp, uint64_t num);

#endif /* MY_UART_H_ */
