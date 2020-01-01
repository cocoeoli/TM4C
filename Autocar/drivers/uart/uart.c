#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "../PID/pid.h"

char uart0_buff[Buff0_Len];
char uart2_buff[Buff2_Len];
char uart1_buff[Buff1_Len];
char uart5_buff[Buff5_Len];

extern uint8_t Pose;
extern uint8_t uart_flag;
extern float set_yaw;
extern uint8_t PS2_flag;

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

//char DMAControlTable[1024];
//char udma_data[10];
//void Uart_dmainit(void)
//{
//            SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);     //时钟初始化
//            uDMAEnable();                                                            //模块使能
//            uDMAControlBaseSet(DMAControlTable);              //模块表
//            uDMAChannelAssign(UDMA_CH8_UART0RX);        //通道分配
//            uDMAChannelAttributeDisable(UDMA_CH8_UART0RX, UDMA_ATTR_USEBURST| UDMA_ATTR_HIGH_PRIORITY|        //失能相应功能
//                                                                    UDMA_ATTR_ALTSELECT| UDMA_ATTR_REQMASK);
//            uDMAChannelAttributeEnable(UDMA_CH8_UART0RX, UDMA_ATTR_REQMASK);
//            uDMAChannelControlSet(UDMA_CH8_UART0RX| UDMA_PRI_SELECT,                               //配置相应通道
//                                  UDMA_SIZE_8|  UDMA_SRC_INC_NONE| UDMA_DST_INC_NONE|  UDMA_ARB_8);
//            uDMAChannelTransferSet(UDMA_CH8_UART0RX|UDMA_PRI_SELECT,
//                                   UDMA_MODE_BASIC, (void*)(HWREG(UART0_BASE + UART_O_DR)), udma_data,10);
////            uDMAChannelTransferSet(UDMA_CH8_UART0RX|UDMA_PRI_SELECT,
////                                  UDMA_MODE_PINGPONG, (void*)(UART4_BASE+UART_O_DR),  remote_dataB,12);
//            uDMAChannelEnable(UDMA_CH8_UART0RX);
//}


void UART0_init(uint32_t Baud)
{
//    Uart_dmainit();                     //uart  dma
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);  //uart function
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 );     //equal to GPIOPadConfigSet()
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_1 );

//    UARTDMAEnable(UART0_BASE,UART_DMA_RX);
    UARTStdioConfig(0, Baud, SysCtlClockGet());

//    UARTFIFOEnable(UART0_BASE);
//    UARTFIFOLevelSet(UART0_BASE,UART_FIFO_TX4_8, UART_FIFO_RX7_8);

    IntPrioritySet(INT_UART0,0x01);
    UARTIntRegister(UART0_BASE,UART0IntHandler);
    UARTIntEnable(UART0_BASE, UART_INT_RT);        //Recive error flag enable
}

void UART1_Init(uint32_t ui32Baud)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC); //Clock 16MHz
    UARTStdioConfig(1, ui32Baud, 16000000);
    IntPrioritySet(INT_UART1,0x02);
    UARTIntRegister(UART1_BASE,UART1IntHandler);
    UARTIntEnable(UART1_BASE, UART_INT_RT);    //Recive error flag enable
}

void UART2_Init(uint32_t Baud)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART2);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART2)) ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOD))  ;

    GPIOPinConfigure(GPIO_PD6_U2RX);
    GPIOPinConfigure(GPIO_PD7_U2TX);
    GPIOPinTypeUART(GPIO_PORTD_BASE, GPIO_PIN_6 | GPIO_PIN_7);

    UARTConfigSetExpClk(UART2_BASE, SysCtlClockGet(), Baud, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntPrioritySet(INT_UART2,0x05);
   UARTIntRegister(UART2_BASE, UART2IntHandler);
    UARTIntEnable(UART2_BASE, UART_INT_RT);
//    IntEnable(INT_UART2);
}

void UART5_Init(uint32_t Baud)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART5)) ;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOE)) ;

    GPIOPinConfigure(GPIO_PE4_U5RX);
    GPIOPinConfigure(GPIO_PE5_U5TX);
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);

    UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), Baud, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
    IntPrioritySet(INT_UART5,0x08);
    UARTIntRegister(UART5_BASE, UART5IntHandler);
    UARTIntEnable(UART5_BASE, UART_INT_RT);
}

void UART0IntHandler(void)
{
    uint8_t i=0;
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, ui32Status);
    while(UARTCharsAvail(UART0_BASE))
    {
        uart0_buff[i++] = (char)UARTCharGetNonBlocking(UART0_BASE);
    }
    uart_flag = 0x01;

//    UART_send_string(uart5_buff, UART1_BASE);
//    UART_send_string("Interrupt uart0!!!\x0d\x0a", UART1_BASE);

}

void UART1IntHandler(void)
{
    uint32_t ui32Status;
    uint16_t i=0;
    ui32Status = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ui32Status);
    while(UARTCharsAvail(UART1_BASE))
    {
        uart1_buff[i++] = (char)UARTCharGetNonBlocking(UART1_BASE);
    }
    uart_flag = 0x02;
//    UART_send_string("Interrupt uart1!!!\x0d\x0a", UART1_BASE);
}

void UART2IntHandler(void)
{
    uint32_t ui32Status;
    uint16_t i=0;
    ui32Status = UARTIntStatus(UART2_BASE, true);
    UARTIntClear(UART2_BASE, ui32Status);
    while(UARTCharsAvail(UART2_BASE))
    {
        uart2_buff[i++] = (char)UARTCharGetNonBlocking(UART2_BASE);
        if( i > 7)
            break;
    }
//    uart2_buff[i] = '\0';
//    UART_send_string(uart2_buff , UART0_BASE );
//    UART_send_string("\n\x0d\x0a", UART0_BASE);
    uart_flag = 0x04;
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
    Change_pid();
//    UART_send_char_string(uart5_buff, 10, UART5_BASE);
//    UART_send_char_string("\r\n", 2, UART5_BASE);
    uart_flag = 0x10;


}

void Datapro(void) //数据处理函数
{
    uint8_t char_num[2];
//    if(uart1_buff[1] == 'S')
//    {
//       Car_mode = 1;
//       char_num[0] = uart1_buff[2];
//       Distance[0][0] = 530;    //第一个点前方距离
//       Distance[0][1] = 100;    //第一个点右方距离
//       switch(char_num[0])
//       {
//       case '1': {
//           gar_num = 1;
//           Distance[1][1] = 845;  //第二点右侧距离
//           break;
//       }
//       case '2': {
//           gar_num = 2;
//           Distance[1][1] = 584;
//           break;
//       }
//       case '3': {
//           gar_num = 3;
//           Distance[1][1] = 325;
//          break;
//       }
//       case '4': {
//           gar_num = 4;
//           Distance[1][1] = 65;
//           break;
//       }
//       case '5': {
//           gar_num = 5;
//           Distance[1][1] = 820;
//           break;
//       }
//       case '6': {
//           gar_num = 6;
//           Distance[1][1] = 420;
//           break;
//       }
//       }
//    }
    if(uart1_buff[1] == 'D')
    {
        char_num[0] = uart1_buff[2];
        char_num[1] = uart1_buff[3];
        uart1_buff[5] = '\0';
        if((char_num[0] > '0' && char_num[0] < '9') && (char_num[1] > '0' && char_num[1] < '9') )        //满足条件发给openmv
        {
            UART_send_string(uart1_buff, UART0_BASE);
            UART_send_string(uart1_buff, UART1_BASE);
        }
    }
    if(uart0_buff[1] == 'U')          //姿态控制
        {
           char_num[0] = uart0_buff[2];
           switch(char_num[0])
           {
           case '0': {
              Pose = 0;
         //     UART_send_string("Stop \n", UART1_BASE);
              break;
          }
           case '1': {                //前进
               Pose = 0x01;
         //      UART_send_string("Forward \n", UART1_BASE);
               break;
           }
           case '2': {
               Pose = 0x02;
        //       UART_send_string("Back \n", UART1_BASE);
               break;
           }
           case '3': {
               Pose = 0x04;
        //       UART_send_string("Left \n", UART1_BASE);
              break;
           }
           case '4': {
               Pose = 0x08;
       //        UART_send_string("Right \n", UART1_BASE);
               break;
           }
           case '5': {
                 set_yaw = 0;             //0度
       //          UART_send_string("0 C \n", UART1_BASE);
                 break;
             }
           case '6': {
                 set_yaw = 90;            //90
       //          UART_send_string("90 C \n", UART1_BASE);
                 break;
             }
           case '7': {
                 set_yaw = -180;
       //          UART_send_string("-180 \n", UART1_BASE);
                break;
             }
           case '8': {
                 set_yaw = -90;
       //          UART_send_string("-90 \n", UART1_BASE);
                 break;
             }
           }
        }
}

void PS2_Data_pro(void)
{
//    uint8_t char_num[2];
    switch(uart2_buff[0])
    {
        case 'A':           //前进
        {
            PS2_flag = 1;
//            uart2_buff[0] = 'J';
            break;
        }
        case 'B':           //后退
        {
            PS2_flag = 2;
//            uart2_buff[0] = 'J';
            break;
        }
        case 'C':           //向左平移
        {
            PS2_flag = 3;
//            uart2_buff[0] = 'J';
            break;
        }
        case 'D':           //向右平移
        {
            PS2_flag = 4;
//            uart2_buff[0] = 'J';
            break;
        }
        case 'J':           //停车
        {
            PS2_flag = 0;
            break;
        }
        case 'K'            ://左转
        {
            PS2_flag = 5;
            break;
        }
        case 'L':           //右转
        {
            PS2_flag = 6;
            break;
        }
//        default : PS2_flag = 0;
//                break;
    }
}






