/*
 * Data_Rec.c
 *
 *  Created on: 2017年1月22日
 *      Author:wangkun
 *      uart1接收数据
 *      PB0-RX
 *      PB1-TX
 *      uart0发送数据
 *      接收到的数据存放在Receive_Data中
 *
 */
#include "My_UART.h"
#include "delay.h"
extern int Get_Distance_Data[3];


extern void UART0IntHandler(void);
extern void UART1IntHandler(void);
extern void UART2IntHandler(void);


void UART_INIT(void)
{

       ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
       ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
//       SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
//       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

       GPIOPinConfigure(GPIO_PB0_U1RX);
       GPIOPinConfigure(GPIO_PB1_U1TX);
//       GPIOPinConfigure(GPIO_PD6_U2RX);
//       GPIOPinConfigure(GPIO_PD7_U2TX);
       ROM_GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
//       ROM_GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);
//        Configure the UART for 115,200, 8-N-1 operation.

       ROM_UARTConfigSetExpClk(UART1_BASE, ROM_SysCtlClockGet(), 9600,
                               (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                                UART_CONFIG_PAR_NONE));
//       UARTConfigSetExpClk(UART2_BASE,  ROM_SysCtlClockGet(), 9600,
//                                     (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
//                                      UART_CONFIG_PAR_NONE));

 //      IntPrioritySet(INT_UART0,0x02);
       IntPrioritySet(INT_UART1,0x03);
       IntPrioritySet(INT_QEI0,0x01);
       IntPrioritySet(INT_QEI1,0x02);
//       IntPrioritySet(INT_UART2,0x04);    //RECEIVE PIC

//       UARTIntRegister(UART0_BASE,UART0IntHandler);
       UARTIntRegister(UART1_BASE,UART1IntHandler);
//       UARTIntRegister(UART1_BASE,UART2IntHandler);

       ROM_IntMasterEnable();
}
void Get_SDistance(int *Distance)
{
    memset(Get_Distance_Data,0,2);
    UARTCharPut(UART1_BASE,Get_Distance);
    delay_ms(100);
    *Distance = Get_Distance_Data[0] * 256 + Get_Distance_Data[1];
    return;
}
void Get_STemp(int *Shen_V)
{
    memset(Get_Distance_Data,0,2);
    UARTCharPut(UART1_BASE,Get_Temp);
    delay_ms(100);
    Get_Distance_Data[0] = Get_Distance_Data[0]-48;
    *Shen_V = Get_Distance_Data[0] * 0.61 + 331.45;    //shen su ji suan
    return;
}
void UART1_send_char(const char Byte)
{
    UARTCharPut(UART0_BASE, Byte);
}
//char UART1_recive_char(void)
//{
//    char Byte;
//    Byte = UARTCharGet(UART1_BASE);
//    return Byte;
//}
void UART1_send_string(const char *sendbuf)
{
    while(*sendbuf != '\0')
    {
        UART1_send_char(*sendbuf);
        sendbuf ++;
    }
}
//
//void UART1_send_int64_t(const int64_t temp,char on)
//{
//    int64_t temp_p = temp;
//
//    if(temp_p < 0)
//    {
//        UART1_send_char('-');
//        temp_p = 0-temp_p;
//    }
//    if(temp_p > 0)
//    {
//        UART1_send_int64_t(temp_p/10,0);
//        UART1_send_char(temp_p%10 + '0');
//    }
//    else if(temp_p == 0)
//    {
//        if(on)
//            UART1_send_char('0');
//    //  UART1_send_char('\n');
//    }
//}
//
//void UART1_send_int32_t(const int32_t temp,char on)
//{
//    UART1_send_int64_t((int64_t) temp,on);
//}
//
//void UART1_send_int16_t(const int16_t temp,char on)
//{
//    UART1_send_int64_t((int64_t) temp,on);
//}
//
//void UART1_send_float(const float temp,int64_t lenth)
//{
//    int64_t i;
//    float num = temp;
//    int64_t temp_p;
//   //发送整数部分
//    if(num<0)
//    {
//        UART1_send_char('-');
//        num = 0-num;
//    }
//    temp_p = (int64_t)num;
//    UART1_send_int64_t(temp_p,1);
//    UART1_send_char('.');
//    //发送n位小数
//    for(i=0; i<lenth; i++)
//    {
//        UART1_send_char(((int)(10*(num - temp_p)))%10 + '0');
//        num = num*10;
//        temp_p = (int64_t)num;
//    }
//
//}
//
//void UART1_send_int64_t_string(const int64_t *temp, uint64_t num)
//{
//    uint64_t i;
//    for(i=0; i<num; i++)
//        UART1_send_int64_t(temp[i],1);
//}
//void UART1_send_int32_t_string(const int32_t *temp, uint64_t num)
//{
//    uint64_t i;
//    for(i=0; i<num; i++)
//        UART1_send_int32_t(temp[i],1);
//}
//void UART1_send_int16_t_string(const int16_t *temp, uint64_t num)
//{
//    uint64_t i;
//    for(i=0; i<num; i++)
//        UART1_send_int16_t(temp[i],1);
//}
//void UART1_send_char_string(const unsigned char *temp, uint64_t num)
//{
//    uint64_t i;
//    for(i=0; i<num; i++)
//            UART1_send_char(temp[i]);
//}
//void UART1_send_float_string(const float *temp, int64_t lenth, uint64_t num)
//{
//    uint64_t i;
//    for(i=0; i<num; i++)
//        UART1_send_float(temp[i],lenth);
//}
//
//void UART1_recive_string(char *reciveBuf,int num)
//{
//    int i;
//    for(i=0; i<num;i++)
//        reciveBuf[i] = UART1_recive_char();
//}

