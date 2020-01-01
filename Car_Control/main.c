#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/qei.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/rom.h"
#include "utils/uartstdio.h"

#include "Pwm_Control.h"
#include "QEI_Model.h"
#include "delay.h"
#include "oled.h"
#include "pid.h"
#include "My_UART.h"
#include "Gpio.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "Show.h"

#define OpenMV_STX 0xfe
#define Odroid_STX 0xfe
#define OpenMV_LEN 3
#define Odroid_LEN 10

int Receive_Data = 0;
uint32_t QEI0_Value = 0, QEI1_Value = 0;

int Get_Pos_V[2] = {0};
int Get_Distance_Data[3] = {0};
bool  UART0_INT_flag = 0;
int Shen_V = 0;
int Get_C_Distance = 0;

uint8_t rx_pbuffer=23;
uint8_t Rx_Pic_Buffer[4] = {0};
uint8_t Rx_Odroid_Buffer[10] = {0};
float Tar_X = 0,Tar_Y = 0;
float Get_Picture_Postion;
//receive car data order from odroid
float Car_Spped = 0;
float Car_Direction = 0;
float Car_Yaw = 0;

static uint8_t i =0;
bool start_receive = false;

int speed = 0;


short    GyroX, GyroY, GyroZ;//陀螺仪原始数据
short    AcceX, AcceY, AcceZ;//加速度传感器原始数据
float    pitch=0,roll=0,yaw=0;//欧拉角

int pid_result = 0;


void ConfigureUART0(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
//    IntPrioritySet(INT_UART0 ,0x40);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);

    UARTStdioConfig(0, 115200, 16000000);
}


void UART0IntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, ui32Status);
    while(UARTCharsAvail(UART0_BASE))
    {
        Get_Pos_V[0] = UARTCharGetNonBlocking(UART0_BASE);
        Get_Pos_V[1] = UARTCharGetNonBlocking(UART0_BASE);
        UART0_INT_flag =1;
    }
    Receive_Data = Get_Pos_V[0] * 256 + Get_Pos_V[1];
}

//void UART1IntHandler(void)
//{
//    uint32_t ui32Status;
//    ui32Status = UARTIntStatus(UART1_BASE, true);
//    UARTIntClear(UART1_BASE, ui32Status);
//    while(UARTCharsAvail(UART1_BASE))
//    {
//        Get_Distance_Data[0] = UARTCharGetNonBlocking(UART1_BASE);
//        Get_Distance_Data[1] = UARTCharGetNonBlocking(UART1_BASE);
//    }
//}

void UART1IntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ui32Status);
    while(UARTCharsAvail(UART1_BASE))
    {
        rx_pbuffer = UARTCharGetNonBlocking(UART1_BASE);
        if(rx_pbuffer == Odroid_STX)
        {
            i = 0;
            start_receive = 1;
        }
        if(start_receive == 1)
        {
            Rx_Odroid_Buffer[i++] = rx_pbuffer;
            if(i == OpenMV_LEN)
            {
                Car_Spped = (float)Rx_Odroid_Buffer[1];
                Car_Direction = (float)Rx_Odroid_Buffer[2];
                Car_Yaw = (float)Rx_Odroid_Buffer[3];
//                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
//                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
            }
            if(i >= Odroid_LEN)
            {
                i = 0;
                start_receive = 0;
                memset(Rx_Odroid_Buffer,0,10);
            }
        }
    }
}

void UART2IntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART1_BASE, true);
    UARTIntClear(UART1_BASE, ui32Status);
    while(UARTCharsAvail(UART1_BASE))
    {
        rx_pbuffer = UARTCharGetNonBlocking(UART1_BASE);
        if(rx_pbuffer == OpenMV_STX)
        {
            i = 0;
            start_receive = 1;
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
        }
        if(start_receive == 1)
        {
            Rx_Pic_Buffer[i++] = rx_pbuffer;
            if(i == OpenMV_LEN)
            {
                Tar_X = (float)Rx_Pic_Buffer[1];
                Tar_Y = (float)Rx_Pic_Buffer[2];
//                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
//                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
            }
            if(i >= OpenMV_LEN)
            {
                i = 0;
                start_receive = 0;
                memset(Rx_Pic_Buffer,0,3);
            }
        }
    }
}

void IntHandler_Timer0(void)
{
    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    static uint32_t Timer0A_Count = 0;
    Timer0A_Count++;

    if(Timer0A_Count == 4)
    {
        Timer0A_Count = 0;
        mpu_dmp_get_data(&pitch,&roll,&yaw);
    }
}
void IntHandler_Timer1(void)
{
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    static uint32_t Timer1A_Count = 0;
    Timer1A_Count++;

    if(Timer1A_Count == 2)
    {
        Timer1A_Count=0;
        ShowValue(1, (int16_t)yaw);
    }
}

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    FPUEnable();
    FPULazyStackingEnable();

    MoTor_Init();
    QEI0_Init(10);
    QEI1_Init(10);
    ConfigureUART0();
    UART_INIT();
    Led_Key_Init();

    PID_init();
    PIDP_init();

    MPU6050_Init();
    while(mpu_dmp_init())
        delay_ms(10);

    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_RT);
    IntEnable(INT_UART1);
//    while(1)
//    {
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, GPIO_PIN_1);
//        delay_ms(500);
//        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1, 0);
//        delay_ms(500);
//        if(key_scan() == 1)
//        {
//            UARTprintf("start unlock\n");
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
//            delay_s(1);
//            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0);
//            delay_s(1);
//            break;
//        }
//    }
    speed = 50;
    Steering_Gear_SET_Direction(0);
    MoTor_SET_Direction(1);
//    pid_result = 50 + Pid_Speed(50,QEI1_Value);
//    while(1)
//    {
//        mpu_dmp_get_data(&pitch,&roll,&yaw);
//        UARTprintf("Q0:%4d Q1:%4d\n", QEI0_Value, QEI1_Value);
//        delay_ms(100);
//        pid_result = pid_result + Pid_Speed(50,QEI1_Value);
//        MoTor_Left_Speed_Set(pid_result);
//        MoTor_Right_Speed_Set(50);
//
//        UARTprintf("   yaw is %d     roll is  % \d      Pitch is %d    \t",(int)yaw,(int)roll,(int)pitch);
//        UARTprintf("pid result is :%4d \t",pid_result);
//        //MoTor_Speed_Set(30,30);
//    }

    while(1)
    {
        mpu_dmp_get_data(&pitch,&roll,&yaw);
        UARTprintf("Q0:%4d Q1:%4d           ", QEI0_Value, QEI1_Value);
        delay_ms(100);
        UARTprintf("   yaw is %d     roll is  %d      Pitch is %d    \n",(short)yaw,(short)roll,(short)pitch);
        if(yaw > 0 && yaw < 30)
        {
            //Steering_Gear_SET_Direction(yaw * 3);
            MoTor_Speed_Set(1.1 * speed + yaw * 0.5, speed);
        }
        if(yaw >= 30 && yaw < 90)
        {
            //Steering_Gear_SET_Direction(45);
            MoTor_Speed_Set(1.3 * speed,speed);
        }
        if(yaw < 0 && yaw > -30)
        {
            //Steering_Gear_SET_Direction(yaw * 3);
            MoTor_Speed_Set(1.1 * speed, speed -(0.3 * yaw));
        }

        if(yaw > -90 && yaw <= - 30)
        {
            //Steering_Gear_SET_Direction(-45);
            MoTor_Speed_Set(1.1 * speed,1.3 * speed);
        }


//        Get_SDistance(&Get_C_Distance);
//        UARTprintf("   distance is %d\n",Get_C_Distance);
//
//        delay_ms(100);
//        Get_STemp(&Shen_V);
//        UARTprintf("   s_v is %d\n",Shen_V);
    }
}
//***********************编码器中断***********************//中断进入时间由QEI0_Init()设置
void IntHandler_QEI0(void)
{
    uint32_t ui32Status_Int = QEIIntStatus(QEI0_BASE, true);
    QEIIntClear(QEI0_BASE, ui32Status_Int);

    if(ui32Status_Int & QEI_INTTIMER)
    {
        QEI0_Value = QEIVelocityGet(QEI0_BASE)*50/13;//rpm(每分钟转数)
    }
//    if(ui32Status_Int & QEI_INTDIR)
//    {
//        QMotorDir_L = !QMotorDir_L;
//    }
}
void IntHandler_QEI1(void)
{
    uint32_t ui32Status_Int = QEIIntStatus(QEI1_BASE, true);
    QEIIntClear(QEI1_BASE, ui32Status_Int);

    if(ui32Status_Int & QEI_INTTIMER)
    {
        QEI1_Value = QEIVelocityGet(QEI1_BASE)*50/13;//rpm（每分钟转数）
    }
//    if(ui32Status_Int & QEI_INTDIR)
//    {
//        QMotorDir_R = !QMotorDir_R;
//    }
}
