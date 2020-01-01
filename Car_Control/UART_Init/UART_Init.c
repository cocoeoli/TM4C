/*
 * UART_Init.c
 *
 *  Created on: 2018Äê2ÔÂ2ÈÕ
 *      Author: admin
 */
#include "UART_Init.h"

void UART0_Init(uint32_t ui32Baud)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);//Clock 16MHz
    UARTStdioConfig(0, ui32Baud, 16000000);

    //UARTIntRegister(UART0_BASE, IntHandler_UART0);
    //UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    //IntEnable(INT_UART0);
}
void UART0printf(char *pString)
{
    uint16_t i = 0;
    while(pString[i] != '\0')
        UARTCharPut(UART0_BASE, pString[i++]);
}

void UART1_Init(uint32_t ui32Baud)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);//Clock 16MHz
    UARTStdioConfig(1, ui32Baud, 16000000);
}
void UART1printf(char *pString)
{
    uint16_t i = 0;
    while(pString[i] != '\0')
        UARTCharPut(UART1_BASE, pString[i++]);
}
