/*
 * uart.c
 *
 *  Created on: 2019年1月24日
 *      Author: xiong
 */
#include "uart.h"

void UART_send_char(const unsigned char Byte, int32_t URATX)
{
    UARTCharPut(URATX, Byte);
}
char UART_recive_char(int32_t URATX)
{
    char Byte;
    Byte = UARTCharGet(URATX);
    return Byte;
}
void UART_send_string(const char *sendbuf, int32_t URATX)
{
    while(*sendbuf != '\0')
    {
        UART_send_char(*sendbuf, URATX);
        sendbuf ++;
    }
}

void UART_send_int64_t(const int64_t temp,char on, int32_t URATX)
{
    int64_t temp_p = temp;

    if(temp_p < 0)
    {
        UART_send_char('-', URATX);
        temp_p = 0-temp_p;
    }
    if(temp_p > 0)
    {
        UART_send_int64_t(temp_p/10,0,URATX);
        UART_send_char(temp_p%10 + '0', URATX);
    }
    else if(temp_p == 0)
    {
        if(on)
            UART_send_char('0',URATX);
    //  UART_send_char('\n');
    }
}

void UART_send_int32_t(const int32_t temp,char on,int32_t URATX)
{
    UART_send_int64_t((int64_t) temp,on, URATX);
}

void UART_send_int16_t(const int16_t temp,char on, int32_t URATX)
{
    UART_send_int64_t((int64_t) temp,on, URATX);
}

void UART_send_float(const float temp,int64_t lenth, int32_t URATX)
{
    int64_t i;
    float num = temp;
    int64_t temp_p;
   //发送整数部分
    if(num<0)
    {
        UART_send_char('-', URATX);
        num = 0-num;
    }
    temp_p = (int64_t)num;
    UART_send_int64_t(temp_p,1, URATX);
    UART_send_char('.', URATX);
    //发送n位小数
    for(i=0; i<lenth; i++)
    {
        UART_send_char(((int)(10*(num - temp_p)))%10 + '0', URATX);
        num = num*10;
        temp_p = (int64_t)num;
    }

}

void UART_send_int64_t_string(const int64_t *temp, uint64_t num, int32_t URATX )
{
    uint64_t i;
    for(i=0; i<num; i++)
        UART_send_int64_t(temp[i],1,URATX);
}
void UART_send_int32_t_string(const int32_t *temp, uint64_t num, int32_t URATX)
{
    uint64_t i;
    for(i=0; i<num; i++)
        UART_send_int32_t(temp[i],1, URATX);
}
void UART_send_int16_t_string(const int16_t *temp, uint64_t num, int32_t URATX)
{
    uint64_t i;
    for(i=0; i<num; i++)
        UART_send_int16_t(temp[i],1, URATX);
}
void UART_send_char_string(const unsigned char *temp, uint64_t num, int32_t URATX)
{
    uint64_t i;
    for(i=0; i<num; i++)
            UART_send_char(temp[i], URATX);
}
void UART_send_float_string(const float *temp, int64_t lenth, uint64_t num, int32_t URATX)
{
    uint64_t i;
    for(i=0; i<num; i++)
        UART_send_float(temp[i],lenth, URATX);
}

void UART_recive_string(char *reciveBuf,int num, int32_t URATX)
{
    int i;
    for(i=0; i<num;i++)
        reciveBuf[i] = UART_recive_char(URATX);
}

void UART0_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);  //uart function
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 );     //equal to GPIOPadConfigSet()
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_1 );

    UARTStdioConfig(0, 115200, SysCtlClockGet());

    UARTFIFOEnable(UART0_BASE);    //
    UARTFIFOLevelSet(UART0_BASE,UART_FIFO_TX4_8, UART_FIFO_RX4_8);
    UARTIntEnable(UART0_BASE, UART_INT_RX);    //Recive error flag enable
}



