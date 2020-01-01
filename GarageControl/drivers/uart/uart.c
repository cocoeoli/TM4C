#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "uart.h"

extern uint8_t uart_flag;
extern uint8_t uart0_buff[20];
extern uint8_t uart5_buff[20];

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
    UARTIntEnable(UART0_BASE,UART_INT_RT);    //Recive error flag enable
}

//void UART1_Init(uint32_t ui32Baud)
//{
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
//    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
//
//    GPIOPinConfigure(GPIO_PB0_U1RX);
//    GPIOPinConfigure(GPIO_PB1_U1TX);
//    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
//
//    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC); //Clock 16MHz
//    UARTStdioConfig(1, ui32Baud, 16000000);
//    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);    //Recive error flag enable
//}

void UART5_Init(uint32_t Baud)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART5))
        ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE))
        ;

    GPIOPinConfigure(GPIO_PE4_U5RX);
    GPIOPinConfigure(GPIO_PE5_U5TX);
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), Baud, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

//    UARTIntRegister(UART5_BASE, IntHandler_UART5);
    UARTIntEnable(UART5_BASE, UART_INT_RX | UART_INT_RT);
//    IntEnable(INT_UART5);
}


void UART0IntHandler(void)
{
    uint16_t i=0;
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, ui32Status);
    while(UARTCharsAvail(UART0_BASE))
    {
        uart0_buff[i++] = (char)UARTCharGetNonBlocking(UART0_BASE);
    }
//    UART_send_char_string(uart0_buff, 10, UART0_BASE);
//    UART_send_char('\n', UART0_BASE);
    uart_flag |= 0x01;
//    Get_Pos_V = Get_Pos_V & 0xff;
//    UART_send_int32_t(Get_Pos_V, 1, UART0_BASE);
 //   UARTprintf("\n");
 //   sprintf(&var, "%d", Get_Pos_V);

}

void UART5IntHandler(void)
{
    uint16_t i=0;
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART5_BASE, true);
    UARTIntClear(UART5_BASE, ui32Status);
    while(UARTCharsAvail(UART5_BASE))
    {
        uart5_buff[i++] = (char)UARTCharGetNonBlocking(UART5_BASE);
    }
//    UART_send_char_string(uart5_buff, 15, UART5_BASE);
//    UART_send_char('\n', UART0_BASE);
     uart_flag |= 0x02;
//    Get_Pos_V = Get_Pos_V & 0xff;
//    UART_send_int32_t(Get_Pos_V, 1, UART0_BASE);
 //   UARTprintf("\n");
 //   sprintf(&var, "%d", Get_Pos_V);

}

//void UART1IntHandler(void)
//{
//    uint32_t ui32Status;
//    uint16_t i=0;
//    ui32Status = UARTIntStatus(UART1_BASE, true);
//    UARTIntClear(UART1_BASE, ui32Status);
//    while(UARTCharsAvail(UART1_BASE))
//    {
//        uart1_buff[i++] = (char)UARTCharGetNonBlocking(UART1_BASE);
//    }
//    uart_flag |= 0x02;
//}

//void Data1pro(void) //数据处理函数
//{
//    uint8_t char_num[2];
//    if(uart1_buff[1] == 'S')
//    {
//       char_num[0] = uart1_buff[2];
//       Distance[0][0] = 48;    //第一个点前方距离
//       switch(char_num[0])
//       {
//       case '1': {
//           Distance[1][1] = 90;  //第二点右侧距离
//           break;
//       }
//       case '2': {
//           Distance[1][1] = 54;
//           break;
//       }
//       case '3': {
//           Distance[1][1] = 28;
//          break;
//       }
//       case '4': {
//           Distance[1][1] = 2;
//           break;
//       }
//       case '5': {
//           Distance[1][1] = 86;
//           break;
//       }
//       case '6': {
//           Distance[1][1] = 46;
//           break;
//       }
//       }
//    }
//    if(uart1_buff[1] == 'D')
//    {
//        char_num[0] = uart1_buff[2];
//        char_num[1] = uart1_buff[3];
//        Distance[0][0] = 48;
//        switch(char_num[0])
//        {
//         case '1': {
//           Distance[1][1] = 90;  //第二点右侧距离
//           break;
//         }
//         case '2': {
//           Distance[1][1] = 54;
//           break;
//         }
//         case '3': {
//           Distance[1][1] = 28;
//          break;
//         }
//         case '4': {
//           Distance[1][1] = 2;
//           break;
//         }
//         case '5': {
//           Distance[1][1] = 86;
//           break;
//         }
//         case '6': {
//           Distance[1][1] = 46;
//           break;
//         }
//        }
//        switch(char_num[1])
//        {
//              case '1': {
//                  //设定一个左移距离
//                  break;
//              }
//              case '2': {
//                  break;
//              }
//              case '3': {
//                 //设定一个左移距离
//                 break;
//              }
//              case '4': {
//                  break;
//              }
//              case '5': {
//                  //设定一个左移距离
//                  break;
//              }
//              case '6': {
//                  break;
//              }
//        }
//    }
//}






